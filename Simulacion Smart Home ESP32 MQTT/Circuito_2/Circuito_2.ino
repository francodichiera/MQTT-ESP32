#include <WiFi.h>
#include <PubSubClient.h>

// Pines de los LEDs
int ledLiving = 13;
int ledCocina = 14;
int ledDormitorio = 27;
int ledBaño = 26;

// Datos de WiFi
const char* ssid = "iPhone Fran";
const char* password = "holaqtal";

// Cliente WiFi y MQTT
WiFiClient espClient;
PubSubClient client(espClient);

// Función que se ejecuta cuando llega un mensaje del broker
void callback(char* topic, byte* payload, unsigned int length) {
  String mensaje = "";
  for (int i = 0; i < length; i++) {
    mensaje += (char)payload[i];
  }

  String topico = String(topic);
  Serial.println("Tópico: " + topico);
  Serial.println("Mensaje: " + mensaje);

  // Si el mensaje es para encender/apagar todos los LEDs
  if (topico == "casa/luz/todas") {
    int estado = (mensaje == "ON") ? HIGH : LOW;
    digitalWrite(ledLiving, estado);
    digitalWrite(ledCocina, estado);
    digitalWrite(ledDormitorio, estado);
    digitalWrite(ledBaño, estado);
    return;
  }

  // LED individuales
  if (topico == "casa/luz/living") {
    digitalWrite(ledLiving, mensaje == "ON" ? HIGH : LOW); // ? --> if-else
  }
  if (topico == "casa/luz/cocina") {
    digitalWrite(ledCocina, mensaje == "ON" ? HIGH : LOW);
  }
  if (topico == "casa/luz/dormitorio") {
    digitalWrite(ledDormitorio, mensaje == "ON" ? HIGH : LOW);
  }
  if (topico == "casa/luz/baño") {
    digitalWrite(ledBaño, mensaje == "ON" ? HIGH : LOW);
  }
}

void setup() {
  Serial.begin(115200);

  // Configurar pines como salida
  pinMode(ledLiving, OUTPUT);
  pinMode(ledCocina, OUTPUT);
  pinMode(ledDormitorio, OUTPUT);
  pinMode(ledBaño, OUTPUT);

  // Conexión WiFi
  WiFi.begin(ssid, password);
  Serial.print("Conectando a WiFi...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nWiFi conectado");

  // Configurar MQTT
  client.setServer("broker.hivemq.com", 1883);
  client.setCallback(callback);

  // Conexión al broker
  Serial.print("Conectando al broker MQTT...");
  while (!client.connected()) {
    client.connect("ControladorLuces");
    delay(500);
    Serial.print(".");
  }
  Serial.println("\nConectado al broker MQTT");

  // Suscribirse a los tópicos
  client.subscribe("casa/luz/living");
  client.subscribe("casa/luz/cocina");
  client.subscribe("casa/luz/dormitorio");
  client.subscribe("casa/luz/baño");
  client.subscribe("casa/luz/todas");
}

void loop() {
  client.loop();
}
