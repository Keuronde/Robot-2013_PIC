/****************** D E F I N E ***********************************************/
// Pour les moteurs
// Corespondance avec le schéma electrique
// M1 => Moteur gauche
// M2 => Moteur droit
#define TRIS_M_D_SENS   TRISBbits.TRISB3
#define M_D_SENS        LATBbits.LATB2
#define TRIS_M_D_ENABLE TRISCbits.TRISC1

#define TRIS_M_G_SENS   TRISCbits.TRISC0
#define M_G_SENS        LATCbits.LATC0
#define TRIS_M_G_ENABLE TRISCbits.TRISC2




// Pour les DEL
#define TRIS_LED1 TRISBbits.TRISB3
#define TRIS_LED2 TRISBbits.TRISB5

#define LED1 LATBbits.LATB3
#define LED2 LATBbits.LATB5
