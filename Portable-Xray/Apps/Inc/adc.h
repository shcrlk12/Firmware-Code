/*
 * adc.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef INC_ADC_H_
#define INC_ADC_H_

#include <stdint.h>

uint16_t ADC_Get_VFB_GATE(void);
uint16_t ADC_Get_VFB_ACCU(void);
uint16_t ADC_Get_VFB_BUCK(void);
uint16_t ADC_Get_VFB_ANODE(void);

uint16_t ADC_Get_IFB_ACCU(void);
uint16_t ADC_Get_IFB_BUCK(void);

uint16_t ADC_Get_TEMP_MCU(void);
uint16_t ADC_Get_TEMP_SYS(void);

#endif /* INC_ADC_H_ */
