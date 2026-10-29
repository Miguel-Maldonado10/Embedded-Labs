// =======================================================================
// =======================================================================
// ============================= LAB 4 ===================================
// =======================================================================
// =======================================================================


// ======================== Timer by polling =============================

// #include "ti_msp_dl_config.h"

// #define BUZZER_PORT GPIOA
// #define BUZZER_PIN  DL_GPIO_PIN_27

// int main(void)
// {
//     /* Configure GPIO and timer using SysConfig */
//     SYSCFG_DL_init();

//     /* Start the timer */
//     DL_TimerG_startCounter(TIMER_0_INST);

//     while (1)
//     {
//         /* Check whether the timer period event occurred */
//         if (DL_TimerG_getRawInterruptStatus(
//                 TIMER_0_INST,
//                 DL_TIMERG_INTERRUPT_ZERO_EVENT))
//         {
//             /* Clear the timer event flag */
//             DL_TimerG_clearInterruptStatus(
//                 TIMER_0_INST,
//                 DL_TIMERG_INTERRUPT_ZERO_EVENT);

//             /* Toggle the buzzer output */
//             DL_GPIO_togglePins(BUZZER_PORT, BUZZER_PIN);
//         }
//     }
// }

// ======================== Timer by interrupt =============================

// #include "ti_msp_dl_config.h"

// #define BUZZER_PORT GPIOA
// #define BUZZER_PIN  DL_GPIO_PIN_27

// int main(void)
// {
//     /* Initialize GPIO and timer using SysConfig */
//     SYSCFG_DL_init();

//     /* Enable timer zero-event interrupt */
//     DL_TimerA_enableInterrupt(
//         TIMER_0_INST,
//         DL_TIMERA_INTERRUPT_ZERO_EVENT
//     );

//     /* Enable timer interrupt in the NVIC */
//     NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

//     /* Start the timer */
//     DL_TimerA_startCounter(TIMER_0_INST);

//     /* Main loop: CPU can wait for interrupts */
//     while (1)
//     {
//         __WFI();
//     }
// }

// /* Timer interrupt service routine */
// void TIMER_0_INST_IRQHandler(void)
// {
//     /* Check whether the timer reached zero */
//     if (DL_TimerA_getPendingInterrupt(TIMER_0_INST)
//         == DL_TIMERA_IIDX_ZERO)
//     {
//         /* Toggle the buzzer output */
//         DL_GPIO_togglePins(BUZZER_PORT, BUZZER_PIN);
//     }
// }
// =======================================================================
// =======================================================================
// ============================= LAB 4 ===================================
// =======================================================================
// =======================================================================

// =======================================================================
// =======================================================================
// ============================= LAB 4 ===================================
// =======================================================================
// =======================================================================
// =======================================================================
// =======================================================================
// ============================= LAB 4 ===================================
// =======================================================================
// =======================================================================

// ======================  7-Segment Display (0 to 9 in 1 Sec) ===========
// #include <stdint.h>
// #include <ti/devices/msp/msp.h>
// #include <ti/driverlib/m0p/dl_interrupt.h>
// #include "ti_msp_dl_config.h"

// /* ============================================================
// - 7-SEGMENT LOOKUP TABLE (0 to 9)
// - ============================================================ */

// static const uint8_t hexSegmentCode[16] = {
//     0x40U, 0x79, 0x24U, 0x30U, // 0, 1, 2, 3
//     0x19U, 0x12U, 0x02U, 0x78U, // 4, 5, 6, 7
//     0x00U, 0x10U, 0x08U, 0x03U, // 8, 9, A, B
//     0x46U, 0x21U, 0x06U, 0x0EU // C, D, E, F
// };

// /* Global variables for counter and dynamic display */
// static volatile uint8_t counterValue = 0x00U; // Starts at 0, max 9
// static volatile uint8_t displayToggle = 0;    // Alternates between digit 1 and digit 2
// static volatile uint16_t tickCounter = 0;     // Used to time the 1-second cadence

// /* ============================================================
// - 7-SEGMENT DYNAMIC DISPLAY HELPER FUNCTIONS
// - ============================================================ */

