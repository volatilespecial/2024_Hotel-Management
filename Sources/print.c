#include "../Headers/print.h"

void print_type_chambre(type_chambre tc){
     if (tc == standard){
        printf("Standard");
     }else if (tc == communicante){
        printf("Communicante");
     }else if (tc == deluxe) {
        printf("Deluxe");
     }else {
        printf("Accessible"); 
     }
}

void print_suite_deluxe(suite_deluxe sd){
    if (sd == executive) printf(", Suite Executive");
    else if (sd == junior) printf(", Suite Junior");
    else if (sd == presidentielle) printf(", Suite Presidentielle");
    else printf(", Pas de suite");
}

void print_agencement(agencement ag){
    if (ag == simple) printf(", Simple");
    else if (ag == doubl) printf(", Double");
    else if (ag == triple) printf(", Triple");
    else printf(", Quadruple");
}

void print_chambres(hotel *Hotel){
    for(int i = 0; i<Hotel->nb_chambres; i++){
        printf("%d - Chambre %d : ", i+1, Hotel->chambres[i].numero_chambre);
        print_type_chambre(Hotel->chambres[i].tc);
        print_suite_deluxe(Hotel->chambres[i].sd);
        print_agencement(Hotel->chambres[i].ag);
        printf(", %d EUR/nuit\n", Hotel->chambres[i].prix_nuit);
    }
}

void startup(){
    printf("############ Hotel Management V1.0 starting up ############\n");
    printf("Cree par Anparasan Anpukkody et Edouard Crocq\n");
    printf("> Check du fichier chambres_hotel.txt...\n");
}

void shutdown(){
    printf("> Le programme va bientot quitter...\n");
    printf("Cree par Anparasan Anpukkody et Edouard Crocq\n");
    printf("############ Hotel Management V1.0 shutting down ############\n");
    exit(0);
}

void menu(){
    printf("\n--------------------------------------------------------------------------------\n1 - Voir toutes les reservations\t2 - Chercher une reservation\n3 - Ajouter une reservation\t4 - Modifier une reservation\n5 - Supprimer une reservation\t6 - Modifier votre hotel\n0 - Quitter\n--------------------------------------------------------------------------------\n");
}
