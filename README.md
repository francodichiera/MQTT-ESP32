# MQTT-ESP32
## Introducción a MQTT y su uso con ESP32

MQTT (Message Queuing Telemetry Transport) es un protocolo de comunicación ligero basado en el modelo de publicación/suscripción. Permite que dispositivos con recursos limitados, como el ESP32, intercambien mensajes a través de un servidor central llamado broker MQTT. Los dispositivos pueden publicar mensajes en tópicos específicos y suscribirse para recibir mensajes de esos tópicos en tiempo real, facilitando la comunicación eficiente en redes Wi-Fi.

En estos proyectos, usamos MQTT para conectar dos ESP32, permitiendo un chat básico y la simulación de un sistema de iluminación inteligente en el hogar.

----------

## Proyecto 1: Chat básico entre dos ESP32

**Objetivo:**  
Crear un chat simple donde dos placas ESP32 envían y reciben mensajes usando MQTT sobre Wi-Fi.

**Funcionamiento:**

-   Cada ESP32 se conecta a una red Wi-Fi y a un broker MQTT público.
    
-   Publican y reciben mensajes en tópicos específicos.
    
-   Los mensajes siguen el formato `<apellido>: <mensaje>`, para identificar al emisor.
    
-   Se utiliza el Monitor Serial para enviar y mostrar mensajes.
    

**Conceptos trabajados:**

-   Comunicación Wi-Fi con ESP32
    
-   Uso de MQTT: publicación, suscripción y callbacks
    
-   Lectura y escritura en el Monitor Serial
    

----------

## Proyecto 2: Simulación Smart Home con ESP32 y MQTT

**Objetivo:**  
Simular un sistema de iluminación inteligente con dos ESP32 conectados vía MQTT.

**Componentes y roles:**

-   **Panel de Control Inteligente:**
    
    -   4 pulsadores que controlan luces virtuales publicando estados ("ON"/"OFF").
        
    -   Sensor LDR que detecta niveles de luz y enciende o apaga todas las luces.
        
-   **Controlador de Luces:**
    
    -   4 LEDs que se encienden o apagan según mensajes recibidos por MQTT.
        

**Funcionamiento:**

-   El panel publica mensajes en tópicos específicos para cada luz.
    
-   El controlador se suscribe a esos tópicos y ajusta los LEDs según el estado recibido.
    

**Conceptos trabajados:**

-   Manejo de sensores y actuadores con ESP32
    
-   Control remoto mediante MQTT
    
-   Gestión de múltiples tópicos y estados de dispositivos
