#include "boards.h"


#include "usart.h"
#include "hk_usart.h"
#include "gpio.h"
#include "hk_gpio.h"
#include "systick.h"
#include "hk_systick.h"
#include "timer.h"
#include "hk_timer.h"
#include "exit.h"
#include "hk_exit.h"
#include "adc.h"
#include "hk_adc.h"
#include "pwm.h"
#include "hk_pwm.h"
#include "flash.h"
#include "hk_flash.h"

#include "hk_peripheral.h"

// 串口obj赋值s
hk_uart_info_t g_hk_uart_info = {
    .uart = USART1,
    .tx_port = TRACE_UART_TX_GPIO_PORT,
    .rx_port = TRACE_UART_RX_GPIO_PORT,

    .clk = TRACE_UART_CLK,
    .tx_clk = TRACE_UART_TX_GPIO_CLK,
    .rx_clk = TRACE_UART_RX_GPIO_CLK,

    .tx_pin = TRACE_UART_TX_PIN,
    .rx_pin = TRACE_UART_RX_PIN,

    .tx_pin_source = TRACE_UART_TX_SOURCE,
    .rx_pin_source = TRACE_UART_RX_SOURCE,

    .tx_af = TRACE_UART_TX_AF,
    .rx_af = TRACE_UART_RX_AF,
};

hk_uart_config_t g_hk_uart_config = {
    .baudrate = 115200,
    .databits = USART_WordLength_8b,
    .stopbit = USART_StopBits_1,
    .parity = USART_Parity_No,
    .hwfc = USART_HardwareFlowControl_None,
    .mode = USART_Mode_Rx | USART_Mode_Tx,
    .interrupt_priority = 0,
};

usart_object_t g_usart_object = {
  .usart_cfg = {
      .p_pin_cfg = (void *)&g_hk_uart_info,
      .p_usart_cfg = (void *)&g_hk_uart_config,
  },

  .usart_ops = {
      .usart_init = hk_uart_obj_init,
#if defined(__CC_ARM) || defined(__ICCARM__)    //armcc
      .usart_put = hk_uart_obj_put,
#elif defined(__GNUC__)   
      .usart_write = hk_uart_obj_put,
      .usart_read = hk_uart_obj_get,
      .usart_write_buffer = hk_uart_obj_puts,
      .usart_read_buffer  = hk_uart_obj_gets,
      .usart_put_string = hk_uart_obj_putstring,
#endif
  }
};


// led obj
gpio_object_t g_led_obj = {
    .gpio_cfg = {
        .gpio_clk = RCC_AHBPeriph_GPIOC,
        .p_port = (void *)LED_PORT,
        .gpio_pin = LED_PIN,
        .gpio_dir = GPIO_DIR_OUTPUR,
    },

    .gpio_ops = {
        .gpio_init = hk_gpio_obj_init,
        .gpio_output_set = hk_gpio_obj_out_set,
    },
};

// systick
systick_object_t g_systick_obj = {
    .systick_cfg = {
        .clk_div = SysTick_CLKSource_HCLK_Div8,
        .ticks_per_us = 9,
        .ticks_per_sec = 1,
    },

    .systick_ops = {
        .systick_init = hk_systick_init_rebuild,
        .delay_ms = hk_delay_ms_rebuild,
        .delay_us = hk_delay_us_rebuild,
        .systick_get = hk_systick_get,
    },
};

timer_object_t g_timer3_object = {
    .timer_cfg = {
        .period = 1000,             //计数到 1K 时溢出
        .prescaler_freq = 1000000,  //分频后得到 1M 时钟
        .ticks = 0,
        .timer = TIM3,
    },
    .timer_ops = {
        .timer_init = hk_timer3_init,
        .timer_start = hk_timer3_start,
        .timer_stop = hk_timer3_stop,
        .timer_irq_enable = hk_timer3_irq_enable,
        .timer_irq_disable = hk_timer3_irq_disable,
    }
};

