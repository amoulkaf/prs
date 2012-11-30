#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>


int size(char * file)
{
  int fd = open(file, O_RDWR);
  int i = lseek(fd, 0, SEEK_END);
  close(fd);
  return i;
}

void modifiedDate(char * file, char * date)
{
  struct stat b;
  char t[100];
  if(!stat(file, &b)){ 
    strftime(t, 100, "%d/%m/%Y %H:%M:%S", localtime( &b.st_mtime));
  }
  strcpy(date, t);
}

/*fonction qui rajoute un ficher à la fin d'un autre fichier dst*/

void addTo(char * file, char * dst)
{
  int fd1 = open(file, O_RDONLY); 
  int fd2 = open(dst, O_WRONLY | O_CREAT, 0666);
  char c;
  lseek(fd2, 0, SEEK_END);
  while(read(fd1, &c, 1) != 0)
    write(fd2, &c, 1);
  close(fd1);
  close(fd2);
}
 
/*fonction pour concatener de fichier dans un troisieme ficher dst*/

void append(char * file1, char * file2, char * dst)
{
  int fd1 = open(file1, O_RDONLY); 
  int fd2 = open(file2, O_RDONLY);
  int fd3 = open(dst, O_WRONLY | O_CREAT, 0666);
  char c;
  while(read(fd1, &c, 1) != 0)
    write(fd3, &c, 1);
  while(read(fd2, &c, 1) != 0)
    write(fd3, &c, 1);
  close(fd1);
  close(fd2);
  close(fd3);
}

void addHeader(char * src, char * dst)
{
  int fdSrc = open(src, O_RDONLY); 
  int fdDst = open(dst, O_WRONLY | O_CREAT, 0666);
  char fileDate[30];
  int fileSize = size(src);
  int i = 0;
  char c;
  char size[100];
  lseek(fdDst, 0, SEEK_END);
  /*écrire le nom du ficher dans l'archive*/
  c = '+';
  for(i = 0; i < 3; i++)
    write(fdDst, &c, 1);
  write(fdDst, src, strlen(src));
  
  /*rajouter des étoiles apres le nom*/
  c = '$';
  for(i = 0; i < 3; i++)
    write(fdDst, &c, 1);
  
  /*écrire la taille du fichier dans l'archive*/
  sprintf( size, "%d", fileSize );
  // printf("file size de %s est : %d\n", src, fileSize);
  write(fdDst, &size, strlen(size));  

 /*rajouter des étoiles apres le nom*/
  c = ';';
  for(i = 0; i < 3; i++)
    write(fdDst, &c, 1);

  /*écrire la date de derniere modification dans l'archive */
  modifiedDate(src, fileDate);
  i = 0;
  write(fdDst, fileDate, strlen(fileDate));
  c = '*';
  for(i = 0; i < 3; i++)
    write(fdDst, &c, 1);
  close(fdDst);
  close(fdSrc);
}

void makeArchive(char * file1, char * file2, char * archive)
{
  addHeader(file1, archive);
  addTo(file1, archive);
  addHeader(file2, archive);
  addTo(file2, archive);
}

int positionFile(char * file, char * archive)
{
  int count = 0;
  int fd = open(archive, O_RDONLY);
  char c;
  int i = 0;
  int counter = 0;
  int notFound = 0;

  /*parcourir jusqu'à la fin du fichier*/

  while(read(fd, &c, 1) > 0){
    if(c == '+'){  /*'+':l'entete du nom du fichier*/
      counter += 3; /*le nom du fichier est precedé par 2 étoiles*/
      lseek(fd, counter, SEEK_SET);/*avancer le le curseur du fichier jusqu'au nom*/

      /*boucle pour parcourir le nom du fichier*/
      while(!notFound){ // tant que notFound est false
	read(fd, &c, 1);
	printf("valeur de c lu : %c\n", c);
	counter++;
	/*si la lettre lu dans "file" diferente du caractere lu dans le fichier*/
	
	if(file[i] != c)
	  notFound = 1;
	if(c  == '$'){
	  printf("la taille de i : %d\n", i);
	  printf("la strlen de file : %d\n", strlen(file));
	  if(i == strlen(file)){
	    printf("valeur de counter à retourner %d\n", counter);
	    return (counter - strlen(file) - 3);
	  }
	}
	i++;
      }
    }
    
  }
  return -1;
}


void update(char * file, char * archive)
{
  int fd1 = open(file, O_RDONLY);
  int fd2 = open(file, O_WRONLY);
}
main(int argc, char **argv)
{
   
  int p = positionFile(argv[1], argv[2]);
  printf("position : %d\n", p);
  return 0;

}