// static void WriteSegment(GPIO_Regs *port, uint32_t pin, uint8_t code, uint8_t bit)
// {
//     if ((code & bit) != 0U) {
//         DL_GPIO_setPins(port, pin);
//     } else {
//         DL_GPIO_clearPins(port, pin);
//     }
// }

// static void OutputSegments(uint8_t code)
// {
//     WriteSegment(GPIO_GRP_1_SEG_A_PIN_PORT, GPIO_GRP_1_SEG_A_PIN_PIN, code, 0x01U);
//     WriteSegment(GPIO_GRP_1_SEG_B_PIN_PORT, GPIO_GRP_1_SEG_B_PIN_PIN, code, 0x02U);
//     WriteSegment(GPIO_GRP_1_SEG_C_PIN_PORT, GPIO_GRP_1_SEG_C_PIN_PIN, code, 0x04U);
//     WriteSegment(GPIO_GRP_1_SEG_D_PIN_PORT, GPIO_GRP_1_SEG_D_PIN_PIN, code, 0x08U);
//     WriteSegment(GPIO_GRP_1_SEG_E_PIN_PORT, GPIO_GRP_1_SEG_E_PIN_PIN, code, 0x10U);
//     WriteSegment(GPIO_GRP_1_SEG_F_PIN_PORT, GPIO_GRP_1_SEG_F_PIN_PIN, code, 0x20U);
//     WriteSegment(GPIO_GRP_1_SEG_G_PIN_PORT, GPIO_GRP_1_SEG_G_PIN_PIN, code, 0x40U);
// }

// /* ============================================================
// - MAIN PROGRAM
// - ============================================================ */

// int main(void)
// {
//     SYSCFG_DL_init();

//     /* Initialize Timer ISR for 60Hz dynamic multiplexing across 2 digits */
//     DL_TimerA_enableInterrupt(TIMER_0_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT);
//     NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
//     DL_TimerA_startCounter(TIMER_0_INST);

//     while (1)
//     {
//         /* Keep the main loop active instead of sleeping via __WFI() */
//     }
// }

// /* ============================================================
// - TIMER ISR: 60Hz Dynamic Display Multiplexing & Auto-Counting
// - ============================================================ */

// void TIMA0_IRQHandler(void)
// {
//     if (DL_TimerA_getPendingInterrupt(TIMER_0_INST) == DL_TIMERA_IIDX_ZERO)
//     {
//         DL_TimerA_clearInterruptStatus(TIMER_0_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT);

//         /* 
//          * Increment counter every ~100ms. 
//          * At a 60Hz multiplexing rate, the ISR fires 60 times per second (~16.6ms per tick).
//          * 6 ticks ≈ 100ms. Over 10 numbers (0-9), 60 ticks total = exactly 1 second per cycle.
//          */
//         tickCounter++;
//         if (tickCounter >= 100)
//         {
//             tickCounter = 0;
//             counterValue++;
//             if (counterValue > 9)
//             {
//                 counterValue = 0; // Reset back to 0 after 9
//             }
//         }

//         // uint8_t num1 = 0U;                    
//         // uint8_t num2 = counterValue & 0x0FU;  

//         uint8_t num2 = counterValue;
//             /* (e) Turn off control signal for both 7-segments */
//             DL_GPIO_setPins(GPIO_GRP_1_SEV_SEG_1_PORT, GPIO_GRP_1_SEV_SEG_1_PIN);
//             DL_GPIO_setPins(GPIO_GRP_1_SEV_SEG_2_PORT, GPIO_GRP_1_SEV_SEG_2_PIN);

//             /* (f) Send data for the second 7-segment */
//             OutputSegments(hexSegmentCode[num2]);

//             /* (g) Turn on the second 7-segment control signal */
//             DL_GPIO_clearPins(GPIO_GRP_1_SEV_SEG_2_PORT, GPIO_GRP_1_SEV_SEG_2_PIN);

//             displayToggle = 0;
//     }
// }
// +++++++++++++++++++++++4.2.4++++++++++++++++++++++++++++

// #include <stdint.h>
// #include <ti/devices/msp/msp.h>
// #include <ti/driverlib/m0p/dl_interrupt.h>
// #include "ti_msp_dl_config.h"

