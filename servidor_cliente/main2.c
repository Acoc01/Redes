#include "tcp.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main() {
  const char *server_name = "localhost";
  const int server_port = 8877;
  struct tcp_client_t cliente;
  memset(&cliente.server_addr, 0, sizeof(cliente.server_addr));
  tcp_client_connect(&cliente, server_name, server_port);
  printf("Ingrese el nombre del archivo a enviar: \n");
  struct file_data_t file;
  scanf("%s", file.name);

  FILE *fp;
  fopen(file.name, "r");
  fseek(fp, 0L, SEEK_END);
  size_t tam;
  tam = ftell(fp);
  file.size = tam;
  rewind(fp);

  tcp_send(cliente.sock, fp, tam);
  tcp_close(cliente.sock);
  return 0;
}
