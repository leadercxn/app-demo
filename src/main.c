#include "stdio.h"
#include "stdint.h"
#include "string.h"

#include "boards.h"
#include "version.h"

#include "letter_handler.h"
#include "trace.h"
#include "app_timer.h"
#include "hk_peripheral.h"

TIMER_DEF(m_test_timer);

void test_timer_handler(void *p_data)
{
    static bool is_led_off = false;

    if(is_led_off)
    {
        g_led_obj.gpio_ops.gpio_output_set(&g_led_obj.gpio_cfg, is_led_off);
        is_led_off = false;
    }
    else
    {
        g_led_obj.gpio_ops.gpio_output_set(&g_led_obj.gpio_cfg, is_led_off);
        is_led_off = true;
    }
}

void exit_irq_cb(exit_cfg_t *p_exit_cfg)
{
  trace_debug("exit_irq_cb\r\n");
}

int main(void)
{
  uint64_t old_systicks = 0;
  uint16_t adc_ch0_value = 0;

  /* init systick */
  g_systick_obj.systick_ops.systick_init(&g_systick_obj.systick_cfg);

  /* init uart */
  trace_init();

  trace_info("\n\r\n\r");
  trace_info("Wellcome to Application\r\n");
  trace_info("Version %s, Build in %s\r\n",FW_VERSION_STR,__DATE__);

  /* init led */
  g_led_obj.gpio_ops.gpio_init(&g_led_obj.gpio_cfg);
  g_led_obj.gpio_ops.gpio_output_set(&g_led_obj.gpio_cfg, 0);

  /* init letter-shell */
  letter_shell_init();

  TIMER_INIT(&g_timer3_object);

  /* exit */
  g_exit4_15_obj.exit_ops.exit_init(&g_exit4_15_obj.exit_cfg);
  g_exit4_15_obj.exit_ops.exit_irq_cb = exit_irq_cb;

  g_adc1_ch0_obj.adc_ops.adc_init(&g_adc1_ch0_obj.adc_cfg);

  TIMER_CREATE(&m_test_timer, false, false, test_timer_handler);
  TIMER_START(m_test_timer, 1000);

  while (1)
  {
    letter_shell_loop_task();
    TIMER_SCHEDULER_LOOP();

    if((g_timer3_object.timer_cfg.ticks - old_systicks) > 1000)
    {
        old_systicks = g_timer3_object.timer_cfg.ticks;

        g_adc1_ch0_obj.adc_ops.adc_value_get(&g_adc1_ch0_obj.adc_cfg, &adc_ch0_value);

        trace_info("adc %u mv\r\n", adc_ch0_value * 3300 / 4095);
    }
  }
}



