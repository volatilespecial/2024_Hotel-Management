#ifndef STRUCT_ENUM_H
#define STRUCT_ENUM_H

#include <stdbool.h>

#define MAX_CHAR_NAME 30

//Definition des types de chambres, les suites deluxes, et les agencements
typedef enum {standard=1, communicante, deluxe, accessible} type_chambre;
typedef enum {null, executive, junior, presidentielle} suite_deluxe;
typedef enum {simple=1, doubl, triple, quadruple} agencement;

//Struct pour la date
typedef struct date{
    int jour;
    int mois;
    int annee;
} date;

//Struct pour les options avec des booleens
typedef struct option{
    bool petit_dejeuner;
    bool spa;
    bool chaines_tv;
    bool salle_de_sport;
    bool piscine;
} option;

//Struct pour une chambre
typedef struct chambre{
    type_chambre tc;
    suite_deluxe sd;
    agencement ag;
    int numero_chambre;
    int prix_nuit;
} chambre;

//Struct pour une reservation
typedef struct reservation_client{
    int numero_reservation;
    char nom_client[MAX_CHAR_NAME];
    int numero_chambre;
    date arrivee;
    int nombre_jours;
    date depart;
    option option_client;
    int prix_total;
} reservation_client;

//Struct pour l'hotel
typedef struct hotel{
    chambre *chambres;
    int *prix_options;
    int nb_chambres;
} hotel;

//Struct pour toutes les reservtions
typedef struct reservations{
    reservation_client *reservations;
    int nb_reservations;
} reservation;

#endif