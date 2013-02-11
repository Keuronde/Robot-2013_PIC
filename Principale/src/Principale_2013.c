/*********************************************************************
 *
 *      Programme utilisé pour le test du robot.
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
// Compilé avec MCC18, le compilateur C de Microchip pour PIC 18F
#include <p18f2550.h>
#include <timers.h>
#include <delays.h>
#include <stdio.h>
#include "include/moteur_2013.h"
#include "include/Prop2Moteurs.h"
#include "include/serie.h"
#include "include/odometrie.h"



/** V A R I A B L E S ********************************************************/




/** P R I V A T E  P R O T O T Y P E S ***************************************/
void Moteur_2013_Init(void);
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
	// Adapté et modifié par S. KAY
	unsigned char sauv1;
	unsigned char sauv2;

	sauv1 = PRODL;
	sauv2 = PRODH;
	
	
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


void main(void)
{
// Déclaration des variables
	unsigned char donnesSerie[15];
	int vitesse,cmp=0,consigne_vitesse;
	int asser_p, asser_i;
	unsigned int tension;
	long impulsions,consigne;
	donnesSerie[0] = 'B';
	donnesSerie[1] = 'O';
	donnesSerie[2] = 'U';
	donnesSerie[3] = '\r';
	donnesSerie[4] = '\n';

	// Initialisation du robot
	Moteur_2013_Init();

	Vitesse_D((int) -512);
	Vitesse_G((int) -512);

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

void Moteur_2013_Init(){
  // Configuration de la conversion analogique => numérique
	ADCON1 = 0x0E;  // AN0 en analogique
	                // Vref- = Vss
	                // Vref+ = Vdd
	ADCON2 = 0x80;  // Résultats aligné à droite
	ADCON0 = 0x01;  // Acitvation du module de conversion analogique => numérique
	
	
	// Initialisaiton du moteur
	Prop2Moteurs_init();
	
	// Initialisation de l'odometrie
	//OdometrieInit();

}


/******************************************************************************
 * Function:        void LED_1_ON(void)
 *
 * PreCondition:    Robot initialisé
 *
 * Side Effects:    None
 *
 * Overview:        Allume la LED 1.
 *****************************************************************************/
void LED_1_ON(void){
	LED_1 = 0;
}
void LED_1_OFF(void){
	LED_1 = 1;
}

void LED_2_ON(void){
	LED_2 = 0;
}
void LED_2_OFF(void){
	LED_2 = 1;
}

/** EOF CarteTest.c *************************************************************/
