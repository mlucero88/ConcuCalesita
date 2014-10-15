#ifndef ESTADOS_NINIO_H
#define ESTADOS_NINIO_H

// todo agregar estado o lo que sea que indique: "intento de sentarse en ubicacion X" y "se sento en lugar X"
// igual la ubicacion no la da el estado, eso lo sabe la calesita cuando loguea. pensarlo...
// el estado COLA_SALIDA no lo voy a usar. Los pibes, cuando termina la calesita, la calesita los saca de a uno por vez
// y loguea que el pibe salio (sin pasar por COLA_SALIDA
enum Estado {
	COLA_BOLETERIA = 0,
	COLA_CALESITA = 1,
	EN_CALESITA = 2,
	COLA_SALIDA = 3,
	SALIO = 4
};

#endif
