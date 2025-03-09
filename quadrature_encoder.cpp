/*!
 * @file quadrature_encoder.cpp
 * @brief   Quadrature Encoders
 * @author PDBeal
 * @details
 *
 * @remarks Adapted from Raspberry Pi pico-examples by PDBeal
 */

#include "quadrature_encoder.h"

QuadratureEncoder::QuadratureEncoder(uint8_t pin_ab) : quadratureGpioAB(pin_ab)
{
    PIO pio = pio0;
    int sm;
    // Find a free SM on one of the PIO's
    sm = pio_claim_unused_sm(pio, false); // don't panic
    // Try pio1 if SM not found
    if (sm < 0)
    {
        pio = pio1;
        sm = pio_claim_unused_sm(pio, true); // panic if no SM is free
    }

    quadratureSm = sm;
    quadraturePio = pio;
}

QuadratureEncoder::QuadratureEncoder(uint8_t pin_ab, PIO pio, int sm) : quadratureGpioAB(pin_ab), quadraturePio(pio), quadratureSm(sm) { }

// Release memory (as needed):
QuadratureEncoder::~QuadratureEncoder(void)
{
    // if (pixels)
    //     free(pixels);
}

void QuadratureEncoder::begin()
{
    // we don't really need to keep the offset, as this program must be loaded
    // at offset 0
    uint offset = pio_add_program(quadraturePio, &quadrature_encoder_program);
    quadrature_encoder_program_init(quadraturePio, quadratureSm, quadratureGpioAB, 0);
}

int QuadratureEncoder::getCount()
{
    return quadrature_encoder_get_count(quadraturePio, quadratureSm);
}

int16_t QuadratureEncoder::getCount_int16()
{
    return quadrature_encoder_get_count_int16(quadraturePio, quadratureSm);
}
