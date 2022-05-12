#pragma once

#include "ofmain.h"
#define EPSILON 0.01

typedef struct _COR {
	int x, y;
}coordinate;

class waterObj {
	public:
		waterObj(int num_of_line);
		~waterObj();
		void draw();
		void computation();

		int tx, ty;
		int cal_flag = 0;
		int end_draw = 0;

		coordinate *path;
		int num_of_path;
};