#include "../Headers/menu_func.h"

void voir_reservations(reservation *Res){
    if(Res->nb_reservations == 0){
        printf("> Aucune reservation dans le fichier.\n");
    }else{
        trie_reservations(Res);
        for(int i = 0; i<Res->nb_reservations; i++){
            printf("N.%d, Nom : %s, Chambre : %d, Date d'arrivee : %d/%d/%d, Date de depart : %d/%d/%d, Prix total : %d EUROS\n", Res->reservations[i].numero_reservation, Res->reservations[i].nom_client, Res->reservations[i].numero_chambre, Res->reservations[i].arrivee.jour, Res->reservations[i].arrivee.mois, Res->reservations[i].arrivee.annee, Res->reservations[i].depart.jour, Res->reservations[i].depart.mois, Res->reservations[i].depart.annee, Res->reservations[i].prix_total);
        }
    }
    sleep(2);
}

void chercher_reservation(reservation *Res){
    int num_res;
    bool reser_find = false;
    printf("Entrez le numero de la reservation : \n");
    int test = 0;
    do{
        test = scanf("%d",&num_res);
            if (test != 1){
            printf("Erreur de format. Veuillez entrer un nombre :\n");
            scanf("%*[^\n]");
        }
    }while(test !=1);
    for(int i = 0; i<Res->nb_reservations; i++){
        if(Res->reservations[i].numero_reservation == num_res){
            printf("N.%d, Nom : %s, Chambre : %d, Date d'arrivee : %d/%d/%d, Date de depart : %d/%d/%d, Prix total : %d\n", Res->reservations[i].numero_reservation, Res->reservations[i].nom_client, Res->reservations[i].numero_chambre, Res->reservations[i].arrivee.jour, Res->reservations[i].arrivee.mois, Res->reservations[i].arrivee.annee, Res->reservations[i].depart.jour, Res->reservations[i].depart.mois, Res->reservations[i].depart.annee, Res->reservations[i].prix_total);
            printf("Petit-dejeuner : %s, Chaines TV : %s, Salle de sport : %s, Piscine : %s, Spa : %s\n", check_bool(Res->reservations[i].option_client.petit_dejeuner), check_bool(Res->reservations[i].option_client.chaines_tv), check_bool(Res->reservations[i].option_client.salle_de_sport), check_bool(Res->reservations[i].option_client.piscine), check_bool(Res->reservations[i].option_client.spa));
            reser_find = true;
            break;
        }
    }
    if(reser_find == false){
        printf("> Aucune reservation avec ce numero. Veuillez reessayer.\n");
        sleep(2);
    }
}

void ajouter_reservation(hotel *Hotel, reservation *Res){
    input_reservation(Hotel, Res);
    trie_reservations(Res);
}

void modifier_reservation(hotel *Hotel, reservation *Res){
    int choix_user;
    bool reser_find = false;
    int num_res;
    int index_res;
    date new;
    do{
        printf("Vous pouvez modifier seulement la date d'arrivee et la date de depart. Si vous souhaitez modifier autre chose, supprimez la reservation et ajoutez une nouvelle reservation.\n1 - Continuer , 0 - Quitter\n");
        int test = 0;
        do{
        test = scanf("%d",&choix_user);
            if (test != 1){
            printf("Erreur de format. Veuillez entrer un nombre :\n");
            scanf("%*[^\n]");
            }
        }while(test !=1);
    }while(choix_user != 1 && choix_user != 0);
    if(choix_user == 0){
        printf("> Modification annulee...\n");
        sleep(2);
    }else{
        printf("Entrez le numero de la reservation : \n");
        int test = 0;
        do{
            test = scanf("%d",&num_res);
                if (test != 1){
                printf("Erreur de format. Veuillez entrer un nombre :\n");
                scanf("%*[^\n]");
            }
        }while(test !=1);
        for(int i = 0; i<Res->nb_reservations; i++){
            if(Res->reservations[i].numero_reservation == num_res){
                printf("Chambre : %d, Date d'arrivee : %d/%d/%d, Date de depart : %d/%d/%d\n", Res->reservations[i].numero_chambre, Res->reservations[i].arrivee.jour, Res->reservations[i].arrivee.mois, Res->reservations[i].arrivee.annee, Res->reservations[i].depart.jour, Res->reservations[i].depart.mois, Res->reservations[i].depart.annee);
                index_res = i;
                reser_find = true;
                break;
            }
        }
        if(reser_find == false){
            printf("> Aucune reservation avec ce numero. Veuillez reessayer.\n");
            sleep(2);
        }else{
            modif_date_res(Hotel, Res, index_res);
            trie_reservations(Res);
        }
    }  
}

