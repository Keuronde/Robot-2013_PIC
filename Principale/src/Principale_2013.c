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
#include "include/Prop2Moteurs.h"
#include "include/i2c_m.h"
#include "include/WMP.h"



/** V A R I A B L E S ********************************************************/
#pragma udata
volatile unsigned char timer; 
volatile int nb3ms;
unsigned char mTimer;



/** P R I V A T E  P R O T O T Y P E S ***************************************/
void Moteur_2013_Init(void);
void MyInterrupt_H(void);
void MyInterrupt_L(void);
char getTimer(void);

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
	
	
	// Compteur de temps : 1 incrément toutes les 3 ms
   	if(PIR1bits.TMR1IF == 1){
		PIR1bits.TMR1IF = 0;
//		WriteTimer0(65535 - 36000); //pour un préscaler de 1 : 12000 = 1ms
									//pour un préscaler de 32 : 375 = 1 ms
		WriteTimer1(65535 - 48000); //pour un préscaler de 1 : 12000 = 1ms
		timer++;
		
		if(timer == 255){
		    nb3ms--; 
		}
		
	}
	
	gestion_i2c();
	
	
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
	long angle;
	long impulsions;
	// Asservissement en angle
	long angle_consigne, angle_erreur;
	int commande_angle;
	
	// Vitesse
	int V_initial = (int)100;

	// Initialisation du robot
	Moteur_2013_Init();
	

	angle_consigne=0;
	Vitesse_D(V_initial);
	Vitesse_G(V_initial);

	while(1){
		while(mTimer == getTimer());
        // Calculer et récupérer l'angle du gyroscope
        mTimer =getTimer();
        
        WMP_calcul(mTimer); // On actualise l'angle
        angle = WMP_get_Angle(); // Récupérer l'angle du gyrosocpe
        
        if (angle > 0){
			LED2 =1;
		}else{
			LED2=0;
		}
		
		// Asservissement
		angle_erreur = angle_consigne - angle;
        commande_angle = (int)(angle_erreur / (int)250);
        if (commande_angle > (int)1023 ){
			commande_angle= (int)1023; // Saturation positive
		}
		if(commande_angle < (int) -1023){
			commande_angle = (int)-1023; // Saturation negative
		}
        
        // Commande
        Vitesse_D( V_initial - commande_angle );
        Vitesse_G( V_initial + commande_angle );
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
	
	// Init LEDs
	TRIS_LED1 = 0; // sortie
	TRIS_LED2 = 0; // sortie
	LED1 = 1; 
	LED2 = 0;
	Delay10KTCYx(0);
	LED1 = 0; 
	LED2 = 0; 
	Delay10KTCYx(0);
	LED1 = 1; 
	LED2 = 0; 
	Delay10KTCYx(0);
	LED1 = 0; 
	LED2 = 0; 
	Delay10KTCYx(0);
	LED1 = 1; 
	LED2 = 0; 
	Delay10KTCYx(0);
	
	// Initialisaiton du moteur
	Prop2Moteurs_init();
	
	// Initialisation de l'odometrie
	//OdometrieInit();
	
	// Initialisation de l'I2C
	init_i2c();
	
	// Initialisation de la base de temps
	T1CON = 0x81;
	PIE1bits.TMR1IE = 1; // activation des interruptions
	
	
	
	// Initialisation du WMP
	Delay10KTCYx(80); // Temps que le WMP soit prêt
	if(WMP_init()){
		LED2 = 1;
		mTimer = getTimer();
		while(WMP_calibration()){           // Tant que la calibration est en cours
			while(mTimer == getTimer());
			mTimer = getTimer();
		}
		// A décommenter pour avoir un WMP stable
		WMP_init_2();
	   
		while(WMP_calibration()){           // Tant que la calibration est en cours
			while(mTimer == getTimer());
			mTimer = getTimer();
		}
	}else{
		while(1){
			LED1 =!LED1;
			Delay10KTCYx(80);
		}
	}
	
	
    
    // A faire à la fin de l'init : 
    WMP_init_timer(getTimer());
	mTimer = getTimer();
	
	LED1 = 0;
	LED2 = 0;

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
char getTimer(void){
    return timer;
}
/** EOF CarteTest.c *************************************************************/
