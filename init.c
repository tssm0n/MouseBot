#include <htc.h>

/* Program device configuration word
 * Oscillator = Internal RC No Clock
 * Watchdog Timer = Off
 * Power Up Timer = Off
 * Master Clear Enable = External
 * Code Protect = Off
 * Data EE Read Protect = Off
 * Brown Out Detect = BOD and SBOREN disabled
 * Internal External Switch Over Mode = Enabled
 * Monitor Clock Fail-safe = Enabled
 */
__CONFIG(INTIO & WDTDIS & PWRTDIS & MCLREN & UNPROTECT & UNPROTECT & BORDIS & IESOEN & FCMEN);

// Peripheral initialization function
void init(void){
	/***** Common Code ****
	 *  Portbit7:4 interrupt-on-change disabled
	 *  Peripheral interrupts not enabled
	 *  Global interrupt disabled during initialization
	 */
	INTCON	= 0b00000000;
	/*
	 *  Weak pullup on PORT disabled
	 */
	OPTION	= 0b10000000;
	
	/***** 16F690 Code ****
	 *  Internal oscillator set to 4MHz
	 */
	OSCCON	= 0b01100000;
	
	/***** PortA Code ****
	 *  Port directions: 1=input, 0=output
	 */
	TRISA	= 0b00000000;
	
	ei();	// Global interrupts enabled
	
}
