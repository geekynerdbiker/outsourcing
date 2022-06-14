

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

#define F_SIZE 1024
#define R_SIZE 196

int managerMode();

int addBranch(FILE *fp);
int manageRoom(FILE *fp);
int removeBranch(FILE *fp);

int isEmptyBranch(FILE *fp, int numBranch);
int isEmptyRoom(FILE *fp, int numRoom, int numBranch);

int userMode();
void printRoom();
int reserve(char *id);
int editReservation(char *id);
int resetFile(char *date, int numBranch, int numRoom, int people, int startTime, int usingTime);

int main(int argc, char *argv[]) {
    while (1) {
        int command = 0;
        printf("1: Manager Mode, 2: User Mode (0: exit): ");
        scanf("%d", &command);
        
        if (command == 0) exit(0);
        else if (command == 1) managerMode();
        else if (command == 2) userMode();
        else printf("Invalid command\n");
    }
    
    return 0;
}

int managerMode() {
    FILE *fp;
    
    if (access("Data.txt", F_OK) < 0) {
        fp = fopen("Data.txt", "w+");
    } else {
        fp = fopen("Data.txt", "r+");
    }
    
    int command = 0;
    
    printf("1: Add Branch, 2: Manage Branch, 3: Remove Branch (0: exit): ");
    scanf("%d", &command);
    
    
    if (command == 0) return 0;
    else if (command == 1)
        addBranch(fp);
    else if (command == 2)
        manageRoom(fp);
    else if (command == 3)
        removeBranch(fp);
    else            printf("Wrong input.\n");
    
    return 0;
}

int addBranch(FILE *fp) {
    int buffer;
    int numBranch;
    
    printf("Input branch to add: ");
    scanf("%d", &numBranch);
    
    if (numBranch == 0) return 0;
    fseek(fp, (numBranch - 1) * F_SIZE, SEEK_SET);
    fread(&buffer, sizeof(int), 1, fp);
    
    if (numBranch < 1 || numBranch > 6) {
        printf("Wrong input.\n");
        return 0;
    }
    
    if (numBranch != buffer) {
        fseek(fp, (numBranch - 1) * F_SIZE, SEEK_SET);
        fwrite(&numBranch, sizeof(F_SIZE), 1, fp);
        fclose(fp);
        return 1;
    } else {
        printf("Branch already Exist.\n");
        fclose(fp);
        return 0;
    }
    
}

