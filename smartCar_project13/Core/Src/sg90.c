#include "sg90.h"
#include "gpio.h"
#include "tim.h"

void initSG90(void)
{
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_4); //������ʱ��4
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 17); //�������Ϊ0��
}

void sgMiddle(void)
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 17); //�������Ϊ90��
}

void sgRight(void)
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 5); //�������Ϊ0��
}

void sgLeft(void)
{
	__HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_4, 25); //�������Ϊ180��
}
