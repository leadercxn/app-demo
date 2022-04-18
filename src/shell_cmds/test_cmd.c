#include "stdio.h"
#include "string.h"
#include "boards.h"

#include "trace.h"
#include "shell.h"


int test_cmd(int argc, char *agrv[])
{
    printf("%d parameter(s)\r\n", argc);
    for (uint8_t i = 0; i < argc; i++)
    {
        printf("agrv[%d] = %s\r\n", i ,agrv[i]);
    }
	//最后必须要加上换行,以避免与shell内置返回打印重叠
	printf("\r\n");

    return 0;
}

SHELL_EXPORT_CMD(SHELL_CMD_PERMISSION(0)|SHELL_CMD_TYPE(SHELL_TYPE_CMD_MAIN), test, test_cmd, just test cmd);