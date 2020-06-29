#ifndef GY_521_HPP
#define GY_521_HPP
#include "hwlib.hpp"
#include "registermap.hpp"

class GY_521  {
    private :
    hwlib::i2c_bus &bus;
    uint8_t address = 0x68;
    uint8_t registerToSelect;
    uint8_t registerToCombine;

    public :
    /// \brief
    /// Constructor for GY_521
    /// \details
    /// This constructor is used to construct a selected register of the 
    /// GY-521.
    GY_521(hwlib::i2c_bus &bus,uint8_t  registerToSelect):
        bus(bus),
        registerToSelect(registerToSelect)
    {}

    /// \brief
    /// Return value
    /// \details
    /// This function is used to write and read the selected register of the
    /// GY-521 and return the value of the selected register.
    uint16_t value();
    
    /// \brief
    /// wake up call
    /// \details
    /// This function is used to wake the sensor up. If the 
    /// GY-521 is disconnected from the energy source, he will
    /// be in the sleep state. To wake him up u need to use this function
    /// to read and write transactions. 
    void wakeUpCall(hwlib::i2c_bus &bus);

    /// \brief
    /// Combines value
    /// \details
    /// This function is used to write and read the selected registers and
    /// combines the values and returns it. To get both the left and right
    /// values.
    uint16_t combineValue(uint8_t registerToCombine);
};

#endif