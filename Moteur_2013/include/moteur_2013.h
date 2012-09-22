/****************** D E F I N E ***********************************************/
// Pour le moteur
#define TRIS_M_SENS_1 TRISCbits.TRISC0
#define TRIS_M_SENS_2 TRISCbits.TRISC1
#define TRIS_M_ENABLE TRISCbits.TRISC2

#define M_SENS_1 LATCbits.LATC0
#define M_SENS_2 LATCbits.LATC1

// LEDs
#define TRIS_LED_1 TRISBbits.TRISB7
#define TRIS_LED_2 TRISBbits.TRISB6

#define LED_1 LATBbits.LATB7
#define LED_2 LATBbits.LATB6

#define TRIS_LECTURE_SENS TRISBbits.TRISB2
#define LECTURE_SENS PORTBbits.RB2

/***************** P U B L I C   P R O T O T Y P E ****************************/
void LED_1_ON(void);
void LED_1_OFF(void);
void LED_2_ON(void);
void LED_2_OFF(void);