hk_exit_pin_cfg g_hk_exit_pin8_cfg = {
    .exit_pin_port = EXIT_GPIO_PORT,
    .exit_pin = EXIT_GPIO_PIN,
    .exit_pin_port_clk = EXIT_GPIO_PORT_CLK,
    .exit_pin_port_source = EXIT_GPIO_PORT_RESOURCE,
    .exit_pin_source = EXIT_GPIO_PIN_RESOURCE,
};

hk_exit_cfg g_hk_exit8_cfg = {
    .exit_line = EXIT_LINE,
    .exit_trigger = EXIT_TRIGGER_MODE,
};

exit_object_t g_exit4_15_obj = {
    .exit_cfg.p_exit_cfg = (void *)&g_hk_exit8_cfg,
    .exit_cfg.p_pin_cfg = (void *)&g_hk_exit_pin8_cfg,

    .exit_ops.exit_init = hk_exit4_15_init,
    .exit_ops.exit_enable = hk_exit4_15_enable,
    .exit_ops.exit_disable = hk_exit4_15_disable,
};

hk_adc_pin_cfg g_hk_adc1_ch0_pin_cfg = {
    .adc_pin_port_clk = ADC_GPIO_PORT_CLK,
    .adc_pin_port = ADC_GPIO_PORT,
    .adc_pin = ADC_GPIO_PIN_0,
};

hk_adc_cfg g_hk_adc1_cfg = {
    .adc_continuous_mode = DISABLE,
    .adc_data_align = ADC_DataAlign_Right,
    .adc_resolution = ADC_Resolution_12b,
    .adc_trigger = ADC_ExternalTrigConvEdge_None,
    .adc_scan_dir = ADC_ScanDirection_Upward,
};

adc_object_t  g_adc1_ch0_obj = {
    .adc_cfg.p_pin_cfg = (void *) &g_hk_adc1_ch0_pin_cfg,
    .adc_cfg.p_adc_cfg = (void *) &g_hk_adc1_cfg,

    .adc_cfg.channel = ADC_CHANNEL_0,
    .adc_ops.adc_init = hk_adc1_init,
    .adc_ops.adc_enable = hk_adc1_enable,
    .adc_ops.adc_disable = hk_adc1_disable,
    .adc_ops.adc_value_get = hk_adc_value_get,
};

hk_pwm_pin_cfg g_hk_timer15_ch1_pwm_pin_cfg = {
    .pwm_pin = PWM_CH1_PIN,
    .pwm_pin_port = PWM_CH1_GPIO_PORT,
    .pwm_pin_port_clk = PWM_CH1_GPIO_CLK,
    .pwm_pin_source = PWM_CH1_PIN_SOURCE,
    .pwm_pin_af = PWM_CH1_AF,
};

hk_pwm_cfg g_hk_timer15_ch1_pwm_cfg = {
    .duty_cycle = 90,
    .freq = 38500,  //38k
    .output_polarity = TIM_OCPolarity_Low,
    .output_n_polarity = TIM_OCNPolarity_High,
};

pwm_object_t g_timer15_ch1_pwm_obj = {
    .pwm_cfg.p_pin_cfg = (void *) &g_hk_timer15_ch1_pwm_pin_cfg,
    .pwm_cfg.p_pwm_cfg = (void *) &g_hk_timer15_ch1_pwm_cfg,

    .pwm_ops.pwm_init = hk_timer15_ch1_pwm_init,
    .pwm_ops.pwm_enable = hk_timer15_ch1_pwm_enable,
    .pwm_ops.pwm_disable = hk_timer15_ch1_pwm_disable,
};

flash_object_t g_flash_app_param_obj = {
    .flash_cfg.flash_start_addr = FLASH_APP_PARAM_SAVE_ADDR,
    .flash_cfg.flash_max_size = FLASH_PAGE_SIZE,
    .flash_cfg.flash_page_size = FLASH_APP_PARAM_LEN_MAX,

    .flash_ops.flash_write = hk_flash_write,
    .flash_ops.flash_read = hk_flash_read,
};

