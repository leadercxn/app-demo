#include "boards.h"
#include "version.h"


#include "trace.h"
#include "hk_peripheral.h"

int main(void)
{
  trace_init();

  g_led_obj.gpio_ops.gpio_init(&g_led_obj.gpio_cfg);
  g_led_obj.gpio_ops.gpio_output_set(&g_led_obj.gpio_cfg, 1);

  trace_info("loop\r\n");
  trace_debug("debug\r\n");
  while (1)
  {

  }
}
