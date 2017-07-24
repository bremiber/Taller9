#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<netdb.h>

#define BUFLEN 128 
#define QLEN 10 

#ifndef HOST_NAME_MAX 
#define HOST_NAME_MAX 256 
#endif	

int main(int argc, char **argv){

  	int conexion_servidor, conexion_cliente,n;
	char *host; 

	if(argc == 1){
		printf("Uso: ./servidor <ip> <numero de puerto>\n");
		exit(-1);
	}

	if(argc != 3){
		printf( "Por favor especificar un numero ip y de puerto\n");
	}
	
	int puerto = atoi(argv[2]);
	
	if (( n = sysconf(_SC_HOST_NAME_MAX)) < 0) 		
		n = HOST_NAME_MAX; /* best guess */ 
	if ((host = malloc(n)) == NULL) 
		printf(" malloc error"); 
	if (gethostname( host, n) < 0) 		//Obtenemos nombre del host
		printf(" gethostname error"); 

	printf("\nNombre del host: %s\n", host);	//Mostramos nuestro nombre

  socklen_t longc; //Debemos declarar una variable que contendrá la longitud de la estructura
  struct sockaddr_in servidor, cliente;
  char buffer[BUFLEN]; //Declaramos una variable que contendrá los mensajes que recibamos
  puerto = atoi(argv[2]);
  conexion_servidor = socket(AF_INET, SOCK_STREAM, 0); //creamos el socket
  bzero((char *)&servidor, sizeof(servidor)); //llenamos la estructura de 0's
  servidor.sin_family = AF_INET; //asignamos a la estructura
  servidor.sin_port = htons(puerto);
  servidor.sin_addr.s_addr = INADDR_ANY; //especifica nuestra dirección
  if(bind(conexion_servidor, (struct sockaddr *)&servidor, sizeof(servidor)) < 0)
  { //asignamos un puerto al socket
    printf("Error al asociar el puerto a la conexion\n");
    close(conexion_servidor);
    return 1;
  }
  listen(conexion_servidor, 3); //Estamos a la escucha
  printf("A la escucha en el puerto %d\n", ntohs(servidor.sin_port));
  longc = sizeof(cliente); //Asignamos el tamaño de la estructura a esta variable
  conexion_cliente = accept(conexion_servidor, (struct sockaddr *)&cliente, &longc); //Esperamos una conexion
  if(conexion_cliente<0)
  {
    printf("Error al aceptar trafico\n");
    close(conexion_servidor);
    return 1;
  }
  if(recv(conexion_cliente, buffer, 100, 0)<0)
  { //Comenzamos a recibir datos del cliente
    //Si recv() recibe 0 el cliente ha cerrado la conexion. Si es menor que 0 ha habido algún error.
    printf("Error al recibir los datos\n");
    close(conexion_servidor);
    return 1;
  }
  else
  {
    printf("get %s\n",buffer);
	FILE *fp;
	fp = fopen(buffer,"r");        
	if (fp==NULL) {
	fputs ("El archivo no existe",stderr); 
	exit (1);
	}
	else{
	printf("El archivo se esta enviando al cliente...\n");
	}
    
    //printf("Se ha enviado el archivo al cliente");
    bzero((char *)&buffer, sizeof(buffer));
    send(conexion_cliente,fp,100,0);
	fclose(fp);
  }
  close(conexion_servidor);
  return 0;
}
