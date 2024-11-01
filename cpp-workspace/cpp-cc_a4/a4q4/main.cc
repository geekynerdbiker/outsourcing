#include <iostream>
#include <string>
#include "cell.h"
#include "textdisplay.h"
#include "grid.h"
#include "state.h"
#include "window.h"
using namespace std;

// Do not remove any code; do not add code other than where indicated.

int main(int argc, char *argv[]) {
  cin.exceptions(ios::eofbit|ios::failbit);
  string cmd;
  Grid g;

  int count = 0;

  try {
  while (true) {
    cin >> cmd;
		try{
      if (cmd == "new") {
        int n;
        cin >> n;

			  g.init(n);
        cout << g;

      } 
      else if (cmd == "play") {
        int r = 0, c = 0;
        cin >> r >> c;
      
			  if (count % 2 == 0){
           // black move
				   g.setPiece(r,c,Colour::Black);
			  } else {
			     // white move
				   g.setPiece(r,c,Colour::White);
			  }
      
			  cout << g;

        if (g.isFull()){
          Colour winner = g.whoWon();
					string s;
				  if (winner == Colour::Black){
				    cout << "Black wins!" << endl;
						s = "Black wins!";
				  } else if (winner == Colour::White) {
				    cout << "White wins!" << endl;
						s = "White wins!";
				  } else {
            cout << "Tie!" << endl;
						s = "Tie!";
					}
					Xwindow xw = {500, 500};
					xw.drawString(250, 250, s);
				  break;
			  }
     
		    ++count;
      }
		} 
		catch (InvalidMove &) {
		  continue;
		} 
		catch(out_of_range){
      continue;
		}
  }
  }
  catch (ios::failure &) {}  // Any I/O failure quits
}




