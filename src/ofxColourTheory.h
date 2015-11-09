/*
 *  ofxColourTheory.h
 *  Partial port of toxilib colour theory
 http://toxiclibs.org/
 *
 *  Created by Andreas Borg on 07/07/2012
 *  
 */

#ifndef _ofxColourTheory
#define _ofxColourTheory

#include "ofMain.h"


typedef enum ColourStrategy{
    CT_SINGLE_COMPLEMENT,
    CT_COMPLEMENTARY,
    CT_SPLIT_COMPLEMENTARY,
    CT_LEFT_SPLIT_COMPLEMENTARY,
    CT_RIGHT_SPLIT_COMPLEMENTARY,
    CT_ANALOGOUS,
    CT_MONOCHROME,
    CT_TRIAD,
    CT_TETRAD,
    CT_COMPOUND
}ColourStrategy;

typedef struct ColourConstraints{
    ofVec2f hueConstraint;
    ofVec2f saturationConstraint;
    ofVec2f brightnessConstraint;
    ofVec2f alphaConstraint;
    ofVec2f black;
    ofVec2f white;
    string name;
}ColourConstraints;



/**
 * Shade definition: saturation 30-70%, brightness: 90-100%
 LIGHT = new ColorRange(null, new FloatRange( 0.3f, 0.7f), new FloatRange(0.9f, 1.0f), null, new FloatRange(0.15f, 0.30f), null, "light");

 * Shade definition: saturation 70-100%, brightness: 15-40%
 DARK = new ColorRange(null, new FloatRange(0.7f, 1.0f), new FloatRange(0.15f, 0.4f), null, null,  new FloatRange(0.5f, 0.75f), "dark");

 * Shade definition: saturation 80-100%, brightness: 80-100%
 BRIGHT = new ColorRange(null,new FloatRange(0.8f, 1.0f), new FloatRange(0.8f, 1.0f), "bright");

 * Shade definition: saturation 15-30%, brightness: 70-100%
 WEAK = new ColorRange(null, new FloatRange(0.15f, 0.3f), new FloatRange(0.7f, 1.0f), null, new FloatRange(0.2f, 0.2f), null, "weak");

 * Shade definition: saturation 25-35%, brightness: 30-70%
 NEUTRAL = new ColorRange(null,new FloatRange(0.25f, 0.35f), new FloatRange(0.3f, 0.7f), null, new FloatRange(0.15f, 0.15f), new FloatRange(0.9f, 1), "neutral");

 * Shade definition: saturation 40-80%, brightness: 80-100%
 FRESH = new ColorRange(null, new FloatRange( 0.4f, 0.8f), new FloatRange(0.8f, 1.0f), null, new FloatRange(0.05f, 0.3f), new FloatRange(0.8f, 1.0f), "fresh");

 * Shade definition: saturation 20-30%, brightness: 60-90%
SOFT = new ColorRange(null, new FloatRange(0.2f, 0.3f), new FloatRange(0.6f, 0.9f), null, new FloatRange(0.05f, 0.15f), new FloatRange(0.6f, 0.9f), "soft");

 * Shade definition: saturation 90-100%, brightness: 40-100%
 HARD = new ColorRange(null, new FloatRange( 0.9f, 1.0f), new FloatRange(0.4f, 1.0f), "hard");

 * Shade definition: saturation 60-90%, brightness: 40-90%
 WARM = new ColorRange(null, new FloatRange(0.6f, 0.9f), new FloatRange(0.4f, 0.9f), null, new FloatRange(0.2f,0.2f), new FloatRange(0.8f, 1.0f), "warm");

 * Shade definition: saturation 5-20%, brightness: 90-100%
COOL = new ColorRange(null, new FloatRange( 0.05f, 0.2f), new FloatRange(0.9f, 1.0f), null, null, new FloatRange(0.95f, 1.0f), "cool");

 * Shade definition: saturation 90-100%, brightness: 20-35% or 80-100%
 INTENSE = new ColorRange(null,new FloatRange(0.9f, 1.0f), new FloatRange(0.2f, 0.35f), "intense").addBrightnessRange(new FloatRange(0.8f, 1.0f));
*/

typedef enum ColourShade{
    CT_LIGHT,
    CT_DARK,
    CT_BRIGHT,
    CT_WEAK,
    CT_NEUTRAL,
    CT_FRESH,
    CT_SOFT,
    CT_HARD,
    CT_WARM,
    CT_COOL,
    CT_INTENSE
    
}ColourShade;
/**
 * Default hue variance for {@link #getColor(ReadonlyTColor, float)}
 */
#define CT_DEFAULT_VARIANCE = 0.035f;
    




