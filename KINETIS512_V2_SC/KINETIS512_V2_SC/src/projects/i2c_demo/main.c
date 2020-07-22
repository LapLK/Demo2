/*
 * File:		hello_world.c
 * Purpose:		Main process
 *
 */

#include "common.h"
#include "global.h"
#include "hal_i2c.h"
#include "hal_dev_mma8451.h"

/********************************************************************/
void main (void)
{
    hal_i2c_init();
    hal_dev_mma8451_test_function();
}
/********************************************************************/
