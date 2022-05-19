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
    int sock;
    char buffer[1024];
    sock =
        tcp_server_accept(&server_address, &client_address, &client_addr_len);
    tcp_recv(sock, &buffer, 1024);
  }

  return 0;
}
