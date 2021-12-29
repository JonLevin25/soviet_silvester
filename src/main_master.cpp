#include <Arduino.h>
#include <Wire.h>
// #define DEBUG_SERIAL Serial
#include "common.h"
#include "utils/i2c_helper.h"

// #include "sound/putin_test_16khz_8bit_20sec.h"
// #include "sound/putin_test_32khz_8bit_20sec.h"
#include "sound/anthem_22050hz_8bit.h"
#include "Bounce2.h"
#include "utils/utils.h"

#define Pf(x, ...) Serial.printf(x, __VA_ARGS__);

#define PIN_DAC 25
#define PIN_LED_INDICATOR 32
#define PIN_REED 4

#define REED_DEBOUNCE_MILLIS 200

// #define SAMPLE_FREQ 16000
// #define WAV_DATA putin_test_16khz_8bit_20sec_wav
// #define WAV_DATA_LEN putin_test_16khz_8bit_20sec_wav_len

#define SAMPLE_FREQ 22050
#define WAV_DATA anthem_22050hz_8bit_wav
#define WAV_DATA_LEN anthem_22050hz_8bit_wav_len

Bounce reedDebounce = Bounce(PIN_REED, REED_DEBOUNCE_MILLIS);
unsigned int i = 0;

const double SAMPLE_LENGTH_SECS = 1.0 / SAMPLE_FREQ;
const uint32_t SAMPLE_DELAY_MICROS = (uint32_t) round(SAMPLE_LENGTH_SECS * 1E6);

int32_t err_sampleget = 0;
int32_t err_dacWrite = 0;
int32_t err_errs = 0;


// TODO - light triggers
const static double triggers[] = {
  1.0,
  2.0,
  3.0,
  4.0,
  5.0,
};

const static size_t len_triggers = sizeof(triggers) / sizeof(*triggers);
static unsigned long triggers_micros[len_triggers];

void play();

void setup()
{
  Serial.begin(9600);
  Pln("main_master.cpp");
  wire_setup(true, I2C_ADDR_SLAVE);

  pinMode(PIN_LED_INDICATOR, OUTPUT);
  pinMode(PIN_REED, INPUT_PULLUP);
  reedDebounce.attach(PIN_REED);
  
  // Convert triggers to micros
  for (size_t i = 0; i < len_triggers; i++)
  {
    triggers_micros[i] = (unsigned long) round(triggers[i] * 1E6);
    Pf("%f -> %lu\n", triggers[i], triggers_micros[i]);
  }

  delay(1500);
  play();
}

void play()
{
  Serial.printf("Delay micros: %u\n", SAMPLE_DELAY_MICROS);
  Serial.println("===== BEGIN SOUND TEST =====");

  uint16_t trig_idx = 0;
  
  uint32_t start_micros = micros();
  for (size_t i = 0; i < WAV_DATA_LEN; i++)
  {
    uint8_t sample = WAV_DATA[i];
    dacWrite(PIN_DAC, sample);

    // if passed a trigger time - send it via i2c.
    auto m1 = micros();
    if (trig_idx < len_triggers && (m1 - start_micros) >= triggers_micros[trig_idx]) {
      wire_sendMsg(trig_idx, I2C_ADDR_SLAVE);
      trig_idx++;
    }

    // instead of delaying a constant amount,
    // calculate it relative to how far behind we are
    uint32_t next_sample_time = start_micros + SAMPLE_DELAY_MICROS * (i+1);
    auto cur_micros = micros();
    
    if (cur_micros >= next_sample_time) continue;
    delayMicroseconds(next_sample_time - cur_micros);
  }

  Serial.println("===== END SOUND TEST =====");
  wire_sendMsg(END_VALUE, I2C_ADDR_SLAVE);
  // Serial.printf("Errors: ArrayAccess: %u, DacWrite: %u, Errors: %u\n", err_sampleget, err_dacWrite, err_errs);
}

void loop()
{
  reedDebounce.update();
  
  //
  digitalWrite(PIN_LED_INDICATOR, !reedDebounce.read());
  // return;
  //

  if (reedDebounce.fell()) {
    digitalWrite(PIN_LED_INDICATOR, HIGH);
    play();
    digitalWrite(PIN_LED_INDICATOR, LOW);
  }
}
