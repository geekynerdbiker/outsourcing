#include "waterObj.h"

waterObj::waterObj(int num_of_line)
{
	int num_of_path = num_of_line * 2 + 2;
	if (!path) {
		path = new coordinate[num_of_path ];
		for (int i = 0; i < num_of_path; i++)
			path[i].x = path[i].y = 0;
	}
}

waterObj::~waterObj()
{
	if (path)
		delete[] path;
}

void waterObj::draw()
{
	float r, g, b;
	r = ofRandom(0, 100);
	g = ofRandom(0, 100);
	b = ofRandom(185, 255);
	ofSetColor(r, g, b);

	if (cal_flag) {
		for (int i = 0; i < num_of_path - 1; i++) {
			ofDrawLine(path[i].x, path[i].y, path[i + 1].x, path[i + 1].y);
		}
		end_draw = 1;
	}
}

void waterObj::computation()
{
	cal_flag = 1;
}
