//
//  GUI.cpp
//  ViZa
//
//  Created by martin hermant on 14/10/14.
//
//

#include "GUI.h"






GUI * GUI::inst;



GUI::GUI(){
    
    

    ofAddListener(ofEvents().update, this, &GUI::update);

    

    
    ///LOGGER///////////
    
    
    logCanvas = new ofxUISuperCanvas("Log",0,700,900,100,OFX_UI_FONT_SMALL);
    logCanvas->setName("Log");
    
    
    Logger = new ofxUITextArea("Logger","Log",900,0,0,0,OFX_UI_FONT_SMALL);
    Logger->setVisible(true);
    

    
    
 
    

    
    

    

    
    //// FITTER ///////////////
    fitterCanvas = new ofxUISuperCanvas("Fitter");
    fitterCanvas->setName("Fitter");
    samplingPct = new ofxUISlider("sampling%",.05,2,1,100,10);
    typeOfFit = new ofxUIDropDownList("typeOfFit",SliceFitter::DistanceType::types,150,0,0,OFX_UI_FONT_SMALL);
    keepResults = new ofxUIToggle("keep Results",false,10,10);
    fitIt = new ofxUIButton("FitIt",false,10,10);
    applyIt = new ofxUIButton("apply",false,10,10);
    
    ////////////////CLUSTER </////////////////////
    clusterCanvas = new ofxUISuperCanvas("Cluster");
    clusterCanvas->setName("Cluster");
    findClusters = new ofxUIButton("findClusters",false,10,10);
    clusterEps = new ofxUISlider("Epsilon",.01,.3,.05,100,10);
    clusterMinK = new ofxUISlider("MinK",2,100,10,100,10);
    minClusterSize = new ofxUISlider("minClusterSize",0,500,10,100,10);
    tSNE2D = new ofxUIToggle("tSNE2d",false,10,10);
    tSNEPerp = new ofxUISlider("tSNEPerplexity",2,65,5,100,10);
    tSNEtheta = new ofxUISlider("tSNEtheta",.0,.49,.2,100,10);
    findtSNE = new ofxUIButton("tSNE",false,10,10);
    applyTsne = new ofxUIButton("apply",false,10,10);
    
    
    
    //MIDI//////////
    midiCanvas = new ofxUISuperCanvas("Midi");
    midiCanvas->setName("Midi");
    
    
    midiPorts = new ofxUIDropDownList("MidiPorts", Midi::instance()->getPorts(),150,0,0,OFX_UI_FONT_SMALL);
    midiVel = new ofxUIRangeSlider("VelocityRange",0,1,0,1,100,10);
    
    midiRadius = new ofxUISlider("Radius",0,.5,0.05,100,10);
    midiHold = new ofxUIToggle("Hold",false,10,10);
    
    midiLink2Cam = new ofxUIToggle("link2Cam",true,10,10);
    link2x = new ofxUIToggle("link2X",false,10,10);
    
    //VIEWWWW/////////////
    
    viewCanvas = new ofxUISuperCanvas("View");
    viewCanvas->setName("View");
    
    alphaView = new ofxUISlider("alphaView",0,1,0.3f,100,10);
    selBrightest = new ofxUIToggle("SelectBrightest",false,10,10);
    linkClasses = new ofxUIToggle("linkClasses",false,10,10);
    orthoCam = new ofxUIToggle("orthoCam",true,10,10);
    pointSize = new ofxUISlider("pointSize",0,30,1,100,10);
    isClipping = new ofxUIToggle("isClipping",false,10,10);
    show2dViews = new ofxUIToggle("2dViews",false,10,10);
    fishEyeRadius = new ofxUISlider("fishEyeRadius",0.0,1.0,0.,100,10);
    fishEyeStrength = new ofxUISlider("fishEyeStrength",0.01,1,.5,100,10);
    //// PLAYBACK /////////////
    playBack =new ofxUISuperCanvas("playBack");
    playBack->setName("playBack");
    
    continuousPB = new ofxUIToggle("continuousPlayBack",true,10,10);
    holdPB = new ofxUIToggle("hold",false,10,10);
    
    
    ///PLACING//////////////
    
    
       
    viewCanvas->addWidgetDown(alphaView);
    viewCanvas->addWidgetDown(selBrightest);
    viewCanvas->addWidgetDown(linkClasses);
    viewCanvas->addWidgetDown(orthoCam);
    viewCanvas->addWidgetDown(pointSize);
    viewCanvas->addWidgetDown(isClipping);
    viewCanvas->addWidgetDown(show2dViews);
    viewCanvas->addWidgetDown(fishEyeRadius);
    viewCanvas->addWidgetDown(fishEyeStrength);
    
    midiCanvas->addWidgetDown(midiPorts);
    midiCanvas->addWidgetDown(midiVel);
    midiCanvas->addWidgetDown(midiRadius);
    midiCanvas->addWidgetDown(midiHold);
    midiCanvas->addWidgetDown(midiLink2Cam);
    midiCanvas->addWidgetDown(link2x);
    
    fitterCanvas->addWidgetDown(typeOfFit);
    fitterCanvas->addWidgetDown(samplingPct);
    fitterCanvas->addWidgetDown(keepResults);
    fitterCanvas->addWidgetDown(fitIt);
    fitterCanvas->addWidgetDown(applyIt);
    
    
    clusterCanvas->addWidgetDown(findClusters);
    
    clusterCanvas->addWidgetDown(clusterMinK);
    clusterCanvas->addWidgetDown(clusterEps);
    clusterCanvas->addWidgetDown(minClusterSize);
    clusterCanvas->addSpacer();
    clusterCanvas->addLabel("t-SNE");
    clusterCanvas->addSpacer();
    clusterCanvas->addWidgetDown(tSNEtheta);
    clusterCanvas->addWidgetDown(tSNEPerp);
    clusterCanvas->addWidgetDown(tSNE2D);
    clusterCanvas->addWidgetDown(findtSNE);
    clusterCanvas->addWidgetDown(applyTsne);
    
    clusterCanvas->setDimensions(clusterCanvas->getRect()->width, clusterCanvas->getRect()->height*1.3);
    logCanvas->addWidgetDown(Logger);
    
    

    
    playBack->addWidgetDown(continuousPB);
    playBack->addWidgetDown(holdPB);
    
    
    //GLOBAL TAB
    global = new ofxUITabBar();
    
    global->setName("Global");
    
    global->addCanvas(guiAxe.canvas);
    global->addCanvas(guiClass.canvas);
    //    global->addCanvas(logCanvas);
    global->addCanvas(viewCanvas);
    global->addCanvas(fitterCanvas);
    global->addCanvas(clusterCanvas);
    global->addCanvas(midiCanvas);
    global->addCanvas(playBack);
    
    
    
    vector<ofxUIWidget*> ddls;
    ddls.push_back(midiPorts);
    ddls.push_back(typeOfFit);
    for(int i = 0 ; i < ddls.size(); i++){
        ((ofxUIDropDownList*) ddls[i])->setAutoClose(true);
        ((ofxUIDropDownList*) ddls[i])->setShowCurrentSelected(true);
    }
    
}


