#include "tcp.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  // Como el cliente envia el archivo al servidor
  /* struct file_data_t data;
   strcpy(data.name, "archivo.txt");
   data.size = 500;

   tcp_send(sock, &data, sizeof data));*/

  // Se inicia el servidor
  // Se define el puerto del servidor
  int SERVER_PORT = 8877;
  // Se crea la estructura desde tcp.h
  struct tcp_server_t server_address;
  // Se inicializa la estructura con memset
  memset(&server_address, 0, sizeof(server_address));
  // Se crea el servidor y el socket con la funcion tcp_server_create
  tcp_server_create(&server_address, SERVER_PORT);

  struct sockaddr_in client_address;
  socklen_t client_addr_len = 0;

  while (true) {
    tcp_server_accept(&server_address, &client_address, &client_addr_len);
  }

  // Archivos van al cliente
  FILE *fp;

  // abres el archivo

  // Se declara el tam total del archivo
  size_t tam;
  // Se utiliza fseek para encontrar el final
  // del archivo.
  fseek(fp, 0L, SEEK_END);
  // Una vez el puntero esta en el final podemos
  // decir la posicion y nos guardamos el tamanio del archivo
  // Ya que la posicion nos indica el tamanio total del archivo
  // porque estamos al final
  tam = ftell(fp);
  // Luego volvemos fp al inicio con rewind
  rewind(fp);
  // Dentro del while lo que recibe por el buffer
  // lo escribo en un nuevo archivo.

  return 0;
}
