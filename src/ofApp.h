#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "math.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofMesh varLine;
        ofMesh mesh;
        int width = 1200;
        int vWidth = 300;
        int widthCenter = (ofGetWidth()-width)/2;
        int height = 1200;
        int vHeight = 300;
        int heightCenter = (ofGetHeight() - height)/2;
        int scl = 15;
        int cols = width / scl;
        int rows = height / scl;
        int randomZ;

        // ----
        // OpenCV
        ofVideoGrabber 		vidGrabber;
        ofxCvColorImage			colorImg;

        ofxCvGrayscaleImage 	grayImage;
        ofxCvGrayscaleImage 	grayBg;
        ofxCvGrayscaleImage 	grayDiff;

        ofxCvContourFinder 	contourFinder;

        int 				threshold;
        bool				bLearnBakground;



		
};
