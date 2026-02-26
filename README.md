# Energia_IOT

Projeto no Wokwi:
  - Dispositivo 1:
    - https://wokwi.com/projects/415203079914457089
  - Dispositivo 2:
    - https://wokwi.com/projects/415203146870234113

Descrição da Solução:
- A solução proposta consiste em um sistema de monitoramento de energia integrado a dispositivos IoT. O sistema é composto por dois dispositivos: um sensor que coleta dados sobre consumo e geração de energia, e um atuador.
- Os dispositivos se comunicam com um gateway central baseado em Node-RED via protocolo MQTT, garantindo uma troca de mensagens eficiente e confiável. Os dados coletados serão processados, analisados e visualizados em um dashboard em tempo real, acessível por usuários para tomada de decisões informadas.

Fluxo de Funcionamento:
- Coleta de Dados:
  - O sensor IoT coleta os dados de consumo e geração de energia em tempo real e envia as informações para o broker MQTT.
- Processamento de Dados:
  - O Node-RED processa os dados recebidos, que são transmitidos por gráficos.
- Visualização no Dashboard:
  - O painel exibe gráficos, alertas e o estado atual do sistema, fornecendo informações claras para a tomada de decisões.


Tecnologias Utilizadas:

- Plataforma IoT: ESP32 (simulado no Wokwi).
- Sensores: Potentiometer, Slide-potentiometer, Buzzer, Led e Relay Module.
- Protocolo: MQTT para comunicação entre dispositivos e gateway.
- Gateway: Node-RED para processamento, análise e controle de fluxo de mensagens.
- Dashboard: Ferramentas de visualização Node-RED.
- Simulação: Simulador Wokwi para desenvolvimento e teste.

Funcionamento do programa em vídeo:

- https://www.youtube.com/watch?v=zEeLWaHR12Y
