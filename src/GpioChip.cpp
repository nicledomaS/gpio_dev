#include "GpioChip.h"
#include "GpioUtils.h"

#include <iostream>

#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <linux/gpio.h>

namespace gpio_dev
{

namespace
{
    
    int open(const std::string& devName)
    {
        // TODO: throw exception 
        
        return ::open(devName.c_str(), 0);
    }

    std::unique_ptr<gpiochip_info> initChipInfo(int fd)
    {
        auto chipInfo = std::make_unique<gpiochip_info>();
        getChipInfo(fd, *chipInfo);

        // TODO: throw exception 

        return chipInfo;
    }

} // anonymous

GpioChip::GpioChip(const std::string& devName, const std::string& label)
    : m_fd(open(devName)),
    m_label(label),
    m_chipInfo(initChipInfo(m_fd)),
    m_gpioData(std::make_unique<gpiohandle_data>())
{
}

GpioChip::~GpioChip()
{
    close(m_fd);
}

void GpioChip::registerLine(unsigned int line)
{
    m_lines.insert(line);
    doRequestLine();
}

void GpioChip::unregisterLine(unsigned int line)
{
    m_lines.erase(line);
    doRequestLine();
}

void GpioChip::setValue(unsigned int line, uint8_t value)
{
    auto pos = findLine(line);
    if(pos >= 0)
    {
        m_gpioData->values[pos] = value;
        setValues(m_fdSetter, *m_gpioData);
    }
    else
    {
        // TODO: throw exception
    } 
}

uint8_t GpioChip::getValue(unsigned int line)
{
    auto pos = findLine(line);
    if(pos >= 0 && getValues(m_fdSetter, *m_gpioData) >= 0)
    {
        return m_gpioData->values[pos];
    }
    else
    {
        std::cout << "Error: " << strerror(errno) << std::endl;
        // TODO: throw exception
    } 
    return 0;
}

int GpioChip::findLine(unsigned int line) const
{
    const auto& it = m_lines.find(line);
    // TODO: throw exception

    return std::distance(m_lines.begin(), it);
}

void GpioChip::doRequestLine()
{
    close(m_fdSetter);
    m_fdSetter = requestLine(m_fd, m_lines, GPIOHANDLE_REQUEST_OUTPUT, *m_gpioData, m_label);
}

} // gpio_dev