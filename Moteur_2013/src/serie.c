#include <p18f2550.h>
#include "include/serie.h"


struct envoieSerie{
	unsigned char * donnee;
	unsigned char nbDonnee;
};
volatile struct envoieSerie variableSerie;

/** P R I V A T E   P R O T O T Y P E S *******************************/
void envoieOctet(void);

void SerieGestion(void){
	// Envoi des données
	if (PIR1bits.TXIF == 1 && PIE1bits.TXIE == 1){
		envoieOctet();
		// Si on a tout chargé dans le tampon d'envoi
		// On coupe les interruption
		if (variableSerie.nbDonnee == 0){
			PIE1bits.TXIE = 0;
		}
	}
	
}

void envoieOctet(void){
	TXREG = *(variableSerie.donnee);
	variableSerie.nbDonnee--;
	variableSerie.donnee++;
}


void SerieInit(){
	// Require Global interrupt enable
	INTCONbits.GIE = 1;
	INTCONbits.PEIE = 1;
	
	
	TRISCbits.TRISC6 = 1;
	TRISCbits.TRISC7 = 1;
	// Envoie par block de 8 bits
	// Asynchrone
	// BRGH à 1
	TXSTA = 0x04;
	// BRG16 à 1
	BAUDCON = 0x08;
	
	// Baud rate generator
	// 115 200 kb/s
	SPBRGH = 0;
	SPBRG = 103;
	
	// Activation du port série
	RCSTAbits.SPEN = 1;
	// Activation des envois
	TXSTAbits.TXEN = 1;
	
	variableSerie.nbDonnee = 0;
}

char SerieEnvoieDonnee(unsigned char * _donnee, char _nbDonnee){
	if (variableSerie.nbDonnee == 0){
		variableSerie.donnee = _donnee;
		variableSerie.nbDonnee = _nbDonnee;
		// Activation des interrutpions pour les envois
		PIE1bits.TXIE =1;
		
	}else{
		// return erreur
	}
}
