#ifndef PRINT_H
#define PRINT_H

#include <stdio.h>
#include <stdlib.h>
#include "struct_enum.h"

//Affiche le type de la chambre
void print_type_chambre(type_chambre tc);

//Affiche la suite deluxe
void print_suite_deluxe(suite_deluxe sd);

//Affiche l'agencement
void print_agencement(agencement ag);

//Affiche les chambres de l'hotel
void print_chambres(hotel *Hotel);

//Demarrage
void startup();

//Quitter le programme
void shutdown();

//Affiche le menu
void menu();

#endif