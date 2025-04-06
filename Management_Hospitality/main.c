#include <stdio.h>
#include <stdlib.h>
#include <string.h>	
#include <time.h>
#include "patient.h"
#include "doctor.h"
#include "appointment.h"
#include "utils.h"

Vector v;
AppointmentSystem appt_system;

int main() {
    int choice;
    init_doctor(&v);
    init_appointment_system(&appt_system); // Initialize appointment system
    while (1) {
        printf("\n=== Hospital Management System ===\n");
        printf("\nPatient Management:\n");
        printf("1. Load patients from file\n");
        printf("2. Add a patient\n");
        printf("3. Search a patient\n");
        printf("4. Delete a patient\n");
        printf("5. Display patient information\n");
        printf("6. Save patients to file\n");
        printf("\nDoctor Management:\n");
        printf("7. Load doctors from file\n");
        printf("8. Add doctor\n");
        printf("9. Delete a doctor\n");
        printf("10. List Doctors\n");
        printf("11. Save doctors to file\n");
        
        printf("\nAppointment:\n");
        printf("12. Generate appointment from doctor and patient file\n");
        printf("13. Display original appointments\n");
        printf("14. Display the queue appoinment\n");
        printf("15. Pick the next appointment to treat\n\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                load_patient_from_file();  
                break;

            case 2:
                add_patient();
                break;

            case 3:
                search_patient();
                break;
            case 4:
                delete_patient();
                break;

            case 5:
                display_patient_info(); 
                break;

            case 6:
                save_patient_to_file();   
                break;

            case 7:
                load_doctor_from_file(&v);
                break;

            case 8: 
                add_doctor(&v);   
                break;

            case 9:
                delete_doctor_by_name(&v); 
                break;

            case 10:
                list_doctor(&v);
                break;

            case 11:
                save_doctor_to_file(&v);
                break;

            case 12:  // Book appointment
                generate_appointment_from_file(&appt_system);
                break;
            
            case 13:  // View next appointment
                display_appointment(&appt_system);
                break;
            
            case 14:
                display_queue_appointment(&appt_system);    
                break;
            case 15:  // View daily schedule
                pick_next_appointment(&appt_system);
                break;
            
            case 0:
                // Save data before exiting
                save_doctor_to_file(&v);
                save_patient_to_file();  
                free_appointment_system(&appt_system);
                free_list();
                free_doctor(&v);
                printf("Exiting system...\n");
                return 0;
                
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
}