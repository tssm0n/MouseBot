/*
 *	Header file for the ADC unit - designed for PIC16F876/7
 *  BE CAREFUL WITH ADCON1 - IT HAS TO BE MANUALLY ADJUSTED FOR YOUR HARDWARE
 *  IN THE InitialiseADC ROUTINE.
 */	
 
/*
Freely distributable in this original form.
(c) Feb 2000 Shane Tolmie
(c) KeyGhost, now you can record keystrokes on PC with tiny device
Any questions or comments?  shane@keyghost.com 
Updates to FAQ available from http://www.keyghost.com/htpic
*/

/*

sample C code

InitialiseADC(--Channel--);
 
blah = ReadADC(--Channel--);

*/


#include	<pic.h>				//	Pic CPU header file 
#include 	"delay.h"
#include	"adc.h"
/*--------------------------------------------------------------- 
	Initialising the ADC channels 
	---------------------------------------------------------------*/
void InitialiseADC (void) {
	// TRIS registers must be set before calling this method

/*	if 			(ADC_Channel == 0) 	TRISA0 = 1;
	else if (ADC_Channel == 1) 	TRISA1 = 1;
	else if (ADC_Channel == 2) 	TRISA2 = 1;
	else if	(ADC_Channel == 3) 	TRISA3 = 1;
*/
	/* 	------
		 	Specify all to be analogue inputs, refered to VDD. 
		 	Please refer to Page 118 from PIC manual for other configurations.
 			------	*/
	
	/* Analogue-RA0/RA1/RA3 Digital-RA2/RA5	*/
	//ADCON1	= 0b10000100;	
	ADCON1 = 0;

	ADCON0 = 0b10000000; // set ADFM bit (right justify)
} 

/*--------------------------------------------------------------- 
	Reads the ADC level input on a specified ADC channel.
	Takes in an 10-bit ADC channel number.
	Returns an 10 bit number that signifies this level.
	Approximate sampling time = 76.8us
	---------------------------------------------------------------*/
unsigned int ReadADC(unsigned char ADC_Channel){
	
	volatile unsigned int ADC_VALUE;

	/* Selecting ADC channel */
  ADCON0 |= ((ADC_Channel << 2) + 1);				 /* Enable ADC, Fosc/2 */			

	ADIE	  =	0;									 	 		 	/* Masking the interrupt */
  ADIF 	  = 0;								 /* Resetting the ADC interupt bit */						
	ADRESL	=	0; 						 /* Resetting the ADRES value register */
	ADRESH	=	0; 						 
  DelayMs(10);  /* Add a short delay after the initialization */
 
  GODONE = 1;				  					  		 	/* Staring the ADC process */					
  while(!ADIF) continue;			   /* Wait for conversion complete */ 			

	ADC_VALUE	=	 ADRESL;										/* Getting HSB of CCP1 */
	ADC_VALUE	+= (ADRESH << 8);		 				  /* Getting LSB of CCP1 */

  return (ADC_VALUE);     /* Return the value of the ADC process */
}  
