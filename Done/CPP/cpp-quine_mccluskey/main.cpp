#include <iostream>
#include <fstream>
#include <cstring>
#include <time.h>

using namespace std;

int transform(char**minimum_set, int set_num, int length);
void search(char **table, char**pi, int prime_check, int minimum, char**minimum_set, int minimum_number, int length);
void table(char **pi, int prime_check, char ** min, int minimum, int length);
int get_prime(char ***hamming, int length, int * digit, int hamming_length, char **min, int minimum);
void column(char ***hamming, int length, int * digit, int hamming_length, char **min, int minimum);

int main(void) {
    char **min, **hamming, ***next_hamming;
    int length, dontcare = 0, minimum = 0, d = 0, m = 0, hamming_count = 0, i, t;
    int *digit, *hamming_arrange;
    char line[64], *context, **data_digit;
    bool bit_checker = false;
    
    ifstream fin("input_minterm.txt");

    if (!fin) {
        cout << "No such file exist.";
        return 0;
    }

    while (!fin.eof()) {
        fin.getline(line, 64);
        
        if (bit_checker == false) {
            length = atoi(strtok_s(line, " ", &context));
            bit_checker = true;
            continue;
        } else {
            if (*strtok_s(line, " ", &context) == 'd')
                dontcare++;
            else
                minimum++;
        }
    }

    min = new char *[minimum];

    for (int i = 0; i < minimum; i++)
        min[i] = new char[length];

    fin.close();
    fin.open("input_minterm.txt");

    bit_checker = false;

    data_digit = new char *[minimum + dontcare];
    for (int i = 0; i < minimum + dontcare; i++)
        data_digit[i] = new char[64];

    i = 0;
    t = 0;
    digit = new int[length + 1];
    hamming_arrange = new int[length + 1];

    hamming = new char *[minimum + dontcare];
    for (int i = 0; i < minimum + dontcare; i++)
        hamming[i] = new char[length];

    for (int i = 0; i < length + 1; i++) {
        digit[i] = 0;
        hamming_arrange[i] = 0;
    }

    while (!fin.eof()) {
        fin.getline(data_digit[t], 64);

        if (bit_checker == false) {
            bit_checker = true;
            continue;
        } else {
            hamming_count = 0;
            if (*strtok_s(data_digit[t], " ", &context) == 'm') {
                min[i] = strtok_s(NULL, " ", &context);
                for (int k = 0; k < length; k++) {
                    if (min[i][k] == '1')
                        hamming_count++;
                }
                digit[hamming_count]++;
                hamming[t] = min[i];
                i++;

            } else {
                hamming[t] = strtok_s(NULL, " ", &context);
                for (int k = 0; k < length; k++) {
                    if (hamming[t][k] == '1')
                        hamming_count++;
                }
                digit[hamming_count]++;
            }
            t++;
        }
    }

    fin.close();

    next_hamming = new char**[length + 1];

    for (int i = 0; i < length + 1; i++)
        next_hamming[i] = new char*[digit[i]];

    for (int i = 0; i < length + 1; i++) {
        for (int j = 0; j < digit[i]; j++)
            next_hamming[i][j] = new char[length];
    }


    for (int i = 0; i < minimum + dontcare; i++) {
        t = 0;

        for (int j = 0; j < length; j++) {
            if (hamming[i][j] == '1')
                t++;
        }
        next_hamming[t][hamming_arrange[t]] = hamming[i];
        hamming_arrange[t]++;
    }

    column(next_hamming, length, digit, length, min, minimum);
    
    for (int i = 0; i < length + 1; i++)
        delete[] next_hamming[i];

    delete[] next_hamming;

    delete[] digit;
    delete[] hamming_arrange;

    delete[] min;

    for (int i = 0; i < minimum + dontcare; i++)
        delete[] data_digit[i];

    delete[] data_digit;

    delete[] hamming;

    return 0;
}

