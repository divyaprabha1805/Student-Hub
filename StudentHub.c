#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>

// To keep track of the number of students
int i = 0;

// A structure to store the student details
struct studentInfo
{
   char firstName[20];
   char lastName[20];
   int rollNumber;
   float CGPA;
   int courseId[10];
} st[500];

// File to store student data
const char *filename = "student_data.txt";

// Function to save student data to file
void saveToFile()
{
   FILE *fp = fopen(filename, "w");
   if (fp == NULL)
   {
      printf("Error saving data to file!\n");
      return;
   }
   fwrite(&i, sizeof(int), 1, fp); // Save the count of students
   fwrite(st, sizeof(struct studentInfo), i, fp); // Save student details
   fclose(fp);
   printf("Data saved successfully!\n");
}

// Function to load student data from file
void loadFromFile()
{
   FILE *fp = fopen(filename, "r");
   if (fp == NULL)
   {
      printf("No existing data found. Starting fresh!\n");
      return;
   }
   fread(&i, sizeof(int), 1, fp); // Load the count of students
   fread(st, sizeof(struct studentInfo), i, fp); // Load student details
   fclose(fp);
   printf("Data loaded successfully!\n");
}

// Function to add student details
void addStudent()
{
   printf("Add the Student's Details\n\n");
   printf("Enter the first name of the student\n");
   scanf("%s", st[i].firstName);
   printf("Enter the last name of the student\n");
   scanf("%s", st[i].lastName);
   printf("Enter the roll number of the student\n");
   scanf("%d", &st[i].rollNumber);
   printf("Enter the CGPA of the student\n");
   scanf("%f", &st[i].CGPA);
   printf("Enter the course ID of each course of the student\n");
   for (int j = 0; j < 5; j++)
   {
      scanf("%d", &st[i].courseId[j]);
   }
   i++;
   saveToFile();
}

// Function to find the students using roll number
void findByRollNumber()
{
   int temp;
   printf("Enter the roll number of the student\n");
   scanf("%d", &temp);
   for (int j = 0; j < i; j++)
   {
      if (temp == st[j].rollNumber)
      {
         printf("The student's details are\n");
         printf("The first name is %s\n", st[j].firstName);
         printf("The last name is %s\n", st[j].lastName);
         printf("The CGPA is %f\n", st[j].CGPA);
         printf("The enrolled course IDs are: ");
         for (int k = 0; k < 5; k++)
         {
            printf("%d ", st[j].courseId[k]);
         }
         printf("\n");
         return;
      }
   }
   printf("Student not found\n");
}

// Function to find students enrolled in a specific course
void findRegisteredStudent()
{
   int temp;
   printf("Enter the course ID\n");
   scanf("%d", &temp);
   int c = 0;

   for (int j = 0; j < i; j++)
   {
      for (int d = 0; d < 5; d++)
      {
         if (temp == st[j].courseId[d])
         {
            printf("The student's details are\n");
            printf("The first name is %s\n", st[j].firstName);
            printf("The last name is %s\n", st[j].lastName);
            printf("The CGPA is %f\n", st[j].CGPA);
            printf("The enrolled course IDs are: ");
            for (int k = 0; k < 5; k++)
            {
               printf("%d ", st[j].courseId[k]);
            }
            printf("\n");
            c++;
            break;
         }
      }
   }
   if (c == 0)
   {
      printf("No student found for course ID %d\n", temp);
   }
}

// Function to print the total number of students
void totalCount()
{
   printf("The total number of students currently in the system is %d\n", i);
}

// Function to delete a Student
void deleteStudent()
{
   int temp;
   printf("Enter the roll number of the student\n");
   scanf("%d", &temp);
   for (int j = 0; j < i; j++)
   {
      if (temp == st[j].rollNumber)
      {
         for (int k = j; k < i - 1; k++)
         {
            st[k] = st[k + 1];
         }
         i--;
         saveToFile();
         printf("The entered student's record deleted successfully\n");
         return;
      }
   }
   printf("Student not found\n");
}

// Function to update a student's data
void updateStudent()
{
   int temp;
   printf("Enter the roll number of the student\n");
   scanf("%d", &temp);
   for (int j = 0; j < i; j++)
   {
      if (temp == st[j].rollNumber)
      {
         printf("1. First Name\n"
                "2. Last Name\n"
                "3. Roll Number\n"
                "4. CGPA\n"
                "5. Courses\n");
         int c;
         scanf("%d", &c);
         switch (c)
         {
         case 1:
            printf("Enter the updated first name : ");
            scanf("%s", st[j].firstName);
            break;
         case 2:
            printf("Enter the updated last name : ");
            scanf("%s", st[j].lastName);
            break;
         case 3:
            printf("Enter the updated roll number : ");
            scanf("%d", &st[j].rollNumber);
            break;
         case 4:
            printf("Enter the updated CGPA : ");
            scanf("%f", &st[j].CGPA);
            break;
         case 5:
            printf("Enter the updated list of courses: ");
            for (int k = 0; k < 5; k++)
            {
               scanf("%d", &st[j].courseId[k]);
            }
            break;
         }
         saveToFile();
         printf("Records updated successfully\n");
         return;
      }
   }
   printf("Student not found\n");
}

int main()
{
   loadFromFile(); // Load existing data
   int taskToPerform;
   while (1)
   {
      printf("\nEnter the task that you want to perform\n");
      printf("1. Add a new Student Detail\n");
      printf("2. Find the details of a Student using Roll Number\n");
      printf("3. Find the details of Students enrolled in a specific course\n");
      printf("4. Find Total number of Students\n");
      printf("5. Delete the details of a Student\n");
      printf("6. Update the details of a Student\n");
      printf("7. Exit\n");
      scanf("%d", &taskToPerform);

      switch (taskToPerform)
      {
      case 1:
         addStudent();
         break;
      case 2:
         findByRollNumber();
         break;
      case 3:
         findRegisteredStudent();
         break;
      case 4:
         totalCount();
         break;
      case 5:
         deleteStudent();
         break;
      case 6:
         updateStudent();
         break;
      case 7:
         exit(0);
         break;
      default:
         printf("Invalid choice! Try again.\n");
      }
   }

   return 0;
}
