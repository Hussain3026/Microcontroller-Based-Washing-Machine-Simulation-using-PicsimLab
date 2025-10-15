/* 
 * File:   main.h
 * Author: shake
 *
 * Created on 15 June, 2025, 1:10 PM
 */

#ifndef MAIN_H
#define	MAIN_H

#include <xc.h>
#include "clcd1.h"
#include "digital_keypad.h"
#include "timers.h"
#include "washing_machine.h"


#define WASHING_PROGRAM_SCREEN  0x01
#define WATER_LEVEL_SCREEN      0x02
#define START_STOP_SCREEN       0x03
#define START_SCREEN            0x04

#define RESET_WASH_PROGRAM_SCREEN  0x11
#define RESET_NOTHING              0xFF
#define RESET_WATER_LEVEL_SCREEN   0x22
#define RESET_START_SCREEN         0x33
#define PAUSE                      0x44

#define FAN_DDR    TRISC2
#define BUZZER_DDR  TRISC1

#define BUZZER  RC1
#define FAN     RC2

#define ON      1
#define OFF     0




#endif	/* MAIN_H */