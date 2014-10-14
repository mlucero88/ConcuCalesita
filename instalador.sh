#!/bin/bash

# $1 Carpeta a instalar

RUTA_RAIZ="$1/Concucalesita"
let FORCE=0
let CLEAN_CFG=0
let CLEAN_GENERATED=0

if [ "$1" = "-h" ] || [ "$1" = "--help" ] || [ $# -ne 1 ] ; then
	echo "> Uso: instalador <ruta>"
	echo "> ruta: directorio donde se instalará el programa"
	exit 1
fi

if [ ! -d "$1" ]; then
	echo "error: no existe el directorio $1"
	exit 2
fi

mkdir -p "${RUTA_RAIZ}"
mkdir -p "${RUTA_RAIZ}/bin"
mkdir -p "${RUTA_RAIZ}/temp"
mkdir -p "${RUTA_RAIZ}/log"
mkdir -p "${RUTA_RAIZ}/conf"

echo "archivo temporal para memoria compartida" > "${RUTA_RAIZ}/temp/shared_memory"

echo "<precio_boleto> 7.50" > "${RUTA_RAIZ}/conf/config"
echo "<capacidad_calesita> 30" >> "${RUTA_RAIZ}/conf/config"
echo "<duracion_vuelta_calesita> 15" >> "${RUTA_RAIZ}/conf/config"
echo "<ninios_a_generar> 200" >> "${RUTA_RAIZ}/conf/config"

echo "> Instalación exitosa"
