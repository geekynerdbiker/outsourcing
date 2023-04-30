#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FALSE 0
#define TRUE 1
#define NAME_ORDER 1
#define GPA_ORDER 2

typedef struct {
    char* name;
    char* id;
    double gpa;
    int creditHours;
} Student;

typedef struct StudentNode{
    Student* pStudent;
    struct StudentNode* pNext;
} StudentNode;

typedef struct {
    StudentNode* pIDList;
    StudentNode* pHonorRollList;
    StudentNode* pAcademicProbationList;
    StudentNode* pFreshmanList;
    StudentNode* pSophomoreList;
    StudentNode* pJuniorList;
    StudentNode* pSeniorList;
} Database;

void addNode(StudentNode *list, StudentNode *sn, int order) {
    StudentNode *newNode = (StudentNode *)malloc(sizeof(StudentNode));
    
    newNode->pStudent = (Student *)malloc(sizeof(Student));
    newNode->pStudent->name = (char *)malloc(sizeof(char) * 20);
    newNode->pStudent->id = (char *)malloc(sizeof(char) * 20);
    
    strcpy(newNode->pStudent->name, sn->pStudent->name);
    strcpy(newNode->pStudent->id, sn->pStudent->id);
    newNode->pStudent->gpa = sn->pStudent->gpa;
    newNode->pStudent->creditHours = sn->pStudent->creditHours;
    newNode->pNext = (StudentNode *)malloc(sizeof(StudentNode));
    
    if (!list->pStudent) {
        list->pStudent = newNode->pStudent;
        list->pNext = newNode->pNext;
    } else {
        StudentNode *p = list;
        StudentNode *q = NULL;
        
        if (order == NAME_ORDER) {
            while (p->pNext && strcmp(p->pStudent->name, newNode->pStudent->name) < 0) {
                q = p;
                p = p->pNext;
            }
            
            if (!q) {
                newNode->pNext->pStudent = p->pStudent;
                newNode->pNext->pNext = p->pNext;
                list->pStudent = newNode->pStudent;
                list->pNext = newNode->pNext;
            } else {
                if (p) {
                    newNode->pNext->pStudent = p->pStudent;
                    newNode->pNext->pNext = p->pNext;
                }
                q->pNext->pStudent = newNode->pStudent;
                q->pNext->pNext = newNode->pNext;
            }
        } else if (order == GPA_ORDER) {
            while (p->pNext && p->pStudent->gpa < sn->pStudent->gpa)
                p = p->pNext;
            
            if (!q) {
                newNode->pNext->pStudent = p->pStudent;
                newNode->pNext->pNext = p->pNext;
                list->pStudent = newNode->pStudent;
                list->pNext = newNode->pNext;
            } else {
                if (p) {
                    newNode->pNext->pStudent = p->pStudent;
                    newNode->pNext->pNext = p->pNext;
                }
                q->pNext->pStudent = newNode->pStudent;
                q->pNext->pNext = newNode->pNext;
            }
        }
    }
}

void removeNode(StudentNode *list, char *id) {
    StudentNode *p = list;
    StudentNode *q = NULL;
    
    while (p->pNext && strcmp(p->pStudent->id, id)) {
        q = p;
        p = p->pNext;
    } if (p->pNext) {
        if (!q) {
            list->pStudent = p->pNext->pStudent;
            list->pNext = p->pNext->pNext;
            free(p);
        } else {
            q->pNext = p->pNext;
            free(p);
        }
    }
}

