# Configuration de base
CC = gcc
CFLAGS = -Wall -Wextra -O2
TARGET = tata
SRC = tata.c
LIBS = -lm  # Pour les fonctions mathématiques si nécessaire

# Règle par défaut
all: $(TARGET)

# Compilation du programme
$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC) $(LIBS)

# Exécution du programme
run: $(TARGET)
	./$(TARGET)

# Nettoyage
clean:
	rm -f $(TARGET) *.o
