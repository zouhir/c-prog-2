/**
 * @file: main.c
 * @subject: 48430 Embedded C - Assignment 2
 * @name: Zouhir Chahoud
 * @student_id: 11763745
 * @date: 08-09-2017
 *
 * @achieved: Users are able to add a student, delete, print, read & write to file, validation rules applied
 * and users prompt to re-enter a value if it's invalid, users are also able to
 * use space characters in names.
 *
 *
 * @not_achieved: No validation for user use alphabet character for integer input like a day.
 *
 * @note: Please look at the code style & conventions before writing code.
 *
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief: CONSTANTS defineitions for business rules and program logic
 */
#define MAX_NAME_LENGTH 10 /**< Student names can't be over 10 character lengtg */
#define MAX_DAY_VALUE 31 /**< User input over 31 for day of the month value is invalud */
#define MAX_MONTH_VALUE 12 /**< User input over 12 for month of the year value is invaliud */
#define MIN_YEAR_VALUE 1900 /**< User input below 1900 for students date of birth is invalid */
#define MAX_YEAR_VALUE 2017 /**< User input over 2017 for date of birth is invalid */
#define CLASSROOM_SIZE 100 /**< Maximum number of students we support */


/**
 * @brief date struct to represent date as
 * dd integer for day
 * mm integer for month
 * yyyy integer for year
 */
struct date {
    int day; /**< day as dd integer between 0 and MAX_DAY_VALUE */
    int month; /**< month as mm integer between 0 and MAX_MONTH_VALUE */
    int year /**< year as a yyyy integer between MIN_YEAR_VALUE and CLASSROOM_SIZE */;
};
typedef struct date date_t;

/**
 * @brief student struct represents a student in our system with propeties:
 * name: student as a string full name, alphabetical with spaces allowed.
 * birthday: as a date struct.
 * gpa: is a decimal number
 */
struct student {
    char name[MAX_NAME_LENGTH + 1]; /**< max length is 10 and allowing 1 extra character for non-null end of buffer */
    date_t birthday; /**< current format as dd-mm-yyyy please */
    double gpa; /**< current gpa max decimal places is 4 */
};
typedef struct student student_t;


/**
 * @name printMenu
 * @brief a function to print out the main menu for user selection
 * @return void
 */
void printMenu(void);

/**
 * @name printTable
 * @param students: array of current students
 * @param count: current class count
 * @return void
 */
void printTable(student_t students[], int count);

/**
 * @name writeToFile
 * @brief writes the students array to a text file
 * @param students: array of current students
 * @param count: current class count
 * @return void
 */
void writeToFile(student_t students[], int count);

/**
 * @name readFromFile
 * @brief writes the students array to a text file
 * @param students: array of current students
 * @return integer as a count of how many students we've read
 */
int readFromFile(student_t students[]);

/**
 * @name addStudent
 * @brief creates a new student, appends it to the students array and increments the counter
 * @param students
 * @param count
 * @return void
 */
void addStudent(student_t students[], int count);

/**
 * @name deleteStudent
 * @brief delets last student, returns new count
 * @param students
 * @param count
 * @return void
 */
int deleteStudent(student_t students[], int count);

/**
 * @brief
 */
int main() {

    int selection = -1; /**< defaulting menu selection to -1*/
    int count = 0;  /**< initial count for how many students added */
    student_t studentlist[CLASSROOM_SIZE]; /**< students array of size CLASSROOM_SIZE*/

    while (selection != 6) { /* exiting on selection 6 */
        printMenu(); /* start by printing out the selection menu */
        scanf("%d", &selection);
        switch(selection){
            case 1:
                addStudent(studentlist, count);
                count++;
                break;
            case 2:
                count = deleteStudent(studentlist, count);
                break;
            case 3:
                printTable(studentlist, count);
                break;
            case 4:
                writeToFile(studentlist, count);
                break;
            case 5:
                count = readFromFile(studentlist);
                break;
            case 6:
                exit(0);
            default:
                printf("\nInvalid menu selection, try again>");
        }
    }
    return 0;
}


/**
 * @name printMenu
 * @brief implemenation for print menu defined above, check definition for more details.
 */
void printMenu(void) {
    printf("\n\n"
           "1. add student\n"
           "2. delete last student\n"
           "3. display student list\n"
           "4. save the student list to the database\n"
           "5. read the student list from the database\n"
           "6. exit the program\n"
           "Enter your choice> ");
}

/**
 * @name printTable
 * @brief implemenation for print table defined above, check definition for more details.
 */
void printTable(student_t students[], int count)
{
    if(count == 0) {
        printf("No students to print");
        return;
    }
    printf("%-10s %-10s %-6s\n", "Name", "Birthday", "GPA");
    printf("%-10s %-10s %-6s\n", "----------", "----------", "------");
    for (int i = 0; i < count; i++) {
        printf("%-10s %d-%d-%-6d %.4f\n", students[i].name, students[i].birthday.day, students[i].birthday.day, students[i].birthday.year, students[i].gpa);
    }
}

