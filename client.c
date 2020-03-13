#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>
#include <arpa/inet.h>
#include <iostream>
using namespace std;


/* codul de eroare returnat de anumite apeluri */
extern int errno;
/* portul de conectare la server*/
int port;
char A[12][12];

void TransformBack(char A[12][12], char text[145])
{
	int i, j, k = 0;
	for(i = 0; i <= 11; i++)
		for(j = 0; j <= 11; j++)
			A[i][j] = text[k++];
}

void Afisare(char A[12][12])
{
	int i, j;
	for(i = 0; i <= 11; i++)
	{
		for(j = 0; j <= 11; j++)
			cout << A[i][j] << " ";
		cout << endl;
	}
}

int main (int argc, char *argv[])
{
  int sd;			// descriptorul de socket
  struct sockaddr_in server;	// structura folosita pentru conectare 
  char msg[100];		// mesajul trimis
 
  /* exista toate argumentele in linia de comanda? */
  if (argc != 3)
    {
      printf ("[client] Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  /* stabilim portul */
  port = atoi (argv[2]);

  /* cream socketul */
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[client] Eroare la socket().\n");
      return errno;
    }
  

  /* umplem structura folosita pentru realizarea conexiunii cu serverul */
  /* familia socket-ului */
  server.sin_family = AF_INET;
  /* adresa IP a serverului */
  server.sin_addr.s_addr = inet_addr(argv[1]);
  /* portul de conectare */
  server.sin_port = htons (port);
  
  /* ne conectam la server */
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }
	
   bzero (msg, 100); 
   while(1){
   printf ("[client] Alegeti cu ce culoare doriti sa jucati( A=albastru, G=galben, R=rosu, V=verde: ");
   fflush (stdout);   
   read (0, msg, 100);

	if(write(sd, msg, 1) <= 0){
		perror("[client] Eroare la write() spre server. \n");
		return errno;
	}
	
	bzero(msg, 100);
	if(read(sd, msg, 100) < 0){
		perror("[client]Eroare la write() spre server. \n");
		return errno;
	}
	
	 if(strstr(msg, "ales"))
	 {
		cout<<msg << endl;
	    break;
	 }
	 else cout << msg << endl;
	
   }

	int ok = 0;   
   while(1){
	   char text[145];
	   strcpy(text, "");
	   read(sd, text, 144);
	   text[strlen(text)] = 0;
	   TransformBack(A, text);
	   Afisare(A);

   char mesaj[100];
   bzero(mesaj, 100);
   printf ("[client] Alegeti pionul:");
   fflush (stdout);   
   read (0, mesaj, 100);
   //cout << mesaj << endl;
   

  /* trimiterea mesajului la server */
  if (write (sd, mesaj, 100) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
 
   if(strcmp(mesaj,"quit\n")==0)  break;
  /* citirea raspunsului dat de server 
     (apel blocant pina cind serverul raspunde) */
  
  bzero(mesaj, 100);
  if (read (sd, mesaj, 100) < 0)
    {
      perror ("[client]Eroare la read() de la server.\n");
      return errno;
    }
  /* afisam mesajul primit */
  	printf ("[client]Mesajul primit este: %s\n", mesaj);
	}
  /* inchidem conexiunea, am terminat */
  close (sd);
}

