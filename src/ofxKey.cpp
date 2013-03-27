/*
 *  ofxKey.cpp
 *
 *  Copyright 2010 Patricio Gonzalez Vivo http://www.patriciogonzalezvivo.com
 *	All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the author nor the names of its contributors
 *       may be used to endorse or promote products derived from this software
 *       without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * ***********************************************************************/

#include "ofxKey.h"

ofxKey::ofxKey(){
}

ofxKey::ofxKey(string _letter, float _radio, float _angle, float _width, float _height){
	letter = _letter;
	
	radio = _radio;
    angle = _angle;
	
	width = _width;
    height = _height;
	
	pressed = false;
	
	scaleW = 1/width;
	scaleH = 1/height;
}

void ofxKey::scale(float _scale){
    width *= _scale;
    height *= _scale;
    radio *= _scale;
    
    position.x = radio * cos(angle + *keyboardNorth);
	position.y = radio * sin(angle + *keyboardNorth);
	position += *keyboardCenter;
}

void ofxKey::update(){	
	position.x = radio * cos(angle + *keyboardNorth);
	position.y = radio * sin(angle + *keyboardNorth);
	position += *keyboardCenter;
}

void ofxKey::draw(){
	update();
	
    if (pressed){
        fg.lerp(*foregroundColor, 0.1);
        bg.lerp(*backgroundColor, 0.1);
    }
    else {
        fg = *foregroundColor;
        bg = *backgroundColor;    
    }
    
	ofPushMatrix();
		ofTranslate(position.x, position.y);
		ofRotateZ(ofRadToDeg(*keyboardNorth));
		
		ofSetColor(bg);
		ofFill();
        	ofRectRounded(-width*0.5, -height*0.5, width, height, 5);

		ofNoFill();
		ofSetLineWidth(2);
		ofSetColor(fg);
        	ofRectRounded(-width*0.5, -height*0.5, width, height, 5);
	
		ofFill();
		ofSetColor(fg);
		ofScale(width * scaleW,height * scaleH, 1);
		font->drawString(letter, -font->stringWidth(letter)*0.5, font->stringHeight(letter)*0.35);//(height/10)*1.3);
    ofPopMatrix();
}

bool ofxKey::isOver(ofPoint _location){
	ofPoint dirToCenter = position - _location;
	float theta = atan2(dirToCenter.x,dirToCenter.y)-(PI/2);
	float r = dirToCenter.length();
	float x = r * cos(theta + *keyboardNorth);
	float y = r * sin(theta + *keyboardNorth);
	
	if ( (x <= width/2) && (x >= -width/2) && (y <= height/2) && (y >= -height/2)){
        fg = *backgroundColor;
		bg = *foregroundColor;
        pressed = true;
	} else {
        fg = *foregroundColor;
		bg = *backgroundColor;
        pressed = false;
	}
    
	return pressed;
}
