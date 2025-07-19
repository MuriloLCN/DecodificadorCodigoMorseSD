#define F_CPU 16000000UL

#include <avr/io.h>        
#include <util/delay.h>    
#include <avr/pgmspace.h>  

#define pulso_enable() _delay_us(1); set_bit(CONTR_LCD,E); _delay_us(1); clr_bit(CONTR_LCD,E); _delay_us(45)

#define set_bit(y,bit)(y|=(1<<bit))   
#define clr_bit(y,bit)(y&=~(1<<bit))  
#define cpl_bit(y,bit)(y^=(1<<bit))   
#define tst_bit(y,bit)(y&(1<<bit))    

float tempo_pressionado = 0.0;
float tempo_nao_pressionado = 0.0;

// TODO: Ver a quantidade correta de caracteres que cabem no display
char mensagem1[] = "             \0";
char mensagem2[] = "             \0";

// ISR(borda de descida no pino do botão principal)
// {
//     ...

void print_mensagem()
{
  // Imprime a mensagem no display LCD (Obs: O display que temos é i2c, tem que usar a biblioteca eu acho
}

void timer_tick()
{
  // TODO: Abtrair tudo que é relacionado a tempo (50ms, 300ms, etc.) p/ variáveis globais extras
  // senão configurar isso para ser melhor de usar vai ser difícil

  // Função que executa a cada 50ms, colocar ela com o timer
  // if (botao principal pressionado)
  // {
  //     tempo_pressionado += 50;
  //     tempo_nao_pressionado = 0.0;
  // }
  // else
  // {
  //     tempo_pressionado = 0.0;
  //     tempo_nao_pressionado += 50;
  // }
}

int main()
{
    // DDRD = 0xFF;
    // DDRB = 0b00011110; //somente pino de disparo como saída (PB1), captura no PB0 (ICP1)
    // PORTB = 0b11100010;
  
    // TCCR1B = (1<<ICES1)|(1<<CS11); //TC1 com prescaler = 8, captura na borda de subida
    // TIMSK1 = 1<<ICIE1;             //habilita a interrupção por captura
    // sei();                         //habilita a chave de interrupções globais

    while(1)
    {
    }
}