int get_prime(char ***hamming, int length, int * ham, int hamming_length, char **min, int minimum) {
    int n = 0;
    int col_length;
    int ham_distance = 0;
    int check = 0, check_over = 0;
    
    static int prime_check1 = 0;
    static char **pi;
    
    int *next_ham;
    char***next_col;

    next_ham = new int[hamming_length];
    next_col = new char**[hamming_length];

    for (int i = 0; i < hamming_length; i++) {
        col_length = 0;
        for (int j = 0; j < ham[i]; j++) {
            for (int e = 0; e < ham[i + 1]; e++) {
                for (int k = 0; k < length; k++) {
                    if (hamming[i][j][k] != hamming[i + 1][e][k])
                        ham_distance++;
                } if (ham_distance == 1)
                    col_length++;
                ham_distance = 0;
            }
        }
        next_col[i] = new char*[col_length];
        next_ham[i] = col_length;
    }

    for (int i = 0; i < hamming_length; i++) {
        for (int j = 0; j < next_ham[i]; j++)
            next_col[i][j] = new char[length];
    }


    for (int i = 0; i < hamming_length; i++) {
        for (int j = 0; j < ham[i]; j++) {
            for (int e = 0; e < ham[i + 1]; e++) {
                for (int k = 0; k < length; k++) {
                    if (hamming[i][j][k] != hamming[i + 1][e][k])
                        ham_distance++;
                } if (ham_distance == 1) {
                    for (int k = 0; k < length; k++) {
                        if (hamming[i][j][k] != hamming[i + 1][e][k])
                            next_col[i][n][k] = 'X';
                        else
                            next_col[i][n][k] = hamming[i][j][k];
                    }
                    n++;
                }
                ham_distance = 0;
            } if (n == next_ham[i])
                break;
        }
        n = 0;
    }


    for (int i = 0; i < hamming_length + 1; i++) {
        for (int j = 0; j < ham[i]; j++) {
            check = 0;
            for (int e = 0; e < hamming_length; e++) {
                for (int d = 0; d < next_ham[e]; d++) {
                    for (int k = 0; k < length; k++) {
                        if (hamming[i][j][k] != next_col[e][d][k])
                            ham_distance++;
                    } if (ham_distance == 1)
                        check++;
                    ham_distance = 0;
                }
            } if (check == 0)
                prime_check1++;
        }
    }
    if (hamming_length == 0)
        return prime_check1;
    else
        get_prime(next_col, length, next_ham, hamming_length - 1, min, minimum);
}

void table(char **pi, int prime_check, char ** min, int minimum, int length) {
    int m = 0;
    int ess_check = 0;
    
    bool minterm = true;
    
    char **table;
    char **minimum_set;
    
    
    table = new char *[prime_check];
    minimum_set = new char*[prime_check];
    
    for (int i = 0; i < prime_check; i++)
        table[i] = new char[minimum];

    for (int i = 0; i < prime_check; i++)
        minimum_set[i] = new char[length];

    for (int i = 0; i < prime_check; i++) {
        for (int j = 0; j < minimum; j++) {
            for (int k = 0; k < length; k++) {
                if (pi[i][k] != 'X') {
                    if (pi[i][k] != min[j][k]) {
                        minterm = false;
                        break;
                    }
                }
            } if (minterm == true)
                table[i][j] = 'X';
            else
                table[i][j] = '0';
            minterm = true;
        }
    }
        
    for (int i = 0; i < minimum; i++) {
        ess_check = 0;
        
        for (int j = 0; j < prime_check; j++) {
            if (table[j][i] == 'X')
                ess_check++;
        } if (ess_check == 1) {
            for (int j = 0; j < prime_check; j++) {
                if (table[j][i] == 'X') {
                    minimum_set[m] = pi[j];
                    m++;
                    
                    for (int k = 0; k < minimum; k++) {
                        if (table[j][k] == 'X') {
                            for (int d = 0; d < prime_check; d++)
                                table[d][k] = '0';
                        }
                    }
                }
            }
        }
    }
        
    search(table, pi, prime_check, minimum, minimum_set, m, length);
    
    delete[] minimum_set;

    for (int i = 0; i < prime_check; i++)
        delete table[i];
    delete[] table;
}

