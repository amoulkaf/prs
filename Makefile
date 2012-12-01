CC=gcc                       # le compilateur (et aussi linker)
CFLAGS=
LDLIBS= -lm
OBJ= outils.o archivage.o   # les objets correspondants à chaque unité de compilation
EXEC=tar               # nom de l'exécutable

$(EXEC):  $(OBJ)
	$(CC) $^ -o $(EXEC) $(LDFLAGS)

$(OBJ): %.o: %.c
	$(CC) $< -c $(CFLAGS)

clean:
	-rm *.o

mrproper: clean
	-rm $(EXEC)

all: mrproper $(EXEC)