#ifndef PATIENT_H
#define PATIENT_H



// Khai báo struct Patient
typedef struct {
    int id;
    char name[50];
    int age;
    char gender[10];
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