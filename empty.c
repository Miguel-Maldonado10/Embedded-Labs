// ~~ Blinking LED code ~~

// #include <ti/driverlib/m0p/dl_interrupt.h>
// #include "ti_msp_dl_config.h"

// int main(void)
// {
//     SYSCFG_DL_init();

//     while (1) {

//         DL_GPIO_togglePins(GPIOA, DL_GPIO_PIN_22);
//         delay_cycles(3200000); // this values comes from -> MCU Hz * secs 
//     }
// }


// ~~ Pull Up Resistor Button Code ~~

// #include <ti/driverlib/m0p/dl_interrupt.h>
// #include "ti_msp_dl_config.h"

// int main(void)
// {
//     SYSCFG_DL_init();

//     while (1) {
//         // Read the physical state of pin PB18
//         // Because of the Pull-Up resistor, it reads 0 (LOW) when pressed
//         if (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_18) == 0) {
//             // Button is pressed -> Turn the LED ON
//             DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_22);
//         } 
//         else {
//             // Button is released -> Turn the LED OFF
//             DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_22);
//         }
//     }
// }


// ~~ Pull Down Resistor Button Code ~~

// #include <ti/driverlib/m0p/dl_interrupt.h>
// #include "ti_msp_dl_config.h"

// int main(void)
// {
//     SYSCFG_DL_init();

//     while (1) {
//         // Check if pin is HIGH (1), which means the button is pressed 
//         if (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_18) != 0) {
//             // Button is pressed -> Turn the LED OFF
//             DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_22);
//         } 
//         else {
//             // Button is released -> Turn the LED ON
//             DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_22);
//         }
//     }
// }

// LCD Setup

#include <ti/devices/msp/msp.h>          // REQUIRED for __WFI() and core registers
#include <ti/driverlib/m0p/dl_interrupt.h>
#include "ti_msp_dl_config.h"

// #define PIN_RS(x) (x ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_18) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_18))
// #define PIN_RW(x) (x ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_27) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_27))
// #define PIN_EN(x) (x ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_18) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_18))
// #define PIN_D4(x) (x ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_22) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_22))
// #define PIN_D5(x) (x ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_26) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_26))
// #define PIN_D6(x) (x ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_24) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_24))
// #define PIN_D7(x) (x ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_19) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_19))

#define PIN_RS(x) (x ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_20) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_20))
#define PIN_RW(x) (x ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_31) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_31))
#define PIN_EN(x) (x ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_28) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_28))
#define PIN_D4(x) (x ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_16) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_16))
#define PIN_D5(x) (x ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_17) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_17))
#define PIN_D6(x) (x ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_22) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_22))
#define PIN_D7(x) (x ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_19) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_19))

void delay_ms(uint32_t ms) {
    // 32,000,000 Hz clock / 1000 = 32000 cycles per millisecond
    uint32_t period = 80000; 
    
    while(ms--) {
        // Set the reload register
        SysTick->LOAD = period - 1;
        // Clear the current value register
        SysTick->VAL = 0;
        
        // Wait until the COUNTFLAG (bit 16) in the Control register transitions to 1
        while ((SysTick->CTRL & (1UL << 16)) == 0); 
    }
}

// void delay_ms(uint32_t ms) {
//     volatile uint32_t count;
//     while(ms--) {
//         // Roughly 4000 loops at 32MHz takes about 1 millisecond
//         for(count = 0; count < 4000; count++) {
//             __asm("nop"); // Prevents the compiler from deleting this empty loop
//         }
//     }
// }


void LCD_nibble(unsigned char nibble) {
    PIN_D4((nibble >> 0) & 0x01);
    PIN_D5((nibble >> 1) & 0x01);
    PIN_D6((nibble >> 2) & 0x01);
    PIN_D7((nibble >> 3) & 0x01);
    PIN_EN(1);
    delay_ms(50);
    PIN_EN(0);
    delay_ms(50);
}

void LCD_command(unsigned char cmd) {
    PIN_RS(0);
    PIN_RW(0);
    LCD_nibble(cmd >> 4);
    LCD_nibble(cmd & 0x0F);
    delay_ms(2);
}

void LCD_data(unsigned char data) {
    PIN_RS(1);
    PIN_RW(0);
    LCD_nibble(data >> 4);
    LCD_nibble(data & 0x0F);
    delay_ms(1);
}

void ClearLCD(void){
    LCD_command(0x01);
}

void SetCursor(uint8_t row, uint8_t column) {
    uint8_t address;
    if(row == 0){
        address = 0x80 + column;
    } else {
        address = 0xC0 + column;
    }
    LCD_command(address);
}

void LCD_init(void) {
    PIN_RS(0);
    PIN_RW(0);
    PIN_EN(0);
    delay_ms(100);

    LCD_nibble(0x03);
    delay_ms(10);
    LCD_nibble(0x03);
    delay_ms(5);
    LCD_nibble(0x03);
    delay_ms(1);

    LCD_nibble(0x02); // 4 bit mode
    delay_ms(2);

    LCD_command(0x28); // 2 lines
    LCD_command(0x0F); // cursor on
    LCD_command(0x06); // cursor increments
    LCD_command(0x01); // clear lcd
}

