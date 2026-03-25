/*
 * eeprom.c
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#include "eeprom.h"
#include "main_system.h"
#include <string.h>
#include "unit_conversion.h"

//#define DEBUG_EEPROM_INIT

volatile uint16_t eeprom_write_time_counter = 0;
static uint8_t i2c_wr_buffer[66]; // page size = 64; and +2 address bytes;
static uint8_t rtc_time[8];

bool EEPROM_I2C_IsBusy()
{
	//TODO: 구현해야함.
	return true;
}
void EEPROM_I2C_WriteRead(uint16_t address, uint8_t *writeData, uint16_t writeLength, uint8_t *readData, uint16_t readLength)
{
	//TODO: 구현해야함.
}


void EEPROM_I2C_Write(uint16_t address, uint8_t *data, uint16_t dataLength)
{
	//TODO: 구현해야함.
}

int EEPROM_WaitI2C(void)
{
    volatile int16_t delay_var;

    while (EEPROM_I2C_IsBusy() == 1)
    {
        for (delay_var = 0; delay_var < 1000; delay_var++)
        {
            __asm volatile ("nop");
        }
    }
    return 1;
}

volatile int EEPROM_SetAddress(uint16_t address)
{
    // address low/high shall be changed
    i2c_wr_buffer[0] = address >> 8;
    i2c_wr_buffer[1] = address & 0xFF;
    return 1;
}

void EEPROM_UpdateTimeCount(void)
{
	if(eeprom_write_time_counter < 11)
	{
		eeprom_write_time_counter++;
	}
}

void EEPROM_Write(uint16_t address, uint8_t *data, int length)
{
    EEPROM_SetAddress(address);
    for(int i = 0; i < length; i++)
    {
        i2c_wr_buffer[i + 2] = data[i];
    }

    EEPROM_I2C_Write(EEPROM_DEVICE_ADDRESS, &(i2c_wr_buffer[0]), length + 2);
    EEPROM_WaitI2C();

    // shall wait more than a write cycle (5ms in datasheet, but it takes more)
    eeprom_write_time_counter = 0;
    while(eeprom_write_time_counter < 10);
}

inline void EEPROM_WriteByte(uint16_t address, uint8_t byte)
{
    EEPROM_Write(address, &byte, 1);
}

inline void EEPROM_WriteWord(uint16_t address, uint16_t word)
{
    EEPROM_Write(address, (uint8_t *)(&word), 2);
}

inline void EEPROM_WriteDWord(uint16_t address, uint32_t dword)
{
    EEPROM_Write(address, (uint8_t *)(&dword), 4);
}

inline void EEPROM_WriteExposureResults()
{
    EEPROM_Write(ADDR_EXPOSURE_RESULTS + g_accu_system.result_page * EEPROM_PAGE_HALF, (uint8_t *)(&(g_accu_system.result)), sizeof(STRUCT_EXPOSURE_RESULTS));
    g_accu_system.result_page = (g_accu_system.result_page + 1) & RESULT_PAGE_MASK;
}

inline void EEPROM_WriteErrorInfo()
{
    EEPROM_Write(ADDR_ERROR_INFO + g_accu_system.error_page * EEPROM_PAGE_HALF, (uint8_t *)(&(g_accu_system.error_info)), sizeof(STRUCT_ERROR_LOG_INFO));
}
void EEPROM_WriteCalibrationResults()
{
    EEPROM_Write(ADDR_CAL_RESULT, (uint8_t *)(&(g_accu_system.cal_result)), sizeof(STRUCT_CAL_RESULT));
    EEPROM_Write(ADDR_CAL_TABLE, (uint8_t *)(&(g_accu_system.cal_table)), sizeof(STRUCT_CAL_TABLE));
    // update gate voltage setting
    g_accu_system.setting.v_gate_set = g_accu_system.cal_result.v_gate_op;
    uint16_t result_in_volt = CONV_V_GATE_LSB_to_V(g_accu_system.setting.v_gate_set);
    EEPROM_WriteWord(ADDR_EXPOSURE_SETTINGS + 2, result_in_volt);
    // reset error conditions
    PROC_ErrorThresholdEvaluation();
}

void EEPROM_Read(uint16_t address, uint8_t *data, int length)
{
    EEPROM_SetAddress(address);
    EEPROM_I2C_WriteRead(EEPROM_DEVICE_ADDRESS, &(i2c_wr_buffer[0]), 2, data, length);
    EEPROM_WaitI2C();
}

uint8_t EEPROM_ReadByte(uint16_t address)
{
    uint8_t byte = 0;
    EEPROM_Read(address, &byte, 1);
    return byte;
}

uint16_t EEPROM_ReadWord(uint16_t address)
{
    uint16_t word = 0;
    EEPROM_Read(address, (uint8_t *)(&word), 2);
    return word;
}

uint32_t EEPROM_ReadDWord(uint16_t address)
{
    uint32_t dword = 0;
    EEPROM_Read(address, (uint8_t *)(&dword), 4);
    return dword;
}

void EEPROM_WerayInit()
{
    g_weray.system.max_exposure_time = 1000;
    g_weray.system.min_exposure_time = 50;
    g_weray.system.on_off_duty = 60;
    EEPROM_Write(ADDR_WERAY_SYS_SETTINGS, (uint8_t *)(&(g_weray.system)), sizeof(STRUCT_WERAY_SYS_SETTINGS));

    g_weray.settings.passcode = 111;
    g_weray.settings.exp_time_increment = 10;
    g_weray.settings.exp_time = 240;
    g_weray.settings.age_sel = 0;
    g_weray.settings.menu_sel = 0;
    g_weray.settings.tooth_sel = 0;
    EEPROM_Write(ADDR_WERAY_UI_SETTINGS, (uint8_t *)(&(g_weray.settings)), sizeof(STRUCT_WERAY_UI_SETTINGS));

    g_weray.thresholds.temp_amb_min = 50;             // 5 degC
    g_weray.thresholds.temp_tank_max = 500;           // 50 degC
    g_weray.thresholds.v_batt_exp_min = 18500;        // 18.5V
    g_weray.thresholds.v_batt_idle_min = 22000;       // 22.0V, discharging levels
    g_weray.thresholds.v_batt_levels[0] = 22700;      // 22.7V
    g_weray.thresholds.v_batt_levels[1] = 22900;      // 22.9V
    g_weray.thresholds.v_batt_levels[2] = 23400;      // 23.4V
    g_weray.thresholds.v_batt_levels[3] = 23900;      // 23.9V
    g_weray.thresholds.v_batt_charging[0] = 23800;      // 23.8V, charging levels 2025-08-28 Update
    g_weray.thresholds.v_batt_charging[1] = 24100;      // 24.1V
    g_weray.thresholds.v_batt_charging[2] = 24400;      // 24.4V
    g_weray.thresholds.v_batt_charging[3] = 24700;      // 24.7V
    EEPROM_Write(ADDR_WERAY_THRESHOLDS, (uint8_t *)(&(g_weray.thresholds)), sizeof(STRUCT_WERAY_THRESHOLDS));

    g_weray.led_presets.led_set_boot = 0x45;         	// on    - magenta
	g_weray.led_presets.led_set_passwd = 0x15;       	// blink - magenta
	g_weray.led_presets.led_set_ready = 0x42;        	// on    - green
	g_weray.led_presets.led_set_powersave = 0x12;    	// blink - green
	g_weray.led_presets.led_set_sleep = 0x00;        	// off   - black
	g_weray.led_presets.led_set_exp_wait = 0x43;     	// on    - yellow
	g_weray.led_presets.led_set_exposure = 0x00;     	// off   - black
	g_weray.led_presets.led_set_cooldown = 0x14;     	// blink - blue
	g_weray.led_presets.led_set_error = 0x41;        	// on    - red
	g_weray.led_presets.led_set_lobatt = 0x11;       	// blink - red
	g_weray.led_presets.led_set_charge = 0x17;       	// blink - white
    g_weray.led_presets.led_full_charge = 0x47;       // on    - white
	g_weray.led_presets.led_set_tx = 0x47;           	// on    - white
	g_weray.led_presets.led_set_rx = 0x47;           	// on    - white
	g_weray.led_presets.led_set_lock = 0x16;         	// blink - cyan
	g_weray.led_presets.led_set_config = 0x22;       	// fast  - green
    EEPROM_Write(ADDR_WERAY_LED_PRESETS, (uint8_t *)(&(g_weray.led_presets)), sizeof(STRUCT_WERAY_LED_PRESETS));

	g_weray.timings.t_chattering = 10;                // 10ms
	g_weray.timings.t_exp_start_wait = 600;           // 600ms
	g_weray.timings.t_long_press_wait = 1000;         // 1000ms
	g_weray.timings.t_power_save = 60;             	// 60sec
	g_weray.timings.t_sleep = 300;                 	// 300sec
	g_weray.timings.default_exptime[0] = 250;      	// 250ms, adult-front
	g_weray.timings.default_exptime[1] = 350;      	// 350ms, adult-molar
	g_weray.timings.default_exptime[2] = 160;      	// 160ms, child-front
	g_weray.timings.default_exptime[3] = 240;      	// 240ms, child-molar
	g_weray.timings.adj_slow_interval = 150;       	// 150ms
	g_weray.timings.adj_fast_interval = 50;        	// 50ms
	g_weray.timings.t_very_long_press_wait = 2500; 	// 2500ms
	g_weray.timings.t_disp_warning = 1000;         	// 1000ms
    g_weray.timings.t_batt_mon_resume = 60;           // 60sec
    g_weray.timings.t_lr_click_wait = 100;            // 100ms
    EEPROM_Write(ADDR_WERAY_TIMINGS, (uint8_t *)(&(g_weray.timings)), sizeof(STRUCT_WERAY_TIMINGS));

	g_weray.blinks.t_led_blink_on = 500;       	// 500ms
	g_weray.blinks.t_led_blink_off = 500;      	// 500ms
	g_weray.blinks.t_led_fast_blink_on = 200;  	// 200ms
	g_weray.blinks.t_led_fast_blink_off = 200; 	// 200ms
	g_weray.blinks.t_lcd_blink_on = 50;        	// 50ms
	g_weray.blinks.t_lcd_blink_off = 50;       	// 50ms
	g_weray.blinks.t_lcd_blink_duration = 400; 	// 400ms
    EEPROM_Write(ADDR_WERAY_UI_BLINKS, (uint8_t *)(&(g_weray.blinks)), sizeof(STRUCT_WERAY_UI_BLINKS));

    g_weray.options.demo_mode = 0;
    g_weray.options.emitter_activate_enable = 0;
    g_weray.options.exp_sw_interlock = 0;
    g_weray.options.interlock_active_low = 0;
    g_weray.options.lo_batt_bypass = 0;
    g_weray.options.passcode_disable = 0;
    g_weray.options.powersave_disable = 0;
    EEPROM_Write(ADDR_WERAY_OPTIONS, (uint8_t *)(&(g_weray.options)), sizeof(STRUCT_WERAY_OPTIONS));

    STRUCT_WERAY_CIRCUIT_PARAMS circuit_param;
    circuit_param.R_VBATT_Load = 2400000;
    circuit_param.R_VBATT_Sense = 330000;
    circuit_param.R_VTEMP_Load = 10000;
    circuit_param.R_VTEMP_TC = 10000;
    circuit_param.TC_FACTOR = 3984;
    EEPROM_Write(ADDR_WERAY_CIRCUIT, (uint8_t *)(&(circuit_param)), sizeof(STRUCT_WERAY_CIRCUIT_PARAMS));
}

void EEPROM_Init()
{
    // write header
    memset(&(g_accu_system.header.header_string[0]), 0, 32);
    g_accu_system.header.header_string[0] = 'P';
    g_accu_system.header.header_string[1] = 'I';
    g_accu_system.header.header_string[2] = 'C';
    g_accu_system.header.header_string[3] = 'O';
    g_accu_system.header.header_string[4] = '-';
    g_accu_system.header.header_string[5] = 'W';
    g_accu_system.header.header_string[6] = 'E';
    g_accu_system.header.header_string[7] = 'R';
    g_accu_system.header.header_string[8] = 'A';
    g_accu_system.header.header_string[9] = 'Y';
    g_accu_system.header.header_string[10] = '2';
    EEPROM_Write(ADDR_HEADER_INFO, (uint8_t *)(&(g_accu_system.header)), sizeof(STRUCT_HEADER_INFO));

    g_accu_system.serial.fw_version = FW_VERSION;
    g_accu_system.serial.serial_id[0] = 0x20;
    g_accu_system.serial.serial_id[1] = 0x24;
    g_accu_system.serial.serial_id[2] = 0x11;
    g_accu_system.serial.serial_id[3] = 0x17;
    g_accu_system.serial.serial_id[4] = 0x00;
    g_accu_system.serial.serial_id[5] = 0x00;
    g_accu_system.serial.serial_id[6] = 0x00;
    g_accu_system.serial.serial_id[7] = 0x01;
    EEPROM_Write(ADDR_SERIAL_INFO, (uint8_t *)(&(g_accu_system.serial)), sizeof(STRUCT_SERIAL_INFO));

    // write default exposure condition
    g_accu_system.setting.v_anode_set = 5000;   // 50kV for initial run
    g_accu_system.setting.v_gate_set = 1000;    // 1.0kV
    g_accu_system.setting.i_accu_set = 2000;    // 2.0mA
    g_accu_system.setting.t_pulse_on = 50;      // 50msec
    g_accu_system.setting.t_pulse_off = 1500;   // 1.5sec
    g_accu_system.setting.n_repeat = 1;         // single pulse
    EEPROM_Write(ADDR_EXPOSURE_SETTINGS, (uint8_t *)(&(g_accu_system.setting)), sizeof(STRUCT_EXPOSURE_SETTINGS));

    // write default error thresholds
    g_accu_system.threshold.n_error_cycle = 4;
    g_accu_system.threshold.v_margin = 10;       // 10%
    g_accu_system.threshold.i_margin = 10;       // 10%
    g_accu_system.threshold.v_anode_max = 8500;  // 85kV
    g_accu_system.threshold.i_anode_max = 10000; // 10A
    g_accu_system.threshold.v_gate_max = 4400;   // 4.4kV
    g_accu_system.threshold.i_gate_max = 1000;   // 1.0mA
    g_accu_system.threshold.v_accu_max = 300;    // 300V
    g_accu_system.threshold.i_accu_max = 2500;   // 2.5mA
    EEPROM_Write(ADDR_ERROR_THRESHOLDS, (uint8_t *)(&(g_accu_system.threshold)), sizeof(STRUCT_ERROR_THRESHOLDS));

    // write default control parameters
    // write default gate control parameters
    g_accu_system.gate.f_sample = 50000;   // not used
    g_accu_system.gate.p0 = 11;            // tuned with 1:90 transformer, 2025-04-24
    g_accu_system.gate.p1 = 8000;          // tuned with 1:90 transformer, 2025-04-24
    g_accu_system.gate.p2 = 20000;         // tuned with 1:90 transformer, 2025-04-24
    g_accu_system.gate.z1 = 43;            // tuned with 1:90 transformer, 2025-04-24
    g_accu_system.gate.z2 = 4000;          // tuned with 1:90 transformer, 2025-04-24
    g_accu_system.gate.pwm_period = 3999;  // not used (automatically set to anode period/frequency)
    g_accu_system.gate.pwm_min = 0;        // not used
    g_accu_system.gate.pwm_max = 2500;     // not used (automatically set to 1/2 of period)
    EEPROM_Write(ADDR_GATE_CONTROL_VARS, (uint8_t *)(&(g_accu_system.gate)), sizeof(STRUCT_CONTROL_VARS));

    // write default anode control parameters, to be used with buck
    g_accu_system.anode.f_sample = 50000;   // sampling frequency is 50kHz, since ADC trigger is generated at every 1 PWM cycles (see PWM initialization routine)
    g_accu_system.anode.p0 = 10;            // not used
    g_accu_system.anode.p1 = 8000;          // not used
    g_accu_system.anode.p2 = 9000;          // not used
    g_accu_system.anode.z1 = 80;            // not used
    g_accu_system.anode.z2 = 7000;          // not used
    g_accu_system.anode.pwm_period = 3999;  // PWM period is 200MHz / 40kHz = 5000 / 50kHz = 4000
    g_accu_system.anode.pwm_min = 0;        // not used
    g_accu_system.anode.pwm_max = 3799;     // not used (automatically set to (period - 1))
    EEPROM_Write(ADDR_ANODE_CONTROL_VARS, (uint8_t *)(&(g_accu_system.anode)), sizeof(STRUCT_CONTROL_VARS));

    g_accu_system.buck.f_sample = 50000;    // not used
    g_accu_system.buck.p0 = 40;             // tuned with lowmax transformer, 2025-06-25
    g_accu_system.buck.p1 = 500;           // tuned with lowmax transformer, 2025-04-24
    g_accu_system.buck.p2 = 1500;           // tuned with lowmax transformer, 2025-04-24
    g_accu_system.buck.z1 = 4;             // tuned with lowmax transformer, 2025-04-24
    g_accu_system.buck.z2 = 400;            // tuned with lowmax transformer, 2025-04-24
    g_accu_system.buck.pwm_period = 999;   // not used (automatically set to 1/4 of anode period)
    g_accu_system.buck.pwm_min = 0;         // not used
    g_accu_system.buck.pwm_max = 949;      // not used (automatically set to (period - 10))
    EEPROM_Write(ADDR_BUCK_CONTROL_VARS, (uint8_t *)(&(g_accu_system.buck)), sizeof(STRUCT_CONTROL_VARS));

    // write default timing options (for test), all units are in msec
    g_accu_system.timing.t_anode_ramp = 100; // 100msec
    g_accu_system.timing.t_anode_hold = 5;   // 5 msec
    g_accu_system.timing.t_gate_ramp = 10;   // 10 msec
    g_accu_system.timing.t_gate_hold = 5;    // data sample from 5msec after gate ramp
    g_accu_system.timing.t_accu_ramp = 0;    // not used; in WeRay2, accu is turned on before gate ramp
    g_accu_system.timing.t_off_hold = 10;    // 10 msec
    g_accu_system.timing.t_busy_hold = 100;  // not used
    EEPROM_Write(ADDR_TIMING_VARS, (uint8_t *)(&(g_accu_system.timing)), sizeof(STRUCT_TIMING_VARS));

    g_accu_system.options.init_eeprom_enable = 0;
    g_accu_system.options.bypass_interlock = 1;    // do not change; not used for WeRay2 users
    g_accu_system.options.bypass_errors = 0;
    g_accu_system.options.aging_mode = 0;          // not used for WeRay2
    g_accu_system.options.remote_mode = 1;         // do not change; for remote setting
    g_accu_system.options.short_pulse_mode = 0;    // not used for WeRay2
    g_accu_system.options.test_mode = 0;           // set 1 for tube gate v search (do not make undercurrent error)
    g_accu_system.options.auto_calibration = 0;
    g_accu_system.options.control_pid = 0;
    g_accu_system.options.control_ip = 0;
    EEPROM_Write(ADDR_SYS_OPTIONS, (uint8_t *)(&(g_accu_system.options)), sizeof(STRUCT_SYS_OPTIONS));

    g_accu_system.cal_param.v_gate_start = 1000;     // 1kV
    g_accu_system.cal_param.v_gate_ramp_rate = 100;  // 100V step from start
    g_accu_system.cal_param.v_gate_max = 4000;       // 4kV
    g_accu_system.cal_param.v_accu_threshold = 30;   // 30V
    g_accu_system.cal_param.v_accu_margin = 80;      // 80V
    g_accu_system.cal_param.v_accu_max = 160;        // 160V
    g_accu_system.cal_param.i_accu_max = 2000;       // not used for WeRay2
    g_accu_system.cal_param.t_cal_pulse = 50;        // not used for WeRay2
    g_accu_system.cal_param.t_cal_interval = 450;    // not used for WeRay2
    EEPROM_Write(ADDR_CAL_PARAMS, (uint8_t *)(&(g_accu_system.cal_param)), sizeof(STRUCT_CAL_PARAMS));

    g_accu_system.cal_result.v_turn_on = 0;  // not used for WeRay2
    g_accu_system.cal_result.v_gate_op = 0;  // not used for WeRay2
    g_accu_system.cal_result.v_gate_max = 0; // not used for WeRay2
    EEPROM_Write(ADDR_CAL_RESULT, (uint8_t *)(&(g_accu_system.cal_result)), sizeof(STRUCT_CAL_RESULT));

    memset(&(g_accu_system.cal_table), 0, 32); // not used for WeRay2
    EEPROM_Write(ADDR_CAL_TABLE, (uint8_t *)(&(g_accu_system.cal_table)), sizeof(STRUCT_CAL_TABLE));

    g_accu_system.seq_opts.accu_on_threshold = 185;  // not used; turn on ACCU when V_ACCU > 10V
    g_accu_system.seq_opts.accu_off_threshold = 124; // turn off ACCU when V_GATE < 200V
    EEPROM_Write(ADDR_SEQ_OPTIONS, (uint8_t *)(&(g_accu_system.seq_opts)), sizeof(STRUCT_SEQUENCE_OPTS));

    g_accu_system.daisy.id = 0;             // not used for WeRay2,
    g_accu_system.daisy.response_delay = 3; // not used for WeRay2
    EEPROM_Write(ADDR_DAISY_PARAMS, (uint8_t *)(&(g_accu_system.daisy)), sizeof(STRUCT_DAISY_PARAM));

    // initialize board parameters
    STRUCT_BOARD_GATE_PARAMS board_gate;
    board_gate.R_VGATE_Load = 10000000L;     // ohm
    board_gate.R_VGATE_Sense = 6800L;        // ohm
    board_gate.R_VACCU_Load = 10000000L;     // ohm
    board_gate.R_VACCU_Sense = 100000L;      // ohm
    board_gate.R_IACCU_Sense = 1000L;        // ohm
    board_gate.R_IGATE_Sense = 20000L;       // mohm
    board_gate.GAIN_IGATE_Sense = 100L;      // V/V
    EEPROM_Write(ADDR_BOARD_GATE_PARAMS, (uint8_t *)(&board_gate), sizeof(STRUCT_BOARD_GATE_PARAMS));

    STRUCT_BOARD_ANODE_PARAMS board_anode;
    board_anode.R_VANODE_Load = 1200000000L; // ohm, max 2.1GOhm (= 2^31 - 1 = 2,147,483,647)
    board_anode.R_VANODE_Sense = 28000L;     // ohm
    board_anode.R_IBUCK_Sense = 20L;         // mohm
    board_anode.R_IBUCK_OFFSET_H = 33000L;   // ohm
    board_anode.R_IBUCK_OFFSET_L = 0L;       // ohm
    board_anode.R_VBUCK_Load = 33000L;       // ohm
    board_anode.R_VBUCK_Sense = 4700L;       // ohm
    board_anode.GAIN_IBUCK_Sense = 100L;     // V/V
    EEPROM_Write(ADDR_BOARD_ANODE_PARAMS, (uint8_t *)(&board_anode), sizeof(STRUCT_BOARD_ANODE_PARAMS));

    // initialize pid parameters
    g_accu_system.gate_pid.div_shift = 12;
    g_accu_system.gate_pid.kp = 4000;
    g_accu_system.gate_pid.kd = 64;
    g_accu_system.gate_pid.ki = 40;
    g_accu_system.gate_pid.pwm_period = g_accu_system.gate.pwm_period;
    g_accu_system.gate_pid.pwm_max = g_accu_system.gate.pwm_max;
    g_accu_system.gate_pid.pwm_min = g_accu_system.gate.pwm_min;
    EEPROM_Write(ADDR_GATE_CONTROL_PID, (uint8_t *)(&g_accu_system.gate_pid), sizeof(STRUCT_CONTROL_PID));

    g_accu_system.anode_pid.div_shift = 14;
    g_accu_system.anode_pid.kp = 5000;
    g_accu_system.anode_pid.kd = 6;
    g_accu_system.anode_pid.ki = 18;
    g_accu_system.anode_pid.pwm_period = g_accu_system.buck.pwm_period;
    g_accu_system.anode_pid.pwm_max = g_accu_system.buck.pwm_max;
    g_accu_system.anode_pid.pwm_min = g_accu_system.buck.pwm_min;
    EEPROM_Write(ADDR_ANODE_CONTROL_PID, (uint8_t *)(&g_accu_system.anode_pid), sizeof(STRUCT_CONTROL_PID));

    // erase exposure results
    memset(&(g_accu_system.result), 0, sizeof(STRUCT_EXPOSURE_RESULTS));
    for(int i = 0; i < N_RESULT_PAGES; i++)
    {
        EEPROM_Write(ADDR_EXPOSURE_RESULTS + i * EEPROM_PAGE_HALF, (uint8_t *)(&(g_accu_system.result)), sizeof(STRUCT_EXPOSURE_RESULTS));
    }
    g_accu_system.result_page = 0;

    // erase error logs
    memset(&(g_accu_system.error_info), 0, sizeof(STRUCT_ERROR_LOG_INFO));
    for(int i = 0; i < N_ERROR_PAGES; i++)
    {
        EEPROM_Write(ADDR_ERROR_INFO + i * EEPROM_PAGE_HALF, (uint8_t *)(&(g_accu_system.error_info)), sizeof(STRUCT_ERROR_LOG_INFO));
    }
    g_accu_system.error_page = 0;

    // init g_weray parameters
    EEPROM_WerayInit();
}

void EEPROM_WerayLoad()
{
    EEPROM_Read(ADDR_WERAY_SYS_SETTINGS, (uint8_t *)(&(g_weray.system)), sizeof(STRUCT_WERAY_SYS_SETTINGS));
    EEPROM_Read(ADDR_WERAY_UI_SETTINGS, (uint8_t *)(&(g_weray.settings)), sizeof(STRUCT_WERAY_UI_SETTINGS));
    EEPROM_Read(ADDR_WERAY_THRESHOLDS, (uint8_t *)(&(g_weray.thresholds)), sizeof(STRUCT_WERAY_THRESHOLDS));
    EEPROM_Read(ADDR_WERAY_LED_PRESETS, (uint8_t *)(&(g_weray.led_presets)), sizeof(STRUCT_WERAY_LED_PRESETS));
    EEPROM_Read(ADDR_WERAY_TIMINGS, (uint8_t *)(&(g_weray.timings)), sizeof(STRUCT_WERAY_TIMINGS));
    EEPROM_Read(ADDR_WERAY_UI_BLINKS, (uint8_t *)(&(g_weray.blinks)), sizeof(STRUCT_WERAY_UI_BLINKS));
    EEPROM_Read(ADDR_WERAY_OPTIONS, (uint8_t *)(&(g_weray.options)), sizeof(STRUCT_WERAY_OPTIONS));

    STRUCT_WERAY_CIRCUIT_PARAMS circuit;
    EEPROM_Read(ADDR_WERAY_CIRCUIT, (uint8_t *)(&(circuit)), sizeof(STRUCT_WERAY_CIRCUIT_PARAMS));
    g_weray.board.R_VBATT_Load = (float)circuit.R_VBATT_Load;
    g_weray.board.R_VBATT_Sense = (float)circuit.R_VBATT_Sense;
    g_weray.board.R_VTEMP_Load = (float)circuit.R_VTEMP_Load;
    g_weray.board.R_VTEMP_TC = (float)circuit.R_VTEMP_TC;
    g_weray.board.INV_TC_FACTOR = 1.0f / (float)circuit.TC_FACTOR;

    // override exposure time
    g_accu_system.setting.t_pulse_on = g_weray.settings.exp_time;
    g_accu_system.setting.t_pulse_off = g_weray.settings.exp_time * (uint32_t)g_weray.system.on_off_duty;
}

void EEPROM_LoadAll()
{
    // read settings and data from EEPROM
    EEPROM_Read(ADDR_HEADER_INFO, (uint8_t *)(&(g_accu_system.header)), sizeof(STRUCT_HEADER_INFO));
    EEPROM_Read(ADDR_SERIAL_INFO, (uint8_t *)(&(g_accu_system.serial)), sizeof(STRUCT_SERIAL_INFO));
    EEPROM_Read(ADDR_EXPOSURE_SETTINGS, (uint8_t *)(&(g_accu_system.setting)), sizeof(STRUCT_EXPOSURE_SETTINGS));
    EEPROM_Read(ADDR_ERROR_THRESHOLDS, (uint8_t *)(&(g_accu_system.threshold)), sizeof(STRUCT_ERROR_THRESHOLDS));
    EEPROM_Read(ADDR_BUCK_CONTROL_VARS, (uint8_t *)(&(g_accu_system.buck)), sizeof(STRUCT_CONTROL_VARS));
    EEPROM_Read(ADDR_ANODE_CONTROL_VARS, (uint8_t *)(&(g_accu_system.anode)), sizeof(STRUCT_CONTROL_VARS));
    EEPROM_Read(ADDR_GATE_CONTROL_VARS, (uint8_t *)(&(g_accu_system.gate)), sizeof(STRUCT_CONTROL_VARS));
    EEPROM_Read(ADDR_TIMING_VARS, (uint8_t *)(&(g_accu_system.timing)), sizeof(STRUCT_TIMING_VARS));
    EEPROM_Read(ADDR_SYS_OPTIONS, (uint8_t *)(&(g_accu_system.options)), sizeof(STRUCT_SYS_OPTIONS));
    EEPROM_Read(ADDR_CAL_PARAMS, (uint8_t *)(&(g_accu_system.cal_param)), sizeof(STRUCT_CAL_PARAMS));
    EEPROM_Read(ADDR_CAL_RESULT, (uint8_t *)(&(g_accu_system.cal_result)), sizeof(STRUCT_CAL_RESULT));
    EEPROM_Read(ADDR_CAL_TABLE, (uint8_t *)(&(g_accu_system.cal_table)), sizeof(STRUCT_CAL_TABLE));
    EEPROM_Read(ADDR_SEQ_OPTIONS, (uint8_t *)(&(g_accu_system.seq_opts)), sizeof(STRUCT_SEQUENCE_OPTS));
    EEPROM_Read(ADDR_DAISY_PARAMS, (uint8_t *)(&(g_accu_system.daisy)), sizeof(STRUCT_DAISY_PARAM));
    EEPROM_Read(ADDR_ANODE_CONTROL_PID, (uint8_t *)(&(g_accu_system.anode_pid)), sizeof(STRUCT_CONTROL_PID));
    EEPROM_Read(ADDR_GATE_CONTROL_PID, (uint8_t *)(&(g_accu_system.gate_pid)), sizeof(STRUCT_CONTROL_PID));

    // read and convert to floating-point numbers; shall be done before unit conversion
    STRUCT_BOARD_GATE_PARAMS board_gate;
    STRUCT_BOARD_ANODE_PARAMS board_anode;
    EEPROM_Read(ADDR_BOARD_GATE_PARAMS, (uint8_t *)(&board_gate), sizeof(STRUCT_BOARD_GATE_PARAMS));
    EEPROM_Read(ADDR_BOARD_ANODE_PARAMS, (uint8_t *)(&board_anode), sizeof(STRUCT_BOARD_ANODE_PARAMS));
    g_accu_system.board.R_VGATE_Load = (float)board_gate.R_VGATE_Load;
    g_accu_system.board.R_VGATE_Sense = (float)board_gate.R_VGATE_Sense;
    g_accu_system.board.R_VACCU_Load = (float)board_gate.R_VACCU_Load;
    g_accu_system.board.R_VACCU_Sense = (float)board_gate.R_VACCU_Sense;
    g_accu_system.board.R_IACCU_Sense = (float)board_gate.R_IACCU_Sense;
    g_accu_system.board.R_IGATE_Sense = (float)board_gate.R_IGATE_Sense;
    g_accu_system.board.GAIN_IGATE_Sense = (float)board_gate.GAIN_IGATE_Sense;
    g_accu_system.board.R_VANODE_Load = (float)board_anode.R_VANODE_Load;
    g_accu_system.board.R_VANODE_Sense = (float)board_anode.R_VANODE_Sense;
    g_accu_system.board.R_IBUCK_Sense = (float)board_anode.R_IBUCK_Sense;
    g_accu_system.board.R_IBUCK_OFFSET_H = (float)board_anode.R_IBUCK_OFFSET_H;
    g_accu_system.board.R_IBUCK_OFFSET_L = (float)board_anode.R_IBUCK_OFFSET_L;
    g_accu_system.board.R_VBUCK_Load = (float)board_anode.R_VBUCK_Load;
    g_accu_system.board.R_VBUCK_Sense = (float)board_anode.R_VBUCK_Sense;
    g_accu_system.board.GAIN_IBUCK_Sense = (float)board_anode.GAIN_IBUCK_Sense;

    // unit conversion for setting values
    g_accu_system.setting.v_anode_set = CONV_V_ANODE_10V_to_LSB(g_accu_system.setting.v_anode_set);
    g_accu_system.setting.v_gate_set = CONV_V_GATE_V_to_LSB(g_accu_system.setting.v_gate_set);
    g_accu_system.setting.i_accu_set = CONV_I_ACCU_uA_to_LSB(g_accu_system.setting.i_accu_set);

    g_accu_system.threshold.v_anode_max = CONV_V_ANODE_10V_to_LSB(g_accu_system.threshold.v_anode_max);
    g_accu_system.threshold.i_anode_max = CONV_I_ANODE_mA_to_LSB(g_accu_system.threshold.i_anode_max);
    g_accu_system.threshold.v_gate_max = CONV_V_GATE_V_to_LSB(g_accu_system.threshold.v_gate_max);
    g_accu_system.threshold.i_gate_max = CONV_I_GATE_uA_to_LSB(g_accu_system.threshold.i_gate_max);
    g_accu_system.threshold.v_accu_max = CONV_V_ACCU_V_to_LSB(g_accu_system.threshold.v_accu_max);
    g_accu_system.threshold.i_accu_max = CONV_I_ACCU_uA_to_LSB(g_accu_system.threshold.i_accu_max);

    g_accu_system.cal_param.v_gate_start = CONV_V_GATE_V_to_LSB(g_accu_system.cal_param.v_gate_start);
    g_accu_system.cal_param.v_gate_ramp_rate = CONV_V_GATE_V_to_LSB(g_accu_system.cal_param.v_gate_ramp_rate);
    g_accu_system.cal_param.v_gate_max = CONV_V_GATE_V_to_LSB(g_accu_system.cal_param.v_gate_max);
    g_accu_system.cal_param.v_accu_threshold = CONV_V_ACCU_V_to_LSB(g_accu_system.cal_param.v_accu_threshold);
    g_accu_system.cal_param.v_accu_margin = CONV_V_ACCU_V_to_LSB(g_accu_system.cal_param.v_accu_margin);
    g_accu_system.cal_param.v_accu_max = CONV_V_ACCU_V_to_LSB(g_accu_system.cal_param.v_accu_max);
    g_accu_system.cal_param.i_accu_max = CONV_I_ACCU_uA_to_LSB(g_accu_system.cal_param.i_accu_max);

    g_accu_system.cal_result.v_turn_on = CONV_V_GATE_V_to_LSB(g_accu_system.cal_result.v_turn_on);
    g_accu_system.cal_result.v_gate_op = CONV_V_GATE_V_to_LSB(g_accu_system.cal_result.v_gate_op);
    g_accu_system.cal_result.v_gate_max = CONV_V_GATE_V_to_LSB(g_accu_system.cal_result.v_gate_max);

    // read exposure result, and set current page to write result
    g_accu_system.result.n_exposure = 0;
    memset(&(g_accu_system.result), 0, sizeof(STRUCT_EXPOSURE_RESULTS));
    STRUCT_EXPOSURE_RESULTS result_read;
    for(int i = 0; i < N_RESULT_PAGES; i++)
    {
        EEPROM_Read(ADDR_EXPOSURE_RESULTS + i * EEPROM_PAGE_HALF, (uint8_t *)(&(result_read)), sizeof(STRUCT_EXPOSURE_RESULTS));
        if(result_read.n_exposure > g_accu_system.result.n_exposure)
        {
            g_accu_system.result_page = i;
            g_accu_system.result.n_exposure = result_read.n_exposure;
            g_accu_system.result.total_exp_time = result_read.total_exp_time;
        }
    }
    g_accu_system.result_page = (g_accu_system.result_page + 1) & RESULT_PAGE_MASK; // set page to write next time
    DATALOG_InitExposureLog();

    // read error info, and initialize current page
    g_accu_system.error_page = 0;
    g_accu_system.error_info.n_error = 0;
    STRUCT_ERROR_LOG_INFO error_read;
    for(int i = 0; i < N_ERROR_PAGES; i++)
    {
        EEPROM_Read(ADDR_ERROR_INFO + i * EEPROM_PAGE_HALF, (uint8_t *)(&(error_read)), sizeof(STRUCT_ERROR_LOG_INFO));
        if(error_read.n_error > g_accu_system.error_info.n_error)
        {
            g_accu_system.error_page = i;
        }
    }
    g_accu_system.error_info.n_error++;
    g_accu_system.error_info.error_code = (uint16_t)SYSTEM_ERROR_NONE;
    g_accu_system.error_page = (g_accu_system.error_page + 1) & ERROR_PAGE_MASK; // set page to write next time

    // load weray parameters
    EEPROM_WerayLoad();

    // store dead time for buck controller (will be used during CONTROL_Initialize())
    CONTROL_SetBuckDeadTime(g_accu_system.buck.pwm_min);

    // update error thresholds
    PROC_ErrorThresholdEvaluation();
}

void EEPROM_CheckAndLoad()
{
    EEPROM_WaitI2C();
    EEPROM_Read(ADDR_HEADER_INFO, (uint8_t *)(&(g_accu_system.header)), sizeof(STRUCT_HEADER_INFO));
    EEPROM_Read(ADDR_SYS_OPTIONS, (uint8_t *)(&(g_accu_system.options)), sizeof(STRUCT_SYS_OPTIONS));

#ifndef DEBUG_EEPROM_INIT
    if((g_accu_system.header.header_string[0] != 'P') || (g_accu_system.options.init_eeprom_enable == 1))
#endif
    {
        // no data in EEPROM, or reset flag set --> initialize
        EEPROM_Init();
    }
    EEPROM_LoadAll();
}


volatile int RTC_SetAddress(uint16_t address)
{
    i2c_wr_buffer[0] = (uint8_t)(address & 0x1F);
    return 1;
}

void RTC_Read(uint16_t address, uint8_t *data, int length)
{
    RTC_SetAddress(address);
    EEPROM_I2C_WriteRead(RTC_DEVICE_ADDRESS, &(i2c_wr_buffer[0]), 1, data, length);
    EEPROM_WaitI2C();
}

void RTC_Write(uint16_t address, uint8_t *data, int length)
{
    RTC_SetAddress(address);
    for(int i = 0; i < length; i++)
    {
        i2c_wr_buffer[i + 1] = data[i];
    }

    EEPROM_I2C_Write(RTC_DEVICE_ADDRESS, &(i2c_wr_buffer[0]), length + 2);
    EEPROM_WaitI2C();
}

void RTC_PrintTime()
{
    RTC_Read(0x04, &(rtc_time[0]), 7);
    int sec = ((rtc_time[0] >> 4) & 0x7) * 10 + (rtc_time[0] & 0xF);
    int min = ((rtc_time[1] >> 4) & 0x7) * 10 + (rtc_time[1] & 0xF);
    int hr = ((rtc_time[2] >> 4) & 0x3) * 10 + (rtc_time[2] & 0xF);
    int day = ((rtc_time[3] >> 4) & 0x3) * 10 + (rtc_time[3] & 0xF);
    int mo = ((rtc_time[5] >> 4) & 0x1) * 10 + (rtc_time[5] & 0xF);
    int yr = ((rtc_time[6] >> 4) & 0xF) * 10 + (rtc_time[6] & 0xF);
    printf("%d,%d,%d,%d,%d,%d\r\n", yr, mo, day, hr, min, sec);
}

uint16_t RTC_GetTimeSpanInDays()
{
    RTC_Read(0x04, &(rtc_time[0]), 7);
    if(rtc_time[6] < 24) return 3650; // battery reset; timespan is negative

    uint16_t year = ((rtc_time[6] >> 4) & 0x0F) * 10 + (rtc_time[6] & 0x0F) - 24;
    uint16_t month = ((rtc_time[5] >> 4) & 0x01) * 10 + (rtc_time[5] & 0x0F) - 1;
    uint16_t day = ((rtc_time[3] >> 4) & 0x03) * 10 + (rtc_time[3] & 0x0F) - 1;
    uint16_t total_time = year * 365 + month * 30 + day;

    return total_time;
}

void RTC_ResetTime()
{
    // reset to 2024-01-01 (monday)
    rtc_time[6] = (2 << 4) + 4;
    rtc_time[5] = 1;
    rtc_time[4] = 1;
    rtc_time[3] = 1;
    rtc_time[2] = 0;
    rtc_time[1] = 0;
    rtc_time[0] = 0;
    RTC_Write(0x04, &(rtc_time[0]), 7);
}
