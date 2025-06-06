#ifndef DATE_H
#define DATE_H

#include <time.h>
#include <stdlib.h>
#include "struct_enum.h"

//Ajouter le nombre de jours a une date
date* addDays(date d1, int days);

//Verifier si l'annee est une annee bisextille
bool is_leap_year(int year);

//Donner le nombre de jours dans un mois selon l'annee
int check_month(int month, int year);

//Verifier si la date d1 est superieure a date d2
bool est_superieure(date d1, date d2);

//Verifier si la date d1 est inferieure a date d2
bool est_inferieure(date d1, date d2);

//Verifier si la date d est inferieure a la date actuelle
bool est_inferieure_current(date d);

//Donner la date actuelle
date current_date();

//Verifier si la date est valide
bool date_valide(int j, int m, int y);

#endif