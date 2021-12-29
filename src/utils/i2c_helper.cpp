#include "i2c_helper.h"
#include "Wire.h"
#include "common.h"

void (*ReceiveCallback)(uint16_t value);
void _receiveInternal(int len);

void wire_setup(bool is_master, int slave_addr)
{
    if (is_master)
    {
        Wire.begin();
    }
    else
    {
        Wire.begin(slave_addr);
    }
}

void wire_sendMsg(uint16_t value, int slave_addr)
{
  Wire.beginTransmission(slave_addr);
  
  const uint8_t *bytes = (const uint8_t *) &value;

  P("Send msg"); P(value);
  Pln();
  
  Wire.write(bytes, MSG_SIZE);
  
  #ifdef ESP32
  if (Wire.lastError() != 0) {
    Serial.printf("WIRE ERROR: %s\n", Wire.getErrorText(Wire.lastError()));
  }
  #endif

  Wire.endTransmission();
}

void wire_registerCallback(void (*callback)(uint16_t value))
{
    ReceiveCallback = callback;
    Wire.onReceive(_receiveInternal);
}

void _receiveInternal(int len)
{
  if (len != sizeof(MSG_SIZE))
  {
    P("Message size ("); P(len); P(") did not match expected! (");  P(MSG_SIZE); P(')');
    Pln();

    // Workaround - if Wire is not fully read receiveEvent will not be called again.
    P("Values: ");
    while (Wire.available()) {
        P(Wire.read(), HEX); P(' ');
    }
    Pln();
    return;
  }

  static uint8_t buf[MSG_SIZE / sizeof(uint8_t)];
  Wire.readBytes(buf, MSG_SIZE);
  const uint16_t *pVal = (uint16_t *)buf;
  
  ReceiveCallback(*pVal);
}