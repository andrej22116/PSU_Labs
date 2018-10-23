#include <iostream>
#include <cstdint>
#include <string>
#include <iterator>
#include <algorithm>

//#include <bcm2835.h>
#ifdef BCM2835_H

#define PIN RPI_V2_GPIO_PI_12
#define PWM_CHANNEL 0
#define RANGE 100

#endif

enum CommandLineStatusAction {
    InvalidAction = -1,
    InvalidArgument = -2,
    SetPower = 1,
    SetPulseWidth = 2
};

struct CommandLineParams {
    CommandLineStatusAction action;
    union {
        bool enable;
        int8_t pulseWidth;
    } param;
};

CommandLineParams parseArgs(int argc, char** argv);
CommandLineStatusAction getActionFromString(const std::string& actionStr);
std::string toLowerStr(const std::string& str);

#ifdef BCM2835_H
    bool initForSetPulseWidth();
    bool initForSetPower();
#endif
void bcm2835_setPinPower(bool isEnable);
void bcm2835_setPinPulseWidth(int8_t width);

int main(int argc, char** argv)
{
#ifdef BCM2835_H
    if ( !init() ) { return 1; }
#endif

    CommandLineParams params = parseArgs(argc, argv);
    if ( params.action == CommandLineStatusAction::InvalidAction ) {
        std::cerr << "Bad arguments: Invalid action!" << std::endl;
        return 2;
    }
    else if ( params.action == CommandLineStatusAction::InvalidArgument ) {
        std::cerr << "Bad arguments: Invalid action argument!" << std::endl;
        return 3;
    }
    else if ( params.action == CommandLineStatusAction::SetPower ) {
        bcm2835_setPinPower(params.param.enable);
    }
    else if ( params.action == CommandLineStatusAction::SetPulseWidth ) {
        bcm2835_setPinPulseWidth(params.param.pulseWidth);
    }

    return 0;
}

void bcm2835_setPinPower(bool isEnable)
{
#ifdef BCM2835_H
    initForSetPower();
    bcm2835_gpio_write(PIN, isEnable);
#endif
}

void bcm2835_setPinPulseWidth(int8_t width)
{
#ifdef BCM2835_H
    initForSetPulseWidth();
    bcm2835_pwm_set_data(PWM_CHANNEL, width);
#endif
}


CommandLineParams parseArgs(int argc, char** argv)
{
    CommandLineParams params;

    if ( argc == 1 ) {
        params.action = CommandLineStatusAction::SetPulseWidth;
        params.param.pulseWidth = 50;
        return params;
    }
    if ( argc != 3 ) {
        params.action = CommandLineStatusAction::InvalidAction;
        return params;
    }

    params.action = getActionFromString(argv[1]);
    if ( params.action == CommandLineStatusAction::SetPower ) {
        auto status = toLowerStr(argv[2]);

        if ( status == "on" ) {
            params.param.enable = true;
        }
        else if ( status == "off" ) {
            params.param.enable = false;
        }
        else {
            params.action = CommandLineStatusAction::InvalidArgument;
        }
    }
    else if ( params.action == CommandLineStatusAction::SetPulseWidth ) {
        std::string arg = argv[2];
        if (arg.length() > 3) {
            params.action = CommandLineStatusAction::InvalidArgument;
        }

        for (auto ch : arg) {
            if (ch < '0' || ch > '9') {
                params.action = CommandLineStatusAction::InvalidArgument;
                return params;
            }
        }

        const char* beginPtr = arg.c_str();
        const char* endPtr = beginPtr + arg.length();
        char* endParsePointer = nullptr;

        auto number = std::strtol(beginPtr, &endParsePointer, 10);

        if ( endParsePointer != endPtr || number < 0 || number > 100 ) {
            params.action = CommandLineStatusAction::InvalidArgument;
        }
        else {
            params.param.pulseWidth = number;
        }
    }

    return params;
}

CommandLineStatusAction getActionFromString(const std::string& actionStr)
{
    std::string str = toLowerStr(actionStr);

    CommandLineStatusAction action = CommandLineStatusAction::InvalidAction;

    if ( str == "power" ) {
        action = CommandLineStatusAction::SetPower;
    }
    else if ( str == "pulse-width" ) {
        action = CommandLineStatusAction::SetPulseWidth;
    }

    return action;
}

std::string toLowerStr(const std::string& str)
{
    std::string resStr;
    std::back_insert_iterator<std::string> inserter(resStr);
    std::transform(str.begin(), str.end(), inserter, ::tolower);
    return resStr;
}

#ifdef BCM2835_H
bool initForSetPulseWidth()
{
    //! Инициализация библиотеки.
    if ( !bcm2835_init() ) { return false; }

    //! Установка режима дополнительных функций.
    //! Для порта GPIO 12 это режим Alt5
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_ALT5);

    //! Установка делителя тактовой частоты для управления шириной импульса
    bcm2835_pwm_set_clock(BCM2835_PWM_CLOCK_DIVIDER_1);

    /*! Установка режима канала PWM
        Второй параметр - включение режима markspace
        Третий параметр - включение канала PWM
    */
    bcm2835_pwm_set_mode(PWM_CHANNEL, true, true);

    //! Установка максимального значения диапазона вывода ШИМ (от 0 до RANGE)
    bcm2835_pwm_set_range(PWM_CHANNEL, RANGE);

    return true;
}

bool initForSetPower()
{
    //! Инициализация библиотеки.
    if ( !bcm2835_init() ) { return false; }

    //! Установка режима вывода на пин.
    bcm2835_gpio_fsel(PIN, BCM2835_GPIO_FSEL_OUTP);
}
#endif
