/*
 * Fichier .cpp contenant l'implementation des fonctions decrites dans 
 * le fichier Timer1.h
 * 
 * Ecole Polytechnique de Montreal
 * Departement de genie informatique et genie logiciel
 * Cours : inf1900
 *
 * Etienne Chevalier-Tittley, Paul-Marie Akoffodji,
 * Mike-Davy Folepe, Jean-Marc Ndong Ékouaga
 * 
 * Date : 2020-11-03
 *
 * Code qui n'est sous aucune license.
 *
 */
 



#include "Timer1.h"


/// Fonction qui permet de reinitialiser la valeur du compteur TCNT1 à 0 
void resetCounter1()
{
    TCNT1 = 0;
}

/// Fonction qui permet d'arrềter le compteur
void stopTimer()
{
    TCCR1B=0;
}


///  Fonction qui permet d'ajuster le prescaler du timer 1 en utilisant le registre TCCR1B 
//!\ param prescaler  un type enum contenant les différents prescalers qu'on veut pour le timer
void setPrescaler(Prescaler prescaler)
{
    
    switch(prescaler){

        case CLK8: TCCR1B = (1<<CS11);
        break;
        case CLK64:TCCR1B = (1<<CS11)|(1<<CS10);
        break;
        case CLK256: TCCR1B = (1<<CS12);
        break;
        case CLK1024: TCCR1B = (1<<CS12)|(1<<CS10);
        break;

    }

}

///  Fonction qui permet d'ajuster le mode du timer (WaveFormGeneration Mode)
///  parmi trois modes (CTC, PWM Phase correct 8 bit, Fast PWM 8 bit)
///  en utilisant les registres TTCR1B et TCCR1A
//!\ param mode  un type enum contenant les différentrs mode qu'on veut pour le timer
void ajustementModeTimer1(ModeTimer mode)
{
    
    switch(mode)
    {
        case CTC: TCCR1B |= 1 << WGM12;
        break;
        case PHASECORRECT8: TCCR1A |=(1 << WGM10);
        break;
        case FASTPWM8 :TCCR1A |=(1 << WGM10); 
            TCCR1B |= (1<<WGM12);
        break;

    }

}

///  Fonction qui permet d'ajuster le mode de sortie (CompareOutputMOde)
///  sur les sorties OC1A et OC1B (set ou clear) des pins D4 et D5 
///  dépendamment du Waveform Generation mode actuel du timer1
//!\ param mode   un type enum contenant les différentrs mode que l'on veut pour le timer
//!\ param modeC  un type enum contenant les différentrs 
//!\ modes que l'on veut pour les sorties OC1A et OC1B
void compareOutputMode(ModeTimer mode, ModeCompare modeC)
{

    switch(mode)
    {
        
        case CTC: if(modeC==ModeCompare::SET)
        {

            TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0);
        }
        else if(modeC==ModeCompare::CLEAR)
        {

            TCCR1A |= (1 << COM1A1) | (1 << COM1B1)|(0<<COM1A0)|(0<<COM1B0);
        }


        else if(modeC==ModeCompare::NUL){

            TCCR1A |= (0 << COM1A1) | (0 << COM1B1)|(0<<COM1A0)|(0<<COM1B0);
        }
        else if(modeC==ModeCompare::TOOGLE){

            TCCR1A |= (0 << COM1A1) | (1 << COM1A0) | (0 << COM1B1) | (1 << COM1B0); 
        }

        break;

        case PHASECORRECT8: if(modeC==ModeCompare::SET)
        {

            TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0);

        }
        else if (modeC==ModeCompare::CLEAR)
        {

            TCCR1A |= (1 << COM1A1) | (1 << COM1B1)|(0<<COM1A0)|(0<<COM1B0);

        }
        break;
        case FASTPWM8: if(modeC==ModeCompare::SET)
        {

            TCCR1A |= (1 << COM1A1) | (1 << COM1A0) | (1 << COM1B1) | (1 << COM1B0);

        }
        else if (modeC==ModeCompare::CLEAR)
        {

            TCCR1A |= (1 << COM1A1) | (1 << COM1B1)|(0<<COM1A0)|(0<<COM1B0);


        }
        break;

    }


}

///  Fonction qui permet de demarrer la minuterie et d'ajuster
///  la valeur maximale du comptage (OCR1A et OCR1B)
//!\ param time  le temps qu'on veut compter
//!\ param channel , le channel qu'on veut utiliser ,
//!\ CA , CB ou CAB pour les deux.(OCR1A, OCR1B)
void startTimer1Count(uint16_t time, ChannelOCR1X channel)
{

    resetCounter1();

    switch (channel)
    {
        case CA:OCR1A=time;
        break;
        case CB:OCR1B=time;
        break;
        case CAB:OCR1A=time;
            OCR1B=time;
        break;
        
    }
}


