#include <p18f2550.h>
#include "include/moteur_2013.h"

#define NB_CYLCLE_CALCUL 10

char flag_odometrie;

struct {
  unsigned int compteurCyclePrec,compteurCycleOppose;
  int vitesseCycle;
  int  vitesseTab[NB_CYLCLE_CALCUL];
  unsigned char indexVitesse;
} VarOdometrie;


struct {
  int vitesse;
  long distance;
} OdometrieCinematique;

void OdometrieInit(void){
	int i;
	
	// Initialisation des timers
	
	// TIMER 0 : Lecture des impulsions
	T0CON = 0xA8; // Lecture 16 bits, pas d'oscillateur,
	              // Synchro, external signal, timer actif
	TMR0H = 0;
	TMR0L = 0;
	
	// TIMER 1 : Toutes les 1 ms
	T1CON = 0xB1;	// Source interne (Fosc/4 : 12 MHz)
					// 12 000 tics requis
					// Timer actif
					// Timer sur 16 bits
					// Prescaler 1/8 
	// overflow - 375*4 = 1500
	TMR1H = 0xFA;
	TMR1L = 0x23;

	// Activation de l'interruption
	PIE1bits.TMR1IE = 1;
	
	// Gestion du sens
	TRIS_LECTURE_SENS = 1;
	if (LECTURE_SENS){
		// sens positif
		INTCON2bits.INTEDG2 = 0; // interruption sur front descendant
	}else{
		// Sens négatif
		INTCON2bits.INTEDG2 = 1; // interruption sur front montant
	}
	INTCON3bits.INT2IP = 1; // Priorité élevée
	INTCON3bits.INT2IE = 1; // Interruption activée
	
	
	VarOdometrie.compteurCyclePrec = 0;
	VarOdometrie.compteurCycleOppose = 0;
	VarOdometrie.indexVitesse = 0;
	for(i=0;i<NB_CYLCLE_CALCUL;i++){
		VarOdometrie.vitesseTab[i] = 0;
	}
	OdometrieCinematique.distance = 0;
	flag_odometrie = 0;
}

int OdometrieGetVitesse(void){
	//return VarOdometrie.vitesseCycle;
	char i;
	int mVitesse=0;
	for(i=0;i<NB_CYLCLE_CALCUL;i++){
		mVitesse += VarOdometrie.vitesseTab[i];
	}
//	return mVitesse;
	return VarOdometrie.vitesseTab[VarOdometrie.indexVitesse];
}

long OdometrieGetDeplacement(void){
	return OdometrieCinematique.distance;
}

void OdometrieGestion(void){
	
	if (INTCON3bits.INT2IF){
		unsigned int compteurActuel;
		INTCON3bits.INT2IF = 0;
		if (LECTURE_SENS){
			// sens positif
			INTCON2bits.INTEDG2 = 0; // interruption sur front descendant
			LED_1_OFF();
			LED_2_ON();
		}else{
			// Sens négatif
			INTCON2bits.INTEDG2 = 1; // interruption sur front montant
			LED_1_ON();
			LED_2_OFF();
		}
		
		compteurActuel = TMR0L;
		compteurActuel = compteurActuel | ((unsigned int) TMR0H)<< 8;
		// compteur à 0
		TMR0H = 0;
		TMR0L = 0;
		
		// Gestion du rebouclage du compteur
		VarOdometrie.compteurCycleOppose = compteurActuel - VarOdometrie.compteurCyclePrec - VarOdometrie.compteurCycleOppose;
		
		
		// compteur à 0
		VarOdometrie.compteurCyclePrec = 0;
		
		
	}
	
	if (PIR1bits.TMR1IF){
		unsigned int compteurActuel;
		
		PIR1bits.TMR1IF =0;

		TMR1H = 0xFA;
		TMR1L = 0x23;
		compteurActuel = TMR0L;
		compteurActuel = compteurActuel | ((unsigned int) TMR0H)<< 8;
		
		
		// Gestion du rebouclage du compteur
		// Inutile de s'en préoccuper, ça marche tout seul ! (avec des unsigned int)
		
		VarOdometrie.vitesseCycle = compteurActuel - VarOdometrie.compteurCyclePrec - VarOdometrie.compteurCycleOppose;
		
		VarOdometrie.compteurCycleOppose = 0;
		VarOdometrie.compteurCyclePrec = compteurActuel;
		
		// Gestion du sens à implémenter
		// Vitesse
		VarOdometrie.indexVitesse++;
		if (VarOdometrie.indexVitesse == NB_CYLCLE_CALCUL){
			VarOdometrie.indexVitesse = 0;
		}
		if (LECTURE_SENS){
			VarOdometrie.vitesseTab[VarOdometrie.indexVitesse] = VarOdometrie.vitesseCycle;
		}else{
			VarOdometrie.vitesseTab[VarOdometrie.indexVitesse] = -VarOdometrie.vitesseCycle;
		}
		// Deplacement
		OdometrieCinematique.distance = OdometrieCinematique.distance + VarOdometrie.vitesseTab[VarOdometrie.indexVitesse];
		
		flag_odometrie = 1;

	}
}

char getOdometrieFlag (void){
	char tmp;
	tmp = flag_odometrie;
	flag_odometrie = 0;
	return tmp;
}
