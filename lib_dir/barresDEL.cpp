#include "barresDEL.h"
#include "clavier_lib.h"


ActionPorte fermer = ActionPorte::Fermer;
ActionPorte ouvrir = ActionPorte::Ouvrir;

unsigned int etatDesPortes[33] = {};

const unsigned int FERMEE = 1;
const unsigned int OUVERTE = 0;




//======================================================= FONCTIONS  ======================================================

/* Fonction qui fait en sorte que le "Master Reset PIN"  du registre a decalage soit a 1 pour son fonctionnnement*/
///////////////////////////////////////////////////////////////////////////
void activerRegistre()
{
    /* Mise a zero du "Master Reset Pin" --­> logique inversee */
    PORTA |= (1 << PORTA4);
}
///////////////////////////////////////////////////////////////////////////
void activerEntree()
{
    activerRegistre();
    PORTA |= (1 << PORTA3);
}

///////////////////////////////////////////////////////////////////////////
void pousserDEL()
{
    /* On pousse les DELs sur le registre a decalage */
    PORTA |= (1 << PORTA2);
    PORTA &= ~(1 << PORTA2);
}

///////////////////////////////////////////////////////////////////////////
void activerDecalage()
{
    PORTA |= (1 << PORTA4);
    PORTA &= ~(1 << PORTA3);
}

///////////////////////////////////////////////////////////////////////////
/* Fonction qui insere les DEL eteintes pour l'animation */
void decalerRegistre(unsigned int& nDEL)
{
    activerDecalage();

    for (unsigned int i = 0; i < nDEL; i++)
    {
        PORTA |= (1 << PORTA1);
        PORTA &= ~(1 << PORTA1);
    }
}

////////////////////////////////////////////////////////////////////////////
void animerDEL(unsigned int& nDELPorte)
{
    activerEntree();

    for (unsigned int i = 0; i < nDELPorte; i++)
    {
        PORTA |= (1 << PORTA1);
        PORTA &= ~(1 << PORTA1);  
    }   
}

///////////////////////////////////////////////////////////////////////////
void initAffichage()
{
    PORTA &= ~(1 << PORTA4);
    PORTA &= ~(1 << PORTA2);
    PORTA |= (1 << PORTA2);
    PORTA &= ~(1 << PORTA2);
    activerEntree();
}

///////////////////////////////////////////////////////////////////////////
void affichage()
{
    initAffichage();
    unsigned int nDELPorte = 1;
    unsigned int autreDEL = OUVERTE;
    for (int i = 32; i >= 0; i--)
    {
        if (etatDesPortes[i]==FERMEE)
        {
            animerDEL(nDELPorte);
            autreDEL = FERMEE;
        }

        else
        {
            if (autreDEL==FERMEE)
                decalerRegistre(nDELPorte);
        }
            
    }

    pousserDEL();

}

///////////////////////////////////////////////////////////////////////////
void fermerEtats(Porte porte, ActionPorte& action)
{
    
    switch(porte)
    {
        case porteA:
            for (int i = 0; i < 8; i++)
            {
                delay_ms(125);
                if (action == Fermer)
                    etatDesPortes[i]=FERMEE;
                affichage(); 
            }

            break;
        
        case porteB:
            for (int i = 8; i < 16; i++)
            {
                delay_ms(125);
                if (action == Fermer)
                    etatDesPortes[i]=FERMEE;              
                affichage();              
            }

            break;
        
        case porteC:
            for (int i = 16; i < 24; i++)
            {
                delay_ms(125);
                if (action == Fermer)
                    etatDesPortes[i]=FERMEE; 
                affichage();
            }
            
            break;


        case porteD:       
            for (int i = 24; i < 32; i++)
            {
                delay_ms(125);
                if (action == Fermer)
                    etatDesPortes[i]=FERMEE;
                affichage(); 
            }
                        
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
void ouvrirEtats(Porte porte, ActionPorte& action)
{
    unsigned etatA = etatDesPortes[0];
    unsigned etatB = etatDesPortes[8];
    unsigned etatC = etatDesPortes[16];
    unsigned etatD = etatDesPortes[24];

    switch(porte)
    {
        case porteA:
            if (etatA==FERMEE)
            {
                for (int i = 7; i >= 0; i--)
                {
                    delay_ms(125);
                    if (action == Ouvrir)
                    {
                        if (etatDesPortes[i]==FERMEE)
                            etatDesPortes[i]=OUVERTE;
                    }
                        
                    affichage(); 
                }
            }
            break;
        
        case porteB:
            if (etatB==FERMEE)
            {
                for (int i = 15; i >= 8; i--)
                {
                    delay_ms(125);
                    if (action == Ouvrir)
                    {
                        if (etatDesPortes[i]==FERMEE)
                            etatDesPortes[i]=OUVERTE;
                    }
                        
                    affichage();               
                }
            }
            break;
        
        case porteC:
            if (etatC==FERMEE)
            {
                for (int i = 23; i >= 16; i--)
                {
                    delay_ms(125);
                    if (action == Ouvrir)
                    {
                        if (etatDesPortes[i]==FERMEE)
                            etatDesPortes[i]=OUVERTE;
                    }
                        
                    affichage(); 
                }
            }
            break;


        case porteD: 
            if (etatD==FERMEE)
            {      
                for (int i = 31; i >= 24; i--)
                {
                    delay_ms(125);
                    if (action == Ouvrir)
                    {
                        if (etatDesPortes[i]==FERMEE)
                            etatDesPortes[i]=OUVERTE;
                    }   
                    affichage(); 
                }
            }             
            break;
    }
}

///////////////////////////////////////////////////////////////////////////
void fermerPortes(Porte porte)
{
    fermerEtats(porte, fermer);   
}

///////////////////////////////////////////////////////////////////////////
void ouvrirPortes(Porte porte)
{
    ouvrirEtats(porte, ouvrir);    
}

void changerEtatsPorte(const uint8_t& porte, const uint8_t& action)
{
    switch(porte)
    {
        case 'A':
            if (action == FERMEE)
                fermerPortes(Porte::porteA);
            else
                ouvrirPortes(Porte::porteA);
            break;
            
        case 'B':
            if (action == FERMEE)
                fermerPortes(Porte::porteB);
            else
                ouvrirPortes(Porte::porteB);
            break;
            
        case 'C':
            if (action == FERMEE)
                fermerPortes(Porte::porteC);
            else
                ouvrirPortes(Porte::porteC);
            break;
            
        case 'D':
            if (action == FERMEE)
                fermerPortes(Porte::porteD);
            else
                ouvrirPortes(Porte::porteD);
            break;           
    }
}

//========================================================= MAIN  =========================================================//



//int main()
//{
    /*
    setRegisterInput(D);
    setRegisterOutput(A);

    PIND = (1 << PIND2);

    
    fermerPortes(porte_test_B);
    fermerPortes(porte_test_C);
    fermerPortes(porte_test_D);
    ouvrirPortes(porte_test_D);
    ouvrirPortes(porte_test_D);
    ouvrirPortes(porte_test_B);
    ouvrirPortes(porte_test_C);
    fermerPortes(porte_test_B);
    fermerPortes(porte_test_A);
    delay_ms(2000);
    fermerPortes(porte_test_A);
    fermerPortes(porte_test_A);
    */

//}
