/*

	ofxWinMenu basic example - ofApp.cpp

	Example of using ofxWinMenu addon to create a menu for a Microsoft Windows application.
	
	Copyright (C) 2016-2017 Lynn Jarvis.

	https://github.com/leadedge

	http://www.spout.zeal.co

    =========================================================================
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    =========================================================================

	03.11.16 - minor comment cleanup
	21.02.17 - rebuild for OF 0.9.8

*/
#include "ofApp.h"
#include <iostream>
using namespace std;

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("Maze Example"); // Set the app name on the title bar
	ofSetFrameRate(15);
	ofBackground(255, 255, 255);
	// Get the window size for image loading
	windowWidth = ofGetWidth();
	windowHeight = ofGetHeight();
	isdfs = false;
	isBFS = false;
	isOpen = 0;
	// Centre on the screen
	ofSetWindowPosition((ofGetScreenWidth()-windowWidth)/2, (ofGetScreenHeight()-windowHeight)/2);

	// Load a font rather than the default
	myFont.loadFont("verdana.ttf", 12, true, true);

	// Load an image for the example
	//myImage.loadImage("lighthouse.jpg");

	// Window handle used for topmost function
	hWnd = WindowFromDC(wglGetCurrentDC());

	// Disable escape key exit so we can exit fullscreen with Escape (see keyPressed)
	ofSetEscapeQuitsApp(false);

	//
	// Create a menu using ofxWinMenu
	//

	// A new menu object with a pointer to this class
	menu = new ofxWinMenu(this, hWnd);

	// Register an ofApp function that is called when a menu item is selected.
	// The function can be called anything but must exist. 
	// See the example "appMenuFunction".
	menu->CreateMenuFunction(&ofApp::appMenuFunction);

	// Create a window menu
	HMENU hMenu = menu->CreateWindowMenu();

	//
	// Create a "File" popup menu
	//
	HMENU hPopup = menu->AddPopupMenu(hMenu, "File");

	//
	// Add popup items to the File menu
	//

	// Open an maze file
	menu->AddPopupItem(hPopup, "Open", false, false); // Not checked and not auto-checked
	
	// Final File popup menu item is "Exit" - add a separator before it
	menu->AddPopupSeparator(hPopup);
	menu->AddPopupItem(hPopup, "Exit", false, false);

	//
	// View popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "View");

	bShowInfo = true;  // screen info display on
	menu->AddPopupItem(hPopup, "Show DFS",false,false); // Checked
	bTopmost = false; // app is topmost
	menu->AddPopupItem(hPopup, "Show BFS"); // Not checked (default)
	bFullscreen = false; // not fullscreen yet
	menu->AddPopupItem(hPopup, "Full screen", false, false); // Not checked and not auto-check

	//
	// Help popup menu
	//
	hPopup = menu->AddPopupMenu(hMenu, "Help");
	menu->AddPopupItem(hPopup, "About", false, false); // No auto check

	// Set the menu to the window
	menu->SetWindowMenu();

} // end Setup


//
// Menu function
//
// This function is called by ofxWinMenu when an item is selected.
// The the title and state can be checked for required action.
// 
void ofApp::appMenuFunction(string title, bool bChecked) {

	ofFileDialogResult result;
	string filePath;
	size_t pos;

	//
	// File menu
	//
	if(title == "Open") {
		readFile();
	}
	if(title == "Exit") {
		ofExit(); // Quit the application
	}

	//
	// Window menu
	//
	if(title == "Show DFS") {
		bShowInfo = bChecked;  // Flag is used elsewhere in Draw()
		if (isOpen)
		{
			DFS();
			isdfs = true;
		}
		else
			cout << "you must open file first" << endl;
		
	}

	if(title == "Show BFS") {
		bShowInfo = bChecked;
		// doTopmost(bChecked); // Use the checked value directly
		if (isOpen) {
			BFS();
			isbfs = true;
		}
		else
			cout << "you must open file first" << endl;

	}

	if(title == "Full screen") {
		bFullscreen = !bFullscreen; // Not auto-checked and also used in the keyPressed function
		doFullScreen(bFullscreen); // But als take action immediately
	}

	//
	// Help menu
	//
	if(title == "About") {
		ofSystemAlertDialog("ofxWinMenu\nbasic example\n\nhttp://spout.zeal.co");
	}

} // end appMenuFunction


//--------------------------------------------------------------
void ofApp::update() {
}


