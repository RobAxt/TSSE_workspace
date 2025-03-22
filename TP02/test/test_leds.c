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

/** @file test_leds.c
 ** @brief Definición de la función principal del programa
 **/
/**
 *
 * @test Apagar todos los LEDs de una vez.
 * @test Consultar el estado de un LED que está encendido
 * @test Consultar el estado de un LED que est apagado
 * @test Revisar limites de los parametros.
 * @test Revisar parámetros fuera de los limites.
 */
/* === Headers files inclusions =============================================================== */

#include "leds.h"
#include "unity.h"

/* === Macros definitions ====================================================================== */

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

static uint16_t ledsVirtuales;

/* === Private function implementation ========================================================= */

/* === Public function implementation ========================================================== */

void setUp()
{
  initLeds(&ledsVirtuales);
}

//!  @test Con la inicialización todos los LEDs quedan apagados.
void test_todos_los_leds_inician_apagado(void)
{
  uint16_t ledsVirtuales = 0xFFFF;

  initLeds(&ledsVirtuales);
  TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

//! @test Prender un LED individual.
void test_prender_un_LED_individual(void)
{
  turnOnSingleLeds(4);
  // TEST_ASSERT_BIT_HIGH(3, ledsVirtuales)
  TEST_ASSERT_EQUAL_HEX16(0x0008, ledsVirtuales);
}

//! @test Apagar un LED individual.
void test_apagar_un_LED_individual(void)
{
  turnOnSingleLeds(4);
  turnOffSingleLeds(4);
  TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

//! @test Prender y apagar múltiples LED’s.
void test_prender_y_apagar_multiples_LEDs(void)
{
  turnOnSingleLeds(4);
  turnOnSingleLeds(6);
  turnOffSingleLeds(4);
  turnOffSingleLeds(8);
  TEST_ASSERT_EQUAL_HEX16(0x0020, ledsVirtuales);
}

//! @test Prender todos los LEDs de una vez.
void test_prender_todos_los_LEDs(void)
{
  turnOnAllLeds();
  TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
}

/* === End of documentation ==================================================================== */
