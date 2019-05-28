#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateY(ofGetFrameNum() * 0.5);

	int number_of_satellite = 3;
	int number_of_log = 15;

	for (int g = 0; g < 25; g++) {

		auto base_seed_x = ofRandom(1000);
		auto base_seed_y = ofRandom(1000);
		auto base_seed_z = ofRandom(1000);
		auto base_location = glm::vec3(ofMap(ofNoise(base_seed_x, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -350, 350), ofMap(ofNoise(base_seed_y, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -350, 350), ofMap(ofNoise(base_seed_z, (ofGetFrameNum() + number_of_log) * 0.005), 0, 1, -350, 350));
		auto base_radius = 15;

		for (int i = 0; i < number_of_satellite; i++) {

			float noise_seed_x = ofRandom(1000);
			float noise_seed_y = ofRandom(1000);
			auto location = glm::vec3(ofRandom(-1, 1), ofRandom(-1, 1), ofRandom(-1, 1));
			location = glm::normalize(location) * base_radius * 1.5;
			auto prev_location = glm::vec3();
			for (int k = 0; k < number_of_log; k++) {

				auto rotation_y = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_y, (ofGetFrameNum() + k) * 0.01), 0, 1, -PI * 2, PI * 2), glm::vec3(0, 1, 0));
				auto rotation_x = glm::rotate(glm::mat4(), ofMap(ofNoise(noise_seed_x, (ofGetFrameNum() + k) * 0.01), 0, 1, -PI * 2, PI * 2), glm::vec3(1, 0, 0));
				auto tmp_base_location = glm::vec3(ofMap(ofNoise(base_seed_x, (ofGetFrameNum() + k) * 0.005), 0, 1, -350, 350), ofMap(ofNoise(base_seed_y, (ofGetFrameNum() + k) * 0.005), 0, 1, -350, 350), ofMap(ofNoise(base_seed_z, (ofGetFrameNum() + k) * 0.005), 0, 1, -350, 350));
				auto draw_location = tmp_base_location + glm::vec4(location, 0) * rotation_y * rotation_x;

				if (k > 0) {

					ofSetColor(39, ofMap(k, 1, number_of_log, 0, 255));
					ofDrawLine(prev_location, draw_location);
				}

				prev_location = draw_location;
			}

			ofDrawSphere(prev_location, base_radius * 0.3);
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}