int manageRoom(FILE *fp) {
    int numBranch = 0;
    int numRoom = 0;
    
    int command = 0;
    int capacity = 0;
    
    char buffer[R_SIZE] = {0};
    
    printf("1: Add room, 2: Manage Room, 3: remove Room (0: exit): ");
    scanf("%d", &command);
    
    
    if (command == 0) return 0;
    else if (command == 1) {
        printf("Input branch number to add a room (0: exit): ");
        scanf("%d", &numBranch);
        
        if (numBranch == 0) return 0;
        if (numBranch > 6 || numBranch < 1) {
            printf("Wrong input.\n");
            return 0;
        }
        
        if (isEmptyBranch(fp, numBranch) == 0) {
            printf("No such branch.\n");
            return 0;
        }
        
        printf("Input room number to add a room (0: exit): ");
        scanf("%d", &numRoom);
        
        if (numRoom == 0) return 0;
        if (numRoom > 5 || numRoom < 1) {
            printf("Wrong input.\n");
            return 0;
        }
        
        printf("Input capacity of room (0: exit): ");
        scanf("%d", &capacity);
        
        if (capacity == 0) return 0;
        if (capacity > 10 || capacity < 1) {
            printf("Wrong input.\n");
            return 0;
        }
        
        if (isEmptyRoom(fp, numRoom, numBranch) == 1) {
            printf("Room already exist.\n");
            return 0;
        }
        
        fseek(fp, 4 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
        fwrite(&numRoom, sizeof(int), 1, fp);
        
        fseek(fp, 8 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
        fwrite(&capacity, sizeof(int), 1, fp);
        
        sprintf(buffer, "[ Branch %d, Room %d || capacity: %d ]", numBranch, numRoom, capacity);
        fseek(fp, 12 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
        fwrite(buffer, sizeof(buffer), 1, fp);
        
        fclose(fp);
    } else if (command == 2) {
        printf("Input branch number to edit a room (0: exit): ");
        scanf("%d", &numBranch);
        
        if (numBranch == 0) return 0;
        if (numBranch > 6 || numBranch < 1) {
            printf("Wrong input.\n");
        }
        
        if (isEmptyBranch(fp, numBranch) == 0) {
            printf("No such branch.\n");
            return 0;
        }
        
        printf("Input room number to edit (0: exit): ");
        scanf("%d", &numRoom);
        
        if (numRoom == 0) return 0;
        if (numRoom > 5 || numRoom < 1) {
            printf("Wrong input.\n");
            return 0;
        }
        
        printf("Input capacity of room to edit (0: exit): ");
        scanf("%d", &capacity);
        if (capacity == 0) return 0;
        
        if (capacity > 10 || capacity < 1) {
            printf("Wrong input.\n");
            return 0;
        }
        
        if (isEmptyRoom(fp, numRoom, numBranch) == 0) {
            printf("No such room.\n");
            return 0;
        }
        
        fseek(fp, 8 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
        fwrite(&capacity, sizeof(int), 1, fp);
        
        sprintf(buffer, "[ Branch %d, Room %d || capacity: %d ]", numBranch, numRoom, capacity);
        fseek(fp, 12 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
        fwrite(buffer, sizeof(buffer), 1, fp);
        
        fclose(fp);
    } else if (command == 3) {
        int numRoom = 0;
        int zero = 0;
        char buffer[R_SIZE] = {0};
        
        printf("Input branch number to remove a room (0: exit): ");
        scanf("%d", &numBranch);
        
        if (numBranch == 0) return 0;
        if (numBranch > 6 || numBranch < 1) {
            printf("Wrong input.\n");
        }
        
        if (isEmptyBranch(fp, numBranch) == 0) {
            printf("No such branch.\n");
            return 0;
        }
        
        printf("Input room number to remove (0: exit): ");
        scanf("%d", &numRoom);
        
        if (numRoom == 0) return 0;
        if (numRoom > 5 || numRoom < 1) {
            printf("Wrong input.\n");
            return 0;
        }
        
        if (isEmptyRoom(fp, numRoom, numBranch) == 0) {
            printf("No such room.\n");
            return 0;
        }
        
        fseek(fp, 4 + (numRoom-1)*R_SIZE + (numRoom-1) * F_SIZE, SEEK_SET);
        fwrite(&zero, sizeof(int), 1, fp);
        fseek(fp, 8 + (numRoom-1)*R_SIZE + (numRoom-1) * F_SIZE, SEEK_SET);
        fwrite(&zero, sizeof(int), 1, fp);
        fseek(fp, 4 + (numRoom-1)*R_SIZE + (numRoom-1) * F_SIZE, SEEK_SET);
        fwrite(buffer, R_SIZE, 1, fp);
        fclose(fp);
    }
    else
        printf(" Wrong input.\n");
    return 0;
}

int removeBranch(FILE *fp) {
    int numBranch = 0;
    int zero = 0;
    char buffer[F_SIZE] = {0};
    
    printf("Input branch number to remove a room (0: exit): ");
    scanf("%d", &numBranch);
    
    if (numBranch == 0) return 0;
    if (numBranch > 6 || numBranch < 1) {
        printf("Wrong input.\n");
    }
    
    if (isEmptyBranch(fp, numBranch)) {
        printf("No such branch.\n");
        return 0;
    }
    
    fseek(fp, (numBranch-1)*F_SIZE, SEEK_SET);
    fwrite(&zero, sizeof(int), 1, fp);
    fseek(fp, (numBranch-1)*F_SIZE, SEEK_SET);
    fwrite(buffer, F_SIZE, 1, fp);
    
    fclose(fp);
    return 0;
}

int isEmptyBranch(FILE *fp, int numBranch) {
    int buffer = 0;
    
    fseek(fp, (numBranch-1)*F_SIZE, SEEK_SET);
    fread(&buffer, sizeof(int), 1, fp);
    
    if (buffer != numBranch) return 0;
    else return 1;
}

int isEmptyRoom(FILE *fp, int numRoom, int numBranch) {
    int buffer = 0;
    
    fseek(fp, 4 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
    fread(&buffer, sizeof(int), 1, fp);
    
    if (buffer != numRoom) return 0;
    else return 1;
}

int userMode() {
    char id[10] = {0};
    
    while (1) {
        memset(&id, 0xFF, sizeof(id));
        printf("Input user ID: ");
        scanf("%s", id);
        
        if (strlen(id) < 11 && strlen(id) > 4) {
            break;
        } else {
            printf("Wrong input.\n");
        }
    }
    
    int command = 0;
    
    printf("1: Search room, 2: Reserve, 3: Edit reservation (0: exit): ");
    scanf("%d", &command);
    
    
    if (command == 0) return 0;
    else if (command == 1) printRoom();
    else if (command == 2) reserve(id);
    else if (command == 3) editReservation(id);
    
    return 0;
}

void printRoom() {
    FILE *fp;
    
    if (access("Data.txt", F_OK) < 0) {
        printf("No branch exist.\n");
    } else {
        fp = fopen("Data.txt", "r+");
    }
    
    int numBranch = 0;
    int numRoom = 0;
    int capacity = 0;
    char infoRoom[120] = {0};
    
    for (int i = 0;  i < 6; i++) {
        fseek(fp, i * F_SIZE, SEEK_SET);
        fread(&numBranch, sizeof(int), 1, fp);
        for (int j = 0; j < 5; j++) {
            fseek(fp, 4 + j * R_SIZE +  i * F_SIZE, SEEK_SET);
            fread(&numRoom, sizeof(int), 1, fp);
            fseek(fp, 8 + j * R_SIZE + i * F_SIZE, SEEK_SET);
            fread(&capacity, sizeof(int), 1, fp);
            fseek(fp, 12 + j * R_SIZE + i * F_SIZE, SEEK_SET);
            fread(infoRoom, sizeof(infoRoom), 1, fp);
            
            if (numRoom > 0) {
                printf("[ Branch %d < %s >]\n", numBranch, infoRoom);
            }
        }
    }
}

int reserve(char *id) {
    char today[7] = "220530";
    char date[7] = {0};
    char buffer[F_SIZE*6] = {0};
    
    int capacity = 0;
    int arrTime[14] = {0};
    int check = 0;
    
    int numBranch = 0;
    int numRoom = 0;
    int people = 0;
    int startTime = 0;
    int usingTime = 0;
    
    FILE *fp;
    FILE *reserve;
    
    if (access("Data.txt", F_OK) < 0) {
        printf("No branch exist or All of branch is full reserved.\n");
    } else {
        fp = fopen("Data.txt", "r+");
        fseek(fp, 0, SEEK_SET);
        fread(buffer, F_SIZE*6, 1, fp);
    }
    
    printf("Input day to reserve <format: YYMMDD> (0: exit): ");
    scanf("%s", date);
    if (atoi(date) == 0) return 0;
    
    if (atoi(today) == atoi(date)) {
        printf("Cannot reserve same day.");
        return 0;
    }
    
    if (access(date, F_OK) < 0) {
        reserve = fopen(date, "w+");
        fwrite(buffer, F_SIZE*6, 1, reserve);
    } else {
        reserve = fopen(date, "r+");
    }
    
    
    printRoom();
    printf("Input branch number to reserve: ");
    scanf("%d", &numBranch);
    if (numBranch == 0) return 0;
    if (isEmptyBranch(reserve, numBranch) == 0) {
        printf("No branch exist.\n");
        return 0;
    }
    
    printf("Input room number to reserve: ");
    scanf("%d", &numRoom);
    if (numRoom == 0) return 0;
    if (isEmptyRoom(reserve, numRoom, numBranch) == 0) {
        printf("No room exist.\n");
        return 0;
    }
    
    printf("Input number of people: ");
    scanf("%d", &people);
    
    if (people == 0) return 0;
    fseek(reserve, 4 + (numRoom-1)*R_SIZE + (numBranch -1) * F_SIZE, sizeof(int));
    fread(&capacity, sizeof(int), 1, reserve);
    
    if (people > capacity) {
        printf("You cannot reserve more than %d people.\n", capacity);
        return 0;
    }
    
    printf("Input startTime time to use <open: 8~22> (0: exit): ");
    scanf("%d", &startTime);
    if (startTime == 0) return 0;
    if (startTime > 22) {
        printf("Wrong input.\n");
        return 0;
    }
    
    printf("Input time to use <open: 8~22> (0: exit): ");
    scanf("%d", &usingTime);
    if (usingTime == 0) return 0;
    if (usingTime + startTime > 22) {
        printf("Wrong input.\n");
        return 0;
    }
    
    for (int i = 0; i < usingTime; i++) {
        fseek(reserve, 140 + 4 * (startTime-8+i) + (numRoom-1) * R_SIZE + (numBranch-1) * F_SIZE, SEEK_SET);
        fread(&check, sizeof(int), 1, reserve);
        if (check > 0) {
            printf("Someone already reserved at %d.\n", startTime + i);
            return 0;
        }
    }
    
    for (int i = 0; i < usingTime; i++)
        arrTime[startTime - 8 + i] = 1;
    
    for (int i = 0; i < 14; i++) {
        fseek(reserve, 140 + 4 * i + (numRoom-1) * R_SIZE + (numBranch-1) * F_SIZE, SEEK_SET);
        fread(&check, sizeof(int), 1, reserve);
        if (check > 0) arrTime[i] = 1;
    }
    fseek(reserve, 140 + (numRoom-1) * R_SIZE + (numBranch-1) * F_SIZE, SEEK_SET);
    fwrite(arrTime, sizeof(arrTime), 1, reserve);
    
    FILE *user;
    
    if (access(id, F_OK) < 0) {
        user = fopen(id, "w+");
    } else {
        user = fopen(id, "r+");
    }
    
    fseek(user, 0, SEEK_SET);
    
    fwrite(date, sizeof(date), 1, user);
    fwrite(&numBranch, sizeof(int), 1, user);
    fwrite(&numRoom, sizeof(int), 1, user);
    fwrite(&people, sizeof(int), 1, user);
    fwrite(&startTime, sizeof(int), 1, user);
    fwrite(&usingTime, sizeof(int), 1, user);
    
    fclose(user);
    fclose(reserve);
    fclose(fp);
    
    return 0;
    
}

int editReservation(char *id) {
    FILE *user;
    char date[7] = {0};
    int numBranch = 0;
    int numRoom = 0;
    int people = 0;
    int startTime = 0;
    int usingTime = 0;
    
    if (access(id, F_OK) < 0) {
        printf("No reservation information.\n");
        return 0;
    }
    
    user = fopen(id, "r+");
    
    fseek(user, 0, SEEK_SET);
    
    fread(date, sizeof(date), 1, user);
    fread(&numBranch, sizeof(int), 1, user);
    fread(&numRoom, sizeof(int), 1, user);
    fread(&people, sizeof(int), 1, user);
    fread(&startTime, sizeof(int), 1, user);
    fread(&usingTime, sizeof(int), 1, user);
    
    printf(" [ Branch %d, Room %d %dpeople from %d to %d at %s.\n", numBranch, numRoom, people, startTime, startTime+usingTime, date);
    
    int command = 0;
    
    printf("1: Change reservation information (0: exit): ");
    scanf("%d", &command);
    fclose(user);
    
    if (command == 0) return 0;
    else if (command == 1) {
        resetFile(date, numBranch, numRoom, people, startTime, usingTime);
        reserve(id);
        return 0;
    } else {
        printf(" Wrong input!\n");
        return 0;
    }
    
    return 0;
    
}

int resetFile(char *date, int numBranch, int numRoom, int people, int startTime, int usingTime) {
    
    FILE *reserveData;
    reserveData = fopen(date, "r+");
    
    int time = 0;
    
    int check = 0;
    int arrTime[14] = {0};
    
    for (int i = 0; i < 14; i++) {
        fseek(reserveData, 140 + 4 * i + (numRoom - 1) * F_SIZE + (numBranch -1) * F_SIZE, SEEK_SET);
        fread(&check, sizeof(int), 1, reserveData);
        if (check > 0) {
            arrTime[i] = 1;
        }
    }
    
    for (int i = 0; i < usingTime; i++) {
        fseek(reserveData, 140 + 4 * (startTime - 8 + i) + (numRoom - 1) * F_SIZE + (numBranch -1) * F_SIZE, SEEK_SET);
        fwrite(&time, sizeof(int), 1, reserveData);
    }
    
    fclose(reserveData);
    
    return 0;
}
