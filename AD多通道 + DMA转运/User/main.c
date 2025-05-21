#include "stm32f10x.h"
#include "Delay.h"
#include "OLED.h"
#include "ADC.h"

int main(void)
{
    /* 硬件初始化 */
    OLED_Init();
    AD_Init();

    /* 传感器显示标签（光敏/热敏/红外） */
    OLED_ShowString(1, 1, "Lux:    .");  // 光强传感器
    OLED_ShowString(2, 1, "Temp:   .");  // 温度传感器
    OLED_ShowString(3, 1, "IR1:    .");  // 红外传感器1

    while(1) 
    {
        /* 直接读取DMA更新后的数组（无需手动触发） */
        OLED_ShowNum(1, 5, AD_Value[0], 4);  // PA0：光敏传感器
        OLED_ShowNum(2, 5, AD_Value[1], 4);  // PA1：热敏传感器
        OLED_ShowNum(3, 5, AD_Value[2], 4);  // PA2：红外传感器1

//        /* 数据转换（示例公式需根据传感器校准） */
//        float light = sensorData * 100.0f / 4095;  // 光强百分比
//        float temp  = sensorData * 300.0f / 4095;  // 温度量程0-300℃
		
        Delay_ms(50); // 降低刷新频率减少OLED闪烁
    }
}
