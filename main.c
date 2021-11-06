#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
#include "FreeRTOS.h"
#include "task.h"
void GPIO_init(void);
void Red_Task(void);
void Blue_Task(void);

void GPIO_init(){
  SYSCTL_RCGCGPIO_R |= 0x00000020;      //Initialize clock to PORTF
  while((SYSCTL_PRGPIO_R&0x00000020) == 0){}  //safety for clock initialization
  GPIO_PORTF_LOCK_R = 0x4C4F434B;
  GPIO_PORTF_CR_R = 0x0E;       //Enable change to PORTF
  GPIO_PORTF_DIR_R = 0x0E;      //Make led ports as output
  GPIO_PORTF_DEN_R = 0x0E;      // digital enable to pins
}

void Red_Task(){
   while(1){
         GPIO_PORTF_DATA_R^=0x02;
   vTaskDelay(1000/portTICK_PERIOD_MS);
       }
   }
void Blue_Task(){
   while(1){
         GPIO_PORTF_DATA_R^=0x04;
   vTaskDelay(500/portTICK_PERIOD_MS);
       }
   }

int main(void)
{
    GPIO_init();
	xTaskCreate(Red_Task,"BlinkyRed",100,NULL, 1,NULL);
	xTaskCreate(Blue_Task,"BlinkyBlue",100,NULL, 1,NULL);
	vTaskStartScheduler();

}