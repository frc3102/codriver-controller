#include "ad7995.h"

void printBin(uint8_t val)
{
    for (uint8_t i = 1; i < 8; i++)
    {
        if (val < pow(2, i))
            Serial.print(0b0);
    }
    Serial.print(val, BIN);
}

void printReport(Adc7995Report *report)
{
    Serial.print("0: ");
    Serial.print(report->CH0);
    Serial.print(" 1: ");
    Serial.print(report->CH1);
    Serial.print(" 2: ");
    Serial.print(report->CH2);
    Serial.print(" 3: ");
    Serial.println(report->CH3);
}

Ad7995::Ad7995(uint8_t address, uint8_t config, TwoWire *wire = &Wire) : m_addr(address), m_config(config), m_wire(wire)
{
    this->m_enabledChannels = this->numChannels();
}

void Ad7995::begin()
{
    this->m_wire->beginTransmission(this->m_addr);
    this->m_wire->write(this->m_config);
    this->m_wire->endTransmission();
}

Adc7995Report Ad7995::Read()
{
    uint8_t i;
    uint8_t ch;
    uint8_t rxByte[2];
    uint8_t nch = this->m_enabledChannels;
    this->m_wire->requestFrom(this->m_addr, nch * 2);
    Adc7995Report report = {0};
    uint16_t val;

    for (i = 0; i < nch; i++)
    {
        rxByte[0] = this->m_wire->read();
        rxByte[1] = this->m_wire->read();
#ifdef AD7995_DEBUG
        Serial.print("rxByte[");
        Serial.print((2 * i));
        Serial.print("] ");
        printBin(rxByte[0]);
        Serial.print("  rxByte[");
        Serial.print((2 * i) + 1);
        Serial.print("] ");
        printBin(rxByte[1]);
        Serial.println("");
#endif
        ch = ((rxByte[0] << 2) >> 6);
        val = ((rxByte[0] << 6) & 0x3C0) | ((rxByte[1] >> 2) & 0b00111111);
        switch (ch)
        {
        case 0:
            report.CH0 = val;
            break;
        case 1:
            report.CH1 = val;
            break;
        case 2:
            report.CH2 = val;
            break;
        case 3:
            report.CH3 = val;
        }
    }
#ifdef AD7995_DEBUG
    printReport(&report);
#endif
    return report;
}

uint8_t Ad7995::numChannels()
{
    uint8_t c = 0;
    c += (this->m_config & AD7995_CH0) > 0 ? 1 : 0;
    c += (this->m_config & AD7995_CH1) > 0 ? 1 : 0;
    c += (this->m_config & AD7995_CH2) > 0 ? 1 : 0;
    c += (this->m_config & AD7995_CH3) > 0 ? 1 : 0;
    return c;
}
