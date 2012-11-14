/*
 *  ofxColourTheory.cpp
 *  mural
 *
 *  Created by Andreas Borg on 07/07/2012
 *  Copyright 2012 __MyCompanyName__. All rights reserved.
 *
 */

#include "ofxColourTheory.h"

ofxColourTheory::ofxColourTheory(){};


vector<ofColor> ofxColourTheory::createColoursFromStrategy(ofColor col,ColourStrategy cs){
    vector<ofColor> list;
    switch (cs) {
        case CT_ANALOGOUS:
            list = createRangeFromAnalogous(col);
            break;
        case CT_COMPLEMENTARY:
            list = createRangeFromComplementary(col);
            break;
        case CT_SPLIT_COMPLEMENTARY:
            list = createRangeFromSplitComplementary(col);
            break;
        case CT_LEFT_SPLIT_COMPLEMENTARY:
            list = createRangeFromLeftSplitComplementary(col);
            break;   
        case CT_RIGHT_SPLIT_COMPLEMENTARY:
            list = createRangeFromRightSplitComplementary(col);
            break;  
        case CT_COMPOUND:
            list = createRangeFromCompound(col);
            break;  
        case CT_MONOCHROME:
            list = createRangeFromMonochrome(col);
            break;   
            
        default:
            break;
    }
    return list;
};


//------------------------------------------------------------------
vector<ofColor> ofxColourTheory::createRangeFromStrategy(ofColor col,int num, ColourStrategy cs,float variance ){
    vector<ofColor> list = ofxColourTheory::createColoursFromStrategy(col, cs);       
    vector<ofColor> range = getRange(list, num, variance);
    return range;
	
}




vector<ofColor> ofxColourTheory::sampleColourRange(ofImage img, int limit){
    vector<ofColor> colList;
    
    return colList;
	
}

vector<ofColor> ofxColourTheory::createRangeFromAnalogous(ofColor src){
    
    
    vector<ofVec2f> tones;
    tones.push_back(ofVec2f(1, 2.2f));
    tones.push_back(ofVec2f(2, 1));
    tones.push_back(ofVec2f(-1, -0.5f));
    tones.push_back(ofVec2f(-2, 1));
    
    float contrast = 0.25f;
    float theta = 10 *PI / 180.0;
        
    contrast = clipNormalized(contrast);
    
    vector<ofColor> colList;
    colList.push_back(src);
    
    
    for (int i=0;i<tones.size();i++) {
        ofColor c = rotateRYB(src,(int) (theta * tones[i].x));
        float t = 0.44f - tones[i].y * 0.1f;
        if ((float) src.getBrightness()/255.0 - contrast * tones[i].y < t) {
            c.setBrightness(t*255.0);
        } else {
            c.setBrightness(src.getBrightness() - (contrast * tones[i].y)*255.0);
        }
        c.setSaturation(c.getSaturation()-0.05f*255.0);
        colList.push_back(c);
    }
    return colList;
}





vector<ofColor> ofxColourTheory::createRangeFromComplementary(ofColor src) {
    vector<ofColor> colList;
    colList.push_back(src);
    // # A contrasting color: much darker or lighter than the original.
    ofColor c = ofColor(src);
    if (c.getBrightness() > 0.4*255.0) {
        c.setBrightness(0.1f *255.0f+ c.getBrightness() * 0.25f);
    } else {
        c.setBrightness(255.0f - c.getBrightness() * 0.25f);
    }
     colList.push_back(c);
    
    // A soft supporting color: lighter and less saturated.
    c = ofColor(src);
    c.setBrightness(c.getBrightness() + 0.3f*255.0f);
    c.setSaturation(0.1f *255.0f+ c.getSaturation() * 0.3f);
    colList.push_back(c);
    
    /// A contrasting complement: very dark or very light.
    c = getComplement(src);
    
    if (c.getBrightness() > 0.3f *255.0f) {
        c.setBrightness(0.1f *255.0f+ c.getBrightness() * 0.25f);
    } else {
        c.setBrightness(1.0f*255.0f - c.getBrightness() * 0.25f);
    }
    colList.push_back(c);
    
    // The complement and a light supporting variant.
     colList.push_back(getComplement(src));
    
    c = getComplement(src);
    c.setBrightness(c.getBrightness() + 0.3f*255.0f);
    c.setSaturation(0.1f*255.0f + c.getSaturation() * 0.25f);
    colList.push_back(c);
    return colList;
}
vector<ofColor> ofxColourTheory::createRangeFromSplitComplementary(ofColor src) {
    vector<ofColor> colList;
    colList.push_back(src);
    
    
    ofColor a = rotateRYB(src,150);
    a.setBrightness(a.getBrightness()+0.1f*255.0f);
    colList.push_back(a);
    
    ofColor b = rotateRYB(src,210);
    b.setBrightness(b.getBrightness()+0.1f*255.0f);
    colList.push_back(b);
    
    
    return colList;
}

