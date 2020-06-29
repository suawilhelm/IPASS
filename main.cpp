#include "hwlib.hpp"
#include "GY_521.hpp"
#include "registermap.hpp"
#include <vector>
int main( void )
{
auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
hwlib::i2c_bus_bit_banged_scl_sda bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda);

//----------------GY_521 REGISTORS------------------------------------
GY_521 y_out_h(bus,ACCEL_YOUT_H);
//-----------------Wake up the module---------------------------------
y_out_h.wakeUpCall(bus);
//-----------------Led Pins-------------------------------------------
hwlib::target::pin_out leds_left[5]={hwlib::target::pins::d6, hwlib::target::pins::d5, hwlib::target::pins::d4,
                                    hwlib::target::pins::d3, hwlib::target::pins::d2};

hwlib::target::pin_out leds_right[5]={hwlib::target::pins::d11, hwlib::target::pins::d10,
                                    hwlib::target::pins::d9, hwlib::target::pins::d8, hwlib::target::pins::d7};

while(1){
    for(unsigned int i = 0; i < 5; i++){
        leds_left[i].write(0);
        leds_right[i].write(0);
    }
//-----------------read and combine the values------------------------
    int measurment  = y_out_h.combineValue(ACCEL_YOUT_L);

//-----------------Measurment values for left and right---------------
    int left_side_measurment = 65-(measurment /1000);
    int right_side_measurment = 4-(measurment /1000);

//-----------------Values for base-----------------------------------
    if(measurment  >= 65000 && measurment  < 65550){
        leds_left[0].write(1);
        leds_right[4].write(1);
    }
    
//-----------------algorithm for left side----------------------------
    else if(measurment  < 65000 && measurment > 48000){
            if(left_side_measurment > 3){
                left_side_measurment = 4;
            }
            leds_left[left_side_measurment-1].write(1);leds_left[left_side_measurment].write(1);
    }

//-----------------algorithm for right side---------------------------
    else if((measurment  >= 65550)||(measurment  >= 0 && measurment  <= 1000)|(measurment  > 1000 && measurment  <= 48000)){
            if(right_side_measurment < 1){
                right_side_measurment = 1;}
        leds_right[right_side_measurment-1].write(1);leds_right[right_side_measurment].write(1);
    }
//-----------------cout visuals on terminal---------------------------
    leds_left[0].flush();
    hwlib::cout << "accy: " << hwlib::setw( 4 ) << measurment  << "\n";
    hwlib::wait_ms( 300);
}
}