void printStudent(StudentNode *list, int option, char *id) {
    StudentNode *p = list;
    
    int count = 0;
    
    if (option == 8) {
        while (p->pNext) {
            if (!strcmp(p->pStudent->id, id)) {
                printf("%s\n", p->pStudent->name);
                printf("\t%s\n", p->pStudent->id);
                printf("\t%f\n", p->pStudent->gpa);
                printf("\t%d\n", p->pStudent->creditHours);
                
                return;
            }
            p = p->pNext;
        }
    } else {
        while (p->pNext) {
            if (option == 1 && count == 10)
                break;
            
            printf("%s\n", p->pStudent->name);
            printf("\tID - %s\n", p->pStudent->id);
            printf("\tGPA - %f\n", p->pStudent->gpa);
            printf("\tCredit Hours - %d\n", p->pStudent->creditHours);
            p = p->pNext;
            count++;
        }
    }
    if (count == 0 && option >= 4) {
        if (option == 8)
            printf("Sorry, there is no student in the database with the id %s.\n", id);
        else
            printf("There are no students matching that criteria.\n\n");
    }
}
int main(void) {
    Database *db = (Database *)malloc(sizeof(Database));
    
    db->pIDList = (StudentNode *)malloc(sizeof(StudentNode));
    db->pHonorRollList = (StudentNode *)malloc(sizeof(StudentNode));
    db->pAcademicProbationList = (StudentNode *)malloc(sizeof(StudentNode));
    db->pFreshmanList = (StudentNode *)malloc(sizeof(StudentNode));
    db->pSophomoreList = (StudentNode *)malloc(sizeof(StudentNode));
    db->pJuniorList = (StudentNode *)malloc(sizeof(StudentNode));
    db->pSeniorList = (StudentNode *)malloc(sizeof(StudentNode));
    
    printf("CS 211, Spring 2023\n");
    printf("Program 4: Database of Students\n\n");
    
    printf("Enter E to start with an empty database, \n");
    printf("or F to start with a database that has information on students from a file.\n");
    
    char c;
    
    printf("Your choice --> ");
    scanf("%c", &c);
    
    while (c != 'F' && c != 'E') {
        printf("Sorry, that input was invalid. Please try again.\n");
        printf("Your choice --> ");
        scanf("%c", &c);
    }
    
    
    if (c == 'F') {
        char filename[20];
        char str_tmp[1024];
        
        printf("Enter the name of the file you would like to use: ");
        scanf("%s", filename);
        
        FILE *fp = fopen(filename, "r");
        
        if (!fp)
            return 0;
        
        char *p;
        int flag = 0;
        
        while (!feof(fp)) {
            fgets(str_tmp, 1024, fp);
            p = strtok(str_tmp, ",");
            
            while (p && flag) {
                StudentNode *sn = (StudentNode *)malloc(sizeof(StudentNode));
                
                Student *s = (Student *)malloc(sizeof(Student));
                s->name = (char *)malloc(sizeof(char) * 20);
                s->id = (char *)malloc(sizeof(char) * 20);
                
                sn->pStudent = s;
                sn->pNext = (StudentNode *)malloc(sizeof(StudentNode));;
                
                strcpy(s->name, p);
                p = strtok(NULL, ",");
                strcpy(s->id, p);
                p = strtok(NULL, ",");
                s->gpa = atof(p);
                p = strtok(NULL, ",");
                s->creditHours = atoi(p);
                p = strtok(NULL, ",");
                
                addNode(db->pIDList, sn, NAME_ORDER);
                
                if (s->creditHours >= 0 && s->creditHours <= 29)
                    addNode(db->pFreshmanList, sn, NAME_ORDER);
                else if (s->creditHours >= 30 && s->creditHours <= 59)
                    addNode(db->pSophomoreList, sn, NAME_ORDER);
                else if (s->creditHours >= 60 && s->creditHours <= 89)
                    addNode(db->pJuniorList, sn, NAME_ORDER);
                else if (s->creditHours >= 90)
                    addNode(db->pSeniorList, sn, NAME_ORDER);
                if (s->gpa >= 3.5)
                    addNode(db->pHonorRollList, sn, GPA_ORDER);
                if (s->gpa <= 2.0)
                    addNode(db->pAcademicProbationList, sn, GPA_ORDER);
            }
            flag = 1;
        }
        
        fclose(fp);
    }
    
    while (TRUE) {
        printf("\nEnter: \tC to create a new student and add them to the database,\n");
        printf("\tR to read from the database,\n");
        printf("\tD to delete a student from the database, or\n");
        printf("\tX to exit the program.\n");
        
        getchar();
        printf("Your choice --> ");
        scanf("%c", &c);
        
        while (c != 'C' && c != 'R' && c != 'D' && c != 'X') {
            printf("Invalid option. Try again.\n");
            printf("Your choice --> ");
            scanf("%c", &c);
        }
        
        if (c == 'C') {
            StudentNode *sn = (StudentNode *)malloc(sizeof(StudentNode));
            
            Student *s = (Student *)malloc(sizeof(Student));
            s->name = (char *)malloc(sizeof(char) * 20);
            s->id = (char *)malloc(sizeof(char) * 20);
            
            sn->pStudent = s;
            sn->pNext = (StudentNode *)malloc(sizeof(StudentNode));;
            
            getchar();
            printf("Enter the name of the new student: ");
            scanf("%[^\n]s", s->name);
            
            printf("Enter the ID of the new student: ");
            scanf("%s", s->id);
            
            printf("Enter the GPA of the new student: ");
            scanf("%lf", &s->gpa);
            
            printf("Enter the credit hours of the new student: ");
            scanf("%d", &s->creditHours);
            
            addNode(db->pIDList, sn, NAME_ORDER);
            
            if (s->creditHours >= 0 && s->creditHours <= 29)
                addNode(db->pFreshmanList, sn, NAME_ORDER);
            else if (s->creditHours >= 30 && s->creditHours <= 59)
                addNode(db->pSophomoreList, sn, NAME_ORDER);
            else if (s->creditHours >= 60 && s->creditHours <= 89)
                addNode(db->pJuniorList, sn, NAME_ORDER);
            else if (s->creditHours >= 90)
                addNode(db->pSeniorList, sn, NAME_ORDER);
            if (s->gpa >= 3.5)
                addNode(db->pHonorRollList, sn, GPA_ORDER);
            if (s->gpa <= 2.0)
                addNode(db->pAcademicProbationList, sn, GPA_ORDER);
            
            printf("Successfully added the following student to the database!\n");
            
        } else if (c == 'R') {
            printf("Select one of the following: \n");
            printf("\t1) Display the head (first 10 rows) of the database\n");
            printf("\t2) Display students on the honor roll, in order of their GPA\n");
            printf("\t3) Display students on academic probation, in order of their GPA\n");
            printf("\t4) Display freshmen students, in order of their name\n");
            printf("\t5) Display sophomore students, in order of their name\n");
            printf("\t6) Display junior students, in order of their name\n");
            printf("\t7) Display senior students, in order of their name\n");
            printf("\t8) Display the information of a particular student\n");
            
            getchar();
            printf("Your choice --> ");
            scanf("%c", &c);
            
            while (c < '1' || c > '8') {
                printf("Sorry, that input was invalid. Please try again.\n");
                printf("Your choice --> ");
                scanf("%c", &c);
            }
            char id[20];
            
            switch (c) {
                case '1':
                    printStudent(db->pIDList, 1, NULL);
                    break;
                case '2':
                    printStudent(db->pHonorRollList, 2, NULL);
                    break;
                case '3':
                    printStudent(db->pAcademicProbationList, 3, NULL);
                    break;
                case '4':
                    printStudent(db->pFreshmanList, 4, NULL);
                    break;
                case '5':
                    printStudent(db->pSophomoreList, 5, NULL);
                    break;
                case '6':
                    printStudent(db->pJuniorList, 6, NULL);
                    break;
                case '7':
                    printStudent(db->pSeniorList, 7, NULL);
                    break;
                case '8':
                    printf("Enter the id of the student to find: ");
                    scanf("%s", id);
                    printStudent(db->pIDList, 8, id);
                    break;
                    
            }
        } else if (c == 'D') {
            char id[20];
            
            printf("Enter the id of the student to br removed: ");
            scanf("%s", id);
            
            removeNode(db->pIDList, id);
            removeNode(db->pHonorRollList, id);
            removeNode(db->pAcademicProbationList, id);
            removeNode(db->pFreshmanList, id);
            removeNode(db->pSophomoreList, id);
            removeNode(db->pJuniorList, id);
            removeNode(db->pSeniorList, id);
            
        } else if (c == 'X') {
            printf("Thanks for playing!\n");
            printf("Exiting...\n");
            
            return 0;
        }
    }
    
    return 0;
}