class ofxColourTheory {
	
  public:
	
	ofxColourTheory();
    //returns default number of colours from that strategy
	static vector<ofColor> createColoursFromStrategy(ofColor col,ColourStrategy cs);
    
    
    //returns desired number of colours within given strategy range
	static vector<ofColor> createRangeFromStrategy(ofColor col,int num, ColourStrategy cs,float variance = 0.05f);
    
    
    
    static  vector<ofColor> sampleColourRange(ofImage img, int limit);
    static  vector<ofColor> createRangeFromAnalogous(ofColor col);
    static  vector<ofColor> createRangeFromComplementary(ofColor col);
    static  vector<ofColor> createRangeFromSplitComplementary(ofColor src);
    static  vector<ofColor> createRangeFromLeftSplitComplementary(ofColor src);
    static  vector<ofColor> createRangeFromRightSplitComplementary(ofColor src);
    static  vector<ofColor> createRangeFromCompound(ofColor src);
    static  vector<ofColor> createRangeFromMonochrome(ofColor src);
    
   static  ofColor getColor(float variance,ColourConstraints  cr);
    
   static  ofColor getColor(float variance,ofColor * c=0, ofVec2f hueConstraint = ofVec2f(0.0,1.0),ofVec2f saturationConstraint = ofVec2f(0.0,1.0),ofVec2f brightnessConstraint = ofVec2f(0.0,1.0),ofVec2f alphaConstraint = ofVec2f(0.0,1.0));
   static  vector<ofColor> getColors(ofColor c, int num, float variance, ofVec2f hueConstraint = ofVec2f(0.0,1.0),ofVec2f saturationConstraint = ofVec2f(0.0,1.0),ofVec2f brightnessConstraint = ofVec2f(0.0,1.0),ofVec2f alphaConstraint = ofVec2f(0.0,1.0));
    
   static  vector<ofColor> getRange(vector<ofColor> cols, int num, float variance, ofVec2f hueConstraint = ofVec2f(0.0,1.0),ofVec2f saturationConstraint = ofVec2f(0.0,1.0),ofVec2f brightnessConstraint = ofVec2f(0.0,1.0),ofVec2f alphaConstraint = ofVec2f(0.0,1.0));
    
    
   static  float clipNormalized(float a) {
        if (a < 0) {
            return 0;
        } else if (a > 1) {
            return 1;
        }
        return a;
    };
	
    
    static float normalizedRandom() {
        return abs(ofRandomf() * 2.0f) - 1.0f;
    }
    
    //updated Aug 30, 2015 to keep 0-1 range
    static float luminance(ofColor col) {
        float tot = 255* 0.299f + 255* 0.587f+255 * 0.114f;
        return (col.r * 0.299f + col.g * 0.587f + col.b * 0.114f)/tot;
    }
    
    
    static void invert(ofColor col) {
        col.set(255-col.r,255-col.g,255-col.b);
    }
    
    
    
   static  vector<ofVec2f> getRYB_WHEEL(){
        vector<ofVec2f> RYB_WHEEL;
        RYB_WHEEL.push_back(ofVec2f(0, 0)); 
        RYB_WHEEL.push_back(ofVec2f(15, 8)); 
        RYB_WHEEL.push_back(ofVec2f(30, 17));
        RYB_WHEEL.push_back(ofVec2f(45, 26));
        RYB_WHEEL.push_back(ofVec2f(60, 34));
        RYB_WHEEL.push_back(ofVec2f(75, 41));
        RYB_WHEEL.push_back(ofVec2f(90, 48));
        RYB_WHEEL.push_back(ofVec2f(105, 54)); 
        RYB_WHEEL.push_back(ofVec2f(120, 60));
        RYB_WHEEL.push_back(ofVec2f(135, 81));
        RYB_WHEEL.push_back(ofVec2f(150, 103)); 
        RYB_WHEEL.push_back(ofVec2f(165, 123));
        RYB_WHEEL.push_back(ofVec2f(180, 138));
        RYB_WHEEL.push_back(ofVec2f(195, 155));
        RYB_WHEEL.push_back(ofVec2f(210, 171));
        RYB_WHEEL.push_back(ofVec2f(225, 187));
        RYB_WHEEL.push_back(ofVec2f(240, 204));
        RYB_WHEEL.push_back(ofVec2f(255, 219));
        RYB_WHEEL.push_back(ofVec2f(270, 234));
        RYB_WHEEL.push_back(ofVec2f(285, 251));
        RYB_WHEEL.push_back(ofVec2f(300, 267));
        RYB_WHEEL.push_back(ofVec2f(315, 282));
        RYB_WHEEL.push_back(ofVec2f(330, 298));
        RYB_WHEEL.push_back(ofVec2f(345, 329));
        RYB_WHEEL.push_back(ofVec2f(360, 0));
        
        return RYB_WHEEL;
    }
    
