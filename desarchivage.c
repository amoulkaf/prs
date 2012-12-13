#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
#include "desarchivage.h"
#include "outils.h"
#include <math.h>
#include <unistd.h>
#include <stdbool.h>


struct dateModif{
  int day;
  int month;
  int year;
  int hour;
  int minute;
  int second;
};


#define True 1
#define False 0

void creationFichierArchive(char * name, char * file, int size)
{
  int fd = open(name,O_WRONLY|O_CREAT,0666);
  
    write(fd,file,size);
  
  close(fd);
  
}

int ifDossier(char * name)
{
  int i;
  for(i=0;i<sizeof(name);i++){
    if(name[i]=='/')
      return True;
  }
  return False;
}

void creerDossierArchive(char * name)
{
  mkdir(name,0766);
}
 
int createFolders(char *path)
{
  char c;
  int i = 0;
  int fileFound = 0;
  char directory[100];
  int j = 0;
  int fd;
  while(fileFound == 0){
    do{
      directory[j] = path[i];
      c = directory[j];
      i++; j++;
    }while(directory[j-1] != '/' && c != '\0');
    if( c == '/')
      fileFound = 1;
    if(fileFound == 0)      
      mkdir(directory,0766);     
    else{
      fd = open(directory, O_WRONLY | O_CREAT ,0766);
      return fd;
    }
  }
  
}

void extract(char * archive)
{
  int fd = open(archive,O_RDONLY);
  int size;
  char * file;
  char * name;
  dateModif date;
  char c;
  int i = 0;
  int fdF;
  while (read(fd,&c,1) >0){ //test lecture possible
    name = getNextFileName(fd);
    size = getNextFileSize(fd);
    date =lastModifedArchive(fd);
    file = readNextFile(fd,size);
    if(ifDossier(name))
      fdF = createFolders(name);
    else
      fdF = open(name, O_WRONLY | O_CREAT ,0766);
    write(fdF, &file, (strlen(file)-1));
  }
  close(fd);
}

void update(char * archive, char * file)
{
  DIR *rep = NULL;
  deleteFileArchive(archive, file);
  rep = opendir(file);
   if(rep == NULL){
      addHeader(file, archive);
      addTo(file, archive);
    }
    else
      archiveFolder(file, archive);
}

void filesInArchive(char * archive, int files)
{
   int fd = open(archive,O_RDONLY);
   int size;
   char * file;
   char * name;
   dateModif date;
   DIR *rep = NULL;
   int i;
   for(i = 0;i < files; i++)
     {
       name = getNextFileName(fd);
       size = getNextFileSize(fd);
       date =lastModifedArchive(fd);
       printf("\tNom du fichier : %s\n", name);
       printf("\ttaille du fichier : %d\n", size);
       printf("\tDate De Derniere Modif : %d/%d/%d \t %d:%d:%d\n\n",date->day, date->month, date->year, date->hour, date->minute, date->second);
       free(date);
     }
}


  
