#include "grid.h"
#include "graphicsdisplay.h"


// dtor
Grid::~Grid(){
   delete td;
	 delete ob;
}


// setObserver
void Grid::setObserver(Observer<Info, State> *ob){
   this->ob = ob;
}


// isFull
bool Grid::isFull() const {
   bool result = true;
	 for(int i = 0; i < dimension; ++i){
      for(int j = 0; j < dimension; ++j){
			   Cell c = theGrid.at(i).at(j);
				 Info i = c.getInfo();
				 if (i.colour == Colour::NoColour){
				     result = false;
				 }
			}
	 }

	 return result;
}

// whoWon
Colour Grid::whoWon() const {
  int b = 0;
	int w = 0;
	for(int i = 0; i < dimension; ++i){
     for(int j = 0; j < dimension; ++j){
       Cell c = theGrid.at(i).at(j);
			 Info i =  c.getInfo();
			 if(i.colour == Colour::Black){
         ++b;
			 } else if (i.colour == Colour::White){
			   ++w;
			 }
		 }
	}

	if (b > w){
    return Colour::Black;
	} else if (w > b){
    return Colour::White;
	} else {
    return Colour::NoColour;
	}
}  


// init
void Grid::init(size_t n){
   dimension = n;
	 
	 // clear the old Grid
	 //for(size_t i = 0; i < n; ++i){
   //  theGrid[i].clear();   
	 //}

   theGrid.clear();

 	 if (td){
	   delete td;
	 }
	 delete ob;

	 ob = new GraphicsDisplay(n);
   
	 // create the new Grid
   for(size_t i = 0; i < n; ++i){
			std::vector<Cell> arr;
			for(size_t j = 0; j < n; ++j){
			   Cell cell = Cell{i,j};
         if ((i == n/2 - 1 && j == n/2 - 1) || (i == n/2 && j == n/2)){
            cell.setPiece(Colour::Black);
				 } 
         if ((i == n/2 - 1 && j == n/2) || (i == n/2 && j == n/2 - 1)){
            cell.setPiece(Colour::White);
				 }

         arr.emplace_back(cell); 
			}
			theGrid.emplace_back(arr);
	 }

	 td = new TextDisplay(dimension);

	 // set observers
   for(size_t i = 0; i < n; ++i){
      for(size_t j = 0; j < n; ++j){
         Cell & cell = theGrid.at(i).at(j);
         
          
				 
				 for(int k = -1; k <= 1; ++k){
            for(int t = -1; t <= 1; ++t){
						   if ((i+k) < 0 || (j+t) < 0) continue;
							 if (k == 0 && t == 0) continue;
               if ((i+k) >= n || (j+t) >= n) continue; 
               Cell & obscell = theGrid.at(i+k).at(j+t);
							 cell.attach(&obscell);
						}
				 }

				 cell.attach(td);
          cell.attach(ob);
			}
	 }
}


 // setPiece
void Grid::setPiece(size_t r, size_t c, Colour colour){
   Cell & cell = theGrid.at(r).at(c);
   Info i = cell.getInfo();

	 if (i.colour != Colour::NoColour){
	   throw InvalidMove{};
	 } else if (r < 0 || c < 0 || r >= theGrid.size() || c >= theGrid.size()) {
	   throw InvalidMove{};
	 } else {
	   cell.setPiece(colour);
	   cell.notify(cell);
   
	   cell.notifyObservers(); // notifies neighbour cells
	   //td->notify(cell); // notifies textdisplay
   }
}


// toggle
void Grid::toggle(size_t r, size_t c){
   Cell & cell = theGrid.at(r).at(c);
	 cell.toggle();
   
   cell.notifyObservers();
	 td->notify(cell);
}

// output operator
std::ostream & operator<< (std::ostream &out, const Grid &g){
    out << *(g.td);
		return out;
}







