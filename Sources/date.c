#include "../Headers/date.h"

date* addDays(date d1, int days){
    date *newDate = malloc(sizeof(date));
    if(newDate == NULL) exit(0);
    int year = 2024, m=3, d=31;
    struct tm t = {.tm_year = d1.annee-1900, .tm_mon = d1.mois-1, .tm_mday = d1.jour};
    t.tm_mday += days;
    mktime(&t);
    newDate->jour = t.tm_mday;
    newDate->mois = t.tm_mon+1;
    newDate->annee = t.tm_year+1900;
    return newDate;
}

bool is_leap_year(int year){
    if (year%4 == 0) return true;
    else return false;
}

int check_month(int month, int year){
    if(month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) return 31;
    if(month == 02){
        if(is_leap_year(year)) return 29;
        else return 28;
    }else{
        return 30;
    }
}

bool est_superieure(date d1, date d2){
    if (d1.annee > d2.annee) return true;
    if (d1.annee < d2.annee) return false;
    if (d1.mois > d2.mois) return true;
    if (d1.mois < d2.mois) return false;
    if (d1.jour > d2.jour) return true;
    if (d1.jour < d2.jour) return false;
    else return false;
}

bool est_inferieure(date d1, date d2){
    if (d1.annee < d2.annee) return true;
    if (d1.annee > d2.annee) return false;
    if (d1.mois < d2.mois) return true;
    if (d1.mois > d2.mois) return false;
    if (d1.jour < d2.jour) return true;
    if (d1.jour > d2.jour) return false;
    else return false;
    
}

bool est_inferieure_current(date d){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    if (d.annee < tm.tm_year+1900) return true;
    if (d.annee == tm.tm_year+1900 && d.mois < tm.tm_mon+1) return true;
    if (d.annee == tm.tm_year+1900 && d.mois == tm.tm_mon+1 && d.jour < tm.tm_mday) return true;
    return false;
}

date current_date(){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    date d;
    d.annee = tm.tm_year+1900;
    d.mois = tm.tm_mon+1;
    d.jour = tm.tm_mday;
    return d;
}

bool date_valide(int j, int m, int y){
    date d1;
    d1.jour = j;
    d1.mois = m;
    d1.annee = y;
    if (!est_inferieure_current(d1)) return false;
    if(y >= 1900 && y<=9999){
        if(m>=1 && m<12){
            if((j>=1 && j <= 31) && (m==1 || m==3 || m==5 || m==7 || m==8 || m==10 || m==12)){
                return true;
            }else if((j>=1 && j<=30) && (m==4 || m==6 || m==9 || m==11)){
                return true;
            }else if((j>=1 && j<=28) && (m==2)){
                return true;
            }else if((j==29 && m==2) && (y%400==0 || (y%4==0 && y%100!=0))){
                return false;
            }else{
                return false;
            }
        }else{
            return false;
        }
    }else{
        return false;
    }
}