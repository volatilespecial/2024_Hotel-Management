#ifndef WRITE_READ_FILE_H
#define WRITE_READ_FILE_H


#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
//#include <unistd.h>
#include <string.h>
//#include <time.h>
#include "struct_enum.h"
#include "print.h"
#include "check_bool_string.h"

//Lire les informations du fichier chambres_hotel.txt et creer une structure
hotel* read_chambres_hotel();

//Ecriture des informations de la structure hotel dans le fichier chambres_hotel.txt
void write_chambres_hotel(hotel *Hotel);

//Ecriture des informations de la structure reservation dans le fichier reservations_clients.txt
void write_reservations_clients(reservation *Res);

//Lire les informations du fichier reservations_clients.txt et creer une structure
reservation* read_reservations_clients();


#endif
