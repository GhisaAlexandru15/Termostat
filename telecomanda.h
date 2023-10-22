float T=20;
unsigned char a[5], i, prev, sistem=0;
unsigned long cycle=0, t, icr_l, icr_h, timps;

void reset_semnal()
{
  i=0;  
  a[0]=0;  a[1]=0;  a[2]=0;  a[3]=0;  a[4]=0;
}

void init_telecomanda()
{
  DDRB &= ~(1<<0);
  TCCR1A = 0b00000000;
  TCCR1B = 0b01000001;
  TIMSK1 = 0b00100001;
  reset_semnal();
}

unsigned char decodare_semnal(unsigned char a) 
{
  switch(a)
  {
    case 233: return 1;   break;
    case 229: return 2;   break;
    case 225: return 3;   break;
    case 237: return 4;   break;
    case 253: return 5;   break;
    case 241: return 6;   break;
    case 224: return 7;   break;
    case 168: return 8;   break;
    case 216: return 9;   break;
    case 152: return 0;   break;
    case 164: return 10;  break; //*
    case 200: return 11;  break; //#
    case 140: return 12;  break; //OK 
    case 156: return 20;  break; //^
    case 181: return 21;  break; //v
    case 220: return 22;  break; //<
    case 149: return 23;  break; //>
    case  33: return 50;  break; //continuare
    default:  return 100; break; //eroare
  }
}

void reglare_temperatura()
{
  a[0]=decodare_semnal(a[3]);
  if(a[0]!=50) prev=a[0];
    
  switch(prev)
  {
    case 20: if(T<95&&T>=40||T<35) T=T+0.5*(sistem+1);   break;
    case 21: if(T>40||T<=35&&T>5)  T=T-0.5*(sistem+1);   break;
    case 10: 
      if(!sistem) T==5  ? T=20 : T=5;
      else        T==40 ? T=70 : T=40;
    break;
    case 11: 
      if(!sistem) {sistem=1; T=70;}
      else        {sistem=0; T=20;}
    break;
  }
  
  reset_semnal();
  timps=millis();
}

ISR (TIMER1_CAPT_vect)
{
  TCNT1H=0;
  TCNT1L=0;
  icr_l = ICR1L;
  icr_h = ICR1H;
  t = (((icr_h<<8) | icr_l)+65535*cycle);

  if(t>100000 && t<1680000 || t>1690000) 
    reset_semnal();
  else if(t>25000 && t<100000) //1
    a[i/8]|=1<<(i%8);
  else if(t>1680000 && t<1690000) //continuare
    i=a[3]=33;

  if(i>=33) 
    reglare_temperatura();
  else i++;

  cycle=0; 
}

ISR(TIMER1_OVF_vect)
{
  cycle++;
}