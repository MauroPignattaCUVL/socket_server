#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>

int main(int argc, char** argv) {
	//estructura con datos del server
    struct sockaddr_in dirServer;
    dirServer.sin_family = AF_INET;
    dirServer.sin_addr.s_addr = INADDR_ANY;
    dirServer.sin_port = htons(8080);
    
	//crea socket 
    int client = socket(AF_INET, SOCK_STREAM, 0);
	
    // verifica que se haya podido conectar
    if (connect(client, (void *) &dirServer, sizeof(dirServer)) != 0 )
    {
        perror("No se pudo conectar con el servidor");
        return 1;
    }
	
    //recibe un mensaje de bienvenida del servidor
    char mensaje[256];
    recv(client, &mensaje, sizeof(mensaje), 0 );
    puts(mensaje);
    
	//envia mensajes al servidor
    while(1)
    {
        fgets(mensaje,sizeof(mensaje),stdin);
        send (client, mensaje, strlen(mensaje), 0);
    }
    
	close(client);
    return (EXIT_SUCCESS);
}

