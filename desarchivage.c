#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdint.h>
#include <fcntl.h>
#include <time.h>
#include <string.h>
#include <dirent.h>
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

bool ifDossier(char * name)
{
  int i;
  for(i=0;i=sizeof(name);i++)
    if(name[i]=='/')
      return True;
  return False;
}

void creerDossierArchive(char * name)
{
  mkdir(name,0766);
}
 
void createFileInfolder(char *folder, char * file)
{
  
}

void extract(char * archive)
{
  int fd = open(archive,O_RDONLY);
  int size;
  char * file;
  char * name;
  dateModif date;
  char c;


  while (read(fd,&c,1 >0)){ //test lecture possible

    name = getNextFileName(fd);
    size = getNextFileSize(fd);
    date =lastModifedArchive(fd);
    file = readNextFile(fd,size);

    if(ifDossier (name)){

      creerDossierArchive(name);
    
    }else{
 
      creationFichierArchive(name,file,size);
    
    }

  }
  close(fd);

}
  

int main(int argc, char **argv)
{

 

 
}

 