vector<ofColor> ofxColourTheory::createRangeFromLeftSplitComplementary(ofColor src) {
    ofColor left = getComplement(src);
    left = rotateRYB(left,-30);
    left.setBrightness(left.getBrightness()+0.1f*255.0f);
    vector<ofColor> colList = createRangeFromComplementary(src);
    
    for (int i = 3; i < 6; i++) {
        ofColor c = colList[i];
        c.setHue(left.getHue());
    }
    return colList;
}
vector<ofColor> ofxColourTheory::createRangeFromRightSplitComplementary(ofColor src) {
    ofColor right = getComplement(src);
    right = rotateRYB(right,30);
    right.setBrightness(right.getBrightness()+0.1f*255.0f);
    vector<ofColor> colList = createRangeFromComplementary(src);
    
    for (int i = 3; i < 6; i++) {
        ofColor c = colList[i];
        c.setHue(right.getHue());
    }
    return colList;
}



vector<ofColor> ofxColourTheory::createRangeFromCompound(ofColor src) {
    vector<ofColor> colList;
    colList.push_back(src);
    bool isFlipped = ofRandomf()>.5;
    
    int direction = isFlipped ? -1 : 1;
    
    ofColor c = rotateRYB(src,30 * direction);
    c.setBrightness(wrap(c.getBrightness()/255.0f, 0.25f, 0.6f, 0.25f)*255.0f);
    colList.push_back(c);
    
    c = rotateRYB(src,30 * direction);
    c.setSaturation(wrap(c.getSaturation()/255.0f, 0.4f, 0.1f, 0.4f)*255.0f);
    c.setBrightness(wrap(c.getBrightness()/255.0f, 0.4f, 0.2f, 0.4f)*255.0f);
    colList.push_back(c);
    
    c = rotateRYB(src,160 * direction);
    c.setSaturation(wrap(c.getSaturation()/255.0f, 0.25f, 0.1f, 0.25f)*255.0f);
    c.setBrightness(max(0.2f*255, c.getBrightness()*255));
    colList.push_back(c);
    
    c = rotateRYB(src,150 * direction);
    c.setSaturation(wrap(c.getSaturation()/255.0f, 0.1f, 0.8f, 0.1f)*255.0f);
    c.setBrightness(wrap(c.getBrightness()/255.0f, 0.3f, 0.6f, 0.3f)*255.0f);
     colList.push_back(c);
    
    c = rotateRYB(src,150 * direction);
    c.setSaturation(wrap(c.getSaturation()/255.0f, 0.1f, 0.8f, 0.1f)*255.0f);
    c.setBrightness(wrap(c.getBrightness()/255.0f, 0.4f, 0.2f, 0.4f)*255.0f);
     
     
    // colors.add(c);
    
    return colList;
}


vector<ofColor> ofxColourTheory::createRangeFromMonochrome(ofColor src) {
    vector<ofColor> colList;
    
    colList.push_back(src);
 
    ofColor c(src.r,src.g,src.b);
    c.setBrightness(wrap((float)c.getBrightness()/255.0f, 0.5f, 0.2f, 0.3f)*255.0f);
    c.setSaturation(wrap((float)c.getSaturation()/255.0f, 0.3f, 0.1f, 0.3f)*255.0f);
    colList.push_back(c);
    
    
    c.set(src.r,src.g,src.b);
    c.setBrightness(wrap((float)c.getBrightness()/255.0f, 0.2f, 0.2f, 0.6f)*255.0);
    colList.push_back(c);
    
    
    c.set(src.r,src.g,src.b);
    
    float a = 0.2f;
    float b = (float)c.getBrightness()/2555.0f + (1 - (float)c.getBrightness()/2555.0f) * 0.2f;
    float bright = max(a,b)*255.0f;
    c.setBrightness(bright);
    c.setSaturation(wrap((float)c.getSaturation()/255.0f, 0.3f, 0.1f, 0.3f)*255.0f);
    colList.push_back(c);
        
    c.set(src.r,src.g,src.b);
    c.setBrightness(wrap((float)c.getBrightness()/255.0f, 0.5f, 0.2f, 0.3f)*255.0f);
    colList.push_back(c);
    
    return colList;
}


