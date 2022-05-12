#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	Mygraph = NULL;
	load_flag = FALSE;
	draw_flag = FALSE;
	line_flag = FALSE;
	shortest_flag = FALSE;

	width = ofGetWidth();
	height = ofGetHeight();

	ofSetFrameRate(FRAME);
	ofBackground(240, 255, 255);

}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {
	if (draw_flag == TRUE)
		background.draw(0, 0);

	// Add something for path
	if (shortest_flag == TRUE) {
		Mygraph->draw_dfs(stride_x, stride_y);
	}

	if (line_flag == TRUE) {
		Mygraph->draw_path(stride_x, stride_y);
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if (key == 'd') {
		if (load_flag == FALSE) return;

		draw_flag = TRUE;
		Mygraph->dfs_computation(0);
		Mygraph->dfs_print();
	}
	// Add something for another key
	if (key == 's') {
		if (draw_flag == TRUE) {
			shortest_flag = TRUE;
		}
	}	
	if (key == 'p') {
		if (draw_flag == TRUE) {
			line_flag = TRUE;
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key) {

	if (key == 'l') {
		// Open the Open File Dialog
		if (Mygraph != NULL) {
			delete(Mygraph);
			printf("Deleted previous Mygraph!\n");
			draw_flag = FALSE;
			line_flag = FALSE;
			shortest_flag = FALSE;
		}
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select file generated from MazeGen");

		// Check whether the user opened a file
		if (openFileResult.bSuccess) {
			ofLogVerbose("User selected a file");

			// We have a file, so let's check it and process it
			read_from_file(openFileResult);
			load_flag = TRUE;

		}
	}
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button) {

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y) {

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h) {

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg) {

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo) {

}

void ofApp::set_background()
{
	// set Fbo background!
	background.allocate(width, height);
	background.begin(); // start saving textures into ofFbo
	ofClear(240, 255, 255, 0);

	// First, draw the outer wall of our maze
	ofSetColor(outer_wall);
	ofSetLineWidth(4);

	ofDrawLine(stride_x, stride_y, width - stride_x, stride_y); // line from upper left to upper right
	ofDrawLine(stride_x, stride_y, stride_x, height - stride_y); // line from upper left to bottom left

	ofDrawLine(width - stride_x, height - stride_y, width - stride_x, stride_y); // line from bottom right to upper right
	ofDrawLine(width - stride_x, height - stride_y, stride_x, height - stride_y); // line from bottom right to bottom left

	// Next, fill the maze 
	ofSetColor(inner_wall);
	ofSetLineWidth(3);

	float line_x, line_y;
	int no;

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			if (i == 0 || j == 0 || i == (row - 1) || j == (col - 1)) continue; // ignore the outer_wall line

			line_x = stride_x + (j / 2) * stride_x;
			line_y = stride_y + (i / 2) * stride_y;

			// draw vertical line 
			if ((i % 2) && (j % 2 == 0)) {

				if (maze_construct[i][j] == '|')
					ofDrawLine(line_x, line_y, line_x, line_y + stride_y);

			}

			// draw horizontal line 
			else if ((i % 2 == 0) && (j % 2)) {

				if (maze_construct[i][j] == '-')
					ofDrawLine(line_x, line_y, line_x + stride_x, line_y);
			}

		}

	}
	background.end(); // finish saving textures into ofFbo
}


void ofApp::set_random_color()
{
	// random color for wall 
	outer_wall.set(ofRandom(255), ofRandom(255), ofRandom(255));
	inner_wall.set(ofRandom(255), ofRandom(255), ofRandom(255));

	// random color for path 
	Mygraph->path.set(ofRandom(255), ofRandom(255), ofRandom(255));
	Mygraph->sp.set(ofRandom(255), ofRandom(255), ofRandom(255));

}

void ofApp::read_from_file(ofFileDialogResult openFileResult)
{
	FILE *fp;
	long size;
	char *buf, *ptr;
	size_t result;
	int node_index, k = 0, crlf = 0;

	string fileName = openFileResult.getName();

	fp = fopen(fileName.c_str(), "r"); // convert std::string to const char *

	// get file size 
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);

	// malloc buf *
	buf = (char *)malloc(sizeof(char) * size);

	result = fread(buf, 1, size, fp);

	// To determine the size of row and col 
	for (int i = 0; i < result; i++) {
		if (buf[i] == '\n') {
			if (crlf == 0)
				col_num = (i - 1) / 2;

			crlf++;
		}
	}
	row_num = (crlf - 1) / 2;

	// initialize graph data structure 
	Mygraph = new graph(row_num, col_num);
	Mygraph->node_num = row_num * col_num;

	set_random_color(); // set random color each time..

	// set uniform distance for visibility 
	stride_x = (float)width / (float)(col_num + 2);
	stride_y = (float)height / (float)(row_num + 2);

	row = row_num * 2 + 1; // index for maze_construct
	col = col_num * 2 + 1;

	maze_construct = (char **)malloc(sizeof(char*)*(row));

	for (int i = 0; i < row; i++)
		maze_construct[i] = (char*)malloc(sizeof(char)*(col));

	// use strtok to ignore crlf at buf 
	ptr = strtok(buf, "\r\n");

	while (ptr != NULL)
	{
		printf("%s\n", ptr);
		strcpy(maze_construct[k], ptr);
		ptr = strtok(NULL, "\r\n");
		k++;
		if (k > row_num * 2) break;
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {

			// connect horizontal rooms 
			if ((i % 2) && (j % 2 == 0)) {
				node_index = (i / 2) * col_num + (j / 2 - 1); // node_index for horizontal connection

				if (maze_construct[i][j] == ' ') {
					Mygraph->put_edge(node_index, node_index + 1);
				}
			}

			// connect vertical rooms 
			else if ((i % 2 == 0) && (j % 2)) {
				node_index = (i / 2 - 1) * col_num + (j / 2); // node_index for vertical connection

				if (maze_construct[i][j] == ' ') {
					Mygraph->put_edge(node_index, node_index + col_num);
				}

			}
		}

	}

	set_background();

	//Mygraph->print_adj();

	printf("set background completed!\n");

	fclose(fp);
	free(buf);
}