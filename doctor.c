#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "doctor.h"
struct Node_doctor *root = NULL;

void init_doctor(Vector* v) {
    v->size = 0;
    v->capacity = 2;
    v->data = malloc(v->capacity * sizeof(Doctor));
}


struct Node_doctor* getNewNode(Doctor doctor) {
    struct Node_doctor *newNode = malloc(sizeof(struct Node_doctor));
    newNode->doctor = doctor;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;

}
struct Node_doctor* insert(struct Node_doctor* root, Doctor doctor) {
    if (root == NULL)
        return getNewNode(doctor);
    if (root->doctor.id < doctor.id) {
        root->right = insert(root->right, doctor);
    }
    else if (root->doctor.id > doctor.id) {
        root->left = insert(root->left, doctor);
    }

    return root;
}

Doctor search(struct Node_doctor* root, int doctor_id) {
    if (root == NULL) {
        printf("Doctor not found.\n");
        exit(1);
    }

    if (root->doctor.id == doctor_id) 
        return root->doctor;
    
    if (root->doctor.id < doctor_id) 
        return search(root->right, doctor_id);
    else
        return search(root->left, doctor_id);

}
void search_doctor(Vector* v) {
    printf("This is our doctor id list:\n");
    for (int i = 0; i < v->size; i ++) {
        printf("%d ", v->data[i].id);
    }
    printf("\n");
    printf("Enter the id of the doctor that you want to search:\n");
    int doctor_id;
    scanf("%d", &doctor_id);
    Doctor Answer = search(root, doctor_id);
    printf("Name: %s, ID: %d\n", Answer.name, Answer.id);

}

void inorder_doctor(struct Node_doctor* root) { 
    if (root == NULL) return;
    inorder_doctor(root->left);
    printf("Name: %s, ID: %d\n", root->doctor.name, root->doctor.id);
    inorder_doctor(root->right);
}

void list_doctor() {
    printf("Doctor List:\n");
    inorder_doctor(root);
    return;
}


void load_doctor_from_file(Vector* v) {
    FILE* f_open = fopen("data/doctors.txt", "r");

    Doctor human;
    while (fscanf(f_open, "%s %d", human.name, &human.id) == 2) {
        if (v->size == v->capacity) {
            v->capacity *= 2;
            v->data = realloc(v->data, v->capacity * sizeof(Doctor));
        }
    
        ((Doctor*)(v->data))[v->size++] = human;

    }

    for (int i = 0; i < v->size; i++) {
        root = insert(root, v->data[i]);
    }
    
    fclose(f_open);

}

void save_doctor_to_file(Vector* v) {
    FILE* f_open = fopen("data/doctors.txt", "w");
    for (int i = 0; i < v->size; i++) {
        fprintf(f_open,"%s %d\n", v->data[i].name, v->data[i].id);
    }
    fclose(f_open);

}


struct Node_doctor* findMin(struct Node_doctor* root) {
    if (root->left == NULL) {
        return root;
    }
    return findMin(root->left);
}


struct Node_doctor* deleteNode(struct Node_doctor* root, int examined_id) {
    if (root == NULL) {
        return NULL;
    }
    if (root->doctor.id > examined_id) root->left = deleteNode(root->left, examined_id);
    if (root->doctor.id < examined_id) root->right = deleteNode(root->right,examined_id);

    if (root->doctor.id == examined_id) {
        
        if (root->right == NULL && root->left == NULL) {
            free(root);
            return NULL;
        }
        else if (root->right == NULL) {
            struct Node_doctor* temp = root->left;
            free(root);
            return temp;
        }
        else if (root->left == NULL) {
            struct Node_doctor* temp = root->right;
            free(root);
            return temp;
        }
        else {
            struct Node_doctor* Lowest_id_doctor = findMin(root->right);
            root->doctor.id = Lowest_id_doctor->doctor.id;
            root->right = deleteNode(root->right, Lowest_id_doctor->doctor.id);
        }   
    }
    return root;
}


void delete_doctor_by_name(Vector* v) {
    printf("Doctor's Name List:\n");
    for (int i = 0 ; i < v->size; i++) {
        printf("%s\n", v->data[i].name);
    }
    int id_result = -1;

    printf("Enter the name of the patient that you want delete:\n");
    char name[50];
    scanf("%s", name);
    int i = 0;
    for (; i < v->size; i++) {
        if (strcmp(v->data[i].name, name) == 0) {
            id_result = v->data[i].id;
            break;
            
        }
    }

    for (int j = i; j < v->size - 1; j++) {
        v->data[j] = v->data[j + 1];
    }
    v->size--;
    if (id_result == -1) {
        printf("Can not find the given doctor name.\n");
    } else {
        root = deleteNode(root, id_result);
    }

}

void add_doctor(Vector* v) {
    Doctor human;
    printf("Enter the doctor name:\n");
    scanf("%s", human.name);
    printf("Enter the doctor id:\n");
    scanf("%d", &human.id);

    if (v->size == v->capacity) {
        v->capacity *= 2;
        v->data = realloc(v->data, v->capacity * sizeof(Doctor));
    }

    v->data[v->size++] = human;
    root = insert(root, human);

}

void free_bst_doctor(struct Node_doctor* root) {
    if (root == NULL) return;
    free_bst_doctor(root->left);
    free_bst_doctor(root->right);
    free(root);
}

void free_doctor(Vector *v) {
    free(v->data);
    free_bst_doctor(root);
    root = NULL;
}