void supprimer_reservation(reservation *Res){
    int reser_aSupp;
    int index_aSupp = -1;
    int confirm_Supp = 0;
    reservation_client *newArray;
    printf("Entrez le numero de la reservation a supprimer : \n");
	int test = 0;
	do{
		test = scanf("%d",&reser_aSupp);
			if (test != 1){
			printf("Erreur de format. Veuillez entrer un nombre :\n");
			scanf("%*[^\n]");
		}
	}while(test !=1);
    for(int i = 0; i<Res->nb_reservations; i++){
        if(Res->reservations[i].numero_reservation == reser_aSupp){
            index_aSupp = i;
            break;
        }
    }
    if(index_aSupp == -1){
        printf("> La reservation n'a pas ete trouve. Veuillez reessayer.\n");
        sleep(2);
    }else{
        printf("N.%d, Nom : %s, Chambre : %d, Date d'arrivee : %d/%d/%d, Date de depart : %d/%d/%d, Prix total : %d\n", Res->reservations[index_aSupp].numero_reservation, Res->reservations[index_aSupp].nom_client, Res->reservations[index_aSupp].numero_chambre, Res->reservations[index_aSupp].arrivee.jour, Res->reservations[index_aSupp].arrivee.mois, Res->reservations[index_aSupp].arrivee.annee, Res->reservations[index_aSupp].depart.jour, Res->reservations[index_aSupp].depart.mois, Res->reservations[index_aSupp].depart.annee, Res->reservations[index_aSupp].prix_total);
        printf("Petit-dejeuner : %s, Chaines TV : %s, Salle de sport : %s, Piscine : %s, Spa : %s\n", check_bool(Res->reservations[index_aSupp].option_client.petit_dejeuner), check_bool(Res->reservations[index_aSupp].option_client.chaines_tv), check_bool(Res->reservations[index_aSupp].option_client.salle_de_sport), check_bool(Res->reservations[index_aSupp].option_client.piscine), check_bool(Res->reservations[index_aSupp].option_client.spa));
        do{
            printf("Voulez-vous supprimer cette reservation ?\nAttention, cette action est irreversible !\n1 - Oui , 0 - Non\n");
            int test = 0;
            do{
                test = scanf("%d",&confirm_Supp);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
        }while(confirm_Supp != 1 && confirm_Supp != 0);
        if(confirm_Supp == 0){
            printf("> Suppression annulee...\n");
            sleep(2);
        }else{
            newArray = malloc((Res->nb_reservations-1) * sizeof(reservation_client));
            if(newArray == NULL) exit(0);
            memmove(newArray, Res->reservations, index_aSupp * sizeof(reservation_client));
            memmove(newArray + index_aSupp, Res->reservations + index_aSupp + 1, (Res->nb_reservations - index_aSupp - 1) * sizeof(reservation_client));
            free(Res->reservations);
            Res->reservations = newArray;
            Res->nb_reservations--;
            printf("> Reservation supprimee !\n");
            trie_reservations(Res);
            sleep(2);
        }
    }
}

void ajoutChambre(hotel *Hotel){
    int confirm_ch;
    chambre *aAjouter = malloc(sizeof(chambre));
    if(aAjouter == NULL) exit(0);
    printf("Entrez les details de la nouvelle chambre : \n");
    do{
        printf("Type de la chambre : 1 pour standard, 2 pour communicante, 3 pour deluxe, 4 pour accessible\n");
        int test = 0;
        do{
            test = scanf("%d",&aAjouter->tc);
                if (test != 1){
                printf("Erreur de format. Veuillez entrer un nombre :\n");
                scanf("%*[^\n]");
            }
        }while(test !=1);
    }while(aAjouter->tc!=1 && aAjouter->tc!=2 && aAjouter->tc!=3 && aAjouter->tc!=4);

    if(aAjouter->tc == deluxe){
        do{
            printf("Deluxe : 1 pour suite executive, 2 pour suite junior, 3 pour suite presidentielle\n");
            int test = 0;
            do{
                test = scanf("%d",&aAjouter->sd);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
         }while(aAjouter->sd!=1 && aAjouter->sd!= 2 && aAjouter->sd!=3);
    }else{
        aAjouter->sd = 0;
    }
    do{
        printf("Agencement : 1 pour simple, 2 pour double, 3 pour triple, 4 pour quadruple\n");
        int test = 0;
        do{
            test = scanf("%d",&aAjouter->ag);
                if (test != 1){
                printf("Erreur de format. Veuillez entrer un nombre :\n");
                scanf("%*[^\n]");
            }
        }while(test !=1);
    }while(aAjouter->ag!= 1 && aAjouter->ag!= 2 && aAjouter->ag!=3 && aAjouter->ag!= 4);
    
    bool numero_dispo = false;
    int counter;
    printf("Le prix d'une nuit pour cette chambre : ");
    int test = 0;
    do{
        test = scanf("%d",&aAjouter->prix_nuit);
            if (test != 1){
            printf("Erreur de format. Veuillez entrer un nombre :\n");
            scanf("%*[^\n]");
        }
    }while(test !=1);

    while(numero_dispo == false){
        counter = 0;
        printf("Entrez le numero de la chambre : \n");
        int test = 0;
        do{
            test = scanf("%d",&aAjouter->numero_chambre);
                if (test != 1){
                printf("Erreur de format. Veuillez entrer un nombre :\n");
                scanf("%*[^\n]");
            }
        }while(test !=1);

        for(int i = 0; i<Hotel->nb_chambres; i++){
            if(Hotel->chambres[i].numero_chambre == aAjouter->numero_chambre){
                printf("> Le numero de la chambre n'est pas disponible. Veuillez reessayer.\n");
                break;
            }else{
                counter++;
            }
        }
        if(counter == Hotel->nb_chambres){
            numero_dispo = true;
        }
    }
    printf("Pour resumer :\nNumero de la chambre %d, ", aAjouter->numero_chambre);
    print_type_chambre(aAjouter->tc);
    print_suite_deluxe(aAjouter->sd);
    print_agencement(aAjouter->ag);
    printf("\n");
    do{
        printf("1 - Confirmer la nouvelle chambre , 0 - Annuler la nouvelle chambre\n");
        int test = 0;
        do{
            test = scanf("%d",&confirm_ch);
                if (test != 1){
                printf("Erreur de format. Veuillez entrer un nombre :\n");
                scanf("%*[^\n]");
            }
        }while(test !=1);
    }while(confirm_ch != 1 && confirm_ch != 0);
    if(confirm_ch == 0){
        printf("> Annulation de la nouvelle chambre...\n");
        free(aAjouter);
        sleep(2);
    }else{
        Hotel->nb_chambres++;
        Hotel->chambres = realloc(Hotel->chambres, Hotel->nb_chambres * sizeof(chambre));
        Hotel->chambres[Hotel->nb_chambres-1] = *aAjouter;
        free(aAjouter);
    }
}

void supprimer_chambre(hotel *Hotel, reservation *Res){
    int ch_Supp;
    printf("Entrez le numero de la chambre a supprimer : \n");
    int test = 0;
    do{
        test = scanf("%d",&ch_Supp);
            if (test != 1){
            printf("Erreur de format. Veuillez entrer un nombre :\n");
            scanf("%*[^\n]");
        }
    }while(test !=1);
    bool check_num_ch = false;
    int index_Supp = -1;
    chambre *newArray;
    int *reser_num = malloc(1 * sizeof(int));
    int size = 0;
    int j = 0;
    for(int i = 0; i<Hotel->nb_chambres; i++){
        if(Hotel->chambres[i].numero_chambre == ch_Supp){
            check_num_ch = true;
            index_Supp = i;
            break;
        }
    }
    if(check_num_ch == false){
        printf("> La chambre n'existe pas. Veuillez reessayer.\n");
        free(reser_num);
        free(newArray);
        sleep(2);
        return;
    }else{
        newArray = malloc((Hotel->nb_chambres - 1) * sizeof(chambre));
        if(newArray == NULL) exit(0);
        memcpy(newArray, Hotel->chambres, index_Supp * sizeof(chambre));
        memcpy(newArray + index_Supp, Hotel->chambres + index_Supp + 1, (Hotel->nb_chambres - index_Supp - 1) * sizeof(chambre));
        Hotel->nb_chambres--;
        free(Hotel->chambres);
        Hotel->chambres = newArray;
        printf("> La chambre a ete supprime !\n");
        for(int i = 0; i<Res->nb_reservations; i++){
            if(Res->reservations[i].numero_chambre == ch_Supp){
            size++;
            reser_num = realloc(reser_num, size * sizeof(int));
            reser_num[j] = Res->reservations[i].numero_reservation;
            j++;
            if (reser_num == NULL) exit(0);
            }
        }
        for(int i = 0; i<size; i++){
            supprimer_reservation_aux(Res, reser_num[i]);
        }
        printf("> Les reservations ont ete supprimees !\n");
    }
    free(reser_num);
    sleep(2);
}

void modifier_chambre(hotel *Hotel, reservation *Res){
    int num_ch_Mod;
    bool check_num_ch = false;
    int index_Mod = -1;
    int confirm;
    int mod;
    int *reser_num = malloc(1 * sizeof(int));
    int size = 0;
    int j = 0;
    printf("Entrez le numero de la chambre a modifier : \n");
    int test = 0;
    do{
        test = scanf("%d",&num_ch_Mod);
            if (test != 1){
            printf("Erreur de format. Veuillez entrer un nombre :\n");
            scanf("%*[^\n]");
        }
    }while(test !=1);
    chambre *new = malloc(sizeof(chambre));
    if(new == NULL) exit(0);
    for(int i = 0; i<Hotel->nb_chambres; i++){
        if(Hotel->chambres[i].numero_chambre == num_ch_Mod){
            check_num_ch = true;
            index_Mod = i;
            break;
        }
    }
    if(check_num_ch == false){
        printf("> La chambre n'existe pas. Veuilez reessayer.\n");
        sleep(2);
    }else{
        printf("Chambre a modifier : N.%d, ", Hotel->chambres[index_Mod].numero_chambre);
        print_type_chambre(Hotel->chambres[index_Mod].tc);
        print_suite_deluxe(Hotel->chambres[index_Mod].sd);
        print_agencement(Hotel->chambres[index_Mod].ag);
        printf(", Prix : %d EUROS/nuit\n", Hotel->chambres[index_Mod].prix_nuit);
        do{
            printf("1 - Continuer , 0 - Annuler la modification\n");
            int test = 0;
            do{
                test = scanf("%d",&confirm);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);
        }while(confirm != 1 && confirm != 0);
        if(confirm == 0){
            printf("> Annulation de la modification...\n");
            sleep(2);
        }else{
            do{
                printf("Type de la chambre : 1 pour standard, 2 pour communicante, 3 pour deluxe, 4 pour accessible\n");
                int test = 0;
                do{
                    test = scanf("%d",&new->tc);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(new->tc!=1 && new->tc!=2 && new->tc!=3 && new->tc!=4);

            if(new->tc == deluxe){
                do{
                    printf("Deluxe : 1 pour suite executive, 2 pour suite junior, 3 pour suite presidentielle\n");
                    int test = 0;
                    do{
                        test = scanf("%d",&new->sd);
                            if (test != 1){
                            printf("Erreur de format. Veuillez entrer un nombre :\n");
                            scanf("%*[^\n]");
                        }
                    }while(test !=1);
                }while(new->sd!=1 && new->sd!= 2 && new->sd!=3);
            }else{
                new->sd = 0;
            }

            do{
                printf("Agencement : 1 pour simple, 2 pour double, 3 pour triple, 4 pour quadruple\n");
                scanf("%d", &new->ag);
            }while(new->ag!= 1 && new->ag!= 2 && new->ag!=3 && new->ag!= 4);
        
            printf("Le prix d'une nuit pour cette chambre : ");
            int test = 0;
            do{
                test = scanf("%d",&new->prix_nuit);
                    if (test != 1){
                    printf("Erreur de format. Veuillez entrer un nombre :\n");
                    scanf("%*[^\n]");
                }
            }while(test !=1);

            printf("Pour resumer : \nN.%d, ", Hotel->chambres[index_Mod].numero_chambre);
            print_type_chambre(new->tc);
            print_suite_deluxe(new->sd);
            print_agencement(new->ag);
            printf("\n");
            do{
                printf("1 - Modifier , 0 - Annuler\n");
                
                int test = 0;
                do{
                    test = scanf("%d",&mod);
                        if (test != 1){
                        printf("Erreur de format. Veuillez entrer un nombre :\n");
                        scanf("%*[^\n]");
                    }
                }while(test !=1);
            }while(mod != 1 && mod != 0);
            if(mod == 0){
                printf("> Annulation de la modification...\n");
                sleep(2);
            }else{
                Hotel->chambres[index_Mod].tc = new->tc;
                Hotel->chambres[index_Mod].sd = new->sd;
                Hotel->chambres[index_Mod].ag = new->ag;
                Hotel->chambres[index_Mod].prix_nuit = new->prix_nuit;
                for(int i = 0; i<Res->nb_reservations; i++){
                    if(Res->reservations[i].numero_chambre == Hotel->chambres[index_Mod].numero_chambre){
                        size++;
                        reser_num = realloc(reser_num, size * sizeof(int));
                        reser_num[j] = Res->reservations[i].numero_reservation;
                        j++;
                        if (reser_num == NULL) exit(0);
                    }
                }
                printf("> La chambre a ete modifie !\n");
                for(int i = 0; i<size; i++){
                    supprimer_reservation_aux(Res, reser_num[i]);
                }
                printf("> Les reservations ont ete supprimees !\n");
            }
        }
    }
    free(reser_num);
    free(new);
}

void modifier_hotel(hotel *Hotel, reservation *Res){
    int choix;
    do{
        printf("1 - Ajouter une chambre , 2 - Supprimer une chambre , 3 - Modifier une chambre , 0 - Revenir au menu principal\n");
        printf("Supprimer ou modifier une chambre supprimera toutes les reservations liees a cette chambre ! Cette action est irreversible !\n");
        int test = 0;
        do{
            test = scanf("%d",&choix);
                if (test != 1){
                printf("Erreur de format. Veuillez entrer un nombre :\n");
                scanf("%*[^\n]");
            }
        }while(test !=1);
    }while(choix != 1 && choix !=2 && choix != 3 && choix != 0);
    if(choix == 1){
        ajoutChambre(Hotel);
    }
    if(choix == 2){
        supprimer_chambre(Hotel, Res);
    }
    if(choix == 3){
        modifier_chambre(Hotel, Res);
    }else{
        return;
    }
}
