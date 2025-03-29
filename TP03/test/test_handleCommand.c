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
/** @note Pruebas pendientes de revision
 *
 * @test Test01:
 * @test Test02:
 * @test Test03:
 * @test Test04:
 * @test Test05:
 */
/* === Headers files inclusions =============================================================== */

#include "handleServerUtil.h"
#include "mock_fcntl.h"   // mock de la funcion open
#include "mock_unistd.h"  // mock de las funciones read, write, unlink, close
#include "unity.h"

/* === Macros definitions ====================================================================== */

#define BUFSIZE 256

/* === Private data type declarations ========================================================== */

/* === Private variable declarations =========================================================== */

/* === Private function declarations =========================================================== */

/* === Public variable definitions ============================================================= */

/* === Private variable definitions ============================================================ */

static char *command;
static char response[BUFSIZE];

/* === Private function implementation ========================================================= */
int auxiliar_open(const char *pathname, int flags)
{
  return 5;
}

ssize_t auxiliar_read(int fd, void *buf, size_t count)
{
  return (ssize_t)count;
}

ssize_t auxiliar_write(int fd, const void *buf, size_t count)
{
  return (ssize_t)count;
}

int auxiliar_close(int fd)
{
  return 0;
}

int auxiliar_unlink(const char *pathname)
{
  return 0;
}
/* === Public function implementation ========================================================== */

void setUp()
{
  command = NULL;
  memset(response, '\0', BUFSIZE);

  open_fake.custom_fake = auxiliar_open;
  read_fake.custom_fake = auxiliar_read;
  write_fake.custom_fake = auxiliar_write;
  close_fake.custom_fake = auxiliar_close;
  unlink_fake.custom_fake = auxiliar_unlink;
}

void tearDown(void)
{
}

void test_de_prueba(void)
{
  command = "SET hola mundo";
  TEST_ASSERT_EQUAL(OK, handleCommand(command, response));
}

/* === End of documentation ==================================================================== */
