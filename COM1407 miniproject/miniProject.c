#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct EmployeeDetails {
    char fname[50];
    char lname[50];
    char nic[20];
    int gender;
    int year;
    int month;
    int day;
    int no;
    char line1[100];
    char line2[100];
    char bank[50];
    int accountNo;
};

int main() {
    int choice;
    FILE *file;
    file = fopen("employee.txt", "a+");

    if (!file) {
        printf("Error opening file.\n");
        return 1;
    }

	start:
    printf("\n\n\t\t\tWelcome to Dinethla Motors\n");
    printf("------------------------------------------------------------------\n");
    printf("\t1 for Add Employee\t\t2 for View Employee\n");
    printf("\t3 for Search Employee\t\t4 for Update Employee\n");
    printf("\t5 for Delete Employee\t\t6 for Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > 6 ||  (choice >= 'a'  &&  choice <= 'z') || (choice >= 'A'  &&  choice <= 'Z')) {
        printf("Invalid choice. Try again.\n");
        goto start;
    }

    if (choice == 1) { 
        struct EmployeeDetails employee;

        printf("Employee First Name and Last Name: ");
        scanf("%s %s", employee.fname, employee.lname);
        printf("NIC No: ");
        scanf("%s", employee.nic);
        printf("1 - Male / 2 - Female: ");
        scanf("%d", &employee.gender);
        printf("Birthday (yyyy mm dd): ");
        scanf("%d %d %d", &employee.year, &employee.month, &employee.day);
        printf("Address Number: ");
        scanf("%d", &employee.no);
        printf("Address Line 1: ");
        scanf(" %s", employee.line1);
        printf("Address Line 2: ");
        scanf(" %s", employee.line2);
        printf("Bank Name: ");
        scanf(" %s", employee.bank);
        printf("Bank Account Number: ");
        scanf("%d", &employee.accountNo);

        fprintf(file, "%s %s %s %d %d %d %d %d %s %s %s %d\n",
                employee.fname, employee.lname, employee.nic, employee.gender,
                employee.year, employee.month, employee.day, employee.no,
                employee.line1, employee.line2, employee.bank, employee.accountNo);

        printf("Employee added successfully.\n");
        goto start;

    } else if (choice == 2) { 
        struct EmployeeDetails employee;
        rewind(file);

        printf("\nEmployee Records:\n");
        printf("---------------------------------------------------------------------------\n");
        while (fscanf(file, "%s %s %s %d %d %d %d %d %s %s %s %d",
                      employee.fname, employee.lname, employee.nic, &employee.gender,
                      &employee.year, &employee.month, &employee.day, &employee.no,
                      employee.line1, employee.line2, employee.bank, &employee.accountNo) != EOF) {
            printf("Name: %s %s, NIC: %s, Gender: %s, DOB: %04d-%02d-%02d\n",
                   employee.fname, employee.lname, employee.nic,
                   (employee.gender == 1 ? "Male" : "Female"),
                   employee.year, employee.month, employee.day);
            printf("Address: %d, %s, %s\n", employee.no, employee.line1, employee.line2);
            printf("Bank: %s, Account No: %d\n", employee.bank, employee.accountNo);
            printf("---------------------------------------------------------------------------\n");
        }
        goto start;

    } else if (choice == 3) { 
        struct EmployeeDetails employee;
        char searchNIC[20];
        int found = 0;

        printf("Enter NIC to search: ");
        scanf("%s", searchNIC);

        rewind(file);
        while (fscanf(file, "%s %s %s %d %d %d %d %d %s %s %s %d",
                      employee.fname, employee.lname, employee.nic, &employee.gender,
                      &employee.year, &employee.month, &employee.day, &employee.no,
                      employee.line1, employee.line2, employee.bank, &employee.accountNo) != EOF) {
            if (strcmp(employee.nic, searchNIC) == 0) {
                printf("Employee Found\n");
                printf("Name: %s %s, NIC: %s, Gender: %s, DOB: %04d-%02d-%02d\n",
                       employee.fname, employee.lname, employee.nic,
                       (employee.gender == 1 ? "Male" : "Female"),
                       employee.year, employee.month, employee.day);
                printf("Address: %d, %s, %s\n", employee.no, employee.line1, employee.line2);
                printf("Bank: %s, Account No: %d\n", employee.bank, employee.accountNo);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Employee with NIC %s not found.\n", searchNIC);
        }
        goto start;

    } else if (choice == 4) { 
        struct EmployeeDetails employee;
        char searchNIC[20];
        int found = 0;

        FILE *tempFile = fopen("temp.txt", "w");

        if (!tempFile) {
            printf("Error creating temporary file.\n");
            goto start;
        }

        printf("Enter NIC to update: ");
        scanf("%s", searchNIC);

        rewind(file);
        while (fscanf(file, "%s %s %s %d %d %d %d %d %s %s %s %d",
                      employee.fname, employee.lname, employee.nic, &employee.gender,
                      &employee.year, &employee.month, &employee.day, &employee.no,
                      employee.line1, employee.line2, employee.bank, &employee.accountNo) != EOF) {
            if (strcmp(employee.nic, searchNIC) == 0) {
                printf("Employee Found. Enter updated details.\n");
                printf("Employee First Name and Last Name: ");
                scanf("%s %s", employee.fname, employee.lname);
                printf("1 - Male / 2 - Female: ");
                scanf("%d", &employee.gender);
                printf("Birthday (yyyy mm dd): ");
                scanf("%d %d %d", &employee.year, &employee.month, &employee.day);
                printf("Address Number: ");
                scanf("%d", &employee.no);
                printf("Address Line 1: ");
                scanf(" %s", employee.line1);
                printf("Address Line 2: ");
                scanf(" %s", employee.line2);
                printf("Bank Name: ");
                scanf(" %s", employee.bank);
                printf("Bank Account Number: ");
                scanf("%d", &employee.accountNo);

                found = 1;
            }

            fprintf(tempFile, "%s %s %s %d %d %d %d %d %s %s %s %d\n",
                    employee.fname, employee.lname, employee.nic, employee.gender,
                    employee.year, employee.month, employee.day, employee.no,
                    employee.line1, employee.line2, employee.bank, employee.accountNo);
        }

        fclose(file);
        fclose(tempFile);

        remove("employee.txt");
        rename("temp.txt", "employee.txt");

        file = fopen("employee.txt", "a+");

        if (found) {
            printf("Employee updated successfully.\n");
        } else {
            printf("Employee with NIC %s not found.\n", searchNIC);
        }
        goto start;

    } else if (choice == 5) { 
        struct EmployeeDetails employee;
        char searchNIC[20];
        int found = 0;

        FILE *tempFile = fopen("temp.txt", "w");

        if (!tempFile) {
            printf("Error creating temporary file.\n");
            goto start;
        }

        printf("Enter NIC to delete: ");
        scanf("%s", searchNIC);

        rewind(file);
        while (fscanf(file, "%s %s %s %d %d %d %d %d %s %s %s %d",
                      employee.fname, employee.lname, employee.nic, &employee.gender,
                      &employee.year, &employee.month, &employee.day, &employee.no,
                      employee.line1, employee.line2, employee.bank, &employee.accountNo) != EOF) {
            if (strcmp(employee.nic, searchNIC) == 0) {
                found = 1;
            } else {
                fprintf(tempFile, "%s %s %s %d %d %d %d %d %s %s %s %d\n",
                        employee.fname, employee.lname, employee.nic, employee.gender,
                        employee.year, employee.month, employee.day, employee.no,
                        employee.line1, employee.line2, employee.bank, employee.accountNo);
            }
        }

        fclose(file);
        fclose(tempFile);

        remove("employee.txt");
        rename("temp.txt", "employee.txt");

        file = fopen("employee.txt", "a+");

        if (found) {
            printf("Employee deleted successfully.\n");
        } else {
            printf("Employee with NIC %s not found.\n", searchNIC);
        }
        goto start;

    } else if (choice == 6) { 
        fclose(file);
        printf("Thank you for using Dinethla Motors Employee Management System!\n");
		goto end;
    }
	end:
    return 0;
}

