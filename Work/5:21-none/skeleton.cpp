Board Game
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <cmath>
using namespace std;

const int TILE_SIZE=16;
const int TILE_BOARD_LENGTH = 4;
const int NUM_CHANCE_TYPE = 2;
const int NUM_CHANCE_1 = 2;
const int NUM_CHANCE_2 = 2;
const int ROUNDS=5;
const char BOARD_FRONT[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH] = { {'A', 'B', 'C', 'D'}, {'E','F', 'G', 'H'}, {'I', 'J', 'K', 'L'}, {'M', 'N', 'O', 'P'} };
char COLOR_NUM[12]={'B','B','B','B','B','B','R','R','R','R','R','R'};

//For General_Calculator class
const int CALC_MAX_EXPR_LENGTH = 100;
const int CALC_MAX_OPERATOR_LEVEL = 3;

//Color define 
#define COLOR_RED    "\033[31m"      /* Red */
#define COLOR_DEFAULT   "\033[0m"
#define COLOR_BLUE    "\033[34m"      /* Blue */


class Board {
public:
        // A Constructor of the Board class.
        // Initialze class with pair<char,pair<char, string>> tiles
        // @param board_front:  The front-side of the board (Use global variable BOARD_FRONT)
        // @param board_back:  The back-side of the board ( pair< string array (number or operation), char (color)>  read from Tiles.txt )
	    Board(const char board_front[][TILE_BOARD_LENGTH], pair<string,char> board_back[][TILE_BOARD_LENGTH]);
        
        // Fuction for getting (number or operation) and color corresponding the input alphabet.
        // @param alphabet: Player's input alphabet.
        // @return <string  (number or operation),  char color> corresponding to alphabet.
        pair<string,char> get_num_from_back(char alphabet) const;
        
        // Function for printing front-side of the board.
        void print_front() const;    
        
        // Function for printing front-side of the board except chosen tiles. 
        // @param alphabet: Player's input alphabets. 
        void print_selected_flipped(string alphabets) const;

        // Function for printing back-side of the board.
        void print_back() const;     
        
        // These two functions change the colors (Red, Blue).
	    // Note that only numbers have color. (Colors whose corresponding back sides are numbers are changed only)
        // Do not fix these two functions.!!!!
	    void color_change_board (); 
	    void shuffle(char *arr, int num); 

private:
	pair<char, pair<string,char>> tiles[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH]; 
};

//DO NOT FIX
void Board::color_change_board (){
     shuffle(COLOR_NUM,12);
     int k=0;
     for (int i=0;i<TILE_BOARD_LENGTH;i++){
         for (int j=0;j<TILE_BOARD_LENGTH;j++){
                if ( (tiles[i][j].second.first =="+") || (tiles[i][j].second.first =="-") || (tiles[i][j].second.first =="x") ||  (tiles[i][j].second.first =="/") ){
                        tiles[i][j].second.second= 'W';
                }
                else{
                         tiles[i][j].second.second= COLOR_NUM[k];
                         k++;
                }
        }
     }
}


//DO NOT FIX
void Board::shuffle(char *arr, int num) {
        srand(0);
        int temp;
        int rn;
        for (int i=0; i < num-1; i++) {
                rn = rand() % (num - i) + i; 
                temp = arr[i];
                arr[i] = arr[rn];
                arr[rn] = temp;
        }
}

class Player {
public:
        // A Constructor of the Player class.
        // Initialze chance_count array and score=0.
	    Player();

        // Function for adding player's score.
        // @param chance_type: (int type) type of chance (1,2,3).
        void add_score(int chance_type);
	
        // Function for reducing the remaining number of specific chance type.
        // If chance is used, reduce the remaining chance count. 
        // @param chance_type: (int type) type of chance (1,2,3).
        void reduce_chance_count(int chance_type);
        
        // Function for getting score.
        int get_score() const;
        
