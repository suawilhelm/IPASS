//          Copyright Sua Wilhelm  2020.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          https://www.boost.org/LICENSE_1_0.txt)
#include "mpu_6050.hpp"
#include "hwlib.hpp"
#include "registermap.hpp"
    
    uint16_t MPU_6050::value(){
        MPU_6050::bus.i2c_bus::write(MPU_6050::address).write(MPU_6050::registerToSelect);
        uint8_t returnValue =  MPU_6050::bus.i2c_bus::read(MPU_6050::address).read_byte();
        return returnValue;
    }

    void MPU_6050::wakeUpCall(){
        auto start = MPU_6050::bus.i2c_bus::write(MPU_6050::address);
        start.write(WAKE_UP);
        start.write(0);
    }

    uint16_t MPU_6050::combineValue(uint8_t registerToCombine)
    {    MPU_6050::bus.i2c_bus::write(MPU_6050::address).write(MPU_6050::registerToSelect);
        uint8_t firstValue =  MPU_6050::bus.read(MPU_6050::address).read_byte();

        MPU_6050::bus.i2c_bus::write(MPU_6050::address).write(registerToCombine);
        uint8_t secondValue =  MPU_6050::bus.read(MPU_6050::address).read_byte();
        return static_cast<int>(firstValue<<8 | secondValue);
    }





