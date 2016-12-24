#include <SPI.h>
#include "VirtualWire.h"

struct temp_pkg {
  double internal;
  double celsius;
  double farenheit;
};

uint8_t transmit_pin = A0;
temp_pkg heat_data;
uint8_t data_len = sizeof(temp_pkg);
uint16_t speed = 4000;

void setup() {
  Serial.begin(9600);
  Serial.println("Setting up reception of heat data.");
  vw_set_rx_pin(transmit_pin); // data output pin
  vw_setup(speed); // bits per second
  vw_rx_start();
}

void loop() {
  if (vw_get_message((uint8_t *)&heat_data, &data_len))
    {
      Serial.println("Data received:");
      Serial.println("Internal Temperature = " + String(heat_data.internal));
      Serial.println(String(heat_data.celsius) + "C");
      Serial.println(String(heat_data.farenheit) + "F");
    }
}
