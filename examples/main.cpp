#include "GpioChip.h"
#include "Gpio.h"

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#include <linux/gpio.h>
#include <sys/ioctl.h>

#include <chrono>
#include <thread>
#include <iostream>

constexpr auto DeviceName = "/dev/gpiochip1";

int main (int argc, char** argv)
{
    std::cout << "Start program" << std::endl;

    auto chip = std::make_shared<gpio_dev::GpioChip>(DeviceName, "GpioProto");
    gpio_dev::Gpio gpio_0(0, chip);
    gpio_dev::Gpio gpio_1(1, chip);

    bool check = false;

    while(true)
    {
        std::this_thread::sleep_for(std::chrono::seconds(1));
        
        auto value_0 = gpio_0.value();
        auto value_1 = gpio_1.value();

        std::cout << "Current value_0: " << std::to_string(value_0) << std::endl;
        std::cout << "Current value_1: " << std::to_string(value_1) << std::endl;

        gpio_0.setValue(check ? 1 : 0);
        gpio_1.setValue(check ? 0 : 1);

        check = !check;
    }

    return 0;
}

// void printLineInformation(int fd, const gpiochip_info& info)
// {
//     for(int i = 0; i < info.lines; ++i)
//     {
//         struct gpioline_info linfo;
//         int ret = gpio_lib::getLineInfo(fd, i, linfo);
//         if (ret == -1) {
//             ret = -errno;
//             std::cerr << "Failed to issue LINEINFO IOCTL" << std::endl;
//             break;
//         }

//         std::cout << "Line name: "
//                     << std::string(linfo.name[0] == 0 ? "Unnamed" : linfo.name)
//                     << ", Consumer: " 
//                     << std::string(linfo.consumer[0] == 0 ? "Unused" : linfo.consumer)
//                     << ", Flag: "
//                     << std::to_string(linfo.flags)
//                     << std::endl;
//     }
// }