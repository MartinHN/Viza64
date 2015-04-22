//
//  Timed.h
//  RTaudio
//
//  Created by martin hermant on 27/02/14.
//
//

#ifndef __RTaudio__Timed__
#define __RTaudio__Timed__
#include "ofMain.h"


class Wtng{
    public :
    Wtng(unsigned long t, string s):time(t),msg(s),isDone(false){};
    unsigned long time;
    string msg;
    bool isDone;
};

class Timed {
public:
    
    Timed(){
        ofAddListener(ofEvents().update, this, &Timed::update);
    };
    void update(ofEventArgs & args);
    void addDel(float del,string s);
    void delDel(string s);
    
    vector<Wtng> list;
};


extern Timed TimeLine;
#endif /* defined(__RTaudio__Timed__) */
