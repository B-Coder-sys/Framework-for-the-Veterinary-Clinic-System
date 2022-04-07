/*
***************************
                        Assignment 1 - Milestone 2
Full Name  :Kranti KC
Student ID#:146277215
Email      :Kk-c3
Section    :NDD

Authenticity Declaration:
I declare this submission is the result of my own work and has not been
shared with any other student or 3rd party content provider. This submitted
piece of work is entirely of my own creation.
***************************
*/

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
// include the user library "core" so we can use those functions
#include "core.h"
// include the user library "clinic" where the function prototypes are declared
#include "clinic.h"


//////////////////////////////////////
// DISPLAY FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Display's the patient table header (table format)
void displayPatientTableHeader(void)
{
    printf("Pat.# Name            Phone#\n"
        "----- --------------- --------------------\n");
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Displays a single patient record in FMT_FORM | FMT_TABLE format
void displayPatientData(const struct Patient* patient, int fmt)
{
    if (fmt == FMT_FORM)
    {
        printf("Name  : %s\n"
            "Number: %05d\n"
            "Phone : ", patient->name, patient->patientNumber);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
    else
    {
        printf("%05d %-15s ", patient->patientNumber,
            patient->name);
        displayFormattedPhone(patient->phone.number);
        printf(" (%s)\n", patient->phone.description);
    }
}


//////////////////////////////////////
// MENU & ITEM SELECTION FUNCTIONS
//////////////////////////////////////

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// main menu
void menuMain(struct ClinicData* data)
{
    int selection;

    do {
        printf("Veterinary Clinic System\n"
            "=========================\n"
            "1) PATIENT     Management\n"
            "2) APPOINTMENT Management\n"
            "-------------------------\n"
            "0) Exit System\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');
        switch (selection)
        {
        case 0:
            printf("Are you sure you want to exit? (y|n): ");
            selection = !(inputCharOption("yn") == 'y');
            putchar('\n');
            if (!selection)
            {
                printf("Exiting system... Goodbye.\n\n");
            }
            break;
        case 1:
            menuPatient(data->patients, data->maxPatient);
            break;
        case 2:
            printf("<<< Feature not yet available >>>\n\n");
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient Management
void menuPatient(struct Patient patient[], int max)
{
    int selection;

    do {
        printf("Patient Management\n"
            "=========================\n"
            "1) VIEW   Patient Data\n"
            "2) SEARCH Patients\n"
            "3) ADD    Patient\n"
            "4) EDIT   Patient\n"
            "5) REMOVE Patient\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 5);
        putchar('\n');
        switch (selection)
        {
        case 1:
            displayAllPatients(patient, max, FMT_TABLE);
            suspend();
            break;
        case 2:
            searchPatientData(patient, max);
            break;
        case 3:
            addPatient(patient, max);
            suspend();
            break;
        case 4:
            editPatient(patient, max);
            break;
        case 5:
            removePatient(patient, max);
            suspend();
            break;
        }
    } while (selection);
}

// !!! DO NOT MODIFY THIS FUNCTION DEFINITION !!!
// Menu: Patient edit
void menuPatientEdit(struct Patient* patient)
{
    int selection;

    do {
        printf("Edit Patient (%05d)\n"
            "=========================\n"
            "1) NAME : %s\n"
            "2) PHONE: ", patient->patientNumber, patient->name);

        displayFormattedPhone(patient->phone.number);

        printf("\n"
            "-------------------------\n"
            "0) Previous menu\n"
            "-------------------------\n"
            "Selection: ");
        selection = inputIntRange(0, 2);
        putchar('\n');

        if (selection == 1)
        {
            printf("Name  : ");
            inputCString(patient->name, 1, NAME_LEN);
            putchar('\n');
            printf("Patient record updated!\n\n");
        }
        else if (selection == 2)
        {
            inputPhoneData(&patient->phone);
            printf("Patient record updated!\n\n");
        }

    } while (selection);
}

void displayAllPatients(const struct Patient patient[], int max, int fmt)
{
    int index = 0, found = 1, printed = 0;
    while (index < max) {// checking if value of index is smaller than max value
        if (patient[index].patientNumber != 0) {
            if (!printed)
                displayPatientTableHeader();
            displayPatientData(&patient[index], fmt);
            found = 0;
            printed = 1;
        }
        index++;
    }
    if (found) {
        printf("*** No records found ***\n\n");
    }
    putchar('\n');
}

void searchPatientData(const struct Patient patient[], int max)
{
    int choice;
    //display menu
    do {
        printf("Search Options\n"
            "==========================\n"
            "1) By patient number\n"
            "2) By phone number\n"
            "..........................\n"
            "0) Previous menu\n"
            "..........................\n"
            "Selection: ");

        choice = inputIntRange(0, 2);
        putchar('\n');

        if (choice == 1) {
            searchPatientByPatientNumber(patient, max);
            suspend();
        }
        else if (choice == 2) {
            searchPatientByPhoneNumber(patient, max);
            suspend();
        }
    } while (choice);

}

void addPatient(struct Patient patient[], int max)
{
    int found = 0, i = -1;
    while (!found && ++i < max) {
        if (patient[i].patientNumber == 0) {
            found = 1;
        }
    }

    if (found) {
        int P_Number = nextPatientNumber(patient, max);
        patient[i].patientNumber = P_Number;
        inputPatient(&patient[i]);
        printf("*** New patient record added ***\n\n");
    }
    else {
        printf("ERROR: Patient listing is FULL!\n\n");
    }
}

void editPatient(struct Patient patient[], int max)
{
    printf("Enter the patient number: ");
    int patNum = inputIntPositive();
    putchar('\n');
    int i = findPatientIndexByPatientNum(patNum, patient, max);
    if (i == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        menuPatientEdit(&patient[i]);
    }
}

void removePatient(struct Patient patient[], int max)
{
    printf("Enter the patient number: ");
    int patNum = inputIntPositive();
    putchar('\n');
    int i = findPatientIndexByPatientNum(patNum, patient, max);
    if (i == -1) {
        printf("ERROR: Patient record not found!\n\n");
    }
    else {
        displayPatientData(&patient[i], 1);
        putchar('\n');
        printf("Are you sure you want to remove this patient record? (y/n): ");
        int choose = (inputCharOption("yn") == 'y');


        if (choose) {
            patient[i].patientNumber = 0;
            printf("Patient record has been removed!\n\n");
        }
        else {
            printf("Operation aborted.\n\n");
        }
    }
}

void searchPatientByPatientNumber(const struct Patient patient[], int max)
{
    printf("Search by patient number: ");
    int num = inputIntPositive();
    putchar('\n');
    int i = findPatientIndexByPatientNum(num, patient, max);

    if (i == -1) {
        printf("*** No records found ***\n\n");
    }
    else {
        displayPatientData(&patient[i], 1);
        putchar('\n');
    }
}

void searchPatientByPhoneNumber(const struct Patient patient[], int max)
{
    printf("Search by phone number: ");
    char phone[PHONE_LEN + 1];
    inputCString(phone, PHONE_LEN, PHONE_LEN);
    putchar('\n');
    int found = 0;
    displayPatientTableHeader();
    int i = -1;
    while (++i < max) {

        if ((strcmp(patient[i].phone.number, phone) == 0)) {
            displayPatientData(&patient[i], 2);
            found = 1;
        }
    }
    if (!found) {
        printf("\n*** No records found ***\n");
    }
    putchar('\n');
}

int nextPatientNumber(const struct Patient patient[], int max)
{
    int latest = 0;
    int i = -1;
    while (++i < max) {
        if (latest < patient[i].patientNumber) {
            latest = patient[i].patientNumber;
        }
    }
    return latest + 1;

}

int findPatientIndexByPatientNum(int patientNumber, const struct Patient patient[], int max)
{
    int index = -1;
    int i = 0;
    while (i < max) {
        if (patient[i].patientNumber == patientNumber) {
            index = i;
        }
        i++;
    }
    return index;
}

void inputPatient(struct Patient* patient)
{
    printf("Patient Data Input\n"
        "------------------\n"
        "Number: %05d\n", patient->patientNumber);
    printf("Name  : ");
    inputCString(patient->name, 1, NAME_LEN);
    putchar('\n');
    inputPhoneData(&patient->phone);
}

void inputPhoneData(struct Phone* phone)
{
    printf("Phone Information\n"
        "-----------------\n"
        "How will the patient like to be contacted?\n"
        "1. Cell\n"
        "2. Home\n"
        "3. Work\n"
        "4. TBD\n"
        "Selection: ");

    int selection = inputIntRange(1, 4);
    putchar('\n');
    if (selection == 1) {
        strcpy(phone->description, "CELL");
    }
    else if (selection == 2) {
        strcpy(phone->description, "HOME");
    }
    else if (selection == 3) {
        strcpy(phone->description, "WORK");
    }
    else if (selection == 4) {
        strcpy(phone->description, "TBD");
        strcpy(phone->number, "");
    }

    if (selection != 4) {
        printf("Contact: %s\n", phone->description);
        printf("Number : ");
        inputCString(phone->number, 10, PHONE_LEN);
        putchar('\n');
    }
}

