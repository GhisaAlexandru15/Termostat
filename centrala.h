void init_centrala() 
{
  DDRB |= 1<<5;
  PORTB &= !(1<<5);
}

void pornire_centrala()
{
  PORTB |= (1<<5);
}

void oprire_centrala()
{
  PORTB &= !(1<<5);
}
