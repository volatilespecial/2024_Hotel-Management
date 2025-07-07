#include "../Headers/check_bool_string.h"

bool check_string(char *x){
    if(strcmp(x, "true") == 0){
        return true;
    }else{
        return false;
    }
}

char* check_bool(bool x){
    if(x == true){
        return "true";
    }else{
        return "false";
    }
}

char* string_correct(char *x){
    char *res = malloc((strlen(x)+1) * sizeof(char));
    if (res == NULL) exit(0);
    for(int i = 0; i<strlen(x); i++){
        res[i] = x[i];
    }
    res[strlen(x)] = '\0';
    return res;
}