        // Function for printing remaining chance list.
	    void print_remaining_chance_list() const; 
        
	    // Function for checking the specific chance is remained.
        // @param chance_type: (int type) type of chance (1,2,3).
	    bool has_remaining_chance(int chance_type) const;
        
	    // Function for setting the color for tile
	    // @param tile_color: (char type) color ('R' or 'B')
	    void  set_color(char tile_color);

	    // Function for getting color.
	    char get_color();
 
private:
	    int chance_count[NUM_CHANCE_TYPE];
        int score;
	    char color;
};


class General_Calculator{
	public:
		
        // Evaluate the expression (consisting of various operators and terms) at the given level.
		double CalculateExpression(string s, int& idx, int level = 1);
		
        // Evalute the term number starting at the idx. idx value is updated to the next unread index.
		double EvaluateTerm(string s, int& idx);
		
        // Convert substring of given input s starting from idx into double. Update the idx value to next unread index.
		double StringToNumber(string s, int& idx);
		
        // Return the priority level of given operator character.
		int OperatorPriority(char op);
		
		
        // Evaluate the operator given left and right operands and operator chraracter.
        // Function that executes the arithmetic operation with the given inputs
        // @param operand : (double type) operand number
        // @param op : (char type) operator (+,-,*,/,^)
        // @return : The calculation outcome of the "left op right"
		double CalculateOperator(double left, double right, char op);
		
                
        // Increment the idx value until it points to the next closest non-space character.
		void skipoverSpace(string s, int& idx) ;

};

// You can use it or not
void General_Calculator::skipoverSpace(string s, int& idx) {
        while (s[idx] == ' ') {
                idx++;
        }
}

// You can use it or not
int General_Calculator::OperatorPriority(char op) {
        switch (op) {
        case '^':
                return 3;
        case 'x':
                return 2;
        case '/':
                return 2;
        case '+':
                return 1;
        case '-':
                return 1;
        default:
                return 0;
        }
}
// You can use it or not
double General_Calculator::CalculateOperator(double left, double right, char op) {
        switch (op) {
        case '^':
                return pow(left, right);
        case 'x':
                return left * right;
        case '/':
                if (right == 0) return INFINITY;
                return left / right;
        case '+':
                return left + right;
        case '-':
                return left - right;
        default:
                return left;
        }
}



class Simple_Calculator{
    public:
        // Implement the length 3/5 formula calculation utilizing the CalculateOperator function
        // @param input : (string type) formular
        // @param input_size : (int type) the length of the input (3 or 5)
        // @return : The calculation outcome for either input of size 3 or 5.
        double CalculateExpression (string s,int input_size) ;

        // Function that executes the arithmetic operation with the given inputs
        // @param operand : (double type) operand number
        // @param op : (char type) operator (+,-,*,/,^)
        // @return : The calculation outcome of the "left op right"
        double CalculateOperator(double left, double right, char op);        
        
};

// You can use it or not
double Simple_Calculator::CalculateOperator(double left, double right, char op) {
	switch (op) {
        case '^':
                return pow(left, right);
        case 'x':
                return left * right;
        case '/':
                if (right == 0) return INFINITY;
                return left / right;
        case '+':
                return left + right;
        case '-':
                return left - right;
        default:
                return left;
        }
}



class Game {
public:
        // A Constructor of the Game class.
        // Initialze board class object and current_player_idx=0
        // @param board_front:  The front-side of the board (Use global variable BOARD_FRONT)
        // @param board_back:  The back-side of the board (pair < string,char> array, Read from Tiles.txt ) 
        Game(const char board_front[][TILE_BOARD_LENGTH], pair<string,char> board_back[][TILE_BOARD_LENGTH]); 

        // Function for running the game. 
        // 1) Start round
        //   1-1) Print Game start &
	    //      Generate target number which can be calculated from both players.
        //   1-2) Print the back-side of the board for 5 seconds.
        //   1-3) Loop play_turn until round is done. 
        // 2) print final results and game is done.
	    void run(); 