GUI::~GUI(){
    //    delete global;
}

void GUI::setup(){
    
    
    guiAxe.setup();
    
    guiClass.setup();

    
    logCanvas->autoSizeToFitWidgets();
    
    
}



void GUI::registerListener(){
    
    map< ofxUIToggle*,ofxUICanvas* > w = global->canvases;
    for(map< ofxUIToggle*,ofxUICanvas* > ::iterator it = w.begin() ; it!=w.end() ; ++it){
        //        it->second->setParent(global);
        ofAddListener(((ofxUICanvas*)(it->second))->newGUIEvent,this,&GUI::guiEvent);
    }
    
    
}

void GUI::guiEvent(ofxUIEventArgs &e){

    
    ofxUICanvas * root,*parent;
    
    
    
    root = (ofxUICanvas*)e.widget;
    
    while(root->getParent()!=NULL ){root= (ofxUICanvas*)root->getParent();}
    if(e.widget->getParent()!=NULL){ parent = (ofxUICanvas*)e.widget->getParent();}
    else{parent = root;}
    
    

    
    
    // hack for avoiding double hits on opened DDLists
    checkOverlapingDDL(e);
    
//    
//    if(parent == NULL){
//        ofLogError("GUI", "orphan !!! : " +e.widget->getName() );
//        return;
//    }
    //ID for GUI Controls
    string rootName = root->getName();
    string parentName = parent->getName();
    
    
    
    if(root!=NULL){
        ofLogVerbose("GUI",root->getName() + "//" + e.getParent()->getName() + "//" + e.getName());
    }
    
    if(root == guiAxe.canvas){
        guiAxe.guiEvent(e);
    }
    //CLASSES ////////////////////////////////
      else if(root == guiClass.canvas){
          guiClass.guiEvent(e);

    }
    
    // View
    else    if(rootName == "View" ){
        
        if(e.widget == alphaView){
            Container::stateColor[0].a = pow((alphaView)->getValue(),2);
            Physics::updateAllColorsAlpha();
        }
        if(e.widget == linkClasses){
            Physics::linkClasses = linkClasses->getValue();
        }
        if(e.widget == orthoCam){
            Camera::mainCam->setcamOrtho(orthoCam->getValue());
        }
        if(e.widget == pointSize){
            Container::radius = pointSize->getValue();
            //            glPointSize(Container::radius);
        }
        if(e.widget == show2dViews){
            
            Camera::mainCam->setRelativeViewPort(0, 0,show2dViews->getValue()? .75:1, 1);
            Camera::mainCam->updateViewPort();
            Camera::setSecondaryVisible(show2dViews->getValue());
            Physics::updateVScreen();
            
        }
    }
    
    // FITTER ///////////////
    
    else if(rootName == "Fitter"){
        if(e.widget == keepResults){
            SliceFitter::i()->keepResult = keepResults->getValue();
        }
        else if (e.widget == typeOfFit){
            if(typeOfFit->getSelectedIndeces().size()>0){
                SliceFitter::i()->type.idx = typeOfFit->getSelectedIndeces()[0];
            }
        }
        else if(e.widget == samplingPct){
            SliceFitter::i()->samplePct = samplingPct->getValue();
        }
        else if(e.widget == fitIt && !fitIt->getValue()){
            if(SliceFitter::i()->fitThread.isThreadRunning()){
                SliceFitter::i()->fitThread.fitter->forceStop();
            }
            else
                SliceFitter::i()->fitFor();
        }
        else if (e.widget == applyIt && !applyIt->getValue()){
            Physics::applyEquation(SliceFitter::i()->fitEquation);
            for(int i = 0 ; i < 3 ; i++){
                guiAxe.aggr[i]->setLabelText("FitterEq");
                guiAxe.attr[i]->setLabelText("FitterEq");
            }
        }
        
    }
    
    // CLUSTER /////////////////////////////////////////////
    else if (rootName == "Cluster"){
        if(e.widget == findClusters && !findClusters->getValue()){
            vector<int> classes(Physics::vs.size(),0);
            Physics::kNN.dbscan(&classes,  clusterMinK->getValue(), clusterEps->getValue(),minClusterSize->getValue());
            //            Physics::kNN.medoids(&classes,  clusterMinK->getValue(), clusterEps->getValue(),minClusterSize->getValue());
            
            
            Container::classeMap["Cluster"].clear();
            
            for(int i = 0 ; i < classes.size();i++){
                
                if(abs(classes[i])>0){
                    Physics::updateOneColor(i, ofColor(Container::getColorForId(abs(classes[i])-1),255*alphaView->getValue()));
                    
                }
                else{
                    Physics::updateOneColor(i, ofColor(ofColor::white,5));
                }
                Container::containers[i]->setClass("Cluster", ofToString(abs(classes[i])));
            }
            
            
            Physics::updateVScreen();
            
        }
  
        if(e.widget == findtSNE && !findtSNE->getValue()){
            
            int dim = tSNE2D->getValue()?2:3;
            for(int i = 0 ; i < dim ;i++){
                guiAxe.aggr[i]->setLabelText("tSNE");
                guiAxe.attr[i]->setLabelText("tSNE");
            }
            
            if(ofxTSNE::i()->isThreadRunning()){
                ofxTSNE::i()->stopThread();
            }
            else{
                ofxTSNE::i()->init(Container::normalizedAttributes, Container::attrSize, Container::containers.size(), tSNEtheta->getValue(), tSNEPerp->getValue(),dim);
                ofxTSNE::i()->startThread();
            }
        }
        else if (e.widget == applyTsne && !applyTsne->getValue()){
            if(Physics::applyFit()){
                for(int i = 0 ; i < tSNE2D->getValue()?2:3 ;i++){
                    guiAxe.aggr[i]->setLabelText("tSNE");
                    guiAxe.attr[i]->setLabelText("tSNE");
                }
            }
        }
    }
    
    // Midi
    
    else    if(rootName == "Midi" ){
        if(parentName == "MidiPorts"){
            Midi::instance()->midiIn.closePort();
            Midi::instance()->midiIn.openPort(e.getName());
        }
        if(e.getName() == "VelocityRange"){
            Midi::velScale.set(((ofxUIRangeSlider*)e.widget)->getValueLow(),((ofxUIRangeSlider*)e.widget)->getValueHigh());
        }
        if(e.getName() == "Radius"){
            Midi::radius = ((ofxUISlider*)e.widget)->getValue();
        }
        if(e.getName()=="Hold"){
            Midi::hold=((ofxUIToggle*)e.widget)->getValue();
        }
        if(e.getName() == "link2Cam"){
            Midi::link2Cam = ((ofxUIToggle*)e.widget)->getValue();
        }
        if(e.widget == link2x ){
            if(link2x->getValue())
                Midi::midiModulo = Physics::maxs->x - Physics::mins->x + 1;
            else{
                Midi::midiModulo = 12;
            }
        }
        
        
        
    }
    else if (rootName=="playBack"){

    }

    lastFramenum = ofGetFrameNum();
    
}








