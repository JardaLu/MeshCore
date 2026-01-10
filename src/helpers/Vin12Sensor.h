#pragma once
#include <Arduino.h>

#ifndef VIN_ADC_PIN
  #define VIN_ADC_PIN A0
#endif

#ifndef VIN_ADC_K
  #define VIN_ADC_K 4.206f
#endif

static inline uint32_t readVin12_mV()
{
  // pro napětí kolem 0–3.3V na pinu je bezpečné dát 11dB
  // (přesný rozsah závisí na ESP32-S3 kalibraci, ale 11dB je pro tvoje ~2.9V správně)
  analogSetPinAttenuation(VIN_ADC_PIN, ADC_11db);

  uint32_t sum = 0;
  const int n = 16;
  for (int i = 0; i < n; i++) {
    sum += analogReadMilliVolts(VIN_ADC_PIN);
    delay(2);
  }
  float adc_mv = sum / (float)n;
  float vin_mv = adc_mv * VIN_ADC_K;

  return (uint32_t)(vin_mv + 0.5f);
}
