#include "hwlib.hpp"
#include "GY_521.hpp"
#include "registermap.hpp"
#include <vector>
//-----------------Address of the MPU-6050---------------------------------------
uint_fast8_t address = 0x68 ;

int main( void )
{
auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
hwlib::i2c_bus_bit_banged_scl_sda bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda );

//-----------------Wake up the module---------------------------------------
{
auto start = bus.i2c_bus::write(address);
start.write(WAKE_UP);
start.write(0);
}

//----------------GY_521 REGISTORS------------------------------------

GY_521 y_out_l(bus,address,ACCEL_YOUT_H);
GY_521 y_out_h(bus,address,ACCEL_YOUT_L );

hwlib::target::pin_out

//-----------------Led Pins---------------------------------------
auto right_led1 = hwlib::target::pin_out(hwlib::target::pins::d6);
auto right_led2 = hwlib::target::pin_out(hwlib::target::pins::d5);
auto right_led3 = hwlib::target::pin_out(hwlib::target::pins::d4);
auto right_led4 = hwlib::target::pin_out(hwlib::target::pins::d3);
auto right_led5 = hwlib::target::pin_out(hwlib::target::pins::d2);
auto left_led1 = hwlib::target::pin_out(hwlib::target::pins::d7);
auto left_led2 = hwlib::target::pin_out(hwlib::target::pins::d8);
auto left_led3 = hwlib::target::pin_out(hwlib::target::pins::d9);
auto left_led4 = hwlib::target::pin_out(hwlib::target::pins::d10);
auto left_led5 = hwlib::target::pin_out(hwlib::target::pins::d11);

while(1){

    left_led1.write(0);left_led2.write(0);left_led3.write(0);left_led4.write(0);left_led5.write(0);
    right_led1.write(0);right_led2.write(0);right_led3.write(0);right_led4.write(0);right_led5.write(0);

//-----------------read and combine the values---------------------------------------
    int combinedValue = static_cast<int>(y_out_l.value() <<8 | y_out_h.value());


//-----------------Values for base ---------------------------------------
    if(combinedValue >= 65000 && combinedValue < 65550){
        left_led1.write(1);
        right_led1.write(1);
    }

//-----------------Values for the left side------------------------------
    if(combinedValue < 65000 && combinedValue >= 63000){
        left_led1.write(1);left_led2.write(1);
    }
    if(combinedValue < 63000 && combinedValue >= 61000){
        left_led2.write(1);left_led3.write(1);
    }
    if(combinedValue < 61000 && combinedValue >= 59000){
        left_led3.write(1);left_led4.write(1);
    }
    if(combinedValue < 59000 && combinedValue >= 56000){
        left_led4.write(1);left_led5.write(1);
    }

//-----------------Values for the right side------------------------------
    if((combinedValue >= 65550)||(combinedValue > 0 && combinedValue <= 900)){
        right_led1.write(1);right_led2.write(1);
    }
    if(combinedValue > 900 && combinedValue <= 2100){
        right_led2.write(1);right_led3.write(1);
    }
    if(combinedValue > 2100 && combinedValue <= 4000){
        right_led3.write(1);right_led4.write(1);
    }
    if(combinedValue > 4000 && combinedValue < 48000){
        right_led4.write(1);right_led5.write(1);
    }

//-----------------cout visuals on terminal--------------------------------------
    left_led1.flush();
    hwlib::cout << "accy: " << hwlib::setw( 4 ) << combinedValue << "\n";
    hwlib::wait_ms( 300);
}
}
