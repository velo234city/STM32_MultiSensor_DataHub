#include "dht11.h"
#include "gpio.h"

#define DHT11_PORT     GPIOB
#define DHT11_PIN        GPIO_PIN_0

extern TIM_HandleTypeDef htim2;

static void delay_us(uint16_t us){
	
	 __HAL_TIM_SET_COUNTER(&htim2,0);
   while(__HAL_TIM_GET_COUNTER(&htim2)<us);
}

uint8_t DHT11_Read(DHT11_DATA *data){
  uint8_t bits[5]={0};
	uint8_t i,j;
	
	
	//First a signal is sent by pulling low for 18ms
	HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_RESET);
  HAL_Delay(18);
	HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_SET);
	delay_us(20);
	
	
	//set the pin as input
	GPIO_InitTypeDef gpio={0};
	gpio.Pin=DHT11_PIN;
	gpio.Mode=GPIO_MODE_INPUT;
	gpio.Pull=GPIO_NOPULL;
	HAL_GPIO_Init(DHT11_PORT,&gpio);
	
	//wait for DHT response (low 80us, then high 80us)
	if (HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN) != GPIO_PIN_RESET){
	
		//No response
		goto error;
	}
	
	while (HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN) == GPIO_PIN_RESET);// wait for high
	while (HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN) == GPIO_PIN_SET);// wait for low
		
	// Read 40 bits
	for(j=0;j<5;j++){
	  for(i=0;i<8;i++){
    
     while(HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN) == GPIO_PIN_RESET);// wait for low bit to start
     delay_us(30);//if still high after 30us, it is a 1.
     
     if(HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN) ==	GPIO_PIN_SET){
		    
		    bits[j]|=(1<<(7-i));//MSB first 
			 
		 }	

     while (HAL_GPIO_ReadPin(DHT11_PORT,DHT11_PIN) == GPIO_PIN_SET); // wait for end of bit		 
		
  }
}
	
  // set the pin back to output high for the next start
  gpio.Mode=GPIO_MODE_OUTPUT_PP;
  gpio.Pull=GPIO_NOPULL;
  gpio.Speed=GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(DHT11_PORT,&gpio);
  HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_SET);

 //verify checksum
 if(bits[0]+bits[1]+bits[2]+bits[3]==bits[4]){
  
	  data->hum_integral=bits[0];
	  data->hum_decimal=bits[1];
	  data->temp_integral=bits[2];
	  data->temp_decimal=bits[3];
	  data->checksum=bits[4];
	  return DHT11_OK;
 }
	 error: 
	 // set pin back to output high even on error
	 gpio.Mode=GPIO_MODE_OUTPUT_PP;
	 gpio.Pull=GPIO_NOPULL;
	 gpio.Speed=GPIO_SPEED_FREQ_LOW;
   HAL_GPIO_Init(DHT11_PORT,&gpio);
   HAL_GPIO_WritePin(DHT11_PORT,DHT11_PIN,GPIO_PIN_SET);
   return DHT11_ERROR;
 }