//--------------------------------------------------------------
void ofApp::draw() {

	char str[256];
	//ofBackground(0, 0, 0, 0);
	ofSetColor(100);
	ofSetLineWidth(5);
    int i, j;
    
	// TO DO : DRAW MAZE; 
	// 저장된 자료구조를 이용해 미로를 그린다.
	// add code here
	size = (double)ofGetHeight() / (double)(widthWall * (HEIGHT - (HEIGHT) / 2) + heightWall * ((HEIGHT) / 2));

	ofSetColor(ofColor::black);

	for (i = 0; i < HEIGHT; i++) {
		float y = size * (widthWall * (i - i/2) + heightWall * (i / 2));
		for (j = 0; j < WIDTH; j++) {
			float x = size * (widthWall * (j - j/2) + heightWall * (j / 2));
			if (maze[i][j] == '+')
				ofDrawRectangle(x, y, widthWall * size, widthWall * size);
            else if (maze[i][j] == '|')
                ofDrawRectangle(x, y, widthWall * size, heightWall * size);
			else if(maze[i][j] == '-')
				ofDrawRectangle(x, y, heightWall * size, widthWall * size);
		}
	}

	if (isdfs)
	{
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen)
			dfsdraw();
		else
			cout << "You must open file first" << endl;
	}

	if (isBFS) {
		ofSetColor(200);
		ofSetLineWidth(5);
		if (isOpen)
            bfsdraw();
		else
			cout << "You must open file first" << endl;
	}

	if(bShowInfo) {
		// Show keyboard duplicates of menu functions
		sprintf(str, " comsil project");
		myFont.drawString(str, 15, ofGetHeight()-20);
	}

} // end Draw


void ofApp::doFullScreen(bool bFull)
{
	// Enter full screen
	if(bFull) {
		// Remove the menu but don't destroy it
		menu->RemoveWindowMenu();
		// hide the cursor
		ofHideCursor();
		// Set full screen
		ofSetFullscreen(true);
	}
	else { 
		// return from full screen
		ofSetFullscreen(false);
		// Restore the menu
		menu->SetWindowMenu();
		// Restore the window size allowing for the menu
		ofSetWindowShape(windowWidth, windowHeight + GetSystemMetrics(SM_CYMENU)); 
		// Centre on the screen
		ofSetWindowPosition((ofGetScreenWidth()-ofGetWidth())/2, (ofGetScreenHeight()-ofGetHeight())/2);
		// Show the cursor again
		ofShowCursor();
		// Restore topmost state
		if(bTopmost) doTopmost(true);
	}

} // end doFullScreen


void ofApp::doTopmost(bool bTop)
{
	if(bTop) {
		// get the current top window for return
		hWndForeground = GetForegroundWindow();
		// Set this window topmost
		SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		ShowWindow(hWnd, SW_SHOW);
	}
	else {
		SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
		ShowWindow(hWnd, SW_SHOW);
		// Reset the window that was topmost before
		if(GetWindowLong(hWndForeground, GWL_EXSTYLE) & WS_EX_TOPMOST)
			SetWindowPos(hWndForeground, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
		else
			SetWindowPos(hWndForeground, HWND_TOP, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE); 
	}
} // end doTopmost


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	
	// Escape key exit has been disabled but it can be checked here
	if(key == VK_ESCAPE) {
		// Disable fullscreen set, otherwise quit the application as usual
		if(bFullscreen) {
			bFullscreen = false;
			doFullScreen(false);
		}
		else {
			ofExit();
		}
	}

	// Remove or show screen info
	if(key == ' ') {
		bShowInfo = !bShowInfo;
		// Update the menu check check because the item state has been changed here
		menu->SetPopupItem("Show DFS", bShowInfo);
	}

	if(key == 'f') {
		bFullscreen = !bFullscreen;	
		doFullScreen(bFullscreen);
		// Do not check this menu item
		// If there is no menu when you call the SetPopupItem function it will crash
	}

} // end keyPressed

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
bool ofApp::readFile(){
	ofFileDialogResult openFileResult = ofSystemLoadDialog("Select .maz file");
	string filePath;
	size_t pos;
	// Check whether the user opened a file
	if (openFileResult.bSuccess) {
		ofLogVerbose("User selected a file");

		//We have a file, check it and process it
		string fileName = openFileResult.getName();
		//string fileName = "maze0.maz";
		printf("file name is %s\n", fileName);
		filePath = openFileResult.getPath();
		printf("Open\n");
		pos = filePath.find_last_of(".");
		if (pos != string::npos && pos != 0 && filePath.substr(pos + 1) == "maz") {

			ofFile file(fileName);

			if (!file.exists()) {
				cout << "Target file does not exists." << endl;
				return false;
			}
			else {
				cout << "We found the target file." << endl;
				isOpen = 1;
			}

			ofBuffer buffer(file);

			// Input_flag is a variable for indication the type of input.
			// If input_flag is zero, then work of line input is progress.
			// If input_flag is one, then work of dot input is progress.
			int input_flag = 0;

			// Idx is a variable for index of array.
			int idx = 0;

			// Read file line by line
			int cnt = 0;


			// TO DO
			// .maz 파일을 input으로 받아서 적절히 자료구조에 넣는다
			if (buffer.size())
				for (auto line : buffer.getLines())
                    maze.push_back(line);

            WIDTH = maze[0].size();
			HEIGHT = maze.size();
			
			check.resize(HEIGHT);
			visited.resize(HEIGHT);
			path.resize(HEIGHT);

		}
		else {
			printf("  Needs a '.maz' extension\n");
			return false;
		}
	}
}
void ofApp::freeMemory() {

	//TO DO
	// malloc한 memory를 free해주는 함수
	maze.clear();
    check.clear();
    visited.clear();
    path.clear();
    
    maze.shrink_to_fit();
	check.shrink_to_fit();
	visited.shrink_to_fit();
	path.shrink_to_fit();
}

