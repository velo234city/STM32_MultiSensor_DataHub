#ifndef DHT11_H
#define DHT11_H

#include "stm32f1xx_hal.h"


typedef struct{

	uint8_t hum_integral;
  uint8_t hum_decimal;
  uint8_t temp_integral;
  uint8_t temp_decimal;
  uint8_t checksum;
} DHT11_DATA;

#define DHT11_OK     0
#define DHT11_ERROR  1

uint8_t DHT11_Read(DHT11_DATA *data);




#endif