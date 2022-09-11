#include <msp430.h> 


#define     seg_a       BIT0
#define     seg_b       BIT1
#define     seg_c       BIT2
#define     seg_d       BIT3
#define     seg_e       BIT4
#define     seg_f       BIT5
#define     seg_g       BIT6
#define     seg_p       BIT7

#define     ZERO        (seg_a + seg_b + seg_c + seg_d + seg_e + seg_f)
#define     UM          (seg_b + seg_c)
#define     DOIS        (seg_a + seg_b + seg_g + seg_e + seg_d)
#define     TRES        (seg_a + seg_b + seg_c + seg_d + seg_g)
#define     QUATRO      (seg_b + seg_c + seg_f + seg_g)
#define     CINCO       (seg_a + seg_c + seg_d + seg_g + seg_f)
#define     SEIS        (seg_a + seg_g + seg_c + seg_d + seg_e + seg_f)
#define     SETE        (seg_a + seg_b + seg_c)
#define     OITO        (seg_a + seg_b + seg_c + seg_d + seg_e + seg_f + seg_g)
#define     NOVE        (seg_a + seg_b + seg_c + seg_d + seg_f + seg_g)

void mostra_digito(char sel_disp);
void ini_p1(void);
void ini_p2(void);

unsigned int unidade = 0;
unsigned int dezena = 0;


void main (void){
  WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer


    ini_p1();
    ini_p2();

    do {
    mostra_digito('1');
    mostra_digito('2');
    } while(1);
}


void mostra_digito(char sel_disp){

  switch(sel_disp){
    case '1':
      P1OUT &= ~(BIT1);
      P1OUT |= BIT0;
      switch(unidade){
        case 0:
          P2OUT = ZERO;
          break;
        case 1:
          P2OUT = UM;
          break;
        case 2:
          P2OUT = DOIS;
          break;
        case 3:
          P2OUT = TRES;
          break;
        case 4:
          P2OUT = QUATRO;
          break;
        case 5:
          P2OUT = CINCO;
          break;
        case 6:
          P2OUT = SEIS;
          break;
        case 7:
          P2OUT = SETE;
          break;
        case 8:
          P2OUT = OITO;
          break;
        case 9:
          P2OUT = NOVE;
          break;
      }
      break;


    case '2':
      P1OUT &= ~(BIT0);
      P1OUT |= BIT1;
      switch(dezena){
        case 0:
          P2OUT = ZERO;
          break;
        case 1:
          P2OUT = UM;
          break;
        case 2:
          P2OUT = DOIS;
          break;
        case 3:
          P2OUT = TRES;
          break;
        case 4:
          P2OUT = QUATRO;
          break;
        case 5:
          P2OUT = CINCO;
          break;
        case 6:
          P2OUT = SEIS;
          break;
        case 7:
          P2OUT = SETE;
          break;
        case 8:
          P2OUT = OITO;
          break;
        case 9:
          P2OUT = NOVE;
          break;
      }
      break;
  }
}


void ini_p1(void){
  P1DIR = ~(BIT3);
  P1OUT = 0;
  //Interrupcoes
  P1IFG = 0;
  P1IES = BIT3;
  P1IE = BIT3;
}



void ini_p2(void){
  P2SEL = 0;
  P2SEL2 = 0;
  P2DIR = 0xFF;
  P2OUT = 0xFF;
}

#pragma vector=PORT1_VECTOR
  __interrupt void RTI_Porta_1(void){
  P1IFG &= ~BIT3; // Limpeza de flag obrigatoria

  if( unidade < 9 ){
    unidade++;
  }

  else if(dezena < 9){
    unidade = 0;
    dezena++;
  }

  else{
    unidade = 0;
    dezena = 0;
  }
}
