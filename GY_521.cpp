#include "GY_521.hpp"
#include "hwlib.hpp"
#include "registermap.hpp"

    uint16_t GY_521::value(){
        GY_521::bus.i2c_bus::write(GY_521::address).write(GY_521::registerToSelect);
        uint8_t returnValue =  GY_521::bus.i2c_bus::read(GY_521::address).read_byte();
        return returnValue;
    }

    void GY_521::wakeUpCall(hwlib::i2c_bus &bus){
        GY_521::bus.i2c_bus::write(GY_521::address);
        bus.write(WAKE_UP);
        bus.write(0);
    }

    uint16_t GY_521::combineValue(uint8_t registerToCombine)
    {    GY_521::bus.i2c_bus::write(GY_521::address).write(GY_521::registerToSelect);
        uint8_t firstValue =  GY_521::bus.read(GY_521::address).read_byte();

        GY_521::bus.i2c_bus::write(GY_521::address).write(registerToCombine);
        uint8_t secondValue =  GY_521::bus.read(GY_521::address).read_byte();
        return static_cast<int>(firstValue<<8 | secondValue);
    }





