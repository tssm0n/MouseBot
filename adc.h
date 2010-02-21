#ifndef ADC_H_
#define ADC_H_

/*
 *	Header file for the ADC unit
 */	

extern void InitialiseADC (void); 
/*--------------------------------------------------------------- 
	Initialising the ADC channels 
	---------------------------------------------------------------*/


extern unsigned int ReadADC(unsigned char ADC_Channel);
/*--------------------------------------------------------------- 
	Reads the ADC level input on a specified ADC channel.
	Takes in an 10-bit ADC channel number.
	Returns an 10 bit number that signifies this level.
	Approximate sampling time = 76.8us
	---------------------------------------------------------------*/



#endif /*ADC_H_*/
