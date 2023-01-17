#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetLineWidth(1);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	int len = 40;
	int width = len * 0.15;

	for (int x = -len * 8; x <= len * 8; x += len) {

		for (int y = -len * 8; y <= len * 8; y += len) {

			ofPushMatrix();
			ofTranslate(x, y, 0);

			ofMesh mesh, frame;
			frame.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
			mesh.addVertex(glm::vec3());
			for (int param = 0; param <= 100; param++) {

				float deg = param * 3.6 - 135;
				auto noise_value = ofNoise(x * 0.002 + cos(deg * DEG_TO_RAD) * 0.15, y * 0.002 + sin(deg * DEG_TO_RAD) * 0.15, ofGetFrameNum() * 0.015);

				vector<glm::vec3> vertices;
				if (noise_value > 0.5) {

					vertices.push_back(glm::vec3(this->make_point(len, param), width * 0.5));
				}
				else {

					vertices.push_back(glm::vec3(len * 0.4 * cos(deg * DEG_TO_RAD), len * 0.4 * sin(deg * DEG_TO_RAD), width * 0.5));
				}

				mesh.addVertices(vertices);
				frame.addVertices(vertices);

				if (param > 0) {

					mesh.addIndex(0);
					mesh.addIndex(mesh.getNumVertices() - 1);
					mesh.addIndex(mesh.getNumVertices() - 2);

					frame.addIndex(frame.getNumVertices() - 1);
					frame.addIndex(frame.getNumVertices() - 2);
				}
			}

			ofSetColor(0);
			frame.drawWireframe();

			ofSetColor(0, 168);
			mesh.draw();

			ofPopMatrix();
		}
	}

	this->cam.end();
}

//--------------------------------------------------------------
glm::vec2 ofApp::make_point(int len, int param) {

	param = param % 100;
	if (param < 25) {

		return glm::vec2(ofMap(param, 0, 25, -len * 0.5, len * 0.5), -len * 0.5);
	}
	else if (param < 50) {

		return glm::vec2(len * 0.5, ofMap(param, 25, 50, -len * 0.5, len * 0.5));
	}
	else if (param < 75) {

		return glm::vec2(ofMap(param, 50, 75, len * 0.5, -len * 0.5), len * 0.5);
	}
	else {

		return glm::vec2(-len * 0.5, ofMap(param, 75, 100, len * 0.5, -len * 0.5));
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}