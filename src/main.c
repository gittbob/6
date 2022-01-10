#include <stm32f10x.h>

void LED_GPIO_Config(void);
void Delay_Nms(uint32_t);
void Init_SysTick(void);

int main(int argc, char const *argv[])
{
  SystemInit();
  LED_GPIO_Config();
  Init_SysTick();

  while (1)
  {
    GPIO_SetBits(GPIOB, GPIO_Pin_8);
    Delay_Nms(1000);
    GPIO_ResetBits(GPIOB, GPIO_Pin_8);
    Delay_Nms(1000);
  }
}

//配置LED用到I/O端口
void LED_GPIO_Config(void)
{
  GPIO_InitTypeDef GPIO_InitStucture;
  //使能PC端口时钟
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
  GPIO_InitStucture.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStucture.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStucture.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStucture);
  GPIO_SetBits(GPIOB, GPIO_Pin_8);
}

//初始化滴答定时器
void Init_SysTick(void)
{
  //1ms时基
  if (SysTick_Config(SystemCoreClock/9000))
  {
    //等待SysTick配置成功
    while(1);
  }
}

//1ms延时函数(@8M)72000/8
__IO uint32_t TimingDelay;
void Delay_Nms(__IO uint32_t ntime)
{
  TimingDelay = ntime;
	while (TimingDelay != 0);
}