// /* ============================================================
//  * 7-SEGMENT LOOKUP TABLE (Active-Low for Common-Anode)
//  * ============================================================ */

// static const uint8_t hexSegmentCode[16] = {
//     0x40U, // 0
//     0xF9U, // 1
//     0x24U, // 2
//     0x30U, // 3
//     0x19U, // 4
//     0x12U, // 5
//     0x02U, // 6
//     0x78U, // 7
//     0x00U, // 8
//     0x10U, // 9
//     0x08U, // A
//     0x03U, // b
//     0x46U, // C
//     0x21U, // d
//     0x06U, // E
//     0x0EU  // F
// };

// /* Global variables for counter and dynamic multiplexing */
// static volatile uint8_t counterValue = 0x00U; // Counts from 00 to FF
// static volatile uint8_t displayToggle = 0;    // Alternates between digit 1 and digit 2
// static volatile uint16_t tickCounter = 0;     // Tracks 1-second interval

// /* ============================================================
//  * SEGMENT HELPER FUNCTIONS
//  * ============================================================ */

// static void WriteSegment(GPIO_Regs *port, uint32_t pin, uint8_t code, uint8_t bit)
// {
//     if ((code & bit) != 0U) {
//         DL_GPIO_setPins(port, pin);     // HIGH turns segment OFF
//     } else {
//         DL_GPIO_clearPins(port, pin);   // LOW turns segment ON
//     }
// }

// static void OutputSegments(uint8_t code)
// {
//     WriteSegment(GPIO_GRP_1_SEG_A_PIN_PORT, GPIO_GRP_1_SEG_A_PIN_PIN, code, 0x01U);
//     WriteSegment(GPIO_GRP_1_SEG_B_PIN_PORT, GPIO_GRP_1_SEG_B_PIN_PIN, code, 0x02U);
//     WriteSegment(GPIO_GRP_1_SEG_C_PIN_PORT, GPIO_GRP_1_SEG_C_PIN_PIN, code, 0x04U);
//     WriteSegment(GPIO_GRP_1_SEG_D_PIN_PORT, GPIO_GRP_1_SEG_D_PIN_PIN, code, 0x08U);
//     WriteSegment(GPIO_GRP_1_SEG_E_PIN_PORT, GPIO_GRP_1_SEG_E_PIN_PIN, code, 0x10U);
//     WriteSegment(GPIO_GRP_1_SEG_F_PIN_PORT, GPIO_GRP_1_SEG_F_PIN_PIN, code, 0x20U);
//     WriteSegment(GPIO_GRP_1_SEG_G_PIN_PORT, GPIO_GRP_1_SEG_G_PIN_PIN, code, 0x40U);
// }

// /* ============================================================
//  * MAIN PROGRAM
//  * ============================================================ */

// int main(void)
// {
//     SYSCFG_DL_init();

//     /* Enable global interrupts */
//     __enable_irq();

//     /* Initialize Timer ISR for 60Hz multiplexing (120Hz total toggle rate for 2 digits) */
//     DL_TimerA_enableInterrupt(TIMER_0_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT);
//     NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);
//     DL_TimerA_startCounter(TIMER_0_INST);

//     while (1)
//     {
//         /* Main loop remains idle; multiplexing and counting happen in the Timer ISR */
//         __WFI();
//     }
// }

// /* ============================================================
//  * TIMER ISR: 60Hz Multiplexing & 1-Second Counter Increment
//  * ============================================================ */

// void TIMA0_IRQHandler(void)
// {
//     if (DL_TimerA_getPendingInterrupt(TIMER_0_INST) == DL_TIMERA_IIDX_ZERO)
//     {
//         DL_TimerA_clearInterruptStatus(TIMER_0_INST, DL_TIMERA_INTERRUPT_ZERO_EVENT);

//         /* 
//          * 1-Second Counter Logic:
//          * Multiplexing runs at 120Hz total toggles (60Hz per digit). 
//          * 120 ticks = exactly 1 second. Every 120 ticks, increment counterValue.
//          */
//         tickCounter++;
//         if (tickCounter >= 120)
//         {
//             tickCounter = 0;
//             counterValue++; // Automatically rolls over past 0xFF back to 0x00
//         }