    /**
     * Rotates the color by x degrees along the <a
     * href="http://en.wikipedia.org/wiki/RYB_color_model">RYB color wheel</a>
     * 
     * @param theta
     * @return itself
     
     
     
     OpenFrameworks is using 0-255 for HBS range, not 0-1. Need to convert.
     
     */
     static ofColor rotateRYB(ofColor col,int theta) {

        float h = (float) col.getHue()/255.0 * 360;
        vector<float> hsb;
        hsb.push_back((float) col.getHue()/255.0) ;
        hsb.push_back((float) col.getSaturation()/255.0) ;
        hsb.push_back((float) col.getBrightness()/255.0) ;
        theta %= 360;
        
        float resultHue = 0;
        
        vector<ofVec2f> RYB_WHEEL = getRYB_WHEEL();
                  
        for (int i = 0; i < RYB_WHEEL.size() - 1; i++) {
            ofVec2f p = RYB_WHEEL[i];
            ofVec2f q = RYB_WHEEL[i + 1];
            if (q.y < p.y) {
                q.y += 360;
            }
            if (p.y <= h && h <= q.y) {
                resultHue = p.x + (q.x - p.x) * (h - p.y) / (q.y - p.y);
                break;
            }
        }
        
        //fmod = %, ie remainder
        
        // And the user-given angle (e.g. complement).
        resultHue = fmod((resultHue + theta),360);
        
        // For the given angle, find out what hue is
        // located there on the artistic color wheel.
        for (int i = 0; i < RYB_WHEEL.size() - 1; i++) {
            ofVec2f p = RYB_WHEEL[i];
            ofVec2f q = RYB_WHEEL[i + 1];
            if (q.y < p.y) {
                q.y += 360;
            }
            if (p.x <= resultHue && resultHue <= q.x) {
                h = p.y + (q.y - p.y) * (resultHue - p.x) / (q.x - p.x);
                break;
            }
        }
        
       // col.setHsb(<#float hue#>, <#float saturation#>, <#float brightness#>)
        hsb[0] = fmod(h, 360) / 360.0f;
        
        ofColor newCol;
        newCol.setHsb(hsb[0]*255, hsb[1]*255, hsb[2]*255);
        return newCol;
    }
    
    static ofColor getComplement(ofColor col){
        return rotateRYB(col,180);
    }
    

    static float wrap(float x, float min, float threshold,float plus) {
        if (x - min < threshold) {
            return x + plus;
        } else {
            return x - min;
        }
    }
    /**
     * Sorts the list by relative distance to each predecessor, starting with
     * the darkest color in the list.
     * 
     * @param isReversed
     *            true, if list is to be sorted in reverse.
     * @return itself
     */
    
    static void sortByDistance(vector<ofColor> &colors) {
        if (colors.size() == 0) {
            return;
        }
        int totalCount = colors.size();
        ofColor root = getDarkest(colors);
        // put it in the sorted list as starting element.
        vector<ofColor> sorted;
        sorted.push_back(root);
        
        // Remove the darkest color from the stack,
        
        vector<ofColor> stack(colors);
         vector<ofColor>::iterator it =  std::find(stack.begin(), stack.end(), root);
       // ofLog()<<"erase darkest "<<(*it)<<endl;
        //if(it != stack.end()){
           stack.erase(it);
       // }
        
        
        // Now find the color in the stack closest to that color.
        // Take this color from the stack and add it to the sorted list.
        // Now find the color closest to that color, etc.
        int sortedCount = 0;
        
        while (stack.size() > 1) {
            ofColor closest = stack[0];
            ofColor lastSorted = sorted[sortedCount];
            float distance = distanceBetween(closest, lastSorted);
           // ofLog()<<"searching: "<<endl;
            int foundId=0;
            for (int i = stack.size() - 1; i >= 0; i--) {
                ofColor c = stack[i];
                float d = distanceBetween(c, lastSorted);
              //  ofLog()<<"dist: "<<d<< " stack.size()  "<<stack.size()<< " sortedCount "<<sortedCount<<" totalCount "<<totalCount <<endl;
                if (d < distance) {
                    closest = c;
                    distance = d;
                    foundId=i;
                }
            }
            sorted.push_back(closest);
            stack.erase(stack.begin()+foundId);
            
            sortedCount++;
        }
        sorted.push_back(stack[0]);
       
        colors = sorted;
        
    }
	/**
     * Finds and returns the darkest color of the list.
     * 
     * @return darkest color or null if there're no entries yet.
     */
    static ofColor getDarkest(vector<ofColor> &colors) {
        ofColor darkest;
        float minBrightness = FLT_MAX;
        for (int i=0;i<colors.size();i++) {
            ofColor c = colors[i];
            float luma = luminance(c);
            if (luma < minBrightness) {
                darkest = c;
                minBrightness = luma;
            }
        }
        return darkest;
    }
    
