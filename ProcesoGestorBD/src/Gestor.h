#ifndef GESTOR_H_
#define GESTOR_H_

#include "ProtocoloGestor.h"
#include <vector>

/**
 * @brief Clase utilizada por el gestor para comunicarse con el cliente. Maneja
 * internamente una cola de mensajes. Persiste en un archivo al destruirse.
 */
class Gestor {
public:

	/**
	 * @brief Constructor que instancia una cola de mensajes que usara el
	 * gestor. En caso de que @a nombreArchivoTabla sea un archivo existente
	 * creado por esta clase al destruirse, se cargaran los registros
	 * contenidos en dicho archivo
	 * @pre El archivo @a nombreArchivoCola debe existir
	 * @param nombreArchivoTabla Nombre del archivo utilizado para cargar y/o
	 * persisitir la base de datos
	 * @param nombreArchivoCola Nombre de archivo utilizado para iniciar el
	 * gestor
	 * @param caracter Caracter utilizado para iniciar el gestor
	 * @throw std::string Error al crear la cola de mensajes
	 */
	Gestor(const std::string& nombreArchivoTabla,
			const std::string& nombreArchivoCola,
			char caracter) /* throw (std::string) */;

	/**
	 * @brief Destructor. Persiste la base de datos
	 */
	~Gestor();

	/**
	 * @brief Metodo que atiende la siguiente solicitud en la cola
	 * @note En caso de no haber una solicitud pendiente, el metodo se
	 * bloquea hasta recibir una solicitud o una interrupcion
	 */
	void atenderSolicitud();

private:

	void cargarTabla();
	void persistirTabla() const;
	bool agregarRegistro(const Registro& registro);

	const Registro* buscarRegistroPorNombre(const std::string& nombre) const;

	std::vector< Registro > tabla;
	ProtocoloGestor protocolo;
	std::string nombreArchivoTabla;
};

#endif
