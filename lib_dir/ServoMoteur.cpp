
#include "ServoMoteur.h"
double MAX_ANGLE = 180.0;
double AJOUT_TEMPS_MAX = 0.05; // Nécessité de rajouter un petit temps en front montant pour l'inclinaison a 180 degre
double PERIODE = 8.25;         // 1/frequence , frequence avec prescaler de 256 egale a 122.07
double PWMMAXIMAL = 255;       // la valeur de compte maximal du timer 0 = (2 exposant 8)-1


///  Fonction qui permet de faire bouger les servomoteurs en utilisant le timer 2
//!\ param porte  la porte du servomoeteur qu'on veut faire bouger(E ou F).
//!\ param degre  le degre d'inclinaison des bras ( 0 a 180)
void pwmTimer2InitForSErvo(PorteServo porte, double degre)
{

    double timeOn = 0;
    TCCR2A |= (1 << WGM21) | (1 << WGM20);
    TCCR2B |= (0 << WGM22);
    TCCR2B |= (1 << CS22) | (1 << CS21) | (0 << CS20);

    if (degre == MAX_ANGLE)
    {
        timeOn = ((double)(degre / MAX_ANGLE)) + 1 + AJOUT_TEMPS_MAX;
    }
    else
    {
        timeOn = ((double)(degre / MAX_ANGLE)) + 1;
    }

    double frequence = ((double)(timeOn / PERIODE)) * 100;
    double count = (frequence * PWMMAXIMAL) / 100;
    switch (porte)
    {
    case E:
        TCCR2A |= (1 << COM2A1) | (0 << COM2A0);
        OCR2A = count;
        break;
    case F:
        TCCR2A |= (1 << COM2B1) | (0 << COM2B0);
        OCR2B = count;
        break;
    }
}