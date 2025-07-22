#define F_CPU 16000000UL

#include <avr/io.h>        
#include <util/delay.h>    
// #include <avr/pgmspace.h>  

#define pulso_enable() _delay_us(1); set_bit(CONTR_LCD,E); _delay_us(1); clr_bit(CONTR_LCD,E); _delay_us(45)

#define set_bit(y,bit)(y|=(1<<bit))   
#define clr_bit(y,bit)(y&=~(1<<bit))  
#define cpl_bit(y,bit)(y^=(1<<bit))   
#define tst_bit(y,bit)(y&(1<<bit))    

#define INTERVALO_MS 50
#define INTERVALO_LIMITE_CURTO 200
#define INTERVALO_LIMITE_LONGO 600
#define TEMPO_ENTRE_LETRAS 750

// PORTD
#define BOTAO_PRINCIPAL PD2
#define BOTAO_ESPACO PD3
#define BOTAO_APAGAR PD4

// PORTB
#define LED_VERMELHO PB0
#define LED_AZUL PB1
#define LED_AMARELO PB2
#define LED_VERDE PB3

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
  	cpl_bit(PORTB, LED_VERDE);
    // Verifica estado do botão em tempo real
    if (!(PIND & (1 << PD2)))  // botão pressionado (nível baixo)
    {
        tempo_pressionado += INTERVALO_MS;
        tempo_nao_pressionado = 0.0;
    }
    else
    {
        tempo_pressionado = 0.0;
        tempo_nao_pressionado += INTERVALO_MS;
    }
}

// Executa a cada 50ms
ISR(TIMER1_COMPA_vect)
{
    timer_tick();
}

// Executa quando o botão é solto
ISR(INT0_vect)
{
    cpl_bit(PORTB, LED_AZUL);
}


int main()
{
    // Configurando os botões
    clr_bit(DDRD, BOTAO_PRINCIPAL);
    clr_bit(DDRD, BOTAO_APAGAR);
    clr_bit(DDRD, BOTAO_ESPACO);

    set_bit(PORTD, BOTAO_PRINCIPAL);
    set_bit(PORTD, BOTAO_APAGAR);
    set_bit(PORTD, BOTAO_ESPACO);

    // Configurando LEDs
    set_bit(DDRB, LED_VERMELHO);
    set_bit(DDRB, LED_AMARELO);
    set_bit(DDRB, LED_AZUL);
    set_bit(DDRB, LED_VERDE);

    // Inicia LEDs desligados
    clr_bit(PORTB, LED_VERMELHO);
    clr_bit(PORTB, LED_AMARELO);
    clr_bit(PORTB, LED_AZUL);
    clr_bit(PORTB, LED_VERDE);

    // Cálculo: 
    // OCR1A = (F_CPU / (prescaler * frequência)) - 1
    // frequência = 20Hz
    // Com prescaler = 64: OCR1A = 16000000 / (64 * 20) - 1 = 12499
    cli();
    TCCR1B |= (1 << WGM12); // Clear time quando a comparação for igual
    TCCR1B |= (1 << CS11) | (1 << CS10); // Prescaler 64
    OCR1A = 12499; // 50ms
    TIMSK1 |= (1 << OCIE1A); // Habilita interrupção por comparação              

    EICRA |= (1 << ISC01); // Interrupção na borda de descida
    EICRA &= ~(1 << ISC00);
    EIMSK |= (1 << INT0); // Habilita interrupção

    sei();
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