//         /* Split counterValue into Upper Digit (Num1) and Lower Digit (Num2) */
//         uint8_t num1 = (counterValue >> 4) & 0x0FU; // Upper nibble
//         uint8_t num2 = counterValue & 0x0FU;        // Lower nibble

//         if (displayToggle == 0)
//         {
//             /* (a) Turn off control signal for both 7-segments */
//             DL_GPIO_setPins(GPIO_GRP_1_SEV_SEG_1_PORT, GPIO_GRP_1_SEV_SEG_1_PIN);
//             DL_GPIO_setPins(GPIO_GRP_1_SEV_SEG_2_PORT, GPIO_GRP_1_SEV_SEG_2_PIN);

//             /* (b) Send data for the first 7-segment (Upper Digit) */
//             OutputSegments(hexSegmentCode[num1]);

//             /* (c) Turn on the first 7-segment control signal */
//             DL_GPIO_clearPins(GPIO_GRP_1_SEV_SEG_1_PORT, GPIO_GRP_1_SEV_SEG_1_PIN);

//             displayToggle = 1;
//         }
//         else
//         {
//             /* (e) Turn off control signal for both 7-segments */
//             DL_GPIO_setPins(GPIO_GRP_1_SEV_SEG_1_PORT, GPIO_GRP_1_SEV_SEG_1_PIN);
//             DL_GPIO_setPins(GPIO_GRP_1_SEV_SEG_2_PORT, GPIO_GRP_1_SEV_SEG_2_PIN);

//             /* (f) Send data for the second 7-segment (Lower Digit) */
//             OutputSegments(hexSegmentCode[num2]);

//             /* (g) Turn on the second 7-segment control signal */
//             DL_GPIO_clearPins(GPIO_GRP_1_SEV_SEG_2_PORT, GPIO_GRP_1_SEV_SEG_2_PIN);

//             displayToggle = 0;
//         }
//     }
// }

// +++++++++++++++++++++++Complementary task++++++++++++++++++++++++++++
// #include <stdio.h>
// #include <stdint.h>
// #include <stdlib.h>
// #include <string.h>
// #include <ti/devices/msp/msp.h>
// #include <ti/driverlib/m0p/dl_interrupt.h>
// #include "ti_msp_dl_config.h"

// #define SYSTICK_CLOCK_HZ 80000000UL

// /* ============================================================
//  * LCD PIN DEFINITIONS (From Experiment 3 Working Code)
//  * ============================================================ */

// #define PIN_RS(x) ((x) ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_20) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_20))
// #define PIN_RW(x) ((x) ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_31) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_31))
// #define PIN_EN(x) ((x) ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_28) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_28))

// #define PIN_D4(x) ((x) ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_16) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_16))
// #define PIN_D5(x) ((x) ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_17) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_17))
// #define PIN_D6(x) ((x) ? DL_GPIO_setPins(GPIOA, DL_GPIO_PIN_22) : DL_GPIO_clearPins(GPIOA, DL_GPIO_PIN_22))
// #define PIN_D7(x) ((x) ? DL_GPIO_setPins(GPIOB, DL_GPIO_PIN_19) : DL_GPIO_clearPins(GPIOB, DL_GPIO_PIN_19))

// /* ============================================================
//  * SYSTICK DELAYS
//  * ============================================================ */

// void delay_us(uint32_t us)
// {
//     while (us > 0)
//     {
//         uint32_t chunk = us;
//         if (chunk > 1000U) {
//             chunk = 1000U;
//         }
//         uint32_t cycles = (SYSTICK_CLOCK_HZ / 1000000UL) * chunk;
//         DL_SYSTICK_setPeriod(cycles);
//         DL_SYSTICK_resetValue();
//         while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U) {
//             /* Wait */
//         }
//         us -= chunk;
//     }
// }

// void delay_ms(uint32_t ms)
// {
//     while (ms > 0U)
//     {
//         delay_us(1000U);
//         ms--;
//     }
// }

