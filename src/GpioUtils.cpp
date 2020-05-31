#include "GpioUtils.h"

#include <linux/gpio.h>
#include <sys/ioctl.h>

#include <string.h>

namespace gpio_lib
{

int getChipInfo(int fd, gpiochip_info& chipInfo)
{
    memset(&chipInfo, 0, sizeof(gpiochip_info));
    return ioctl(fd, GPIO_GET_CHIPINFO_IOCTL, &chipInfo);
}

int getLineInfo(int fd, unsigned int line, gpioline_info& lineInfo)
{
    memset(&lineInfo, 0, sizeof(gpioline_info));
    lineInfo.line_offset = line;
    return ioctl(fd, GPIO_GET_LINEINFO_IOCTL, &lineInfo);
}

int requestLine(
    int fd,
    const std::set<unsigned int>& lines,
    unsigned int flag,
    gpiohandle_data& data,
    const std::string& consumerLabel)
{
    gpiohandle_request req;
    memset(&req, 0, sizeof(gpiohandle_request));
    memset(&data, 0, sizeof(gpiohandle_data));
    
    strcpy(req.consumer_label, consumerLabel.c_str());
    req.flags = flag;
    req.lines = lines.size();

    size_t idx = 0;
    for(const auto& line : lines)
    {
        req.lineoffsets[idx++] = line;
    }

    if (flag & GPIOHANDLE_REQUEST_OUTPUT)
    {
        memcpy(req.default_values, &data, sizeof(req.default_values));
    }

    auto ret = ioctl(fd, GPIO_GET_LINEHANDLE_IOCTL, &req);

    return ret < 0 ? ret : req.fd; 
}

int getValues(int fd, gpiohandle_data& data)
{
    return ioctl(fd, GPIOHANDLE_GET_LINE_VALUES_IOCTL, &data);
}

int setValues(int fd, const gpiohandle_data& data)
{
    return ioctl(fd, GPIOHANDLE_SET_LINE_VALUES_IOCTL, &data);
}

} // gpio_lib