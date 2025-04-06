#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "patient.h"
#include "doctor.h"
#include <time.h>

#define MAX_PURPOSE_LEN 100

typedef struct {
    int appointment_id;
    Patient patient;
    Doctor doctor;
    time_t datetime;
} Appointment;

// BST thoi gian
typedef struct BSTNode {
    Appointment data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

// Queue process order benh nhan
typedef struct QueueNode {
    Appointment data;
    struct QueueNode* next;
} QueueNode;

typedef struct {
    BSTNode* bst_root;
    QueueNode* queue_front;
    QueueNode* queue_rear;
    int count;
} AppointmentSystem;


void init_appointment_system(AppointmentSystem* system);
int book_appointment(AppointmentSystem* system, Patient patient, Doctor doctor, time_t datetime);
Appointment* get_next_appointment(const AppointmentSystem* system);
void find_appointments_in_range(const AppointmentSystem* system,
    time_t start,
    time_t end,
    const Appointment** results,  // Keep const here
    int* count);

void free_appointment_system(AppointmentSystem* system);
void display_appointment(AppointmentSystem* system);
void free_appointment_system(AppointmentSystem* system);
void pick_next_appointment(AppointmentSystem* appt_system);
void inorder_appointment(struct BSTNode* root);
void generate_appointment_from_file(AppointmentSystem* appt_system);
void free_bst(BSTNode* node);
void display_queue_appointment(AppointmentSystem* system);

#endif