#include <p18cxxx.h>
#include <pwm.h>
#include "../include/Prop2Moteurs.h"

/** D E F I N E *******************************************************/
#define VITESSE_MIN (unsigned int) 510


// PWM1 => Gauche
// PWM2 => Droite

// Fonctions privées
void Avance_G(void);
void Recule_G(void);
void Avance_D(void);
void Recule_D(void);


// Initialisation du Moteur
void Prop2Moteurs_init(void){
    TRIS_M_D_SENS = 0; // Sortie
    TRIS_M_G_SENS = 0; // Sortie
    TRIS_M_D_ENABLE = 0; // Sortie
    TRIS_M_G_ENABLE = 0; // Sortie
    // Ouverture du PWM1
   	OpenPWM1(255);
  	SetDCPWM1(0);
  	// Ouverture du PWM2
   	OpenPWM2(255);
  	SetDCPWM2(0);
  	PR2 = 255;
  	TMR2 = 0x04;
  	// PWM à 11kHz
  	T2CONbits.T2CKPS0 = 1;
	// Stop 
  	Stop_G();
  	Stop_D();
}

void Vitesse_G(int _vitesse){
	if (_vitesse > 0){
		Avance_G();
	}else{
		Recule_G();
		_vitesse = -_vitesse;
	}
	
	if (_vitesse > (int)1023){
		_vitesse = (int)1023;
	}
	SetDCPWM1( ((int)_vitesse));
}

void Vitesse_D(int _vitesse){
	if (_vitesse > 0){
		Avance_D();
	}else{
		Recule_D();
		_vitesse = -_vitesse;
	}
	
	if (_vitesse > (int)1023){
		_vitesse = (int)1023;
	}
	SetDCPWM2( ((int)_vitesse));
}
void Stop_G(){
    Vitesse_G((int) 0);
}
void Stop_D(){
    Vitesse_G((int) 0);
}

void Avance_G(){
    M_D_SENS = 1;
}
    
void Recule_G(){
    M_D_SENS = 0;
}

void Avance_D(){
    M_G_SENS = 1;
}
    
void Recule_D(){
    M_G_SENS = 0;
}


