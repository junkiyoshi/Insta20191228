#pragma once
#include "ofMain.h"

// Leap Motion SDK
#include "Leap.h"
#pragma comment(lib, "Leap.lib")

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void mouseEntered(int x, int y) {};
	void mouseExited(int x, int y) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	// Leap Motion
	Leap::Controller leap;
	ofEasyCam cam;
	vector<glm::vec3> location_list;
	vector<glm::vec3> velocity_list;
};