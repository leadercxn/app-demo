#include "boards.h"


#include "usart.h"
#include "hk_usart.h"
#include "gpio.h"
#include "hk_gpio.h"



#include "hk_peripheral.h"

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

// 串口obj赋值
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
#endif
  }
};

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