void column(char ***hamming, int length, int * ham, int hamming_length, char **min, int minimum) {
    int n = 0; int static prime, prime_check2 = 0;
    int check = 0, check_over = 0;
    static char **pi;
    int ham_distance = 0;
    int *next_ham;
    char***next_col;
    int col_length;

    next_ham = new int[hamming_length];
    next_col = new char**[hamming_length];

    for (int i = 0; i < hamming_length; i++) {
        col_length = 0;
        
        for (int j = 0; j < ham[i]; j++) {
            for (int e = 0; e < ham[i + 1]; e++) {
                for (int k = 0; k < length; k++) {
                    if (hamming[i][j][k] != hamming[i + 1][e][k])
                        ham_distance++;
                } if (ham_distance == 1)
                    col_length++;
                ham_distance = 0;
            }
        }
        next_col[i] = new char*[col_length];
        next_ham[i] = col_length;
    }

    for (int i = 0; i < hamming_length; i++) {
        for (int j = 0; j < next_ham[i]; j++)
            next_col[i][j] = new char[length];
    }


    for (int i = 0; i < hamming_length; i++) {
        for (int j = 0; j < ham[i]; j++) {
            for (int e = 0; e < ham[i + 1]; e++) {
                for (int k = 0; k < length; k++) {
                    if (hamming[i][j][k] != hamming[i + 1][e][k])
                        ham_distance++;
                } if (ham_distance == 1) {
                    for (int k = 0; k < length; k++) {
                        if (hamming[i][j][k] != hamming[i + 1][e][k])
                            next_col[i][n][k] = 'X';
                        else
                            next_col[i][n][k] = hamming[i][j][k];
                    }
                    n++;
                }
                ham_distance = 0;
            }
            if (n == next_ham[i])
                break;
        }
        n = 0;
    }

    if (prime_check2 == 0) {
        prime = get_prime(hamming, length, ham, hamming_length, min, minimum);
        pi = new char*[prime];
        for (int i = 0; i <prime; i++)
            pi[i] = new char[length];
    }

    for (int i = 0; i < hamming_length + 1; i++){
        for (int j = 0; j < ham[i]; j++) {
            check = 0;
            
            for (int e = 0; e < hamming_length; e++) {
                for (int d = 0; d < next_ham[e]; d++) {
                    for (int k = 0; k < length; k++) {
                        if (hamming[i][j][k] != next_col[e][d][k])
                            ham_distance++;
                    } if (ham_distance == 1)
                        check++;
                    ham_distance = 0;
                }
            } if (check == 0) {
                pi[prime_check2] = hamming[i][j];
                
                if (prime_check2 > 0) {
                    for (int j = 0; j < prime_check2; j++) {
                        check_over = 0;
                        for (int i = 0; i < length; i++) {
                            if (pi[prime_check2][i] == pi[j][i])
                                check_over++;
                        } if (check_over == length) {
                            prime_check2--;
                            break;
                        }
                    }
                }
                prime_check2++;
            }
        }
    }

    if (hamming_length == 0) {
        table(pi, prime_check2, min, minimum, length);
        
        delete[] next_col;
        delete[] next_ham;
        
        delete[] pi;
    }
    else
        column(next_col, length, next_ham, hamming_length - 1, min, minimum);
}

void search(char **table, char**pi, int prime_check, int minimum, char**minimum_set, int minimum_number, int length) {
    ofstream file("result.txt");
    
    for (int i = 0; i < minimum; i++) {
        for (int j = 0; j < prime_check; j++) {
            if (table[j][i] == 'X') {
                minimum_set[minimum_number] = pi[j];
                minimum_number++;
                
                for (int k = 0; k < minimum; k++) {
                    if (table[j][k] == 'X') {
                        for (int d = 0; d < prime_check; d++)
                            table[d][k] = '0';
                    }
                }
            }
        }
    }

    for (int i = 0; i < minimum_number; i++) {
        for (int j = 0; j < length; j++)
            file << minimum_set[i][j];
        file << endl;
    }

    file << "Cost(# of transistors): " << transform(minimum_set, minimum_number, length) << endl;
    cout << "파일 생성 완료!" << endl;
    file.close();

}

int transform(char**minimum_set, int set_num, int length) {
    int total_trans = 0;

    for (int i = 0; i < set_num; i++) {
        for (int j = 0; j < length; j++) {
            if (minimum_set[i][j] != 'X') {
                total_trans += 2;
                if (minimum_set[i][j] == '0')
                    total_trans += 2;
            }
        }
        total_trans += 2;
    }

    total_trans += (set_num * 2) + 2;
    return total_trans;
}