ofColor ofxColourTheory::getColor(float variance,ColourConstraints  cr){
    return ofxColourTheory::getColor(variance,0, cr.hueConstraint,cr.saturationConstraint,cr.brightnessConstraint,cr.alphaConstraint);

};

/**
 * Creates a new color based on the constraints defined in the range. If an
 * input color is specified, the method will use the hue of that color and
 * the given variance to create a shade of a hue within the tolerance.
 * 
 * @param c
 * @param variance
 * @return color
 */
ofColor ofxColourTheory::getColor(float variance,ofColor * c, ofVec2f hueConstraint,ofVec2f saturationConstraint,ofVec2f brightnessConstraint,ofVec2f alphaConstraint) {
    float h, s, b, a;
    if (c != 0) {
       
        if ((*c) == ofColor::black) {
            ofColor nc;
            //was using black.pickRandom here...not sure what that means..see toxi ColorRange
            nc.setHsb(c->getHue(), 0, 0, c->a);
            return nc;
            
        } else if ((*c) ==ofColor::white) {
            ofColor nc;
            nc.setHsb(c->getHue(), 0, 255, c->a);
            return nc;
        }
        if ((*c)==ofColor::gray) {
            ofColor nc;
            if(ofRandomf()>0.5){
                nc.setHsb(c->getHue(), 0, 0, c->a);
            }else{
                nc.setHsb(c->getHue(), 0, 255, c->a);
            }
            
            return nc;
        }
        h = c->getHue() + variance * normalizedRandom()*255.0f;
        
        a = c->a;
        
    } else {
        h = ofRandom(hueConstraint.x*255.0f,hueConstraint.y*255.0f);
        a = ofRandom(alphaConstraint.x*255.0f,alphaConstraint.y*255.0f);
    }
    s = ofRandom(saturationConstraint.x*255.0f,saturationConstraint.y*255.0f);
    b = ofRandom(brightnessConstraint.x*255.0f,brightnessConstraint.y*255.0f);
    if(h>255){
        //cap
        h = h-255;
    }
    if(h<0){
        h = 255+h;
    }
    
    
   // 
    ofColor nc;
    nc.setHsb(h,s,b,a);
    
    
    
    //ofLog()<<"nc: "<<nc<<" hueConstraint "<<hueConstraint<<" saturationConstraint "<<saturationConstraint <<endl;
    
    
    return nc;
}

vector<ofColor> ofxColourTheory::getColors(ofColor c, int num, float variance, ofVec2f hueConstraint,ofVec2f saturationConstraint,ofVec2f brightnessConstraint,ofVec2f alphaConstraint) {
    //ofLog()<<"getColors num: "<<num<<" org hue "<<c.getHue()<<endl;
    vector<ofColor> list;
    for (int i = 0; i < num; i++) {
        list.push_back(getColor(variance,&c,hueConstraint,saturationConstraint,brightnessConstraint,alphaConstraint));
    }
    return list;
}

vector<ofColor> ofxColourTheory::getRange(vector<ofColor> cols, int num, float variance, ofVec2f hueConstraint,ofVec2f saturationConstraint,ofVec2f brightnessConstraint,ofVec2f alphaConstraint) {
    vector<ofColor> list;
    int numPerRange = (int)floor(float(num/cols.size()));
    for (int i = 0; i < cols.size()-1; i++) {
        //check out this vector concat!
        //todo..fix vector length
        vector<ofColor> b = getColors(cols[i],numPerRange,variance,hueConstraint,saturationConstraint,brightnessConstraint,alphaConstraint);
        list.insert(list.end(), b.begin(), b.end());
    
    }
    
    //add last to fill unevenly split range, eg. 33,33,33,34 to get 100
    int i = cols.size()-1;
    int remainingNum = numPerRange + num-numPerRange*cols.size();
   // ofLog()<<"numPerRange "<<numPerRange<<" remainingNum "<<remainingNum<<endl;
    vector<ofColor> b = getColors(cols[i],remainingNum,variance,hueConstraint,saturationConstraint,brightnessConstraint,alphaConstraint);
    list.insert(list.end(), b.begin(), b.end());
    return list;
}



