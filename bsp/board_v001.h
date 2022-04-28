#ifndef BOARD_V100_H__
#define BOARD_V100_H__

#include "hk32f0xx.h"

/* GPIO */
#define LED_PIN                             GPIO_Pin_13
#define LED_PORT                            GPIOC
#define LED_PORT_PERIPH_CLK                 RCC_AHBPeriph_GPIOC

#define KT0646_EN_PIN                       GPIO_Pin_13                 
#define KT0646_EN_GPIO_PORT                 GPIOB                       
#define KT0646_EN_GPIO_CLK                  RCC_AHBPeriph_GPIOB

#define KT0656_EN_PIN                       GPIO_Pin_6
#define KT0656_EN_GPIO_PORT                 GPIOA
#define KT0656_EN_GPIO_CLK                  RCC_AHBPeriph_GPIOA

#define AD22650_EN_PIN                       GPIO_Pin_7
#define AD22650_EN_GPIO_PORT                 GPIOA
#define AD22650_EN_GPIO_CLK                  RCC_AHBPeriph_GPIOA

/* UART */
#define TRACE_UART                          USART1
#define TRACE_UART_CLK                      RCC_APB2Periph_USART1

#define TRACE_UART_TX_PIN                   GPIO_Pin_9
#define TRACE_UART_TX_GPIO_PORT             GPIOA
#define TRACE_UART_TX_GPIO_CLK              RCC_AHBPeriph_GPIOA
#define TRACE_UART_TX_SOURCE                GPIO_PinSource9
#define TRACE_UART_TX_AF                    GPIO_AF_1

#define TRACE_UART_RX_PIN                   GPIO_Pin_10
#define TRACE_UART_RX_GPIO_PORT             GPIOA
#define TRACE_UART_RX_GPIO_CLK              RCC_AHBPeriph_GPIOA
#define TRACE_UART_RX_SOURCE                GPIO_PinSource10
#define TRACE_UART_RX_AF                    GPIO_AF_1

/* TIMER */
#define TIM3_CLK                            RCC_APB1Periph_TIM3
#define TIM3_IRQ                            TIM3_IRQn
    
#define USER_TIMER_CLK                      TIM3_CLK
#define USER_TIMER_IRQ                      TIM3_IRQ
#define USER_TIMER                          TIM3
    
#define USER_TIMER_CH                       TIM_IT_CC1
#define USER_TIMER_FREQ                     1000000     //定时器经分频后获得的频率
#define USER_TIMER_PERIOD                   1000        //定时器溢出计数

/* I2C */
#define VIRT1_SCL_PIN                       GPIO_Pin_12                  /* 模拟I2C-SCL */
#define VIRT1_SCL_GPIO_PORT                 GPIOB                        /* GPIOB */
#define VIRT1_SCL_GPIO_CLK                  RCC_AHBPeriph_GPIOB
#define VIRT1_SDA_PIN                       GPIO_Pin_11                  /* 模拟I2C-SDA */
#define VIRT1_SDA_GPIO_PORT                 GPIOB                        /* GPIOB */
#define VIRT1_SDA_GPIO_CLK                  RCC_AHBPeriph_GPIOB


#define VIRT2_SCL_PIN                       GPIO_Pin_5                   /* 模拟I2C2-SCL */
#define VIRT2_SCL_GPIO_PORT                 GPIOA                        /* GPIOA */
#define VIRT2_SCL_GPIO_CLK                  RCC_AHBPeriph_GPIOA
#define VIRT2_SDA_PIN                       GPIO_Pin_4                   /* 模拟I2C2-SDA */
#define VIRT2_SDA_GPIO_PORT                 GPIOA                        /* GPIOA */
#define VIRT2_SDA_GPIO_CLK                  RCC_AHBPeriph_GPIOA

/* EXIT */
#define EXIT_GPIO_PORT_CLK                  RCC_AHBPeriph_GPIOA
#define EXIT_GPIO_PIN                       GPIO_Pin_8
#define EXIT_GPIO_PORT_RESOURCE             EXTI_PortSourceGPIOA
#define EXIT_GPIO_PIN_RESOURCE              EXTI_PinSource8
#define EXIT_TRIGGER_MODE                   EXTI_Trigger_Falling
#define EXIT_GPIO_PORT                      GPIOA
#define EXIT_LINE                           EXTI_Line8

#endif
