#include "MXML.h"

MXML *  MXML::mxml = nullptr;

MXML::MXML()
{
}

void MXML::startTag(){
	outputFile += "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"no\"?>\n\
		<!DOCTYPE score-partwise PUBLIC\n\"-//Recordare//DTD MusicXML 3.0 Partwise//EN\"\n\"http://www.musicxml.org/dtds/partwise.dtd\">\n\
		<score-partwise version=\"3.1\">\n\
		<part-list>\n\
		<score-part id=\"Right\"></score-part>\n\
		<score-part id=\"Left\"></score-part>\n\
		</part-list>\n";
}
void MXML::startMeasureTag(){ 
	outputFile += "<measure>\n";
}
void MXML::endMeasureTag(){
	outputFile += "</measure>\n";
}
void MXML::startAtrrtibutesTag(){
	outputFile += "  <attributes>\n";
}
void MXML::endAttributesTag(){
	outputFile += "  </attributes>\n";
}
void MXML::startNoteTag(){
	outputFile += "  <note>\n";
}
void MXML::endNoteTag(){
	outputFile += "  </note>\n";
}
void MXML::startPitchTag(){
	outputFile += "   <pitch>\n";
}
void MXML::endPitchTag(){
	outputFile += "   </pitch>\n";
}
void MXML::startDurationTag(){
	outputFile += "  <duration>";
}
void MXML::endDurattionTag(){
	outputFile += "</duration>\n";
}
void MXML::startOctaveTag(){
	outputFile += "    <octave>"; 
}
void MXML::endOctaveTag(){
	outputFile += "</octave>\n";
}
void MXML::startStepTag(){
	outputFile += "    <step>";
}
void MXML::endStepTag(){
	outputFile += "</step>\n";
}
void MXML::startAlterTag(){
	outputFile += "    <alter>";
}
void MXML::endAlterTag(){
	outputFile += "</alter>";
}
void MXML::addAlterTag(Note note){
	if (!note.isSharp()) return;
	startAlterTag();
	outputFile += "1";
	endAlterTag();
}
void MXML::addOctaveTag(int octave){
	startOctaveTag();
	outputFile += std::to_string(octave);
	endOctaveTag();
}
void MXML::addSteptag(int step){
	startStepTag();
	outputFile += std::to_string(step);
	endStepTag();
}
void MXML::addDurationTag(Fraction duration){
	startDurationTag();
	if (duration == Fraction::eight) outputFile += "1";
	else outputFile += "2";
	endDurattionTag();
}
void MXML::addPitchTag(Note note){
	startPitchTag();
	startStepTag();
	outputFile += note.getPitchC();
	endStepTag();
	startOctaveTag();
	outputFile += std::to_string(note.getOctaveI());
	endOctaveTag();
	addAlterTag(note);
	endPitchTag();
}
void MXML::addAtributesTag(Fraction takt, std::string sign, int line){
	startAtrrtibutesTag();
	addDivisionTag(2);
	startTimeTag();
	addBeatsTag(takt.getNumerator());
	addBitTypeTag(takt.getDenomitot());
	endTimeTag();
	startClefTag();
	addSignTag(sign);
	addLineTag(line);
	endClefTag();
	endAttributesTag();
}
void MXML::addTieTag(MusicalSymbol* ms){
	if (ms->isPartOfSymbol()) {
		if (ms->isFirstpart()) outputFile += "   <tie type=\"start\"/>\n";
		else outputFile += "   <tie type=\"end\"/>\n";
	}
}
void MXML::addChordTag(Note*note){
	if (!note->isPartOfChord() || note->isFirstInChord()) return;
	outputFile += "     <chord/>\n";
}
void MXML::addRestTag(Rest* rest){
	startNoteTag();
	outputFile += "   <rest/>\n";
	addDurationTag(rest->getDuration());
	endNoteTag();
}
void MXML::startPartTagRight(){
	outputFile += "<part id=\"Right\">\n";
}
void MXML::startPartTagLeft() {
	outputFile += "<part id=\"Left\">\n";
}
void MXML::endPartTag(){
	outputFile += "</part>\n";
}
void MXML::startTimeTag(){
	outputFile += "   <time>\n";
}
void MXML::endTimeTag(){
	outputFile += "   </time>\n";
}
void MXML::addBeatsTag(int beats){
	outputFile += "    <beats>" + std::to_string(beats) + "</beats>\n";
}
void MXML::addBitTypeTag(int bitType){
	outputFile += "    <beat-type>" + std::to_string(bitType) + "</beat-type>\n";
}
void MXML::startClefTag(){
	outputFile += "   <clef>\n";
}
void MXML::endClefTag(){
	outputFile += "   </clef>\n";
}
void MXML::addSignTag(std::string sign){
	outputFile += "    <sign>" + sign + "</sign>\n";
}
void MXML::addLineTag(int line){
	outputFile += "    <line>" + std::to_string(line) + "</line>\n";
}
void MXML::addDivisionTag(int division){
	outputFile +=  "   <divisions>" + std::to_string(division) + "</divisions>\n";
}
void MXML::addNoteTag(Note *note){
	startNoteTag();
	addChordTag(note);
	addPitchTag(*note);
	addDurationTag(note->getDuration());
	addTieTag(note);
	endNoteTag();
}
void MXML::addChord(Chord* chord) {
	for (auto note : chord->getNotes())
		addNoteTag(&note);
}
MXML* MXML::getMXML() {
	if (mxml == nullptr)
		mxml = new MXML();
	return mxml;
}
void MXML::addMeasureTag(Takt * takt, MXML::Choice choice){
	startMeasureTag();
	auto symbols = takt->getSymbols();
	if (choice == Choice::STARTLEFTPART) addAtributesTag(takt->getDuration(), "F", 4);
	if (choice == Choice::STARTRIGHTPART) addAtributesTag(takt->getDuration(), "G", 2);
	for (auto symbol : symbols) {
		if (symbol->type() == "NOTE") {
			addNoteTag(dynamic_cast<Note*>(symbol));
			continue;
		}
		if (symbol->type() == "CHORD") {
			addChord(dynamic_cast<Chord*>(symbol));
			continue;
		}
		if (symbol->type() == "REST") {
			addRestTag(dynamic_cast<Rest*>(symbol));
			continue;
		}
	}
	endMeasureTag();
}
bool MXML::exportCompososition(std::string fileName) {
	startTag();
	startPartTagRight();
	auto takts = composition->getTaktsForRight();
	Choice choice = Choice::STARTRIGHTPART;
	for (auto takt : takts) {
		addMeasureTag(takt, choice);
		choice = Choice::NOTHING;
	}
	endPartTag();
	startPartTagLeft();
	takts = composition->getTaktsForLeft();
	choice = Choice::STARTLEFTPART;
	for (auto takt : takts) {
		addMeasureTag(takt, choice);
		choice = Choice::NOTHING;
	}
	endPartTag();
	outputFile += "</score-partwise>";
	std::ofstream music(fileName);
	music << outputFile;
	outputFile = "";
	music.close();
	return true;
}
void MXML::setCompostition(Composition* composition) {
	this->composition = composition;
}
