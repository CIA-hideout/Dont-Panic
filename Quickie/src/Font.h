#pragma once
#ifndef _FONT_H_
#define _FONT_H_

#include "graphics.h"

class Font
{
	Graphics*	graphics;
	ID3DXFont*	font;
	RECT*		font_rect;

	// current font's values
	int height;
	UINT width, weight;
	bool italics;
	std::string fontName;

public:
	Font();
	~Font();

	bool initialize(Graphics* graphics);
	bool createFont();
	bool createFont(int height, UINT width, UINT weight, bool i, std::string fN);
	void print(int x, int y, std::string sentence);						// prints the text on screen given the coordinates
	int getTotalWidth(std::string text);

	// GET Methods
	ID3DXFont* getFont(){ return font; }
	RECT* getFontRect(){ return font_rect; }
	std::string getFontName(){ return fontName; }
	int getHeight(){ return height; }
	UINT getWidth(){ return width; }
	UINT getWeight() { return weight; }
	bool getItalics(){ return italics; }
	
	// SET Methods
	void setFont(ID3DXFont* f){ font = f; }
	void setRect(RECT* r){ font_rect = r; }
	void setHeight(int h) { height = h; }
	void setWidth(UINT w) { width = w; }
	void setWeight(UINT w) { weight = w; }
	void setItalics(bool i){ italics = i; }
	void setFontName(std::string fN) { fontName = fN; }
};

#endif