bool ofApp::DFS()//DFS탐색을 하는 함수
{
	//TO DO
	//DFS탐색을 하는 함수 ( 3주차)
	dX = WIDTH - 2;
	dY = HEIGHT - 2;
    
	bool flag= false;
	int x, y;
	int X, Y;
	int mX, mY;
	
	stack< pair<int, int>> stack;
	vector<vector<pair<int, int>>> route(HEIGHT);

	for (int i = 0; i < HEIGHT; i++) {
        route[i].resize(WIDTH);
		check[i].resize(WIDTH);
        visited[i].resize(WIDTH);
        path[i].resize(WIDTH);
		
        fill(check[i].begin(), check[i].end(), false);
        fill(visited[i].begin(), visited[i].end(), false);
        fill(path[i].begin(), path[i].end(), false);
	}

    stack.push({ 1, 1 });
	visited[1][1] = true;
    
	while (stack.size() && !flag) {
        x = stack.top().second;
        y = stack.top().first;
		
		check[y][x] = true;
        stack.pop();

		for (int d = 0; d < 4; d++) {
            X = x + dir[d][0];
            Y = y + dir[d][1];

			if (visited[Y][X])
				continue;
			if (f[Y][X] != ' ')
				continue;

			visited[Y][X] = true;
			stack.push({ Y, X });
			route[Y][X] = { y, x };

			if (Y == dY && X == dX) {
				flag = true;
				break;
			}
		}
	}

	if (flag) {
		y = dY;
		x = dX;
		path[y][x] = true;

		while (y != 1 || x != 1) {
			mY = route[y][x].first;
			mX = route[y][x].second;
			path[mY][mX] = true;
			y = mY;
			x = mX;
		}
	}
	route.clear();
	route.shrink_to_fit();

	return true;
}

bool ofApp::BFS(){
	dX = WIDTH - 2;
	dY = HEIGHT - 2;
    
	bool flag = false;
	int x, y;
	int X, Y;
	int mX, mY;

	queue< pair<int, int>> queue;
	vector<vector<pair<int, int>>> route(HEIGHT);
    
    for (int i = 0; i < HEIGHT; i++) {
		route[i].resize(WIDTH);
        check[i].resize(WIDTH);
        visited[i].resize(WIDTH);
        path[i].resize(WIDTH);
        
        fill(check[i].begin(), check[i].end(), false);
        fill(visited[i].begin(), check[i].end(), false);
        fill(path[i].begin(), check[i].end(), false);
    }


    queue.push({ 1, 1 });
	visited[1][1] = true;
    
	while (queue.size() && !flag) {
        x = queue.front().second;
        y = queue.front().first;
		
		check[y][x] = true;
		queue.pop();

		for (int d = 0; d < 4; d++) {
            X = x + dir[d][0];
            Y = y + dir[d][1];
			

			if (visited[Y][X]) continue;
			if (maze[Y][X] != ' ') continue;

			visited[Y][X] = true;
			queue.push({ Y, X });
			route[Y][X] = { y, x };

			if (X == dX && Y == dY) {
				flag = true;
				break;
			}
		}
	}

	if (flag) {
		x = dX;
		y = dY;
		path[y][x] = true;

		while (x != 1 || y != 1) {
			mX = route[y][x].second;
			mY = route[y][x].first;
			path[mY][mX] = true;
			x = mX, y = mY;
		}
	}

	route.clear();
	route.shrink_to_fit();
    
	return 0;
}

