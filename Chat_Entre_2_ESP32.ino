#include <WiFi.h>
#include <PubSubClient.h>

WiFiClient espClient;  // Declarar el WiFiClient antes de usarlo
PubSubClient client(espClient);  // Ahora puedes pasarlo al PubSubClient


void setup() {
 Serial.begin(9600);


  //---------- Conectarse a una red por nombre + contraseña-------------------
 
  Serial.println("probado...");
  WiFi.begin("iPhone Fran", "holaqtal");

  
  while (WiFi.status() != WL_CONNECTED) {

    Serial.print(".");
   
    delay(500);
    // aun no esta conectado
  }
  Serial.println("");   
   

  // ok

  //-----2. Configurar el broker MQTT-----
  // Creamos un cliente de MQTT con la conexión a internet via wifi
  // Realizamos la conexión con el servidor
  client.setServer("broker.hivemq.com", 1883);

  //------3. Conectarse a un tópico-------
  client.connect("AnuelAA");  // devuelve un booleano indicando si se conecto correctamente

  while(!client.connected())
  {
    Serial.print("not connected.");
    delay(500);  // devuelve un booleano que nos permite chequear si la conexión fue exitosa
  }
   

  client.subscribe("huergo/sistemas-embebidos/dichiera");  // seguir patron del topico a escuchar

  client.setCallback(callback);

}

void loop() {
  //4. Leer del monitor serial el mensaje a enviar
  
  if (Serial.available()) {
    String msg;

    msg = Serial.readStringUntil('\n');
    msg = "dichiera:"+ msg;
    client.publish("huergo/sistemas-embebidos/luzko", msg.c_str());  // convertir el mensaje mediante .c_str()

  }

  client.loop();
  
  
}

//6. Recibir mensajes
// Callback (una función con una firma particular) que respondera ante un nuevo mensaje recibido
void callback(char* topic, byte* payload, unsigned int length) {
  // Iteramos el payload
  for (int i = 0; i < length; i++) {
    char letra = (char)payload[i];

    Serial.print(letra);
    
  }
  Serial.println();
  

}
