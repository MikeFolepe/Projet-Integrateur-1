/*
 *Fichier d'en-tête contenant les signatures des fonctions ququi vont nous permettre 
 * d’utiliser les ressources de l’EEPROM interne ainsi qu’utiliser l’USART pour permettre la 
 *transmission par le port RS232
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



#ifndef RS232_H
#define RS232_H

#define F_CPU 8000000
#include <avr/io.h>
#include <util/delay.h>
#include <avr/eeprom.h>


enum Parity
{
    DISABLED,
    EVEN,
    ODD,
};


///  Fonction qui permet de lire à partir de la mémoire EEPROM selon un intervalle d'adresses
//!\ param debut    L'adresse dont on commence la lecture.
//!\ param fin      L'adresse dont on finit la lecture.
//!\ return message Le tableau de char contenant le message lue de la mémoire.
uint8_t* lectureEeprom(uint8_t debut, uint8_t fin);

///  Fonction qui permet d'écrire dans la mémoire EEPROM à partir d'une adresse.
//!\ param message       Tableau contenant les char à écrire.
//!\ param tailleTableau La taille du tableau contenant le message.
//!\ param debut         L'adresse dont on commence l'écriture.
void ecritureEeprom(char message[],uint8_t tailleTabeau, uint8_t debut);

///  Fonction qui permet d'initialiser les registres de l'USART, utilise les fonctions
///  setParity, setStopBit et setBitSize.
//!\ param parity   La parité utilisée par l'USART : disable, even ou odd.
//!\ param stopBit  Le nombre de stop bits utilisé.
//!\ param bitSize  Le nombre de bits transmis par l'USART.
void initialisationUSART(Parity parity, uint8_t stopBit, uint8_t bitSize);

///  Fonction qui permet d'initialiser les registres de parité de l'USART.
//!\ param parity   La parité utilisé par l'USART : disable, even ou odd.
void setParity(Parity parity);

///  Fonction qui permet d'initialiser les registres de stop bits de l'USART.
//!\ param stopBit  Le nombre de stop bits utilisé, 1 ou 2.
void setStopBit(uint8_t stopBit);

///  Fonction qui permet d'initialiser les registres du nombre de bits transmis de l'USART.
//!\ param bitSize Le nombre de bits transmis par l'USART.
void setBitSize(uint8_t bitSize);

///  Fonction qui permet de transmettre par le port RS232 un octet.
//!\ param donnee  L'octet à transmettre.
void transmissionUSART(char donnee);

///  Fonction qui permet de transmettre par le port RS232 un tableau d'octets.
//!\ param message  Le tableau contenant les octets à transmettre.
//!\ tailleTableau  Le nombre d'octets que le tableau contient.
void transmissionMessageUSART(char message[], uint8_t tailleTableau);

uint8_t receptionUSART( void );
#endif
