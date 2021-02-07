
/*
 * Fichier .cpp contenant l'implementation des fonctions decrites dans 
 * le fichier RS232.h
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
 
#include "RS232.h"


///  Fonction qui permet de lire à partir de la mémoire EEPROM selon un intervalle d'adresses
//!\ param debut    L'adresse dont on commence la lecture.
//!\ param fin      L'adresse dont on finit la lecture.
//!\ return message Le tableau de char contenant le message lue de la mémoire.
uint8_t* lectureEeprom(uint8_t debut, uint8_t fin)
{
    uint8_t message[fin - debut];

    unsigned int adresse = debut;
    uint8_t i = 0;
    uint8_t byteLue;

    while(byteLue != 0xFF || adresse == fin)
    {
        byteLue = eeprom_read_byte((uint8_t*)adresse);

        if(byteLue == 0xFF)   // Vérifie si byteLue est égal 0xFF avant de le transmettre pour éviter d'afficher le char end of line.
        {
            break;
        }
        message[i] = byteLue;
        i++;
        adresse++;
    }
    uint8_t *messagePtr = message;
    return messagePtr;
}

///  Fonction qui permet d'écrire dans la mémoire EEPROM à partir d'une adresse.
//!\ param message       Tableau contenant les char à écrire.
//!\ param tailleTableau La taille du tableau contenant le message.
//!\ param debut         L'adresse dont on commence l'écriture.
void ecritureEeprom(char message[], uint8_t tailleTableau, uint8_t debut)
{
    unsigned int adresse = debut;
    for(uint8_t i = 0; i < tailleTableau; i++)
    {
        eeprom_write_byte((uint8_t*)adresse, message[i]);
        adresse++;
    }
}

///  Fonction qui permet d'initialiser les registres de l'USART, utilise les fonctions
///  setParity, setStopBit et setBitSize.
//!\ param parity   La parité utilisée par l'USART : disable, even ou odd.
//!\ param stopBit  Le nombre de stop bits utilisés.
//!\ param bitSize  Le nombre de bits transmis par l'USART.
void initialisationUSART(Parity parity, uint8_t stopBit, uint8_t bitSize)
{
    
    UBRR0H = 0;
    UBRR0L = 0xCF;  // 2400 bauds

    // registres permettant la réception et la transmission par le USART0

    UCSR0A = 0;
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);

    setParity(parity);
    setStopBit(stopBit);
    setBitSize(bitSize);
}

///  Fonction qui permet d'initialiser les registres de parité de l'USART.
//!\ param parity   La parité utilisé par l'USART : disable, even ou odd.
void setParity(Parity parity)
{
    switch(parity)
    {

        case DISABLED : UCSR0C |= (0 << UPM01 | 0 << UPM00);
        break;   

        case EVEN : UCSR0C |= (1 << UPM01 | 0 << UPM00);
        break;   

        case ODD : UCSR0C |= (1 << UPM01 | 1 << UPM00);
        break;
    }
}

///  Fonction qui permet d'initialiser les registres de stop bits de l'USART.
//!\ param stopBit  Le nombre de stop bits utilisé, 1 ou 2.

void setStopBit(uint8_t stopBit)
{
    switch(stopBit){

        case 1: UCSR0C |= (0 << USBS0);
        break;

        case 2: UCSR0C |= (1 << USBS0);
        break;
    }
}

///  Fonction qui permet d'initialiser les registres du nombre de bits transmis de l'USART.
//!\ param bitSize Le nombre de bits transmis par l'USART.( chifffres entre 5 et 8)
void setBitSize(uint8_t bitSize)
{
    switch(bitSize){

        case 5: UCSR0C |= (0 << UCSZ02 | 0 << UCSZ01 | 0 << UCSZ00);
        break;

        case 6: UCSR0C |= (0 << UCSZ02 | 0 << UCSZ01 | 1 << UCSZ00);
        break;

        case 7: UCSR0C |= (0 << UCSZ02 | 1 << UCSZ01 | 0 << UCSZ00);
        break;

        case 8: UCSR0C |= (0 << UCSZ02 | 1 << UCSZ01 | 1 << UCSZ00);
        break;

        case 9: UCSR0C |= (1 << UCSZ02 | 1 << UCSZ01 | 1 << UCSZ00);
        break;
    }
}

///  Fonction qui permet de transmettre par le port RS232 un octet.
//!\ param donnee  L'octet à transmettre.
void transmissionUSART(char donnee)
{
    /* Wait for empty transmit buffer */
    while ( !( UCSR0A & (1<<UDRE0)) );

    /* Put data into buffer, sends the data */
    UDR0 = donnee;
}

///  Fonction qui permet de transmettre par le port RS232 un tableau d'octets.
//!\ param message  Le tableau contenant les octets à transmettre.
//!\ tailleTableau  Le nombre d'octets que le tableau contient.
void transmissionMessageUSART(char message[], uint8_t tailleTableau)
{
    for(uint8_t i = 0; i < tailleTableau; i++)
    {
        transmissionUSART(message[i]);
    }
}
uint8_t receptionUSART( void )
{
    /* Wait for data to be received */
    while ( !(UCSR0A & (1<<RXC0)) );
    /* Get and return received data from buffer */
    return UDR0;
}

