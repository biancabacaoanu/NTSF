#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h> 
#include <netinet/in.h>
#include <unistd.h> 
#include <errno.h> 
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h> 
#include <iostream>
#include <time.h>
using namespace std;
char A[12][12];

/* portul folosit */

#define PORT 2728

extern int errno; /* eroarea returnata de unele apeluri */

/* functie de convertire a adresei IP a clientului in sir de caractere */
char * conv_addr(struct sockaddr_in address) {
  static char str[25];
  char port[7];

  /* adresa IP a clientului */
  strcpy(str, inet_ntoa(address.sin_addr));
  /* portul utilizat de client */
  bzero(port, 7);
  sprintf(port, ":%d", ntohs(address.sin_port));
  strcat(str, port);
  return (str);
}
int linie[4]={4,1,11,8};
int coloana[4]={1,8,4,11};
int Bazal[4]={1,1,10,10};
int Bazac[4]={1,10,1,10};
int Finall[4]={6,1,6,11};
int Finalc[4]={1,6,11,6};

void matrice(char A[12][12]) {
  int i, j;
  
  for(j = 1; j <= 11; j++)
	  A[0][j] = 'a' - 1 + j;
  
  for (i = 1; i <= 11; i++)
    for (j = 1; j <= 11; j++) A[i][j] = ' ';
  for (int i = 1; i <= 11; i++)
    for (int j = 1; j <= 11; j++) {
      if (i == 6 && (j < 6 && j > 1)) A[i][j] = '-';
      else if (i == 6 && (j > 6 && j < 11)) A[i][j] = '-';
      else if ((i < 6 && j > 1) && j == 6) A[i][j] = '-';
      else if ((i > 6 && i < 11) && j == 6) A[i][j] = '-';
      else if (i > 4 && i < 8) {
        A[i][1] = 'P';
        A[i][11] = 'P';
      } else if (j > 4 && j < 8) {
        A[1][j] = 'P';
        A[11][j] = 'P';
      } else if (j < 5 || j > 7) {
        A[4][j] = 'P';
        A[8][j] = 'P';
        A[j][4] = 'P';
        A[j][8] = 'P';
      } else A[i][j] = '-';
    }
    


  A[1][1] = '*';
  A[1][2] = '*';
  A[2][1] = '*';
  A[2][2] = '*';
  A[10][1] = '*';
  A[10][2] = '*';
  A[11][1] = '*';
  A[11][2] = '*';
  A[1][10] = '*';
  A[1][11] = '*';
  A[2][10] = '*';
  A[2][11] = '*';
  A[10][10] = '*';
  A[10][11] = '*';
  A[11][10] = '*';
  A[11][11] = '*';
  A[4][1]='0'; 
  A[1][8]='0';
  A[11][4]='0';
  A[8][11]='0';
  A[0][0] = '*';
  for(i = 1; i <= 11; i++)
      A[i][0] = 'a' + i - 1;
}

void Transformare(char text[256], char A[12][12]){
	int k = 0, i, j;
	strcpy(text, "");
	for(i = 0; i <= 11; i++)
		for(j = 0; j <= 11; j++)
			text[k++] = A[i][j];

	text[k] = 0;
}

