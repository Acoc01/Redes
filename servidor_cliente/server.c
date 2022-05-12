#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

/**
 * TCP Uses 2 types of sockets, the connection socket and the listen socket.
 * The Goal is to separate the connection phase from the data exchange phase.
 * */

int main(int argc, char *argv[]) {
  // port to start the server on
  int SERVER_PORT = 8877; // Puerto del servidor que escuchara

  // socket address used for the server
  struct sockaddr_in
      server_address; // Se crea la estructura de la direccion del server
  memset(&server_address, 0, sizeof(server_address)); // Se inicializa todo en 0
  server_address.sin_family =
      AF_INET; // Se especifica la familia de direccion AF_INET

  // htons: host to network short: transforms a value in host byte
  // ordering format to a short value in network byte ordering format
  server_address.sin_port =
      htons(SERVER_PORT); // Guarda el puerto en bytes en sin_port

  // htonl: host to network long: same as htons but to long
  // Esto hace que el socket este disponible en cualquier interfaz
  server_address.sin_addr.s_addr = htonl(INADDR_ANY);

  // create a TCP socket, creation returns -1 on failure
  int listen_sock; // Se crea el socket
  // Nuevamente se usa la funcion para crear el socket
  // Nuevamente el primer parametro es la definicion de a que familia
  // de protocolo pertenece el socket, en este caso PF_INET
  // Luego se indica el tipo de socket, SOCK_STREAM se usa para TCP/IP
  // Y finalmente la flag, estandar que es 0.
  if ((listen_sock = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
    printf("could not create listen socket\n");
    return 1;
  }

  // bind it to listen to the incoming connections on the created server
  // address, will return -1 on error
  // Aqui vincula una direccion al socket.
  if ((bind(listen_sock, (struct sockaddr *)&server_address,
            sizeof(server_address))) < 0) {
    printf("could not bind socket\n");
    return 1;
  }

  int wait_size = 16; // maximum number of waiting clients, after which
                      // dropping begins
                      // Numero maximo de clientes conectados simultaneos
  /*La funcion listen prepara al socket para recibir informacion en el futuro
   * se le asigna como primer parametro el socket y de segundo parametro
   * indica cuantas conecciones pendiente puede llegar a tener, en este caso
   * 16*/
  if (listen(listen_sock, wait_size) < 0) {
    printf("could not open socket for listening\n");
    return 1;
  }

  // socket address used to store client address
  struct sockaddr_in
      client_address;         // Se crea un socket para la direccion del cliente
  int client_address_len = 0; // El largo de la direccion del cliente

  // run indefinitely
  while (true) {
    // open a new socket to transmit data per connection
    int sock; // Crea un nuevo socket para transmitir en cada conexion nueva
    /*La funcion accept es para sockets listeners.
     * el primer parametro incluye la descripcion del socket listener
     * la segunda un puntero a la estructura donde se almacenara la direccion
     * del cliente.
     * finalmente el ultimo parametro es un puntero a donde se guarda
     * la longitud de la direccion del cliente*/
    if ((sock = accept(listen_sock, (struct sockaddr *)&client_address,
                       &client_address_len)) < 0) {
      printf("could not open a socket to accept data\n");
      return 1;
    }
    /*Las siguientes lineas son para preparar al socket listener
     * para recibir la informacion de los clientes, es decir
     * los mensajes que enviara el cliente*/
    int n = 0;
    int len = 0, maxlen = 100;
    char buffer[maxlen];
    char *pbuffer = buffer;

    printf(
        "client connected with ip address: %s\n",
        inet_ntoa(client_address.sin_addr)); // inet_ntoa devuelve la direccion.

    // keep running as long as the client keeps the connection open
    while ((n = recv(sock, pbuffer, maxlen, 0)) > 0) {
      pbuffer += n;
      maxlen -= n;
      len += n;
      buffer[len] = '\0';
      printf("received: '%s'\n", buffer);

      // echo received content back
      send(sock, buffer, len, 0);
    }

    close(sock);
  }

  close(listen_sock);
  return 0;
}
