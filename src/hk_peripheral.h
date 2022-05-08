#ifndef __HK_PERIPHERAL_H
#define __HK_PERIPHERAL_H

#include "usart.h"
#include "gpio.h"
#include "systick.h"
#include "exit.h"
#include "adc.h"
#include "pwm.h"
#include "flash.h"

extern usart_object_t   g_usart_object;
extern gpio_object_t    g_led_obj;
extern systick_object_t g_systick_obj;
extern timer_object_t   g_timer3_object;
extern exit_object_t    g_exit4_15_obj;
extern adc_object_t     g_adc1_ch0_obj;
extern pwm_object_t     g_timer15_ch1_pwm_obj;
extern flash_object_t   g_flash_app_param_obj;

#endif