        // Function for playing each turn.
        // @return true if round is done. 
	    // 1) Chance-selecting step
        // 2) Tile-selecting step
        // 3) Result evaluation step
        bool play_turn(); 

        // Function for printing the final results.
        void print_final_result() const;

        //Function for handling exception during tile selection step:
        //1) Invalid formular exception.
        //2) Repetition exception.
        //3) Color exception.
        //@param inputs: (string type) input alphabets
        //@param input_size: (int type) size of alphabets
        //@param current_player_idx: (&int) 
        //@return if exception occurs, return false. (if not, return true)
        bool handle_tile_exception(string alphabets,int input_size,int& current_player_idx) ;
 

        // Function for generating the target number. 
        // @param: vector<int> intersection: this is output of find_intersection function
        // Do not fix it.!!!!
        int generate_target_num(vector<int> intersection);

        // Function that finds all possible natural numbers using numbers and operators in the current board
        // with certain color ('R' or 'B')
        // @param color: (char type) red or blue
        // @return: (vector<int>) sorted array which contains all possible natural numbers and operators in the current board with certain color ('R' or 'B')
        vector<int> possible_target_num(char color) ;
		
        // Function for sorting
        // @param: (vector<int>& array
        void sorting (vector<int>& arr);

        //Function that finds intersection between two vectors: find all possible intersections.
        //Ex)A: [1,1,1,2,2,3,4,5,12,21],  B: [1,1,2,3,3,7,8]
        // Intersection: [1,1,2,3] (Elements of arrays are not distinct)
        // @param left_arr: (vector<int>) array
        // @param right_arr: (vector<int>) array
        // @param left_len, right_len: (int type) length of arrays
        // @return: (vector<int>) intersection 
        vector<int> find_intersection( vector<int> left_arr, vector<int> right_arr,int left_len, int right_len) const;


        // Function that verifies if the input number is integer.
        // @param number : (double type) number to verify if it is integer
        // @return : true if the number is integer, false if it is not.
        bool is_integer (double number) const; 
 
  
private:
	    int current_player_idx; 
	    Player players[2];
        Board board;
        //Simple_Calculator calculator;
        General_Calculator calculator;
	    int round;
        int target_num;
};

// DO NOT FIX
int Game::generate_target_num(vector<int> intersection){
	int size_intersection= intersection.size();
	int random_idx;
	if (size_intersection!=0) {
		random_idx = rand() % size_intersection;
		target_num= intersection[random_idx];
		return target_num;
	} else {return -1;}
}



int main(void) {  
	ifstream ifs("Tile.txt");
    if (ifs.fail()) {
		cout << "Input tile text not found! Quitting..." << endl;
		exit(1);
	}

     //IMPLEMENT HERE (Read Tile.txt)
     //   pair<string,char> board_back[TILE_BOARD_LENGTH][TILE_BOARD_LENGTH];
     //   ifs.close();        
     //   Game game=Game(BOARD_FRONT,board_back); 
     //   game.run();
     //	cout << "Thanks for playing the game!" << endl;
     //	cout << "20XX-XXXXX Name" << endl;
	return 0;

}

The end

- Tile. text
R9 R12 R6 B4
R8 B5 W+ R7
B11 W- W/ B10
Wx B1 B3 R2

Calculator
#include <iostream>
#include <fstream>
#include <string>
#include <unistd.h>
#include <vector>
#include <cmath>
using namespace std;

//For General_Calculator class
const int CALC_MAX_EXPR_LENGTH = 100;
const int CALC_MAX_OPERATOR_LEVEL = 3;


class General_Calculator{
	public:
		
        	// Evaluate the expression (consisting of various operators and terms) at the given level.
		double CalculateExpression(string s, int& idx, int level = 1);
		
        	// Evalute the term number starting at the idx. idx value is updated to the next unread index.
		double EvaluateTerm(string s, int& idx);
		
