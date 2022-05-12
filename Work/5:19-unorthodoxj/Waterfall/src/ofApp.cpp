#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetFrameRate(15); // Limit the speed of our program to 15 frames per second
    
    // We still want to draw on a black background, so we need to draw
    // the background before we do anything with the brush
    ofBackground(255,255,255);
    ofSetLineWidth(4);
    
    draw_flag = 0;
    load_flag = 0;
    dot_diameter = 20.0f;
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(127,23,31);  // Set the drawing color to brown
    
    // Draw shapes for ceiling and floor
    ofDrawRectangle(0, 0, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofDrawRectangle(0, 728, 1024, 40); // Top left corner at (50, 50), 100 wide x 100 high
    ofSetLineWidth(5);
    
    
    ofSetLineWidth(5);
    if( draw_flag ){
        
        
        /* COMSIL1-TODO 3 : Draw the line segment and dot in which water starts to flow in the screen.
         Note that after drawing line segment and dot, you have to make selected water start dot colored in red.
         */

		for (int i = 0; i < num_of_line; i++) {
			ofDrawLine(l[i].x1, l[i].y1, l[i].x2, l[i].y2);
		}

		for (int i = 0; i < num_of_dot; i++) {
			if (d[i].r)
				ofSetColor(ofColor::red);
			else
				ofSetColor(ofColor::black);
			ofDrawCircle(d[i].x1, d[i].y1, dot_diameter / 2);
		}

        // 2nd week portion.
        ofSetLineWidth(2);
		if (draw_sub_flag) {
			if (!wl.cal_flag)
				wl.computation();
			wl.draw();
		}
    }
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'v') {
        // HACK: only needed on windows, when using ofSetAutoBackground(false)
        glReadBuffer(GL_FRONT);
        ofSaveScreen("savedScreenshot_"+ofGetTimestampString()+".png");
    }
    if (key == 'q'){
        // Reset flags
        draw_flag = 0;
        
        // Free the dynamically allocated memory exits.
		delete[] d;
		delete[] l;

        cout << "Dynamically allocated memory has been freed." << endl;
        
        _Exit(0);
    }
    if (key == 'd'){
        if( !load_flag) return;
		draw_flag = 1;
        /* COMSIL1-TODO 2: This is draw control part.
        You should draw only after when the key 'd' has been pressed.
        */
    }
    if (key == 's'){
        // 2nd week portion.
		draw_sub_flag = 1;
    }
    if (key == 'e'){
        // 2nd week portion.
		draw_sub_flag = 0;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    if( key == 'l'){
        // Open the Open File Dialog
        ofFileDialogResult openFileResult= ofSystemLoadDialog("Select a only txt for Waterfall");
        
        // Check whether the user opened a file
        if( openFileResult.bSuccess){
            ofLogVerbose("User selected a file");
            
            // We have a file, so let's check it and process it
            processOpenFileSelection(openFileResult);
            load_flag = 1;
        }
    }
    
    /* COMSIL1-TODO 4: This is selection dot control part.
     You can select dot in which water starts to flow by left, right direction key (<- , ->).
     */
    if (key == OF_KEY_RIGHT){
		prev = cur;
		if (cur == num_of_dot - 1)
			cur = 0;
		else
			cur++;

		d[cur].r = 1;
		d[prev].r = 0;
		nowDot = cur;

		cout << "Selcted Dot Coordinate is (" << d[cur].x1 << ", " << d[cur].y1 << ")" << endl;
    }
    if (key == OF_KEY_LEFT){
		prev = cur;
		if (cur == 0)
			cur = num_of_dot - 1;
		else
			cur--;

		d[cur].r = 1;
		d[prev].r = 0;
		nowDot = cur;

        cout << "Selcted Dot Coordinate is (" << d[cur].x1 << ", " << d[cur].y1 << ")" << endl;
    }
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

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
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

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

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) { 
    //Path to the comma delimited file
    //string fileName = "input.txt";
    
    string fileName = openFileResult.getName();
    ofFile file(fileName);
    
    if( !file.exists()) cout << "Target file does not exists." << endl;
    else cout << "We found the target file." << endl;
    
    ofBuffer buffer(file);
    /* This variable is for indicating which type of input is being received.
     IF input_type == 0, then work of getting line input is in progress.
     IF input_type == 1, then work of getting dot input is in progress.
     */
    int input_type = 0;
	int lcnt = 0;
	int dcnt = 0;
	int width = ofGetScreenWidth();
	int height = ofGetScreenHeight();
    
    
    /* COMSIL1-TODO 1 : Below code is for getting the number of line and dot, getting coordinates.
     You must maintain those information. But, currently below code is not complete.
     Also, note that all of coordinate should not be out of screen size.
     However, all of coordinate do not always turn out to be the case.
     So, You have to develop some error handling code that can detect whether coordinate is out of screen size.
    */
 
    
    // Read file line by line
    for (ofBuffer::Line it = buffer.getLines().begin(), end = buffer.getLines().end(); it != end; ++it) {
        string line = *it;
        
        // Split line into strings
        vector<string> words = ofSplitString(line, " ");
        
        if( words.size() == 1){
            if( input_type == 0){ // Input for the number of lines.
                num_of_line = atoi(words[0].c_str());
                cout << "The number of line is: " << num_of_line << endl;
				l = new ln[num_of_line];
            }
            else{ // Input for the number of dots.
                num_of_dot = atoi(words[0].c_str());
                cout << "The number of dot is: " << num_of_dot << endl;
				d = new dt[num_of_dot];
            }
        }
        else if (words.size() >= 2){
            int x1,y1,x2,y2;
            if( input_type == 0){ // Input for actual information of lines
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
                x2 = atoi(words[2].c_str());
                y2 = atoi(words[3].c_str());
				if (x1 < 0 || x2 < 0 || x1 > width || x2 > width) {
					cout << "Out of Screen error!" << endl;
					return;
				}
				if (y1 < 0 || y2 < 0 || y1 > height || y2 > height) {
					cout << "Out of Screen error!" << endl;
					return;
				}
				l[lcnt].x1 = x1;
				l[lcnt].x2 = x2;
				l[lcnt].y1 = y1;
				l[lcnt].y2 = y2;
				lcnt++;
				if (lcnt == num_of_line)
					input_type = 1;
            }
            else{ // Input for actual information of dots.
                x1 = atoi(words[0].c_str());
                y1 = atoi(words[1].c_str());
				if (x1 < 0 || x1 > width) {
					cout << "Out of Screen error!" << endl;
					return;
				}
				if (y1 < 0 || y1 >height) {
					cout << "Out of Screen error!" << endl;
					return;
				}
				d[dcnt].x1 = x1;
				d[dcnt].y1 = y1;
				dcnt++;
            }
        } // End of else if.
    } // End of for-loop (Read file line by line).
    
    initializeWaterLines();
}

void ofApp::initializeWaterLines() {
	int num = 50;
	int lx, ly;
	wl.assign(num, waterObj(num_of_line));

	lx = d[nowDot].x1;
	ly = d[nowDot].y1;

	for (int i = 0; i < num; i++) {
		wl[i].tx = lx;
		wl[i].ty = ly;
		wl[i].path[0].x = lx;
		wl[i].path[0].y = ly;
	}
}