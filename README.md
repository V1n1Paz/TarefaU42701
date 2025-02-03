# Projeto de Controle de LEDs com Interrupções e Debouncing para Raspberry Pi Pico W / BitDogLab

Este projeto foi desenvolvido para consolidar a compreensão do uso de interrupções em microcontroladores e a manipulação de LEDs, incluindo LEDs comuns e LEDs endereçáveis WS2812. Ele utiliza a placa de desenvolvimento **BitDogLab** com o microcontrolador **RP2040** (Raspberry Pi Pico W) para realizar as seguintes funcionalidades:

## Objetivos

- Compreender o funcionamento e a aplicação de interrupções em microcontroladores.
- Identificar e corrigir o fenômeno de bouncing em botões através de debouncing via software.
- Manipular e controlar LEDs comuns e LEDs endereçáveis WS2812.
- Utilizar resistores de pull-up internos para botões de acionamento.
- Desenvolver um projeto funcional que combine hardware e software.

## Descrição do Projeto

### Componentes Utilizados

- **Matriz de LEDs 5x5 (WS2812)**: Conectada à **GPIO 7**.
- **LED RGB**: Conectado às **GPIOs 11, 12 e 13**.
- **Botão A**: Conectado à **GPIO 5**.
- **Botão B**: Conectado à **GPIO 6**.

### Funcionalidades

1. **LED vermelho piscando**: O LED vermelho do LED RGB pisca 5 vezes por segundo.
2. **Botão A**: Incrementa o número exibido na matriz de LEDs cada vez que for pressionado.
3. **Botão B**: Decrementa o número exibido na matriz de LEDs cada vez que for pressionado.
4. **Exibição de números**: Os LEDs WS2812 são utilizados para criar efeitos visuais representando números de 0 a 9. O número é exibido na matriz de LEDs em formato fixo (ex.: estilo digital com segmentos iluminados).

### Requisitos

- **Uso de interrupções**: Todas as funcionalidades relacionadas aos botões devem ser implementadas utilizando interrupções (IRQ).
- **Debouncing via Software**: Implementação do tratamento do fenômeno de bouncing nos botões via software.
- **Controle de LEDs**: Demonstração de controle de LEDs comuns e LEDs WS2812.
- **Organização do código**: O código deve estar bem estruturado e comentado para fácil compreensão.

## Como Rodar

1. Clone este repositório para o seu ambiente local:
   ```bash
   git clone https://github.com/seu-usuario/nome-do-repositorio.git
