#include "drawboard.hpp"

drawboard::drawboard(short initX, short initY, short width, short height, HANDLE wHnd, const char* DrawLB, const char* DrawRB, const char* DrawMB) :
Form(initX, initY, width, height, wHnd) {
    _DrawLB = DrawLB, _DrawMB = DrawMB, _DrawRB = DrawRB;
}

void drawboard::click(short X, short Y, DWORD MouseButtonState) {
    if (isInside(X,Y)) {
        if (MouseButtonState & FROM_LEFT_1ST_BUTTON_PRESSED) {		// LEFT CLICK
            putChar(X, Y, *_DrawLB);                                 // Default: 0xDB
        }
        else if (MouseButtonState & RIGHTMOST_BUTTON_PRESSED) { 	// RIGHT CLICK
            putChar(X, Y, *_DrawRB);                                 // Default: 0xB1
        }
        else if (MouseButtonState & FROM_LEFT_2ND_BUTTON_PRESSED) {	// MIDDLE CLICK
            putChar(X, Y, *_DrawMB);                                 // Default: ' '
        }        
    }
}

void drawboard::presskey(WORD PressedKeyCode, DWORD ControlKeyState) {
    if (PressedKeyCode == 'C')
        clear();
}