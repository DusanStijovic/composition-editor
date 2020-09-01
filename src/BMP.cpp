#include "BMP.h"

BMP* BMP::bmp = nullptr;

void BMP::splitInteger(int data, unsigned char splitted[4])const {
	splitted[0] = (data) & ~(-1L << 8);
	data = data >> 8;
	splitted[1] = (data) & ~(-1L << 8);
	data = data >> 8;
	splitted[2] = (data) & ~(-1L << 8);
	data = data >> 8;
	splitted[3] = (data) & ~(-1L << 8);
}
void BMP::loadColor() {
	enum Color { R, G, B };
	std::ifstream file("note.txt");
	std::string result = "";
	std::regex space("([^ ]+) ([^ ]+) ([^ ]+) ([^ ]+)?");
	int		i = 0;
	while (std::getline(file, result)) {
		std::smatch data;
		if (std::regex_match(result, data, space)) {
			Note note = Note(data.str(1));
			unsigned char r = std::stoi(data.str(2));
			unsigned char g = std::stoi(data.str(3));
			unsigned char b = std::stoi(data.str(4));
			std::vector<unsigned char>colors;
			colors.resize(3);
			colors[R] = r; colors[G] = g; colors[B] = b;
			symbolColor[note] = colors;
			i++;
		}
	}
}
BMP* BMP::getBMP() {
	if (bmp == nullptr) {
		bmp = new BMP();
	}
	return bmp;
}
std::vector<unsigned char> BMP::getColor(MusicalSymbol* ms) {
	std::vector<unsigned char> color; color.resize(3);
	color[0] = color[1] = color[2] = 0;
	if (ms->type() == "REST") {
		color[0] = color[1] = color[2] = 0xFF;
		return color;
	}
	if (ms->type() == "NOTE") {
		return  symbolColor[*Note::getNote(ms)];

	}
	if (ms->type() == "CHORD") {
		Chord* chord = Chord::getChord(ms);
		for (auto note : chord->getNotes()) {
			color[0] += symbolColor[note][0];
			color[1] += symbolColor[note][1];
			color[2] += symbolColor[note][2];
		}
		color[0] /= chord->getNotes().size();
		color[1] /= chord->getNotes().size();
		color[2] /= chord->getNotes().size();
		return color;
	}
}
void BMP::prepareColors() {
	int currentNumofBytesinRow = 0, currentNumofRows = 0, currentPixelinRow = 0;
	int pixelInBytes = 3;
	std::vector<unsigned char> rowColor;
	for (auto taktPair : *composition) {
		std::list<MusicalSymbol*> symbols = Takt::extractSymbols(taktPair.first, taktPair.second);
		for (auto symbol : symbols) {
			int i = 1;
			if (symbol->getDuration() == Fraction::quarter) i = 2;
			while (i--) {
				std::vector<unsigned char> color(getColor(symbol));
				rowColor.push_back(color[2]); rowColor.push_back(color[1]); rowColor.push_back(color[0]);
				currentPixelinRow++;
				currentNumofBytesinRow += pixelInBytes;
				if (currentPixelinRow == width) {
					int temp = padding;
					while (temp--) {
						rowColor.push_back(0x00);
					}
					colors.push_back(rowColor);
					rowColor.clear();
					currentPixelinRow = 0;
					currentNumofRows++;
				}
			}

		}
		for (auto& symbol : symbols) {
			delete symbol;
			symbol = nullptr;
		}
	}
	int bytesInLastRow = currentPixelinRow * 3;
	if (bytesInLastRow != 0) currentNumofRows++;
	while (bytesInLastRow != 0 and bytesInLastRow != width * 3 + padding) {
		rowColor.push_back(0xFF);
		bytesInLastRow++;
	}
	if (!rowColor.empty()) colors.push_back(rowColor);
	height = currentNumofRows;
}
void BMP::readWidth() {
	std::cout << "Unesite sirinu slike u broju piksela: \n";
	std::string choice;
	do {
		try {
			std::cin >> choice;
			width = std::stoi(choice);
			return;
		}
		catch (std::invalid_argument ia) {
			std::cout << "Uneli ste nevalidne podatke, unesite broj piksela, ne ostale znakove!\n";
		}
		catch (std::out_of_range& oitOf) {
			std::cout << "Uneli ste preveliki broj!";
		}

	} while (true);

}
bool BMP::exportCompososition(std::string fileName) {
	if (composition == nullptr) {
		std::cout << "Nije postavljena kompozicija!\n";
		return false;
	}
	readWidth();
	loadColor();
	int pixelBytes = 3;
	int bytesPerRow = pixelBytes * width;
	padding = 4 - bytesPerRow % 4;
	if (padding == 4) padding = 0;
	prepareColors();
	int sizeInBytes = (bytesPerRow + padding) * height;
	splitInteger(sizeInBytes + 54, bmpHeader.size);
	splitInteger(height, dibHeader.height);
	splitInteger(width, dibHeader.width);
	splitInteger(sizeInBytes, dibHeader.bitMapSize);

	std::ofstream outFile(fileName, std::ios::binary);
	for (auto byte : bmpHeader.ID)
		outFile << byte;
	for (auto byte : bmpHeader.size)
		outFile << byte;
	for (auto byte : bmpHeader.notUseTimes2)
		outFile << byte;
	for (auto byte : bmpHeader.notUseTimes2)
		outFile << byte;
	for (auto byte : bmpHeader.pixelStarts)
		outFile << byte;
	for (auto byte : dibHeader.sizeDIB)
		outFile << byte;
	for (auto byte : dibHeader.width)
		outFile << byte;
	for (auto byte : dibHeader.height)
		outFile << byte;
	for (auto byte : dibHeader.color)
		outFile << byte;
	for (auto byte : dibHeader.bitPerPixel)
		outFile << byte;
	for (auto byte : dibHeader.BI_RGB)
		outFile << byte;
	for (auto byte : dibHeader.bitMapSize)
		outFile << byte;
	for (auto byte : dibHeader.fixed1)
		outFile << byte;
	for (auto byte : dibHeader.fixed2)
		outFile << byte;
	for (auto byte : dibHeader.fixed3)
		outFile << byte;
	for (auto byte : dibHeader.fixed4)
		outFile << byte;
	for (int i = colors.size() - 1; i >= 0; i--) {
		for (auto color : colors[i])
			outFile << color;
	}
	outFile.close();
	colors.clear();
	return true;


}