// void SysTick_Init(void)
// {
//     SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
//     DL_SYSTICK_init(SYSTICK_CLOCK_HZ / 1000UL);
//     DL_SYSTICK_enable();
// }

// /* ============================================================
//  * LCD LOW-LEVEL FUNCTIONS
//  * ============================================================ */

// void LCD_nibble(uint8_t nibble)
// {
//     PIN_D4((nibble >> 0) & 1U);
//     PIN_D5((nibble >> 1) & 1U);
//     PIN_D6((nibble >> 2) & 1U);
//     PIN_D7((nibble >> 3) & 1U);

//     PIN_EN(1);
//     delay_us(1);
//     PIN_EN(0);
//     delay_us(1);
// }

// void LCD_command(uint8_t cmd)
// {
//     PIN_RS(0);
//     PIN_RW(0);
//     LCD_nibble(cmd >> 4);
//     LCD_nibble(cmd & 0x0F);

//     if (cmd == 0x01 || cmd == 0x02) {
//         delay_ms(2);
//     } else {
//         delay_us(50);
//     }
// }

// void LCD_data(uint8_t data)
// {
//     PIN_RS(1);
//     PIN_RW(0);
//     LCD_nibble(data >> 4);
//     LCD_nibble(data & 0x0F);
//     delay_us(50);
// }

// void ClearLCD(void)
// {
//     LCD_command(0x01);
// }

// void SetCursor(uint8_t row, uint8_t column)
// {
//     uint8_t address = (row == 0U) ? (0x80U + column) : (0xC0U + column);
//     LCD_command(address);
// }

// void LCD_init(void)
// {
//     PIN_RS(0);
//     PIN_RW(0);
//     PIN_EN(0);
//     delay_ms(40);

//     LCD_nibble(0x03);
//     delay_ms(5);
//     LCD_nibble(0x03);
//     delay_ms(2);
//     LCD_nibble(0x03);
//     delay_ms(2);
//     LCD_nibble(0x02);
//     delay_ms(2);

//     LCD_command(0x28); // 4-bit interface, 2 lines
//     LCD_command(0x0C); // Display ON, cursor OFF
//     LCD_command(0x06); // Increment cursor
//     ClearLCD();
// }

// void LCD_print(const char *str)
// {
//     while (*str != '\0')
//     {
//         LCD_data((uint8_t)*str);
//         str++;
//     } 
// }

// /* ============================================================
//  * QUADRATURE SENSOR FUNCTIONS (From Exp 3)
//  * ============================================================ */

// uint8_t ReadWheelState(void)
// {
//     uint8_t left =
//         (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_7) != 0U);

//     uint8_t right =
//         (DL_GPIO_readPins(GPIOB, DL_GPIO_PIN_8) != 0U);

//     return (uint8_t)((left << 1) | right);
// }

// static const int8_t quadrature_delta[16] =
// {
//      0,  1, -1,  0,  /* old state 00 */
//     -1,  0,  0,  1,  /* old state 01 */
//      1,  0,  0, -1,  /* old state 10 */
//      0, -1,  1,  0   /* old state 11 */
// };

// /* ============================================================
//  * TACHOMETER GLOBALS
//  * ============================================================ */

// // volatile int32_t net_delta_pulses = 0;   // Accumulated steps over the measurement interval
// // volatile uint32_t rpm = 0;
// // volatile char current_dir[17] = "Stopped         ";
// // volatile bool update_display = false;


// /* Adjust PULSES_PER_REV to match your physical encoder wheel slot count (e.g., 20) */
// // #define PULSES_PER_REV  20  

// /* Encoder settings */
// #define WHEEL_CYCLES 6U
// #define COUNTS_PER_REV (4U * WHEEL_CYCLES)
// #define ENCODER_PINS (DL_GPIO_PIN_7 | DL_GPIO_PIN_8)
// #define SAMPLE_TICKS 60U

// volatile uint8_t oldWheelState = 0U;
// volatile int32_t net_edges = 0;
// volatile uint32_t valid_edges = 0U;
// volatile int8_t last_edge_dir = 0;

// volatile uint32_t rpm = 0U;
// volatile int8_t direction = 0;
// volatile bool update_display = false;