void GUI::LogIt(string s){
    instance()->Logger->setTextString(s);
    
}

bool GUI::isOver(int x,int y){
    bool res = global->isHit(x,y);
    
    ofxUICanvas * c = global->getActiveCanvas();
    if(c)res |= c->isHit(x, y);
    res |= logCanvas->isHit(x,y);
    return res;
    //    global->getActiveCanvas();
}



void GUI::checkOverlapingDDL(ofxUIEventArgs & e){
    
    switch (e.getKind()) {
        case OFX_UI_WIDGET_DROPDOWNLIST:
        {bool hideothers = ((ofxUIDropDownList*)e.widget)->getValue();
            
            if(e.getCanvasParent()!=NULL){
                vector<ofxUIWidget*> vv = e.getCanvasParent()->getWidgetsOfType(OFX_UI_WIDGET_DROPDOWNLIST);
                for(vector<ofxUIWidget*>::iterator it = vv.begin() ; it !=vv.end() ; ++it){
                    if(e.widget->getRect()->x ==  (*it)->getRect()->x && e.widget->getRect()->y <  (*it)->getRect()->y &&((ofxUIDropDownList*)*it)!=e.widget){
                        
                        ((ofxUIDropDownList*)*it)->setVisible(!hideothers);
                    }
                }
            }
        }
            break;
            
            
        default:
            break;
    }
    
}


void GUI::update(ofEventArgs &a){
    guiClass.async();
    guiAxe.async();
}