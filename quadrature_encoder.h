#pragma once

#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "hardware/timer.h"

#include "quadrature_encoder.pio.h"

//
// ---- quadrature encoder interface example
//
// the PIO program reads phase A/B of a quadrature encoder and increments or
// decrements an internal counter to keep the current absolute step count
// updated. At any point, the main code can query the current count by using
// the quadrature_encoder_*_count functions. The counter is kept in a full
// 32 bit register that just wraps around. Two's complement arithmetic means
// that it can be interpreted as a 32-bit signed or unsigned value, and it will
// work anyway.
//

class quadrature_encoder
{

public:
    /*!
     * \brief Constructor
     *
     * \param pin_ab: GPIO pin to connect the A phase of the encoder. The B phase must be connected to the next pin.
     * \param pio: pio selected
     * \param sm: state machine selected
     */
    quadrature_encoder(uint8_t pin_ab, PIO pio, int sm);

    /*!
     * \brief Constructor
     *
     * \param pin_ab: GPIO pin to connect the A phase of the encoder. The B phase must be connected to the next pin.
     */
    quadrature_encoder(uint8_t pin_ab);

    /*!
     * \brief Release memory (as needed):
     */
    virtual ~quadrature_encoder();

    /*!
     * \brief Initialize the class instance after calling constructor
     */
    void begin(void);

    /*!
     * \brief Returns the current encoder position
     *
     * \return Returns the current count of the quadrature encoder
     */
    int getCount(void);

    /*!
     * \brief Returns the current encoder position
     *
     * \return Returns the current count of the quadrature encoder as a 16-bit integer
     */
    int16_t getCount_int16(void);

private:
    // pio - 0 or 1
    PIO quadraturePio;

    // pio state machine to use
    int quadratureSm;

    uint8_t quadratureGpioAB; // Pin for A phase of the encoder. The B phase is the next consecutive pin.
};