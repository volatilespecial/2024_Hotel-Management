#ifndef TRIE_H
#define TRIE_H

#include <stdlib.h>

#include "struct_enum.h"

//Compare les valeurs
int compare_reservations(const void *a, const void *b);

//Trie avec qsort
void trie_reservations(reservation *Res);

#endif