    /**
     * Finds and returns the lightest (luminance) color of the list.
     * 
     * @return lightest color or null, if there're no entries yet.
     */
    static ofColor getLightest(vector<ofColor> &colors) {
        ofColor lightest;
        float maxBrightness = FLT_MIN;
        for (int i=0;i<colors.size();i++) {
            ofColor c = colors[i];
            float luma = luminance(c);
            if (luma > maxBrightness) {
                lightest = c;
                maxBrightness = luma;
            }
        }
        return lightest;
    }
    
    static ofColor getRandom(vector<ofColor> &colors) {
        return colors[ofRandom(colors.size()-1)];
    }
    
    /**
     * Returns a reversed copy of the current list.
     * 
     * @return reversed copy of the list
     */
    static void reverse(vector<ofColor> &colors) {
        //return new ColorList(colors).reverse();
    }
    
    /**
     * Inverts all colors in the list.
     * 
     * @return itself
     */
    static void invert(vector<ofColor> &colors) {
        for (int i=0;i<colors.size();i++) {
            invert(colors[i]);
        }
    }
    

    
    static float distanceBetween(ofColor a,ofColor b) {
        float hue = a.getHue()/255.0f *TWO_PI;
        float hue2 = b.getHue()/255.0f * TWO_PI;
        ofVec3f v1((cos(hue) * a.getSaturation()/255.0f),
                                     (sin(hue) * a.getSaturation()/255.0f), a.getBrightness()/255.0f);
        ofVec3f v2((cos(hue2) * b.getSaturation()/255.0f),
                             (sin(hue2) * b.getSaturation()/255.0f), b.getBrightness()/255.0f);
        return v1.distance(v2);
    }
    
