#ifndef MENU_FUNC_H
#define MENU_FUNC_H

#include <stdlib.h>
#include <unistd.h>
#include "struct_enum.h"
#include "print.h"
#include "write_read_file.h"
#include "date.h"
#include "trie.h"
#include "reservation_hotel.h"

//Voir toutes les reservations
void voir_reservations(reservation *Res);

//Cherche une reservation
void chercher_reservation(reservation *Res);

//Ajouter une reservation
void ajouter_reservation(hotel *Hotel, reservation *Res);

//Modifier une reservation
void modifier_reservation(hotel *Hotel, reservation *Res);

//Supprimer une reservation
void supprimer_reservation(reservation *Res);

//Ajouter une chambre dans l'hotel
void ajoutChambre(hotel *Hotel);

//Modifier une chambre de l'hotel
void modifier_chambre(hotel *Hotel, reservation *Res);

//Modifier l'hotel
void modifier_hotel(hotel *Hotel, reservation *Res);

#endif