// /* Debugging variables */
// volatile uint32_t encoder_irq_count = 0U;
// volatile uint32_t encoder_valid_count = 0U;
// volatile uint32_t timer_sample_count = 0U;


// /* ============================================================
//  * GPIO INTERRUPT - ENCODER
//  * ============================================================ */

// void GROUP1_IRQHandler(void)
// {
//     if (DL_Interrupt_getPendingGroup(DL_INTERRUPT_GROUP_1)
//         == DL_INTERRUPT_GROUP1_IIDX_GPIOB)
//     {
//         uint32_t pending =
//             DL_GPIO_getEnabledInterruptStatus(
//                 GPIOB, ENCODER_PINS
//             );

//         if (pending != 0U)
//         {
//             DL_GPIO_clearInterruptStatus(GPIOB, pending);

//             DL_Interrupt_clearGroup(
//                 DL_INTERRUPT_GROUP_1,
//                 DL_INTERRUPT_GROUP1_GPIOB
//             );

//             encoder_irq_count++;

//             uint8_t newState = ReadWheelState();

//             if (newState != oldWheelState)
//             {
//                 uint8_t index =
//                     (uint8_t)((oldWheelState << 2) | newState);

//                 int8_t delta = quadrature_delta[index];

//                 oldWheelState = newState;

//                 if (delta != 0)
//                 {
//                     net_edges += delta;
//                     valid_edges++;
//                     encoder_valid_count++;
//                     last_edge_dir = delta;
//                 }
//             }
//         }
//     }
// }
// /* ============================================================
//  * TIMER INTERRUPT HANDLER (TIMA0 for Tachometer Sampling)
//  * ============================================================ */
// // void TIMA0_IRQHandler(void)
// // {
// //     switch (DL_TimerA_getPendingInterrupt(TIMER_0_INST))
// //     {
// //         case DL_TIMER_IIDX_ZERO:
// //         {
// //             int32_t pulses = net_delta_pulses;
// //             net_delta_pulses = 0; // Reset accumulator for next window

// //             if (pulses > 0) {
// //                 strcpy((char *)current_dir, "Clockwise       ");
// //             } else if (pulses < 0) {
// //                 strcpy((char *)current_dir, "Counter-CW      ");
// //             } else {
// //                 strcpy((char *)current_dir, "Stopped         ");
// //             }

// //             /* 
// //              * Calculation for RPM:
// //              * Timer configured to trigger every 100 ms (10 times a second).
// //              * RPM = (abs(pulses) / PULSES_PER_REV) * 10 * 60 = abs(pulses) * 600 / PULSES_PER_REV
// //              * (If your timer period is different in SysConfig, adjust the multiplier accordingly).
// //              */
// //             rpm = (uint32_t)((abs(pulses) * 600UL) / PULSES_PER_REV);
// //             update_display = true;
// //             break;
// //         }
// //         default:
// //             break;
// //     }
// // }

// /* ============================================================
//  * TIMER INTERRUPT - RPM CALCULATION
//  * ============================================================ */

// void TIMA0_IRQHandler(void)
// {
//     if (DL_TimerA_getPendingInterrupt(TIMER_0_INST)
//         == DL_TIMER_IIDX_ZERO)
//     {
//         static uint8_t tick_count = 0U;

//         tick_count++;

//         if (tick_count >= SAMPLE_TICKS)
//         {
//             tick_count = 0U;
//             timer_sample_count++;

//             uint32_t edges = valid_edges;
//             int32_t signed_count = net_edges;
//             int8_t last_dir = last_edge_dir;

//             valid_edges = 0U;
//             net_edges = 0;
//             last_edge_dir = 0;

//             rpm = (edges * 120UL) / COUNTS_PER_REV;

//             if (edges == 0U)
//                 direction = 0;
//             else if (signed_count > 0)
//                 direction = 1;
//             else if (signed_count < 0)
//                 direction = -1;
//             else
//                 direction = last_dir;

//             update_display = true;
//         }
//     }
// }

// /* ============================================================
//  * MAIN
//  * ============================================================ */

// // int main(void)
// // {
// //     SYSCFG_DL_init();

