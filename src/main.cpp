#include <Arduino.h>

#include "sound/putin_test_16khz_8bit_20sec.h"
#include "sound/putin_test_32khz_8bit_20sec.h"

#define DAC_PIN 25


#define SAMPLE_FREQ 16000
#define PUTIN putin_test_16khz_8bit_20sec_wav
#define PUTIN_LEN putin_test_16khz_8bit_20sec_wav_len


// #define SAMPLE_FREQ 32000
// #define PUTIN putin_test_32khz_8bit_20sec_wav
// #define PUTIN_LEN putin_test_32khz_8bit_20sec_wav_len

const double SAMPLE_LENGTH_SECS = 1.0 / SAMPLE_FREQ;
const uint32_t SAMPLE_DELAY_MICROS = (uint32_t) round(SAMPLE_LENGTH_SECS * 1E6);

void setup()
{
  Serial.begin(9600);
  Serial.println("===== BEGIN SOUND TEST =====");
  for (size_t i = 0; i < PUTIN_LEN; i++)
  {
    uint8_t sample = PUTIN[i];
    dacWrite(DAC_PIN, sample);
    delayMicroseconds(SAMPLE_DELAY_MICROS);
  }
  Serial.println("===== END SOUND TEST =====");
}

void loop()
{

}

