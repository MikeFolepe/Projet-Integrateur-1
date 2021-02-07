#Fichier Makefile de l'executable
#
#Ecole Polytechnique de Montreal
#Departement de genie informatique et genie logiciel
#Cours : inf1900
#
#Etienne Chevalier-Tittley, Paul-Marie Akoffodji,
#Mike-Davy Folepe, Jean-Marc Ndong Ékouaga
# 
#Date : 2020-11-03
#
#Code qui n'est sous aucune license.
#

# Nom du microcontroleur cible
# (exemple: 'at90s8515')

MCU=atmega324pa

#le nom du projet

PROJECTNAME= main

# le nom de la librairie

LIB_NAME=libcommune

# Fichiers sources
# Utilisez le suffixe .cpp pour les fichiers C++
# Listez tous les fichiers a compiler, separes par
# un espace. exemple: 'tp1.c tp2.cpp':

PRJSRC= $(wildcard *.cpp )

# Inclusions additionnels (ex: -I/path/to/mydir)
INC= -I ../../lib_dir

# Libraires a lier (ex: -lmylib)
LIBS= -L ../../lib_dir -l commune 

# Niveau d'optimization
# Utilisez s (size opt), 1, 2, 3 ou 0 (off)
OPTLEVEL=s

# Programmer ID - Ne pas changer 
# Liste complete des IDs disponible avec avrdude
AVRDUDE_PROGRAMMERID=usbasp



####### variables #######

#compilateur utilise
CC=avr-gcc
#pour copier le contenu d'un fichier objet vers un autre
OBJCOPY=avr-objcopy
#pour permettre le transfert vers le microcontroleur
AVRDUDE=avrdude
#pour supprimer les fichiers lorsque l'on appel make clean
REMOVE=rm -f
# HEXFORMAT -- format pour les fichiers produient .hex
HEXFORMAT=ihex



####### Options de compilation #######

# Flags pour le compilateur en C
CFLAGS=-I. -I/usr/include/simavr  -MMD $(INC) -g -mmcu=$(MCU) -O$(OPTLEVEL) \
	-fpack-struct -fshort-enums             \
	-funsigned-bitfields -funsigned-char    \
	-Wall                                        

# Flags pour le compilateur en C++
CXXFLAGS=-fno-exceptions     

# Linker pour lier les librairies utilisees
LDFLAGS=-Wl,-Map,$(TRG).map -mmcu=$(MCU)



####### Cible (Target) #######

#Nom des cibles par defaut
TRG=$(PROJECTNAME).elf
HEXROMTRG=$(PROJECTNAME).hex
HEXTRG=$(HEXROMTRG) $(PROJECTNAME).ee.hex



####### Definition de tout les fichiers objets #######

# Cette fonction permet de differencier les fichiers .c
# des fichiers .cpp

# Fichier C++
CPPFILES=$(filter %.cpp, $(PRJSRC))

# Liste de tout les fichiers objet que nous devons creer

OBJDEPS= $(CPPFILES:.cpp=.o)


####### Creation des commandes du Makefile ####### 

# Creation des cibles Phony (Phony Target)
# En plus de la commande make qui permet de compiler
# votre projet, vous pouvez utilisez les commandes
# make all, make install et make clean
.PHONY: all install clean 

# Make all permet simplement de compiler le projet
#
all: $(TRG) $(HEXROMTRG)

# Implementation de la cible
$(TRG): $(OBJDEPS)
	$(CC) $(LDFLAGS) -o $(TRG) $(OBJDEPS) \
	-lm $(LIBS)


# De C++ a objet
%.o: %.cpp
	$(CC) $(CFLAGS) $(CXXFLAGS) -c $<

# Verification des dependances (header dependencies)
-include *.d

# Pour plus d'information sur cette section, consulter:
# http://bit.ly/2580FU8

# Production des fichiers hex a partir des fichiers elf
%.hex: %.elf
	$(OBJCOPY) -j .text -j .data \
		-O $(HEXFORMAT) $< $@

# Make install permet de compiler le projet puis
# d'ecrire le programme en memoire flash dans votre
# microcontroleur. Celui-ci doit etre branche par cable USB
install: $(HEXROMTRG)				
	$(AVRDUDE) -c $(AVRDUDE_PROGRAMMERID)   \
	-p $(MCU) -P -e -U flash:w:$(HEXROMTRG)


# Commande echo pour tester l'existance des variables
echo:
	@echo "OBJDEPS = $(OBJDEPS)"
	@echo "TRG = $(TRG)"
	@echo "CPPFILES = $(CPPFILES)"
	@echo "HEXTRG = $(HEXTRG)"



# Make clean permet d'effacer tout les fichiers generes
# lors de la compilation
clean:
	$(REMOVE) $(TRG) $(TRG).map $(OBJDEPS) $(HEXTRG) *.d
