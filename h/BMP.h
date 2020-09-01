#pragma once
#include "Formatter.h"
#include <vector>
#include <fstream>
#include "Note.h"
#include <regex>
#include <map>

class BMP :public Formatter{
	static BMP* bmp;
	int padding;
	int width;
	int height;
	static const int pixelSize = 3;
	std::map<Note, std::vector<unsigned char>> symbolColor;
	std::vector<std::vector<unsigned char>> colors;

	struct BMPHEADER {
		unsigned char ID[2] = { 0x42, 0x4D };
	    unsigned char size[4] = { 0x0,0x0,0x0,0x0 };
		unsigned char notUseTimes2[2] = { 0x0,0x0 };
		unsigned char pixelStarts[4] = { 0x36,0x00,0x00,0x00 };
	};
	struct DIBHEADER {
		unsigned char sizeDIB[4] = { 0x28,0x00,0x00,0x00 };
		unsigned char width[4] = { 0x02,0x00,0x00,0x00 };
		unsigned char height[4] = { 0x02,0x00,0x00,0x00 };
		unsigned char color[2] = { 0x01,0x00 };
		unsigned char bitPerPixel[2] = { 0x18,0x00 };
		unsigned char BI_RGB[4] = { 0x00,0x00,0x00,0x00 };
		unsigned char bitMapSize[4] = { 0x00,0x00,0x00,0x00 };
		unsigned char fixed1[4] = { 0x13,0x0B,0x00,0x00 };
		unsigned char fixed2[4] = { 0x13,0x0B,0x00,0x00 };
		unsigned char fixed3[4] = { 0x00,0x00,0x00,0x00 };
		unsigned char fixed4[4] = { 0x00,0x00,0x00,0x00 };
	};
	void splitInteger(int data, unsigned char splitted[4])const;
	BMPHEADER bmpHeader;
	DIBHEADER dibHeader;
	void loadColor();
	std::vector<unsigned char>getColor(MusicalSymbol* ms);
	void prepareColors() ;
	void readWidth();

public:
	static BMP* getBMP();
	bool exportCompososition(std::string fileName) ;
	void setComposition(Composition* comp) {
		composition = comp;
	}
	
};

