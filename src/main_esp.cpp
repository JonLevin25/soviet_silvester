#include <Arduino.h>

#include "sound/putin_test_16khz_8bit_20sec.h"
#include "sound/putin_test_32khz_8bit_20sec.h"
#include "Bounce2.h"
#include "utils/utils.h"

#define PIN_DAC 25
#define PIN_LED_INDICATOR 32
#define PIN_REED 4


#define REED_DEBOUNCE_MILLIS 200

#define SAMPLE_FREQ 16000
#define WAV_DATA putin_test_16khz_8bit_20sec_wav
#define WAV_DATA_LEN putin_test_16khz_8bit_20sec_wav_len

Bounce reedDebounce = Bounce(PIN_REED, REED_DEBOUNCE_MILLIS);
unsigned int i = 0;


// #define SAMPLE_FREQ 32000
// #define WAV_DATA putin_test_32khz_8bit_20sec_wav
// #define WAV_DATA_LEN putin_test_32khz_8bit_20sec_wav_len

const double SAMPLE_LENGTH_SECS = 1.0 / SAMPLE_FREQ;
const uint32_t SAMPLE_DELAY_MICROS = (uint32_t) round(SAMPLE_LENGTH_SECS * 1E6);

int32_t err_sampleget = 0;
int32_t err_dacWrite = 0;
int32_t err_errs = 0;


void play()
{
  Serial.printf("Delay micros: %u\n", SAMPLE_DELAY_MICROS);
  Serial.println("===== BEGIN SOUND TEST =====");
  
  uint32_t start_micros = micros();
  for (size_t i = 0; i < WAV_DATA_LEN; i++)
  {
    uint8_t sample = WAV_DATA[i];
    dacWrite(PIN_DAC, sample);

    // instead of delaying a constant amount,
    // calculate it relative to how far behind we are
    uint32_t next_sample_time = start_micros + SAMPLE_DELAY_MICROS * (i+1);
    auto cur_micros = micros();
    
    if (cur_micros >= next_sample_time) continue;
    delayMicroseconds(next_sample_time - cur_micros);
  }

  Serial.println("===== END SOUND TEST =====");
}
  // Serial.printf("Errors: ArrayAccess: %u, DacWrite: %u, Errors: %u\n", err_sampleget, err_dacWrite, err_errs);

void setup()
{
  Serial.begin(9600);
  Serial.println("main_esp.cpp");
  pinMode(PIN_LED_INDICATOR, OUTPUT);
  pinMode(PIN_REED, INPUT_PULLUP);
  reedDebounce.attach(PIN_REED);
  
  
  // delay(1500);
  // play();
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
