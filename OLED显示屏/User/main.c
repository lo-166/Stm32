#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "OLED.h"



int main(void)
{
	OLED_Init();

while(1)
{
	OLED_ShowString(1, 1, "Holle");
}
}
