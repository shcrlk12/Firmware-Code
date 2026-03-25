/*
 * data_struct.h
 *
 *  Created on: Jan 6, 2026
 *      Author: Owner
 */

#ifndef DATA_STRUCT_H_
#define DATA_STRUCT_H_

#ifdef	__cplusplus
extern "C" {
#endif
#include <stdint.h>
#include <stdbool.h>

struct header_info_t
{
    uint8_t header_string[32];
} __attribute__((packed));
typedef struct header_info_t STRUCT_HEADER_INFO;

struct serial_info_t
{
    uint16_t fw_version;
    uint8_t serial_id[8];
} __attribute__((packed));
typedef struct serial_info_t STRUCT_SERIAL_INFO;

struct exposure_settings_t
{
    uint16_t v_anode_set;
    uint16_t v_gate_set;
    uint16_t i_accu_set;
    uint32_t t_pulse_on;
    uint32_t t_pulse_off;
    uint32_t n_repeat;
} __attribute__((packed));
typedef struct exposure_settings_t STRUCT_EXPOSURE_SETTINGS;

struct exposure_results_t
{
    uint32_t n_exposure;
    uint32_t total_exp_time;
    uint16_t v_buck;
    uint16_t v_anode;
    uint16_t i_anode;
    uint16_t v_gate;
    uint16_t i_gate;
    uint16_t v_accu;
    uint16_t i_accu;
} __attribute__((packed));
typedef struct exposure_results_t STRUCT_EXPOSURE_RESULTS;

struct error_thresholds_t
{
    uint16_t n_error_cycle;
    uint16_t v_margin;
    uint16_t i_margin;
    uint16_t v_anode_max;
    uint16_t i_anode_max;
    uint16_t v_gate_max;
    uint16_t i_gate_max;
    uint16_t v_accu_max;
    uint16_t i_accu_max;
} __attribute__((packed));
typedef struct error_thresholds_t STRUCT_ERROR_THRESHOLDS;

struct control_vars_t
{
    uint32_t f_sample;
    uint32_t p0;
    uint32_t p1;
    uint32_t p2;
    uint32_t z1;
    uint32_t z2;
    uint16_t pwm_period;
    uint16_t pwm_min;
    uint16_t pwm_max;
} __attribute__((packed));
typedef struct control_vars_t STRUCT_CONTROL_VARS;

struct control_pid_vars_t
{
    int32_t div_shift;
    int32_t kp;
    int32_t kd;
    int32_t ki;
    uint16_t pwm_period;
    uint16_t pwm_min;
    uint16_t pwm_max;
} __attribute((packed));
typedef struct control_pid_vars_t STRUCT_CONTROL_PID;

struct timing_vars_t
{
    uint16_t t_anode_ramp;
    uint16_t t_anode_hold;
    uint16_t t_gate_ramp;
    uint16_t t_gate_hold;
    uint16_t t_accu_ramp;
    uint16_t t_off_hold;
    uint16_t t_busy_hold;
} __attribute__((packed));
typedef struct timing_vars_t STRUCT_TIMING_VARS;

struct sequence_opts_t
{
    uint16_t accu_on_threshold;
    uint16_t accu_off_threshold;
} __attribute__((packed));
typedef struct sequence_opts_t STRUCT_SEQUENCE_OPTS;

struct sys_options_t
{
    uint8_t init_eeprom_enable;
    uint8_t bypass_interlock;
    uint8_t bypass_errors;
    uint8_t aging_mode;
    uint8_t remote_mode;
    uint8_t short_pulse_mode;
    uint8_t test_mode;
    uint8_t auto_calibration;
    uint8_t control_pid;
    uint8_t control_ip;
} __attribute__((packed));
typedef struct sys_options_t STRUCT_SYS_OPTIONS;

struct cal_params_t
{
    uint16_t v_gate_start;
    uint16_t v_gate_ramp_rate; // digit/sec
    uint16_t v_gate_max;       // for safety, do not exceed this value when finding turn-on
    uint16_t v_accu_threshold; // threshold to determine turn-on voltage
    uint16_t v_accu_margin;    // margin for accu
    uint16_t v_accu_max;       // max affordable accu voltage, depends on switching MOSFET
    uint16_t i_accu_max;       // max current for tube
    uint16_t t_cal_pulse;
    uint16_t t_cal_interval;
} __attribute__((packed));
typedef struct cal_params_t STRUCT_CAL_PARAMS;

struct cal_result_t
{
    uint16_t v_turn_on;
    uint16_t v_gate_op;
    uint16_t v_gate_max;
} __attribute__((packed));
typedef struct cal_result_t STRUCT_CAL_RESULT;

struct cal_table_t
{
    uint16_t v_gate[16];
} __attribute__((packed));
typedef struct cal_table_t STRUCT_CAL_TABLE;

struct daisy_param_t
{
    uint16_t id;
    uint16_t response_delay;
} __attribute__((packed));
typedef struct daisy_param_t STRUCT_DAISY_PARAM;

struct board_gate_params_t
{
    uint32_t R_VGATE_Load;     // ohm
    uint32_t R_VGATE_Sense;    // ohm
    uint32_t R_VACCU_Load;     // ohm
    uint32_t R_VACCU_Sense;    // ohm
    uint32_t R_IACCU_Sense;    // ohm
    uint32_t R_IGATE_Sense;    // mohm
    uint32_t GAIN_IGATE_Sense; // V/V
} __attribute__((packed));
typedef struct board_gate_params_t STRUCT_BOARD_GATE_PARAMS;

struct board_anode_params_t
{
    uint32_t R_VANODE_Load;    // ohm, max 2GOhm
    uint32_t R_VANODE_Sense;   // ohm
    uint32_t R_IBUCK_Sense;    // mohm
    uint32_t R_IBUCK_OFFSET_H; // ohm
    uint32_t R_IBUCK_OFFSET_L; // ohm
    uint32_t R_VBUCK_Load;     // ohm
    uint32_t R_VBUCK_Sense;    // ohm
    uint32_t GAIN_IBUCK_Sense; // V/V
} __attribute__((packed));
typedef struct board_anode_params_t STRUCT_BOARD_ANODE_PARAMS;

// this stores type-converted parameters, to speed-up calculation without precision loss
struct board_parameters_t
{
    float R_VGATE_Load;     // ohm
    float R_VGATE_Sense;    // ohm
    float R_VACCU_Load;     // ohm
    float R_VACCU_Sense;    // ohm
    float R_IACCU_Sense;    // ohm
    float R_IGATE_Sense;    // mohm
    float GAIN_IGATE_Sense; // V/V
    float R_VANODE_Load;    // ohm, max 2GOhm
    float R_VANODE_Sense;   // ohm
    float R_IBUCK_Sense;    // mohm
    float R_IBUCK_OFFSET_H; // ohm
    float R_IBUCK_OFFSET_L; // ohm
    float R_VBUCK_Load;     // ohm
    float R_VBUCK_Sense;    // ohm
    float GAIN_IBUCK_Sense; // V/V
} __attribute__((packed));
typedef struct board_parameters_t STRUCT_BOARD_PARAMS;

struct result_accumulator_t
{
    uint32_t v_buck;
    uint32_t v_anode;
    uint32_t i_anode;
    uint32_t v_gate;
    uint32_t i_gate;
    uint32_t v_accu;
    uint32_t i_accu;
    uint32_t n_sample;
} __attribute__((packed));
typedef struct result_accumulator_t STRUCT_RESULT_ACCUMULATOR;

struct error_log_info_t
{
    uint16_t error_code;
    uint16_t n_error;
    uint32_t n_exposure;
    uint16_t v_buck;
    uint16_t v_anode;
    uint16_t i_anode;
    uint16_t v_gate;
    uint16_t i_gate;
    uint16_t v_accu;
    uint16_t i_accu;
    uint16_t anode_target;
    uint16_t anode_pwm;
    uint16_t gate_target;
    uint16_t gate_pwm;
    uint16_t dac_output;
} __attribute__((packed));
typedef struct error_log_info_t STRUCT_ERROR_LOG_INFO;

struct aging_settings_t
{
    // actual settings
    uint16_t v_gate_set;
    uint16_t v_gate_previous;
    uint16_t i_accu_set;
    uint32_t t_pulse_on; // 1 count = 0.1ms
    uint32_t t_pulse_off;
    uint32_t n_repeat;
    // error thresholds, for compatiblity with gate HV supply
    uint16_t i_gate_limit;
    uint16_t i_gate_trip;
    uint16_t v_gate_limit;
} __attribute__((packed));
typedef struct aging_settings_t STRUCT_AGING_SETTINGS;

struct test_parameters_t
{
    uint16_t channel;
    uint16_t pwm_period_set;
    uint16_t pwm_dutyset;
    uint16_t anode_target;
    uint16_t gate_target;
    uint16_t accu_target;
    uint16_t duration;
    uint16_t buck_period;
    uint16_t buck_duty;
} __attribute__((packed));
typedef struct test_parameters_t STRUCT_TEST_PARAMETERS;

struct system_flags_t
{
    // system states
    bool system_busy;
    bool system_xon;
    bool system_xon_stabilized;
    bool system_error_occurred;
    bool system_error_reset;
    bool system_init_done;
    bool system_warmup_required;
    bool system_statemachine_run;
    bool system_controlstate_run;
    // for remote operation
    bool trigger_uart_exposure;
    bool trigger_tube_calibration;
    bool trigger_user_stop;
    // operation sequence modes for remote operation
    bool exposure_infinite_pulses;
    bool exposure_continuous;
    bool exposure_pulse_modulation;
    // for local operation, long pulse mode
    bool trigger_gpio_exposure;
    // for local operation, short pulse mode
    bool trigger_gpio_gate_on;
    bool trigger_gpio_accu_on;
    bool trigger_gpio_accu_off;
    // write data flags (processed with lowest priority)
    bool write_result;
    bool write_error;
    bool write_calibration;
    // these flags are for test purpose
    bool trigger_test_pwm;
    bool trigger_test_buck_anode;
    bool trigger_test_dac;
    bool trigger_test_accu;
    bool trigger_test_control;
    // these flags are for aging system with daisy chain
    bool trigger_aging_gate_on;
    bool trigger_aging_gate_off;
    bool trigger_aging_gate_change;
    bool trigger_aging_pulse_start;
    bool trigger_daisy_chain;
    bool trigger_daisy_response;
    bool gate_sweep_start;
    bool gate_sweep_searched;
    // weray flags
    bool weray_passwd_input;
    bool weray_battery_state_monitor;
    bool weray_lcd_contents_update;
    bool weray_lcd_powerstate_update;
    bool weray_sys_health_update;
    bool weray_remote_exposure;
    bool weray_exposure_success;
    bool weray_clear_error;
    bool weray_config_rewrite;
    bool weray_config_init;
    bool weray_write_user_setting;
    bool weray_exit_powersave;
    bool weray_sleep;
};
typedef struct system_flags_t STRUCT_SYSTEM_FLAGS;

struct evalutaed_error_thresholds_t
{
    uint16_t n_error_cycle;
    uint16_t v_gate_min;
    uint16_t v_gate_max;
    uint16_t i_gate_max;
    uint16_t v_accu_max;
    uint16_t i_accu_min;
    uint16_t i_accu_max;
    uint16_t v_anode_max;
    uint16_t v_anode_min;
    uint16_t i_anode_max;
};
typedef struct evalutaed_error_thresholds_t STRUCT_EVAL_ERROR_THRESHOLDS;


struct accu_system_t
{
    // parameters located on EEPROM
    STRUCT_HEADER_INFO header;
    STRUCT_SERIAL_INFO serial;
    STRUCT_EXPOSURE_SETTINGS setting;
    STRUCT_ERROR_THRESHOLDS threshold;
    STRUCT_CONTROL_VARS buck;
    STRUCT_CONTROL_VARS anode;
    STRUCT_CONTROL_VARS gate;
    STRUCT_TIMING_VARS timing;
    STRUCT_SYS_OPTIONS options;
    STRUCT_CAL_PARAMS cal_param;
    STRUCT_CAL_RESULT cal_result;
    STRUCT_CAL_TABLE cal_table;
    STRUCT_SEQUENCE_OPTS seq_opts;
    STRUCT_DAISY_PARAM daisy;
    STRUCT_CONTROL_PID anode_pid;
    STRUCT_CONTROL_PID gate_pid;

    // variables on RAM, result and error info is recorded to EEPROM when required
    int16_t result_page;
    int16_t error_page;
    int16_t error_count;
    STRUCT_EXPOSURE_RESULTS result;
    STRUCT_ERROR_LOG_INFO error_info;
    STRUCT_SYSTEM_FLAGS flags;
    STRUCT_RESULT_ACCUMULATOR accumulator;
    STRUCT_EVAL_ERROR_THRESHOLDS evaluated_threshold;
    STRUCT_AGING_SETTINGS aging;
    STRUCT_TEST_PARAMETERS test_param;
    STRUCT_BOARD_PARAMS board;

    // this is to calculate cumulative operation time
    uint32_t pulse_time_counter_sum;

    // state functions
    // ADC conversion job is called every 1/f_sample (priority 7)
    // system timer job is called every 1ms (priority 2)
    // state machine job is called every 100us (priority 3)
    void (*SystemTimerJob)(uint32_t time_counter);
    void (*StateMachineJob)(uint32_t time_counter);
};
typedef struct accu_system_t STRUCT_ACCU_SYSTEM;

struct weray_ui_settings_t
{
	uint16_t passcode;
	uint16_t exp_time_increment;
    uint16_t exp_time;
	uint8_t menu_sel;
	uint8_t age_sel;
	uint8_t tooth_sel;
} __attribute__((packed));
typedef struct weray_ui_settings_t STRUCT_WERAY_UI_SETTINGS;

struct weray_sys_settings_t
{
	uint16_t min_exposure_time;
	uint16_t max_exposure_time;
	uint16_t on_off_duty;
} __attribute__((packed));
typedef struct weray_sys_settings_t STRUCT_WERAY_SYS_SETTINGS;

struct weray_thresholds_t
{
	uint16_t temp_tank_max;
	uint16_t temp_amb_min;
	uint16_t v_batt_exp_min;
	uint16_t v_batt_idle_min;
	uint16_t v_batt_levels[4];
	uint16_t v_batt_charging[4];
} __attribute__((packed));
typedef struct weray_thresholds_t STRUCT_WERAY_THRESHOLDS;

struct weray_led_presets_t
{
	uint8_t led_set_boot;
	uint8_t led_set_passwd;
	uint8_t led_set_ready;
	uint8_t led_set_powersave;
	uint8_t led_set_sleep;
	uint8_t led_set_exp_wait;
	uint8_t led_set_exposure;
	uint8_t led_set_cooldown;
	uint8_t led_set_error;
	uint8_t led_set_lobatt;
	uint8_t led_set_charge;
    uint8_t led_full_charge;
	uint8_t led_set_tx;
	uint8_t led_set_rx;
	uint8_t led_set_lock;
	uint8_t led_set_config;
} __attribute__((packed));
typedef struct weray_led_presets_t STRUCT_WERAY_LED_PRESETS;

struct weray_ui_timings_t
{
	uint16_t t_chattering;
	uint16_t t_exp_start_wait;
	uint16_t t_long_press_wait;
	uint16_t t_power_save;
	uint16_t t_sleep;
	uint16_t default_exptime[4];
	uint16_t adj_slow_interval;
	uint16_t adj_fast_interval;
	uint16_t t_very_long_press_wait;
	uint16_t t_disp_warning;
	uint16_t t_batt_mon_resume;
    uint16_t t_lr_click_wait;
} __attribute__((packed));
typedef struct weray_ui_timings_t STRUCT_WERAY_TIMINGS;

struct weray_ui_blinks_t
{
	uint16_t t_led_blink_on;
	uint16_t t_led_blink_off;
	uint16_t t_led_fast_blink_on;
	uint16_t t_led_fast_blink_off;
	uint16_t t_lcd_blink_on;
	uint16_t t_lcd_blink_off;
	uint16_t t_lcd_blink_duration;
} __attribute__((packed));
typedef struct weray_ui_blinks_t STRUCT_WERAY_UI_BLINKS;

struct weray_options_t
{
	uint8_t passcode_disable;
	uint8_t powersave_disable;
	uint8_t emitter_activate_enable;
	uint8_t lo_batt_bypass;
	uint8_t demo_mode;
	uint8_t exp_sw_interlock;
	uint8_t interlock_active_low;
} __attribute__((packed));
typedef struct weray_options_t STRUCT_WERAY_OPTIONS;

struct _weray_circuit_params
{
    uint32_t R_VBATT_Load;     // ohm
    uint32_t R_VBATT_Sense;    // ohm
    uint32_t R_VTEMP_Load;     // ohm
    uint32_t R_VTEMP_TC;       // ohm
    uint32_t TC_FACTOR;        // --
} __attribute__((packed));
typedef struct _weray_circuit_params STRUCT_WERAY_CIRCUIT_PARAMS;

struct weray_board_t
{
    float R_VBATT_Load;     // ohm
    float R_VBATT_Sense;    // ohm
    float R_VTEMP_Load;     // ohm
    float R_VTEMP_TC;       // ohm
    float INV_TC_FACTOR;    // --
};
typedef struct weray_board_t STRUCT_WERAY_BOARD;

struct weray_led_t
{
	bool error;
	bool power;
	bool wait;
	bool ready;
	bool exposure;
	bool record;
};
typedef struct weray_led_t STRUCT_WERAY_LED;

struct weray_params_t
{
    STRUCT_WERAY_SYS_SETTINGS system;
    STRUCT_WERAY_UI_SETTINGS settings;
    STRUCT_WERAY_THRESHOLDS thresholds;
    STRUCT_WERAY_LED_PRESETS led_presets;
    STRUCT_WERAY_LED led;
    STRUCT_WERAY_TIMINGS timings;
    STRUCT_WERAY_UI_BLINKS blinks;
    STRUCT_WERAY_OPTIONS options;
    STRUCT_WERAY_BOARD board;
};
typedef struct weray_params_t STRUCT_WERAY_PARAMS;

#ifdef	__cplusplus
}
#endif

#endif /* DATA_STRUCT_H_ */
