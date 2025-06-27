#include <WiFi.h>
#include <PubSubClient.h>

// Pines
const int buttonPins[5] = {27, 33, 25, 26, 14};
const int ldrPin = 39;

// Tópicos MQTT correspondientes
const char* topics[4] = {
  "casa/luz/living",
  "casa/luz/cocina",
  "casa/luz/dormitorio",
  "casa/luz/baño"
};
const char* allLightsTopic = "casa/luz/todas";

// Estados actuales de cada luz
bool lucesEstado[4] = {false, false, false, false};
bool lucesEncendidasPorOscuridad = false;

WiFiClient espClient;
PubSubClient client(espClient);

// Umbral de oscuridad
const int LDR_UMBRAL = 2500;

void setup() {
  Serial.begin(115200);

  // Inicializar pines de botones
  for (int i = 0; i < 4; i++) {
    pinMode(buttonPins[i], INPUT_PULLUP);
  }

  // Conexión WiFi
  WiFi.begin("iPhone Fran", "holaqtal");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("Conectado a WiFi");

  // Configuración MQTT
  client.setServer("broker.hivemq.com", 1883);
  while (!client.connected()) {
    Serial.println("Conectando MQTT...");
    if (client.connect("PanelControl")) {
      Serial.println("Conectado a MQTT");
    } else {
      delay(500);
    }
  }

  client.setCallback(callback);
}

void loop() {
  client.loop();
  controlarBotones();
  controlarLDR();
}

void controlarBotones() {
  for (int i = 0; i < 4; i++) {
    if (digitalRead(buttonPins[i]) == LOW) {  // Si el botón está presionado
      delay(50);  // Pequeño debounce
      if (digitalRead(buttonPins[i]) == LOW) {  // Comprobar de nuevo
        lucesEstado[i] = !lucesEstado[i];  // Cambiar el estado de la luz
        const char* mensaje = lucesEstado[i] ? "ON" : "OFF";
        client.publish(topics[i], mensaje);  // Publicar estado de la luz
        Serial.printf("Botón %d -> %s\n", i + 1, mensaje);
        delay(500);  // Evitar múltiples envíos por una sola pulsación
      }
    }
  }
}

void controlarLDR() {
  int ldrValue = analogRead(ldrPin);
  Serial.print("LDR: ");
  Serial.println(ldrValue);

  // Controlar luces por la cantidad de luz detectada
  if (ldrValue < LDR_UMBRAL && !lucesEncendidasPorOscuridad) {
    client.publish(allLightsTopic, "ON");
    lucesEncendidasPorOscuridad = true;
    Serial.println("Oscuridad detectada -> Encender todas las luces");
  } else if (ldrValue >= LDR_UMBRAL && lucesEncendidasPorOscuridad) {
    client.publish(allLightsTopic, "OFF");
    lucesEncendidasPorOscuridad = false;
    Serial.println("Luz detectada -> Apagar todas las luces");
  }

  delay(1000);  // Límite de lectura del LDR
}

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido en ");
  Serial.print(topic);
  Serial.print(": ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}
