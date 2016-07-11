#include <TinyGPS.h>
#include <SoftwareSerial.h>

TinyGPS gps;
SoftwareSerial nss(6, 255);

void setup() {
  Serial.begin(9600);
  nss.begin(4800);
  Serial.println("Reading GPS");
}

void loop() {
  bool newdata = false;
  unsigned long start = millis();
  while (millis() - start < 5000) {
    if (feedgps())
    newdata = true;
  }
  if (newdata) {
    gpsdump(gps);
  }

}

void gpsdump(TinyGPS &gps) {
  float flat, flon;
  unsigned long age;
  gps.f_get_position (&flat, &flon, &age);
  Serial.print(flat, 4); 
  Serial.print(", ");
  Serial.println(flon, 4);
  }
  bool feedgps() {
    while(nss.available()) {
      if(gps.encode(nss.read()))
        return true;
    }
    return false;
}  


