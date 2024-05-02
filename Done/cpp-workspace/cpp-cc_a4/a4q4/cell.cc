#include "cell.h"

// ctor
Cell::Cell(size_t r, size_t c): r{r}, c{c}{}

// methods

void Cell::setPiece(Colour colour){
   this->colour = colour;
}

void Cell::toggle(){
   if (colour == Colour::Black){
      colour = Colour::White;
	 } else if (colour == Colour::White){
      colour = Colour::Black;
	 }
}

void Cell::notify(Subject<Info, State> &whoFrom){
   Info i = whoFrom.getInfo();
	 State olds = whoFrom.getState();

   if (colour == Colour::NoColour){
     return;
   }

	 if (this == &whoFrom){


      // change current state
      State news = State{StateType::NewPiece, i.colour};
      setState(news);


	 } else if(olds.type == StateType::NewPiece)  {
   
	 // NewPiece
		 
		 if(i.row == r - 1 && i.col == c && colour != i.colour){
        // N
				State s = State{StateType::Relay, colour, Direction::N};
				setState(s);
		 } else if (i.row == r - 1 && i.col == c - 1 && colour != i.colour){
        // NW
				State s = State{StateType::Relay, colour, Direction::NW};
				setState(s);
		 } else if (i.row == r - 1 && i.col == c + 1 && colour != i.colour){
        // NE
				State s = State{StateType::Relay, colour, Direction::NE};
				setState(s);
		 } else if (i.row == r && i.col == c - 1 && colour != i.colour){
		    // W
				State s = State{StateType::Relay, colour, Direction::W};
				setState(s);
		 } else if (i.row == r && i.col == c + 1 && colour != i.colour){
		    // E
				State s = State{StateType::Relay, colour, Direction::E};
				setState(s);
		 } else if (i.row == r + 1 && i.col == c && colour != i.colour){
		    // S
				State s = State{StateType::Relay, colour, Direction::S};
				setState(s);
		 } else if (i.row == r + 1 && i.col == c - 1 && colour != i.colour){
				// SW
				State s = State{StateType::Relay, colour, Direction::SW};
				setState(s);
		 } else if (i.row == r + 1 && i.col == c + 1 && colour != i.colour){
				// SE
				State s = State{StateType::Relay, colour, Direction::SE};
				setState(s);
		 }
     

		 // continue to notify the observers
 		 if (colour != Colour::NoColour && colour != i.colour){
		    notifyObservers();
		 }


   } else if (olds.type == StateType::Relay){
   
	 // Relay
		 
		 if(i.row == r - 1 && i.col == c && olds.direction == Direction::N){
        
				if (colour == i.colour){
				  
					// Continue to relay (N)
				  State s = State{StateType::Relay, colour, Direction::N};
				  setState(s);
        } else {
				  
					// reply
          State s = State{StateType::Reply, colour, Direction::N};
				  setState(s);
				}

				notifyObservers();
 
		 } else if (i.row == r - 1 && i.col == c - 1 && olds.direction == Direction::NW){
        
				if (colour == i.colour){
				  
					// Continue to relay (NW)
				  State s = State{StateType::Relay, colour, Direction::NW};
				  setState(s);
				} else {
          
					// reply
					State s = State{StateType::Reply, colour, Direction::NW};
					setState(s);
				}

				notifyObservers();

		 } else if (i.row == r - 1 && i.col == c + 1 && olds.direction == Direction::NE){
        
				if (colour == i.colour){
				  
					// Continue to relay (NE)
				  State s = State{StateType::Relay, colour, Direction::NE};
				  setState(s);
				} else {
          
					// reply
					State s = State{StateType::Reply, colour, Direction::NE};
					setState(s);
				}

				notifyObservers();

		 } else if (i.row == r && i.col == c - 1 && olds.direction == Direction::W){
		    if (colour == i.colour){
					
					// Continue to relay (W)
				  State s = State{StateType::Relay, colour, Direction::W};
				  setState(s);
				} else {
				  
					// reply
					State s = State{StateType::Reply, colour, Direction::W};
				  setState(s);
				}

				notifyObservers();

		 } else if (i.row == r && i.col == c + 1 && olds.direction == Direction::E){
		    
				if (colour == i.colour){
			 	  
					// Continue to relay (E)
				  State s = State{StateType::Relay, colour, Direction::E};
				  setState(s);
				} else {

				  // reply
				  State s = State{StateType::Reply, colour, Direction::E};
				  setState(s);
				}

				notifyObservers();

		 } else if (i.row == r + 1 && i.col == c && olds.direction == Direction::S){
		    
				if (colour == i.colour){
				  
					// Continue to relay (S)
				  State s = State{StateType::Relay, colour, Direction::S};
				  setState(s);
				} else {

				  // reply
				  State s = State{StateType::Reply, colour, Direction::S};
					setState(s);
				}

				notifyObservers();

		 } else if (i.row == r + 1 && i.col == c - 1 && olds.direction == Direction::SW){
				
				if (colour == i.colour){
				  
					// Continue to relay (SW)
				  State s = State{StateType::Relay, colour, Direction::SW};
				  setState(s);
				} else {
				  
					// reply
					State s = State{StateType::Reply, colour, Direction::SW};
					setState(s);
				}

				notifyObservers();

		 } else if (i.row == r + 1 && i.col == c + 1 && olds.direction == Direction::SE){
				
				if (colour == i.colour){
				  
					// Continue to relay (SE)
				  State s = State{StateType::Relay, colour, Direction::SE};
				  setState(s);
				} else {
				  
					// reply
					State s = State{StateType::Reply, colour, Direction::SE};
					setState(s);
				}

				notifyObservers();

		 }
	   
	 
	 } else if (olds.type == StateType::Reply){
   
	 // Reply

		 State mystate = getState();

		 if(i.row == r + 1 && i.col == c && olds.direction == Direction::N && colour != i.colour){
        
        State s = State{StateType::Reply, i.colour, mystate.direction};
				setState(s);  // change my state
			  toggle();  // toggle my colour

				notifyObservers();
 
		 } else if (i.row == r + 1 && i.col == c + 1 && olds.direction == Direction::NW &&
		            colour != i.colour){
        
        State s = State{StateType::Reply, i.colour, mystate.direction};
				setState(s);  // change my state
			  toggle();  // toggle my colour

				notifyObservers();

		 } else if (i.row == r + 1 && i.col == c - 1 && olds.direction == Direction::NE &&
		            colour != i.colour){
        
        State s = State{StateType::Reply, i.colour, mystate.direction};
				setState(s);  // change my state
			  toggle();  // toggle my colour

				notifyObservers();

		 } else if (i.row == r && i.col == c + 1 && olds.direction == Direction::W &&
		            colour != i.colour){

        State s = State{StateType::Reply, i.colour, mystate.direction};
				setState(s);  // change my state
			  toggle();  // toggle my colour
				notifyObservers();

		 } else if (i.row == r && i.col == c - 1 && olds.direction == Direction::E &&
		            colour != i.colour){
		    
        State s = State{StateType::Reply, i.colour, mystate.direction};
				setState(s);  // change my state
			  toggle();  // toggle my colour
				notifyObservers();

		 } else if (i.row == r - 1 && i.col == c && olds.direction == Direction::S &&
		            colour != i.colour){
		    
        State s = State{StateType::Reply, i.colour, mystate.direction};
				setState(s);  // change my state
			  toggle();  // toggle my colour

				notifyObservers();

		 } else if (i.row == r - 1 && i.col == c + 1 && olds.direction == Direction::SW &&
		            colour != i.colour){
				
        State s = State{StateType::Reply, i.colour, mystate.direction};
				setState(s);  // change my state
			  toggle();  // toggle my colour

				notifyObservers();

		 } else if (i.row == r - 1 && i.col == c - 1 && olds.direction == Direction::SE && 
		            colour != i.colour){
				
        State s = State{StateType::Reply, i.colour, mystate.direction};
				setState(s);  // change my state
			  toggle();  // toggle my colour

				notifyObservers();

		 }
/*

		 if (mystate.direction == olds.direction && colour != i.colour){
        
        State s = State{StateType::Reply, colour, mystate.direction};
				setState(s);  // change my state
			  toggle();  // toggle my colour
				notifyObservers();  // notify my observers
		 }*/


	 }
}

Info Cell::getInfo() const {
  return Info{r,c,colour};
}




