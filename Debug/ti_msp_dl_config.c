/*
 * Copyright (c) 2023, Texas Instruments Incorporated
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
 *  ============ ti_msp_dl_config.c =============
 *  Configured MSPM0 DriverLib module definitions
 *
 *  DO NOT EDIT - This file is generated for the MSPM0G350X
 *  by the SysConfig tool.
 */

#include "ti_msp_dl_config.h"

DL_TimerA_backupConfig gTIMER_0Backup;

/*
 *  ======== SYSCFG_DL_init ========
 *  Perform any initialization needed before using any board APIs
 */
SYSCONFIG_WEAK void SYSCFG_DL_init(void)
{
    SYSCFG_DL_initPower();
    SYSCFG_DL_GPIO_init();
    /* Module-Specific Initializations*/
    SYSCFG_DL_SYSCTL_init();
    SYSCFG_DL_TIMER_0_init();
    SYSCFG_DL_I2C_0_init();
    /* Ensure backup structures have no valid state */
	gTIMER_0Backup.backupRdy 	= false;

}
/*
 * User should take care to save and restore register configuration in application.
 * See Retention Configuration section for more details.
 */
SYSCONFIG_WEAK bool SYSCFG_DL_saveConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_saveConfiguration(TIMER_0_INST, &gTIMER_0Backup);

    return retStatus;
}


SYSCONFIG_WEAK bool SYSCFG_DL_restoreConfiguration(void)
{
    bool retStatus = true;

	retStatus &= DL_TimerA_restoreConfiguration(TIMER_0_INST, &gTIMER_0Backup, false);

    return retStatus;
}

SYSCONFIG_WEAK void SYSCFG_DL_initPower(void)
{
    DL_GPIO_reset(GPIOA);
    DL_GPIO_reset(GPIOB);
    DL_TimerA_reset(TIMER_0_INST);
    DL_I2C_reset(I2C_0_INST);

    DL_GPIO_enablePower(GPIOA);
    DL_GPIO_enablePower(GPIOB);
    DL_TimerA_enablePower(TIMER_0_INST);
    DL_I2C_enablePower(I2C_0_INST);
    delay_cycles(POWER_STARTUP_DELAY);
}

