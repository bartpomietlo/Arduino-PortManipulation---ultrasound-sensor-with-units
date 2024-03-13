#include "funkcje.h"
int wart,modulo,dzies,setki,wyn;


int main(){
  DDRD = B11111101; 
  DDRB = B11111111;
  while(1){
    wyn=odleglosc(pomiar());
    wyswietl(wyn);
  }
}