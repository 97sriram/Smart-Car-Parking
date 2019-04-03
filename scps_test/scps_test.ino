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

const char* ssid = "Budugutta";
const char* password = "Kinglohit";
const char* host = "scps.000webhostapp.com";

long lastMsg = 0;
char msg[50];
int value = 0;
String dsen1;
String dsen2;
int dsenc1;
int dsenc2;


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
  pinMode(DSEN1_PIN, INPUT);
  pinMode(DSEN2_PIN, INPUT);
  SPI.begin();
  

  setup_wifi();
  mfrc522.PCD_Init();

}




void loop() {

  
    host_connect();
    RfidScan();
    readPin();
    delay(1);
    upd();
    
}

void readPin()
{
  long now = millis();
  if (now - lastMsg > 100) {
    lastMsg = now;
    dsen1 = digitalRead(DSEN1_PIN);
    dsenc1 = digitalRead(DSEN1_PIN);
    dsen2 = digitalRead(DSEN2_PIN);
    dsenc2 = digitalRead(DSEN2_PIN);
    char message1[4];
    char message2[4];
    dsen1.toCharArray(message1, 4);
    dsen2.toCharArray(message2, 4);
    Serial.print("sen1=");
    Serial.println(dsen1);
    Serial.print("sen2=");
    Serial.println(dsen2);
    if(dsenc1==0)
    {
      Serial.println("HIGH");
      slot1="occupied";
    }
    if(dsenc1==1)
    {
      Serial.println("LOW");
      slot1="avail";
    }
    if(dsenc2==0)
    {
      Serial.println("HIGH");
      slot2="occupied";
    }
     if(dsenc2==1)
    {
      Serial.println("LOW");
      slot2="avail";
    }
  }
  
}



void upd()
{
  if(slrf=="0")
  {
  String url = "/smartcar/insert.php?slot1="+slot1+"&slot2="+slot2;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +"Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(500);
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
  }
  }
  else if(slrf=="54")
  {
    String url = "/smartcar/insertrf.php?slrf="+slrf;
  Serial.print("Requesting URL: ");
  Serial.println(url);
  
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +"Host: " + host + "\r\n" + "Connection: close\r\n\r\n");
  delay(500);
  
  while(client.available()){
    String line = client.readStringUntil('\r');
    Serial.print(line);
    
  }
  slrf="0";
  }
  
  Serial.println();
  Serial.println("closing connection");
  delay(10000);
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
  }
  else if ((buffer[0] == 06) && (y == 0))
  {
    Serial.println("owner Name   : ABCD ");
    Serial.println("Age  : 22 years");
    Serial.println("ACCESS DENIED");
    slrf="06";
    y = 2;
    x = 0;
  }
  else
  {
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


