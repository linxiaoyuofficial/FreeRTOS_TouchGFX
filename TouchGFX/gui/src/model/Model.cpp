#include <gui/model/Model.hpp>
#include <gui/model/ModelListener.hpp>

#include <stdio.h>
#include "led.h"

Model::Model() : modelListener(0)
{

}

void Model::tick()
{

}

void Model::m_BSP_LED_on()
{
	printf("LED_ON\n");
	LED1_ON;
}

void Model::m_BSP_LED_off()
{
	printf("LED_OFF\n");
	LED1_OFF;
}
