#include "RS232.h"
#include "PWM.h"
#include "DEL.h"
#include "Moteur.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#define F_CPU 8000000

enum Porte
{
    porteA,
    porteB,
    porteC,
    porteD
};

// Porte porte_test_C = porteC;
// Porte porte_test_B = porteB;
// Porte porte_test_A = porteA;
// Porte porte_test_D = porteD;

enum ActionPorte
{
   Ouvrir,
   Fermer
};






void activerRegistre();

void activerEntree();

void pousserDEL();

void activerDecalage();

void decalerRegistre(unsigned int& nDEL);

void animerDEL(unsigned int& nDELPorte);

void initAffichage();

void affichage();

void fermerEtats(Porte porte, ActionPorte& action);

void ouvrirEtats(Porte porte, ActionPorte& action);

void fermerPortes(Porte porte);

void changerEtatsPorte(const uint8_t& porte,const uint8_t& action);