// //     SysTick_Init();
// //     LCD_init();

// //     /* Enable Timer Interrupt for Tachometer Sampling */
// //     NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

// //     ClearLCD();
// //     SetCursor(0, 0);
// //     LCD_print("Speed=0000RPM");
// //     SetCursor(1, 0);
// //     LCD_print("Stopped         ");

// //     uint8_t oldState = ReadWheelState();

// //     while (1)
// //     {
// //         uint8_t newState = ReadWheelState();

// //         if (newState != oldState)
// //         {
// //             uint8_t index = (uint8_t)((oldState << 2) | newState);
// //             int8_t delta = quadrature_delta[index];
// //             oldState = newState;

// //             if (delta != 0)
// //             {
// //                 net_delta_pulses += delta;
// //             }
// //             update_display = true;
// //         }

// //         if (update_display)
// //         {
// //             char line1[17];
// //             char line2[17];

// //             snprintf(line1, sizeof(line1), "Speed=%04luRPM", (unsigned long)rpm);
// //             snprintf(line2, sizeof(line2), "%-16s", current_dir);

// //             SetCursor(0, 0);
// //             LCD_print(line1);
// //             SetCursor(1, 0);
// //             LCD_print(line2);

// //             // delay_ms(500);
// //             update_display = false;
// //         }
// //     }
// // }

// int main(void)
// {
//     __disable_irq();

//     SYSCFG_DL_init();
//     SysTick_Init();
//     LCD_init();

//     SetCursor(0, 0);
//     LCD_print("Speed=0000RPM   ");

//     SetCursor(1, 0);
//     LCD_print("Stopped         ");

//     oldWheelState = ReadWheelState();

//     /* Enable PB7 and PB8 interrupts */
//     DL_GPIO_clearInterruptStatus(GPIOB, ENCODER_PINS);
//     DL_GPIO_enableInterrupt(GPIOB, ENCODER_PINS);

//     NVIC_ClearPendingIRQ(GPIOB_INT_IRQn);
//     NVIC_EnableIRQ(GPIOB_INT_IRQn);

//     /* Enable original TIMA0 interrupt */
//     DL_TimerA_clearInterruptStatus(
//         TIMER_0_INST,
//         DL_TIMERA_INTERRUPT_ZERO_EVENT
//     );

//     DL_TimerA_enableInterrupt(
//         TIMER_0_INST,
//         DL_TIMERA_INTERRUPT_ZERO_EVENT
//     );

//     NVIC_ClearPendingIRQ(TIMER_0_INST_INT_IRQN);
//     NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

//     /* Timer auto-starts through SysConfig */
//     __enable_irq();

//     while (1)
//     {
//         if (update_display)
//         {
//             uint32_t rpm_snapshot;
//             int8_t direction_snapshot;

//             __disable_irq();

//             rpm_snapshot = rpm;
//             direction_snapshot = direction;
//             update_display = false;

//             __enable_irq();

//             if (rpm_snapshot > 9999U)
//                 rpm_snapshot = 9999U;

//             const char *dir_text;

//             if (direction_snapshot > 0)
//                 dir_text = "Clockwise";
//             else if (direction_snapshot < 0)
//                 dir_text = "Counter-CW";
//             else
//                 dir_text = "Stopped";

//             char line1[17];
//             char line2[17];

//             snprintf(
//                 line1,
//                 sizeof(line1),
//                 "Speed=%04luRPM   ",
//                 (unsigned long)rpm_snapshot
//             );

//             snprintf(
//                 line2,
//                 sizeof(line2),
//                 "%-16s",
//                 dir_text
//             );

//             SetCursor(0, 0);
//             LCD_print(line1);

//             SetCursor(1, 0);
//             LCD_print(line2);
//         }
//     }
// }

/*---------Lab 5---------*/


#include "ti_msp_dl_config.h"

/* Counter and multiplexing state variables */
static volatile uint8_t gCounter = 0;
static volatile uint16_t gTickCount = 0;
static volatile bool gDisplaySelect = false; // false = Tens digit, true = Units digit

