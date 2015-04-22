//
//  Camera.h
//  ViZa
//
//  Created by martin hermant on 20/01/15.
//
//

#ifndef __ViZa__Camera__
#define __ViZa__Camera__

#include <iostream>
#include "ofMain.h"



class Camera : public ofEasyCam{
public:
    
    static Camera* hoveredCam;
    static Camera* mainCam;
    static vector<Camera*> allInstances;
    Camera();
    Camera (float x,float y,float w, float h);
    virtual ~Camera();
    void setup();
    void setcamOrtho(bool t);
    void drawMire();
    void drawCam();
    float toCamZ(float z);
    void setRelativeViewPort(float x,float y, float width,float height);
    
    
    void reset();
    void begin();
    void end();
    ofVec3f distanceVanish();
    void updateViewPort();
    bool isVisible;
    
    bool isPointVisible(const ofVec3f & v);
    
    void setupGL();
    static Camera* getActiveCam();
    static void setSecondaryVisible(bool t);
private:
    
    void drawAxes(float newSize);
    void mouseMoved(ofMouseEventArgs &arg);
    float depth;
    
    static ofMesh cacheAxe;
    
    ofRectangle relViewPort;
    
    
    
};



#endif /* defined(__ViZa__Camera__) */
