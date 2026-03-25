/*
 * adc.c
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#include "adc.h"

// interrupt triggered adc values
volatile uint16_t ad_result_vfb_anode;
volatile uint16_t ad_result_vfb_buck;
volatile uint16_t ad_result_vfb_gate;
volatile uint16_t ad_result_vfb_accu;
volatile uint16_t ad_result_ifb_accu;
volatile uint16_t ad_result_ifb_buck;

// software triggered adc values
volatile uint16_t ad_result_v_batt;
volatile uint16_t ad_result_temp_mcu;
volatile uint16_t ad_result_temp_sys;

inline uint16_t ADC_Get_VFB_GATE(void)
{
    return ad_result_vfb_gate;
}

inline uint16_t ADC_Get_VFB_ACCU(void)
{
    return ad_result_vfb_accu;
}

inline uint16_t ADC_Get_VFB_BUCK(void)
{
    return ad_result_vfb_buck;
}

inline uint16_t ADC_Get_VFB_ANODE(void)
{
    return ad_result_vfb_anode;
}

inline uint16_t ADC_Get_IFB_ACCU(void)
{
    return ad_result_ifb_accu;
}

inline uint16_t ADC_Get_IFB_BUCK(void)
{
    return ad_result_ifb_buck;
}

inline uint16_t ADC_Get_TEMP_MCU(void)
{
    return ad_result_temp_mcu;
}

inline uint16_t ADC_Get_TEMP_SYS(void)
{
    return ad_result_temp_sys;
}
