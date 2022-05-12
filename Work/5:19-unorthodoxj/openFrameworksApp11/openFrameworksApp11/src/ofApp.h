#pragma once

#include "ofMain.h"
#include "graph.h"


#define FRAME 20

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y);
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void mouseEntered(int x, int y);
	void mouseExited(int x, int y);
	void windowResized(int w, int h);
	void dragEvent(ofDragInfo dragInfo);
	void gotMessage(ofMessage msg);

	// newly added
	void set_background();
	void set_random_color();
	void read_from_file(ofFileDialogResult openFileResult);

	ofColor outer_wall;
	ofColor inner_wall;

	ofFbo background; // to draw maze input

	bool draw_flag; // 'd'
	bool load_flag; // 'l'
	bool shortest_flag; // 's'
	bool line_flag; // 'p'

	int width;
	int height;
	int row, col, row_num, col_num; // row, col: index to access the string, *_num: actual value of row, col
	float stride_x; // uniform horizontal distance
	float stride_y; // uniform vertical distance

	char **maze_construct;
	graph *Mygraph;

};