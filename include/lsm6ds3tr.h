/*
 * lsm6ds3tr.h: Minimal LSM6DS3TR sensor driver for gesture recognition. 
 *
 * Sets up the sensor to detect a particular guesture and generate an interrupt.
 *
 * Requires I2C bus read / write functions to be passed in, as declared in i2c_wrapper.h.
 * 
 * Tom Clayton 2025
 * 
 */

#ifndef LSM6DS3TR_H
#define LSM6DS3TR_H

#include <stdint.h>
#include "i2c_wrapper.h"

/*
 * Initialise the LSM6DS sensor
 * 
 * @param i2c_bus: The I2C bus that the sensor is connected to.
 * 
 * @return 0 on success, -1 on failure
 */
int lsm6ds_init(const i2c_bus_t *i2c_bus);

/*
 * Set the device to detect taps.
 */
int lsm6ds_setup_tap();

/*
 * Set the device to detect absolute wrist tilts.
 */
int lsm6ds_setup_AWT();

/*
 * Set the device to detect 6D orientation changes.
 */
int lsm6ds_setup_6D();

#endif LSM6DS3TR_H