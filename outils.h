typedef struct dateModif * dateModif;

int size(char * file);
void lastModified(char * file, char * date);
void addTo(char * file, char * dst);
void append(char * file1, char * file2, char * dst);
void addHeader(char * src, char * dst);
void makeArchive(char * file1, char * file2, char * archive);
int positionFile(char * file, char * archive);
int ifFolder(char * directory);
char ** filesInFolder(char * directory);
char * getNextFileName(int fd);
int readAndCast(int fd, int n);
dateModif lastModifedArchive(int fd);
char * readNextFile(int fd, int size);
