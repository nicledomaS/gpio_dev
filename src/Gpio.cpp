#include "Gpio.h"
#include "GpioChip.h"

namespace gpio_dev
{

Gpio::Gpio(unsigned int line, const std::shared_ptr<GpioChip>& gpioChip)
    : m_line(line),
    m_gpioChip(gpioChip)
{
    m_gpioChip->registerLine(m_line);
}

Gpio::~Gpio()
{
    m_gpioChip->unregisterLine(m_line);
}

void Gpio::setValue(uint8_t value)
{
    m_gpioChip->setValue(m_line, value);
}

uint8_t Gpio::value() const
{
    return m_gpioChip->getValue(m_line);
}

} // gpio_dev