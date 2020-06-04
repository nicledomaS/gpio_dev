#pragma once

#include <memory>
#include <set>
#include <string>

struct gpiochip_info;
struct gpioline_info;

struct gpiohandle_data;

namespace gpio_dev
{

int getChipInfo(int fd, gpiochip_info& chipInfo);
int getLineInfo(int fd, unsigned int line, gpioline_info& lineInfo);

int requestLine(
    int fd,
    const std::set<unsigned int>& lines,
    unsigned int flag,
    gpiohandle_data& data,
    const std::string& consumerLabel);

int getValues(int fd, gpiohandle_data& data);
int setValues(int fd, const gpiohandle_data& data);

} // gpio_dev