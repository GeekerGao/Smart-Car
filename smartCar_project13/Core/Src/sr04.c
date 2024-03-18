#include "sr04.h"
#include "gpio.h"
#include "tim.h"

void TIM2_Delay_us(uint16_t n_us)
{
    /* ʹ�ܶ�ʱ��2���� */
    __HAL_TIM_ENABLE(&htim2);
    __HAL_TIM_SetCounter(&htim2, 0);
    while(__HAL_TIM_GetCounter(&htim2) < ((1 * n_us)-1) );
    /* �رն�ʱ��2���� */
    __HAL_TIM_DISABLE(&htim2);
}

double get_distance(void)
{
		int cnt=0;
		//1. Trig ����Trig�˿�����10us�ĸߵ�ƽ
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_SET);//����
		TIM2_Delay_us(20);
		HAL_GPIO_WritePin(GPIOA, GPIO_PIN_10, GPIO_PIN_RESET);//����

		//2. echo�ɵ͵�ƽ��ת���ߵ�ƽ����ʾ��ʼ���Ͳ�
		//������ȥ����һ�£���ʼ������ʱ��
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_RESET);//�ȴ������ƽ����
		HAL_TIM_Base_Start(&htim2);
		__HAL_TIM_SetCounter(&htim2,0);

		//3. �ɸߵ�ƽ��ת�ص͵�ƽ����ʾ��������
		while(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_11) == GPIO_PIN_SET);//�ȴ������ƽ���
		//����������һ�£����ǿ�ʼֹͣ��ʱ��
		HAL_TIM_Base_Stop(&htim2);

		//4. ������м侭������ʱ��
		cnt = __HAL_TIM_GetCounter(&htim2);

		//5. ���� = �ٶ� ��340m/s��* ʱ��/2������1�α�ʾ1us��
		return (cnt*340/2*0.000001*100); //��λ��cm
}
