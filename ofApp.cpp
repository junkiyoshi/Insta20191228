#include "ofApp.h"	

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	Leap::Frame frame = this->leap.frame();
	for (Leap::Hand hand : frame.hands()) {

		auto velocity = glm::vec3(hand.palmVelocity().x * -1, hand.palmVelocity().y * -1, hand.palmVelocity().z);
		auto location = glm::vec3(
				ofMap(hand.palmPosition().x, -300, 300, -ofGetWidth() * 0.5, ofGetWidth() * 0.5),
				ofMap(hand.palmPosition().y, 0, 300, -ofGetHeight() * 0.5, ofGetHeight() * 0.5),
				hand.palmPosition().z);

		auto future = location + velocity * 100;
		auto random_deg_1 = ofRandom(360);
		auto random_deg_2 = ofRandom(360);
		future += glm::vec3(
			100 * cos(random_deg_1 * DEG_TO_RAD) * sin(random_deg_2 * DEG_TO_RAD),
			100 * sin(random_deg_1 * DEG_TO_RAD) * sin(random_deg_2 * DEG_TO_RAD),
			100 * cos(random_deg_2 * DEG_TO_RAD)
		);
		auto future_distance = future - location;

		this->location_list.push_back(location);
		this->velocity_list.push_back(glm::normalize(future_distance) * glm::length(velocity * 0.05));
	}

	for (int i = this->location_list.size() - 1; i > -1; i--) {

		this->location_list[i] += this->velocity_list[i];
		this->velocity_list[i] *= 1.01;

		if (glm::length(this->location_list[i]) > 720) {

			this->location_list.erase(this->location_list.begin() + i);
			this->velocity_list.erase(this->velocity_list.begin() + i);
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (auto& location : this->location_list) {

		ofDrawSphere(location, 5);
		for (auto& other : this->location_list) {

			if (location == other) continue;

			if (glm::distance(location, other) < 100) {

				ofDrawLine(location, other);
			}
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}