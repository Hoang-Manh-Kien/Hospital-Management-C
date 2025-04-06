#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "appointment.h"
#include "doctor.h"
#include "patient.h"
#include "utils.h"
//BST


void init_appointment_system(AppointmentSystem* system) {
    system->bst_root = NULL;
    system->queue_front = NULL;
    system->queue_rear = NULL;
    system->count = 0;
}


//new node
static BSTNode* new_bst_node(Appointment appt) {
    BSTNode* node = (BSTNode*)malloc(sizeof(BSTNode));
    if (node) {
        node->data = appt;
        node->left = node->right = NULL;
    }
    return node;
}
//process appointment theo thu tu
static QueueNode* new_queue_node(Appointment appt) {
    QueueNode* node = (QueueNode*)malloc(sizeof(QueueNode));
    if (node) {
        node->data = appt; //appointment trong node
        node->next = NULL; //pointer tiep theo la NULLO
    }
    return node;
}



void inorder_appointment(struct BSTNode* root) {
    if (root == NULL) {
        return;
    }
    inorder_appointment(root->left);
    printf("Appt #%d:\n", root->data.appointment_id);
    printf("Patient information: Name: %s, Age: %d, Gender: %s\n", root->data.patient.name, root->data.patient.age, root->data.patient.gender);
    printf("Doctor: Name: %s, ID: %d\n\n", root->data.doctor.name, root->data.doctor.id);
    inorder_appointment(root->right);
}
void display_appointment(AppointmentSystem* appt_system) {
    if (appt_system->bst_root == NULL) return;
    inorder_appointment(appt_system->bst_root);
}


int hour = 0, min = 0;
void generate_appointment_from_file(AppointmentSystem* appt_system) {
    FILE* f1 = fopen("data/doctors.txt", "r");
    FILE* f2 = fopen("data/patients.txt", "r");
    FILE* f3 = fopen("data/appointments.txt", "w");
    Doctor doctor;
    Patient patient;


    time_t t;             // Biến kiểu time_t để lưu thời gian hiện tại
    struct tm *local_time;   // Con trỏ đến struct chứa thông tin thời gian

    time(&t);             // Lấy thời gian hiện tại
    local_time = localtime(&t);  // Chuyển đổi sang local time (giờ hệ thống)
    

    int year = local_time->tm_year + 1900;
    int month = local_time->tm_mon + 1;
    int day = local_time->tm_mday;
    printf("\nCurrent: %02d/%02d/%d\n\n", day, month, year);
    

    while ((fscanf(f1, "%99s %d", doctor.name, &doctor.id) == 2) &&
        fscanf(f2, "%s %d %s", patient.name, &patient.age, patient.gender) == 3)
        {

            printf("Doctor: %s, ID: %d ", doctor.name, doctor.id);
            printf("Patient: %s, Age: %d, Gender: %s |\n", patient.name, patient.age, patient.gender);
            printf("The time when the patient can treated by their doctor is: %d:00\n", hour + 1);
            
            fprintf(f3,"Doctor: %s, ID: %d ", doctor.name, doctor.id);
            fprintf(f3,"Patient: %s, Age: %d, Gender: %s |\n", patient.name, patient.age, patient.gender);
            fprintf(f3,"The time when the patient can treated by their doctor is: %d:00\n\n", hour + 1);
            
            time_t appt_time = create_time(year, month, day, hour, min);
            hour++;

            if (book_appointment(appt_system, patient, doctor, appt_time)) {
                printf("Appointment booked successfully!\n\n");
            } else {
                printf("Failed to book appointment (time slot may be taken)\n\n");
            }
    }
    
    while (fscanf(f1, "%s %d", doctor.name, &doctor.id) == 2) {
        // Xử lý dữ liệu bác sĩ còn lại
        printf("Doctor: %s, ID: %d\n", doctor.name, doctor.id);
    }
       
    while (fscanf(f2, "%s %d %s", patient.name, &patient.age, patient.gender) == 3) {
        // Xử lý dữ liệu bệnh nhân còn lại
        printf("Patient: %s, Age: %d, Gender: %s\n", patient.name, patient.age, patient.gender);
    }
    
    
    fclose(f1);
    fclose(f2);
    fclose(f3);
}

//book appointment
int book_appointment(AppointmentSystem* system, Patient patient, Doctor doctor, time_t datetime) {
    Appointment appt;
    appt.appointment_id = system->count + 1; //tao ID cho appointment
    appt.patient = patient;
    appt.doctor = doctor;
    appt.datetime = datetime; //store datetime appointment


    BSTNode** current = &system->bst_root;
    while (*current != NULL) {
        if (datetime < (*current)->data.datetime) {
            current = &((*current)->left);
        } else if (datetime > (*current)->data.datetime) {
            current = &((*current)->right);
        } else {
            return 0; 
        }
    }

    *current = new_bst_node(appt); // Gắn node mới vào cây
    if (*current == NULL) return 0;

    //queue node cho appointment 
    QueueNode* q_node = new_queue_node(appt);
    if (q_node == NULL) return 0;

    if (system->queue_rear == NULL) {
        system->queue_front = system->queue_rear = q_node;
    } else {
        system->queue_rear->next = q_node;
        system->queue_rear = q_node;
    }

    system->count++;
    return 1;
}

// Hiển thị các phần tử trong queue
void display_queue_appointment(AppointmentSystem* appt_system) {
    if (appt_system->queue_front == NULL) {
        printf("There are no patient in the current list\n");
        return;
    }
    QueueNode* head = appt_system->queue_front;
    while (head != NULL) {
        Appointment data = head->data;
        printf("Appt #%d:\n", data.appointment_id);
        printf("Patient information: Name: %s, Age: %d, Gender: %s\n", data.patient.name, data.patient.age, data.patient.gender);
        printf("Doctor: Name: %s, ID: %d\n\n", data.doctor.name, data.doctor.id);
        printf("Time: %s\n\n", ctime(&data.datetime));
        head = head->next;
    }
    
    printf("\n");
}

void pick_next_appointment(AppointmentSystem* appt_system) {
    if (appt_system->queue_front == NULL) return;
    QueueNode* next = appt_system->queue_front;
    Appointment front_data = next->data;
    
    printf("\nNext Appointment:\n");
    printf("Name: %s, Age: %d, Gender: %s\n", front_data.patient.name, front_data.patient.age, front_data.patient.gender);
    printf("Name: %s, ID: %d\n", front_data.doctor.name, front_data.doctor.id);
    printf("Time: %s", ctime(&front_data.datetime));
    
    appt_system->queue_front = appt_system->queue_front->next;

    if (appt_system->queue_front == NULL) {
        appt_system->queue_rear = NULL;
    }

    free(next);

    
            
}
//free memory
void free_bst(BSTNode* node) {
    if (node) {
        free_bst(node->left);
        free_bst(node->right);
        free(node);
    }
}

void free_appointment_system(AppointmentSystem* system) {
    free_bst(system->bst_root);
    
    while (system->queue_front) {
        QueueNode* temp = system->queue_front;
        system->queue_front = system->queue_front->next;
        free(temp);
    }
    free(system->queue_front);
    free(system->queue_rear = NULL);
    system->count = 0;
}