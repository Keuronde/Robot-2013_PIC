#include <p18cxxx.h>
#include <pwm.h>
#include "../include/Prop2Moteurs.h"

/** D E F I N E *******************************************************/
#define VITESSE_MIN (unsigned int) 600
#define VITESSE_MAX (unsigned int) 1023


// PWM1 => Gauche
// PWM2 => Droite

// Fonctions privées
int adapteVitesse(int _vitesse);
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
	_vitesse = adapteVitesse(_vitesse);
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
	_vitesse = adapteVitesse(_vitesse);
	SetDCPWM2( ((int)_vitesse));
}

// Supprime la plage pendant laquelle on allimente le moteur sans que celui-ci tourne.
// _vitesse doit être positive
int adapteVitesse(int _vitesse){
	int vitesse;
	if (_vitesse > 0){
		long l_vitesse;
		l_vitesse = (long) _vitesse * (long)(VITESSE_MAX - VITESSE_MIN);
		vitesse = (int) (l_vitesse / (int) 1023) + VITESSE_MIN;
	}else{
		vitesse = (int)0;
	}
	return vitesse;
}

void Stop_G(){
    Vitesse_G((int) 0);
}
void Stop_D(){
    Vitesse_G((int) 0);
}

void Avance_D(){
    M_D_SENS = 0;
}
    
void Recule_D(){
    M_D_SENS = 1;
}

void Avance_G(){
    M_G_SENS = 0;
}
    
void Recule_G(){
    M_G_SENS = 1;
}


