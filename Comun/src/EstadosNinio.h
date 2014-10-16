#ifndef ESTADOS_NINIO_H
#define ESTADOS_NINIO_H

enum Estado {
	NACE = -1,				// Estado inicial. No se loguea
	EN_COLA_BOLETERIA = 0,
	COMPRA_BOLETO = 1,
	EN_COLA_CALESITA = 2,
	ENTRA_CALESITA = 3,
	SALE_CALESITA = 4
};

#endif
