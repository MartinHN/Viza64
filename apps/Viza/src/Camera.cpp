//
//  Camera.cpp
//  ViZa
//
//  Created by martin hermant on 20/01/15.
//
//

#include "Camera.h"
#include "Container.h"
#include "Physics.h"
#include "ofApp.h"


ofMesh Camera::cacheAxe;
Camera* Camera::hoveredCam;
Camera* Camera::mainCam;
vector<Camera*> Camera::allInstances;


Camera::Camera(float x, float y , float w, float h){
    Camera::Camera();
    relViewPort.set(x,y,w,h);
}

Camera::Camera(){
    ofAddListener(ofEvents().mouseMoved, this, &Camera::mouseMoved);
    enableOrtho();
    relViewPort.set(0,0,1,1);
    allInstances.push_back(this);
    isVisible = true;
    
}

Camera::~Camera(){
    int foundIdx=ofFind(allInstances,this);
    if( foundIdx!=allInstances.size() ){
        allInstances.erase(allInstances.begin()+foundIdx);
    }
    ofRemoveListener(ofEvents().mouseMoved, this, &Camera::mouseMoved);
    
}
void Camera::setupGL(){
//    GLfloat attPoints[] = {0,,0};//*,0};
    glPointParameterfv(	GL_POINT_DISTANCE_ATTENUATION,&distanceVanish()[0]);
//    Container::radius = 10;
    glPointSize(Container::radius);
}
void Camera::setup(){
    ofEasyCam::reset();
    setDistance(1);
    orbit(0,0, getDistance());
    setAutoDistance(false);
    enableMouseInput();
    disableMouseMiddleButton();
}

void Camera::drawCam(){
    
    ofPushMatrix();
    ofPushView();
    
    ofMatrix4x4 t ;
    ofMatrix4x4 ortho ;
    float angle;
    ofVec3f v;
    
    float size = 60;
    float coneBase = size/4;
    float coneHeight  = size/4;
    
    ofSetColor(100);
    ofFill();
    ofSetLineWidth(14);
    if(viewport.getMinX()>0)ofDrawLine(viewport.getTopLeft(),viewport.getBottomLeft());
    if(viewport.getMaxX()<ofGetWindowWidth())ofDrawLine(viewport.getTopRight(),viewport.getBottomRight());
    if(viewport.getMinY()>0)ofDrawLine(viewport.getTopLeft(),viewport.getTopRight());
    if(viewport.getMaxY()>ofGetWindowHeight())ofDrawLine(viewport.getBottomLeft(),viewport.getBottomRight());
    
    // get camera rotation
    getOrientationQuat().getRotate(angle, v);
    
    ofViewport(viewport.getMaxX()-2*size,viewport.getMinY(),2*size,2*size,true);
    
	ortho.makeOrthoMatrix(-size,  size  , -size, size, .1, 2*size);
    ofSetOrientation(ofGetOrientation(),true);
    t.makeTranslationMatrix(0,0,-size);
    
    ofSetMatrixMode(OF_MATRIX_PROJECTION);
	ofLoadMatrix( ortho);
	ofSetMatrixMode(OF_MATRIX_MODELVIEW);
	ofLoadMatrix( t);
    
    ofRotate(angle,v.x,-v.y,v.z);
    
    drawAxes(size);
    
    ofPopView();
    ofPopMatrix();
    
}

void Camera::end(){
    drawMire();
    ofEasyCam::end();
    drawCam();
}

void Camera::setcamOrtho(bool t){
    
    
    if(t){
        enableOrtho();
        
        float a = MIN(viewport.width,viewport.height);
        setScale(1.0/a);
        depth = getDistance()*20*a;
        setFarClip(depth);
        setNearClip(.000001f);
//        setNearClip(.5f*a);
        setLensOffset(ofVec2f(-1,-1));
        
        
        
    }
    else{
        disableOrtho();
        setScale(1);
        setNearClip(.000001f);
        depth = getDistance()*3;
        setFarClip(depth);
        setFov(2*ofRadToDeg(atan(.5/getDistance())));
        setLensOffset(ofVec2f(0,0));
        
        
        
    }
    
}

void Camera::drawMire(){
    ofPushMatrix();
    ofPushStyle();
    ofNoFill();
    ofSetLineWidth(1);
    ofSetCircleResolution(60);
    ofSetColor(0,0,255);
    ofDrawCircle(ofVec3f(0),.5);
    ofRotateX(90);
    ofSetColor(0,255,0);
    ofDrawCircle(ofVec3f(0),.5);
    ofRotateY(90);
    ofSetColor(255,0,0);
    ofDrawCircle(ofVec3f(0),.5);
    ofPopStyle();
    ofPopMatrix();
    
    ofPushMatrix();
    ofPushStyle();
    ofFill();
    for (int i = 0 ; i < 3 ; i++){
        ofVec3f mask(i==0?255:0,i==1?255:0,i==2?255:0);
        ofSetColor (mask.x,mask.y,mask.z);
        //        ofSetDrawBitmapMode(OF_BITMAPMODE_MODEL_BILLBOARD);
        ofDrawBitmapString(GUI::instance()->guiAxe.attr[i]->getSelected()[0]->getName() +"."+ GUI::instance()->guiAxe.aggr[i]->getSelected()[0]->getName(), .45/255.*mask);
    }
    ofPopStyle();
    ofPopMatrix();
}

