extern int wart,modulo,dzies,setki,wyni;
const int listaD[]={B00000000,B11100000,B10000000,B00000000,B00100000,B01000000,B01000000,B00000000,B00000000,B00000000,B11101111,B00101111,B01001111};
const int listaB[]={B00001000,B00001001,B00000100,B00000110,B00000011,B00000010,B00000000,B00001011,B00000000,B00000010,B11110100,B11110100,B11110101};
//listaD is the array that manages the PortD pins, so do listaB with Port B pins



void opoz(short int s){ //this is the functions responsable for the delay
  for (long int x=0; x<s*1600;x++){
    asm("");
  }
}
int analogr(){        //reading from analog input
    ADMUX |= B00000000;
    ADMUX |= B01000000;
    ADCSRA |= B11000000;
    wart = ADCL | (ADCH << 8); 
    return wart; 
}
int pomiar() {     //measuring the time between signals
  int i=0;  
  PORTD &= B11111110; 
  while (!(PIND & (1 << 1))) {
    i += 1;                  
  }
  int startTime = i;        
  while (PIND & (1 << 1)) {  
    i += 1;
  }
  int duration = i - startTime; 
  return duration;
}
 odleglosc(int duration){  //calculating the distance
  float distance = duration *0.75* 0.68/80;   
  return distance;
}

//units managing
void jednost(){
  PORTD |= B00010101;
  PORTB |= B00110000;
}
void dziesi(){
  PORTD |= B00011001;
  PORTB |= B00110000;
}
void sto(){
  PORTD |= B00011101;
  PORTB |= B00010000;
}
void lista(int p){
  PORTD = listaD[p];           //0-7
  PORTB = listaB[p];  // 8-13
}
void wyswietl(int wart){  //displaying the calculations and units
      modulo=wart%10;
      dzies=wart/10;
      if (wart>=100){
          setki=wart/100;
          dzies=wart/10;dzies%=10;
      }
      lista(modulo);jednost();
      opoz(50);
      if (analogr()>=660){
          lista(10);
          opoz(50);
          if (wart>=10){
            lista(dzies);dziesi();
          }
          opoz(40);
          if (wart>=100){
            lista(setki);sto();
          }
          opoz(50);
      }
      else if (analogr()>=330){
          lista(11);
          opoz(50);
          PORTD = B11111011;
          PORTB = B11101111;
          opoz(50);
          if (wart<10){
            lista(0);dziesi();
          }
          opoz(40);
          if (wart>=10){
            lista(dzies);dziesi();
          }
          opoz(45);
          if (wart>=100){
            lista(setki);sto();
          }
          opoz(40);
      }
      else{
         lista(12);
          opoz(46);
          PORTD = B11111111;
          PORTB = B11001111;
          opoz(50);
          if (wart<10){
            lista(0);dziesi();
            opoz(50);
            lista(0);sto();
          }
          opoz(40);
          if (wart>=10 && wart<=100){
            lista(0);sto();
            opoz(45);
            lista(dzies);dziesi();
          }
          opoz(45);
          if (wart>=100){
            lista(dzies);dziesi();
            opoz(40);
            lista(setki);sto();
          }
          opoz(30);
      }
  }
  