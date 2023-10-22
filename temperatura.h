int adc_l, adc_h, adc, ms=0;
float Vin, lnR, tempK, tempC, tempF;
float A = 0.001125308852122;
float B = 0.000234711863267;
float C = 0.000000085663516;

void init_timer_adc()
{
  TCNT2 = 0;   
  OCR2A = 125;
  TCCR2A |= (1 << WGM21);
  TCCR1B |= (1 << CS22); 
  TCCR1B |= (1 << CS20); 
  TIMSK2 |= (1 << OCIE2A);   
}

void init_adc()
{
  ADMUX &= 0b11011111;
  ADMUX |= 0b01000000;
  ADCSRA |= 0b11100111;
  ADCSRB &= 0b11111000;
}

ISR (TIMER2_COMPA_vect)
{
  ms++;
  if(ms>=250)
  {
    ms=0;

    ADMUX &= 0b11100000;
    ADMUX |= 0;
    ADCSRA |= (1<<6);
    adc_l = ADCL;
    adc_h = ADCH;
    adc = ((adc_h << 8) | adc_l);

    Vin = ((float)adc)/1024.0*5;
    lnR = log(10000.0 *((5.0/Vin - 1)));
    tempK = 1/(A+(B+C*lnR*lnR)*lnR); 
    tempC = tempK-273.15;  
    tempF = tempC*9/5+32;
  }
}
