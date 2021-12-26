#include <Arduino.h>

const uint16_t freqs[] = {
  50,
  100,
  150,
  200,
  400,
  1000,
  2000,
};
const size_t freqs_len = sizeof(freqs) / sizeof(freqs[0]);

#define DAC_PIN 25
#define TONE_LEN_MILLIS 1000U
#define WAIT_LEN_MILLIS 250U

void playToneDac(uint16_t freq, uint16_t millis, uint8_t amp)
{ 
  const uint32_t start_micros = micros();
  const uint32_t end_micors = start_micros + millis * 1e3;
  const uint32_t delay_micros = (uint32_t) round((0.5/freq)*1e6); // delay half so we can set peaks AND troughs

  uint32_t cur_micros = start_micros;
  uint32_t i = 0;
  do
  {
    // Todo simplify for article
    uint8_t val = (i++ % 2) == 0
      ? 0
      : amp;

    dacWrite(DAC_PIN, val);
    
    // instead of delaying a constant amount,
    // calculate it relative to how far behind we are
    uint32_t next_sample_time = start_micros + delay_micros * (i+1);
    delayMicroseconds(next_sample_time - micros());
    cur_micros = micros();
  } while(cur_micros < end_micors);
}

void setup()
{
  Serial.begin(9600);
  Serial.println(freqs_len);
  for (size_t i = 0; i < freqs_len; i++)
  {
    Serial.printf("Playing freq: %u\n", freqs[i]);
    playToneDac(freqs[i], TONE_LEN_MILLIS, 128);
    delay(WAIT_LEN_MILLIS);
  }
}

void loop(){}