                // Convert substring of given input s starting from idx into double. Update the idx value to next unread index.
		double StringToNumber(string s, int& idx);
		
        	// Return the priority level of given operator character.
		int OperatorPriority(char op);
		
		
        	// Evaluate the operator given left and right operands and operator chraracter.
	        // Function that executes the arithmetic operation with the given inputs
        	// @param operand : (double type) operand number
        	// @param op : (char type) operator (+,-,*,/,^)
        	// @return : The calculation outcome of the "left op right"
		double CalculateOperator(double left, double right, char op);
		
                
        	// Increment the idx value until it points to the next closest non-space character.
		void skipoverSpace(string s, int& idx) ;

};

// You can use it or not
void General_Calculator::skipoverSpace(string s, int& idx) {
        while (s[idx] == ' ') {
                idx++;
        }
}

// You can use it or not
int General_Calculator::OperatorPriority(char op) {
        switch (op) {
        case '^':
                return 3;
        case 'x':
                return 2;
        case '/':
                return 2;
        case '+':
                return 1;
        case '-':
                return 1;
        default:
                return 0;
        }
}

// You can use it or not
double General_Calculator::CalculateOperator(double left, double right, char op) {
        switch (op) {
        case '^':
                return pow(left, right);
        case 'x':
                return left * right;
        case '/':
                if (right == 0) return INFINITY;
                return left / right;
        case '+':
                return left + right;
        case '-':
                return left - right;
        default:
                return left;
        }
}


class Simple_Calculator{
    public:
        // Implement the length 3 or 5 formula calculation utilizing the CalculateOperator function
        // @param input : (string type) formular
        // @param input_size : (int type) the length of the input (3 or 5)
        // @return : The calculation outcome for either input of size 3 or 5.
        double CalculateExpression (string s,int input_size) ;

        // Function that executes the arithmetic operation with the given inputs
        // @param operand : (double type) operand number
        // @param op : (char type) operator (+,-,*,/,^)
        // @return : The calculation outcome of the "left op right"
        double CalculateOperator(double left, double right, char op);        
        
};

double Simple_Calculator::CalculateExpression (string s,int input_size) {
    /* 
        (1) Implementation Details
            1) Handle the formula either of length 3 or 5 

        (2) Input / Output
            (Input) 
                input: The formula to calculate.
                input_size : The length of the input

            (Output)
                result : Calculation outcome of the given formula
    */
}

// You can use it or not
double Simple_Calculator::CalculateOperator(double left, double right, char op) {
	switch (op) {
        case '^':
                return pow(left, right);
        case 'x':
                return left * right;
        case '/':
                if (right == 0) return INFINITY;
                return left / right;
        case '+':
                return left + right;
        case '-':
                return left - right;
        default:
                return left;
        }
}



int main (void) {
	General_Calculator general_calculator;
	Simple_Calculator  simple_calculator;
    
    cout << "Enter the expression : ";
    char s[CALC_MAX_EXPR_LENGTH + 1] = "";
    cin.getline(s, CALC_MAX_EXPR_LENGTH + 1);
    int idx=0;
    double answer;
    
    cout << "Select the type of caculator (G : general / S : simple) : ";
    char cal_type;
    cin >> cal_type;
    
    if (cal_type == 'G') {
        answer= general_calculator.CalculateExpression(s,idx);
    }
    else if (cal_type == 'S'){
        answer= simple_calculator.CalculateExpression(s,5);
        // simple calculator를 구현하지 않고 바로 general_calculator로 구현한 경우에는
        // 위의 "answer = ~" 를 주석처리하고, 
        // 아래 주석처리되어 있는 line을 주석 해제하여 실행 및 제출하세요
        
        //answer= general_calculator.CalculateExpression(s,idx);
    }
    else {
        cout << "Please enter the right type (G or S)";
    }

    cout << answer << endl;
}



