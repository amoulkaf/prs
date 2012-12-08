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
    printf("files[%d] : %s", i, files[i]);
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
  char * p;
  int size;
  dateModif d;
  char * file;
  //archiveList(argc, argv);
  deleteFileArchive(argv[2], argv[1]);
  return 0;
}
