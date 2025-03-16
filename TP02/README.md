# Trabajo Práctico 02 - Testing de Software en Sistemas Embebidos
## Herramientas
```bash
sudo apt install git
sudo apt install clang-format
sudo apt install pre-commit
sudo apt install valgrind
sudo apt install doxygen
```

## Inicializacion de entorno

```bash
:$/TSSE_workspace$ git init
:$/TSSE_workspace$ pre-commit install
:$/TSSE_workspace/TP02$ pre-commit install
```

## Estructura del Proyecto
```
TP02/
├── src/                     # Archivos fuente (.c)
├── inc/                     # Archivos de encabezado (.h)
├── bin/                     # Ejecutables generados
├── test/                    #
|     └── support/           #
├── makefile                 # Archivo de construcción
├── doxyfile                 # Archivo de formato de documentacion
├── .clang-format            # Archivo oculto de formato de codigo
├── .pre-commit-config.yaml  # Archivo oculto de configuracion de Hooks de pre-commit
├── .gitignore               # Archivo oculto para ignorar archivos o carpetas a commitear
├── LICENSE.txt              # licencia MIT
└── README.md                # Este archivo
```

## Compilación

Para compilar el proyecto, asegúrate de tener instalado `gcc` y `make`. Luego, simplemente ejecuta el siguiente comando en la terminal dentro de la carpeta del proyecto:

```bash
make
```
