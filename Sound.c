// Sound.c
// Runs on any computer
// Sound assets based off the original Space Invaders 
// Import these constants into your SpaceInvaders.c for sounds!
// Jonathan Valvano
// November 17, 2014
#include <stdint.h>
#include "Sound.h"
#include "DAC.h"
#include "Timer1.h"
#include <stdint.h>
#include "tm4c123gh6pm.h"
#include "SoundWave.h" 


unsigned long Index = 0;
const unsigned char *Wave;
unsigned long SoundCount = 0;

void (*PeriodicTask)(void);   // user function

// ***************** Timer3_Init ****************
// Activate Timer3 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer3_Init(void(*task)(void), unsigned long period){
  SYSCTL_RCGCTIMER_R |= 0x08;   // 0) activate TIMER3
  PeriodicTask = task;          // user function
  TIMER3_CTL_R = 0x00000000;    // 1) disable TIMER3A during setup
  TIMER3_CFG_R = 0x00000000;    // 2) configure for 32-bit mode
  TIMER3_TAMR_R = 0x00000002;   // 3) configure for periodic mode, default down-count settings
  TIMER3_TAILR_R = period-1;    // 4) reload value
  TIMER3_TAPR_R = 0;            // 5) bus clock resolution
  TIMER3_ICR_R = 0x00000001;    // 6) clear TIMER3A timeout flag
  TIMER3_IMR_R = 0x00000001;    // 7) arm timeout interrupt
  NVIC_PRI8_R = (NVIC_PRI8_R&0x00FFFFFF)|0x80000000; // 8) priority 4
// interrupts enabled in the main program after all devices initialized
// vector number 51, interrupt number 35
  NVIC_EN1_R = 1<<(35-32);      // 9) enable IRQ 35 in NVIC
  TIMER3_CTL_R = 0x00000001;    // 10) enable TIMER3A
}

void Timer3A_Handler(void){
  TIMER3_ICR_R = TIMER_ICR_TATOCINT;// acknowledge TIMER3A timeout
  (*PeriodicTask)();                // execute user task
}


//Periodic function passed to Timer3 
//It determines whether a sound should play or not
void Sound_Play(void){
  if(SoundCount){
    DAC_Out(Wave[Index]>>4);
    Index = Index + 1;
    SoundCount = SoundCount - 1;
  }else{
		DAC_Out(0);
  }
}
void Sound_Init(void){
  DAC_Init();               // initialize simple 4-bit DAC
  Index = 0;
  SoundCount = 0;
}
void SoundOut(const unsigned char *pt, unsigned long count){
  Wave = pt;
  Index = 0;
  SoundCount = count;
}
void Sound_Shoot(void){
  SoundOut(shoot,4080);
}
void Sound_Killed(void){
  SoundOut(invaderkilled,3377);
}
void Sound_Explosion(void){
  SoundOut(explosion,2000);
}
void Sound_InvaderShoot(void){
  SoundOut(invadershoot,1802);
}
