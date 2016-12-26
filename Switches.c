#include "tm4c123gh6pm.h"


unsigned long PrevRegMiss = 0; 
unsigned long PrevSpecMiss = 0; 

// Heartbeat to Debugg timer2
void HeartBeat_Init(void){
	//******** Initialize Heartbeat 
	volatile unsigned long  delay;
	SYSCTL_RCGCGPIO_R |= 0x20;
	while((SYSCTL_PRGPIO_R & 0x20) == 0);
	
	GPIO_PORTF_AMSEL_R &= ~0x0E;      
  GPIO_PORTF_PCTL_R &= ~0x0000FFFF; // regular function
  GPIO_PORTF_AFSEL_R &= ~0x0E;   	
	GPIO_PORTF_DIR_R  |= 0x0E;				// PF1, 2, 3 
	GPIO_PORTF_DEN_R  |= 0x0E;				// Enable pins 
}

unsigned char Switch_Fire(void){
	unsigned char j; 
	if(((GPIO_PORTB_DATA_R & 0x10) == 0x10) && (PrevRegMiss == 0) ) {
		j = 1; 
		
	}
	else {

	j = 0; 
	}
 PrevRegMiss = GPIO_PORTB_DATA_R & 0x10; 
	return j; 

}

unsigned char Spec_Fire(void){
unsigned char z; 
if(((GPIO_PORTB_DATA_R & 0x20) == 0x20) && (PrevSpecMiss == 0) ){
z = 1;
}
else{
z = 0; 
}
PrevSpecMiss = GPIO_PORTB_DATA_R & 0x20;
return z; 
}



