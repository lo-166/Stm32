#ifndef __LED_H
#define __LED_H

void LED_Init(void);
void LEDn_set_IO(int y , GPIO_TypeDef* x, uint16_t GPIO_Pin_X);
void LED1_Ture(void);
void LED3_Ture(void);
#endif
