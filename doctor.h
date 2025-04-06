#ifndef DOCTOR_H
#define DOCTOR_H

// Cấu trúc Doctor
typedef struct {
    char name[100];
    int id;
} Doctor;

struct Node_doctor {
    Doctor doctor;
    struct Node_doctor* left;
    struct Node_doctor* right;
};

typedef struct {
    Doctor* data;
    int size;
    int capacity;
} Vector;
void delete_doctor_by_name(Vector* v);
void init_doctor(Vector* v);
void load_doctor_from_file(Vector* v);
void list_doctor();
void add_doctor(Vector* v);
void search_doctor(Vector* v);
void save_doctor_to_file(Vector* v);
void delete_doctor_by_name(Vector* v);
struct Node_doctor* getNewNode(Doctor doctor);
struct Node_doctor* insert(struct Node_doctor* root, Doctor doctor);
Doctor search(struct Node_doctor* root, int doctor_id);
void search_doctor(Vector* v);
void inorder_doctor(struct Node_doctor* root);
void free_doctor(Vector* v);

#endif // DOCTOR_H