#ifndef _GD_
#define _GD_
#include "observer.h"
#include "state.h"
#include "subject.h"
#include "window.h"
#include "info.h"

class GraphicsDisplay : public Observer<Info, State>{
    Xwindow xw;
		const int gridSize;
  public:
	  GraphicsDisplay(int gridSize);

		void notify(Subject<Info, State> & whoNotified) override;
};




#endif
