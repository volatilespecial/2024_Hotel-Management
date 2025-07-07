#include "../Headers/write_read_file.h"

hotel* read_chambres_hotel(){
    bool first_line = true;
    bool second_line = false;
    FILE *chambre_hotel = fopen("chambres_hotel.txt","r");
    hotel *Hotel = malloc(sizeof(hotel));
    if (Hotel == NULL) exit(0);
    //chambre *details_chambres;
    int total_chambre;
    char line[30];
    int tmp[5];
    int i = 0;
    int j = 0;
    while(fgets(line, 30, chambre_hotel)){
        if(second_line){
            Hotel->prix_options = malloc(5 * sizeof(int));
            if(Hotel->prix_options == NULL) exit(0);
            char *token = strtok(line, ";");
            while(token != NULL){
                tmp[i] = atoi(token);
                i++;
                token = strtok(NULL,";");
            }
            Hotel->prix_options[0] = tmp[0];
            Hotel->prix_options[1] = tmp[1];
            Hotel->prix_options[2] = tmp[2];
            Hotel->prix_options[3] = tmp[3];
            Hotel->prix_options[4] = tmp[4];
            i = 0;
            second_line = false;
        }
        else if(first_line){
            total_chambre = atoi(line);
            Hotel->chambres = malloc(total_chambre * sizeof(chambre));
            if(Hotel->chambres == NULL) exit(0);
            Hotel->nb_chambres = total_chambre;
            first_line = false;
            second_line = true;
        }else{
            char *token = strtok(line, ";");
            while(token != NULL){
                tmp[i] = atoi(token);
                i++;
                token = strtok(NULL,";");
            }
            Hotel->chambres[j].numero_chambre = tmp[0];
            Hotel->chambres[j].tc = tmp[1];
            Hotel->chambres[j].sd = tmp[2];
            Hotel->chambres[j].ag = tmp[3];
            Hotel->chambres[j].prix_nuit = tmp[4];
            j++;
            i = 0;
        }
    }
    fclose(chambre_hotel);
    return Hotel;
}

void write_chambres_hotel(hotel *Hotel){
    FILE *chambres_hotel = fopen("chambres_hotel.txt", "w+");
    fprintf(chambres_hotel, "%d\n", Hotel->nb_chambres);
    fprintf(chambres_hotel, "%d;%d;%d;%d;%d\n", Hotel->prix_options[0], Hotel->prix_options[1], Hotel->prix_options[2], Hotel->prix_options[3], Hotel->prix_options[4]);
    for(int i = 0; i<Hotel->nb_chambres; i++){
        fprintf(chambres_hotel, "%d;%d;%d;%d;%d\n", Hotel->chambres[i].numero_chambre, Hotel->chambres[i].tc, Hotel->chambres[i].sd, Hotel->chambres[i].ag, Hotel->chambres[i].prix_nuit);
    }
    fclose(chambres_hotel);
}

void write_reservations_clients(reservation *Res){
    FILE *res_cli = fopen("reservations_clients.txt", "w+");
    fprintf(res_cli, "%d\n", Res->nb_reservations);
    for(int i = 0; i<Res->nb_reservations; i++){
        fprintf(res_cli, "%d;%s;%d;%d;%d;%d;%d;%d;%d;%d;%s;%s;%s;%s;%s;%d\n", Res->reservations[i].numero_reservation, Res->reservations[i].nom_client, Res->reservations[i].numero_chambre, Res->reservations[i].arrivee.jour, Res->reservations[i].arrivee.mois, Res->reservations[i].arrivee.annee, Res->reservations[i].nombre_jours, Res->reservations[i].depart.jour, Res->reservations[i].depart.mois, Res->reservations[i].depart.annee, check_bool(Res->reservations[i].option_client.petit_dejeuner), check_bool(Res->reservations[i].option_client.chaines_tv), check_bool(Res->reservations[i].option_client.salle_de_sport), check_bool(Res->reservations[i].option_client.piscine), check_bool(Res->reservations[i].option_client.spa), Res->reservations[i].prix_total);
    }
    fclose(res_cli);
}

reservation* read_reservations_clients(){
    bool first_line = true;
    FILE *reservations = fopen("reservations_clients.txt","r");
    reservation *Reservation = malloc(sizeof(reservation));
    int total_reservations;
    char line[100];
    char *tmp[16];
    int i = 0;
    int j = 0;
    while(fgets(line, 100, reservations)){
        if(first_line){
            total_reservations = atoi(line);
            Reservation->reservations = malloc(total_reservations * sizeof(reservation_client));
            if(Reservation->reservations == NULL) exit(0);
            Reservation->nb_reservations = total_reservations;
            first_line = false;
        }else{
            char *token = strtok(line, ";");
            while(token != NULL){
                tmp[i] = token;
                i++;
                token = strtok(NULL,";");
            }
            Reservation->reservations[j].numero_reservation = atoi(tmp[0]);
            strcpy(Reservation->reservations[j].nom_client, string_correct(tmp[1]));
            //Reservation->reservations[j].nom_client = string_correct(tmp[1]);
            Reservation->reservations[j].numero_chambre = atoi(tmp[2]);
            Reservation->reservations[j].arrivee.jour = atoi(tmp[3]);
            Reservation->reservations[j].arrivee.mois = atoi(tmp[4]);
            Reservation->reservations[j].arrivee.annee = atoi(tmp[5]);
            Reservation->reservations[j].nombre_jours = atoi(tmp[6]);
            Reservation->reservations[j].depart.jour = atoi(tmp[7]);
            Reservation->reservations[j].depart.mois = atoi(tmp[8]);
            Reservation->reservations[j].depart.annee = atoi(tmp[9]);
            Reservation->reservations[j].option_client.petit_dejeuner = check_string(tmp[10]);
            Reservation->reservations[j].option_client.spa = check_string(tmp[11]);
            Reservation->reservations[j].option_client.chaines_tv = check_string(tmp[12]);
            Reservation->reservations[j].option_client.salle_de_sport = check_string(tmp[13]);
            Reservation->reservations[j].option_client.piscine = check_string(tmp[14]);
            Reservation->reservations[j].prix_total = atoi(tmp[15]);

            j++;
            i = 0;
        }
    }
    fclose(reservations);
    return Reservation;
}
