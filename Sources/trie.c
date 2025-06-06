#include "../Headers/trie.h"

int compare_reservations(const void *a, const void *b){
    const reservation_client *res1 = (const reservation_client *)a;
    const reservation_client *res2 = (const reservation_client *)b;

    if (res1->numero_chambre != res2->numero_chambre) {
        return res1->numero_chambre - res2->numero_chambre;
    } else {
        if (res1->arrivee.annee != res2->arrivee.annee) {
            return res1->arrivee.annee - res2->arrivee.annee;
        } else if (res1->arrivee.mois != res2->arrivee.mois) {
            return res1->arrivee.mois - res2->arrivee.mois;
        } else {
            return res1->arrivee.jour - res2->arrivee.jour;
        }
    }
}

void trie_reservations(reservation *Res){
    qsort(Res->reservations, Res->nb_reservations, sizeof(reservation_client), compare_reservations);
}