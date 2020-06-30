#ifndef MPU_6050_HPP
#define MPU_6050_HPP
#include "hwlib.hpp"
#include "registermap.hpp"

class MPU_6050  {
    private :
    hwlib::i2c_bus &bus;
    uint8_t address = 0x68;
    uint8_t registerToSelect;
    uint8_t registerToCombine;

    public :
    /// \brief
    /// Constructor for MPU_6050
    /// \details
    /// This constructor is used to construct a selected register of the 
    /// MPU-6050. The bus is needed to send data to the selected register.
    MPU_6050(hwlib::i2c_bus &bus,uint8_t  registerToSelect):
        bus(bus),
        registerToSelect(registerToSelect)
    {}
    /// \brief
    /// Return value
    /// \details
    /// This function is used to write and read the selected register of the
    /// MPU-6050 and return the value of the selected register. 
    uint16_t value();
    
    /// \brief
    /// wake up call
    /// \details
    /// This function is used to wake the sensor up. If the 
    /// MPU-6050 is disconnected from the energy source, he will
    /// be in the sleep state. To wake him up you need to use this function
    /// to read and write transactions from the GY-521. 
    void wakeUpCall();

    /// \brief
    /// Combines value
    /// \details
    /// This function is used to write and read the selected registers and
    /// combines the values and returns it, to get both the plus and minus
    /// values of one sensor.
    uint16_t combineValue(uint8_t registerToCombine);
};

#endif