/**
 * @name addStudent
 * @brief implemenation for print table defined above, check definition for more details.
 *
 * @todo: extract the while loops and validation login into a function
 * to lower the amount of repeteation.
 */
void addStudent(student_t students[], int index) {

    /**
     * Flags to set validation for user input.
     * -1 = invalid
     * 1 = valid
     */
    int validName = -1;
    int validGpa = -1;
    int validDay = -1;
    int validMonth = -1;
    int validYear = -1;

    date_t dob; /**< date object to handle date of birth details */

    /**
     * Prompts the user to enter their name
     * Loops until validation rules is satesfied
     *
     * valid if name is less than MAX_NAME_LENGTH character length
     */
    printf("Enter your name> ");
    while( validName < 0 ) {
        scanf(" %[^\n]s", students[index].name);
        if( strlen(students[index].name) > MAX_NAME_LENGTH ) {
            printf("\nName is invalid, try again> ");
        } else {
            validName = 1;
        }
    }

    /**
     * Prompts the user to enter their birthday day
     * Loops until validation rules is satesfied
     *
     * valid if day is less than MAX_DAY_VALUE
     */
    printf("Enter birthday: day> ");
    while( validDay < 0 ) {
        scanf(" %d", &dob.day);
        if( dob.day > 0 && dob.day <= MAX_DAY_VALUE) {
            validDay = 1;
        } else {
            printf("\nDate day is not valid, try again> ");
        }
    }

    /**
     * Prompts the user to enter their birthday month
     * Loops until validation rules is satesfied
     *
     * valid if day is less than MAX_MONTH_VALUE but greater than 0
     */
    printf("Enter birthday: month> ");
    while( validMonth  < 0 ) {
        scanf(" %d", &dob.month);
        if(dob.month > 0 && dob.month <= MAX_MONTH_VALUE) {
            validMonth = 1;
        } else {
            printf("\nDate month is not valid, try again> ");
        }
    }

    /**
     * Prompts the user to enter their birthday year
     * Loops until validation rules is satesfied
     *
     * valid if day is less than MAX_YEAR_VALUE but greater than MIN_YEAR_VALUE
     */
    printf("Enter birthday: year> ");
    while( validYear  < 0 ) {
        scanf(" %d", &dob.year);
        if( dob.year < MAX_YEAR_VALUE && dob.year > MIN_YEAR_VALUE ) {
            validYear = 1;
        } else {
            printf("\nDate year is not valid, try again > ");
        }
    }

    students[index].birthday = dob; /**< Assigned the valid date object to the student struct object */

    /**
     * Prompts the user to enter their GPA
     * Loops until validation rules is satesfied
     *
     * valid if day is greater than 0
     */
    printf("Enter GPA> ");
    while( validGpa  < 0 ) {
        scanf(" %lf", &students[index].gpa);
        if( students[index].gpa > 0) {
            validGpa = 1;
        } else {
            printf("\nGPA is not valid, try again> ");
        }
    }

}

/**
 * @name deleteStudent
 * @brief implemenation for delete defined above, check definition for more details.
 */
int deleteStudent(student_t students[], int count) {
    if(count == 0) { /* if class is empty, do nothing */
        printf("\nClass room is already empty\n");
        return 0;
    }
    printf("\nWe have deleted %s from the class \n", students[count - 1].name);
    return count - 1; /* decerement the counter value */
}

/**
 * @name writeToFile
 * @brief implemenation for writeToFile defined above, check definition for more details.
 */
void writeToFile(student_t students[], int count) {
    FILE *outfile; /**< the destination file object */

    /* trying to open students.txt file with `w` write permission */
    outfile = fopen ("students.txt","w");
    if (outfile == NULL)
    {
        fprintf(stderr, "\nError opening students.txt\n"); /* Error reading the file, exit. */
        exit (1);
    }

    for(int i = 0; i < count; ++i) {
        fwrite (&students[i], sizeof(struct student), 1, outfile); /* write all students to the file. */
    }
    fclose(outfile); /* never forget to close or your data won't be written. */
}

int readFromFile(student_t students[]) {
    FILE *input;
    int count = 0;

    /* trying to open students.txt file with `r` only permission */
    input = fopen ("students.txt","r");
    if (input == NULL)
    {
        fprintf(stderr, "\nError opening students.txt\n"); /* Error reading the file, exit. */
        exit (1);
    }
    /**
     * as long as students of struct size are found, read them and insert them in array students
     * exit the loop once the class is full
     */
    while(fread(&students[count],sizeof(struct student),1, input) > 0 && count < CLASSROOM_SIZE) {
        count ++;
    }
    fclose(input); /* close the file. */
    return count; /* return the count. */
}