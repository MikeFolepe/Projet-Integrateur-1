#include "Option2.h"


Porte courrante;
PorteServo current;
ActionPorte actualAction;
double degree;
uint8_t tableauChar[4];
uint8_t SIZE_ATTENDU = 2;

///  Fonction qui permet d'identifier les informations entrees au clavier
//!\ param tab          le tableau qui contient les information sur les portes (A-F) et les états(0,1) ou (0-180)
void identificationPortes(uint8_t tab[]){

    if (tab[0] == 'A')
    {
        courrante = porteA;
    }
    if (tab[0] == 'B')
    {
        courrante = porteB;
    }
    if (tab[0] == 'C')
    {
        courrante = porteC;
    }
    if (tab[0] == 'D')
    {
        courrante = porteD;
    }

    if (tab[1] == 0)
    {
        actualAction = Ouvrir;
    }
    if (tab[1] == 1)
    {
        actualAction = Fermer;
    }

    if (tab[0] == 'E')
    {
        current = E;
    }
    if (tab[0] == 'F')
    {
        current = F;
    }

    degree = tab[1] * 100 + tab[2] * 10 + tab[3];
}


/// Fonction qui permet de vérfier si les entrée au clavier pour l'option 2 est valide
//!\ param tab          le tableau qui contient les information sur les portes (A-F) et les états(0,1) ou (0-180)
bool entreeValideServoPorte(uint8_t tab[]){

    if (tab[0] == 'A' || tab[0] == 'B' || tab[0] == 'C' || tab[0] == 'D')
    {
        if (tab[1] > 1)
        {
            return false;
        }
        return true;
    }

    if (tab[0] == 'E' || tab[0] == 'F')
    {
        if (degree > 180)
        {
            return false;
        }
        return true;
    }
    return false;
}


/// Fonction qui permet de faire ce qui est demandé pour l'option 2 
/// elle utilise les fonctions déclarées ci dessus 
/// elle sera directement appelé dans le main du projet
bool configurerOption2(){

    char message[] = "\n\nVeuillez definir l'etat d'un dispositif\n\n";
    transmissionMessageUSART(message, sizeof(message));
    LectureClavier(tableauChar, SIZE_ATTENDU);
    identificationPortes(tableauChar);


    if(!entreeValideServoPorte(tableauChar))
    {
        return false;
    }

    if(tableauChar[0] == 'E' || tableauChar[0] == 'F'){

        pwmTimer2InitForSErvo(current,degree);
    }

    else{

        changerEtatsPorte(tableauChar[0], tableauChar[1]);
    }
    return true;
}