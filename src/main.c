#include "stdio.h"
#include "string.h"

#include "boards.h"
#include "version.h"

#include "letter_handler.h"
#include "trace.h"
#include "hk_peripheral.h"
#include "nt_handler.h"

int main(void)
{
  uint8_t rx_buf = 0;

  g_systick_obj.systick_ops.systick_init(&g_systick_obj.systick_cfg);

  trace_init();

  trace_info("\n\r\n\r");
  trace_info("Wellcome to Application\r\n");
  trace_info("Version %s, Build in %s\r\n",FW_VERSION_STR,__DATE__);


  g_led_obj.gpio_ops.gpio_init(&g_led_obj.gpio_cfg);
  g_led_obj.gpio_ops.gpio_output_set(&g_led_obj.gpio_cfg, 0);

//  init_nt_shell();

  letter_shell_init();

  trace_info("loop\r\n");
  while (1)
  {
#if 0
    g_led_obj.gpio_ops.gpio_output_set(&g_led_obj.gpio_cfg, 0);
    g_systick_obj.systick_ops.delay_ms(NULL,10);
    g_led_obj.gpio_ops.gpio_output_set(&g_led_obj.gpio_cfg, 1);
    g_systick_obj.systick_ops.delay_ms(NULL,50);
#endif

#if 0
    g_usart_object.usart_ops.usart_read_buffer((char *)&rx_buf,1);
    g_usart_object.usart_ops.usart_write_buffer(&rx_buf, 1);
#endif

#if 0
    ntshell_loop_task();
#endif
  }
}



