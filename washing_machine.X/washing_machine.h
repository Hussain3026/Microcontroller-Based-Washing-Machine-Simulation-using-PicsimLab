/* 
 * File:   washing_machine.h
 * Author: shake
 *
 * Created on 15 June, 2025, 12:23 PM
 */

#ifndef WASHING_MACHINE_H
#define	WASHING_MACHINE_H
void power_on_screen(void);
void clear_screen(void);
void washing_program_display(unsigned char key);
void water_level_screen(unsigned char key);
void set_time(void);
void run_program(unsigned char key);
void door_status_check(void);
#endif	/* WASHING_MACHINE_H */