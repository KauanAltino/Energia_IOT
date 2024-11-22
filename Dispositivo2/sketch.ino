#include <WiFi.h>
#include <PubSubClient.h>

// Configurações de Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqttServer = "broker.hivemq.com";
const int mqttPort = 1883;
const char* topicCorrente = "energia/corrente";  // Tópico para corrente
const char* topicTensao = "energia/tensao";      // Tópico para tensão

WiFiClient espClient;
PubSubClient client(espClient);

// Pinos
#define BUZZER_PIN 25
#define RELAY_PIN 26

void setup() {
  Serial.begin(115200);

  // Configuração dos pinos
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  // Conectar ao Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Conectando ao WiFi...");
  }
  Serial.println("Conectado ao WiFi");

  // Configuração do cliente MQTT
  client.setServer(mqttServer, mqttPort);
  client.setCallback(callback);

  reconnect(); // Conecta ao broker MQTT ao iniciar
}

void loop() {
  if (!client.connected()) {
    reconnect(); // Reconecta se a conexão com o broker MQTT for perdida
  }
  client.loop(); // Mantém a comunicação MQTT ativa
}

// Função para reconectar ao broker MQTT
void reconnect() {
  while (!client.connected()) {
    Serial.println("Reconectando ao broker MQTT...");
    if (client.connect("Dispositivo2")) {
      Serial.println("Reconectado ao broker MQTT");
      client.subscribe(topicCorrente);  // Reassina os tópicos
      client.subscribe(topicTensao);
    } else {
      Serial.print("Falha na conexão. Estado: ");
      Serial.println(client.state());
      delay(5000); // Aguarda antes de tentar novamente
    }
  }
}

// Callback para processar mensagens recebidas
void callback(char* topic, byte* payload, unsigned int length) {
  char message[50];
  strncpy(message, (char*)payload, length);
  message[length] = '\0';  // Garante que a string terminada em nulo

  Serial.print("Mensagem recebida: ");
  Serial.println(message);

  // Declaração das variáveis dentro do callback
  float current = 0.0;
  float voltage = 0.0;
  
  // Verificar se a mensagem é do tópico de corrente ou tensão
  if (strcmp(topic, topicCorrente) == 0) {
    // Processa corrente
    current = atof(message);  // Converte a string para float
    Serial.print("Corrente recebida: ");
    Serial.println(current);
  } else if (strcmp(topic, topicTensao) == 0) {
    // Processa tensão
    voltage = atof(message);  // Converte a string para float
    Serial.print("Tensão recebida: ");
    Serial.println(voltage);
  }

  // Limites de corrente e tensão
  float currentLimit = 5.0;   // Exemplo: 5A
  float voltageLimit = 220.0; // Exemplo: 220V

  // Verifica se a corrente ou tensão excedem o limite
  if (current > currentLimit || voltage > voltageLimit) {
    digitalWrite(BUZZER_PIN, HIGH); // Ativa o buzzer
    digitalWrite(RELAY_PIN, HIGH);  // Liga o relé
    Serial.println("Limite excedido! Buzzer e Relé ativados.");
  } else {
    digitalWrite(BUZZER_PIN, LOW);  // Desativa o buzzer
    digitalWrite(RELAY_PIN, LOW);   // Desliga o relé
    Serial.println("Corrente e Tensão dentro dos limites.");
  }
}
