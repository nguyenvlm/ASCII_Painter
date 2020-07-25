#include "consoleForm.hpp"

				/*----Protected Group----*/

CHAR_INFO Form::getBufferCell(int pos) {
	return _content[pos];
}

void Form::editBufferCell(int pos, char c) {
	_content[pos].Char.AsciiChar = c;
}

void Form::editBufferCell(int pos, DWORD F_Attr, DWORD B_Attr) {
	_content[pos].Attributes = F_Attr | (B_Attr << 4);
}

void Form::editBufferCell(int pos, char c, DWORD F_Attr, DWORD B_Attr) {
	_content[pos].Char.AsciiChar = c;
	_content[pos].Attributes = F_Attr | (B_Attr << 4);
}

void Form::editBufferCell(int pos, CHAR_INFO copycell) {
	_content[pos] = copycell;
}

void Form::update() {
	WriteConsoleOutputA(_wHnd, _content, _bufferSize, {0,0}, &_writeArea);
}

void Form::update(short X, short Y) {
	COORD tmpSize = {1,1};
	COORD tmpPos = {0,0};
	SMALL_RECT tmpWriteArea = {X, Y, X, Y};
	WriteConsoleOutputA(_wHnd, &_content[correctX(X) + _bufferSize.X * correctY(Y)], tmpSize, tmpPos, &tmpWriteArea);
}

short Form::correctX(short X) {
	return X - _initPos.X;
}

short Form::correctY(short Y) {
	return Y - _initPos.Y;
}

void Form::writeString(short X, short Y, std::string write_content, size_t len) {
	for (size_t i = 0; i < len; i++) editBufferCell(X + _bufferSize.X * Y, write_content[i]);

}

void Form::writeString(int pos, std::string write_content, size_t len) {
	for (size_t i = 0; i < len; i++) editBufferCell(i, write_content[i]);
}

void Form::fillChar(char c) {
	for (int i = 0; i < _bufferSize.X * _bufferSize.Y; i++) _content[i].Char.AsciiChar = c;
	update();
}

void Form::clear() {
	fillChar(' ');
	update();
}

void Form::putChar(short X, short Y, char c) {
	if (isInside(X,Y)) {
		_content[correctX(X) + _bufferSize.X * correctY(Y)].Char.AsciiChar = c;
		update(X,Y);
	}
}

void Form::setCellAttribute(short X, short Y, DWORD F_Attr, DWORD B_Attr) {
	if (isInside(X,Y)) {
		_content[correctX(X) + _bufferSize.X * correctY(Y)].Attributes = F_Attr | (B_Attr << 4);
		update(X,Y);
	}
}

				/*----Public Group----*/

Form::Form(short initX, short initY ,short width, short height, HANDLE wHnd) {
	_wHnd = wHnd;
    _bufferSize = {width, height};
    _initPos = {initX, initY};
    _content =  (CHAR_INFO*)malloc((_bufferSize.X * _bufferSize.Y)*sizeof(CHAR_INFO));
    _writeArea = {_initPos.X, _initPos.Y, _initPos.X + _bufferSize.X - 1, _initPos.Y + _bufferSize.Y - 1};
    fillFormAttributes(0,LWHITE);
    fillChar(' ');
    // Copy to display:	
    update();
}
		
Form::~Form() {free(_content);}

short Form::getinitX() {return _initPos.X;}
short Form::getinitY() {return _initPos.Y;}
short Form::getwidth() {return _bufferSize.X;}
short Form::getheight() {return _bufferSize.Y;}

bool Form::isInside(short X, short Y) {
	return 		correctX(X) < _bufferSize.X 
			&& 	correctY(Y) < _bufferSize.Y 
			&& 	X >= _initPos.X 
			&& 	Y >= _initPos.Y;
}
		
void Form::fillFormAttributes(DWORD foreground, DWORD background) {
	for (int i=0; i < _bufferSize.X * _bufferSize.Y; i++) _content[i].Attributes = foreground | (background << 4);
	update();
}

void Form::bringToFront()  {
	update();
}