void ofApp::dfsdraw(){
    //TO DO
    //DFS를 수행한 결과를 그린다. (3주차 내용)
    ofSetColor(ofColor::gray);
    for (int i = 0; i < HEIGHT; i++) {
        float y = size * (heightWall * (i / 2) + widthWall * (i - i / 2) +
            (float)heightWall / 2 - (float)widthWall / 2);
        for (int j = 0; j < WIDTH; j++) {
            float x = size * (heightWall * (j / 2) + widthWall * (j - j / 2) +
                (float)heightWall / 2 - (float)widthWall / 2);
            if (check[i][j]) {
                if ((i % 2) && (j % 2))
                    ofDrawRectangle(x, y, widthWall * size, widthWall * size);
                else if (i % 2)
                    ofDrawRectangle(x - heightWall * size + widthWall * size, y, heightWall * size, widthWall * size);
                else
                    ofDrawRectangle(x, y - heightWall * size + widthWall * size, widthWall * size, heightWall * size);
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        float y = size * (heightWall * (i / 2) + widthWall * (i - i / 2) +
            (float)heightWall / 2 - (float)widthWall / 2);
        for (int j = 0; j < WIDTH; j++) {
            float x = size * (heightWall * (j / 2) + widthWall * (j - j / 2) +
                (float)heightWall / 2 - (float)widthWall / 2);
            if (path[i][j]) {
                ofSetColor(ofColor::red);
                if ((i == 1 && j == 1) || (i == dY && j == dX))
                    ofSetColor(ofColor::green);
                if ((i % 2) && (j % 2))
                    ofDrawRectangle(x, y, widthWall * size, widthWall * size);
                else if (i % 2)
                    ofDrawRectangle(x - heightWall * size + widthWall * size, y, heightWall * size, widthWall * size);
                else
                    ofDrawRectangle(x, y - heightWall * size + widthWall * size, widthWall * size, heightWall * size);
            }
        }
    }
}

void ofApp::bfsdraw(){
    ofSetColor(ofColor::gray);
    for (int i = 0; i < HEIGHT; i++) {
        float y = size * (widthWall * (i - i / 2) + heightWall * (i / 2) + (float)heightWall / 2 - (float)widthWall / 2);
        for (int j = 0; j < WIDTH; j++) {
            float x = size * (widthWall * (j - j / 2) + heightWall * (j / 2) + (float)heightWall / 2 - (float)widthWall / 2);
            if (check[i][j]) {
                if ((i % 2) && (j % 2))
                    ofDrawRectangle(x, y, widthWall * size, widthWall * size);
                else if (i % 2)
                    ofDrawRectangle(x - heightWall * size + widthWall * size, y, heightWall * size, widthWall * size);
                else
                    ofDrawRectangle(x, y - heightWall * size + widthWall * size, widthWall * size, heightWall * size);
            }
        }
    }

    for (int i = 0; i < HEIGHT; i++) {
        float y = size * (widthWall * (i - i / 2) + heightWall * (i / 2) + (float)heightWall / 2 - (float)widthWall / 2);
        for (int j = 0; j < WIDTH; j++) {
            float x = size * (widthWall * (j - j / 2) + heightWall * (j / 2) + (float)heightWall / 2 - (float)widthWall / 2);
            if (path[i][j]) {
                ofSetColor(ofColor::red);
                if ((i == 1 && j == 1) || (i == dY && j == dX))
                    ofSetColor(ofColor::green);
                if ((i % 2) && (j % 2))
                    ofDrawRectangle(x, y, widthWall * size, widthWall * size);
                else if (i % 2)
                    ofDrawRectangle(x - heightWall * size + widthWall * size, y, heightWall * size, widthWall * size);
                else
                    ofDrawRectangle(x, y - heightWall * size + widthWall * size, widthWall * size, heightWall * size);
            }
        }
    }
}

