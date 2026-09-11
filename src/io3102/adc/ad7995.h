#ifndef AD7995_H_
#define AD7995_H_
#include <Arduino.h>
#include <Wire.h>

#define AD7995_CONFIG 0x00

#define AD7995_CH0 0b00010000
#define AD7995_CH1 0b00100000
#define AD7995_CH2 0b01000000
#define AD7995_CH3 0b10000000
#define AD7995_ALLCH AD7995_CH0 | AD7995_CH1 | AD7995_CH2 | AD7995_CH3

void printBin(uint8_t val);

struct Adc7995Report
{
    uint16_t CH0;
    uint16_t CH1;
    uint16_t CH2;
    uint16_t CH3;
};

class Ad7995
{
public:
    Ad7995(uint8_t addr, uint8_t config, TwoWire *wire = &Wire);
    void begin();
    Adc7995Report Read();

private:
    uint8_t numChannels();
    uint8_t m_addr;
    uint8_t m_config;
    uint8_t m_enabledChannels;
    TwoWire *m_wire;
};

#endif