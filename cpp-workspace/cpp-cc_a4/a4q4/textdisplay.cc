#include "textdisplay.h"
#include "subject.h"

// ctor
TextDisplay::TextDisplay(int n): gridSize{n} {
  for(int i = 0; i < n; ++i){
	 std::vector<char> arr;
		for(int j = 0; j < n; ++j){
       if ((i == n/2 - 1 && j == n/2 - 1) || (i == n/2 && j == n/2)){
			   arr.emplace_back('B');  
			 } else if ((i == n/2 - 1 && j == n/2) || (i == n/2 && j == n/2 - 1)){
			   arr.emplace_back('W');
			 } else {
         arr.emplace_back('-');
			 }
		}
		theDisplay.emplace_back(arr);
	}
}

// notify
void TextDisplay::notify(Subject<Info, State> &whoNotified){
    Info i = whoNotified.getInfo();
		Colour c = i.colour;
		size_t row = i.row;
		size_t col = i.col;
		char & text = theDisplay.at(row).at(col);
		if (c == Colour::Black){
       text = 'B';
		} else if(c == Colour::White){
       text = 'W';
		} else {
       text = '-';
		}
}


// output operator
std::ostream & operator<<(std::ostream & out, const TextDisplay & td){
    for(int i = 0; i < td.gridSize; ++i){
		   for(int j = 0; j < td.gridSize; ++j){
			    out << td.theDisplay.at(i).at(j); 
			 }
			 out << std::endl;
		}
	return out;
}









