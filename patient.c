#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "patient.h"
#include "utils.h"


Node* head = NULL;

void add_patient() {
    Patient new_patient;
    printf("Enter the patient's name: ");
    scanf("%49s", new_patient.name);  // Limit input length
    
    printf("Enter the patient's age: ");
    while (scanf("%d", &new_patient.age) != 1 || new_patient.age <= 0) {
        printf("Invalid age. Please enter a positive number: ");
        while (getchar() != '\n'); // Clear input buffer
    }

    // Gender validation loop
    do {
        printf("Enter the patient's gender (Male/Female): ");
        scanf("%9s", new_patient.gender);  // Limit input length
        if (!is_valid_gender(new_patient.gender)) {
            printf("Invalid gender. Please enter either 'Male' or 'Female'.\n");
        }
    } while (!is_valid_gender(new_patient.gender));

    Node* new_node = (Node*)malloc(sizeof(Node));
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
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
    printf("Successfully added patient\n\n");
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
    if (!f_open) {
        perror("Error opening patient file");
        return;
    }

    Patient human;
    while (fscanf(f_open, "%49s %d %9s", human.name, &human.age, human.gender) == 3) {
        // Validate gender
        if (!is_valid_gender(human.gender)) {
            printf("Warning: Invalid gender '%s' for patient %s - using 'Unknown'\n", 
                  human.gender, human.name);
            strcpy(human.gender, "Unknown");
        }

        Node* new_node = (Node*)malloc(sizeof(Node));
        if (!new_node) {
            printf("Memory allocation failed\n");
            break;
        }

        human.id = generate_patient_id();
        new_node->data = human;
        new_node->next = NULL;

        if (head == NULL) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != NULL) {
                current = current->next;
            }
            current->next = new_node;
        }
    }
    printf("Successfully loaded data from patient file!\n");
    fclose(f_open);
}  