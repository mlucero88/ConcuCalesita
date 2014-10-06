#ifndef BYTESTREAM_H
#define	BYTESTREAM_H

#include <cstddef>

/**
 * @brief Clase contenedora para una secuencia de bytes, utilizada para el
 * envio y recepcion de datos a traves de un socket, a una seccion de memoria
 * compartida, escritura y lectura en un archivo, etc.
 */

typedef char byte_t;

class ByteStream {
public:

	/**
	 * @brief Construye un ByteStream con capacidad @a capacidad
	 * @param capacidad Capacidad del stream, en bytes
	 */
	explicit ByteStream(size_t capacidad = 0);

	/**
	 * @brief Construye un ByteStream a partir de una copia de los datos
	 * apuntados por @a stream, cuyo tamanio es @a tamanio. La capacidad del
	 * objeto creado es @a tamanio
	 * @param stream Puntero a los datos que se guardaran en la instancia
	 * creada
	 * @param tamanio Tamanio total de los datos apuntados por @a stream en
	 * bytes
	 */
	ByteStream(const byte_t* stream, size_t tamanio);

	/**
	 * @brief Constuctor copia
	 * @param aCopiar Instancia a copiar
	 */
	ByteStream(const ByteStream& aCopiar);

	/**
	 * @brief Metodo que elimina el contenido previo y le asigna una copia de
	 * los datos apuntados por @a stream, cuyo tamanio es @a tamanio. La
	 * capacidad del objeto sera @a tamanio si su capacidad previa era menor a
	 * @a tamanio, o se mantendra con la misma capacidad si era mayor o igual
	 * @param stream Puntero a los datos que se guardaran en la instancia
	 * @param tamanio Tamanio total de los datos apuntados por @ stream en bytes
	 */
	void asignarStream(const byte_t* stream, size_t tamanio);

	/**
	 * @brief Metodo para redimensionar la capacidad del stream. Los datos se
	 * conservan. En caso de que @a nuevaCapacidad sea menor al tamanio ocupado
	 * en el stream, el stream queda en estado lleno y los datos que quedaron
	 * afuera de la capacidad se pierden
	 * @param nuevaCapacidad Tamanio nuevo del stream
	 */
	void redimensionar(size_t nuevaCapacidad);

	/**
	 * @brief Metodo para insertar datos al final del stream (es decir, desde
	 * la ultima posicion en donde se escribio). Si el stream no tiene
	 * suficiente capacidad libre, se redimensiona para poder insertar el nuevo
	 * dato
	 * @param dato Puntero a los datos a insertar
	 * @param tamanioDato Tamanio de los datos a insertar
	 */
	void insertarDatos(const void* dato, size_t tamanioDato);

	/**
	 * @brief Metodo que vacia los datos del stream
	 */
	void vaciarStream();

	/**
	 * @brief Metodo que obtiene el stream para consulta, no modificacion
	 * @return Puntero a los datos guardados en el stream
	 */
	const byte_t* obtenerStream() const;

	/**
	 * @brief Metodo para obtener el tamanio ocupado
	 * @return El tamanio ocupado, en bytes
	 */
	size_t getTamanioOcupado() const;

	/**
	 * @brief Metodo para obtener la capacidad maxima
	 * @return La capacidad maxima, en bytes
	 */
	size_t getCapacidadTotal() const;

	/**
	 * @brief Metodo para obtener la capacidad restante
	 * @return La capacidad restante, en bytes
	 */
	size_t getCapacidadRestante() const;

	/**
	 * @brief Metodo para consultar si el stream esta lleno
	 * @return <tt>true</tt> si el stream esta lleno
	 */
	bool estaLleno() const;

	ByteStream& operator=(const ByteStream& aCopiar);

	/**
	 * @brief Destructor
	 */
	~ByteStream();

private:

	byte_t *stream;
	size_t capacidad, tamanio;

	void copiar(const ByteStream& aCopiar);
};

#endif
