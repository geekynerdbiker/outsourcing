#include <iostream>
#include <cstdio>
#include <string>
#include <unistd.h>

using namespace std;

#define F_SIZE 1024
#define R_SIZE 196
#define F_OK 0

class Manage{

private:
    int mode;
    FILE *fp;
    int numBranch;
    int numRoom;
    int capacity;
    int buffer;

    void addBranch() {
        cout << "Input branch to add: ";
        cin >> numBranch;
        
        if (numBranch == 0) return;
        fseek(fp, (numBranch - 1) * F_SIZE, SEEK_SET);
        fread(&buffer, sizeof(int), 1, fp);
        
        if (numBranch != buffer) {
            fseek(fp, (numBranch - 1) * F_SIZE, SEEK_SET);
            fwrite(&numBranch, sizeof(F_SIZE), 1, fp);
            fclose(fp);
            return;
        } else {
            cout << "Branch already Exist.\n";
            fclose(fp);
            return;
        }
    }
    
    void manageRoom() {
        
        int zero = 0;
        char buffer[R_SIZE] = {0};

        cout << "1: Add room, 2: Manage Room, 3: remove Room (0: exit): ";
        cin >> mode;

        while (1) {
            if (mode == 0) return;
            else if (mode == 1) {
                cout << "Input branch number to add a room (0: exit): ";
                cin >> numBranch;

                if (numBranch == 0) return;
                if (numBranch > 6 || numBranch < 1) cout << "Wrong input.\n";
                
                if (isEmptyBranch(numBranch) == 0) {
                    cout << "No such branch.\n";
                    break;
                }

                cout << "Input room number to add a room (0: exit): ";
                cin >> numRoom;
                
                if (numRoom == 0) return;
                if (numRoom > 5) {
                    cout << "Wrong input.\n";
                    break;
                }

                cout << "Input capacity of room (0: exit): ";
                cin >> capacity;
                
                if (capacity == 0) return;
                if (capacity > 10) {
                    cout << " 잘못된 접근입니다!\n";
                    return;
                }

                if (isEmptyRoom(numRoom, numBranch) == 1) {
                    cout << "Room already exist.\n";
                    return;
                }

                fseek(fp, 4 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
                fwrite(&numRoom, sizeof(int), 1, fp);
                
                fseek(fp, 8 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
                fwrite(&capacity, sizeof(int), 1, fp);

                sprintf(buffer, "[ Branch %d, Room %d || capacity: %d ]", numBranch, numRoom, capacity);
                fseek(fp, 12 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
                fwrite(buffer, sizeof(buffer), 1, fp);

                fclose(fp);
                return;
            } else if (mode == 2) {
                cout << "Input branch number to edit a room (0: exit): ";
                cin >> numBranch;

                if (numBranch == 0) return;
                if (numBranch > 6 || numBranch < 1) cout << " 잘못된 접근입니다!\n";
                
                if (isEmptyBranch(numBranch) == 0) {
                    cout << "No such branch.\n";
                    break;
                }

                cout << "Input room number to edit (0: exit): ";
                cin >> numRoom;

                if (numRoom == 0) return;
                if (numRoom > 5) {
                    cout << " 잘못된 접근입니다!\n";
                    break;
                }

                cout << "Input capacity of room to edit (0: exit): ";
                cin >> capacity;
                if (capacity == 0) return;
                if (capacity > 10) {
                    cout << " 잘못된 접근입니다!\n";
                    return;
                }

                if (isEmptyRoom(numRoom, numBranch) == 0) {
                    cout << "No such room.\n";
                    return;
                }

                fseek(fp, 8 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
                fwrite(&capacity, sizeof(int), 1, fp);

                sprintf(buffer, "[ Branch %d, Room %d || capacity: %d ]", numBranch, numRoom, capacity);
                fseek(fp, 12 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
                fwrite(buffer, sizeof(buffer), 1, fp);
                
                fclose(fp);
                return;
            } else if (mode == 3) {
                memset(buffer, 0, sizeof(R_SIZE));

                cout << "Input branch number to remove a room (0: exit): ";
                cin >> numBranch;
                
                if (numBranch == 0) break;
                if (isEmptyBranch(numBranch) == 0) {
                    cout << "No such branch.\n";
                    break;
                }
                
                cout <<"Input room number to remove (0: exit): ";
                cin >> numRoom;

                if (numRoom == 0) break;
                if (isEmptyRoom(numRoom, numBranch) == 0) {
                    printf("No such room.\n");
                    break;
                }

                fseek(fp, 4 + (numRoom-1)*R_SIZE + (numBranch-1) * F_SIZE, SEEK_SET);
                fwrite(&zero, sizeof(int), 1, fp);
                fseek(fp, 8 + (numRoom-1)*R_SIZE + (numBranch-1) * F_SIZE, SEEK_SET);
                fwrite(&zero, sizeof(int), 1, fp);
                fseek(fp, 4 + (numRoom-1)*R_SIZE + (numBranch-1) * F_SIZE, SEEK_SET);
                fwrite(buffer, R_SIZE, 1, fp);
                
                fclose(fp);
                return;
            } else {
                cout << "Wrong Option!!" << endl;
            }
        }
    }

    void removeBranch() {
        char buffer[F_SIZE] = {0};
        int zero = 0;
        cout << "Input branch number to remove a room (0: exit): ";
        cin >> numBranch;

        if (numBranch == 0) return;
        if (isEmptyBranch(numBranch) == 0) {
            printf("No such branch.\n");
            return;
        }

        fseek(fp, (numBranch-1)*F_SIZE, SEEK_SET);
        fwrite(&zero, sizeof(int), 1, fp);
        fseek(fp, (numBranch-1)*F_SIZE, SEEK_SET);
        fwrite(buffer, F_SIZE, 1, fp);
        
        fclose(fp);
        return;
    }

public:
    Manage() {
        if (access("Data.txt", F_OK) < 0) {
            fp = fopen("Data.txt", "w+");
        } else {
            fp = fopen("Data.txt", "r+");
        }
    }
    ~Manage() {}

    // 관리자 모드
    void manageMode() {
        cout << "1: Add Branch, 2: Manage Branch, 3: Remove Branch (0: exit): ";
        cin >> mode;
        
        if (mode == 0) return;
        else if (mode == 1) {
                addBranch();
                return;
        } else if (mode == 2) {
                manageRoom();
                return;
        } else if (mode == 3) {
                removeBranch();
                return;
        } else {
            cout << "Wrong Option!\n";
        }
    }

protected:
    int isEmptyBranch(int numBranch) {
        int buffer = 0;
        
        fseek(fp, (numBranch-1)*F_SIZE, SEEK_SET);
        fread(&buffer, sizeof(int), 1, fp);

        if (buffer != numBranch) return 0;
        else return 1;
    }

    int isEmptyRoom(int numRoom, int numBranch) {
        int buffer = 0;
        
        fseek(fp, 4 + (numRoom-1)*R_SIZE + (numBranch-1)*F_SIZE, SEEK_SET);
        fread(&buffer, sizeof(int), 1, fp);

        if (buffer != numRoom) return 0;
        else return 1;
    }
};

class User : protected Manage{

private:
    int mode;
    
    int numBranch;
    int numRoom;
    int people;
    int startTime;
    int usingTime;

    char id[11];
    char date[7];

    int check;

    FILE *fp;
    FILE *reserveData;
    FILE *user;

    void printRoom() {
        if (access("Data.txt", F_OK) < 0) {
            cout << "No branch exist or All of branch is full reserved.\n";
        } else {
            fp = fopen("Data.txt", "r+");
        }
        int capacity = 0;
        char infoRoom[120] = {0};

        for(int i = 0;  i < 6; i++) {
            fseek(fp, i * F_SIZE, SEEK_SET);
            fread(&numBranch, sizeof(int), 1, fp);
            for(int j = 0; j < 5; j++) {
                fseek(fp, 4 + j * R_SIZE +  i * F_SIZE, SEEK_SET);
                fread(&numRoom, sizeof(int), 1, fp);
                fseek(fp, 8 + j * R_SIZE + i * F_SIZE, SEEK_SET);
                fread(&capacity, sizeof(int), 1, fp);
                fseek(fp, 12 + j * R_SIZE + i * F_SIZE, SEEK_SET);
                fread(infoRoom, sizeof(infoRoom), 1, fp);
                if (numRoom > 0) {
                    cout << "[ Branch " << numBranch << " <" << infoRoom << " >]\n";
                }
            }
        }
        fclose(fp);
    }

    void reserveUser() {
        char today[7] = "220526";
        char filebuffer[F_SIZE*6] = {0};
        int capacity = 0;
        int arrTime[14] = {0};
        
        if (access("Data.txt", F_OK) < 0) {
            cout << "No branch exist or All of branch is full reserved.\n" << endl;
        } else {
            fp = fopen("Data.txt", "r+");
            fseek(fp, 0, SEEK_SET);
            fread(filebuffer, F_SIZE*6, 1, fp);
        }

        cout << "Input day to reserve <format: YYMMDD> (0: exit): ";
        cin >> date;
        if (atoi(date) == 0) return;

        if (atoi(today) == atoi(date)) {
            cout << "Cannot reserve same day.\n";
            return;
        }
        
        if (access(date, F_OK) < 0) {
            reserveData = fopen(date, "w+");
            fwrite(filebuffer, F_SIZE*6, 1, reserveData);
        } else {
            reserveData = fopen(date, "r+");
        }
        
        printRoom();
        cout << "Input branch number to reserve: ";
        scanf("%d", &numBranch);
        
        if (numBranch == 0) return;
        if (isEmptyBranch(numBranch) == 0) {
            cout << "No branch exist.\n";
            return;
        }

        cout << "Input room number to reserve: ";
        cin >> numRoom;
        
        if (numRoom == 0) return;
        if (isEmptyRoom(numRoom, numBranch) == 0) {
            cout << "No room exist.\n";
            return;
        }
        cout << "Input number of people: ";
        cin >> people;
        
        if (people == 0) return;
        fseek(reserveData, 8 + (numRoom-1)*R_SIZE + (numBranch -1) * F_SIZE, SEEK_SET);
        fread(&capacity, sizeof(int), 1, reserveData);

        if (people > capacity) {
            cout << "You cannot reserve more than " << capacity << " people.\n";
            return;
        }
        cout << "Input startTime time to use <open: 8~22> (0: exit): ";
        cin >> startTime;
        
        if (startTime == 0) return;
        if (startTime > 22) {
            cout << "Wrong input.\n";
            return;
        }
        cout << "Input time to use <open: 8~22> (0: exit): ";
        cin >> usingTime;
        if (usingTime == 0) return;
        if (usingTime + startTime > 22) {
            cout << "Wrong input.\n";
            return;
        }

        for(int i = 0; i < usingTime; i++) {
            fseek(reserveData, 140 + 4 * (startTime-8+i) + (numRoom-1) * R_SIZE + (numBranch-1) * F_SIZE, SEEK_SET);
            fread(&check, sizeof(int), 1, reserveData);
            if (check > 0) {
                cout  << "Someone already reserved at " << startTime + i << ".\n";
                return;
            }
        }

        for(int i = 0; i < usingTime; i++)
            arrTime[startTime - 8 + i] = 1;
        
        for(int i = 0; i < 14; i++) {
            fseek(reserveData, 140 + 4 * i + (numRoom-1) * R_SIZE + (numBranch-1) * F_SIZE, SEEK_SET);
            fread(&check, sizeof(int), 1, reserveData);
            if (check > 0) arrTime[i] = 1;
        }
        
        fseek(reserveData, 140 + (numRoom-1) * R_SIZE + (numBranch-1) * F_SIZE, SEEK_SET);
        fwrite(arrTime, sizeof(arrTime), 1, reserveData);

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
        fclose(reserveData);
        fclose(fp);

        return;
    }
    
    // 예약 수정
    void eidtReservation() {

        if (access(id, F_OK) < 0) {
            cout << "No reservation information.\n";
            return;
        }

        user = fopen(id, "r+");

        memset(date, (char)0xFF, sizeof(date));
    
        fseek(user, 0, SEEK_SET);
        fread(date, sizeof(date), 1, user);
        fread(&numBranch, sizeof(int), 1, user);
        fread(&numRoom, sizeof(int), 1, user);
        fread(&people, sizeof(int), 1, user);
        fread(&startTime, sizeof(int), 1, user);
        fread(&usingTime, sizeof(int), 1, user);

        cout << "[ Branch " << numBranch << ", Room " << numRoom << " " << people << "people from " << startTime << " to " << startTime+usingTime << " at " << date << ".\n";

        cout << "1: Change reservation information (0: exit): ";
        cin >> mode;
        fclose(user);

        if (mode == 0) return;
        else if (mode == 1) {
            resetFile();
            reserveUser();
            return;
        } else {
            cout << "Wrong Option!\n";
            return;
        }

        return;

    }

    void resetFile() {
        reserveData = fopen(date, "r+");

        int time = 0;
        int arrTime[14] = {0};

        for(int i = 0; i < 14; i++) {
            fseek(reserveData, 140 + 4 * i + (numRoom - 1) * F_SIZE + (numBranch -1) * F_SIZE, SEEK_SET);
            fread(&check, sizeof(int), 1, reserveData);
            if (check > 0) {
                arrTime[i] = 1;
            }
        }

        for(int i = 0; i < usingTime; i++) {
            fseek(reserveData, 140 + 4 * (startTime - 8 + i) + (numRoom - 1) * F_SIZE + (numBranch -1) * F_SIZE, SEEK_SET);
            fwrite(&time, sizeof(int), 1, reserveData);
        }

        fclose(reserveData);

        return;
    }

public:
    User() {};
    ~User() {};

    void userMode() {
        while (1) {
            while (1) {
                memset(&id, 0xFF, sizeof(id));
                cout << "Input user ID: ";
                cin >> id;

                if (strlen(id) < 11 && strlen(id) > 4) break;
                else cout <<"Wrong input.\n";
            }

            cout << "1: Search room, 2: Reserve, 3: Edit reservation (0: exit): ";
            cin >> mode;

            if (mode == 0) return;
            else if (mode == 1) {
                printRoom();
                return;
            } else if (mode == 2) {
                reserveUser();
                return;
            } else if (mode == 3) {
                eidtReservation();
                return;
            }
        }
    }
};

int main(int argc, char *argv[]) {
    Manage manage;
    User user;
    
    while (1) {
        int command = 0;
        cout << "1: Manager Mode, 2: User Mode (0: exit): ";
        cin >> command;
        
        if (command == 0) exit(0);
        else if (command == 1) manage.manageMode();
        else if (command == 2) user.userMode();
        else printf("Invalid command\n");
    }

    return 0;
}
