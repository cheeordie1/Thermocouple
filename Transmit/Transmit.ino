#include <SPI.h>
#include "Adafruit_MAX31855.h"
#include "VirtualWire.h"

uint8_t transmit_pin = 13;
uint16_t speed = 4000;
int seconds = 60;
int thermoCLK = 10 ;
int thermoCS = 9;
int thermoDO = 8;

int lpDelay(int);

Adafruit_MAX31855 thermocouple(thermoCLK, thermoCS, thermoDO);

struct temp_pkg {
  double internal;
  double celsius;
  double farenheit;
};

void setup() {
  vw_set_tx_pin(transmit_pin); // data output pin
  vw_setup(speed); // bits per second
}

void loop() {
  temp_pkg reading;
  reading.internal = thermocouple.readInternal();
  reading.celsius = thermocouple.readCelsius();
  reading.farenheit = thermocouple.readFarenheit();
  if (!isnan(reading.celsius) && !isnan(reading.farenheit))
    {
      vw_send((uint8_t *)&reading, sizeof(temp_pkg));
      vw_wait_tx(); // wait until message sends
    }
  delay(1000); // wait 1 minute to send another message
}