int litera(char x){
	int a = x;
	if(a >= 97 && a <= 108) return 1;
	return 0;
}
 
 void sus(int &linie, int &coloana, int &valoare, int Finall, int Finalc){
 int i = linie - 1, j = coloana, v = valoare - 1;
	while((A[i][j]=='P' || A[i][j]=='0') && v>0 && A[i - 1][j] != ' ' && (i - 1) != 0){
		if(i==Finall && j==Finalc){
			v=0;
            break;
		}
		i--;
		v--;
    }
	linie = i, coloana = j, valoare = v;
	cout << linie << " " << coloana << " " << valoare << endl;
}

 void jos(int &linie, int &coloana, int &valoare, int Finall, int Finalc){
	int i = linie + 1, j = coloana, v = valoare - 1;
	while((A[i][j]=='P' || A[i][j]=='0') && v>0 && A[i + 1][j] != ' ' && (i + 1) != 12){
		if(i==Finall && j==Finalc){
			v=0;
            break;
		}
		i++;
		v--;
    }
	linie = i, coloana = j, valoare = v;
	cout << linie << " " << coloana << " " << valoare << endl;
}

 void stanga(int &linie, int &coloana, int &valoare,int Finall,int Finalc){
	int i = linie, j = coloana - 1, v = valoare - 1;
	while((A[i][j]=='P' || A[i][j]=='0') && v>0 && A[i][j - 1] != ' ' && j - 1 != 0){
		if(i==Finall && j==Finalc){
			v=0;
            break;
		}
		j--;
		v--;
    }
	linie = i, coloana = j, valoare = v;
	cout << linie << " " << coloana << " " << valoare << endl;
}
 void dreapta(int &linie,int &coloana,int &valoare, int Finall, int Finalc){
	int i = linie, j = coloana + 1, v = valoare - 1;
	while((A[i][j]=='P' || A[i][j]=='0') && v>0 && A[i][j + 1] != ' ' && (j + 1) != 12){
		if(i==Finall && j==Finalc){
			v=0;
            break;
		}
		j++;
		v--;
    }
	linie = i, coloana = j, valoare = v;
	cout << linie << " " << coloana << " " << valoare << endl;
}


 void Deplasare(char A[][12], int x, int y, int valoare,char culoare, int lin,int col){
	int linie = x, coloana = y;     
	while(valoare>0){
		cout << linie << " " << coloana << " " << valoare << endl;
        if(linie==4 && (coloana>=1 && coloana<4)) dreapta(linie,coloana,valoare,lin,col);
		else if((linie>1 && linie<=4) && coloana==4) sus(linie, coloana,valoare,lin,col);
		else if(linie==1 && (coloana>=4 && coloana<8)) dreapta(linie, coloana, valoare,lin,col);
		else if((linie>=1 && linie<4) && coloana==8) jos(linie,coloana, valoare,lin,col);
		else if(linie==4 && (coloana>=8 && coloana<11)) dreapta( linie, coloana, valoare,lin,col);
		else if((linie>=4 && linie<8) && coloana==11) jos(linie, coloana, valoare,lin,col);
		else if(linie==8 && (coloana<=11 && coloana>8)) stanga(linie,coloana, valoare,lin,col);
		else if((linie>=8 && linie<11) && coloana==8) jos(linie, coloana, valoare,lin,col);
		else if(linie==11 && (coloana<=8 && coloana>4)) stanga(linie,coloana, valoare,lin,col);
		else if((linie<=11 && linie>8) && coloana==4) sus(linie, coloana, valoare,lin,col);
		else if(linie==8 && (coloana>1 && coloana<=4)) stanga(linie, coloana, valoare,lin,col);
		else if((linie<=8 && linie>=4) && coloana==1) sus(linie, coloana, valoare,lin,col);
	}
	if(x==lin && y==col){
		A[x][y]='0';
		A[linie][coloana]=culoare;
	}
    else { A[x][y]='P';
		A[linie][coloana]=culoare;
	}
}

