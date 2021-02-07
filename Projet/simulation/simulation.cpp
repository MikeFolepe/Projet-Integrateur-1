

#include "Horloge.h"
#include "Interruption.h"
#include "can.h"
#include "RS232.h"
#include "clavier_lib.h"
#include "Sonar.h"
#include "Option2.h"
#include <stdio.h>

#define DEMO_DDR DDRB   // Data Direction Register AVR occupé par l'afficheur.
#define DEMO_PORT PORTB // Port AVR occupé par l'afficheur

void static inline w(void)
{
  cp_wait_ms(2000);
}
LCM disp(&DEMO_DDR, &DEMO_PORT);

volatile double compteurTemps = 0;
volatile bool horlogeContinue = true;

ISR(TIMER1_COMPA_vect)
{
  compteurTemps += 0.5;
  if (compteurTemps == 1439)
  {
    stopTimer();
    horlogeContinue = false;
  }
}

ISR(INT1_vect)
{
  stopTimer();
  EIFR |= (1 << INTF1);
}

ISR(INT0_vect)
{
  uint8_t time = TCNT0;
  uint8_t distance = (((time * 128) + 128) / 58) / 100;
  if (distance < 2)
  {
    stopTimer();
    horlogeContinue = false;
  }

  if (compteurTemps != 1439)
  {
    horlogeContinue = true;
  }

  EIFR |= (1 << INTF0);
}

int main()
{

  DDRA = 0x00;
  DDRC = 0xff;
  DDRD = 0xff;
  //transmissionUSART(0);

  intialisationTimer1Interrupt();
  intialisationBoutonInterrupt(BoutonInterrupt::D3); // Faire partir l'interruption
  intialisationBoutonInterrupt(BoutonInterrupt::D2);

  //---------------DEPART CLOCK------------------//

  resetClock();

  can readValue;
  uint16_t valeur16b;
  uint8_t valeur;
  uint16_t topValue;
  double tension;

  uint16_t a = 0;

  while (horlogeContinue)
  {

    DDRD = (0 << DDD1 | 0 << DDD2 | 0 << DDD3);
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
    _delay_ms(1000);
    triggerPulse();
    countTimer0(255);
  }

  uint16_t compteur = compteurTemps;
  char temps[10];
  sprintf(temps, "%d", compteur);

  transmissionMessageUSART(temps, sizeof(temps));
}
