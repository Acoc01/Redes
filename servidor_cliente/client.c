#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main() {
    /*Variable que setea el nombre del servidor*/
	const char* server_name = "localhost";
    /*Variable que setea el puerto que utilizara el servidor*/
	const int server_port = 8877;
    /*Linea que crea la estructura sockaddr_in de nombre
     * server_address, inicializan sus arreglos y variables en 0
     * utilizando memset.
     * Luego se indica que la direccion para el socket
     * de transporte debe ser AF_INET, la IP.*/
	struct sockaddr_in server_address;
	memset(&server_address, 0, sizeof(server_address));
	server_address.sin_family = AF_INET;

	// creates binary representation of server name
	// and stores it as sin_addr
	// http://beej.us/guide/bgnet/output/html/multipage/inet_ntopman.html
    // Convierte la direccion a su formato de texto estandar.
    // Se pasa por parametro la direccion para el socket de transporte
    // luego el argumento siguiente es la fuente y el tercero el destino.
    // Es decir convierte localhost en binario y lo guarda en sin_addr
	inet_pton(AF_INET, server_name, &server_address.sin_addr);

	// htons: port in network order format
    // Transforma un entero a un formato de red.
	server_address.sin_port = htons(server_port);

	// open a stream socket
	int sock;
    //La funcion socket crea un nuevo socket, devuelve un entero
    //que es nuestro socket.
    //Tiene por parametros el dominio, que en este caso es PF_INET
    //que es un packete del tipo IP,TCP/IP o UDP/IP
    //El segundo parametro es el tipo de socket que queremos
    //En este caso se indica que queremos un SOCK_STREAM
    //que se utiliza para crear una transmision TCP/IP
    //Y el ultimo parametro es el protocolo que se indica como default.
	if ((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
		printf("could not create socket\n");
		return 1;
        //Si el valor es menor que 0 entonces no se pudo crear el socket
	}

	// TCP is connection oriented, a reliable connection
	// **must** be established before any data is exchanged
    // Aqui se crea la coneccion entre dos hosts utilizando el
    // socket creado anteriormente, se especifica la direccion al 
    // host de destino mediante un puntero a sockaddr
    // Y se indica igual el tamanio de la estructura.
    // Si el retorno es menor a 0 quiere decir que no hubo conexion
	if (connect(sock, (struct sockaddr*)&server_address,
	            sizeof(server_address)) < 0) {
		printf("could not connect to server\n");
		return 1;
	}

	// send

	// data that will be sent to the server
    // Se crea la informacion que se va a enviar al otro host
	const char* data_to_send = "Gangadhar Hi Shaktimaan hai";
    /*Funcion que inicia la transmision del mensaje
     * El primer argumento es el socket por el cual se realizara la 
     * transmision.
     * El segundo argumento es el buffer conteniendo el mensaje a enviar
     * El tercer argumento es el largo del mensaje a enviar.
     * El ultimo argumento es la bandera indicando el tipo
     * de mensaje que sera transmitido, en este caso es un mensaje
     * estandar con flag 0.*/
	send(sock, data_to_send, strlen(data_to_send), 0);

	// receive

	int n = 0; //variable que guarda el retorno de recv
	int len = 0, maxlen = 100; //tamanio actual y maximo del mensaje
	char buffer[maxlen];//Buffer donde se guarda el mensaje
	char* pbuffer = buffer;//Puntero a la posicion inicial del buffer

	// will remain open until the server terminates the connection
    /*La funcion recv recibe el mensaje enviado
     * nuevamente el primer parametro es el socket por el cual
     * ocurrira la comunicacion
     * pbuffer es el puntero al inicio del buffer
     * maxlen es la maxima longitud del mensaje
     * finalmente 0 es una flag para un mensaje estandar*/
	while ((n = recv(sock, pbuffer, maxlen, 0)) > 0) {
		pbuffer += n;//Mueve el puntero a la posicion n
		maxlen -= n;//Le resta a maxlen el largo del mensaje
		len += n;//Se guarda la longitud del mensaje

		buffer[len] = '\0';//Se agrega el termino de string
		printf("received: '%s'\n", buffer);
	}

	// close the socket
    // Simplemente cierra la comunicacion una vez no hay mas mensajes.
	close(sock);
	return 0;
}
