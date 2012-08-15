#include <p18f2550.h>

#define NB_CYLCLE_CALCUL 10

struct {
  unsigned int  compteurCyclePrec;
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
	VarOdometrie.compteurCyclePrec = 0;
	VarOdometrie.indexVitesse = 0;
	for(i=0;i<NB_CYLCLE_CALCUL;i++){
		VarOdometrie.vitesseTab[i] = 0;
	}
	OdometrieCinematique.distance = 0;
}

int OdometrieGetVitesse(void){
	return VarOdometrie.vitesseCycle;
}

long OdometrieGetDeplacement(void){
	return OdometrieCinematique.distance;
}

void OdometrieGestion(void){
	if (INTCONbits.TMR0IF){
		unsigned int compteurActuel;
		
		INTCONbits.TMR0IF =0;

		TMR0H = 0xFE;
		TMR0L = 0x88;
		compteurActuel = TMR1L;
		compteurActuel = compteurActuel | ((unsigned int) TMR1H)<< 8;
		
		// Gestion du rebouclage du compteur
		if (compteurActuel > VarOdometrie.compteurCyclePrec){
			VarOdometrie.vitesseCycle = compteurActuel - VarOdometrie.compteurCyclePrec;
		}else{
			VarOdometrie.vitesseCycle = ((unsigned int)0xFFFF - VarOdometrie.compteurCyclePrec) + compteurActuel + 1;
		}
		VarOdometrie.compteurCyclePrec = compteurActuel;
		
		// Gestion du sens à implémenter
		OdometrieCinematique.distance = OdometrieCinematique.distance + VarOdometrie.vitesseCycle;
		
		
		
	}
}
