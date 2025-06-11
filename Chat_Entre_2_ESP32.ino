#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;  // Declarar el WiFiClient antes de usarlo
PubSubClient client(espClient);  // Ahora puedes pasarlo al PubSubClient


void setup() {
 Serial.begin(9600);
 Serial.println("hola");

  //---------- Conectarse a una red por nombre + contraseña-------------------
 
  Serial.println("probado...");
  WiFi.begin("iPhone Fran", "holaqtal");

  if (WiFi.status() != WL_CONNECTED) {
    // aun no esta conectado
  }
  // ok

  //-----2. Configurar el broker MQTT-----
  // Creamos un cliente de MQTT con la conexión a internet via wifi
  // Realizamos la conexión con el servidor
  client.setServer("broker.hivemq.com", 1883);

  //------3. Conectarse a un tópico-------
  client.connect("AnuelAA");  // devuelve un booleano indicando si se conecto correctamente

  client.connected();  // devuelve un booleano que nos permite chequear si la conexión fue exitosa

  client.subscribe("huergo/sistemas-embebidos/dichiera");  // seguir patron del topico a escuchar

  client.setCallback(callback);

}

void loop() {
  //4. Leer del monitor serial el mensaje a enviar
  
  if (Serial.available()) {
    String msg;
    msg = Serial.readStringUntil('\n');
    client.publish("huergo/sistemas-embebidos/maradona", "hola kudi");  // convertir el mensaje mediante .c_str()

  }

  client.loop();
  
  
}

//6. Recibir mensajes
// Callback (una función con una firma particular) que respondera ante un nuevo mensaje recibido
void callback(char* topic, byte* payload, unsigned int length) {
  // Iteramos el payload
  for (int i = 0; i < length; i++) {
    char letra = (char)payload[i];
    
  }
  Serial.println("letra");
  

}