/* Helper function to output a 4-bit BCD value to the 74LS47 decoder */
void set_bcd_output(uint8_t val) {
    // Bit 0 (LSB) -> SEG_A_PIN
    if (val & 0x01) {
        DL_GPIO_setPins(GPIO_GRP_1_SEG_A_PIN_PORT, GPIO_GRP_1_SEG_A_PIN_PIN);
    } else {
        DL_GPIO_clearPins(GPIO_GRP_1_SEG_A_PIN_PORT, GPIO_GRP_1_SEG_A_PIN_PIN);
    }

    // Bit 1 -> SEG_B_PIN
    if (val & 0x02) {
        DL_GPIO_setPins(GPIO_GRP_1_SEG_B_PIN_PORT, GPIO_GRP_1_SEG_B_PIN_PIN);
    } else {
        DL_GPIO_clearPins(GPIO_GRP_1_SEG_B_PIN_PORT, GPIO_GRP_1_SEG_B_PIN_PIN);
    }

    // Bit 2 -> SEG_C_PIN
    if (val & 0x04) {
        DL_GPIO_setPins(GPIO_GRP_1_SEG_C_PIN_PORT, GPIO_GRP_1_SEG_C_PIN_PIN);
    } else {
        DL_GPIO_clearPins(GPIO_GRP_1_SEG_C_PIN_PORT, GPIO_GRP_1_SEG_C_PIN_PIN);
    }

    // Bit 3 (MSB) -> SEG_D_PIN
    if (val & 0x08) {
        DL_GPIO_setPins(GPIO_GRP_1_SEG_D_PIN_PORT, GPIO_GRP_1_SEG_D_PIN_PIN);
    } else {
        DL_GPIO_clearPins(GPIO_GRP_1_SEG_D_PIN_PORT, GPIO_GRP_1_SEG_D_PIN_PIN);
    }
}

int main(void) {
    // Initialize system and peripherals configured in SysConfig
    SYSCFG_DL_init();

    // Enable Timer interrupt for multiplexing and counting
    DL_TimerA_startCounter(TIMER_0_INST);
    NVIC_EnableIRQ(TIMER_0_INST_INT_IRQN);

    while (1) {
        // Main loop can perform other background tasks if needed
        __WFI(); // Wait For Interrupt to save power
    }
}

/* Timer Interrupt Handler (fires every 8.33 ms) */
void TIMER_0_INST_IRQHandler(void) {
    switch (DL_TimerA_getPendingInterrupt(TIMER_0_INST)) {
        case DL_TIMER_IIDX_ZERO:
            {
                // 1. Update counter every ~1 second (120 ticks * 8.33 ms = 1000 ms)
                gTickCount++;
                if (gTickCount >= 120) {
                    gTickCount = 0;
                    gCounter++;
                    if (gCounter > 99) {
                        gCounter = 0;
                    }
                }

                // 2. Multiplexing logic (alternates digits every 8.33 ms)
                uint8_t tens = gCounter / 10;
                uint8_t units = gCounter % 10;

                if (!gDisplaySelect) {
                    // Display Tens Digit
                    set_bcd_output(tens);
                    
                    // Enable Digit 1 (PNP transistor active low: CLEAR turns ON)
                    DL_GPIO_clearPins(GPIO_GRP_1_SEV_SEG_1_PORT, GPIO_GRP_1_SEV_SEG_1_PIN);
                    // Disable Digit 2 (SET turns OFF)
                    DL_GPIO_setPins(GPIO_GRP_1_SEV_SEG_2_PORT, GPIO_GRP_1_SEV_SEG_2_PIN);

                    gDisplaySelect = true;
                } else {
                    // Display Units Digit
                    set_bcd_output(units);

                    // Disable Digit 1 (SET turns OFF)
                    DL_GPIO_setPins(GPIO_GRP_1_SEV_SEG_1_PORT, GPIO_GRP_1_SEV_SEG_1_PIN);
                    // Enable Digit 2 (PNP transistor active low: CLEAR turns ON)
                    DL_GPIO_clearPins(GPIO_GRP_1_SEV_SEG_2_PORT, GPIO_GRP_1_SEV_SEG_2_PIN);

                    gDisplaySelect = false;
                }
            }
            break;
        default:
            break;
    }
}