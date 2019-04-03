#include<ESP8266WiFi.h>
#include <PubSubClient.h>
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN D1
#define SS_PIN D2
#define DSEN1_PIN D3
#define DSEN2_PIN D0
MFRC522 mfrc522(SS_PIN, RST_PIN);



int RfidNo = 0;
int x = 0;
int y = 0;
int z = 0;
int amt = 130;
int rej;
String buf;
String slot1;
String slot2;

const char* ssid = "Virus";
const char* password = "123456789";
const char* host = "scps.000webhostapp.com";

long lastMsg = 0;
char msg[50];
int value = 0;
String dsen1;
String dsen2;
int dsenc1;
int dsenc2;

String rcv="";


String slrf="0";



WiFiClient client;


void setup_wifi() {
  delay(100);
  // We start by connecting to a WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  randomSeed(micros());
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}







void setup() {
  Serial.begin(115200);
    pinMode(D3, OUTPUT);
    digitalWrite(D3, LOW);

  SPI.begin();
  

  setup_wifi();
  mfrc522.PCD_Init();




  
}

void loop() {

  host_connect();
  RfidScan();

    delay(1);
    //upd();
    upda();
    

  
}



//void upd()
//{
//  
//  
//  
//
//  client.print(String("GET ") + "/smartcar/parf.php/" + " HTTP/1.1\r\n" + "Host: " + host + "\r\n" + "Connection: close\r\n\r\n"); //GET request for server response.
//  delay(500);
//  
//  while(client.available()){
//    
//    String line = client.readStringUntil('\r'); //Read the server response line by line..
//      rcv+=line; //And store it in rcv.
//  }
//
//  Serial.println("Received string: ");
//  Serial.println(rcv);
//
//  Serial.println();
//  Serial.println("closing connection");
//  delay(5000);
//  
//}

void upda()
{
  String url = "/smartcar/insertprf.php?slrf="+slrf;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +"Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(500);
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  Serial.println();
  Serial.println("closing connection");
  delay(5000);
}
  




void host_connect()
{
  Serial.print("connecting to ");
  Serial.println(host);

  const int httpPort = 80;
  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
  }
  Serial.println("Connected Successfully to host");
  Serial.println("");
}



void dump_byte_array(byte *buffer, byte bufferSize)
{

  if ((buffer[0] == 54 ) && (x == 0))
  {
    Serial.println("owner Name   : SRIRAM ");
    Serial.println("Age  : 25 years");
    Serial.println("ACCESS GRANTED");
    slrf="54";
    Serial.println();
    Serial.println();
    x = 2;
    y = 0;
    digitalWrite(D3, LOW);
  }
  else if ((buffer[0] == 06) && (y == 0))
  {
    Serial.println("owner Name   : NIVETHA ");
    Serial.println("Age  : 22 years");
    Serial.println("ACCESS DENIED");
    slrf="06";
    y = 2;
    x = 0;
  }
  else
  {
    digitalWrite(D3, HIGH);
    slrf="0";
    Serial.println("Wrong ID");
  }
}


void RfidScan()
{
  if ( ! mfrc522.PICC_IsNewCardPresent())
    return;

  if ( ! mfrc522.PICC_ReadCardSerial())
    return;
  dump_byte_array(mfrc522.uid.uidByte, mfrc522.uid.size);
}




