/****************** D E F I N E ***********************************************/
// Pour les moteurs
#define TRIS_M_D_SENS TRISCbits.TRISC7
#define TRIS_M_G_SENS TRISCbits.TRISC6
#define TRIS_M_G_ENABLE TRISCbits.TRISC2
#define TRIS_M_D_ENABLE TRISCbits.TRISC1

#define M_D_SENS LATCbits.LATC7
#define M_G_SENS LATCbits.LATC6

// Pour les DEL
#define TRIS_LED1 TRISBbits.TRISB3
#define TRIS_LED2 TRISBbits.TRISB2

#define LED1 LATBbits.LATB3
#define LED2 LATBbits.LATB2
