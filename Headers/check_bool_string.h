#ifndef CHECK_BOOL_STRING_H
#define CHECK_BOOL_STRING_H

#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//Verifie si x est "true" ou "false" et retourne true ou false
bool check_string(char *x);

//Verifie si x est true ou false et retourne "true" ou "false"
char* check_bool(bool x);

//Corrige la chaine de caracteres en ajoutant '\0' a la fin
char* string_correct(char *x);

#endif