#include <stdio.h>
//#include <stdlib.h>
//#include <stdbool.h>
//#include <unistd.h>
//#include <string.h>
//#include <time.h>
#include "./Headers/struct_enum.h"
#include "./Headers/print.h"
#include "./Headers/write_read_file.h"
#include "./Headers/date.h"
#include "./Headers/trie.h"
#include "./Headers/check_bool_string.h"
#include "./Headers/reservation_hotel.h"
#include "./Headers/menu_func.h"



int main(){

    startup();

    int total_chambres;
    
    hotel *Hotel;
    reservation *Reservation;

    //Si le fichier chambres_hotel.txt existe
    if(access("chambres_hotel.txt", F_OK) == 0){
        printf("> Fichier trouve !\n");
        //Creation de structure avec les informations du fichier
        Hotel = read_chambres_hotel();
        if(access("reservations_clients.txt", F_OK) == 0){
            Reservation = read_reservations_clients();
        }else{
            Reservation = init_reservation();
            write_reservations_clients(Reservation);
        }
        

        //Supprime les reservations dont la date de depart est inferieure a la date actuelle
        supp_reserv_fini(Reservation);

        //Trie les reservations selon le numero de la chambre, puis selon la date d'arrivee
        trie_reservations(Reservation);
        

    //Si le fichier n'existe pas
    }else{
        int choix = -1;
        printf("> /!\\ Le fichier n'a pas ete trouve. Voulez-vous creer un ficher avec les informations de votre hotel ?\nSi le fichier reservations_clients.txt existe deja, il sera ecrase.\n");
        do{
            printf("1 - Creer un nouveau fichier\t 0 - Quitter\n");
            scanf("%d", &choix);
        }while(choix != 1 && choix != 0);
        if (choix == 1){
            printf("Combien de chambres dans votre hotel ?\n");
            scanf("%d", &total_chambres);

            //Creation de structure hotel avec le nombre de chambres
            Hotel = init_hotel(total_chambres);

            //Ecriture dans fichier texte
            write_chambres_hotel(Hotel);

            Reservation = init_reservation();

            write_reservations_clients(Reservation);
        }else{
            shutdown();
        } 
    }
    int choix_menu = -1;
    do{
        menu();
        int test = 0;
        do{
            test = scanf("%d",&choix_menu);
                if (test != 1){
                printf("Erreur de format. Veuillez entrer un nombre :\n");
                scanf("%*[^\n]");
            }
        }while(test !=1);
        printf("\n");
        if(choix_menu == 1){
            voir_reservations(Reservation);
        }
        if(choix_menu == 2){
            chercher_reservation(Reservation);
        }
        if(choix_menu == 3){
            ajouter_reservation(Hotel, Reservation);
            write_reservations_clients(Reservation);
        }
        if(choix_menu == 4){
            modifier_reservation(Hotel, Reservation);
            write_reservations_clients(Reservation);
        }
        if(choix_menu == 5){
            supprimer_reservation(Reservation);
            write_reservations_clients(Reservation);
        }
        if(choix_menu == 6){
            modifier_hotel(Hotel, Reservation);
            write_chambres_hotel(Hotel);
            write_reservations_clients(Reservation);
        }
        if(choix_menu == 0){
            write_chambres_hotel(Hotel);
            write_reservations_clients(Reservation);
            free(Reservation->reservations);
            free(Reservation);
            free(Hotel->chambres);
            free(Hotel);
            shutdown();
        }
    }while(choix_menu != 0);
    return 0;
}