void Camera::begin()
{
    setupGL();
    ofEasyCam::begin(viewport);
}


void Camera::setRelativeViewPort(float x,float y, float width,float height){
    
    relViewPort.set(x, y, width, height);
    
    viewport.x = ofApp::scrS.x*x;
    viewport.y = ofApp::scrS.y*y;
    viewport.width = ofApp::scrS.x*width;
    viewport.height = ofApp::scrS.y*height;
    
}


void Camera::updateViewPort(){
    viewport.x = ofApp::scrS.x*relViewPort.x;
    viewport.y = ofApp::scrS.y*relViewPort.y;
    viewport.width = ofApp::scrS.x*relViewPort.width;
    viewport.height = ofApp::scrS.y*relViewPort.height;
    setcamOrtho(isOrtho);
}
float Camera::toCamZ(float z){
    float nZ = (getDistance()-z)/getScale().z;
    return ofMap(nZ,getNearClip(), getFarClip(), -1, 1);
}


void Camera::reset()
{
    if(this==getActiveCam()){
        ofEasyCam::reset();
        setcamOrtho(isOrtho);
    }
    
    
}
void Camera::mouseMoved(ofMouseEventArgs &arg){
    if(isVisible){
        
        if(viewport.inside(arg.x,arg.y)){
            if(this!=hoveredCam){
                hoveredCam = this;
                Physics::updateVScreen();
            }
            else{
                hoveredCam=this;
            }
        }
        if(GUI::instance()->isOver(arg.x,arg.y)){
            if(getMouseInputEnabled())disableMouseInput();
        }
        else if(!getMouseInputEnabled())enableMouseInput();
    }
}


ofVec3f Camera::distanceVanish(){
    if(getOrtho()){
        float max = 10;
        return ofVec3f( 0,//getScale().x,//2/(max*max)-1,
                       0,//(2-2/(max*max))*getScale().x/getDistance(),
                       pow(getScale().x/getDistance(),2)//0
                       );
    }
    else return ofVec3f(0,2.0f/tan(ofDegToRad(getFov()/2.0f)),0);
}

Camera * Camera::getActiveCam(){
    return hoveredCam?hoveredCam:mainCam;
}


bool Camera::isPointVisible(const ofVec3f & v){
    bool res = true;
    if(GUI::instance()->isClipping->getValue()){
        res &= v.x>=-0.5 && v.x <= 0.5 &&
               v.y>=-0.5 && v.y <= 0.5 &&
                v.z>=-0.51 && v.z <= 0.51 ;
        if(res == false) return res;
    }
    
    ofVec3f clipC = v * getModelViewProjectionMatrix(viewport);
    res &= clipC.x>-1 && clipC.x <1 &&
            clipC.y>-1 && clipC.y <1 &&
            clipC.z>-1 && clipC.z <0 ;
    return res;
}

void Camera::drawAxes(float newSize){
    float size = 1;
    if(cacheAxe.getNumVertices()==0){
        cacheAxe.setMode(OF_PRIMITIVE_TRIANGLES);
        float coneHeight = size*.2;
        float coneBase = size*.1;
        float axeW = size*.02;
        ofMesh curMesh;
        ofColor curCol;
        
        
        for(int i = 0 ; i < 3 ; i++){
            
            curCol = ofColor(i==0?255:0,i==1?255:0,i==2?255:0);
            
            curMesh = ofMesh::cone(coneBase,coneHeight,10,2,0,OF_PRIMITIVE_TRIANGLES);
            
            for(int j=0;j<curMesh.getNumVertices() ; j ++){
                ofVec3f vert = curMesh.getVertex(j);
                vert.rotate(i==2?-90:0,0,i==0?90:0);
                vert[i]+=(i==1?-1:1)*(size-coneHeight);
                curMesh.setVertex(j, vert);
                curMesh.addColor(curCol);
            }
            cacheAxe.append(curMesh);
            
            curMesh.clear();
            curMesh = ofMesh::cylinder(axeW, size-coneHeight,6,2,0,false,OF_PRIMITIVE_TRIANGLES);
            
            for(int j=0;j<curMesh.getNumVertices() ; j++){
                ofVec3f vert = curMesh.getVertex(j);
                vert.rotate(i==2?90:0,0,i==0?90:0);
                vert[i]+=(i==1?-1:1)*(size-coneHeight)/2;
                curMesh.setVertex(j, vert);
                curMesh.addColor(curCol);
            }
            cacheAxe.append(curMesh);
            
            
        }
        
        
    }
    
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    
    ofScale(newSize/size,newSize/size,newSize/size);
    cacheAxe.draw();
    ofScale(1,1,1);
    
}
void Camera::setSecondaryVisible(bool t){
    for(int i = 0 ; i < allInstances.size() ; i++){
        if(allInstances[i]!=mainCam)allInstances[i]->isVisible = t;
    }
}