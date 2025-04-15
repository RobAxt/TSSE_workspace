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

/** @file test_handleCommand.c
 ** @brief Definición de las pruebas unitarias a la funcion del servidor handleCommand
 **/
/** @note Casos de prueba
 *
 * @test Test01: se prueban casos de comandos validos.
 *  |  caso  |    comando     |   return    |  buffer |
 *  |  SET   | SET hola mundo |     OK      |  mundo  |
 *  |  GET   | GET hola       | OK_RESPONSE |  mundo  |
 *  |  DEL   | DEL hola       |     OK      |    -    |
 *
 * @test Test02: se prueban casos de comandos malformados.
 *  |  caso  | comando  |  return  |  buffer |
 *  |  SET   | SET hola |  ERROR   |    -    |
 *  |  GET   | GET      |  ERROR   |    -    |
 *  |  DEL   | DEL      |  ERROR   |    -    |
 *
 * @test Test03: se prueban casos de comandos invalidos.
 *  |  caso  | comando  |  return  |  buffer |
 *  |  SET   | set hola |  ERROR   |    -    |
 *  |  GET   | get hola |  ERROR   |    -    |
 *  |  DEL   | del hola |  ERROR   |    -    |
 *
 * @test Test04: error al abrir el archivo.
 *  |  caso  |    comando     |   return   |  buffer |
 *  |  SET   | SET hola mundo |  NOT_FOUND |    -    |
 *  |  GET   | GET hola       |  NOT_FOUND |    -    |
 *
 * @test Test05: archivo no encontrado al borrar.
 *  |  caso  |  comando  |   return   |  buffer |
 *  |  DEL   | DEL hola  |     OK     |    -    |
 *
 */
/* === Headers files inclusions =============================================================== */

#include "fff.h"
#include "handleServerUtil.h"
#include "mock_fcntl.h"   // mock de la funcion open
#include "mock_unistd.h"  // mock de las funciones read, write, unlink, close
#include "unity.h"

/* === Macros definitions ====================================================================== */

#define BUFSIZE                  256
#define cantidad(variable, tipo) (sizeof(variable) / sizeof(tipo))

/* === Private data type declarations ========================================================== */

typedef struct
{
  char description[BUFSIZE];
  char command[BUFSIZE];
  char response[BUFSIZE];
  int retorno;
  char buffer[BUFSIZE];
} testCase_t;

testCase_t validCases[] = {{.description = "Valid SET",
                            .command = "SET hola mundo\n",
                            .response = "mundo",
                            .retorno = OK,
                            .buffer = '\0'},
                           {.description = "Valid GET",
                            .command = "GET hola\n",
                            .response = '\0',
                            .retorno = OK_RESPONSE,
                            .buffer = "mundo"},
                           {.description = "Valid DEL",
                            .command = "DEL hola\n",
                            .response = '\0',
                            .retorno = OK,
                            .buffer = '\0'}};

testCase_t malformCases[] = {{.description = "Malformed SET",
                              .command = "SET hola\n",
                              .response = '\0',
                              .retorno = ERROR,
                              .buffer = '\0'},
                             {.description = "Malformed GET",
                              .command = "GET \n",
                              .response = '\0',
                              .retorno = ERROR,
                              .buffer = '\0'},
                             {.description = "Malformed DEL",
                              .command = "DEL \n",
                              .response = '\0',
                              .retorno = ERROR,
                              .buffer = '\0'}};

testCase_t invalidCases[] = {{.description = "Invalid SET",
                              .command = "set hola mundo\n",
                              .response = '\0',
                              .retorno = ERROR,
                              .buffer = '\0'},
                             {.description = "Invalid GET",
                              .command = "get hola\n",
                              .response = '\0',
                              .retorno = ERROR,
                              .buffer = '\0'},
                             {.description = "Invalid DEL",
                              .command = "del hola\n",
                              .response = '\0',
                              .retorno = ERROR,
                              .buffer = '\0'}};
/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

/* === Private function implementation ========================================================= */

ssize_t validCases_read(int fd, void *buf, size_t count)
{
  memcpy(buf, validCases[fd - 3].buffer, count);
  printf("[TEST] Valid Cases Auxiliar Read: %s - Count: %d\r\n", (char *)buf, count);
  return (ssize_t)count;
}

ssize_t validCases_write(int fd, const void *buf, size_t count)
{
  memcpy(validCases[fd - 3].buffer, buf, count);
  printf("[TEST] Valid Cases Auxiliar Write: %s - Count: %d\r\n", (char *)buf, count);
  return (ssize_t)count;
}

/* === Public function implementation ========================================================== */

void setUp()
{
  FFF_RESET_HISTORY();
  RESET_FAKE(read);
  RESET_FAKE(write);
}

void tearDown(void)
{
}

// @test Test01: se prueban casos de comandos validos.
void test_comandos_validos(void)
{
  close_fake.return_val = 0;
  read_fake.custom_fake = validCases_read;
  write_fake.custom_fake = validCases_write;
  unlink_fake.return_val = 0;

  for(int i = 0; i < cantidad(validCases, testCase_t); i++)
  {
    printf("[TEST] Test Case: %s\r\n", validCases[i].description);
    open_fake.return_val = 3 + i;
    TEST_ASSERT_EQUAL(validCases[i].retorno,
                      handleCommand(validCases[i].command, validCases[i].response));
    TEST_ASSERT_EQUAL_STRING(validCases[i].response, validCases[i].buffer);
  }
}

// @test Test02: se prueban casos de comandos malformados.
void test_comandos_malformados(void)
{
  open_fake.return_val = 3;
  close_fake.return_val = 0;
  read_fake.custom_fake = NULL;
  write_fake.custom_fake = NULL;
  unlink_fake.return_val = 0;

  for(int i = 0; i < cantidad(malformCases, testCase_t); i++)
  {
    printf("[TEST] Test Case: %s\r\n", malformCases[i].description);
    TEST_ASSERT_EQUAL(malformCases[i].retorno,
                      handleCommand(malformCases[i].command, malformCases[i].response));
  }
}

// @test Test03: se prueban casos de comandos invalidos.
void test_comandos_invalidos(void)
{
  open_fake.return_val = 3;
  close_fake.return_val = 0;
  read_fake.custom_fake = NULL;
  write_fake.custom_fake = NULL;
  unlink_fake.return_val = 0;

  for(int i = 0; i < cantidad(invalidCases, testCase_t); i++)
  {
    printf("[TEST] Test Case: %s\r\n", invalidCases[i].description);
    TEST_ASSERT_EQUAL(invalidCases[i].retorno,
                      handleCommand(invalidCases[i].command, invalidCases[i].response));
  }
}
/* === End of documentation ==================================================================== */
