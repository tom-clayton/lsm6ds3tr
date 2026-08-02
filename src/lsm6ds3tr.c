/*
 * lsm6ds3tr.c: Minimal LSM6DS3TR sensor driver for gesture recognition. 
 *
 * Sets up the sensor to detect a particular guesture and generate an interrupt.
 *
 * Tom Clayton 2025
 * 
 */

#include "lsm6ds3tr.h"

static const i2c_bus_t *bus;

int lsm6ds_init(const i2c_bus_t *i2c_bus)
{
    int err;
    if (i2c_bus == NULL) return -1;
    bus = i2c_bus;
    uint8_t id;
    if (err = i2c_read_reg(bus,LSM6DS_ID_REG, &id) < 0) return err;
    if (id != LSM6DS_CHIP_ID) return -1;
    return 0;
}

int lsm6ds_setup_tap()
{   
    int err;
    if((err = i2c_write_reg(bus, LSM6DS_CTRL1_XL_REG, 0x60)) < 0) return err;   // Turn on accelerometer 
    if((err = i2c_write_reg(bus, LSM6DS_CTRL6_C_REG, 0x00)) < 0) return err;    // High-performance operating mode enabled for accelerometer
    if((err = i2c_write_reg(bus, LSM6DS_TAP_CFG_REG, 0x8E)) < 0) return err;    // Enable interrupts and enable tap detection on all axis
    if((err = i2c_write_reg(bus, LSM6DS_TAP_THS_6D_REG, 0x8C)) < 0) return err; // Set tap threshold
    if((err = i2c_write_reg(bus, LSM6DS_INT_DUR2_REG, 0x7F)) < 0) return err;   // Set duration, quiet and shock time windows
    if((err = i2c_write_reg(bus, LSM6DS_WAKE_UP_THS_REG, 0x80)) < 0) return err;// Enable double tap 
    if((err = i2c_write_reg(bus, LSM6DS_MD1_CFG_REG, 0x08)) < 0) return err;    // Route double tap interrupt to INT1 pin 
}

int lsm6ds_setup_AWT()
{   
    int err;
    if((err = i2c_write_reg(bus, LSM6DS_CTRL1_XL_REG, 0x20)) < 0) return err;       // Turn on accelerometer 
    if((err = i2c_write_reg(bus, LSM6DS_CTRL6_C_REG, 0x10)) < 0) return err;        // High-performance operating mode disabled for accelerometer
    if((err = i2c_write_reg(bus, LSM6DS_CTRL10_C_REG, 0x84)) < 0) return err;       // Enable tilt detection
    if((err = i2c_write_reg(bus, LSM6DS_DRDY_PULSE_CFG_REG, 0x01)) < 0) return err; // Set interupt 
    if((err = i2c_write_reg(bus, LSM6DS_CTRL4_C_REG, 0x20)) < 0) return err;        // INT 2 to INT 1 pin
}

int lsm6ds_setup_6D()
{   
    int err;
    if((err = i2c_write_reg(bus, LSM6DS_CTRL1_XL_REG, 0x20)) < 0) return err;       // Turn on accelerometer 
    if((err = i2c_write_reg(bus, LSM6DS_CTRL6_C_REG, 0x10)) < 0) return err;        // High-performance operating mode disabled for accelerometer
    if((err = i2c_write_reg(bus, LSM6DS_TAP_CFG_REG, 0x80)) < 0) return err;        // Enable interrupts
    if((err = i2c_write_reg(bus, LSM6DS_TAP_THS_6D_REG, 0x20)) < 0) return err;     // Set 6D threshold
    if((err = i2c_write_reg(bus, LSM6DS_CTRL8_XL_REG, 0x40)) < 0) return err;       // Setup filter
    if((err = i2c_write_reg(bus, LSM6DS_MD1_CFG_REG, 0x04)) < 0) return err;        // Route 6D orientation change interrupt to INT1 pin
}