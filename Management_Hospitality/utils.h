#ifndef UTILS_H
#define UTILS_H

#include <time.h>
#include <stdbool.h>  // For bool type

/* Time Utility */
time_t create_time(int year, int mon, int day, int hour, int min);
/* ID Generation */
int generate_patient_id(void);




#endif // UTILS_H