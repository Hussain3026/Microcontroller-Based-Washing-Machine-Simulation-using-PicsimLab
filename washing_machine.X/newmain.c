#include "main.h"

// Configuration bits (adjust or add based on your PIC)
#pragma config WDTE = OFF  // Watchdog Timer Enable

// Global Variables
unsigned char operational_mode = WASHING_PROGRAM_SCREEN;
unsigned char reset_flag = RESET_WASH_PROGRAM_SCREEN;

// Function to initialize hardware components
static void init_config(void) {
    init_clcd();              // Initialize CLCD
    init_digital_keypad();    // Initialize digital keypad
    init_timer2();            // Initialize Timer2

    GIE = 1;      // Global Interrupt Enable
    PEIE = 1;     // Peripheral Interrupt Enable

    BUZZER_DDR = 0;
    FAN_DDR = 0;
    BUZZER = OFF;
    FAN = OFF;
}

void main(void) {
    init_config();

    unsigned char key;

    clcd_print("Press Key5 to", LINE1(1));
    clcd_print("Power On", LINE2(5));
    clcd_print("Washing Machine", LINE3(1));

    // Wait for SW5 to be pressed
    while (read_digital_keypad(STATE) != SW5) {
        for (unsigned long int delay = 3000; delay--;);  // crude delay
    }

    clear_screen();
    power_on_screen();

    while (1) {
        key = read_digital_keypad(STATE);

        // To avoid bouncing effect
        for (unsigned int delay = 3000; delay--;);

        if ((key == LPSW4) && (operational_mode == WASHING_PROGRAM_SCREEN)) {
            operational_mode = WATER_LEVEL_SCREEN;
            reset_flag = RESET_WATER_LEVEL_SCREEN;
        }
        else if ((key == LPSW4) && (operational_mode == WATER_LEVEL_SCREEN)) {
            operational_mode = START_STOP_SCREEN;
            clear_screen();
            clcd_print("Press Switch", LINE1(0));
            clcd_print("SW5: START", LINE2(0));
            clcd_print("SW6: STOP", LINE3(0));
            set_time();
        }
        else if ((key == SW5) && (operational_mode == PAUSE)) {
            operational_mode = START_SCREEN;
            TMR2ON = ON;
            FAN = ON;
        }

        switch (operational_mode) {
            case WASHING_PROGRAM_SCREEN:
                washing_program_display(key);
                break;

            case WATER_LEVEL_SCREEN:
                water_level_screen(key);
                break;

            case START_STOP_SCREEN:
                if (key == SW5) {
                    operational_mode = START_SCREEN;
                    reset_flag = RESET_START_SCREEN;
                    continue;
                }
                else if (key == SW6) {
                    operational_mode = WASHING_PROGRAM_SCREEN;
                    reset_flag = RESET_WASH_PROGRAM_SCREEN;
                    continue;
                }
                break;

            case START_SCREEN:
                run_program(key);
                break;

            default:
                break;
        }
    }

    return;
}