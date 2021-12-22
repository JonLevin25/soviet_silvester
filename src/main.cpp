#include <Arduino.h>

#include "sound/putin_test_16khz_8bit_20sec.h"
#include "sound/putin_test_32khz_8bit_20sec.h"

#define DAC_PIN 25


#define SAMPLE_FREQ 16000
#define WAV_DATA putin_test_16khz_8bit_20sec_wav
#define WAV_DATA_LEN putin_test_16khz_8bit_20sec_wav_len


// #define SAMPLE_FREQ 32000
// #define WAV_DATA putin_test_32khz_8bit_20sec_wav
// #define WAV_DATA_LEN putin_test_32khz_8bit_20sec_wav_len

const double SAMPLE_LENGTH_SECS = 1.0 / SAMPLE_FREQ;
const uint32_t SAMPLE_DELAY_MICROS = (uint32_t) round(SAMPLE_LENGTH_SECS * 1E6);

int32_t err_sampleget = 0;
int32_t err_dacWrite = 0;
int32_t err_errs = 0;

void updateMaxError(uint32_t actual, uint32_t expected, int32_t *ptrMaxError) { 
  bool errPositive = actual > expected;
  uint32_t uerror = errPositive
    ? (actual - expected)
    : (expected - actual);

  if (uerror < *ptrMaxError) return;

  *ptrMaxError = errPositive
    ? +((int32_t)uerror)
    : -((int32_t)uerror);
}

void play()
{
  Serial.printf("Delay micros: %u\n", SAMPLE_DELAY_MICROS);
  Serial.println("===== BEGIN SOUND TEST =====");
  
  uint32_t start_micros = micros();
  for (size_t i = 0; i < WAV_DATA_LEN; i++)
  {
    uint8_t sample = WAV_DATA[i];
    dacWrite(DAC_PIN, sample);
    
    // instead of delaying a constant amount,
    // calculate it relative to how far behind we are
    uint32_t next_sample_time = start_micros + SAMPLE_DELAY_MICROS * (i+1);
    delayMicroseconds(next_sample_time - micros());
  }

  Serial.println("===== END SOUND TEST =====");
}
  // Serial.printf("Errors: ArrayAccess: %u, DacWrite: %u, Errors: %u\n", err_sampleget, err_dacWrite, err_errs);

void setup()
{
  Serial.begin(9600);
  delay(1500);
  play();
}

void loop(){ }