int NTSF(int fd, int valoare, char culoare,int linie,int coloana,int Bazal,int Bazac) {
  int bytes; /* numarul de octeti cititi/scrisi */
  char msg[100]; //mesajul primit de la client 
  char msgrasp[100] = " "; //mesaj de raspuns pentru client
  bzero(msg, 100);
  bytes = read(fd, msg, 100);
  if (bytes < 0) {
    perror("Eroare la read() de la client.\n");
    return 0;
  }
	int x = 0, y = 0, i;
	for(i = 0; msg[i]; i++)
		if(litera(msg[i]))
			if(x == 0) x = int(msg[i]) - 96;
			else if(y == 0) y = int(msg[i]) - 96;
	
	cout << valoare << endl;
	cout << x << " " << y << endl;
	cout << Bazal << " " << Bazac << endl;
	if(A[x][y] != culoare){
		bzero(msg, 100);
		strcpy(msg, "Aceasta piesa nu iti apartine!");
		bytes = strlen(msg);
		if(write(fd, msg, bytes) < 0){
			perror("[server] Eroare la write() catre client.\n");
			return 0;
		}
		return 0;
	}
    else if (valoare==6 && A[linie][coloana]=='0' &&((x!=Bazal && y!=Bazac)&&(x!=Bazal && y!=Bazac+1)&&(x!=Bazal+1 && y!=Bazac)&&(x!=Bazal+1 && y!=Bazac+1))){
		bzero(msg,100);
		strcpy(msg,"Trebuie sa alegeti un pion din baza, alegeti alt pion!");
		bytes=strlen(msg);
		if(write(fd, msg, bytes) < 0){
			perror("[server] Eroare la write() catre client.\n");
			return 0;
		}
		return 0;
	}
    else if(valoare==6 && A[linie][coloana]=='0' &&((x==Bazal && y==Bazac)||(x==Bazal && y==Bazac+1)||(x==Bazal+1 && y==Bazac)||(x==Bazal+1 && y==Bazac+1))){
		A[linie][coloana]=culoare;
		A[x][y]='*';
		bzero(msg, 100);
		strcpy(msg, "Mutare efectuata!");
		bytes = strlen(msg);
		if(write(fd, msg, bytes) < 0){
			perror("[server] Eroare la write() catre client.\n");
			return 0;
		}
		return bytes;
     }
	else if(valoare < 6 && ((x==Bazal&&y==Bazac)||(x==Bazal && y==Bazac+1)||(x==Bazal+1 && y==Bazac)||(x==Bazal+1 && y==Bazac+1))){
		bzero(msg,100);
		strcpy(msg,"Trebuie sa alegeti un pion din baza, alegeti alt pion!");
		bytes=strlen(msg);
		if(write(fd, msg, bytes) < 0){
			perror("[server] Eroare la write() catre client.\n");
			return 0;
		}
		return 0;
	}
	else if(valoare < 6){ 
		Deplasare(A,x,y,valoare,culoare,linie,coloana);
		bzero(msg, 100);
		strcpy(msg, "Mutare efectuata!");
		bytes = strlen(msg);
		if(write(fd, msg, bytes) < 0){
			perror("[server] Eroare la write() catre client.\n");
			return 0;
		}
		return bytes;
	}
     
  printf("[server]Mesajul a fost receptionat...%s\n", msg);
  /*if (strcmp(msg, "quit\n") == 0) return -1;
  else { //pregatim mesajul de raspuns 
    bzero(msg, 100);

    //printf("[server]Trimitem mesajul inapoi...%s\n", msgrasp);
	strcpy(msg, "Mutare efectuata!");
	bytes = strlen(msg);	
    if (bytes && write(fd, msg, bytes) < 0) {
      perror("[server] Eroare la write() catre client.\n");
      return 0;
    }

    return bytes;
  }*/
}

int zar(){
	srand(time(NULL));
	return rand()%6+1;
}


 void Colorare(char A[12][12],char c){
 int ok = 0, ok1 = 0;
 for(int i=1;i<=11 && !ok;i++)
   for(int j=1;j<=11 && !ok1;j++)
     if(A[i][j]=='*'){
        A[i][j]=c; 
		A[i][j+1]=c;
		A[i+1][j]=c;
		A[i+1][j+1]=c;
		ok = 1;
		ok1 = 1;

     }
}
 

void Afisare(char A[12][12]) {
  for (int i = 0; i <= 11; i++) {
    for (int j = 0; j <= 11; j++)
      cout << A[i][j] << " ";
    cout << endl;
  }
}

