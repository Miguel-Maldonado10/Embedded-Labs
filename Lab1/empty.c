// #include "ti_msp_dl_config.h"
// #include <stdint.h>

// /* LAB 7 - TABLE 7.3
//  *
 
// PB1 -> PB7 -> STOP
// PB2 -> PB6 -> LEFT
// PB3 -> PB8 -> RIGHT*
// S1 -> PB9
// S2 -> PA8*/

// void setMotorState(uint32_t s1, uint32_t s2)
// {
//     // Clear both outputs first
//     DL_GPIO_clearPins(
//         GPIO_GRP_0_HB_IN1_PORT,
//         GPIO_GRP_0_HB_IN1_PIN
//     );

//     DL_GPIO_clearPins(
//         GPIO_GRP_0_HB_IN2_PORT,
//         GPIO_GRP_0_HB_IN2_PIN
//     );

//     if (s1) {
//         DL_GPIO_setPins(
//             GPIO_GRP_0_HB_IN1_PORT,
//             GPIO_GRP_0_HB_IN1_PIN
//         );
//     }

//     if (s2) {
//         DL_GPIO_setPins(
//             GPIO_GRP_0_HB_IN2_PORT,
//             GPIO_GRP_0_HB_IN2_PIN
//         );
//     }
// }

// int main(void)
// {
//     SYSCFG_DL_init();

//     // Start stopped
//     setMotorState(0, 0);

//     while (1)
//     {
//         // PB1: active LOW
//         uint32_t pb1 = DL_GPIO_readPins(
//             GPIO_GRP_0_IN_0_PORT,
//             GPIO_GRP_0_IN_0_PIN
//         ) & GPIO_GRP_0_IN_0_PIN;

//         // PB2: active HIGH
//         uint32_t pb2 = DL_GPIO_readPins(
//             GPIO_GRP_0_IN_1_PORT,
//             GPIO_GRP_0_IN_1_PIN
//         ) & GPIO_GRP_0_IN_1_PIN;

//         // PB3: active LOW
//         uint32_t pb3 = DL_GPIO_readPins(
//             GPIO_GRP_0_IN_2_PORT,
//             GPIO_GRP_0_IN_2_PIN
//         ) & GPIO_GRP_0_IN_2_PIN;

//         if (pb1 == 0) {
//             // Button 1: STOP
//             setMotorState(0, 0);
//         }
//         else if (pb2 != 0) {
//             // Button 2: LEFT
//             setMotorState(0, 1);
//         }
//         else if (pb3 == 0) {
//             // Button 3: RIGHT
//             setMotorState(1, 0);
//         }

//         // Keep previous state when no button is pressed
//         DL_Common_delayCycles(320000);
//     }
// }

//=====================================================================


/*========== LAB 7.2.2 ==========*/

// #include "ti_msp_dl_config.h"
// #include <stdint.h>

// /*
//  * LAB 7.2.2 - DC MOTOR WITH SPEED CONTROL
//  *
//  * Basic I/O S1 -> PB7  -> Speed UP 20%
//  * Basic I/O S2 -> PB6  -> Speed DOWN 20%
//  * LaunchPad S2 -> PB21 -> STOP / LEFT / RIGHT
//  *
//  * PB9 -> L293D M_IN1
//  * PA8 -> L293D M_IN2
//  *
//  * Software PWM using GPIO
//  */

// // About 1 ms at 32 MHz, before software overhead
// #define PWM_PERIOD_CYCLES 32000U

// typedef enum {
//     MOTOR_STOP = 0,
//     MOTOR_LEFT,
//     MOTOR_RIGHT
// } MotorState;

// // Start stopped, with 60% speed selected
// static volatile MotorState motorState = MOTOR_STOP;
// static volatile uint8_t speedPercent = 100;


// /*-----------------------------------------
//  * MOTOR DIRECTION CONTROL
//  *-----------------------------------------*/

// void setMotorState(uint32_t s1, uint32_t s2)
// {
//     DL_GPIO_clearPins(
//         GPIO_GRP_0_HB_IN1_PORT,
//         GPIO_GRP_0_HB_IN1_PIN
//     );

//     DL_GPIO_clearPins(
//         GPIO_GRP_0_HB_IN2_PORT,
//         GPIO_GRP_0_HB_IN2_PIN
//     );

//     if (s1) {
//         DL_GPIO_setPins(
//             GPIO_GRP_0_HB_IN1_PORT,
//             GPIO_GRP_0_HB_IN1_PIN
//         );
//     }

//     if (s2) {
//         DL_GPIO_setPins(
//             GPIO_GRP_0_HB_IN2_PORT,
//             GPIO_GRP_0_HB_IN2_PIN
//         );
//     }
// }


// /*-----------------------------------------
//  * BUTTON INPUTS
//  *-----------------------------------------*/

// static uint8_t buttonPressed(uint8_t index)
// {
//     if (index == 0) {
//         // Basic I/O S1: active LOW
//         return !(DL_GPIO_readPins(
//             GPIOB, DL_GPIO_PIN_7
//         ) & DL_GPIO_PIN_7);
//     }

