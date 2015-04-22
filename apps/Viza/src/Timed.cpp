//
//  Timed.cpp
//  RTaudio
//
//  Created by martin hermant on 27/02/14.
//
//

#include "Timed.h"


 Timed TimeLine;




void Timed::addDel(float del, string s){
    list.push_back(Wtng(del+ofGetElapsedTimeMillis(),s));
    
}

void Timed::delDel(string s){
    for(vector<Wtng>::iterator it = list.begin() ; it !=list.end() ; ++it){
        if((*it).msg == s){
            list.erase(it++);
            break;
        }
    }
}

void Timed::update(ofEventArgs & args){
   
    vector<Wtng>::iterator it = list.begin();
    if(list.size()>0 && list.back().isDone)list.pop_back();
    while (it!=list.end()){
        if(!it->isDone){
       
        if( (unsigned long )ofGetElapsedTimeMillis()>it->time){
            cout<<it->msg<<endl;
            ofSendMessage(it->msg);
            it->isDone=true;
        }
        }
        ++it;
        
        
    }
    
    
}