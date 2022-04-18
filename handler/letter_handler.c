#include "letter_handler.h"
#include "shell.h"
#include "usart.h"

static Shell shell;
static char shellBuffer[128];


/**
 * @brief 用户shell写
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际写入的数据长度
 */
short userShellWrite(char *data, unsigned short len)
{
    g_usart_object.usart_ops.usart_write_buffer((uint8_t *)data, len);
    return len;
}

/**
 * @brief 用户shell读
 * 
 * @param data 数据
 * @param len 数据长度
 * 
 * @return short 实际读取到
 */
short userShellRead(char *data, unsigned short len)
{
    return g_usart_object.usart_ops.usart_read_buffer((uint8_t *)data, len);
}

Shell get_shell(void)
{
    return shell;
}

void letter_shell_init(void)
{

    shell.write = userShellWrite;
    shell.read = userShellRead;
    shellInit(&shell, shellBuffer, sizeof(shellBuffer));

    shellTask(&shell);

    // while (1)
    // {
    //     usart_get_chars(&m_usart_obj, buff, 10);
    //     usart_put_string(&m_usart_obj, "\n\r");
    //     usart_put_chars(&m_usart_obj, buff, 10);
    // }
    

}


