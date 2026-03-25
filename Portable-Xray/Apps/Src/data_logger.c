/*
 * data_logger.c
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */


#include "data_logger.h"
#include <stdint.h>
#include "adc.h"

#define BUFFER_LENGTH_LOG 1024
#define N_RESULT_PAGES 128
#define MASK_NORMAL_TRANSIENT 1023
#define RESULT_PAGE_MASK 127

// these are for recording logs
volatile uint8_t log_start = 0;
volatile uint16_t log_index = 0;
volatile uint16_t log_interval = 0;
volatile uint16_t log_interval_counter = 0;

static uint16_t log_buffer_v_gate[BUFFER_LENGTH_LOG];
static uint16_t log_buffer_v_accu[BUFFER_LENGTH_LOG];
static uint16_t log_buffer_v_anode[BUFFER_LENGTH_LOG];
static uint16_t log_buffer_v_buck[BUFFER_LENGTH_LOG];
static uint16_t log_buffer_i_accu[BUFFER_LENGTH_LOG];
static uint16_t log_buffer_i_anode[BUFFER_LENGTH_LOG];

volatile uint16_t explog_index = 0;
static uint16_t explog_v_gate[N_RESULT_PAGES];
static uint16_t explog_v_accu[N_RESULT_PAGES];
static uint16_t explog_v_anode[N_RESULT_PAGES];
static uint16_t explog_v_buck[N_RESULT_PAGES];
static uint16_t explog_i_accu[N_RESULT_PAGES];
static uint16_t explog_i_anode[N_RESULT_PAGES];

void DATALOG_Start(uint16_t interval)
{
    log_index = 0;
    log_interval = interval;
    log_interval_counter = 0;
    log_start = 1;
}

void DATALOG_Sample()
{
    // log transient data
    if(log_start == 1)
    {
        if(log_interval_counter == 0)
        {
            if(log_index < BUFFER_LENGTH_LOG)
            {
                log_buffer_v_gate[log_index] = ADC_Get_VFB_GATE();
                log_buffer_v_accu[log_index] = ADC_Get_VFB_ACCU();
                log_buffer_v_anode[log_index] = ADC_Get_VFB_ANODE();
                log_buffer_v_buck[log_index] = ADC_Get_VFB_BUCK();
                log_buffer_i_accu[log_index] = ADC_Get_IFB_ACCU();
                log_buffer_i_anode[log_index] = ADC_Get_IFB_BUCK();
                log_index++;
            }
            else
            {
                log_start = 0;
            }
        }

        log_interval_counter++;
        if(log_interval_counter >= log_interval)
        {
            log_interval_counter = 0;
        }
    }
}

void DATALOG_FillBufferWithZero()
{
    for(int i = log_index; i < BUFFER_LENGTH_LOG; i++)
    {
        log_buffer_v_gate[i] = 0;
        log_buffer_v_accu[i] = 0;
        log_buffer_v_anode[i] = 0;
        log_buffer_v_buck[i] = 0;
        log_buffer_i_accu[i] = 0;
        log_buffer_i_anode[i] = 0;
    }
}

uint32_t DATALOG_GetData(uint16_t index, uint16_t type)
{
    uint16_t target_index = index & MASK_NORMAL_TRANSIENT;
    uint16_t target_type = type & 0x07;
    uint32_t result;
    switch(target_type)
    {
        case 0:
            result = CONV_V_GATE_LSB_to_V(log_buffer_v_gate[target_index]);
            break;
        case 1:
            result = CONV_V_ACCU_LSB_to_V(log_buffer_v_accu[target_index]);
            break;
        case 2:
            result = CONV_V_ANODE_LSB_to_10V(log_buffer_v_anode[target_index]);
            break;
        case 3:
            result = CONV_V_BUCK_LSB_to_mV(log_buffer_v_buck[target_index]);
            break;
        case 4:
            result = CONV_I_ACCU_LSB_to_uA(log_buffer_i_accu[target_index]);
            break;
        case 5:
        default:
            result = CONV_I_ANODE_LSB_to_mA(log_buffer_i_anode[target_index]);
            break;
    }
    return result;
}

void DATALOG_GetDataSet(uint16_t index, uint16_t *data_buffer)
{
    *(data_buffer) = log_buffer_v_gate[index];
    *(data_buffer + 1) = log_buffer_v_accu[index];
    *(data_buffer + 2) = log_buffer_v_anode[index];
    *(data_buffer + 3) = log_buffer_v_buck[index];
    *(data_buffer + 4) = log_buffer_i_accu[index];
    *(data_buffer + 5) = log_buffer_i_anode[index];
}

void DATALOG_InitExposureLog()
{
    explog_index = 0;
    memset(explog_v_gate, 0, sizeof(uint16_t) * N_RESULT_PAGES);
    memset(explog_v_accu, 0, sizeof(uint16_t) * N_RESULT_PAGES);
    memset(explog_v_anode, 0, sizeof(uint16_t) * N_RESULT_PAGES);
    memset(explog_v_buck, 0, sizeof(uint16_t) * N_RESULT_PAGES);
    memset(explog_i_accu, 0, sizeof(uint16_t) * N_RESULT_PAGES);
    memset(explog_i_anode, 0, sizeof(uint16_t) * N_RESULT_PAGES);
}

void DATALOG_ExposureLog(uint16_t v_gate, uint16_t v_accu, uint16_t v_anode, uint16_t v_buck, uint16_t i_accu, uint16_t i_anode)
{
    explog_index = (explog_index + 1) & RESULT_PAGE_MASK;
    explog_v_gate[explog_index] = v_gate;
    explog_v_accu[explog_index] = v_accu;
    explog_v_anode[explog_index] = v_anode;
    explog_v_buck[explog_index] = v_buck;
    explog_i_accu[explog_index] = i_accu;
    explog_i_anode[explog_index] = i_anode;
}

void DATALOG_GetExpLogSet(uint16_t nth_old, uint16_t *data_buffer)
{
    nth_old = nth_old & RESULT_PAGE_MASK;
    uint16_t index = explog_index + N_RESULT_PAGES;
    index = (index - nth_old) & RESULT_PAGE_MASK;
    *(data_buffer) = explog_v_gate[index];
    *(data_buffer + 1) = explog_v_accu[index];
    *(data_buffer + 2) = explog_v_anode[index];
    *(data_buffer + 3) = explog_v_buck[index];
    *(data_buffer + 4) = explog_i_accu[index];
    *(data_buffer + 5) = explog_i_anode[index];
}
