#include "hwlib.hpp"


uint8_t read(hwlib::i2c_bus &bus, int deviceAddress, uint8_t registerToRead){
    bus.write(deviceAddress).write(registerToRead);
    uint8_t returnValues =  bus.read(deviceAddress).read_byte();
    return returnValues;
    }

void setbit(hwlib::i2c_bus &bus, int deviceAddress, uint8_t registerToRead, uint8_t bit){
    bus.write(deviceAddress).write(registerToRead);
    }



int main( void )
{
uint_fast8_t address = 0x68; //address mpu

auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
/*
auto right_led1 = hwlib::target::pin_out(hwlib::target::pins::d2);
auto right_led2 = hwlib::target::pin_out(hwlib::target::pins::d3);
auto right_led3 = hwlib::target::pin_out(hwlib::target::pins::d4);
auto right_led4 = hwlib::target::pin_out(hwlib::target::pins::d5);
auto right_led5 = hwlib::target::pin_out(hwlib::target::pins::d6);
*/
auto left_led1 = hwlib::target::pin_out(hwlib::target::pins::d7);
auto left_led2 = hwlib::target::pin_out(hwlib::target::pins::d8);
auto left_led3 = hwlib::target::pin_out(hwlib::target::pins::d9);
auto left_led4 = hwlib::target::pin_out(hwlib::target::pins::d10);
auto left_led5 = hwlib::target::pin_out(hwlib::target::pins::d11);


hwlib::i2c_bus_bit_banged_scl_sda bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );


{hwlib::i2c_write_transaction start = ((hwlib::i2c_bus*)(&bus))->write(address);
start.write(0x6B);
start.write(0);
}
while(1){
    int16_t value = read(bus,address, 61);
    int16_t value2 = read(bus,address, 62);

    int comValue = static_cast<int>(value <<8 | value2);


//-----------------Values for base---------------------------------------
    if(comValue <200 && comValue > +0){
        left_led1.write(0);left_led2.write(0);left_led3.write(0);left_led4.write(0);left_led5.write(0);
        left_led1.flush();
    }
    if(comValue >= 64900){
        left_led1.write(0);left_led2.write(0);left_led3.write(0);left_led4.write(0);left_led5.write(0);
        left_led1.flush();
    }
//-----------------Values for the left side------------------------------
    if(comValue < 64900 && comValue >= 63000){
        left_led1.write(1);left_led2.write(0);left_led3.write(0);left_led4.write(0);left_led5.write(0);
        left_led1.flush();
    }
    if(comValue < 63000 && comValue >= 61000){
        left_led1.write(1);left_led2.write(1);left_led3.write(0);left_led4.write(0);left_led5.write(0);
        left_led1.flush();
    }
    if(comValue < 61000 && comValue >= 59000){
        left_led1.write(1);left_led2.write(1);left_led3.write(1);left_led4.write(0);left_led5.write(0);
        left_led1.flush();
    }
    if(comValue < 59000 && comValue >= 57000){
        left_led1.write(1);left_led2.write(1);left_led3.write(1);left_led4.write(1);left_led5.write(0);
        left_led1.flush();
    }
    if(comValue < 57000 && comValue > 48000){
        left_led1.write(1);left_led2.write(1);left_led3.write(1);left_led4.write(1);left_led5.write(1);
        left_led1.flush();
    }
//-----------------Values for the right side------------------------------
    if(comValue > 200 && comValue <= 900){
        hwlib::cout <<"ledje 1"<< "\n";
    }
    if(comValue > 900 && comValue <= 2100){
        hwlib::cout <<"ledje 1"<< "\n";
        hwlib::cout <<"ledje 2"<< "\n";
    }
    if(comValue > 2100 && comValue <= 4000){
        hwlib::cout <<"ledje 1"<< "\n";
        hwlib::cout <<"ledje 2"<< "\n";
        hwlib::cout <<"ledje 3"<< "\n";
    }
    if(comValue > 4000 && comValue < 48000){
        hwlib::cout <<"ledje 1"<< "\n";
        hwlib::cout <<"ledje 2"<< "\n";
        hwlib::cout <<"ledje 3"<< "\n";
        hwlib::cout <<"ledje 4"<< "\n";
    }

    hwlib::cout << "accy: " << hwlib::setw( 4 ) << comValue << "\n";
    hwlib::wait_ms( 300);
}
}
