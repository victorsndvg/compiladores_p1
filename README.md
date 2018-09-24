# Compiladores e Intérpretes
## Practica 1: Analizador léxico

### 1. Compilación

La compilación del código fuente está basado en CMake.
Se puede obtener una distribución de CMake para Windows, Linux o Mac en el siguiente enlace: https://cmake.org/download/

También es necesario disponer del comando `make` para la compilación.

A continuación se describe un ejemplo de compilación de esta práctica con CMake en Linux. Para otro sistema operativo utilice los comandos análogos.
- Se denomina `$ROOT` al directorio raíz del proyecto software de este práctica, en el que se encuentra este fichero README.md.
- Se denomina `$BUILD` a la ruta en donde se desea compilar y generar los ejecutables. Se recomienda que sea diferente a $ROOT.
- Se identifica `path/to/cmake` con la ruta al archivo ejecutable `cmake` de la instalación de CMake.
- Se identifica `path/to/make` con la ruta al archivo ejecutable `make` de la instalación de CMake.

1. `cd $ROOT`
2. `mkdir $BUILD`
3. `cd $BUILD`
4. `path/to/cmake $ROOT [-DCMAKE_BUILD_TYPE=DEBUG]`
5. `path/to/make`

#### 1.1 Resultados de la compilación

Una vez realizado el proceso descrito en el punto 1. se obtendrán algunos directorios relevantes:
- $BUILD/lib: ruta en donde se encuentra la librería estática del código de la práctica.
- $BUILD/test: ruta en donde se encuentran varios tests unitarios para comprobar el funcionamiento de los subsistemas de software que se incluyen en esta práctica.
- $BUILD/bin: ruta en donde se encuentra el ejecutable principal de esta práctica. El ejecutable se llama `analyze`.

#### 1.2 Ejecución de la práctica

Para ejecutar la práctica es necesario haber realizado el proceso anterior. Eso significa tener disponible el ejecutable principal de la práctica y tener acceso al fichero de código fuente `concurrentSum.go`.

El comado de ejecución es el siguiente: 

$BUILD/bin/analyze path/to/concurrentSum.go

La salida por pantalla obtenida es un lexema por línea con el formato `(CODE) LEX`: 
- `CODE`: código correspondiente asignado desde la tabla de símbolos (entero de 4 dígitos)
- `LEX` es el lexema identificado.

En caso de haber compilado la práctica en modo `DEBUG`, la salida tendrá el formato `#LEX <SI,EI> |PS->CS| (CODE) LEX`:
- `#LEX`: contador de lexemas identificados (entero de 3 dígitos).
- `SI`: índice de comienzo de lexema en el doble buffer  (entero de 3 dígitos).
- `EI`: índice de fin de lexema en el doble buffer  (entero de 3 dígitos).
- `PS`: estado previo a la aceptación del lexema  (entero de 2 dígitos).
- `PS`: estado de aceptación del lexema  (entero de 2 dígitos).
- `CODE`: código correspondiente asignado desde la tabla de símbolos (entero de 4 dígitos)
- `LEX` es el lexema identificado.

### 2. Organización del código fuente.

El código fuente de la práctica se encuentra distribuído en varias carpetas contenidas en `$ROOT/src`. Estas carpetas son:
- `$ROOT/src/lib`: directorio que contiene el código fuente de la librería.
- `$ROOT/src/include`: directorio que contiene los ficheros de definición.
- `$ROOT/src/examples`:  directorio que contiene el código fuente del ejecutable principal.
- `$ROOT/src/tests`: directorio que contiene el código fuente de los tests unitarios.

#### 2.1 Código fuente de la librería:
- `file.c`: Implementa las operaciones básicas con ficheros.  
- `doublebuffer.c`: Implementación del doble buffer para interaccionar con el sistema de entrada.
- `dictionary.c`: Implementación de un diccionario para almacenar la tabla de símbolos.
- `statetransition.c`: Implementación del autómata finito determinista del análisis léxico.
- `lexicalanalyzer.c`: Analizador léxico y estados de aceptación del autómata. Devuelve lexemas.
- `grammaranalyzer.c`: Analizador gramatical, es el consumidor de los lexemas recibidos desde el analizador léxico.

#### 2.2 Ficheros de definición:
- `definitions.h`: Enumeración de las palabras reservadas.
- `file.h`: Cabecera de las operaciones básicas con ficheros.  
- `doublebuffer.h`: Cabecera de las funciones básicas del doble buffer.
- `dictionary.h`: Funciones principales del diccionario.
- `statetransition.h`: Función principal del cálculo de cambio de estado.
- `lexicalanalyzer.h`: Función principal del analizador léxico.
- `grammaranalyzer.h`: Función principal del analizador gramatical.

#### 2.3 Ejecutable principal:
- `analize.c`: código fuente del ejecutable principal

#### 2.4 Código fuente de los tests unitarios:
- `readchartest.c`: Pruebas de las operaciones básicas de entrada. 
- `doublebuffertest.c`: Pruebas de la lectura desde fichero con el doble buffer.
- `dictionarytest.c`: Pruebas de inserción y borrado en el diccionario.
- `statetransitiontest.c`: Prueba de la implementación del diagrama de estados
- `lexanalizertest.c`: Prueba del analizador léxico.

#### 2.5 Dependencias

Como la librería es en donde se encuentra toda la lógica, a continuación se muestra un diagrama de dependencias para intentar aclarar la interacción entre los difentes módulos que implementan la práctica. Se incluye también el programa principal.

```
 --------¬_
|          |
| file.c   |
|          |
 ----------
     ^
     |
 --------¬_          --------¬_
|          |        |          |
| double   |        | statetran|
| buffer.c |        | sition.c |
 ----------          ----------
     ^                    ^
     |                    |
     |     |--------------
 ----------¬_                      ------------¬_
|            |                    |              |
| lexical    |------------------->| dictionary.c |
| analyzer.c |                    |              |
 ------------                      --------------
      ^                                   ^
      |   |-------------------------------|
      |   |
 ----------¬_          --------¬_
|            |        |          |
| grammar    |<-------| analyze.c|
| analizer.c |        |          |
 ------------          ----------
```

