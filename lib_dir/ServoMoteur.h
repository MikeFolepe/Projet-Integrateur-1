#include "Sonar.h"

enum PorteServo 
{
    E,
    F
};

///  Fonction qui permet de faire bouger les servomoteurs en utilisant le timer 2
//!\ param porte  la porte du servomoeteur qu'on veut faire bouger(E ou F).
//!\ param degre  le degre d'inclinaison des bras ( 0 a 180)
void pwmTimer2InitForSErvo(PorteServo porte, double degre);