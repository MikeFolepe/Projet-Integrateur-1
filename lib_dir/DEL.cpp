/*
 * Fichier .cpp contenant l'implementation des fonctions decrites dans 
 * le fichier DEL.h
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



#include "DEL.h"



///  Fonction qui permet d'allumer une DEL avec une couleur: verte, rouge
///  ou ambre sur une broche d'un port.
//!\ param port  une catégorie de port.
//!\ param position1 le premier  indice de  broche pour l'écriture.
//!\ param position2 le deuxieme indice de  broche pour l'écriture.
//!\ param couleur  la couleur de DEL désirée.
void allumerDEL(volatile uint8_t& port, uint8_t position1, uint8_t  position2, Couleur couleur)
{   

    switch(couleur) 
    {

        case VERT:  setSortiePort(port, position1);
        break;

        case ROUGE: setSortiePort(port, position2);
        break;
        
        case AMBRE: setSortiePort(port, position1);
            _delay_ms(5);
            setSortiePort(port, position2);
            _delay_ms(5);
        break;
      
    }
}

