/* =====================================================
   CodeAlpha - C Programming Internship
   TASK 3 (High): Student Management System
   Menu-driven program to Add, Delete, Update, Search and
   Display student records, using structures and file
   handling for permanent storage.
   ===================================================== */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define FILENAME "students.dat"

typedef struct {
    int id;
    char name[50];
    int age;
    char course[30];
    float marks;
} Student;

/* ---- Add a new student record ---- */
void addStudent() {
    FILE *fp = fopen(FILENAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    Student s;
    printf("\nEnter Student ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name);
    printf("Enter Age: ");
    scanf("%d", &s.age);
    printf("Enter Course: ");
    scanf(" %[^\n]", s.course);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(Student), 1, fp);
    fclose(fp);
    printf("\nStudent record added successfully!\n");
}

/* ---- Display all student records ---- */
void displayStudents() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    Student s;
    int found = 0;
    printf("\n%-6s %-20s %-5s %-15s %-6s\n", "ID", "Name", "Age", "Course", "Marks");
    printf("--------------------------------------------------------\n");

    while (fread(&s, sizeof(Student), 1, fp)) {
        printf("%-6d %-20s %-5d %-15s %-6.2f\n", s.id, s.name, s.age, s.course, s.marks);
        found = 1;
    }

    if (!found) printf("No records found!\n");
    fclose(fp);
}

/* ---- Search for a student by ID ---- */
void searchStudent() {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    int id, found = 0;
    Student s;
    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("\nRecord Found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nCourse: %s\nMarks: %.2f\n",
                   s.id, s.name, s.age, s.course, s.marks);
            found = 1;
            break;
        }
    }

    if (!found) printf("\nStudent with ID %d not found!\n", id);
    fclose(fp);
}

/* ---- Update an existing student record ---- */
void updateStudent() {
    FILE *fp = fopen(FILENAME, "rb+");
    if (fp == NULL) {
        printf("\nNo records found!\n");
        return;
    }

    int id, found = 0;
    Student s;
    printf("\nEnter Student ID to update: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id == id) {
            printf("Enter new Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter new Age: ");
            scanf("%d", &s.age);
            printf("Enter new Course: ");
            scanf(" %[^\n]", s.course);
            printf("Enter new Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(Student), SEEK_CUR);
            fwrite(&s, sizeof(Student), 1, fp);
            found = 1;
            printf("\nRecord updated successfully!\n");
            break;
        }
    }

    if (!found) printf("\nStudent with ID %d not found!\n", id);
    fclose(fp);
}

/* ---- Delete a student record ---- */
void deleteStudent() {
    FILE *fp = fopen(FILENAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");
    if (fp == NULL || temp == NULL) {
        printf("\nError opening file!\n");
        return;
    }

    int id, found = 0;
    Student s;
    printf("\nEnter Student ID to delete: ");
    scanf("%d", &id);

    while (fread(&s, sizeof(Student), 1, fp)) {
        if (s.id != id) {
            fwrite(&s, sizeof(Student), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);
    remove(FILENAME);
    rename("temp.dat", FILENAME);

    if (found)
        printf("\nRecord deleted successfully!\n");
    else
        printf("\nStudent with ID %d not found!\n", id);
}

/* ---- Main menu loop ---- */
int main() {
    int choice;

    do {
        printf("\n===== STUDENT MANAGEMENT SYSTEM =====\n");
        printf("1. Add Student\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("\nExiting program. Goodbye!\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}
