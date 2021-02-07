#ifndef CLAVIER_H
#define CLAVIER_H 


#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include "RS232.h"
#include "Tableaux.h"


const uint8_t NB_RANGEES  = 4;
const uint8_t NB_COLONNES = 4;

void LectureClavier(uint8_t tab[], uint8_t nbCaracteres);

#endif
