#include "WProgram.h"

extern "C" int main(void)
{
#ifdef USING_MAKEFILE
  PORTE_PCR29 = PORT_PCR_MUX(3) | PORT_PCR_DSE;// Set pin mux for TPM0 CH1, high drive strength
  PORTE_PCR31 = PORT_PCR_MUX(3) | PORT_PCR_DSE;// Set pin mux for TPM0 CH1, high drive strength
  FTM0_MOD = 1875;  // Set PWM period to 1/2 System clock
  FTM0_C2SC = FTM_CSC_MSB | FTM_CSC_ELSB;   // Set for edge-aligned PWM
  FTM0_C4SC = FTM_CSC_MSB | FTM_CSC_ELSB;   // Set for edge-aligned PWM
  FTM0_C2V = 1876;
  FTM0_C4V = 1876;
  FTM0_SC |= FTM_SC_PS(7);
  FTM0_SC |= FTM_SC_CLKS(1);

  delay(100);
  FTM0_C4V = 1;
  FTM0_C2V = 500;

  PORTC_PCR1 |= PORT_PCR_MUX(1);
  GPIOC_PDDR |= (1 << 0);


  while(1){
    if(GPIOC_PDIR & (1 << 1))
      usb_keyboard_press(KEY_A, MODIFIERKEY_SHIFT);
  }

#else
	// Arduino's main() function just calls setup() and loop()....
	setup();
	while (1) {
		loop();
		yield();
	}
#endif
}

