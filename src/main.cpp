#include <Arduino.h>

#include "sound/putin_test_16khz_8bit_20sec.h"
#include "sound/putin_test_32khz_8bit_20sec.h"

#define DAC_PIN 25

// don't fully understand why delay needs to be _half_ the sample length
#define SAMPLE_DELAY_MICROS ((uint32_t) round(SAMPLE_LENGTH_SECS * 1E6))
#define SAMPLE_LENGTH_SECS (1.0/SAMPLE_FREQ)


#define SAMPLE_FREQ 16000
#define PUTIN putin_test_16khz_8bit_20sec_wav
#define PUTIN_LEN putin_test_16khz_8bit_20sec_wav_len


// #define SAMPLE_FREQ 32000
// #define PUTIN putin_test_32khz_8bit_20sec_wav
// #define PUTIN_LEN putin_test_32khz_8bit_20sec_wav_len

void setup()
{
  Serial.begin(9600);
  Serial.println("===== BEGIN SOUND TEST =====");
  for (size_t i = 0; i < PUTIN_LEN; i++)
  {
    uint8_t sample = PUTIN[i];
    dacWrite(DAC_PIN,sample);
    delayMicroseconds(SAMPLE_DELAY_MICROS);
  }
  Serial.println("===== END SOUND TEST =====");
}

void loop()
{

}

