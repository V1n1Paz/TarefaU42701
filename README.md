# Projeto de Controle de LEDs com Interrupções e Debouncing para Raspberry Pi Pico W / BitDogLab

Autor: Vinicius de Jesus Paz
>Video explicativo disponível no repositório para download.

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

### Pré-requisitos

- **Raspberry Pi Pico W** ou **BitDogLab**.
- **VS Code** configurado com a **Pico SDK**.
- **CMake** e **GCC** para compilação.

### Passo 1: Instalar o Pico SDK

Para compilar o código e carregar no Raspberry Pi Pico W, é necessário ter o **Pico SDK** instalado no seu ambiente de desenvolvimento. Siga os passos abaixo para configurar:

1. **Instalar o VS Code**: Se você ainda não tem o Visual Studio Code instalado, faça o download [aqui](https://code.visualstudio.com/).

2. **Instalar o Pico SDK**:
   - Siga as instruções de instalação do Pico SDK no [site oficial da Raspberry Pi](https://www.raspberrypi.org/documentation/pico/getting-started/).
   - Após isso, configure o SDK no seu ambiente com as instruções fornecidas no link.

### Passo 2: Clonar o Repositório

Clone o repositório para o seu computador:

```bash
git clone https://github.com/seu-usuario/nome-do-repositorio.git
