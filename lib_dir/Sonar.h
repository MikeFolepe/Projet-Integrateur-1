#include "PWM.h"
#include "RS232.h"
#include "math.h"
#include "Interruption.h"

#include <stdlib.h>

#include "lcm_so1602dtr_m_fw.h"
#include "customprocs.h"

///  Fonction qui utiliser le timer 0 pour compter le temps du signal d'écho du sonar 
//!\ param duree  duree maximale du signal echo.
void countTimer0(uint8_t duree);

///  Fonction qui permet d'activer le sonar en envoyant un pulse
void triggerPulse();

