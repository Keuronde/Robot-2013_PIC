


/** D E F I N E **************************************************************/
// Etat utilisé pour la stratégie
#define E_AVANCE1 0
#define E_AVANCE2 1
#define E_TOURNE_A_DROITE 2
#define E_AVAL 3
#define E_PASSE 4
#define E_RECULE 5
#define E_ATTRAPE 6
#define O_RIEN 1
#define O_PRESENT 0
#define CT_RIEN 0
#define CT_PRESENT 1



// Utilisation des pattes du PIC

// Tirette
#define TRIS_TIRETTE        TRISAbits.TRISA0
#define TIRETTE             PORTAbits.RA0

// Bouton Jaune/Bleu
#define TRIS_JB             TRISAbits.TRISA1
#define JB                  PORTAbits.RA1

// Capteur IR 1
#define TRIS_IR_BALLE_AV    TRISAbits.TRISA5
#define IR_BALLE_AV         PORTAbits.RA5

// Capteur IR 2
#define TRIS_IR_BALLE_AR    TRISCbits.TRISC0
#define IR_BALLE_AR         PORTCbits.RC0

// Capteur Sonic
// La configuration du capteur sonic se fait au lancement de la mesure.
// La définition des pattes se fait dans le fichier CapteurSonic.h

//#define TRIS_SONIC          TRISBbits.TRISB7
//#define SONIC               PORTBbits.RB7

// Capteur IR avant gauche
#define TRIS_IR_AV_G        TRISBbits.TRISB6
#define IR_AV_G             PORTBbits.RB6

// Capteur IR avant droit
#define TRIS_IR_AV_D        TRISBbits.TRISB5
#define IR_AV_D             PORTBbits.RB5

// Contacteur 3 
#define TRIS_CT_AV          TRISBbits.TRISB0
#define CT_AV               LATBbits.LATB0
//#define CT_AV               PORTBbits.RB0

// Contacteur 2 
#define TRIS_CT_AR          TRISBbits.TRISB1
#define CT_AR               LATBbits.LATB1
//#define CT_AR               PORTBbits.RB1

// Contacteur 1 
#define TRIS_CT_BALLE       TRISBbits.TRISB2
//#define CT_BALLE            LATBbits.LATB2
#define CT_BALLE            PORTBbits.RB2 




/** P R I V A T E  P R O T O T Y P E S ***************************************/
void Poivron_Init(void);
void tirette(void);
unsigned char getWrite(void);
unsigned int getGauche(void);
unsigned int getDroite(void);
unsigned int getHaut(void);
unsigned int getBas(void);
unsigned char getContact(void);
void resetContact(void);
void attente(void);
char jaune(void);
