#include "tcp.h"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

void tcp_server_create(struct tcp_server_t *server, int port) {
    // Crear socket de escucha (se guarda en server->listen_sock)

    // Bindear socket a puerto

    // Escuchar conexiones entrantes
}

int tcp_server_accept(struct tcp_server_t *server,
                      struct sockaddr_in *client_addr) {
    // Aceptar primera conexion entrante (guardar dirección del cliente en
    // client_addr)

    // Retorna descriptor de archivo del socket de comunicación con el cliente
}

void tcp_client_connect(struct tcp_client_t *client, const char *host,
                        int port) {
    // Crear socket de cliente (se guarda en client->sock)
    client->server_addr.sin_family = AF_INET;
    inet_pton(AF_INET, host, &client->server_addr.sin_addr);
    client->server_addr.sin_port = htons(port);

    int sock;
    if((sock = socket(PF_INET, SOCK_STREAM, 0)) < 0){
      printf("No se pudo crear socket\n");
    }
    client->sock = sock;

    // Conectar con host y puerto indicados (se guarda en client->server_addr y
    // se usa en llamada a connect())
    if(connect(sock, (struct sockaddr*)&client->server_addr, 
        sizeof(client->server_addr)) < 0){
      printf("No se pudo establecer conexion al servidor \n");
    }
}

void tcp_send(int sock, const void *data, size_t size) {
}

void tcp_recv(int sock, void *data, size_t size) {
}

void tcp_close(int sock) {
    close(sock);
}
