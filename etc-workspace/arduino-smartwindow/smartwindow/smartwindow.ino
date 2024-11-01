#include <DHT.h>
#include <SoftwareSerial.h>

#define RX 2
#define TX 3

#define ENABLE 4
#define STEP 5
#define DIR 6

#define DHTPIN 8
#define DHTTYPE DHT22

#define MIN_TEMP 30
#define MAX_TEMP 20
#define MIN_HUMID 60
#define MAX_HUMID 30


DHT dht(DHTPIN, DHTTYPE);
SoftwareSerial HC06(TX, RX);

bool isOpened = false;
void setup() {
  pinMode(ENABLE, OUTPUT);
  pinMode(STEP, OUTPUT);
  pinMode(DIR, OUTPUT);

  digitalWrite(ENABLE, LOW);
  digitalWrite(STEP, LOW);
  digitalWrite(DIR, LOW);

  Serial.begin(9600);
  HC06.begin(9600);
  dht.begin();
  delay(1000);
}

void loop() {
  char command;
  float temp = dht.readTemperature();
  float humid = dht.readHumidity();
  
  String data = String(humid) + "," + String(temp);
  HC06.println(data);

  if (HC06.available()) {
    command = HC06.read();
    
    if (command == 'o')
      open();
    else if (command == 'c')
      close();
  }

  delay(100);

  if (temp > MIN_TEMP || temp < MAX_TEMP || humid > MIN_HUMID || humid < MAX_HUMID) {
    open();
  } else {
    close();
  }
}

void open() {
  if (isOpened)
    return;
  
  digitalWrite(DIR, LOW);
  for (int i = 0; i < 2400; i++) {
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP, LOW);
  }

  isOpened = true;
}

void close() {
  if (!isOpened)
    return;
  
  digitalWrite(DIR, HIGH);
  for (int i = 0; i < 2400; i++) {
    digitalWrite(STEP, HIGH);
    digitalWrite(STEP, LOW);
  }
  
  isOpened = false;
}