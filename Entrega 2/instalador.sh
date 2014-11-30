#!/bin/bash

# $1 Carpeta a instalar

if [ "$1" = "-h" ] || [ "$1" = "--help" ] || [ $# -ne 1 ] ; then
	echo "> Uso: instalador <ruta>"
	echo "> ruta: directorio donde se instalará el programa"
	exit 1
fi

if [ ! -d "$1" ]; then
	echo "error: no existe el directorio $1"
	exit 2
fi

RUTA_RAIZ="$(echo "$1" | sed 's/\/$//')/TP2-GestorBD"

mkdir -p "${RUTA_RAIZ}"

PATH_PROYECTOS="$(dirname "$0")"

#Compilacion Protocolo
mkdir -p "${PATH_PROYECTOS}/Protocolo/obj"

g++ -O2 -c "${PATH_PROYECTOS}/Protocolo/src/Message_Queue/MessageQueueException.cpp" -o "${PATH_PROYECTOS}/Protocolo/obj/MessageQueueException.o"
g++ -O2 -c "${PATH_PROYECTOS}/Protocolo/src/ProtocoloCliente.cpp" -o "${PATH_PROYECTOS}/Protocolo/obj/ProtocoloCliente.o"
g++ -O2 -c "${PATH_PROYECTOS}/Protocolo/src/ProtocoloGestor.cpp" -o "${PATH_PROYECTOS}/Protocolo/obj/ProtocoloGestor.o"

ar -r "${PATH_PROYECTOS}/Protocolo/libProtocolo.a" "${PATH_PROYECTOS}/Protocolo/obj/MessageQueueException.o" "${PATH_PROYECTOS}/Protocolo/obj/ProtocoloCliente.o" "${PATH_PROYECTOS}/Protocolo/obj/ProtocoloGestor.o"

#Compilacion Cliente
mkdir -p "${PATH_PROYECTOS}/ProcesoCliente/obj"

g++ -O2 -c -I"${PATH_PROYECTOS}/Protocolo/src" "${PATH_PROYECTOS}/ProcesoCliente/src/Cliente.cpp" -o "${PATH_PROYECTOS}/ProcesoCliente/obj/Cliente.o"
g++ -O2 -c -I"${PATH_PROYECTOS}/Protocolo/src" "${PATH_PROYECTOS}/ProcesoCliente/src/cliente.cpp" -o "${PATH_PROYECTOS}/ProcesoCliente/obj/cliente.o"

g++ -L"${PATH_PROYECTOS}/Protocolo" -o "${RUTA_RAIZ}/cliente" "${PATH_PROYECTOS}/ProcesoCliente/obj/Cliente.o" "${PATH_PROYECTOS}/ProcesoCliente/obj/cliente.o" -lProtocolo

#Compilacion Gestor
mkdir -p "${PATH_PROYECTOS}/ProcesoGestorBD/obj"

g++ -O2 -c -I"${PATH_PROYECTOS}/Protocolo/src" "${PATH_PROYECTOS}/ProcesoGestorBD/src/Gestor.cpp" -o "${PATH_PROYECTOS}/ProcesoGestorBD/obj/Gestor.o"
g++ -O2 -c -I"${PATH_PROYECTOS}/Protocolo/src" "${PATH_PROYECTOS}/ProcesoGestorBD/src/gestor.cpp" -o "${PATH_PROYECTOS}/ProcesoGestorBD/obj/gestor.o"

g++ -L"${PATH_PROYECTOS}/Protocolo" -o "${RUTA_RAIZ}/gestor" "${PATH_PROYECTOS}/ProcesoGestorBD/obj/Gestor.o" "${PATH_PROYECTOS}/ProcesoGestorBD/obj/gestor.o" -lProtocolo

echo "> Instalación exitosa"