void LCD_print(char *str) {
    while(*str){
        LCD_data(*str++);
    }
}

// int main(void) {
//     SYSCFG_DL_init();
    
//     // INITIALIZE HARDWARE TIMER FOR DELAYS (Hardcoded 32MHz clock rate)
//     // DL_SYSTICK_init(80000000);
//     // DL_SYSTICK_enable();

//     LCD_init();
//     // LCD_print("HOLA");

//     while(1){
//         delay_ms(100);
//     }
// }

const char* messages[16] = {
    "Sooooo", "understand", "Dont", "waste", "your time",  "always searching", 
    "for those", "wasted years", "Face up", "Make your stand",  "And realize", 
    "youre", "living", "in the", "golden", "years"
};


int main(void) {
    SYSCFG_DL_init();
    
    // Initialize and enable SysTick so delay_ms() works properly (assuming a 32MHz CPU clock)
    DL_SYSTICK_init(32000000);
    DL_SYSTICK_enable();

    LCD_init();
    
    // Print your message to the LCD
    LCD_print("Hola");

    while(1){
        delay_ms(100);
    }
}

// ~~ LCD Scrolling~~



// volatile int current_index = 0;
// volatile bool update_display = true;

// void delay_cycles(uint32_t cycles) {
//     // while (cycles--) { __NOP(); }
//     int i;
//     for(i = 0; i < ms * 1000; i++){
//         __no_operation();
//     }
// }

// void lcd_pulse_nibble(uint8_t nibble) {
//     DL_GPIO_clearPins(GG_LCD_PORT, GG_LCD_PIN_D4_PIN | GG_LCD_PIN_D5_PIN | GG_LCD_PIN_D6_PIN | GG_LCD_PIN_D7_PIN );

//     if (nibble & 0x01) DL_GPIO_setPins(GG_LCD_PORT, GG_LCD_PIN_D4_PIN);
//     if (nibble & 0x02) DL_GPIO_setPins(GG_LCD_PORT, GG_LCD_PIN_D5_PIN);
//     if (nibble & 0x04) DL_GPIO_setPins(GG_LCD_PORT, GG_LCD_PIN_D6_PIN);
//     if (nibble & 0x08) DL_GPIO_setPins(GG_LCD_PORT, GG_LCD_PIN_D7_PIN);

//     lcd_pulse_enable();
// }

// void lcd_send(uint8_t value, uint32_t is_data) {
//     if (is_data) {
//         DL_GPIO_setPins(GG_LCD_PORT, GG_LCD_PIN_RS_PIN);
//     } else {
//         DL_GPIO_clearPins(GG_LCD_PORT, GG_LCD_PIN_RS_PIN);
//     }
//     lcd_send_nibble(0x03); delay_cycles(5000);
//     lcd_send_nibble(0x03); delay_cycles(200);
//     lcd_send_nibble(0x03);
//     lcd_send_nibble(0x02); // sets to 4 bit mode

//     lcd_send(0x28, 0); // 2 lines, 5x8 font
//     lcd_send(0x0C, 0); // Display on, cursor off
//     lcd_send(0x06, 0); // Entry mode: increment auto
//     lcd_send(0x01, 0); // Clear screen   
// }

// void refresh_list_view(void) {
//     lcd_send(0x80, 0);
//     lcd_print(messages[current_index]);

//     lcd_send(0xC0, 0);
//     lcd_print(messages[(current_index + 1) % 16]);
// }

// int main(void)
// {
//     SYSCFG_DL_init();
//     lcd_init();

//     NVIC_EnableIRQ(GG_BUTTONS_INT_IRQN);

//     while (1) {
//         if (update_display) {
//             refresh_list_view();
//             update_display = false;
//         }
//         __WFI(); // Stand By
//     }
// }

// void GG_BUTTONS_INT_IRQHandler(void) {
//     uint32_t gpio_interrupts = DL_GPIO_getEnabledInterruptStatus(GG_BUTTONS_PORT, GG_BUTTONS_PIN_UP_PIN | GG_BUTTONS_PIN_DOWN_PIN);

//     delay_cycles(3200000);

//     if ((gpio_interrupts & GG_BUTTONS_PIN_UP_PIN) == 0) {
//         if(DL_GPIO_readPins(GG_BUTTONS_PORT, GG_BUTTONS_PIN_UP_PIN) == 0){
//             current_index = (current_index - 1 + 16) % 16; // UP
//             update_display = true;
//         }
//     }
//     else if (gpio_interrupts & GG_BUTTONS_PIN_DOWN_PIN) == 0 {
//         if(DL_GPIO_readPins(GG_BUTTONS_PORT, GG_BUTTONS_PIN_DOWN_PIN) == 0){
//             current_index = (current_index + 1) % 16; // DOWN
//             update_display = true;
//         }
//     }
//     DL_GPIO_clearInterruptStatus(GG_BUTTONS_PORT, GG_BUTTONS_PIN_UP_PIN | GG_BUTTONS_PIN_DOWN_PIN);
    
// }