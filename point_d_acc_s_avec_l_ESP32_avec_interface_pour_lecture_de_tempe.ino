#include<ESP8266WiFi.h>
#include "DHT.h"
#define DHTPIN 2     // Broche de données du capteur DHT11
#define DHTTYPE DHT11   // Type de capteur DHT utilisé
#define LED_PIN_1 4  // Broche pour la première LED
#define LED_PIN_2 5  // Broche pour la deuxième LED

WiFiServer server (80);
DHT dht4(4, DHT11);

void setup() 
{
pinMode(4, OUTPUT);
Serial.begin(9600);
digitalWrite(4, HIGH);
WiFi.disconnect();
delay(3000);
Serial.println("Start");
WiFi.begin("Darrylo","Azert12&");
Serial.begin(9600);
  dht.begin();
  pinMode(LED_PIN_1, OUTPUT);
  pinMode(LED_PIN_2, OUTPUT);

while((!(WiFi.status() == WL_CONNECTED)))
{
  delay(300);
  Serial.println("...");
}
Serial.println("Réseau connecté");
Serial.println("You IP adresse is :");
Serial.println((WiFi.localIP().toString()));
server.begin();

}

void loop() 
{
 WiFiClient client = server.available();
 if(!client) 
 {
  return;
 }
 while(!client.available())
 {
  delay(1);
 }
 client.println("HTTP/1.1 200 OK");
 client.println("Content-Type: text/html");
client.println("");
client.println("<!DOCTYPE HTML>");
client.println("<html>");
client.println("<head>");
client.println("</head>");
client.println("<body>");
client.println("<h1 style=""color:#ff0000"">");
client.println("SERVEUR WEB");
client.println("</h1>");
client.println("<span style=""color:#000000; font-size: 14px"">");
client.println("PARAMETRE DE TEMPERATURE ET D\'HUMIDITE");
client.println("<span style=""color:#000000; font-size:14px"">");
client.println("DHT11");
client.println("</span>");
client.println("<br>");
client.println("<span style=""color:#ff0000; font-size:14px"">");
client.println("Le taux de température est :");
client.println("</span>");
client.println("<span style=""color:#ff0000; font-size:20px"">");
  client.println((dht4.readTemperature()));
  client.println("</span>");
  client.println("<br>");
  client.println("<span style=""color:green;font-size:14px"">");
  client.println("Le taux d'humidity est :");

  client.println("</span>");
  client.println("<span style=""color:green; font-size:20px"">");
  client.println((dht4.readHumidity()));
  client.println("</span>");
  delay(1000);
  client.println("</body>");
  client.println("</html>");
  
  delay(1);
  client.flush();

  delay(2000);  // Attendre quelques secondes entre chaque lecture

  float h = dht.readHumidity();    // Lire l'humidité
  float t = dht.readTemperature();  // Lire la température en degrés Celsius

  if (isnan(h) || isnan(t)) {  // Vérifier si la lecture a échoué
    Serial.println("Erreur lors de la lecture du capteur DHT !");
    return;
  }

  Serial.print("Humidité : ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Température : ");
  Serial.print(t);
  Serial.println("°C");

  // Allumer la première LED si la température est supérieure à 25°C
  if (t > 30) {
    digitalWrite(LED_PIN_1, HIGH);
  } else {
    digitalWrite(LED_PIN_1, LOW);
  }

  // Allumer la deuxième LED si l'humidité est supérieure à 70%
  if (h > 50) {
    digitalWrite(LED_PIN_2, HIGH);
  } else {
    digitalWrite(LED_PIN_2, LOW);
  

 }
 }
