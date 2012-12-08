int readAndCast(int fd, int n)
{
  int i;
  char c;
  int tmp;
  int res = 0;
  for(i = 1; i <= n; i++){
    read(fd, &c, 1);
    tmp = atoi(c);
    res += (n - i) * 10;
  }
  return 0;
}

struct dateModif * lastModifedArchive(int fd)
{
  char c;
  dateModif date = malloc(sizeof(struct dateModif));
  bool found = false;
  int tmp;
  
  while(read(fd, &c, 1) > 0 && found == false){ 
    if(c == ';'){
      found = true;
      do{
	read(fd, &c, 1);
      }while(c !=';');
      /* lecture de du jour de modification*/
      lseek(fd, -1, SEEK_CUR);
      date->day = readAndCast(fd, 2);
      read(fd, &c, 1); //lecture des '/'
      /*lecture du mois de modification*/
      date->month = readAndCast(fd, 2);
      read(fd, &c, 1);//lecture des '/'
      /*lecture de l'année de modification*/
      date->year = readAndCast(fd, 4);
      read(fd,&c,1);
      /*lecture de l'heure de modification */
      date->hour = readAndCast(fd, 2);
      read(fd,&c,1);
      /*lecture de la minute de modification */
      date->minute = readAndCast(fd, 2);
      read(fd,&c,1);
      /*lecture de la seconde de modification */
      date->second = readAndCast(fd, 2);
      return date;
    }
  }
}
