/*
 * Copyright (c) 2023, Texas Instruments Incorporated - http://www.ti.com
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ============ ti_msp_dl_config.h =============
 *  Configured MSPM0 DriverLib module declarations
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */
#ifndef ti_msp_dl_config_h
#define ti_msp_dl_config_h

#define CONFIG_MSPM0G350X
#define CONFIG_MSPM0G3507

#if defined(__ti_version__) || defined(__TI_COMPILER_VERSION__)
#define SYSCONFIG_WEAK __attribute__((weak))
#elif defined(__IAR_SYSTEMS_ICC__)
#define SYSCONFIG_WEAK __weak
#elif defined(__GNUC__)
#define SYSCONFIG_WEAK __attribute__((weak))
#endif

#include <ti/devices/msp/msp.h>
#include <ti/driverlib/driverlib.h>
#include <ti/driverlib/m0p/dl_core.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform all required MSP DL initialization
 *
 *  This function should be called once at a point before any use of
 *  MSP DL.
 */


/* clang-format off */

#define POWER_STARTUP_DELAY                                                (16)


#define CPUCLK_FREQ                                                     32000000



/* Defines for PWM */
#define PWM_INST                                                           TIMA1
#define PWM_INST_IRQHandler                                     TIMA1_IRQHandler
#define PWM_INST_INT_IRQN                                       (TIMA1_INT_IRQn)
#define PWM_INST_CLK_FREQ                                                1000000
/* GPIO defines for channel 0 */
#define GPIO_PWM_C0_PORT                                                   GPIOB
#define GPIO_PWM_C0_PIN                                            DL_GPIO_PIN_4
#define GPIO_PWM_C0_IOMUX                                        (IOMUX_PINCM17)
#define GPIO_PWM_C0_IOMUX_FUNC                       IOMUX_PINCM17_PF_TIMA1_CCP0
#define GPIO_PWM_C0_IDX                                      DL_TIMER_CC_0_INDEX



/* Defines for TIMER_0 */
#define TIMER_0_INST                                                     (TIMA0)
#define TIMER_0_INST_IRQHandler                                 TIMA0_IRQHandler
#define TIMER_0_INST_INT_IRQN                                   (TIMA0_INT_IRQn)
#define TIMER_0_INST_LOAD_VALUE                                             (2U)




/* Defines for I2C_0 */
#define I2C_0_INST                                                          I2C0
#define I2C_0_INST_IRQHandler                                    I2C0_IRQHandler
#define I2C_0_INST_INT_IRQN                                        I2C0_INT_IRQn
#define GPIO_I2C_0_SDA_PORT                                                GPIOA
#define GPIO_I2C_0_SDA_PIN                                         DL_GPIO_PIN_0
#define GPIO_I2C_0_IOMUX_SDA                                      (IOMUX_PINCM1)
#define GPIO_I2C_0_IOMUX_SDA_FUNC                       IOMUX_PINCM1_PF_I2C0_SDA
#define GPIO_I2C_0_SCL_PORT                                                GPIOA
#define GPIO_I2C_0_SCL_PIN                                         DL_GPIO_PIN_1
#define GPIO_I2C_0_IOMUX_SCL                                      (IOMUX_PINCM2)
#define GPIO_I2C_0_IOMUX_SCL_FUNC                       IOMUX_PINCM2_PF_I2C0_SCL



/* Defines for HB_IN2: GPIOA.8 with pinCMx 19 on package pin 54 */
#define GPIO_GRP_0_HB_IN2_PORT                                           (GPIOA)
#define GPIO_GRP_0_HB_IN2_PIN                                    (DL_GPIO_PIN_8)
#define GPIO_GRP_0_HB_IN2_IOMUX                                  (IOMUX_PINCM19)
/* Defines for HB_IN1: GPIOB.9 with pinCMx 26 on package pin 61 */
#define GPIO_GRP_0_HB_IN1_PORT                                           (GPIOB)
#define GPIO_GRP_0_HB_IN1_PIN                                    (DL_GPIO_PIN_9)
#define GPIO_GRP_0_HB_IN1_IOMUX                                  (IOMUX_PINCM26)
/* Defines for IN_0: GPIOB.7 with pinCMx 24 on package pin 59 */
#define GPIO_GRP_0_IN_0_PORT                                             (GPIOB)
#define GPIO_GRP_0_IN_0_PIN                                      (DL_GPIO_PIN_7)
#define GPIO_GRP_0_IN_0_IOMUX                                    (IOMUX_PINCM24)
/* Defines for IN_1: GPIOB.6 with pinCMx 23 on package pin 58 */
#define GPIO_GRP_0_IN_1_PORT                                             (GPIOB)
#define GPIO_GRP_0_IN_1_PIN                                      (DL_GPIO_PIN_6)
#define GPIO_GRP_0_IN_1_IOMUX                                    (IOMUX_PINCM23)
/* Defines for IN_2: GPIOB.21 with pinCMx 49 on package pin 20 */
#define GPIO_GRP_0_IN_2_PORT                                             (GPIOB)
#define GPIO_GRP_0_IN_2_PIN                                     (DL_GPIO_PIN_21)
#define GPIO_GRP_0_IN_2_IOMUX                                    (IOMUX_PINCM49)


/* clang-format on */

void SYSCFG_DL_init(void);
void SYSCFG_DL_initPower(void);
void SYSCFG_DL_GPIO_init(void);
void SYSCFG_DL_SYSCTL_init(void);
void SYSCFG_DL_PWM_init(void);
void SYSCFG_DL_TIMER_0_init(void);
void SYSCFG_DL_I2C_0_init(void);


bool SYSCFG_DL_saveConfiguration(void);
bool SYSCFG_DL_restoreConfiguration(void);

#ifdef __cplusplus
}
#endif

#endif /* ti_msp_dl_config_h */
