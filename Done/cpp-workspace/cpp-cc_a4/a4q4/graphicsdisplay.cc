#include "graphicsdisplay.h"
#include "window.h"
#include "observer.h"
#include "subject.h"

GraphicsDisplay::GraphicsDisplay(int gridSize) : gridSize{gridSize} , xw{500, 500}{
		 int index = 500 / gridSize;
		 for(int i = 0; i < gridSize; ++i){
		    for(int j  = 0; j < gridSize; ++j){
           if ((i == gridSize/2 && j == gridSize/2) || (i == gridSize/2 - 1 && j == gridSize/2 -1)) {
					   xw.fillRectangle(i*index, j*index, index, index, 7);
					 } else if ((i == gridSize/2 - 1 && j == gridSize/2) || (i == gridSize/2 && j == gridSize/2 -1)){
					   xw.fillRectangle(i*index, j*index, index, index, 8); 
					 } else {
					   xw.fillRectangle(i*index, j*index, index, index, 4);
				   }
				}
		 }
}



void GraphicsDisplay::notify(Subject<Info, State> & whoNotified){
        
    Info i = whoNotified.getInfo();
		int colour;
		if (i.colour == Colour::Black){
      colour = 1;
		} else if (i.colour == Colour::White){
		  colour = 0;
		} else {
		  colour = 4;
		}
		size_t row = i.row;
		size_t col = i.col;
    
		int index = 500 / gridSize;

		xw.fillRectangle(col*index, row*index, index, index, colour);
    
}





