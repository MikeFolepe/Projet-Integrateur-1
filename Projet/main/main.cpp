#define DEMO_DDR DDRB   // Data Direction Register AVR occupé par l'afficheur.
#define DEMO_PORT PORTB // Port AVR occupé par l'afficheur

#include "Projet.h"

const uint16_t MIN_23H59 = 480; // 23h59 en minutes.

volatile Etat etatPresent = configuration;
volatile double compteurTemps = 0;
volatile uint16_t tempsFinSimulation = MIN_23H59;
volatile bool horlogeContinue = true;
volatile bool interruptionButton = false;

// LCD
void static inline w(void)
{
    cp_wait_ms(2000);
}
LCM disp(&DEMO_DDR, &DEMO_PORT);

// INTERRUPT SONAR
ISR(INT0_vect)
{
    uint8_t time = TCNT0;
    uint8_t distance = (((time * 128) + 128) / 58) / 100;
    if (distance < 2)
    {
        stopTimer();
        horlogeContinue = false;
    }

    if (compteurTemps != tempsFinSimulation)
    {
        horlogeContinue = true;
    }

    EIFR |= (1 << INTF0);
}

// INTERRUPT CLOCK
ISR(TIMER1_COMPA_vect)
{
    compteurTemps += 0.5;
    if (compteurTemps == tempsFinSimulation)
    {
        stopTimer();
        horlogeContinue = false;
        etatPresent = configuration;
    }
}

// INTERRUPT BOUTON
ISR(INT1_vect)

{
    _delay_ms(10);

    stopTimer();
    resetClock();
    horlogeContinue = false;
    interruptionButton = true;
    etatPresent = configuration;

    EIFR |= (1 << INTF1);
}

int main()
{
    DDRA = ~(1 << DDA0);
    DDRB = 0xff;
    DDRC = ~(1 << DDC5);
    DDRD = ~(1 << DDD1 | 1 << DDD2 | 1 << DDD3);

    resetClock();

    intialisationTimer1Interrupt();
    intialisationBoutonInterrupt(BoutonInterrupt::D2);
    intialisationBoutonInterrupt(BoutonInterrupt::D3);

    uint16_t heureDepart = 0;

    Action listeActions[30];
    uint8_t tailleListe = 0;

    Action fileAttenteActions[30];
    uint8_t tailleFileAttente = 0;

    uint8_t nbActionsExecutees = 0;

    uint8_t choixOption[1];

    while (true)
    {
        switch (etatPresent)
        {

        case configuration:
        {
            disp.clear();
            w();
            disp << "Configuration";
            w();
            do
            {

                char option1[] = "\n\n1- Definir l'heure de depart\n";
                transmissionMessageUSART(option1, sizeof(option1));

                char option2[] = "2- Definir l'etat d'un dispositif\n";
                transmissionMessageUSART(option2, sizeof(option2));

                char option3[] = "3- Afficher les actions programmees\n";
                transmissionMessageUSART(option3, sizeof(option3));

                char option4[] = "4- Programmer une action\n";
                transmissionMessageUSART(option4, sizeof(option4));

                char option5[] = "5- Supprimer une action programee\n";
                transmissionMessageUSART(option5, sizeof(option5));

                char option6[] = "6- Demarrer la simulation\n\n";
                transmissionMessageUSART(option6, sizeof(option6));

                LectureClavier(choixOption, sizeof(choixOption));

                switch (choixOption[0])
                {

                case 1:
                {
                    //---------------DEPART CLOCK------------------//

                    resetClock();
                    //------------------CODE OPTION1---------------//
                    affichageMessageInvite();

                    uint8_t tab[4];

                    if (!setClocktime(heureDepart, tab))
                    {
                        messageErreur();
                        break;
                    }
                    tempsFinSimulation = MIN_23H59 + heureDepart;
                    interruptionButton = false;
                    break;
                }

                case 2:
                {
                    if (!configurerOption2())
                    {
                        messageErreur();
                    }
                    break;
                }

                case 3:
                {
                    afficherActions(listeActions, tailleListe);
                    break;
                }

                case 4:
                {
                    if (!ajouterAction(listeActions, tailleListe))
                    {
                        messageErreur();
                    }
                    break;
                }

                case 5:
                {
                    if (!SupprimerAction(listeActions, tailleListe))
                    {
                        messageErreur();
                    }
                    break;
                }

                case 6:
                {
                    etatPresent = simulation;
                    horlogeContinue = true;
                    break;
                }

                default:
                {
                    char erreur[] = "\n\nVeuillez entrer un numero d'option valide [1 - 6]";
                    transmissionMessageUSART(erreur, sizeof(erreur));
                }
                }

            } while (choixOption[0] != 6);

            break;
        }
        case simulation:
        {
            disp.clear();
            w();
            disp << "Simulation";
            w();

            can readValue;
            uint16_t valeur16b;
            uint8_t valeur;
            uint16_t topValue;
            double tension;

            uint16_t a = 0;
            uint16_t time; // format hh:mm (ex : 12:00 -> time = 1200)

            compteurTemps = heureDepart;

            if (interruptionButton) //  Si le bouton poussoir interrompt la simulation, puis on repasse en mode simulation,
            {                       //  on redémarre à partir de l'heure de départ.
                setHeureDepart(heureDepart);
            }

            while (horlogeContinue)
            {

                valeur16b = readValue.lecture(0);
                valeur = valeur16b >> 2;
                tension = (double(valeur * 5) / 255); // 5V == 60 hz   && tension== ?? ?? = 12* tension
                topValue = setvalueOCR1A(tension);

                if (tension == 0)
                {
                    topValue = 15624; // (8000000 / 1* 2 * 256) -1   gestion d'exceptions
                }
                a = TCNT1;
                makeclockOn(ModeTimer::CTC, Prescaler::CLK256, ModeCompare::TOOGLE);
                startTimer1Count(topValue, ChannelOCR1X::CA); // 1h en 1s reeel : 260  // 1min en 1s réel  : 15624
                TCNT1 = a;
                _delay_ms(100);

                triggerPulse();
                countTimer0(255);

                minutesToTimeFormat(compteurTemps, time);

                remplirFileAttente(time, tailleFileAttente, fileAttenteActions, tailleListe, listeActions);

                executerActions(nbActionsExecutees, tailleFileAttente, fileAttenteActions);
            }
            executerActions(nbActionsExecutees, tailleFileAttente, fileAttenteActions);

            //uint16_t compteur = compteurTemps;
            //char temps[10];
            //sprintf(temps, "%d", compteur);
            //compteurTemps = heureDepart;
            //horlogeContinue = true;

            //transmissionMessageUSART(temps, sizeof(temps));

            break;
        }
        }
    }
}