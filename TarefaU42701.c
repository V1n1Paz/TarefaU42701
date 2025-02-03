#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/clocks.h"
#include "hardware/adc.h"
#include "pico/bootrom.h"

//arquivo .pio
#include "TarefaU42701.pio.h"

//número de LEDs
#define NUM_PIXELS 25

//pino de saída
#define OUT_PIN 7

#define LED_PIN_RED 13
#define LED_PIN_GREEN 11
#define LED_PIN_BLUE 12


//botão de interupção
const uint BUT_PIN_A = 5;
const uint BUT_PIN_B = 6;

static volatile uint but_count = 0;
static volatile uint32_t last_time = 0;
//vetor para criar imagem na matriz de led - 1
double number0[25] = {0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 1.0, 0.0, 
                        0.0, 1.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 1.0, 1.0, 0.0};

// Vetor para criar imagem na matriz de LED - 1
double number1[25] = {0.0, 0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0, 0.0, 
                        0.0, 0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0, 0.0};

double number2[25] = {0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0, 0.0, 
                        0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 1.0, 1.0, 0.0};

double number3[25] = {0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0, 0.0, 
                        0.0, 0.1, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 1.0, 1.0, 0.0};

double number4[25] = {0.0, 1.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 1.0, 0.0, 
                        0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0, 0.0,
                        0.0, 0.0, 0.0, 1.0, 0.0};

double number5[25] = {0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0, 0.0, 
                        0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 1.0, 1.0, 0.0};

double number6[25] = {0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 0.0, 0.0, 1.0, 0.0, 
                        0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 1.0, 1.0, 0.0};

double number7[25] = {0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0, 0.0, 
                        0.0, 0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0, 0.0,
                        0.0, 0.0, 1.0, 0.0, 0.0};

double number8[25] = {0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 1.0, 0.0, 
                        0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 1.0, 0.0,
                        0.0, 1.0, 1.0, 1.0, 0.0};

double number9[25] = {0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 1.0, 0.0, 
                        0.0, 1.0, 1.0, 1.0, 0.0,
                        0.0, 1.0, 0.0, 0.0, 0.0,
                        0.0, 1.0, 1.0, 1.0, 0.0};

double* numbers[10] = {number0, number1, number2, number3, number4, number5, number6, number7, number8, number9};


//rotina da interrupção
static void gpio_irq_handler(uint gpio, uint32_t events){
    uint32_t current_time = to_us_since_boot(get_absolute_time());
    if (current_time - last_time >= 300000){
        last_time = current_time;
        if (gpio == BUT_PIN_A && but_count < 9)
            but_count++;
        else if (gpio == BUT_PIN_B && but_count > 0)
            but_count--;
        
    }
    printf("A = %d\n", but_count);
}

//rotina para definição da intensidade de cores do led
uint32_t matrix_rgb(double b, double r, double g)
{
  unsigned char R, G, B;
  R = r * 255;
  G = g * 255;
  B = b * 255;
  return (G << 24) | (R << 16) | (B << 8);
}

//rotina para acionar a matrix de leds - ws2812b
void numero_pio(double *numero, uint32_t valor_led, PIO pio, uint sm, double r, double g, double b){

    for (int16_t i = 0; i < NUM_PIXELS; i++) {
        if (i%2==0)
        {
            valor_led = matrix_rgb(numero[24-i], r=0.0, g=0.0);
            pio_sm_put_blocking(pio, sm, valor_led);

        }else{
            valor_led = matrix_rgb(b=0.0, numero[24-i], g=0.0);
            pio_sm_put_blocking(pio, sm, valor_led);
        }
    }
}

//função principal
int main()
{
    PIO pio = pio0; 
    bool ok;
    uint16_t i;
    uint32_t valor_led;
    double r = 0.0, b = 0.0 , g = 0.0;

    //coloca a frequência de clock para 128 MHz, facilitando a divisão pelo clock
    ok = set_sys_clock_khz(128000, false);

    // Inicializa todos os códigos stdio padrão que estão ligados ao binário.
    stdio_init_all();

    printf("iniciando a transmissão PIO");
    if (ok) printf("clock set to %ld\n", clock_get_hz(clk_sys));

    //configurações da PIO
    uint offset = pio_add_program(pio, &TarefaU42701_program);
    uint sm = pio_claim_unused_sm(pio, true);
    TarefaU42701_program_init(pio, sm, offset, OUT_PIN);

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, GPIO_OUT);
    gpio_put(LED_PIN_RED, 0);

    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, GPIO_OUT);
    gpio_put(LED_PIN_GREEN, 0);

    gpio_init(LED_PIN_BLUE);
    gpio_set_dir(LED_PIN_BLUE, GPIO_OUT);
    gpio_put(LED_PIN_BLUE, 0);
    
    gpio_set_irq_enabled_with_callback(BUT_PIN_A, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);
    gpio_set_irq_enabled_with_callback(BUT_PIN_B, GPIO_IRQ_EDGE_FALL, 1, &gpio_irq_handler);

    //inicializar o botão de interrupção - GPIO5
    gpio_init(BUT_PIN_A);
    gpio_set_dir(BUT_PIN_A, GPIO_IN);
    gpio_pull_up(BUT_PIN_A);

    //inicializar o botão de interrupção - GPIO5
    gpio_init(BUT_PIN_B);
    gpio_set_dir(BUT_PIN_B, GPIO_IN);
    gpio_pull_up(BUT_PIN_B);

    //interrupção da gpio habilitada
    gpio_set_irq_enabled_with_callback(BUT_PIN_A, GPIO_IRQ_EDGE_FALL, 1, & gpio_irq_handler);

    while (true) {
    numero_pio(numbers[but_count], valor_led, pio, sm, r, g, b);
    gpio_put(LED_PIN_RED, 1);
    sleep_ms(100);
    gpio_put(LED_PIN_RED, 0);
    sleep_ms(100);

    }
    
}