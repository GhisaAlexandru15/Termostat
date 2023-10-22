void oprire_afisaj()
{
  PORTD &= 0b00000000; 
  PORTB |= 0b00011110;
}

void init_afisaj()
{
  DDRB |= 0b00011110;
  DDRD |= 0b11111111;
  oprire_afisaj();
}

void afisare(char nr, char c)
{
  oprire_afisaj();
  
  if(c==2) PORTD |= 1<<7;
  switch(nr)
  {
    case 0: PORTD |= 0b00111111;  break;
    case 1: PORTD |= 0b00000110;  break;
    case 2: PORTD |= 0b01011011;  break;
    case 3: PORTD |= 0b01001111;  break;
    case 4: PORTD |= 0b01100110;  break;
    case 5: PORTD |= 0b01101101;  break;
    case 6: PORTD |= 0b01111101;  break;
    case 7: PORTD |= 0b00000111;  break;
    case 8: PORTD |= 0b01111111;  break;
    case 9: PORTD |= 0b01101111;  break;
    case 12: PORTD |= 0b00111001; break;
    case 15: PORTD |= 0b01110001; break;
    case -1: PORTD |= 0b01000000; break; 
    case 'E': PORTD |= 0b01111001; break;
    case 'r': PORTD |= 0b01010000; break;
    case '.': PORTD |= 0b10000000; break;
  }

  switch(c)
  {
    case 1: PORTB &= 0b11111101;  break;
    case 2: PORTB &= 0b11111011;  break;
    case 3: PORTB &= 0b11110111;  break;
    case 4: PORTB &= 0b11101111;  break;
  }
  delay(3);
}

void afisare_temperatura(float tempAF, unsigned char sistem)
{

  if(tempAF>=100 )
  {
    afisare((int)tempAF/100,1);
    afisare((int)tempAF/10%10,2);
    afisare((int)tempAF%10,3);
  }
  else if(tempAF<0)
  {
    afisare(-1,1);
    afisare((int)(-tempAF)/10,2);
    afisare((int)(-tempAF)%10,3);
  }
  else
  {
    afisare((int)tempAF/10,1);
    afisare((int)tempAF%10,2);
    afisare('.',2);
    afisare((int)(tempAF*10)%10,3);
  }
  if(!sistem) afisare(12,4); 
  else        afisare(15,4);
}

void afisare_eroare()
{
  afisare('E',1);
  afisare('r',2);
  afisare('r',3);
}

void afisare_fulg()
{
  afisare('.',4);
}
