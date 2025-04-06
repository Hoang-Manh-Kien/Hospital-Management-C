#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"
#include <time.h>

time_t create_time(int year, int mon, int day, int hour, int min) {
    struct tm tm = {0};
    tm.tm_year = year - 1900;
    tm.tm_mon = mon - 1;
    tm.tm_mday = day;
    tm.tm_hour = hour;
    tm.tm_min = min;
    return mktime(&tm);
}

int count_from_one = 0;

int generate_patient_id() {
    count_from_one++;
    return count_from_one;
}   

