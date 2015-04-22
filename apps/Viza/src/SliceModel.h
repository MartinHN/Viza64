//
//  SliceModel.h
//  ViZa
//
//  Created by martin hermant on 16/12/14.
//
//

#ifndef __ViZa__SliceModel__
#define __ViZa__SliceModel__

#include <iostream>


#include "ofxNonLinearFit.h"
#include "DSP.h"

namespace ofxNonLinearFit {
	namespace Models {
        
        typedef struct Data{
            double x,y,z;
            Data():x(0),y(0),z(0){};
            Data(ofVec3f &v){
                x=v.x;
                y=v.y;
                z=v.z;
            }
            Data(float _x,float _y,float _z):x(_x),y(_y),z(_z){}
            Data(double _x,double _y,double _z):x(_x),y(_y),z(_z){}
        }Data;
		struct SliceModelPoint {
			vector<double> descriptorsDiff;
			Data angle;

		};
        
		class SliceModel : public Base<SliceModelPoint, SliceModel> {
		public:
			typedef SliceModelPoint DataPoint;
            
            vector<float>  parametersf;
            
            int size = 0;
            int type = 0;
			unsigned int getParameterCount() const override;
			double getResidual(DataPoint) const override;
			void evaluate(DataPoint &) const override;
            
//			/// Override this if you would like to interpret the 6 pose parameters in a non-default way
			virtual void cacheModel() override;

			Data evaluate(const vector<double> & x) const;
            Data getAngle(Data & v)const ;
		
            
		};
	}
}

#endif /* defined(__ViZa__SliceModel__) */