SYSCONFIG_WEAK void SYSCFG_DL_GPIO_init(void)
{

    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_0_IOMUX_SDA,
        GPIO_I2C_0_IOMUX_SDA_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_initPeripheralInputFunctionFeatures(GPIO_I2C_0_IOMUX_SCL,
        GPIO_I2C_0_IOMUX_SCL_FUNC, DL_GPIO_INVERSION_DISABLE,
        DL_GPIO_RESISTOR_NONE, DL_GPIO_HYSTERESIS_DISABLE,
        DL_GPIO_WAKEUP_DISABLE);
    DL_GPIO_enableHiZ(GPIO_I2C_0_IOMUX_SDA);
    DL_GPIO_enableHiZ(GPIO_I2C_0_IOMUX_SCL);

    DL_GPIO_initDigitalOutput(GPIO_GRP_0_PIN_RS_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_0_PIN_D6_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_0_PIN_RW_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_0_PIN_EN_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_0_PIN_D4_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_0_PIN_D5_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_0_PIN_D7_IOMUX);

    DL_GPIO_initDigitalInputFeatures(GG_OCTO_OCTOLEFT_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalInputFeatures(GG_OCTO_OCTORIGHT_IOMUX,
		 DL_GPIO_INVERSION_DISABLE, DL_GPIO_RESISTOR_PULL_UP,
		 DL_GPIO_HYSTERESIS_DISABLE, DL_GPIO_WAKEUP_DISABLE);

    DL_GPIO_initDigitalOutput(GPIO_GRP_1_SEG_A_PIN_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_1_SEG_B_PIN_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_1_SEG_C_PIN_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_1_SEG_D_PIN_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_1_SEG_E_PIN_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_1_SEG_G_PIN_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_1_SEG_F_PIN_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_1_SEV_SEG_1_IOMUX);

    DL_GPIO_initDigitalOutput(GPIO_GRP_1_SEV_SEG_2_IOMUX);

    DL_GPIO_clearPins(GPIOA, GPIO_GRP_0_PIN_D6_PIN |
		GPIO_GRP_0_PIN_RW_PIN |
		GPIO_GRP_0_PIN_EN_PIN |
		GPIO_GRP_1_SEG_A_PIN_PIN |
		GPIO_GRP_1_SEG_D_PIN_PIN |
		GPIO_GRP_1_SEG_E_PIN_PIN |
		GPIO_GRP_1_SEG_F_PIN_PIN |
		GPIO_GRP_1_SEV_SEG_1_PIN |
		GPIO_GRP_1_SEV_SEG_2_PIN);
    DL_GPIO_enableOutput(GPIOA, GPIO_GRP_0_PIN_D6_PIN |
		GPIO_GRP_0_PIN_RW_PIN |
		GPIO_GRP_0_PIN_EN_PIN |
		GPIO_GRP_1_SEG_A_PIN_PIN |
		GPIO_GRP_1_SEG_D_PIN_PIN |
		GPIO_GRP_1_SEG_E_PIN_PIN |
		GPIO_GRP_1_SEG_F_PIN_PIN |
		GPIO_GRP_1_SEV_SEG_1_PIN |
		GPIO_GRP_1_SEV_SEG_2_PIN);
    DL_GPIO_clearPins(GPIOB, GPIO_GRP_0_PIN_RS_PIN |
		GPIO_GRP_0_PIN_D4_PIN |
		GPIO_GRP_0_PIN_D5_PIN |
		GPIO_GRP_0_PIN_D7_PIN |
		GPIO_GRP_1_SEG_B_PIN_PIN |
		GPIO_GRP_1_SEG_C_PIN_PIN |
		GPIO_GRP_1_SEG_G_PIN_PIN);
    DL_GPIO_enableOutput(GPIOB, GPIO_GRP_0_PIN_RS_PIN |
		GPIO_GRP_0_PIN_D4_PIN |
		GPIO_GRP_0_PIN_D5_PIN |
		GPIO_GRP_0_PIN_D7_PIN |
		GPIO_GRP_1_SEG_B_PIN_PIN |
		GPIO_GRP_1_SEG_C_PIN_PIN |
		GPIO_GRP_1_SEG_G_PIN_PIN);
    DL_GPIO_setLowerPinsPolarity(GPIOB, DL_GPIO_PIN_7_EDGE_RISE_FALL |
		DL_GPIO_PIN_8_EDGE_RISE_FALL);
    DL_GPIO_clearInterruptStatus(GPIOB, GG_OCTO_OCTOLEFT_PIN |
		GG_OCTO_OCTORIGHT_PIN);
    DL_GPIO_enableInterrupt(GPIOB, GG_OCTO_OCTOLEFT_PIN |
		GG_OCTO_OCTORIGHT_PIN);

}


SYSCONFIG_WEAK void SYSCFG_DL_SYSCTL_init(void)
{

	//Low Power Mode is configured to be SLEEP0
    DL_SYSCTL_setBORThreshold(DL_SYSCTL_BOR_THRESHOLD_LEVEL_0);

    DL_SYSCTL_setSYSOSCFreq(DL_SYSCTL_SYSOSC_FREQ_BASE);
    /* Set default configuration */
    DL_SYSCTL_disableHFXT();
    DL_SYSCTL_disableSYSPLL();
    DL_SYSCTL_setULPCLKDivider(DL_SYSCTL_ULPCLK_DIV_1);
    DL_SYSCTL_setMCLKDivider(DL_SYSCTL_MCLK_DIVIDER_DISABLE);

}



/*
 * Timer clock configuration to be sourced by BUSCLK /  (4000000 Hz)
 * timerClkFreq = (timerClkSrc / (timerClkDivRatio * (timerClkPrescale + 1)))
 *   62500 Hz = 4000000 Hz / (8 * (63 + 1))
 */
static const DL_TimerA_ClockConfig gTIMER_0ClockConfig = {
    .clockSel    = DL_TIMER_CLOCK_BUSCLK,
    .divideRatio = DL_TIMER_CLOCK_DIVIDE_8,
    .prescale    = 63U,
};

/*
 * Timer load value (where the counter starts from) is calculated as (timerPeriod * timerClockFreq) - 1
 * TIMER_0_INST_LOAD_VALUE = (8.33 ms * 62500 Hz) - 1
 */
static const DL_TimerA_TimerConfig gTIMER_0TimerConfig = {
    .period     = TIMER_0_INST_LOAD_VALUE,
    .timerMode  = DL_TIMER_TIMER_MODE_PERIODIC,
    .startTimer = DL_TIMER_START,
};

SYSCONFIG_WEAK void SYSCFG_DL_TIMER_0_init(void) {

    DL_TimerA_setClockConfig(TIMER_0_INST,
        (DL_TimerA_ClockConfig *) &gTIMER_0ClockConfig);

    DL_TimerA_initTimerMode(TIMER_0_INST,
        (DL_TimerA_TimerConfig *) &gTIMER_0TimerConfig);
    DL_TimerA_enableInterrupt(TIMER_0_INST , DL_TIMERA_INTERRUPT_ZERO_EVENT);
    DL_TimerA_enableClock(TIMER_0_INST);





}


static const DL_I2C_ClockConfig gI2C_0ClockConfig = {
    .clockSel = DL_I2C_CLOCK_BUSCLK,
    .divideRatio = DL_I2C_CLOCK_DIVIDE_1,
};

SYSCONFIG_WEAK void SYSCFG_DL_I2C_0_init(void) {

    DL_I2C_setClockConfig(I2C_0_INST,
        (DL_I2C_ClockConfig *) &gI2C_0ClockConfig);
    DL_I2C_setAnalogGlitchFilterPulseWidth(I2C_0_INST,
        DL_I2C_ANALOG_GLITCH_FILTER_WIDTH_50NS);
    DL_I2C_enableAnalogGlitchFilter(I2C_0_INST);




}

