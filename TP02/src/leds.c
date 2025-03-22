/************************************************************************************************
Copyright (c) 2025, Roberto Axt <roberto.axt@gmail.com>

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
associated documentation files (the "Software"), to deal in the Software without restriction,
including without limitation the rights to use, copy, modify, merge, publish, distribute,
sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial
portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES
OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

SPDX-License-Identifier: MIT
*************************************************************************************************/

/** @file leds.c
 ** @brief Definición de la biblioteca para el control de LEDs
 **/

/* === Headers files inclusions =============================================================== */

#include "leds.h"

/* === Macros definitions ====================================================================== */

//! @brief Mascara para apagar todos los leds
#define ALL_LEDS_OFF 0x0000
//! @brief Mascara para prender todos los leds
#define ALL_LEDS_ON 0xFFFF
//! @brief Desplazamiento de los LEDS para obtener la mascara
#define LEDS_TO_BIT_OFFSET 1
//! @brief Constate con el primer bit en uno para generar la mascara
#define FIRST_BIT 1

/* === Private data type declarations ========================================================== */

//! @brief  Variable privada para lmacenar la direccion de puerto de salida
static uint16_t* portAddress;

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/**
 * @brief Función privada para converitr el numero de un led en una mascara de bits
 *
 * @param led numero de led para el que se desea generara la mascara
 * @return retorna el valor de la mascara a usar
 */
static uint16_t ledToMask(uint8_t led);

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

uint16_t ledToMask(uint8_t led)
{
  return (FIRST_BIT << (led - LEDS_TO_BIT_OFFSET));
}

/* === Public function implementation ========================================================== */

void initLeds(uint16_t* memAddress)
{
  portAddress = memAddress;
  *portAddress = ALL_LEDS_OFF;
}

void turnOnSingleLeds(uint8_t led)
{
  *portAddress |= ledToMask(led);
}

void turnOffSingleLeds(uint8_t led)
{
  *portAddress &= ~ledToMask(led);
}

void turnOnAllLeds(void)
{
  *portAddress = ALL_LEDS_ON;
}
/* === End of documentation ==================================================================== */
