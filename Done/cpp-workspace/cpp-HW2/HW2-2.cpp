#include <iostream>
#include <vector>

using namespace std;

class BlackHole {
    int b_pos;
    int w_pos;
    int pass;
    int status;
    int curr;
    
    public BlackHole(int b, int w, int y, int z) {
        b_pos = b;
        w_pos = w;
        pass = curr = y;
        status = z;
    }
    
    int is_closed() {
        return status == curr;
    }
    
    void pass_through() {
        if (curr > status)
            curr--;
        else if (curr == status)
            curr = pass;
    }
};

int main(void) {
    int len;
    cin >> len;
    
    int black_holes;
    cin >> black_holes;
    
    int DP[len+1];
    vector<BlackHole> bhs;
    
    for (int i = 0; i < black_holes; i++) {
        int b, w, y, z;
        cin >> b >> w >> y >> z;
        BlackHole bh = new BlackHole(b, w, y, z);
        bhs.push_back(bh);
    }
        
}
/*
[ INPUT ]
5
2
3 1 1 0
4 2 1 0

[ OUTPUT ]
11


[ INPUT ]
9
2
6 4 3 0
8 2 2 2

[ OUTPUT ]
15


[ INPUT ]
10
4
5 3 3 3
6 4 5 5
7 2 1 1
9 8 1 1

[ OUTPUT ]
10


[ INPUT ]
10
4
5 3 1 0
6 4 2 0
7 2 1 0
9 8 1 0

[ OUTPUT ]
36
 */
