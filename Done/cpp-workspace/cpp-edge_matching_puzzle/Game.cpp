#include <iostream>
#include <vector>
#include <algorithm>

#define LINE 3
#define DIR 4
#define LEN 9

using namespace std;

vector<int> rotate_card(vector<int> card);
bool check_left(vector<vector<int>> &placement, vector<int> &card, int placed);
bool check_up(vector<vector<int>> &placement, vector<int> &card, int placed);
bool check_left_and_up(vector<vector<int>> &placement, vector<int> &card, int placed);
bool match(vector<vector<int>> &placement, vector<int> &card);
void try_card(vector<vector<int>> &placement, vector<int> &card, vector<vector<int>> &untried);
void add_placement(vector<vector<int>> &placement);
void solve(vector<vector<int>> &placement, vector<vector<int>> &cardset);

int solution = 0;
vector<vector<int>> results;

vector<int> rotate_card(vector<int> card) {
    vector<int> rotated;
    
    rotated.push_back(card[1]);
    rotated.push_back(card[2]);
    rotated.push_back(card[3]);
    rotated.push_back(card[0]);
    rotated.push_back(card[4]);
    rotated.push_back(card[5]+1);
    
    return rotated;
}

bool check_left(vector<vector<int>> &placement, vector<int> &card, int placed) {
    if ((placement[placed - 1][1] == 1 && card[3] == 2) || (placement[placed - 1][1] == 2 && card[3] == 1))
        return true;
    else if ((placement[placed - 1][1] == 3 && card[3] == 4) || (placement[placed - 1][1] == 4 && card[3] == 3))
        return true;
    else if ((placement[placed - 1][1] == 5 && card[3] == 6) || (placement[placed - 1][1] == 6 && card[3] == 5))
        return true;
    else if ((placement[placed - 1][1] == 7 && card[3] == 8) || (placement[placed - 1][1] == 8 && card[3] == 7))
        return true;
    else
        return false;
}


bool check_up(vector<vector<int>> &placement, vector<int> &card, int placed) {
    if ((placement[placed - LINE][2] == 1 && card[0] == 2) || (placement[placed - LINE][2] == 2 && card[0] == 1))
        return true;
    else if ((placement[placed - LINE][2] == 3 && card[0] == 4) || (placement[placed - LINE][2] == 4 && card[0] == 3))
        return true;
    else if ((placement[placed - LINE][2] == 5 && card[0] == 6) || (placement[placed - LINE][2] == 6 && card[0] == 5))
        return true;
    else if ((placement[placed - LINE][2] == 7 && card[0] == 8) || (placement[placed - LINE][2] == 8 && card[0] == 7))
        return true;
    else
        return false;
}

bool check_left_and_up(vector<vector<int>> &placement, vector<int> &card, int placed) {
    return check_left(placement, card, placed) && check_up(placement, card, placed);
}

bool match(vector<vector<int>> &placement, vector<int> &card) {
    int placed = (int)placement.size();
    
    if (placed == 0)
        return true;
    else if (placed < LINE)
        return check_left(placement, card, placed);
    else if (placed % LINE == 0)
        return check_up(placement, card, placed);
    else
        return check_left_and_up(placement, card, placed);
}

void try_card(vector<vector<int>> &placement, vector<int> &card, vector<vector<int>> &remaining) {
    if (match(placement, card)) {
        placement.push_back(card);
        solve(placement, remaining);
    }
}

void add_placement(vector<vector<int>> &placement) {
    vector<int> result;
    for (int i = 0; i < placement.size(); i++) {
        result.push_back(placement[i][4]);
        result.push_back(placement[i][5]);
    }
    results.push_back(result);
}

void solve(vector<vector<int>> &placement, vector<vector<int>> &cardset) {
    if (placement.size() == LEN) {
        solution++;
        add_placement(placement);
    } else {
        vector<vector<int>> remaining;
        for (int i = 0; i < cardset.size(); i++) {
            remaining.assign(cardset.size(), vector<int>(cardset.size()));
            copy(cardset.begin(), cardset.end(), remaining.begin());
            remaining.erase(remove(remaining.begin(), remaining.end(), cardset[i]), remaining.end());
        
            try_card(placement, cardset[i], remaining);
            
            vector<int> rotated = rotate_card(cardset[i]);
            try_card(placement, rotated, remaining);
            
            rotated = rotate_card(rotated);
            try_card(placement, rotated, remaining);
            
            rotated = rotate_card(rotated);
            try_card(placement, rotated, remaining);
        }
    }
    placement.pop_back();
}
int main(int argc, char **argv) {
    vector<vector<int>> cards;

    for (int i = 0; i < LEN; i++) {
        vector<int> v;
        for (int j = 0; j < DIR; j++) {
            int k;
            cin >> k;
            v.push_back(k);
        }
        v.push_back(i+1);
        v.push_back(0);
        cards.push_back(v);
    }
    
    vector<vector<int>> placement;
    
    solve(placement, cards);
    
    cout << solution << endl;
    for (int i = 0; i < solution; i++) {
        for (int j = 0; j < LEN; j++)
            cout << results[i][j * 2] << "(" << results[i][j * 2 + 1] << ") ";
        cout << endl;
    }

    return 0;
}

/*
 INPUT
1 4 3 5
3 1 2 6
6 1 3 4
7 8 2 5
7 3 6 2
6 4 3 1
7 4 6 5
6 8 1 3
8 2 5 6
 */
