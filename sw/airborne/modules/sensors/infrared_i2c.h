/*
 * Copyright (C) 2010 ENAC
 *
 * This file is part of paparazzi.
 *
 * paparazzi is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * paparazzi is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with paparazzi; see the file COPYING.  If not, write to
 * the Free Software Foundation, 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

/*
 * Driver for i2c infrared sensor
 */

#ifndef INFRARED_I2C_H
#define INFRARED_I2C_H

#include "std.h"
#include "generated/airframe.h"
#include "infrared.h"
#include "i2c.h"

extern int16_t ir_i2c_ir1;
extern int16_t ir_i2c_ir2;
extern int16_t ir_i2c_top;
extern volatile bool_t ir_i2c_done;
extern bool_t ir_i2c_data_available;
extern uint8_t ir_i2c_conf_word;
extern bool_t ir_i2c_conf_hor_done, ir_i2c_conf_ver_done;

extern struct i2c_transaction irh_trans, irv_trans;

extern void infrared_i2c_init( void );
extern void infrared_i2c_update( void );
extern void infrared_i2c_hor_event( void );
extern void infrared_i2c_ver_event( void );

#define infrared_i2cEvent() { \
  if (irh_trans.status == I2CTransSuccess) infrared_i2c_hor_event(); \
  if (irv_trans.status == I2CTransSuccess) infrared_i2c_ver_event(); \
}

#define infrared_i2cDownlink() DOWNLINK_SEND_DEBUG_IR_I2C(DefaultChannel, &ir_i2c_ir1, &ir_i2c_ir2, &ir_i2c_top)

#define infrared_i2c_SetConfWord(_v) { \
  ir_i2c_conf_hor_done = FALSE; \
  ir_i2c_conf_ver_done = FALSE; \
  ir_i2c_conf_word = _v; \
}

#endif // INFRARED_I2C_H
