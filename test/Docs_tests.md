# Pruebas de Validación - Implementación de `mmap`, `munmap` y `msync`

## Objetivo

Este documento describe los casos de prueba utilizados para validar la
implementación de las llamadas al sistema `mmap`, `munmap` y `msync`,
así como el comportamiento de la page cache y el manejo de permisos.

------------------------------------------------------------------------

# Test 1 -- Lectura desde un archivo mapeado

## Objetivo

Verificar que un archivo puede mapearse correctamente en memoria y que
su contenido puede leerse directamente desde la región mapeada.

## Flujo

1.  Abrir `hello.txt`.
2.  Crear un mapping con `mmap`.
3.  Leer el contenido utilizando `write(1, ptr, 8)`.

## Resultado esperado

Se imprime exactamente el contenido almacenado en el archivo.

**Funcionalidades cubiertas** - `mmap` - Traducción de direcciones -
Lectura desde memoria mapeada

------------------------------------------------------------------------

# Test 2 -- Escritura y sincronización con memoria secundaria

## Objetivo

Verificar que las modificaciones realizadas sobre una región mapeada son
persistidas en el archivo mediante `msync`.

## Flujo

1.  Abrir `hello.txt`.
2.  Crear un mapping con permisos de lectura y escritura.
3.  Escribir un valor directamente sobre la memoria mapeada.
4.  Ejecutar `msync`.
5.  Reabrir el archivo y verificar el contenido.

## Resultado esperado

El archivo contiene el nuevo contenido escrito en memoria.

**Funcionalidades cubiertas** - `mmap` - Escritura sobre memoria
mapeada - `msync` - Persistencia en memoria secundaria

------------------------------------------------------------------------

# Test 3 -- Compartición de mappings entre procesos

## Objetivo

Verificar que dos procesos pueden compartir el mismo archivo mapeado.

## Flujo

1.  Crear un `fork`.
2.  El hijo abre el archivo y crea un mapping.
3.  El hijo modifica el contenido del mapping.
4.  El padre espera al hijo.
5.  El padre crea otro mapping del mismo archivo.
6.  El padre verifica que observa los cambios realizados por el hijo.

## Resultado esperado

El padre observa exactamente la modificación realizada por el hijo.

**Funcionalidades cubiertas** - `fork` - `mmap` - Page Cache
compartida - Compartición de memoria mediante archivos

------------------------------------------------------------------------

# Test 4 -- Validación de permisos

## Objetivo

Verificar que un mapping creado únicamente con permisos de lectura no
permite escrituras.

## Flujo

1.  Crear un mapping de solo lectura.
2.  Intentar utilizar `read()` para copiar datos hacia la región
    mapeada.

## Resultado esperado

La operación falla mostrando un mensaje de permiso denegado (por
ejemplo, *write permission denied*).

**Funcionalidades cubiertas** - Protección de memoria - Validación del
campo `prot` - Control de acceso sobre mappings

------------------------------------------------------------------------

# Test 5 -- Independencia de la lista de mappings después de `fork`

## Objetivo

Verificar que padre e hijo mantienen listas de mappings independientes.

## Flujo

1.  Crear tres mappings distintos.
2.  Ejecutar `fork`.
3.  El hijo ejecuta `munmap` sobre el mapping intermedio.
4.  El padre espera al hijo.
5.  El padre accede nuevamente a los tres mappings.

## Resultado esperado

El padre continúa accediendo correctamente a los tres mappings,
demostrando que `munmap` del hijo no modificó la lista del padre.

**Funcionalidades cubiertas** - `fork` - `munmap` - Copia independiente
de la lista de mappings - Corrección del bug de nodos compartidos

------------------------------------------------------------------------

# Cobertura

  Test      mmap   munmap   msync   Permisos   Page Cache   Fork
  -------- ------ -------- ------- ---------- ------------ ------
  Test 1     ✓                                     ✓       
  Test 2     ✓                ✓                    ✓       
  Test 3     ✓                                     ✓         ✓
  Test 4     ✓                         ✓                   
  Test 5     ✓       ✓                             ✓         ✓
