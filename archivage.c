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
#include "desarchivage.h"
#include <unistd.h>

struct dateModif{
  int day;
  int month;
  int year;
  int hour;
  int minute;
  int second;
};

void archiveFolder(char * directory, char * archive)
{
  char ** files = filesInFolder(directory);
  int numberFiles = filesCounter(directory);
  DIR *rep = NULL;
  int i;
  for(i = 0; i < numberFiles; i++){
    rep = NULL;
    char buffer[2000];
    strcpy(buffer, directory);   
    strcat(buffer,"/");
    strcat(buffer,files[i]);
    rep = opendir(buffer);
    if(rep == NULL){
      addHeader(buffer, archive);
      addTo(buffer, archive);
    }
    else
      archiveFolder(buffer, archive);
  }
}
    
void archiveList(int filesNumber, char ** filesNames)
{
  int i = 1;
  DIR *rep = NULL;

  for(i = 1; i < filesNumber-1; i++){ 
    rep = opendir(filesNames[i]);
    if(rep == NULL){
      addHeader(filesNames[i], filesNames[filesNumber-1]);
      addTo(filesNames[i], filesNames[filesNumber-1]);
    }
    else
      archiveFolder(filesNames[i], filesNames[filesNumber-1]);
  }
}

  
int main(int argc, char **argv)
{
  
  char command [100];
  int fd = open(argv[argc-1], O_RDONLY); 
  char c;
  int taille;
  pid_t t;
  printf("archivage du fichier\n");
  archiveList(argc, argv);
  printf("fichiers dans l'archive : \n");
  filesInArchive(argv[argc-1], argc-2);
  printf("contenu de l'archive : \n");
  if(fork() == 0){
    execlp("cat", "cat", argv[argc-1], NULL);
    return 1;
  }
  else{
    wait(NULL);
    printf("\nsuppression du fichier %s de l'archive\n", argv[1]);
    deleteFileArchive(argv[argc-1], argv[1]);
    printf("contenu de l'archive : \n"); 
    if(fork() == 0){
      execlp("cat", "cat", argv[argc-1], NULL);
      return 0;
    }
    wait(NULL);
    printf("Désarchivage \n");
  }
 
  return 0;
}
