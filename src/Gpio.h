#pragma once

#include <memory>

namespace gpio_dev
{

class GpioChip;

class Gpio
{
public:
    Gpio(unsigned int m_line, const std::shared_ptr<GpioChip>& gpioChip);
    ~Gpio();

    void setValue(uint8_t value);
    uint8_t value() const;

private:
    unsigned int m_line;
    std::shared_ptr<GpioChip> m_gpioChip;
};

} // gpio_dev