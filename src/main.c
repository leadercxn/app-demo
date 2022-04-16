#include "boards.h"
#include "version.h"

#include "letter_handler.h"
#include "trace.h"
#include "hk_peripheral.h"

int main(void)
{
  g_systick_obj.systick_ops.systick_init(&g_systick_obj.systick_cfg);

  trace_init();
//  trace_info("letter init start\r\n");
  letter_shell_init();
//  trace_info("letter init done\r\n");

  g_led_obj.gpio_ops.gpio_init(&g_led_obj.gpio_cfg);

//  trace_info("loop\r\n");
  while (1)
  {
    g_led_obj.gpio_ops.gpio_output_set(&g_led_obj.gpio_cfg, 0);
    g_systick_obj.systick_ops.delay_ms(NULL,10);
    g_led_obj.gpio_ops.gpio_output_set(&g_led_obj.gpio_cfg, 1);
    g_systick_obj.systick_ops.delay_ms(NULL,2000);

//    trace_debug("systick = %u\r\n",hk_systick_get());
  }
}



