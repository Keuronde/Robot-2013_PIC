#include <p18cxxx.h>
#include <pwm.h>
#include "../include/M_prop.h"

/** D E F I N E *******************************************************/
#define VITESSE_MIN (unsigned int) 510


// Fonctions privées
void _sens(char);

char vitesse;
char sens;

// Initialisation du Moteur
void M_prop_init(void){
    TRIS_M_SENS_1 = 0; // Sortie
    TRIS_M_SENS_2 = 0; // Sortie
    TRIS_M_ENABLE = 0; // Sortie
    // Ouverture du PWM
   	OpenPWM1(255);
	SetDCPWM1(0);
	// Stop 
	Stop();
}

void V_fine(int _vitesse){
	if (_vitesse > 0){
		Avance();
	}else{
		Recule();
		_vitesse = -_vitesse;
	}
	
	if (_vitesse > (int)1023){
		_vitesse = (int)1023;
	}
	
	SetDCPWM1( ((int)_vitesse));
}
void V_lent(){
    SetDCPWM1((int)800);
}
void V_rapide(){
    SetDCPWM1(0x03FF);
}
void V_stop(){
    SetDCPWM1(0x0000);
}
void Stop(){
    M_SENS_1 = 0;
    M_SENS_2 = 0;
    sens = AUCUN;
}
void Avance(){
    _sens(0);
}
    
void Recule(){
    _sens(1);
}

void _sens(char s){
    if(s == 0){
        M_SENS_1 = 0;
        M_SENS_2 = 1;
        sens = AVANT;
    }else{
        M_SENS_1 = 1;
        M_SENS_2 = 0;
        sens = ARRIERE;
    }
}

char get_Sens(void){
    return sens;
}

