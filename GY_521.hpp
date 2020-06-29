#ifndef GY_521_HPP
#define GY_521_HPP
#include "hwlib.hpp"
#include "registermap.hpp"

class GY_521  {
    private :

    hwlib::i2c_bus &bus;
    int address;
    uint8_t registerToSelect;
    
    public :
    /// \brief
    /// Constructor for GY_521
    /// \details
    /// This constructor is used to construct a selected register of the 
    /// GY-521.
    GY_521(hwlib::i2c_bus &bus, int address,uint8_t  registerToSelect):
        bus(bus),
        address(address),
        registerToSelect(registerToSelect)
    {}

    /// \brief
    /// Return value
    /// \details
    /// This function is used to write and read the selected register of the
    /// GY-521 and return the value of the selected register.
    uint16_t value(){
        GY_521::bus.i2c_bus::write(GY_521::address).write(GY_521::registerToSelect);
        uint8_t returnValue =  GY_521::bus.i2c_bus::read(GY_521::address).read_byte();
        return returnValue;
    }

};




#endif