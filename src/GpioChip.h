#pragma once

#include <memory>
#include <set>

struct gpiochip_info;
struct gpiohandle_data;

namespace gpio_lib
{

class GpioChip
{
public:
    GpioChip(const std::string& devName, const std::string& label);
    ~GpioChip();

    void registerLine(unsigned int line);

    void setValue(unsigned int line, uint8_t value);
    uint8_t getValue(unsigned int line);

private:
    int findLine(unsigned int line) const;

private:
    int m_fd;
    int m_fdSetter = -1;
    std::string m_label;
    std::set<unsigned int> m_lines;
    std::unique_ptr<gpiochip_info> m_chipInfo;
    std::unique_ptr<gpiohandle_data> m_gpioData;
};

} // gpio_lib