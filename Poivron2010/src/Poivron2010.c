/*********************************************************************
 *
 *      Programme utilis� pour le test du robot.
 *
 *********************************************************************
 * FileName:        Poivron.c
 * Dependencies:    See INCLUDES section below
 * Processor:       PIC18
 * Compiler:        C18 2.30.01+
 * Company:         Microchip Technology, Inc.
 *
 * Author               Date        Comment
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Samuel Kay         09/08/09    Original.
 * Samuel Kay         26/11/11    Add some comments.
 ********************************************************************/

/** I N C L U D E S **********************************************************/
// Compil� avec MCC18, le compilateur C de Microchip pour PIC 18F
#include <p18f2550.h>
#include <timers.h>
#include <delays.h>
#include <stdio.h>
#include "include/Poivron2010.h"
#include "include/serie.h"



/** V A R I A B L E S ********************************************************/
#pragma udata



/** P R I V A T E  P R O T O T Y P E S ***************************************/
void MyInterrupt_H(void);
void MyInterrupt_L(void);

/** V E C T O R  R E M A P P I N G *******************************************/

extern void _startup (void);        // See c018i.c in your C18 compiler dir
#pragma code _RESET_INTERRUPT_VECTOR = 0x000800
void _reset (void)
{
    _asm goto _startup _endasm
}
#pragma code

#pragma code _HIGH_INTERRUPT_VECTOR = 0x000808
void _high_ISR (void)
{
    MyInterrupt_H();
}

#pragma code _LOW_INTERRUPT_VECTOR = 0x000818
void _low_ISR (void)
{
    MyInterrupt_L();
}
#pragma code


#pragma interrupt MyInterrupt_H
void MyInterrupt_H(void){
	// code de "Rustre Corner"
	// Adapt� et modifi� par S. KAY
	unsigned char sauv1;
	unsigned char sauv2;

	sauv1 = PRODL;
	sauv2 = PRODH;
	
	SerieGestion();


	PRODL = sauv1;
	PRODH = sauv2;		

}
#pragma interruptlow MyInterrupt_L
void MyInterrupt_L(void){
	unsigned char sauv1;
	unsigned char sauv2;

	sauv1 = PRODL;
	sauv2 = PRODH;


	PRODL = sauv1;
	PRODH = sauv2;	
}

/** D E C L A R A T I O N S **************************************************/
#pragma code
/******************************************************************************
 * Function:        void main(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Main program entry point.
 *
 * Note:            None
 *****************************************************************************/
/** L E D ***********************************************************/

/** S W I T C H *****************************************************/

void main(void)
{
// D�claration des variables
	char estJaune,etat,ok;
	unsigned int impulsions, impulsions_tmp,vitesse,i;
	unsigned char donnesSerie[12];
	donnesSerie[0] = 'B';
	donnesSerie[1] = 'O';
	donnesSerie[2] = 'U';
	donnesSerie[3] = '\r';
	donnesSerie[4] = '\n';


	impulsions =0;
// Pas de patte en analogique
    

// Initialisation du robot
	Poivron_Init();
	SerieInit();



  // 
	i=0;
	while(1){
		Delay100TCYx(120); // Pause 10 ms
		vitesse = TMR1L;
		vitesse = vitesse | ((unsigned int) TMR1H)<< 8;
		if (vitesse > 0){ // contournement bug silicon ?
			TMR1H = 0;
			TMR1L = 0;
		}
		
		impulsions = impulsions + vitesse;
		impulsions_tmp = impulsions_tmp + vitesse;
		sprintf((char*)donnesSerie,"%3d %6d\r\n",vitesse,impulsions);
		SerieEnvoieDonnee(donnesSerie, 12);
		
		if (impulsions_tmp > 200){
			impulsions_tmp = 0;
			CT_AR = !CT_AR;
		}

	}



	while(1){
	}	

	

}//end main

/******************************************************************************
 * Function:        void Poivron_Init(void)
 *
 * PreCondition:    None
 *
 * Input:           None
 *
 * Output:          None
 *
 * Side Effects:    None
 *
 * Overview:        Initialise le robot.
 *
 * Note:            None
 *****************************************************************************/

void Poivron_Init(){
  ADCON1 |= 0x0F; // Default all pins to digital

	TRIS_CT_AR = 0; // LED en sorite
	
  // Initialisation du Timer1
	T1CON = 0x87; // Lecture 16 bits, pas d'oscillateur,
	              // Synchro, external signal, timer actif

}

/** EOF CarteTest.c *************************************************************/
