//----------------Main code for the GY-521 spirit level---------------
#include "hwlib.hpp"
#include "mpu_6050.hpp"
#include "registermap.hpp"
int main( void )
{
//----------------MPU_6050 REGISTORS------------------------------------
auto scl = hwlib::target::pin_oc( hwlib::target::pins::scl );
auto sda = hwlib::target::pin_oc( hwlib::target::pins::sda );
hwlib::i2c_bus_bit_banged_scl_sda bus = hwlib::i2c_bus_bit_banged_scl_sda( scl,sda);

//----------------MPU_6050 REGISTORS------------------------------------
MPU_6050 y_out_h(bus,ACCEL_YOUT_H);

//-----------------Wake up the module---------------------------------
y_out_h.wakeUpCall();

//-----------------Led Pins-------------------------------------------
hwlib::target::pin_out ledbar_left[5]={hwlib::target::pins::d6, hwlib::target::pins::d5, hwlib::target::pins::d4,
                                    hwlib::target::pins::d3, hwlib::target::pins::d2};

hwlib::target::pin_out ledbar_right[5]={hwlib::target::pins::d11, hwlib::target::pins::d10,
                                    hwlib::target::pins::d9, hwlib::target::pins::d8, hwlib::target::pins::d7};

auto green_led = hwlib::target::pin_out(hwlib::target::pins::d12);

while(1){
//-----------------turn all ledbar off----------------------------------
    for(unsigned int i = 0; i < 5; i++){
        ledbar_left[i].write(0);
        ledbar_right[i].write(0);
        green_led.write(0);
    }
//-----------------read and combine the values------------------------
    int measurement  = y_out_h.combineValue(ACCEL_YOUT_L);

//-----------------measurement values for left and right---------------
    int left_side_measurement = 65-(measurement /1000);
    int right_side_measurement = 4-(measurement /1000);

//-----------------Values for base horizontal-------------------------
//------this statement is used to see if its leveled------
    if(measurement  >= 65000 && measurement  < 65550){
        ledbar_left[0].write(1);
        ledbar_right[4].write(1);
    }

//-----------------base Values for vertical---------------------------
//------this statement is used to see if a corner is 90 degerees------
    if(measurement  >= 48000 && measurement  < 49020){
        green_led.write(1);
    }

//-----------------algorithm for left side----------------------------
    else if(measurement  < 65000 && measurement > 48000){
            if(left_side_measurement > 3){
                left_side_measurement = 4;
            }
            ledbar_left[left_side_measurement-1].write(1);ledbar_left[left_side_measurement].write(1);
    }

//-----------------algorithm for right side---------------------------
    else if((measurement  >= 65550)||(measurement  >= 0 && measurement  <= 1000)|(measurement  > 1000 && measurement  <= 48000)){
            if(right_side_measurement < 1){
                right_side_measurement = 1;}
        ledbar_right[right_side_measurement-1].write(1);ledbar_right[right_side_measurement].write(1);
    }

//-----------------cout visuals on terminal---------------------------
    ledbar_left[0].flush();
    hwlib::cout << "accy: " << hwlib::setw( 4 ) << measurement  << "\n";
    hwlib::wait_ms( 300);
}
}
