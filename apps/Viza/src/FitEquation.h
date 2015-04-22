//
//  FitEquation.h
//  ViZa
//
//  Created by martin hermant on 09/01/15.
//
//

#ifndef ViZa_FitEquation_h
#define ViZa_FitEquation_h

#include "ofMain.h"

class FitEquation{
    
public:
    typedef pair<int,float> eqElem;
    typedef vector< eqElem > eqStruct;
    
    eqStruct equation[3];
    vector<string> paramNames;
    
    
    
    
    eqStruct getTruncated(float min,int axe){
        eqStruct res ;
        for(eqStruct::iterator it = equation[axe].begin() ; it !=equation[axe].end() ; ++it){
            if(abs(it->second)>min){
                res.push_back(*it);
            }
        }
        ofSort(res,&FitEquation::pairCompare);
        return res;
    };
    
    eqStruct getFirsts(int num,int axe,float pruneOrder = 10){
        eqStruct res ;
        
        if(num <=0)num = equation[axe].size();
        int i =0;
        float last;
        ofSort(equation[axe],&FitEquation::pairCompare);
        for(eqStruct::iterator it = equation[axe].begin() ; i <num && it!=equation[axe].end() ; ++it,i++){
            if(i==0 || pruneOrder ==0 || last/abs(it->first)<pruneOrder){
            res.push_back(*it);
            last = abs(it->second);

            }
            else break;
            
        }
        return res;
    }
    
    void clear(){
        for(int i = 0;i<3 ; i++){
            equation[i].clear();
        }
    }
    
    string toString(int axe,int firsts){
        
        string res;
        
        eqStruct curEq;
        curEq = getFirsts(firsts, axe);
        bool begin = true;
        for(eqStruct::iterator it = curEq.begin() ; it != curEq.end() ; ++it){
         if(!begin)res+= " \t";
            res+=(float)it->second>0?"+":"";
            res += ofToString((float)it->second,3) + " ";
            res += paramNames[it->first];
            
            begin = false;
            
            
        }
        
        
        return res;
    }
    string toString(int firsts){
        string res ;
        for(int i = 0 ; i < 3 ; i++){
            res += toString(i,firsts);
            res+="\n";
        }
        return res;
    }
    
    // This function returns true if the first pair is "less"
    // than the second one according to some metric
    // In this case, we say the first pair is "less" if the first element of the first pair
    // is less than the first element of the second pair
    static bool pairCompare(const eqElem& firstElem, const eqElem& secondElem) {
        return abs(firstElem.second) > abs(secondElem.second);
        
    }

    
};




#endif
