
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

#ifndef LEDS_H
#define LEDS_H

/** @file leds.h
 ** @brief Declaración de la biblioteca para el control de LEDs
 **/

/* === Headers files inclusions ================================================================ */

#include <stdint.h>

/* === Cabecera C++ ============================================================================ */

#ifdef __cplusplus
extern "C"
{
#endif

  /* === Public macros definitions ===============================================================
   */

  /* === Public data type declarations ===========================================================
   */

  /* === Public variable declarations ============================================================
   */

  /* === Public function declarations ============================================================
   */

  /**
   * @brief Función para inicializar la biblioteca d eleds
   *
   * @note Esta funcion debe ser llamada antes de utiliazar cualquier otra funcion de la biblioteca
   *
   * @param memAddress puntero a puerto GPIO que controla leds
   * @return void
   */
  void initLeds(uint16_t* memAddress);

  /**
   * @brief Función para encender un led especifico
   *
   * @param led numero de led a encender. Rango de 1 a 16.
   * @return void
   */
  void turnOnSingleLeds(uint8_t led);

  /**
   * @brief Función para apagar un led especifico
   *
   * @param led numero de led a encender. Rango de 1 a 16.
   * @return void
   */
  void turnOffSingleLeds(uint8_t led);

  /**
   * @brief Función para prender todos los led
   *
   * @param  void
   * @return void
   */
  void turnOnAllLeds(void);

  /* === End of documentation ====================================================================
   */

#ifdef __cplusplus
}
#endif

#endif /* LEDS_H */
