#include "../Headers/reservation_hotel.h"

hotel* init_hotel(int total_chambre){
    hotel *Hotel = malloc(sizeof(hotel));
    chambre *chambres = malloc(total_chambre * sizeof(chambre));
    Hotel->prix_options = malloc(5 * sizeof(int));
    if (chambres == NULL || Hotel == NULL || Hotel->prix_options == NULL)  exit(0);
    int tmp = -1;
    printf("Entrez les details des chambres : \n");
    for(int i = 0; i<total_chambre; i++){
        tmp = -1;
        printf("Chambre %d\n", i+1);

        printf("Numero de la chambre : ");
        int test = 0;
        do{
            test = scanf("%d",&chambres[i].numero_chambre);
                if (test != 1){
                printf("Erreur de format. Veuillez entrer un nombre :\n");
                scanf("%*[^\n]");
            }
        }while(test !=1);

        do{
            printf("Type de la chambre : 1 pour standard, 2 pour communicante, 3 pour deluxe, 4 pour accessible\n");
            
            int test = 0;
            do{
                test = scanf("%d",&tmp);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
        }while(tmp!=1 && tmp!=2 && tmp!=3 && tmp!=4);
        chambres[i].tc = tmp;

        tmp = -1;

        if(chambres[i].tc == deluxe){
            do{
                printf("Deluxe : 1 pour suite executive, 2 pour suite junior, 3 pour suite presidentielle\n");
                int test = 0;
                do{
                    test = scanf("%d",&tmp);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(tmp!=1 && tmp!= 2 && tmp!=3);
            chambres[i].sd = tmp;
        }else{
            chambres[i].sd = 0;
        }

        tmp = -1;

        do{
            printf("Agencement : 1 pour simple, 2 pour double, 3 pour triple, 4 pour quadruple\n");
            int test = 0;
            do{
                test = scanf("%d",&tmp);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
        }while(tmp!= 1 && tmp!= 2 && tmp!=3 && tmp!= 4);
        chambres[i].ag = tmp;
        
        printf("Le prix d'une nuit pour cette chambre : ");
        scanf("%d", &chambres[i].prix_nuit);

    }
    printf("\n");
    printf("Entrez les prix des options : si l'option n'est pas disponible dans votre hotel, mettez un 0\n");
    printf("Prix pour le petit-dejeuner : \n");
    scanf("%d", &Hotel->prix_options[0]);
    printf("Prix pour les chaines tv : \n");
    scanf("%d", &Hotel->prix_options[1]);
    printf("Prix pour la salle de sport : \n");
    scanf("%d", &Hotel->prix_options[2]);
    printf("Prix pour la piscine : \n");
    scanf("%d", &Hotel->prix_options[3]);
    printf("Prix pour le spa : \n");
    scanf("%d", &Hotel->prix_options[4]);
    Hotel->chambres = chambres;
    Hotel->nb_chambres = total_chambre;
    return Hotel;
}

reservation* init_reservation(){
    reservation *Res = malloc(sizeof(reservation));
    if(Res == NULL) exit(0);
    Res->nb_reservations = 0;
    return Res;
}

int* recupNumeroChambre(hotel *Hotel, type_chambre tc, suite_deluxe sd, agencement ag, int *size){
    int *roomNum = malloc(1 * sizeof(int));
    int j = 0;
    int realloc_num = 1;
    if(roomNum == NULL) exit(0);
    for(int i = 0; i<Hotel->nb_chambres; i++){
        if(Hotel->chambres[i].tc == tc && Hotel->chambres[i].sd == sd && Hotel->chambres[i].ag == ag){
            roomNum[j] = Hotel->chambres[i].numero_chambre;
            j++;
            realloc_num++;
            roomNum = realloc(roomNum, realloc_num * sizeof(int));

        }
    }
    *size = j;
    return roomNum;
}

reservation* recupReserChambre(reservation *Res, int nb_res, int num_chambres){
    reservation *Res_chambre = malloc(sizeof(reservation));
    if (Res_chambre == NULL) exit(0);
    Res_chambre->nb_reservations = nb_res;
    Res_chambre->reservations = malloc(nb_res * sizeof(reservation_client));
    if(Res_chambre->reservations == NULL) exit(0);
    int j = 0;
    for(int i = 0; i<Res->nb_reservations; i++){
        if(Res->reservations[i].numero_chambre == num_chambres){
            Res_chambre->reservations[j] = Res->reservations[i];
            j++;
        }
    }
    return Res_chambre;
}

int* recupDetailsChambre(hotel *Hotel, int num_chambre){
    int *detailsChambre = malloc(3 * sizeof(int));
    if(detailsChambre == NULL) exit(0);
    for(int i = 0; i<Hotel->nb_chambres; i++){
        if(Hotel->chambres[i].numero_chambre == num_chambre){
            detailsChambre[0] = Hotel->chambres[i].tc;
            detailsChambre[1] = Hotel->chambres[i].sd;
            detailsChambre[2] = Hotel->chambres[i].ag;
            break;
        }
    }
    return detailsChambre;
}

void ajouter_reservation_aux(reservation *Res, reservation_client aAjouter){
    Res->nb_reservations++;
    Res->reservations = realloc(Res->reservations, Res->nb_reservations * sizeof(reservation_client));
    Res->reservations[Res->nb_reservations-1] = aAjouter;
    trie_reservations(Res);
}

void supprimer_reservation_aux(reservation *Res, int reser_aSupp){
    int index_aSupp = -1;
    int confirm_Supp = 0;
    reservation_client *newArray;
    for(int i = 0; i<Res->nb_reservations; i++){
        if(Res->reservations[i].numero_reservation == reser_aSupp){
            index_aSupp = i;
            break;
        }
    }
    newArray = malloc((Res->nb_reservations - 1) * sizeof(reservation_client));
    if(newArray == NULL) exit(0);
    memmove(newArray, Res->reservations, index_aSupp * sizeof(reservation_client));
    memmove(newArray + index_aSupp, Res->reservations + index_aSupp + 1, (Res->nb_reservations - index_aSupp - 1) * sizeof(reservation_client));
    free(Res->reservations);
    Res->reservations = newArray;
    Res->nb_reservations--;
}

void modif_date_res(hotel *Hotel, reservation *Res, int index){
    int date_choix = 1;
    bool reser_done = false;
    date new;
    int nb_jours;
    reservation_client *newRes = malloc(sizeof(reservation_client));
    int size = 0;
    int current_chambre;
    int nb_res_chambre;

    int *detailsCh = recupDetailsChambre(Hotel, Res->reservations[index].numero_chambre);

    int *num_chambres = recupNumeroChambre(Hotel, detailsCh[0], detailsCh[1], detailsCh[2], &size);

    reservation_client *backup = malloc(sizeof(reservation_client));
    if(backup == NULL) exit(0);
    *backup = Res->reservations[index];
    supprimer_reservation_aux(Res, Res->reservations[index].numero_reservation);

    while(date_choix == 1 && reser_done == false){
        do{
            printf("La date d'arrivee : DD/MM/YYYY\n");
            scanf("%d/%d/%d", &new.jour, &new.mois, &new.annee);
        }while(date_valide(new.jour, new.jour, new.annee));
        nb_jours = -1;
        do{
            printf("Le nombre de jours :\n");
            int test = 0;
            do{
                test = scanf("%d", &nb_jours);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
        }while(nb_jours<=0);

        newRes->arrivee = new;
        newRes->nombre_jours = nb_jours;
        newRes->depart = *addDays(newRes->arrivee, newRes->nombre_jours);
        strcpy(newRes->nom_client, string_correct(backup->nom_client));
        newRes->numero_reservation = backup->numero_reservation;
        newRes->option_client = backup->option_client;
        newRes->prix_total = backup->prix_total;  
        
        
        for(int i = 0; i<size; i++){
            if(reser_done == false){
                nb_res_chambre = 0;
                current_chambre = num_chambres[i];
                for(int i = 0; i<Res->nb_reservations; i++){
                    if(Res->reservations[i].numero_chambre == current_chambre) nb_res_chambre++;
                }

                if(nb_res_chambre == 0){
                    newRes->numero_chambre = current_chambre;
                    ajouter_reservation_aux(Res, *newRes);
                    free(newRes);
                    reser_done = true;
                    break;
                }

                else if(nb_res_chambre == 1){
                    reservation *Res_chambre_current = recupReserChambre(Res, nb_res_chambre, num_chambres[i]);
                    if(est_superieure(newRes->arrivee, Res_chambre_current->reservations[0].depart)){
                        newRes->numero_chambre = current_chambre;
                        ajouter_reservation_aux(Res, *newRes);
                        free(newRes);
                        reser_done = true;
                        free(Res_chambre_current->reservations);
                        free(Res_chambre_current);
                        break;  
                    }else if(est_inferieure(newRes->depart, Res_chambre_current->reservations[0].arrivee) && !est_inferieure_current(newRes->arrivee)){
                        newRes->numero_chambre = current_chambre;
                        ajouter_reservation_aux(Res, *newRes);
                        free(newRes);
                        reser_done = true;
                        free(Res_chambre_current->reservations);
                        free(Res_chambre_current);
                        break;  
                    }
                }

                else if(nb_res_chambre > 1){
                    reservation *Res_chambre_current = recupReserChambre(Res, nb_res_chambre, num_chambres[i]);
                    if(est_inferieure(newRes->depart, Res_chambre_current->reservations[0].arrivee) && !est_inferieure_current(newRes->arrivee)){
                        newRes->numero_chambre = current_chambre;
                        ajouter_reservation_aux(Res, *newRes);
                        free(newRes);
                        reser_done = true;
                        free(Res_chambre_current->reservations);
                        free(Res_chambre_current);
                        break;
                    }
                    else if(est_superieure(newRes->arrivee, Res_chambre_current->reservations[nb_res_chambre-1].depart)){
                        newRes->numero_chambre = current_chambre;
                        ajouter_reservation_aux(Res, *newRes);
                        free(newRes);
                        reser_done = true;
                        free(Res_chambre_current->reservations);
                        free(Res_chambre_current);
                        break;
                    }else{
                        for(int j = 0; j<nb_res_chambre-1; j++){
                            if(est_inferieure(Res->reservations[j].depart, newRes->arrivee) && est_superieure(Res->reservations[j+1].arrivee, newRes->depart)){
                                newRes->numero_chambre = current_chambre;
                                ajouter_reservation_aux(Res, *newRes);
                                free(newRes);
                                reser_done = true;
                                free(Res_chambre_current->reservations);
                                free(Res_chambre_current);
                                break;
                            }
                        }
                    }
                    
                }
            }else{
                break;
            }
        }
        if(reser_done == false){
            printf("> Aucune reservation n'est possible pour les dates demandees. Voici les creneaux disponibles : \n");
            for(int i = 0; i<size; i++){
                nb_res_chambre = 0;
                current_chambre = num_chambres[i];
                for(int j = 0; j<Res->nb_reservations; j++){
                    if(Res->reservations[j].numero_chambre == current_chambre) nb_res_chambre++;
                }
                reservation *Res_chambre_current;
                if(nb_res_chambre != 0){
                    Res_chambre_current = recupReserChambre(Res, nb_res_chambre, num_chambres[i]);
                }
                date today = current_date();
                printf("%d/%d/%d - ", today.jour, today.mois, today.annee);
                if(nb_res_chambre == 1){
                    printf("%d/%d/%d\n", Res_chambre_current->reservations[0].arrivee.jour, Res_chambre_current->reservations[0].arrivee.mois, Res_chambre_current->reservations[0].arrivee.annee);
                    printf("%d/%d/%d - \n", Res_chambre_current->reservations[0].depart.jour, Res_chambre_current->reservations[0].depart.mois, Res_chambre_current->reservations[0].depart.annee);
                }else if (nb_res_chambre > 1){
                    printf("%d/%d/%d\n", Res_chambre_current->reservations[0].arrivee.jour,Res_chambre_current->reservations[0].arrivee.mois, Res_chambre_current->reservations[0].arrivee.annee);
                    for(int j = 0; j<nb_res_chambre-1; j++){
                        printf("%d/%d/%d - ", Res_chambre_current->reservations[j].depart.jour,Res_chambre_current->reservations[j].depart.mois, Res_chambre_current->reservations[j].depart.annee);
                        printf("%d/%d/%d\n", Res_chambre_current->reservations[j+1].arrivee.jour,Res_chambre_current->reservations[j+1].arrivee.mois, Res_chambre_current->reservations[j+1].arrivee.annee); 
                    }
                    printf("%d/%d/%d - \n", Res_chambre_current->reservations[nb_res_chambre-1].depart.jour,Res_chambre_current->reservations[nb_res_chambre-1].depart.mois, Res_chambre_current->reservations[nb_res_chambre-1].depart.annee);
                }
                free(Res_chambre_current->reservations);
                free(Res_chambre_current);
            }
            do{
                printf("1 - Modifier la date , 2 - Annuler la modification\n");
                int test = 0;
                do{
                    test = scanf("%d", &date_choix);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(date_choix != 1 && date_choix != 2);
        }
    }
    if(date_choix == 2){
        ajouter_reservation_aux(Res, *backup);
        printf("> Modification annulee...\n");
        free(newRes);
    }else{
        printf("Voici les details de la nouvelle reservation : \n");
        printf("Chambre : %d, Date d'arrivee : %d/%d/%d, Nombre de jours : %d, Date de depart : %d/%d/%d\n", Res->reservations[index].numero_chambre, Res->reservations[index].arrivee.jour, Res->reservations[index].arrivee.mois, Res->reservations[index].arrivee.annee, Res->reservations[index].nombre_jours, Res->reservations[index].depart.jour, Res->reservations[index].depart.mois, Res->reservations[index].depart.annee);
    }
    free(detailsCh);
    free(num_chambres);
    sleep(2);
}

void supp_reserv_fini(reservation *Res){
    int *aSupp = malloc(1 * sizeof(int));
    int size = 0;
    int j = 0;
    if(aSupp == NULL) exit(0);
    for(int i = 0; i<Res->nb_reservations; i++){
        if(est_inferieure_current(Res->reservations[i].depart)){
            size++;
            aSupp = realloc(aSupp, size * sizeof(int));
            aSupp[j] = Res->reservations[i].numero_reservation;
            j++;
            if (aSupp == NULL) exit(0);
        }
    }
    for(int i = 0; i<size; i++){
        supprimer_reservation_aux(Res, aSupp[i]);
    }
    free(aSupp);
}

void input_reservation(hotel *Hotel, reservation *Res){
    char string_tmp[30];
    int *input = malloc(7 * sizeof(int));
    if (input == NULL) exit(0);
    int tmp[5] = {0};
    int choix = 0;
    int i = 0;
    bool check_is = true;
    bool correct = true;

    bool reser_done = false;
    int date_choix = 1;
    int valide_reser = 0;

    int size = 0;

    int *num_chambres;

    int current_chambre;
    int nb_res_chambre;

    int counter = 1;
    bool numero_reser_find = false;

    while(choix != 2){
        i = 0;
        check_is = true;
        choix = 0;
        for(int i = 0; i<5; i++){
            tmp[i] = 0;
        }
        for(int i = 0; i<7; i++){
            input[i] = -1;
        }
        for(int y = 0; y<Hotel->nb_chambres; y++){
            if (i==0){
                tmp[i] = Hotel->chambres[y].tc;
                i++;
            }else{
                if(tmp[i-1] != Hotel->chambres[y].tc){
                    tmp[i] = Hotel->chambres[y].tc;
                    i++;
                }
            }
        }
        while(check_is){
            printf("Commencons par le type de la chambre : ");
            //~ for(int j= 0; j<i; j++){
                //~ if(tmp[j] == standard) printf("1 - Standard ,");
                //~ if(tmp[j] == communicante) printf(" 2 - Communicante ,");
                //~ if(tmp[j] == deluxe) printf(" 3 - Deluxe ,");
                //~ if(tmp[j] == accessible) printf(" 4 - Accessible ");
            //~ }
            for(int j= 0; j<i; j++){
                if(tmp[j] == standard) printf("1 - Standard ,");
            }
            for(int j= 0; j<i; j++){
                if(tmp[j] == communicante) printf(" 2 - Communicante ,");
            }
            for(int j= 0; j<i; j++){
                if(tmp[j] == deluxe) printf(" 3 - Deluxe ,");
            }
            for(int j= 0; j<i; j++){
                if(tmp[j] == accessible) printf(" 4 - Accessible ");
            }
            printf("\n");
            int test = 0;
            do{
                test = scanf("%d", &input[0]);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
            for(int u = 0; u<i; u++){
                if(input[0] == tmp[u]) check_is = false;
            }
        }
        for(int j=0; j<5; j++){
            tmp[j] = 0;
        }
        i=0;
        check_is = true;
        for(int y = 0; y<Hotel->nb_chambres; y++){
            if (input[0] == 3){
                if(Hotel->chambres[y].tc == input[0]){
                    if (i==0){
                        tmp[i] = Hotel->chambres[y].sd;
                        i++;
                    }else{
                        if(tmp[i-1] != Hotel->chambres[y].sd){
                            tmp[i] = Hotel->chambres[y].sd;
                            i++;
                        }
                    }
                }
            }else{
                if(Hotel->chambres[y].tc == input[0]){
                    if (i==0){
                        tmp[i] = Hotel->chambres[y].ag;
                        i++;
                    }else{
                        if(tmp[i-1] != Hotel->chambres[y].ag){
                            tmp[i] = Hotel->chambres[y].ag;
                            i++;
                        }
                    }
                }
            }
        }
        if(input[0] == deluxe){
            while(check_is){
                printf("La suite deluxe : ");
                for(int j= 0; j<i; j++){
                    if(tmp[j] == executive) printf("1 - Suite executive ,");
                    if(tmp[j] == junior) printf(" 2 - Suite junior ,");
                    if(tmp[j] == presidentielle) printf(" 3 - Suite presidentielle ");
                }
                printf("\n");
                int test = 0;
                do{
                    test = scanf("%d", &input[1]);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
                
                for(int u = 0; u<i; u++){
                    if(input[1] == tmp[u]) check_is = false;
                }
            }
        }else{
            input[1] = 0;
        }

        for(int j=0; j<5; j++){
            tmp[j] = 0;
        }
        i=0;

        for(int y = 0; y<Hotel->nb_chambres; y++){
            if(input[0] ==  deluxe){

                if(Hotel->chambres[y].sd == input[1]){
                    if(i == 0){
                        tmp[i] = Hotel->chambres[y].ag;
                        i++;
                    }else{
                        if(tmp[i-1] != Hotel->chambres[y].ag){
                            tmp[i] = Hotel->chambres[y].ag;
                            i++;
                        }
                    }
                }
            }else{
                if(Hotel->chambres[y].tc == input[0]){
                    if(i == 0){
                        tmp[i] = Hotel->chambres[y].ag;
                        i++;
                    }else{
                        if(tmp[i-1] != Hotel->chambres[y].ag){
                            tmp[i] = Hotel->chambres[y].ag;
                            i++;
                        }
                    }
                }
            }
        }

        
        check_is = true;
        while(check_is){
            printf("L'agencement : ");
            for(int j= 0; j<i; j++){
                if(tmp[j] == simple) printf("1 - Simple ,");
                if(tmp[j] == doubl) printf(" 2 - Double ,");
                if(tmp[j] == triple) printf(" 3 - Triple ,");
                if(tmp[j] == quadruple) printf(" 4 - Quadruple ");
            }
            printf("\n");
            int test = 0;
            do{
                test = scanf("%d", &input[2]);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
            for(int u = 0; u<i; u++){
                if(input[2] == tmp[u]) check_is = false;
            }
        }
        printf("Pour resumer : ");
        print_type_chambre(input[0]);
        print_suite_deluxe(input[1]);
        print_agencement(input[2]);
        printf("\n");
        do{
            printf("1 - Modifier la reservation , 2 - Continuer\n");
            int test = 0;
            do{
                test = scanf("%d", &choix);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
        }while(choix != 1 && choix != 2);
    }

    
    reservation_client *newRes = malloc(sizeof(reservation_client));
    if(newRes == NULL) exit(0);

    while(date_choix == 1 && reser_done == false){
        do{
            printf("La date d'arrivee : DD/MM/YYYY\n");
            scanf("%d/%d/%d", &input[3], &input[4], &input[5]);
        }while(date_valide(input[3], input[4], input[5]));
        input[6] = -1;
        do{
            printf("Le nombre de jours :\n");
            int test = 0;
            do{
                test = scanf("%d", &input[6]);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
        }while(input[6]<=0);

        newRes->arrivee.jour = input[3];
        newRes->arrivee.mois = input[4];
        newRes->arrivee.annee = input[5];
        newRes->nombre_jours = input[6];
        newRes->depart = *addDays(newRes->arrivee, newRes->nombre_jours);

        
        num_chambres = recupNumeroChambre(Hotel, input[0], input[1], input[2], &size);
        
        for(int i = 0; i<size; i++){
            if(reser_done == false){
                nb_res_chambre = 0;
                current_chambre = num_chambres[i];
                for(int i = 0; i<Res->nb_reservations; i++){
                    if(Res->reservations[i].numero_chambre == current_chambre) nb_res_chambre++;
                }

                if(nb_res_chambre == 0){
                    Res->nb_reservations++;
                    newRes->numero_chambre = current_chambre;
                    Res->reservations = realloc(Res->reservations, (Res->nb_reservations) * sizeof(reservation_client));
                    Res->reservations[Res->nb_reservations-1] = *newRes;
                    reser_done = true;
                    break;
                }

                else if(nb_res_chambre == 1){
                    reservation *Res_chambre_current = recupReserChambre(Res, nb_res_chambre, num_chambres[i]);
                    if(est_superieure(newRes->arrivee, Res_chambre_current->reservations[0].depart)){
                        Res->nb_reservations++;
                        newRes->numero_chambre = current_chambre;
                        Res->reservations = realloc(Res->reservations, (Res->nb_reservations) * sizeof(reservation_client));
                        Res->reservations[Res->nb_reservations-1] = *newRes;
                        reser_done = true;
                        free(Res_chambre_current->reservations);
                        free(Res_chambre_current);
                        break;  
                    }else if(est_inferieure(newRes->depart, Res_chambre_current->reservations[0].arrivee) && !est_inferieure_current(newRes->arrivee)){
                        Res->nb_reservations++;
                        newRes->numero_chambre = current_chambre;
                        Res->reservations = realloc(Res->reservations, (Res->nb_reservations) * sizeof(reservation_client));
                        Res->reservations[Res->nb_reservations-1] = *newRes;
                        reser_done = true;
                        free(Res_chambre_current->reservations);
                        free(Res_chambre_current);
                        break;  
                    }
                }

                else if(nb_res_chambre > 1){
                    reservation *Res_chambre_current = recupReserChambre(Res, nb_res_chambre, num_chambres[i]);
                    if(est_inferieure(newRes->depart, Res_chambre_current->reservations[0].arrivee) && !est_inferieure_current(newRes->arrivee)){
                        Res->nb_reservations++;
                        newRes->numero_chambre = current_chambre;
                        Res->reservations = realloc(Res->reservations, (Res->nb_reservations) * sizeof(reservation_client));
                        Res->reservations[Res->nb_reservations-1] = *newRes;
                        reser_done = true;
                        free(Res_chambre_current->reservations);
                        free(Res_chambre_current);
                        break;
                    }
                    else if(est_superieure(newRes->arrivee, Res_chambre_current->reservations[nb_res_chambre-1].depart)){
                        Res->nb_reservations++;
                        newRes->numero_chambre = current_chambre;
                        Res->reservations = realloc(Res->reservations, (Res->nb_reservations) * sizeof(reservation_client));
                        Res->reservations[Res->nb_reservations-1] = *newRes;
                        reser_done = true;
                        free(Res_chambre_current->reservations);
                        free(Res_chambre_current);
                        break;
                    }else{
                        for(int j = 0; j<nb_res_chambre-1; j++){
                            if(est_inferieure(Res->reservations[j].depart, newRes->arrivee) && est_superieure(Res->reservations[j+1].arrivee, newRes->depart)){
                                Res->nb_reservations++;
                                newRes->numero_chambre = current_chambre;
                                Res->reservations = realloc(Res->reservations, (Res->nb_reservations) * sizeof(reservation_client));
                                Res->reservations[Res->nb_reservations-1] = *newRes;
                                reser_done = true;
                                free(Res_chambre_current->reservations);
                                free(Res_chambre_current);
                                break;
                            }
                        }
                    }
                    
                }
            }else{
                break;
            }
        }
        if(reser_done == false){
            printf("> Aucune reservation n'est possible pour les dates demandees. Voici les creneaux disponibles : \n");
            for(int i = 0; i<size; i++){
                nb_res_chambre = 0;
                for(int j = 0; j<Res->nb_reservations; j++){
                    if(Res->reservations[j].numero_chambre == current_chambre) nb_res_chambre++;
                }
                reservation *Res_chambre_current;
                if(nb_res_chambre != 0){
                    Res_chambre_current = recupReserChambre(Res, nb_res_chambre, num_chambres[i]);
                }
                date today = current_date();
                printf("%d/%d/%d - ", today.jour, today.mois, today.annee);
                if(nb_res_chambre == 1){
                    printf("%d/%d/%d\n", Res_chambre_current->reservations[0].arrivee.jour, Res_chambre_current->reservations[0].arrivee.mois, Res_chambre_current->reservations[0].arrivee.annee);
                    printf("%d/%d/%d - \n", Res_chambre_current->reservations[0].depart.jour, Res_chambre_current->reservations[0].depart.mois, Res_chambre_current->reservations[0].depart.annee);
                }else if (nb_res_chambre > 1){
                    printf("%d/%d/%d\n", Res_chambre_current->reservations[0].arrivee.jour,Res_chambre_current->reservations[0].arrivee.mois, Res_chambre_current->reservations[0].arrivee.annee);
                    for(int j = 0; j<nb_res_chambre-1; j++){
                        printf("%d/%d/%d - ", Res_chambre_current->reservations[j].depart.jour,Res_chambre_current->reservations[j].depart.mois, Res_chambre_current->reservations[j].depart.annee);
                        printf("%d/%d/%d\n", Res_chambre_current->reservations[j+1].arrivee.jour,Res_chambre_current->reservations[j+1].arrivee.mois, Res_chambre_current->reservations[j+1].arrivee.annee); 
                    }
                    printf("%d/%d/%d - \n", Res_chambre_current->reservations[nb_res_chambre-1].depart.jour,Res_chambre_current->reservations[nb_res_chambre-1].depart.mois, Res_chambre_current->reservations[nb_res_chambre-1].depart.annee);
                }
                free(Res_chambre_current->reservations);
                free(Res_chambre_current);
            }
            do{
                printf("1 - Modifier la date , 2 - Annuler la reservation\n");
                int test = 0;
                do{
                    test = scanf("%d", &date_choix);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(date_choix != 1 && date_choix != 2);
        }
    }
    if(date_choix == 2){
        printf("> Annulation de la reservation...\n");
        free(newRes);
    }else{
        if(input[0] != 3){
            printf("Terminons par les options : \n");
            do{
                printf("Petit-dejeuner : 1 - Oui , 0 - Non\n");
                int test = 0;
                do{
                    test = scanf("%d", &newRes->option_client.petit_dejeuner);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(newRes->option_client.petit_dejeuner != 1 && newRes->option_client.petit_dejeuner != 0);
            do{
                printf("Chaines-TV : 1 - Oui , 0 - Non\n");
                int test = 0;
                do{
                    test = scanf("%d", &newRes->option_client.chaines_tv);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(newRes->option_client.chaines_tv != 1 && newRes->option_client.chaines_tv != 0);
            do{
                printf("Salle de sport : 1 - Oui , 0 - Non\n");
                int test = 0;
                do{
                    test = scanf("%d", &newRes->option_client.salle_de_sport);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(newRes->option_client.salle_de_sport != 1 && newRes->option_client.salle_de_sport != 0);
            do{
                printf("Piscine : 1 - Oui , 0 - Non\n");
                int test = 0;
                do{
                    test = scanf("%d", &newRes->option_client.piscine);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(newRes->option_client.piscine != 1 && newRes->option_client.piscine != 0);
            do{
                printf("Spa : 1 - Oui , 0 - Non\n");
                int test = 0;
                do{
                    test = scanf("%d", &newRes->option_client.spa);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(newRes->option_client.spa != 1 && newRes->option_client.spa != 0);
        }else{
            printf("Toutes les options sont offertes avec les suites deluxes.\n");
            newRes->option_client.petit_dejeuner = true;
            newRes->option_client.chaines_tv = true;
            newRes->option_client.salle_de_sport = true;
            newRes->option_client.piscine = true;
            newRes->option_client.spa = true;
        }
        for(int i = 0; i<Hotel->nb_chambres; i++){
            if(Hotel->chambres[i].numero_chambre == newRes->numero_chambre){
                newRes->prix_total = Hotel->chambres[i].prix_nuit;
                break;
            }
        }
        newRes->prix_total = newRes->prix_total * newRes->nombre_jours;
        if(input[0] != 3){
            if(newRes->option_client.petit_dejeuner == true) newRes->prix_total = newRes->prix_total + Hotel->prix_options[0];
            if(newRes->option_client.chaines_tv == true) newRes->prix_total = newRes->prix_total + Hotel->prix_options[1];
            if(newRes->option_client.salle_de_sport == true) newRes->prix_total = newRes->prix_total + Hotel->prix_options[2];
            if(newRes->option_client.piscine == true) newRes->prix_total = newRes->prix_total + Hotel->prix_options[3];
            if(newRes->option_client.spa == true) newRes->prix_total = newRes->prix_total + Hotel->prix_options[4];
        }
        printf("Prix total de la reservation : \n%d EUROS\n", newRes->prix_total);
        do{
            printf("1 - Valider la reservation , 2 - Annuler la reservation\n");
            int test = 0;
            do{
                test = scanf("%d", &valide_reser);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
        }while(valide_reser != 1 && valide_reser != 2);
        if(valide_reser == 2){
            printf("> Annulation de la reservation...\n");
            free(newRes);
            Res->nb_reservations--;
        }else{
            do{
                strcpy(string_tmp, "");
                printf("Entrez votre nom (sans espaces, max 30 carateres) : \n");
                scanf("%29s", string_tmp);
                scanf("%*[^\n]");
            }while(strlen(string_tmp) > 29);
            strcpy(newRes->nom_client, string_correct(string_tmp));
            
            
            for(int i = 1; i<Res->nb_reservations+1; i++){
                counter = 1;
                for(int j = 0; j<Res->nb_reservations-1; j++){
                    if(Res->reservations[j].numero_reservation == i) break;
                    counter++;
                }
                if(counter == Res->nb_reservations){
                    newRes->numero_reservation = i;
                    numero_reser_find = true;
                    break;
                }
            }
            if(numero_reser_find == false){
                newRes->numero_reservation = Res->nb_reservations;
            }
            Res->reservations[Res->nb_reservations-1] = *newRes;
            free(newRes);
            printf("> La reservation a ete effectue ! Rappel :\n");
            printf("Numero de la reservation : %d\nDate d'arrivee : %d/%d/%d\nDate de depart : %d/%d/%d\nNumero de la chambre : %d\nPrix total : %d\n", Res->reservations[Res->nb_reservations-1].numero_reservation, Res->reservations[Res->nb_reservations-1].arrivee.jour, Res->reservations[Res->nb_reservations-1].arrivee.mois, Res->reservations[Res->nb_reservations-1].arrivee.annee, Res->reservations[Res->nb_reservations-1].depart.jour, Res->reservations[Res->nb_reservations-1].depart.mois, Res->reservations[Res->nb_reservations-1].depart.annee, Res->reservations[Res->nb_reservations-1].numero_chambre, Res->reservations[Res->nb_reservations-1].prix_total);
            printf("Merci d'avoir effectue votre reservation avec Hotel Management !\n");
        }
    }
    free(num_chambres);
    free(input);
    sleep(2);
}
