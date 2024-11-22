#include <WiFi.h>
#include <PubSubClient.h>

// Configurações de Wi-Fi
const char* ssid = "Wokwi-GUEST";
const char* password = "";

// Configuração do Broker MQTT
const char* mqttServer = "broker.hivemq.com"; // Pode ser substituído por outro broker MQTT
const int mqttPort = 1883;
const char* mqttTopicCorrente = "energia/corrente";
const char* mqttTopicTensao = "energia/tensao";

// Pinos dos potenciômetros
#define CORRENTE_PIN 32 // GPIO32
#define TENSAO_PIN 33   // GPIO33

WiFiClient espClient;
PubSubClient client(espClient);

void setup() {
  Serial.begin(115200);

  // Conexão Wi-Fi
  WiFi.begin(ssid, password);
  Serial.print("Conectando ao WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado!");

  // Conexão ao Broker MQTT
  client.setServer(mqttServer, mqttPort);
  while (!client.connected()) {
    Serial.print("Conectando ao broker MQTT...");
    if (client.connect("Dispositivo1")) {
      Serial.println("Conectado!");
    } else {
      Serial.print("Falha. Código de erro: ");
      Serial.println(client.state());
      delay(2000);
    }
  }

  // Configuração dos pinos
  pinMode(CORRENTE_PIN, INPUT);
  pinMode(TENSAO_PIN, INPUT);
}

void loop() {
  // Verifica se o cliente MQTT está conectado
  if (!client.connected()) {
    Serial.println("Reconectando ao broker MQTT...");
    while (!client.connect("Dispositivo1")) {
      Serial.print("Falha ao conectar. Tentando novamente...");
      delay(2000);
    }
    Serial.println("Reconectado ao broker MQTT!");
  }

  // Leitura dos sensores
  int leituraCorrente = analogRead(CORRENTE_PIN);
  int leituraTensao = analogRead(TENSAO_PIN);

  // Conversão das leituras
  float corrente = leituraCorrente * (10.0 / 4095.0); // Simulando corrente (0-10A)
  float tensao = leituraTensao * (240.0 / 4095.0);    // Simulando tensão (0-240V)

  // Publicando no MQTT
  bool correntePublicado = client.publish(mqttTopicCorrente, String(corrente, 2).c_str());
  bool tensaoPublicado = client.publish(mqttTopicTensao, String(tensao, 2).c_str());

  // Verifica se as publicações foram bem-sucedidas
  if (correntePublicado) {
    Serial.print("Corrente publicada: ");
    Serial.println(corrente);
  } else {
    Serial.println("Falha ao publicar corrente");
  }

  if (tensaoPublicado) {
    Serial.print("Tensão publicada: ");
    Serial.println(tensao);
  } else {
    Serial.println("Falha ao publicar tensão");
  }

  delay(1000); // Atualiza a cada 1 segundo
}
