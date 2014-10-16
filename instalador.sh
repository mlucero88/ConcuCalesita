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

RUTA_RAIZ="$(echo "$1" | sed 's/\/$//')/Concucalesita"

mkdir -p "${RUTA_RAIZ}"
mkdir -p "${RUTA_RAIZ}/bin"
mkdir -p "${RUTA_RAIZ}/tmp"
mkdir -p "${RUTA_RAIZ}/log"
mkdir -p "${RUTA_RAIZ}/conf"

echo "archivo temporal para memoria compartida" > "${RUTA_RAIZ}/tmp/shared_memory"
echo "archivo temporal para lockear el logger" > "${RUTA_RAIZ}/tmp/lock_file"
#echo "archivo temporal para fifo entre generador y boleteria" > "${RUTA_RAIZ}/tmp/fifo_gen_bol"
#echo "archivo temporal para fifo entre boleteria y calesita" > "${RUTA_RAIZ}/tmp/fifo_bol_cal"

echo "<precio_boleto> 7.50" > "${RUTA_RAIZ}/conf/config"
echo "<capacidad_calesita> 10" >> "${RUTA_RAIZ}/conf/config"
echo "<duracion_vuelta_calesita> 15" >> "${RUTA_RAIZ}/conf/config"
echo "<ninios_a_generar> 100" >> "${RUTA_RAIZ}/conf/config"

PATH_PROYECTOS="$(dirname "$0")"

#Compilacion IPC
mkdir -p "${PATH_PROYECTOS}/IPC/obj"

g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Common/ByteStream.cpp" -o "${PATH_PROYECTOS}/IPC/obj/ByteStream.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Lock/LockException.cpp" -o "${PATH_PROYECTOS}/IPC/obj/LockException.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Lock/Lock.cpp" -o "${PATH_PROYECTOS}/IPC/obj/Lock.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Pipe/Deserializador.cpp" -o "${PATH_PROYECTOS}/IPC/obj/Deserializador.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Pipe/Fifo.cpp" -o "${PATH_PROYECTOS}/IPC/obj/Fifo.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Pipe/FifoEscritura.cpp" -o "${PATH_PROYECTOS}/IPC/obj/FifoEscritura.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Pipe/FifoLectura.cpp" -o "${PATH_PROYECTOS}/IPC/obj/FifoLectura.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Pipe/ITraductor.cpp" -o "${PATH_PROYECTOS}/IPC/obj/ITraductor.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Pipe/Serializador.cpp" -o "${PATH_PROYECTOS}/IPC/obj/Serializador.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Seniales/SignalHandler.cpp" -o "${PATH_PROYECTOS}/IPC/obj/SignalHandler.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Shared_Memory/SharedMemoryException.cpp" -o "${PATH_PROYECTOS}/IPC/obj/SharedMemoryException.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Shared_Memory/SharedMemoryBlock.cpp" -o "${PATH_PROYECTOS}/IPC/obj/SharedMemoryBlock.o"
g++ -O2 -c "${PATH_PROYECTOS}/IPC/src/Semaforos/Semaforo.cpp" -o "${PATH_PROYECTOS}/IPC/obj/Semaforo.o"

ar -r "${PATH_PROYECTOS}/IPC/libIPC.a" "${PATH_PROYECTOS}/IPC/obj/ByteStream.o" "${PATH_PROYECTOS}/IPC/obj/LockException.o" "${PATH_PROYECTOS}/IPC/obj/Lock.o" "${PATH_PROYECTOS}/IPC/obj/Deserializador.o" "${PATH_PROYECTOS}/IPC/obj/Fifo.o" "${PATH_PROYECTOS}/IPC/obj/FifoEscritura.o" "${PATH_PROYECTOS}/IPC/obj/FifoLectura.o" "${PATH_PROYECTOS}/IPC/obj/ITraductor.o" "${PATH_PROYECTOS}/IPC/obj/Serializador.o" "${PATH_PROYECTOS}/IPC/obj/SignalHandler.o" "${PATH_PROYECTOS}/IPC/obj/SharedMemoryException.o" "${PATH_PROYECTOS}/IPC/obj/SharedMemoryBlock.o" "${PATH_PROYECTOS}/IPC/obj/Semaforo.o"

#Compilacion Comun
mkdir -p "${PATH_PROYECTOS}/Comun/obj"

g++ -O2 -c -Wno-unused-result -I"${PATH_PROYECTOS}/IPC/src" "${PATH_PROYECTOS}/Comun/src/Logger.cpp" -o "${PATH_PROYECTOS}/Comun/obj/Logger.o"
g++ -O2 -c -I"${PATH_PROYECTOS}/IPC/src" "${PATH_PROYECTOS}/Comun/src/Ninio.cpp" -o "${PATH_PROYECTOS}/Comun/obj/Ninio.o"
g++ -O2 -c -I"${PATH_PROYECTOS}/IPC/src" "${PATH_PROYECTOS}/Comun/src/TraductorNinio.cpp" -o "${PATH_PROYECTOS}/Comun/obj/TraductorNinio.o"

ar -r "${PATH_PROYECTOS}/Comun/libComun.a" "${PATH_PROYECTOS}/Comun/obj/Logger.o" "${PATH_PROYECTOS}/Comun/obj/Ninio.o" "${PATH_PROYECTOS}/Comun/obj/TraductorNinio.o"

