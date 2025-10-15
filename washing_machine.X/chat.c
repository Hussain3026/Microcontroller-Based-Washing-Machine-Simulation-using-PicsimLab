#include <xc.h>
#include <stdio.h>
#include <string.h>

// CONFIG
#pragma config FOSC = INTRC_NOCLKOUT
#pragma config WDTE = OFF
#pragma config PWRTE = ON
#pragma config MCLRE = ON
#pragma config CP = OFF
#pragma config CPD = OFF
#pragma config BOREN = OFF
#pragma config IESO = OFF
#pragma config FCMEN = OFF
#pragma config LVP = OFF

#define _XTAL_FREQ 4000000

// Switches
#define SW1 RB0 // Door status
#define SW4 RB1 // Navigation
#define SW5 RB2 // Power ON / Start
#define SW6 RB3 // Pause / Stop

// Buzzer
#define BUZZER RB4

// Mock CLCD display function
void clcd_print(const char *msg) {
    // Stub function for printing to CLCD
    printf("%s\n", msg);
}

// Initialization
void init_config(void) {
    TRISB = 0x0F; // RB0-RB3 inputs (SW1-SW6), others outputs (RB4 for buzzer)
    PORTB = 0x00;
}

// Wait for key press utility
void wait_for_key(unsigned char key_mask) {
    while (!(PORTB & key_mask));
    __delay_ms(500); // debounce delay
}

// Washing programs list
const char *programs[] = {
    "Daily", "Heavy", "Delicates", "Whites",
    "Stain wash", "Eco cottons", "Woolens",
    "Bed sheets", "Rinse+Dry", "Dry only",
    "Wash only", "Aqua store"
};

// Water levels list
const char *water_levels[] = {"Auto", "Low", "Medium", "High", "Max"};

void main(void) {
    unsigned char prog_idx = 0, water_idx = 0;
    unsigned char running = 0;

    init_config();

    // Power ON screen
    clcd_print("Press key5 to Power ON Washing machine");
    wait_for_key(SW5);
    clcd_print("Powering ON Washing Machine");

    // Program selection
    while (1) {
        char msg[20];
        sprintf(msg, "Prog: %s", programs[prog_idx]);
        clcd_print(msg);
        
        if (PORTB & SW4) { // Navigation press
            prog_idx = (prog_idx + 1) % 12;
            __delay_ms(500); // debounce
        }
        if ((PORTB & SW4) && (PORTB & SW5)) { // Simulate long press to select
            break;
        }
    }

    // Water level selection
    while (1) {
        char msg[20];
        sprintf(msg, "Water: %s", water_levels[water_idx]);
        clcd_print(msg);
        
        if (PORTB & SW4) {
            water_idx = (water_idx + 1) % 5;
            __delay_ms(500);
        }
        if ((PORTB & SW4) && (PORTB & SW5)) { // Simulate long press to select
            break;
        }
    }

    // Start screen
    clcd_print("SW5: START SW6: STOP");
    while (1) {
        if (PORTB & SW5) {
            running = 1;
            break;
        }
        if (PORTB & SW6) {
            // Restart program selection
            main();
        }
    }

    // Function screen
    if (running) {
        unsigned char time = 50; // Example time
        while (time > 0) {
            if (PORTB & SW1) {
                BUZZER = 1;
                clcd_print("DOOR: OPEN Please close");
            } else {
                BUZZER = 0;
                char msg[20];
                sprintf(msg, "Func: wash Time: %02u", time);
                clcd_print(msg);
            }

            if (PORTB & SW6) {
                clcd_print("Paused");
                while (!(PORTB & SW5)); // Wait for resume
            }

            __delay_ms(1000); // 1s delay
            time--;
        }
    }

    // Completion screen
    clcd_print("Program completed Remove clothes");

    while (1);
}
