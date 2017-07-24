#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<netdb.h>
int copy_file(char* f_org,char* f_dest); 
int main(int argc, char **argv){

  if(argc == 1){
		printf("Uso: ./cliente <ip> <puerto> <ruta> <archivo>\n");
		exit(-1);
	}

	if(argc != 5){
		printf( "por favor especificar los campos necesarios\n");
	
	}

	int puerto = atoi(argv[2]);
	char *guardar,*aux;
	guardar=argv[3];
	aux=argv[4];

  struct sockaddr_in cliente; //Declaración de la estructura con información para la conexión
  struct hostent *servidor; //Declaración de la estructura con información del host
  servidor = gethostbyname(argv[1]); //Asignacion
  if(servidor == NULL)
  { 
    printf("Host erróneo\n");
    return 1;
  }
  int  conexion;
  char buffer[100];
  conexion = socket(AF_INET, SOCK_STREAM, 0); //Asignación del socket
  puerto=(atoi(argv[2])); //conversion del argumento
  bzero((char *)&cliente, sizeof((char *)&cliente)); //Rellena toda la estructura de 0's
<<<<<<< HEAD
=======
        //La función bzero() es como memset() pero inicializando a 0 todas la variables
>>>>>>> 03dbb4375ddcdd02673e0b3c1240e80efaa4dae1
  cliente.sin_family = AF_INET;
  cliente.sin_port = htons(puerto);
  bcopy((char *)servidor->h_addr, (char *)&cliente.sin_addr.s_addr, sizeof(servidor->h_length));
  //bcopy(); copia los datos del primer elemento en el segundo con el tamaño máximo 
  //del tercer argumento.

<<<<<<< HEAD
  if(connect(conexion,(struct sockaddr *)&cliente,sizeof(cliente)) < 0)
=======
  if(connect(conexion,(struct sockaddr *)&cliente, sizeof(cliente)) < 0)
>>>>>>> 03dbb4375ddcdd02673e0b3c1240e80efaa4dae1
  { //conectando con el host
    printf("Error conectando con el host\n");
    close(conexion);
    return 1;
  }
	
  printf("Conectado con %s:%d\n",inet_ntoa(cliente.sin_addr),htons(cliente.sin_port));
<<<<<<< HEAD
  send(conexion,guardar,100, 0); //envio
  bzero(buffer,100);

  FILE *archivo,*archivo2;
  recv(conexion,archivo,100, 0); //recepción

    
    int data1 =0;
    archivo=fopen(guardar,"r");
    archivo2 = fopen (aux,"w");
    
    while ( (data1 = fgetc (archivo)) != EOF ) {
        fputc (data1,archivo2);
    }
    
    fclose (archivo);
    fclose (archivo2);
    

  printf("\nDescargando archivo y guardandolo en %s \n",aux);

=======
  send(conexion,guardar, 100, 0); //envio
  bzero(buffer, 100);
  recv(conexion, buffer, 100, 0); //recepción
  printf("%s", buffer);
>>>>>>> 03dbb4375ddcdd02673e0b3c1240e80efaa4dae1
return 0;
}
