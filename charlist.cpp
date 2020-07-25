#include "charlist.hpp"

charlist::charlist(short initX, short initY, char* CharLB, char* CharRB, char* CharMB, HANDLE wHnd) : Form(initX, initY, 102, 5, wHnd) {
	
	_CharLB = CharLB, _CharRB = CharRB, _CharMB = CharMB;
	*_CharLB = '\xDB', *_CharRB = '\xB1', *_CharMB = '\x20';
	
	for (short i = 0; i < getwidth() * getheight(); i++) {
		if      (design[i] == '/') 	editBufferCell(i, BLACK, WHITE);
		else if (design[i] == 'i')	{editBufferCell(i, *_CharLB, BLACK, LWHITE); _formBufferPosLB = i;}
		else if (design[i] == 'j')	{editBufferCell(i, *_CharRB, BLACK, LWHITE); _formBufferPosRB = i;}
		else if (design[i] == 'k')	{editBufferCell(i, *_CharMB, BLACK, LWHITE); _formBufferPosMB = i;}
		else						editBufferCell(i, design[i], BLACK, LWHITE);
	}
	for (short i = 0; i < 256; i++)
        _charContent[i].Char.AsciiChar = i,
        _charContent[i].Attributes = BLACK | (LWHITE << 4);
	updateSelectedChars();
	updateCharContent();
	update();
}

void charlist::updateCharContent() {
	for (short y = 1; y <= 3; y++)
		for (short x = 1; x <= 86; x++)
			if (x - 1 + 86 * (y - 1) < 256) editBufferCell(x + getwidth() * y, _charContent[x - 1 + 86 * (y - 1)]);
			else break;
}

void charlist::updateSelectedChars() {
	editBufferCell(_formBufferPosLB, *_CharLB);
	editBufferCell(_formBufferPosRB, *_CharRB);
	editBufferCell(_formBufferPosMB, *_CharMB);
	
}

void charlist::selectChar(DWORD MouseButtonState, char c) {
	if (MouseButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {		// LEFT CLICK
		*_CharLB = c;
		updateSelectedChars();
		update();
	}
	else if (MouseButtonState & RIGHTMOST_BUTTON_PRESSED) { 	// RIGHT CLICK
		*_CharRB = c;
		updateSelectedChars();
		update();
	}
	else if (MouseButtonState & FROM_LEFT_2ND_BUTTON_PRESSED) {	// MIDDLE CLICK
		*_CharMB = c;
		updateSelectedChars();
		update();
	}
}

void charlist::click(short X, short Y, DWORD MouseButtonState) {
	if (isInside(X,Y))
		if (correctX(X) >= 1 && correctX(X) <= 86 && correctY(Y) >= 1 && correctY(Y) <= 3 && correctX(X) - 1 + 86*(correctY(Y) - 1) < 256) 
			selectChar(MouseButtonState, X - 1 + 86 * (Y - 1));
}

void charlist::presskey(WORD PressedKeyCode, DWORD ControlKeyState) {
    if (PressedKeyCode == 'D') {
        *_CharLB = '\xDB', *_CharRB = '\xB1', *_CharMB = '\x20';
        updateSelectedChars();
        update();
    }
}
