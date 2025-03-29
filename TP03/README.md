# Alumno
i0616 Roberto Oscar Axt

# Trabajo Práctico 03 - Testing de Software en Sistemas Embebidos
## Herramientas
```bash
sudo apt install git
sudo apt install clang-format
sudo apt install pre-commit
sudo apt install valgrind
sudo apt install doxygen
sudo apt install ruby
sudo gem install ceedling
```

## Inicializacion de entorno

```bash
:~/TSSE_workspace$ git init
:~/TSSE_workspace/TP03$ ceedling new .
:~/TSSE_workspace/TP03$ pre-commit install
```

## Estructura del Proyecto con Ceedling
```
TP03/
├── src/                     # Archivos fuentes (.c)
├── inc/                     # Archivos de encabezados (.h)
├── doc/                     # Archivos de documentación de doxygen
├── test/                    # Archivos de pruebas unitarias (.c)
|     └── support/           #
├── makefile                 # Archivo de construcción
├── doxyfile                 # Archivo de formato de documentacion
├── .clang-format            # Archivo oculto de formato de codigo
├── .pre-commit-config.yaml  # Archivo oculto de configuracion de Hooks de pre-commit
├── .gitignore               # Archivo oculto para ignorar archivos o carpetas a commitear
├── LICENSE.txt              # licencia MIT
└── README.md                # Este archivo
```

# Comportamiento del proyecto
## Objetivo
Escribir un servidor TCP que permite almacenar información ASCII en forma de clave-valor.

El servidor debe:

1. Esperar a que un cliente se conecte mediante el protocolo TCP, puerto 5000.

2. Esperar a que el cliente envíe un comando a ejecutar. El comando se especifica como una secuencia de caracteres ASCII hasta el \n.

3. Realizar la operación correspondiente.

4. Cortar la conexión con el cliente y volver al paso 1.

Los comandos que acepta el servidor son:

* SET &lt;clave&gt; &lt;valor&gt;\n:
  * Se crea en el servidor un archivo llamado &lt;clave> con el contenido indicado en &lt;valor&gt; (sin incluir el \n).
  * Se responde al cliente OK\n.
* GET &lt;clave&gt;\n:
  * Si existe el archivo correspondiente, se responde al cliente con: OK\n&lt;valor&gt;\n (es decir, una línea de texto que dice OK y otra que contiene el contenido del archivo).
  * Si no existe, se responde con NOTFOUND\n
* DEL &lt;clave&gt;\n:
  * Si existe el archivo correspondiente, se elimina.
  * Tanto si existe como no, se responde OK\n.
Ante cualquier caso excepcional, informar la causa y finalizar el proceso con código de error.

## Cliente
Dado que el protocolo de comunicación es ASCII, no es necesario programar un cliente sino que se pueden utilizar herramientas como nc (netcat) o telnet.

En ubuntu se pueden instalar con: apt install netcat o apt install telnet.

## Ejemplo
En la consola #1 (server): ./server

En la consola #2 (client): nc localhost 5000. Si la conexión es exitosa, el proceso se queda esperando a recibir entrada de stdin.

```bash
$ nc localhost 5000
SET manzana apple
OK
$ nc localhost 5000
SET perro dog
OK
$ nc localhost 5000
SET hola hello
OK
$ nc localhost 5000
GET perro
OK
dog
$ nc localhost 5000
GET casa
NOTFOUND
$ nc localhost 5000
DEL perro
OK
$ nc localhost 5000
GET perro
NOTFOUND
$
```

# Proyecto TCP Server

Este proyecto presenta un servidor TCP básico implementado en C, organizado por directorios para facilitar la gestión del código.

## Estructura del Proyecto
```
TP_Final/
├── src/            # Archivos fuente (.c)
├── inc/            # Archivos de encabezado (.h)
├── bin/            # Ejecutables generados
├── Makefile        # Archivo de construcción
└── README.md       # Este archivo
```
## Compilación

Para compilar el proyecto, asegúrate de tener instalado `gcc` y `make`. Luego, simplemente ejecuta el siguiente comando en la terminal dentro de la carpeta del proyecto:

```bash
make
```

## Ejecución

Una vez que el proyecto está compilado, puedes ejecutar el servidor con el siguiente comando:

```bash
make run
```

## Limpieza de Archivos

Si deseas limpiar los archivos compilados y eliminar el contenido del directorio de construcción (bin), ejecuta:

```bash
make clean
```

## Funcionamiento del Servidor

En funcionamiento normal el servidor responde de la siguiente manera:

```
[INFO] Hello World!
[INFO] Waiting a connection...
[INFO] Connection from:  127.0.0.1
[INFO] Message Received: SET hola mundo
[INFO] Command received: SET
[INFO] Key-Value received: hola - mundo
[INFO] Message to Send: OK
[INFO] Waiting a connection...
[INFO] Connection from:  127.0.0.1
[INFO] Message Received: GET hola
[INFO] Command received: GET
[INFO] Key received: hola
[INFO] Message to Send: OK
[INFO] Message to Send: mundo
[INFO] Waiting a connection...
[INFO] Connection from:  127.0.0.1
[INFO] Message Received: DEL hola
[INFO] Command received: DEL
[INFO] Key received: hola
[INFO] Deleted successfully
[INFO] Message to Send: OK
[INFO] Waiting a connection...
```

# Comportamiento de la funcion a probar
## Función
```C
int handleCommand(char* cmnd, char* resp);
```
## Argumentos de entrada
```C
//! Cadena de caracteres con el comando solicitado y sus argumentos de tener
char* cmnd
//! Espacio reservado de tamaño BUFSIZE para incluir una respuesta de ser necesario
char* resp
```
## Valores de retorno
```C
//! La funcion retorno satisfactoriamente y contiene una respuesta para el usuario
#define OK_RESPONSE  2
//! La funcion retorno satisfactoriamente y no contiene una respuesta
#define OK           1
//! El archivo solicitado por el usuario no fue encontrado
#define NOT_FOUND   -1
//! Un error inesperado ha ocurrido durante la ejecucion del comando solicitado
#define ERROR       -2
```
## Pruebas a realizar
### Prueba 1
Se probará
### Prueba 2
