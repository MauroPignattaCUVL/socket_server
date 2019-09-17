#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char** argv) {
	
    //estructura que contiene datos del servidor 
    struct sockaddr_in dirServer;
    dirServer.sin_family = AF_INET;
    dirServer.sin_addr.s_addr = INADDR_ANY;
    dirServer.sin_port = htons(8080);
	
    char msjServer[256]= "Bienvenido al servidor";
	
    //crea el socket
    int server = socket(AF_INET, SOCK_STREAM, 0);
	
    //libera el socket al cerrar la aplicacion
    int activado = 1;
    setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &activado, sizeof(activado));
   
    //comprobar error
    if ( bind(server, (void*) &dirServer,sizeof (dirServer)) != 0)
    {
        perror("Error de conexion");
        return 1;
    }
    
    puts("Escuchando...");
    listen(server, 100);
    
    //-------------------------------------------------------------------------
    
    // Aceptar conexion y enviar msj bienvenida 
    int client = accept(server, (void*) 0, 0 );
    puts("Conexion realizada con exito");
    send(client, msjServer, sizeof(msjServer), 0);
    
    //--------------------------------------------------------------------------
    
    while (1)
    {
        memset(msjServer,'\0',sizeof(msjServer));
        recv(client, msjServer, sizeof(msjServer), 0 );
        printf("%s",msjServer);
    }
    
	close(server);
    return (EXIT_SUCCESS);
}

