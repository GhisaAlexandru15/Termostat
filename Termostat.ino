#include "afisare.h"
#include "telecomanda.h"
#include "temperatura.h"
#include "centrala.h"

float tempAF;
unsigned long deltat;

void setup() 
{
  
  init_timer_adc();
  init_adc();
  init_telecomanda();
  init_afisaj();
  init_centrala();
  SREG |= 1<<7; 
}

void loop() 
{
  oprire_afisaj();
  deltat=millis()-timps;

  if(!sistem) tempAF=tempC;
  else        tempAF=tempF;
  
  if(tempAF>250 || tempAF<=-100)
  {
    oprire_centrala();
    afisare_eroare();
  }
  else 
  {
    if(deltat<3000)
      if(deltat%500<200 && deltat>1500)
        oprire_afisaj();
      else  afisare_temperatura(T, sistem);
    else 
    {
      if(tempAF<T-0.5*(sistem+1))
        pornire_centrala();
      else if(tempAF>T+0.5*(sistem+1))
        oprire_centrala();
      afisare_temperatura(tempAF, sistem);
    }
    if(T==5 || T==40) afisare_fulg();
  }
}
