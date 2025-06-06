#ifndef RESERVATION_HOTEL_H
#define RESERVATION_HOTEL_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "struct_enum.h"
#include "print.h"
#include "write_read_file.h"
#include "date.h"
#include "trie.h"

//Initialise un hotel si le fichier chambres_hotel.txt n'existe pas
hotel* init_hotel(int total_chambre);

//Initialise une liste de reservation avec 0 si le fichier reservations_clients.txt n'existe pas
reservation* init_reservation();

//Recupere tous les numeros des chambres dont le type, la suite et l'agencement correspond
int* recupNumeroChambre(hotel *Hotel, type_chambre tc, suite_deluxe sd, agencement ag, int *size);

//Recupere toutes les reservations d'une chambre donnee
reservation* recupReserChambre(reservation *Res, int nb_res, int num_chambres);

//Recupere les details d'une chambre donnee
int* recupDetailsChambre(hotel *Hotel, int num_chambre);

//Ajouter une reservation sans entree utilisateur
void ajouter_reservation_aux(reservation *Res, reservation_client aAjouter);

//Supprimer une reservation sans entree utilisateur
void supprimer_reservation_aux(reservation *Res, int reser_aSupp);

//Modifier la date d'une reservation
void modif_date_res(hotel *Hotel, reservation *Res, int index);

//Supprimer les reservations dont la date de depart est inferieure a la date actuelle
void supp_reserv_fini(reservation *Res);

//Ajouter une reservation
void input_reservation(hotel *Hotel, reservation *Res);

#endif