#ifndef IO3102_H_
#define IO3102_H_
#include "adc/ad7995.h"
#include <TCA9555.h>

class DioReport
{
public:
    DioReport(uint16_t raw);
    bool isPressed(uint8_t port) const;

private:
    uint16_t m_raw;
};

class Io3102
{
public:
    Io3102(uint8_t dio_addr, uint8_t adc_addr, uint8_t adc_config, TwoWire *wire = &Wire);
    void begin();
    Adc7995Report ReadADC();
    DioReport ReadDIO();
    TCA9555 *getDIO();

private:
    Io3102();
    Ad7995 m_adc;
    TCA9555 m_dio;
    TwoWire *m_wire;
};

#endif