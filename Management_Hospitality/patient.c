#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "utils.h"


Node* head = NULL;

void add_patient() {
    Patient new_patient;
    printf("Enter the patient's name: ");
    scanf("%s", new_patient.name);
    printf("Enter the patient's age: ");
    scanf("%d", &new_patient.age);
    printf("Enter the patient's gender: ");
    scanf("%s", new_patient.gender);
    Node* new_node = (Node*) malloc(sizeof(Node));
    
    if (new_node == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    new_patient.id = generate_patient_id();
    new_node->data = new_patient;
    new_node->next = NULL;

    if (head == NULL) {
        head = new_node;
    } else {
        Node* current = head;
        while (current -> next != NULL) {
            current = current -> next;
        }
        
        current -> next = new_node;
    }
    printf("Successfully adding patient\n\n");
    
}
void search_patient() {
    printf("List of Patient Name:\n");
    Node* current = head;
    while (current != NULL) {
        printf("%s\n", current->data.name);
        current = current -> next;
    }
    printf("Enter the patient name who you want to find his/her information: ");
    char name[100];
    scanf("%99s", name);
    current = head;
    int check = 0;
    while (current != NULL) {
        if (strcmp(current->data.name,name) == 0) {
            printf("Name: %s, Age: %d, Gender: %s\n", current->data.name, current->data.age, current->data.gender);
            check = 1;
        }
        current = current->next;
    }
    if (!check) {
        printf("Can not find the given patient name in the list.\n");
    }
}
void display_patient_info() {
    Node* current = head;
    printf("Patient List:\n");
    int count = 0;
    while (current != NULL) {
        count++;
        printf("ID: %d, Name: %s, Age: %d, Gender: %s\n", current->data.id, current->data.name, current->data.age, current->data.gender);
        current = current -> next;
    }

    printf("\n");
}

void delete_patient() {

    printf("List of Patient Name:\n");
    Node* current = head;
    while (current != NULL) {
        printf("%s\n", current->data.name);
        current = current -> next;
    }

    printf("Enter the name that you want to remove in the list:\n");
    char name[50];
    scanf("%s", name);
    current = head;
    Node* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->data.name, name) == 0) {
            if (prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }

            printf("Successfully delete that patient\n");
            free(current);
            return;
        }
        prev = current;
        current = current -> next;
    }
    printf("Patient with name %s not found.\n", name);
}

void free_list() {
    Node* current = head;
    while (current != NULL) {
        Node* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}
void save_patient_to_file() {
    FILE* f_open = fopen("data/patients.txt", "w");
    Node* current = head;   


    if (head == NULL) {
        return;
    } 
    
    while (current != NULL) {
        fprintf(f_open, "%s %d %s\n", current->data.name, current->data.age, current->data.gender);
        current = current -> next;
    }
    fclose(f_open);
}
void load_patient_from_file() {
    FILE* f_open = fopen("data/patients.txt", "r");
    Node* current;   


    if (head == NULL) {
        head = (Node*) malloc(sizeof(Node));
        fscanf(f_open, "%s %d %s", head->data.name, &head->data.age, head->data.gender);
        head->data.id = generate_patient_id();
        head->next = NULL;
        current = head;
    } else {
        current = head;
        while (current -> next != NULL) current = current -> next;
    }

    Patient human;
    while (fscanf(f_open, "%s %d %s", human.name, &human.age, human.gender) == 3) {
        Node* New_patient = (Node*) malloc(sizeof(Node));
        strcpy(New_patient->data.name, human.name);
        New_patient->data.age = human.age;
        strcpy(New_patient->data.gender, human.gender);
        New_patient->data.id = generate_patient_id();
        New_patient->next = NULL;
        current -> next = New_patient;
        current = current -> next;
    }
    printf("Successfully load data from patient file!\n");
    fclose(f_open);

}   