    static ColourConstraints getColourConstraints(ColourShade shade){
        
        ColourConstraints cr;
        switch (shade) {
            case CT_LIGHT:
                cr.hueConstraint = ofVec2f(0.0f, 1.0f);
                cr.saturationConstraint = ofVec2f(0.3f, 0.7f);
                cr.brightnessConstraint = ofVec2f(0.9f, 1.0f);
                cr.alphaConstraint = ofVec2f(1.0f, 1.0f);
                cr.black = ofVec2f(0.15f, 0.30f);
                cr.white  = ofVec2f(1.0f, 1.0f);
                cr.name = "light";
                break;
            case CT_DARK:
                cr.hueConstraint = ofVec2f(0.0f, 1.0f);
                cr.saturationConstraint = ofVec2f(0.7f, 1.0f);
                cr.brightnessConstraint = ofVec2f(0.15f, 0.4f);
                cr.alphaConstraint = ofVec2f(1.0f, 1.0f);
                cr.black = ofVec2f(0.0f, 0.0f);
                cr.white  = ofVec2f(0.5f, 0.75f);
                cr.name = "dark";
                break;   
           case CT_BRIGHT:
			   cr.hueConstraint = ofVec2f(0.0f, 1.0f); //default if null
			   cr.saturationConstraint = ofVec2f(0.8f, 1.0f);
               cr.brightnessConstraint = ofVec2f(0.8f, 1.0f);
               cr.alphaConstraint = ofVec2f(1.0f, 1.0f); //default
               cr.black = ofVec2f(0.0f, 0.0f); //default
               cr.white  = ofVec2f(1.0f, 1.0f);
               cr.name = "bright";
                break;  
            case CT_WEAK:
                cr.hueConstraint = ofVec2f(0.0f, 1.0f); //default if null
			   cr.saturationConstraint = ofVec2f(0.15f, 0.3f);
               cr.brightnessConstraint = ofVec2f(0.7f, 1.0f);
               cr.alphaConstraint = ofVec2f(1.0f, 1.0f); //default
               cr.black = ofVec2f(0.2f, 0.2f); //default
               cr.white  = ofVec2f(1.0f, 1.0f);
               cr.name = "weak";
                break;   
            case CT_NEUTRAL:
               cr.hueConstraint = ofVec2f(0.0f, 1.0f); //default if null
			   cr.saturationConstraint = ofVec2f(0.25f, 0.35f);
               cr.brightnessConstraint = ofVec2f(0.3f, 0.7f);
               cr.alphaConstraint = ofVec2f(1.0f, 1.0f); //default
               cr.black = ofVec2f(0.15f, 0.15f); //default
               cr.white  = ofVec2f(0.9f, 1.0f);
               cr.name = "neutral";
                break;   
            case CT_FRESH:
                cr.hueConstraint = ofVec2f(0.0f, 1.0f); //default if null
			   cr.saturationConstraint = ofVec2f(0.4f, 0.8f);
               cr.brightnessConstraint = ofVec2f(0.8f, 1.0f);
               cr.alphaConstraint = ofVec2f(1.0f, 1.0f); //default
               cr.black = ofVec2f(0.05f, 0.3f); //default
               cr.white  = ofVec2f(0.8f, 1.0f);
               cr.name = "fresh";
                break; 
           case CT_SOFT:
                cr.hueConstraint = ofVec2f(0.0f, 1.0f); //default if null
			   cr.saturationConstraint = ofVec2f(0.2f, 0.3f);
               cr.brightnessConstraint = ofVec2f(0.6f, 0.9f);
               cr.alphaConstraint = ofVec2f(1.0f, 1.0f); //default
               cr.black = ofVec2f(0.05f, 0.15f); //default
               cr.white  = ofVec2f(0.6f, 0.9f);
               cr.name = "soft";
                break;  
            case CT_HARD:
                cr.hueConstraint = ofVec2f(0.0f, 1.0f); //default if null
			   cr.saturationConstraint = ofVec2f(0.9f, 1.0f);
               cr.brightnessConstraint = ofVec2f(0.4f, 1.0f);
               cr.alphaConstraint = ofVec2f(1.0f, 1.0f); //default
               cr.black = ofVec2f(0.0f, 0.0f); 
               cr.white  = ofVec2f(1.0f, 1.0f);
               cr.name = "hard";
                break;   
            case CT_WARM:
                cr.hueConstraint = ofVec2f(0.0f, 1.0f); //default if null
			   cr.saturationConstraint = ofVec2f(0.6f, 0.9f);
               cr.brightnessConstraint = ofVec2f(0.4f, 0.9f);
               cr.alphaConstraint = ofVec2f(1.0f, 1.0f); //default
               cr.black = ofVec2f(0.2f, 0.2f); //default
               cr.white  = ofVec2f(0.8f, 1.0f);
               cr.name = "warm";
                break;   
            case CT_COOL:
                cr.hueConstraint = ofVec2f(0.0f, 1.0f); //default if null
			   cr.saturationConstraint = ofVec2f(0.05f, 0.2f);
               cr.brightnessConstraint = ofVec2f(0.9f, 1.0f);
               cr.alphaConstraint = ofVec2f(1.0f, 1.0f); //default
               cr.black = ofVec2f(0.0f, 0.0f); //default
               cr.white  = ofVec2f(0.95f, 1.0f);
               cr.name = "cool";
                break;   
            case CT_INTENSE:
                cr.hueConstraint = ofVec2f(0.0f, 1.0f); //default if null
			   cr.saturationConstraint = ofVec2f(0.9f, 1.0f);
               cr.brightnessConstraint = ofVec2f(0.2f, 0.35f);
               cr.alphaConstraint = ofVec2f(1.0f, 1.0f); //default
               cr.black = ofVec2f(0.0f, 0.0f); //default
               cr.white  = ofVec2f(1.0f, 1.0f);
               cr.name = "intense";
                break; 
            default:
				printf("range choice not available\n");
                break;
        }
        return cr;
    }
    
    
    //util funcs for converting between web standard colour format
    /*
    Eg.
    ofColor hCol;
    ofxColourTheory::hexToColor(hCol,"6400FF");
    cout<<ofxColourTheory::colorToHex(ofColor(100,0,255))<<" "<< hCol<<endl;
    */
    
    static int stringToHex(string hex){
        int aHex;
        stringstream convert(hex);
        convert >> std::hex >> aHex;
        return aHex;
    }
    
    static void hexToColor(ofColor &col,string hex){
        string r = hex.substr(0,2);
        int ri = ofxColourTheory::stringToHex(r);
        string g = hex.substr(2,2);
        int gi = ofxColourTheory::stringToHex(g);
        string b = hex.substr(4,2);
        int bi = ofxColourTheory::stringToHex(b);
        col.set(ri,gi,bi);
    }
    
    static string colorToHex(ofColor col){
        return ofToUpper(ofToHex(col.r)+ofToHex(col.g)+ofToHex(col.b));
    }
};

#endif
