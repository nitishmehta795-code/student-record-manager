/* student.c - Student Record Manager (v1.0.0) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FILE_NAME "students.txt"

typedef struct {
    int roll;
    char name[50];
    float marks;
} Student;

Student students[MAX_STUDENTS];
int count = 0;

/* ---------- input helpers ---------- */
void readString(char *buf, int size) {
    fgets(buf, size, stdin);
    buf[strcspn(buf, "\n")] = '\0';   /* remove trailing newline */
}

int readInt(void) {
    char buf[50];
    readString(buf, sizeof(buf));
    return atoi(buf);
}

float readFloat(void) {
    char buf[50];
    readString(buf, sizeof(buf));
    return (float)atof(buf);
}

/* ---------- file handling ---------- */
void saveToFile(void) {
    FILE *fp = fopen(FILE_NAME, "w");
    if (fp == NULL) {
        printf("Error: could not save to file.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%d\n%s\n%.2f\n",
                students[i].roll, students[i].name, students[i].marks);
    }
    fclose(fp);
}

void loadFromFile(void) {
    FILE *fp = fopen(FILE_NAME, "r");
    if (fp == NULL) return;            /* first run: no file yet */

    char line[100];
    while (count < MAX_STUDENTS && fgets(line, sizeof(line), fp) != NULL) {
        Student s;
        s.roll = atoi(line);

        if (fgets(s.name, sizeof(s.name), fp) == NULL) break;
        s.name[strcspn(s.name, "\n")] = '\0';

        if (fgets(line, sizeof(line), fp) == NULL) break;
        s.marks = (float)atof(line);

        students[count++] = s;
    }
    fclose(fp);
}

/* ---------- helpers ---------- */
int findIndex(int roll) {
    for (int i = 0; i < count; i++) {
        if (students[i].roll == roll)
            return i;
    }
    return -1;
}

void printStudent(Student s) {
    printf("%d | %s | %.2f\n", s.roll, s.name, s.marks);
}

/* ---------- features ---------- */
void addStudent(void) {
    if (count >= MAX_STUDENTS) {
        printf("Record list is full!\n");
        return;
    }

    Student s;
    printf("Roll number: ");
    s.roll = readInt();

    if (findIndex(s.roll) != -1) {
        printf("A student with roll %d already exists.\n", s.roll);
        return;
    }

    printf("Name: ");
    readString(s.name, sizeof(s.name));
    printf("Marks: ");
    s.marks = readFloat();

    students[count++] = s;
    saveToFile();
    printf("Student added.\n");
}

void searchStudent(void) {
    printf("Enter roll number: ");
    int roll = readInt();

    int i = findIndex(roll);
    if (i == -1)
        printf("No student found with roll %d.\n", roll);
    else
        printStudent(students[i]);
}

void updateStudent(void) {
    printf("Enter roll number to update: ");
    int roll = readInt();

    int i = findIndex(roll);
    if (i == -1) {
        printf("No student found with roll %d.\n", roll);
        return;
    }

    char newName[50];
    printf("New name (press Enter to keep \"%s\"): ", students[i].name);
    readString(newName, sizeof(newName));
    if (strlen(newName) > 0)
        strcpy(students[i].name, newName);

    printf("New marks: ");
    students[i].marks = readFloat();

    saveToFile();
    printf("Student updated.\n");
}

void deleteStudent(void) {
    printf("Enter roll number to delete: ");
    int roll = readInt();

    int i = findIndex(roll);
    if (i == -1) {
        printf("No student found with roll %d.\n", roll);
        return;
    }

    /* shift everyone after i one position left */
    for (int j = i; j < count - 1; j++)
        students[j] = students[j + 1];
    count--;

    saveToFile();
    printf("Student deleted.\n");
}

void showAll(void) {
    if (count == 0) {
        printf("No records to show.\n");
        return;
    }
    printf("Roll | Name | Marks\n");
    for (int i = 0; i < count; i++)
        printStudent(students[i]);
}

/* ---------- main ---------- */
int main(void) {
    int choice;

    loadFromFile();

    do {
        printf("\n===== Student Record Manager =====\n");
        printf("1. Add student\n");
        printf("2. Search student\n");
        printf("3. Update student\n");
        printf("4. Delete student\n");
        printf("5. Show all students\n");
        printf("0. Exit\n");
        printf("Choose: ");
        choice = readInt();

        switch (choice) {
            case 1: addStudent();    break;
            case 2: searchStudent(); break;
            case 3: updateStudent(); break;
            case 4: deleteStudent(); break;
            case 5: showAll();       break;
            case 0: printf("Goodbye!\n"); break;
            default: printf("Invalid choice, try again.\n");
        }
    } while (choice != 0);

    return 0;
}