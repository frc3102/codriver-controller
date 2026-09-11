#include "io3102.h"

DioReport::DioReport(uint16_t raw) : m_raw(raw) {}

bool DioReport::isPressed(uint8_t port) const
{
    return !(this->m_raw & (1u << port));
}

Io3102::Io3102(uint8_t dio_addr, uint8_t adc_addr, uint8_t adc_config, TwoWire *wire = &Wire) : m_adc(adc_addr, adc_config), m_dio(dio_addr, wire), m_wire(wire) {}

void Io3102::begin()
{
    this->m_adc.begin();
    this->m_dio.begin();
}

Adc7995Report Io3102::ReadADC()
{
    return this->m_adc.Read();
}

DioReport Io3102::ReadDIO()
{
    return DioReport(this->m_dio.read16());
}

TCA9555 *Io3102::getDIO()
{
    return &this->m_dio;
}