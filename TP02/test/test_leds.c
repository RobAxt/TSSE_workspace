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

//! @test Apagar todos los LEDs de una vez.
void test_apagar_todos_los_LEDs(void)
{
  turnOnAllLeds();
  turnOffAllLeds();
  TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
}

//! @test Consultar el estado de un LED que está encendido
void test_Consultar_el_estado_de_un_LED_encendido(void)
{
  turnOnSingleLeds(4);
  TEST_ASSERT_EQUAL(true, isLedOn(4));
}

//! @test Consultar el estado de un LED que está apagado
void test_Consultar_el_estado_de_un_LED_apagado(void)
{
  turnOnSingleLeds(4);
  turnOffSingleLeds(4);
  TEST_ASSERT_EQUAL(true, isLedOff(4));
}

//! @test Revisar limite inferior de los parametros de led.
void test_revisar_limite_inferior(void)
{
  turnOnSingleLeds(1);
  TEST_ASSERT_EQUAL_HEX16(0x0001, ledsVirtuales);
  TEST_ASSERT_EQUAL(true, isLedOn(1));
}

//! @test Revisar limite superior de los parametros de led.
void test_revisar_limite_superior(void)
{
  turnOnSingleLeds(16);
  TEST_ASSERT_EQUAL_HEX16(0x8000, ledsVirtuales);
  TEST_ASSERT_EQUAL(true, isLedOn(16));
}

//! @test Revisar parámetros fuera del limite inferior.
void test_revisar_fuera_de_limite_inferior(void)
{
  turnOnAllLeds();
  turnOffSingleLeds(-1);
  TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
  TEST_ASSERT_EQUAL(false, isLedOff(-1));

  turnOffAllLeds();
  turnOnSingleLeds(0);
  TEST_ASSERT_EQUAL_HEX16(0x0000, ledsVirtuales);
  TEST_ASSERT_EQUAL(false, isLedOn(0));
}

//! @test Revisar parámetros fuera del limite superior.
void test_revisar_fuera_de_limite_superior(void)
{
  turnOnAllLeds();
  turnOffSingleLeds(18);
  TEST_ASSERT_EQUAL_HEX16(0xFFFF, ledsVirtuales);
  TEST_ASSERT_EQUAL(false, isLedOff(18));

  turnOffAllLeds();
  turnOnSingleLeds(32);
  TEST_ASSERT_EQUAL_HEX(0x0000, ledsVirtuales);
  TEST_ASSERT_EQUAL(false, isLedOn(32));
}
/* === End of documentation ==================================================================== */