//     if (index == 1) {
//         // Basic I/O S2: active HIGH
//         return !!(DL_GPIO_readPins(
//             GPIOB, DL_GPIO_PIN_6
//         ) & DL_GPIO_PIN_6);
//     }

//     // LaunchPad S2: active LOW
//     return !(DL_GPIO_readPins(
//         GPIOB, DL_GPIO_PIN_21
//     ) & DL_GPIO_PIN_21);
// }


// /*-----------------------------------------
//  * BUTTON ACTIONS
//  *-----------------------------------------*/

// static void handleButton(uint8_t index)
// {
//     if (index == 0) {
//         // Speed UP: +20%
//         if (speedPercent < 100) {
//             speedPercent += 20;
//         }
//     }

//     else if (index == 1) {
//         // Speed DOWN: -20%
//         if (speedPercent >= 20) {
//             speedPercent -= 20;
//         }
//     }

//     else {
//         // STOP -> LEFT -> RIGHT -> STOP
//         if (motorState == MOTOR_STOP) {
//             motorState = MOTOR_LEFT;
//         }
//         else if (motorState == MOTOR_LEFT) {
//             motorState = MOTOR_RIGHT;
//         }
//         else {
//             motorState = MOTOR_STOP;
//         }
//     }
// }


// /*-----------------------------------------
//  * SOFTWARE PWM SPEED CONTROL
//  *-----------------------------------------*/

// static void motorPWM(void)
// {
//     uint8_t duty = speedPercent;

//     // Motor stopped or zero speed
//     if (motorState == MOTOR_STOP || duty == 0) {
//         setMotorState(0, 0);
//         DL_Common_delayCycles(PWM_PERIOD_CYCLES);
//         return;
//     }

//     uint32_t s1 = (motorState == MOTOR_RIGHT);
//     uint32_t s2 = (motorState == MOTOR_LEFT);

//     // 100% duty cycle
//     if (duty == 100) {
//         setMotorState(s1, s2);
//         DL_Common_delayCycles(PWM_PERIOD_CYCLES);
//         return;
//     }

//     uint32_t onCycles =
//         (PWM_PERIOD_CYCLES * duty) / 100U;

//     uint32_t offCycles =
//         PWM_PERIOD_CYCLES - onCycles;

//     // ON part of PWM
//     setMotorState(s1, s2);
//     DL_Common_delayCycles(onCycles);

//     // OFF part of PWM
//     setMotorState(0, 0);
//     DL_Common_delayCycles(offCycles);
// }


// /*-----------------------------------------
//  * MAIN
//  *-----------------------------------------*/


// int main(void)
// {
//     SYSCFG_DL_init();

//     // Start with the motor stopped
//     setMotorState(0, 0);

//     uint8_t ready[3] = {1, 1, 1};
//     uint8_t releaseCount[3] = {25, 25, 25};

//     while (1)
//     {
//         for (uint8_t i = 0; i < 3; i++)
//         {
//             uint8_t pressed = buttonPressed(i);

//             if (pressed)
//             {
//                 releaseCount[i] = 0;

//                 // One action per button press
//                 if (ready[i])
//                 {
//                     handleButton(i);
//                     ready[i] = 0;
//                 }
//             }
//             else
//             {
//                 // Wait for a stable release
//                 if (releaseCount[i] < 25)
//                 {
//                     releaseCount[i]++;
//                 }

//                 if (releaseCount[i] >= 25)
//                 {
//                     ready[i] = 1;
//                 }
//             }
//         }

//         // Keep generating PWM
//         motorPWM();
//     }
// }



//========================7.2.3 servo motor========================//
#include "ti_msp_dl_config.h"

#define SERVO_MIN_US 375U
#define SERVO_MAX_US 2100U
#define SERVO_PERIOD 20000U
#define CPU_HZ 32000000U  // Verificar MCLK en SysConfig

// Absolute positions, represented in half-degrees
const uint16_t routineAnglesX2[] = {
    45,   // 22.5 degrees
    225,  // 112.5 degrees
    180,  // 90 degrees
    270,  // 135 degrees
    90,   // 45 degrees
    360,  // 180 degrees
    315,  // 157.5 degrees
    135,  // 67.5 degrees
    0     // 0 degrees
};

void servoSetAngle(uint16_t angleX2)
{
    if (angleX2 > 360U) {
        angleX2 = 360U;
    }

    uint32_t pulseUs = SERVO_MIN_US +
        ((SERVO_MAX_US - SERVO_MIN_US) *
         angleX2 + 180U) / 360U;

    // Preserves your previous PWM compare polarity
    DL_TimerA_setCaptureCompareValue(
        PWM_INST,
        SERVO_PERIOD - pulseUs,
        DL_TIMER_CC_0_INDEX
    );
}

int main(void)
{
    SYSCFG_DL_init();

    // Start at 0 degrees
    servoSetAngle(0);
    DL_TimerA_startCounter(PWM_INST);

    // Remain at 0 degrees for 2 seconds
    DL_Common_delayCycles(CPU_HZ * 2U);

    while (1)
    {
        for (uint32_t i = 0; i < 9; i++)
        {
            servoSetAngle(routineAnglesX2[i]);

            // Hold each position for 2 seconds
            DL_Common_delayCycles(CPU_HZ * 2U);
        }
    }
}
