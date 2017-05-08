#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofSetBackgroundColor(0);
    ofSetFrameRate(60);

    // ------
    // OpenCV
    vidGrabber.setVerbose(true);
    vidGrabber.setup(vWidth, vHeight);
    vidGrabber.listDevices();

    colorImg.allocate(vWidth, vHeight);
    grayImage.allocate(vWidth, vHeight);
    grayBg.allocate(vWidth, vHeight);
    grayDiff.allocate(vWidth, vHeight);

    bLearnBakground = true;
    threshold = 80;

    //--------------------------------------
    // Création des vertex / index
    //mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    float r = 75;
    for (int y = 0 ; y < rows ; y++) {
        for (int x = 0 ; x < cols ; x++) {
            mesh.addVertex(ofPoint(x*scl,y*scl));
        }
    }
    for (int y = 0 ; y < rows-1 ; y++ ) {
        for (int x = 0 ; x < cols-1 ; x ++ ) {
            mesh.addIndex(x+y*cols);
            //mesh.setVertex(x+y*cols, ofPoint(x*scl, y*scl, ofRandom(-1,1)));
            mesh.addIndex((x+1)+y*cols);
            mesh.addIndex(x+(y+1)*cols);

            mesh.addIndex((x+1)+y*cols);
            mesh.addIndex((x+1)+(y+1)*cols);
            //mesh.setVertex((x+1)+(y+1)*cols, ofPoint(x*scl, y*scl, ofRandom(-1,1)));
            mesh.addIndex(x+(y+1)*cols);
        }
    }


}

//--------------------------------------------------------------
void ofApp::update(){
    int clr = 255;
    ofSetColor(clr);

    
    //--------------------------------------
    // -------------------------------------
    // OpenCV
    bool bNewFrame = false;

    vidGrabber.update();
    bNewFrame = vidGrabber.isFrameNew();
    if (bNewFrame){

            colorImg.setFromPixels(vidGrabber.getPixels());
        grayImage = colorImg;
        if (bLearnBakground == true){
            grayBg = grayImage;		// the = sign copys the pixels from grayImage into grayBg (operator overloading)
            bLearnBakground = false;
        }

        // take the abs value of the difference between background and incoming and then threshold:
        grayDiff.absDiff(grayBg, grayImage);
        grayDiff.threshold(threshold);

        // find contours which are between the size of 20 pixels and 1/3 the w*h pixels.
        // also, find holes is set to true so we will get interior contours as well....
        contourFinder.findContours(grayDiff, 2000, (width*height)/3, 5, false);	// find holes
    }
    
    



}

//--------------------------------------------------------------
void ofApp::draw(){


    ofRotateX(30);
    ofTranslate(widthCenter, heightCenter );
    //------
    // OpenCV
    ofSetHexColor(0xffffff);
    ofFill();
    ofSetHexColor(0x333333);
    ofSetHexColor(0xffffff);
    mesh.drawWireframe();

    for (int y = 0 ; y < rows+1 ; y++) {
        for (int x = 0 ; x < cols+1 ; x++) {
            mesh.setVertex(x+y*(width/scl), ofPoint(x*scl,y*scl,0));
        }
    }


    for (int i = 0; i < contourFinder.blobs.size() ; i++){

        for (int j = 0 ; j < contourFinder.blobs[i].nPts ; j++) {

            int blobX = ofMap(contourFinder.blobs[i].pts[j].x, 0, vWidth, 0, height);
            int blobY = ofMap(contourFinder.blobs[i].pts[j].y, 0, vHeight, 0, height);

            int x = blobX / scl;
            int y = blobY / scl;
            int xx = round((blobX + (scl/2)) / scl) * scl;
            int yy = round((blobY + (scl/2)) / scl) * scl;

            mesh.setVertex(x+y*(width/scl), ofPoint(xx-scl,yy-scl,10));

        }

    }


    // Get FrameRate --------------------------------------------------------------
    ofDrawBitmapString(ofGetFrameRate(), width/2, -300);
    float yFrameRate = ofMap(ofGetFrameRate(), 0.0000, 60.0000, 0.000, -300.000);
    int nv = varLine.getNumVertices();
    varLine.addVertex(ofPoint(width/2, yFrameRate, 0));
    varLine.addIndex(nv);
    for (int i = 0 ; i < varLine.getNumVertices() ; i++){
        int y = varLine.getVertex(i).y;
        varLine.setVertex(i, ofPoint((width/2)-(nv--), y , 0));
    }
    varLine.drawWireframe();
    //-----------------------------------------------------------------------------

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key){
        case ' ':
            bLearnBakground = true;
            for (int y = 0 ; y < rows ; y++ ) {
                for (int x = 0 ; x < cols ; x ++ ) {
                        mesh.setVertex(x+y*(width/scl), ofPoint(x*scl,y*scl,0));
                }
            }
            break;
        case '+':
            threshold ++;
            if (threshold > 255) threshold = 255;
            break;
        case '-':
            threshold --;
            if (threshold < 0) threshold = 0;
            break;
         case 'f':
            ofToggleFullscreen();
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

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
