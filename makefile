# Dossiers
OBJDIR = obj
SRCDIR = src
BINDIR = bin
INCDIR = include

# Compilateur et options
CC = g++
CFLAGS = -Wall -I$(INCDIR) -Isupport/libphysics/include -Isupport/SFML/SFML-2.6.1/include
LDFLAGS = -O2 -DNDEBUG -Lsupport/SFML/install/lib/ -lsfml-system -lsfml-graphics -lsfml-window -lsfml-audio -Lsupport/libphysics/Release/ -llibphysics -Wl,-rpath,support/libphysics/Release/

# Fichiers source et objets
SRCS = $(wildcard $(SRCDIR)/*.cpp)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))

# Nom de l'exécutable
EXEC = $(BINDIR)/app

# Compilation finale
all: $(EXEC)

$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CC) $(CFLAGS) -c $< -o $@

# Compilation de l'exécutable principal
$(EXEC): $(OBJS)
	$(CC) $^ -o $@ $(LDFLAGS)

# Compilation des fichiers .cpp en .o
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(INCDIR)/%.hpp | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Création des dossiers si nécessaire
$(OBJDIR) $(BINDIR) $(BUIDIR):
	mkdir -p $@

obj/main.o: $(INCDIR)/properties.hpp 
obj/startscreen.o: $(INCDIR)/properties.hpp 
obj/obstacle.o: $(INCDIR)/properties.hpp 
obj/finishline.o: $(INCDIR)/properties.hpp 
obj/endscreen.o: $(INCDIR)/properties.hpp 
obj/boatoption.o: $(INCDIR)/properties.hpp 

# Exécution
run:
	$(EXEC)

runv:
	valgrind $(EXEC)

rung:
	gdb $(EXEC)

# Nettoyage
clean:
	rm -rf $(OBJDIR)/*.o $(EXEC)