/* programul */
int main() {
  struct sockaddr_in server; /* structurile pentru server si clienti */
  struct sockaddr_in from;
  fd_set readfds; /* multimea descriptorilor de citire */
  fd_set actfds; /* multimea descriptorilor activi */
  struct timeval tv; /* structura de timp pentru select() */
  int sd, client; /* descriptori de socket */
  int optval = 1; /* optiune folosita pentru setsockopt()*/
  int fd;
  /* descriptor folosit pentru 
  	   parcurgerea listelor de descriptori */
  int nfds; /* numarul maxim de descriptori */
  unsigned int len; /* lungimea structurii sockaddr_in */
  char c,c1;
  int numar;
  pid_t fiu;
   cout<<"Introduceti numarul de jucatori: ";
  cin>>numar;
  /* creare socket */
  if ((sd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("[server] Eroare la socket().\n");
    return errno;
  }

  /*setam pentru socket optiunea SO_REUSEADDR */
  setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, & optval, sizeof(optval));

  /* pregatim structurile de date */
  bzero( & server, sizeof(server));

  /* umplem structura folosita de server */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = htonl(INADDR_ANY);
  server.sin_port = htons(PORT);

  /* atasam socketul */
  if (bind(sd, (struct sockaddr * ) & server, sizeof(struct sockaddr)) == -1) {
    perror("[server] Eroare la bind().\n");
    return errno;
  }

  /* punem serverul sa asculte daca vin clienti sa se conecteze */
  if (listen(sd, 5) == -1) {
    perror("[server] Eroare la listen().\n");
    return errno;
  }

  /* completam multimea de descriptori de citire */
  FD_ZERO( & actfds); /* initial, multimea este vida */
  FD_SET(sd, & actfds); /* includem in multime socketul creat */

  tv.tv_sec = 1; /* se va astepta un timp de 1 sec. */
  tv.tv_usec = 0;

  /* valoarea maxima a descriptorilor folositi */
  nfds = sd;

  printf("[server] Asteptam la portul %d...\n", PORT);
  fflush(stdout);

  /* servim in mod concurent clientii... */
  int contor=0, joc = 0;
  while (1) {
    /* ajustam multimea descriptorilor activi (efectiv utilizati) */
    bcopy((char * ) & actfds, (char * ) & readfds, sizeof(readfds));

    /* apelul select() */
 
    if (select(nfds + 1, & readfds, NULL, NULL, & tv) < 0) {
      perror("[server] Eroare la select().\n");
      return errno;
    }
    /* vedem daca e pregatit socketul pentru a-i accepta pe clienti */
    if (FD_ISSET(sd, & readfds)) {
      /* pregatirea structurii client */
      len = sizeof(from);
      bzero( & from, sizeof(from));

      /* a venit un client, acceptam conexiunea */ 
     
     client = accept(sd, (struct sockaddr * ) & from, & len);
	
      /* eroare la acceptarea conexiunii de la un client */
      if (client < 0) {
        perror("[server] Eroare la accept().\n");
        continue;
      }
      else if(client>3) contor++;

      if (nfds < client) /* ajusteaza valoarea maximului */
        nfds = client;

      /* includem in lista de descriptori activi si acest socket */
      
      FD_SET(client, & actfds);

      printf("[server] S-a conectat clientul cu descriptorul %d, de la adresa %s.\n", client, conv_addr(from));
  
 						
      fflush(stdout);
  
    }
     if(contor==numar && joc == 0){
		joc = 1;	 	 
		if((fiu = fork()) == 0){
 		 matrice(A);
		 char mesaj[1], msj[256];
		 int v[numar] = {0};
		 int descriptori[numar];
		 int i;
		 for(i = 0; i < numar; i++)
			 descriptori[i] = i + 4;		 
		 int k = 0;
		 char culori[numar];
		 strcpy(culori, "");
		 int nr = 0;
		 while(nr < numar){
		 	int ok = 0;
			while(ok == 0){
				fd = descriptori[nr];
				if( read(fd, mesaj, 1) < 0){
					perror("Eroare la read()!\n");
					return errno;
				}
				mesaj[1] = '\0';
				if(strstr(culori, mesaj) || (mesaj[0] != 'A' && mesaj[0] != 'V' && mesaj[0] != 'R' && mesaj[0] != 'G')){
					strcpy(msj, "Alegeti alta culoare!");
					write(fd, msj, strlen(msj));
				}
				else if(!strstr(culori, mesaj) && (mesaj[0] == 'A' || mesaj[0] == 'V' || mesaj[0] == 'R' || mesaj[0] == 'G')){
					culori[k++] = mesaj[0];
					culori[k] = '\0';
					Colorare(A, culori[k - 1]);
					strcpy(msj, "Ati ales culoarea!");
					write(fd, msj, strlen(msj));
					ok = 1;
				}
			}
			nr++;
			Afisare(A);
			cout << endl;
		
		 }	
		 v[0] = 1;
		 while(1){
			int i, valoare, tura = 0;
			char text[256];
			strcpy(text, "");
			for(i = 0; i < numar && !tura; i++){
				if(v[i] == 1){	
					fd = descriptori[i];
					Transformare(text, A);
					if(write(fd, text, strlen(text)) < 0){
						perror("Eroare la write() catre client");
						return errno;
					}
					valoare = zar();
					
					
					if(NTSF(fd, valoare, culori[i],linie[i],coloana[i],Bazal[i],Bazac[i]) == -1){
						close(fd);
						FD_CLR(fd, &actfds);
					}
					
					if(i < numar && i + 1 != numar){
						v[i] = 0;
						v[i + 1] = 1;
						tura = 1;
					}
					else if(i + 1 == numar){
						v[0] = 1;
						v[i] = 0;
						tura = 1;
					}
					
				}
			}
		 }
	}
	}
 }
  } /* while */

 /* main */
