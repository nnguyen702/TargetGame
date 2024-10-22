#include "fsl_device_registers.h"

void timer_init() {
SIM_SCGC5 |= SIM_SCGC5_PORTC_MASK; // Port C clock enable. Needed?
SIM_SCGC3 |= SIM_SCGC3_FTM3_MASK;  // FTM3 clock enable
FTM3_MODE = 0x5; // Enable FTM3
FTM3_MOD = 0xFFFF;
FTM3_SC = 0x0E; // System clock / 64

// Port C Pin 10 as FTM3_CH6 (ALT3)
PORTC_PCR10 = 0x300;
}
void delayby1ms(int k) {
FTM3_C6SC = 0x1C; // Output-compare; Set output
FTM3_C6V = FTM3_CNT + 333; // 1 ms
for (int i = 0; i < k; i++) {
while(!(FTM3_C6SC & 0x80));
FTM3_C6SC &= ~(1 << 7);
FTM3_C6V = FTM3_CNT + 333; // 1 ms
}
FTM3_C6SC = 0; // Disable channel
}
enum Timer_States {Wait_Start, START, STOP} Timer_state;
void Tick2() {
	  uint32_t BNT_start,BNT_stop ;
	  uint32_t flag ;
	    switch (Timer_state) {
	      case Wait_Start:
	    	  flag = 0;
	    	  FTM3_C6SC = 0x4;
	    	  for (int i = 0; i < 10; i++) {
	    		  BNT_start=GPIOB_PDIR & 0x04;/*capture and stores bits 2 Port B*/
	    	  }
	        if ( BNT_start) {
	          Timer_state =START;
	        } else {
	          Timer_state = Wait_Start;
	        }
	        break;
	      case START:
	    	  for (int j = 0; j < 10; j++) {
	    	  	    		  BNT_stop = GPIOB_PDIR & 0x08;/*capture and stores bits 3 Port B*/
	    	  	    	  }
	    	  if(BNT_stop)
	    	  {
	    		  Timer_state = Wait_Start;
	    	  }
	    	  else if (flag==1) {
	          Timer_state = STOP;
	        } else {
	          Timer_state = START;
	        }
	        break;
	      case STOP:
	    	  for (int j = 0; j < 10; j++) {
	    		  BNT_stop = GPIOB_PDIR & 0x08;/*capture and stores bits 3 Port B*/
	    	  }
	    	if(BNT_stop){
	        Timer_state = Wait_Start;
	        GPIOD_PDOR = 0x00;
	    	}else{Timer_state = STOP;}
	    }
	    switch (Timer_state) {
	      case Wait_Start:
	    	  GPIOD_PDOR = 0x00;
	        break;
	      case START:
	    	  for (int k = 0; k < 10; k++) {
	    	  	 BNT_stop = GPIOB_PDIR & 0x08;/*capture and stores bits 3 Port B*/
	    	  	  }
	    	  if(!BNT_stop){
	    	  delayby1ms(10000);
	    	  flag = 1;
	    	  } else {
		    	  delayby1ms(0);
		    	  flag = 0;
	    	  }
	        break;
	      case STOP:
	    	  GPIOD_PDOR = 0x01;
	        break;
	      default:
	        break;
	    }
}
int main(void) {

	SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK; /*Enable Port B Clock Gate Control*/
	SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK; /*Enable Port D Clock Gate Control*/

	PORTB_PCR2 = 0x100; /*, configured as Alternative 1 (GPIO)*/
	PORTB_PCR3 = 0x100;
	PORTD_GPCLR = 0x00FF0100; /* Configures Pins 0-7 on Port D to be GPIO */

	GPIOD_PDDR = 0x000000FF; /* Configures Pins 0-7 on Port D to be Output */
	GPIOD_PDOR = 0x00;
	timer_init();
	Timer_state = Wait_Start;
	while(1){
		Tick2();

	}
}
