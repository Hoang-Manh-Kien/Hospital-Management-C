#ifndef PATIENT_H
#define PATIENT_H

#define MAX_NAME_LEN 49
#define MAX_GENDER_LEN 9

typedef struct {
    int id;
    char name[MAX_NAME_LEN + 1];
    int age;
    char gender[MAX_GENDER_LEN + 1];
} Patient;

typedef struct Node  {
    Patient data;
    struct Node* next;
} Node;
void add_patient();
void save_patient_to_file();
void load_patient_from_file();
void search_patient();
void display_patient_info();
void delete_patient();
void free_list();


#endif