#Compilacion Boleteria
mkdir -p "${PATH_PROYECTOS}/ProcesoBoleteria/obj"

g++ -O2 -c -Wno-unused-result -I"${PATH_PROYECTOS}/IPC/src" -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoBoleteria/src/Boleteria.cpp" -o "${PATH_PROYECTOS}/ProcesoBoleteria/obj/Boleteria.o"
g++ -O2 -c -I"${PATH_PROYECTOS}/IPC/src" -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoBoleteria/src/Caja.cpp" -o "${PATH_PROYECTOS}/ProcesoBoleteria/obj/Caja.o"
g++ -O2 -c -I"${PATH_PROYECTOS}/IPC/src" -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoBoleteria/src/boleteria.cpp" -o "${PATH_PROYECTOS}/ProcesoBoleteria/obj/boleteria.o"

g++ -L"${PATH_PROYECTOS}/IPC" -L"${PATH_PROYECTOS}/Comun" -o "${RUTA_RAIZ}/bin/boleteria" "${PATH_PROYECTOS}/ProcesoBoleteria/obj/Boleteria.o" "${PATH_PROYECTOS}/ProcesoBoleteria/obj/Caja.o" "${PATH_PROYECTOS}/ProcesoBoleteria/obj/boleteria.o" -lComun -lIPC -ljsoncpp

#Compilacion Calesita
mkdir -p "${PATH_PROYECTOS}/ProcesoCalesita/obj"

g++ -O2 -c -I"${PATH_PROYECTOS}/IPC/src" -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoCalesita/src/Calesita.cpp" -o "${PATH_PROYECTOS}/ProcesoCalesita/obj/Calesita.o"
g++ -O2 -c -Wno-unused-result -I"${PATH_PROYECTOS}/IPC/src" -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoCalesita/src/MotorCalesita.cpp" -o "${PATH_PROYECTOS}/ProcesoCalesita/obj/MotorCalesita.o"
g++ -O2 -c -I"${PATH_PROYECTOS}/IPC/src" -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoCalesita/src/calesita.cpp" -o "${PATH_PROYECTOS}/ProcesoCalesita/obj/calesita.o"

g++ -L"${PATH_PROYECTOS}/IPC" -L"${PATH_PROYECTOS}/Comun" -o "${RUTA_RAIZ}/bin/calesita"  "${PATH_PROYECTOS}/ProcesoCalesita/obj/Calesita.o" "${PATH_PROYECTOS}/ProcesoCalesita/obj/MotorCalesita.o" "${PATH_PROYECTOS}/ProcesoCalesita/obj/calesita.o" -lComun -ljsoncpp -lIPC

#Compilacion Generador
mkdir -p "${PATH_PROYECTOS}/ProcesoGenerador/obj"

g++ -O2 -c -Wno-unused-result -I"${PATH_PROYECTOS}/IPC/src" -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoGenerador/src/generador.cpp" -o "${PATH_PROYECTOS}/ProcesoGenerador/obj/generador.o"

g++ -L"${PATH_PROYECTOS}/IPC" -L"${PATH_PROYECTOS}/Comun" -o "${RUTA_RAIZ}/bin/generador"  "${PATH_PROYECTOS}/ProcesoGenerador/obj/generador.o" -lComun -ljsoncpp -lIPC

#Compilacion Administrador
mkdir -p "${PATH_PROYECTOS}/ProcesoAdministrador/obj"

g++ -O2 -c -Wno-unused-result -I"${PATH_PROYECTOS}/IPC/src" -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoAdministrador/src/Administrador.cpp" -o "${PATH_PROYECTOS}/ProcesoAdministrador/obj/Administrador.o"
g++ -O2 -c -I"${PATH_PROYECTOS}/IPC/src" -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoAdministrador/src/admin.cpp" -o "${PATH_PROYECTOS}/ProcesoAdministrador/obj/admin.o"

g++ -L"${PATH_PROYECTOS}/IPC" -L"${PATH_PROYECTOS}/Comun" -o "${RUTA_RAIZ}/bin/administrador"  "${PATH_PROYECTOS}/ProcesoAdministrador/obj/Administrador.o" "${PATH_PROYECTOS}/ProcesoAdministrador/obj/admin.o" -lComun -lIPC

#Compilacion Lanzador
mkdir -p "${PATH_PROYECTOS}/ProcesoLanzador/obj"

g++ -O2 -c -Wno-unused-result -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoLanzador/src/Configuracion.cpp" -o "${PATH_PROYECTOS}/ProcesoLanzador/obj/Configuracion.o"
g++ -O2 -c -Wno-unused-result -I"${PATH_PROYECTOS}/Comun/src" "${PATH_PROYECTOS}/ProcesoLanzador/src/lanzador.cpp" -o "${PATH_PROYECTOS}/ProcesoLanzador/obj/lanzador.o"
 
g++ -L"${PATH_PROYECTOS}/Comun" -o "${RUTA_RAIZ}/bin/lanzador" "${PATH_PROYECTOS}/ProcesoLanzador/obj/Configuracion.o" "${PATH_PROYECTOS}/ProcesoLanzador/obj/lanzador.o" -lComun

echo "> Instalación exitosa"
