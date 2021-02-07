#include "Sonar.h"


///  Fonction qui utiliser le timer 0 pour compter le temps du signal d'écho du sonar 
//!\ param duree  duree maximale du signal echo.
void countTimer0(uint8_t duree){

    TCNT0 = 0;
    TCCR0A |= (1 << WGM01); // mode CTC
    TCCR0B |= (1 << CS02) | (0 << CS01) | (1 << CS00);
    OCR0A = duree;

}

///  Fonction qui permet d'activer le sonar en envoyant un pulse de 10 microsecondes
void triggerPulse(){
    PORTC = 1 << PORTC6;
    _delay_us(10); // 10 microsecondes
    PORTC = 0 << PORTC6;
}
