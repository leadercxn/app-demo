#include "string.h"
#include "stdbool.h"

#include "nt_handler.h"
#include "ntshell.h"
#include "ntlibc.h"
#include "usart.h"

static ntshell_t ntshell;

static int func_read(char *buf, int cnt, void *extobj)
{
    return g_usart_object.usart_ops.usart_read_buffer((uint8_t *)buf, cnt);
}

static int func_write(const char *buf, int cnt, void *extobj)
{
    int i = 0;
    for (i = 0; i < cnt; i++)
    {
        g_usart_object.usart_ops.usart_write((uint8_t)buf[i]);
    }

    return cnt;
}


static int func_callback(const char *text, void *extobj)
{
    if (ntlibc_strlen(text) > 0) {
        g_usart_object.usart_ops.usart_put_string("User input text:'");
        g_usart_object.usart_ops.usart_put_string(text);
        g_usart_object.usart_ops.usart_put_string("'\r\n");
    }
    return 0;
}

void init_nt_shell(void)
{
    ntshell_init(
        &ntshell,
        func_read,
        func_write,
        func_callback,
        (void *)&ntshell);

    ntshell_set_prompt(&ntshell, "App>");
}

void ntshell_loop_task(void)
{
    static bool first_use = false;
    if(!first_use)
    {
        func_write("App>", strlen("App>"), NULL);
        first_use = true;
    }
    ntshell_execute_async(&ntshell);
}
