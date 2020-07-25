/**
 * Project: ASCII_Painter
 * Author: nguyenvlm
 * Compiler: mingw_w64
 * Compiler option flags: -std=c++14 -Wall -O2 -static-libgcc -static-libstdc++
 * 
 */

#include "consoleForm.hpp"
#include "charlist.hpp"
#include "drawboard.hpp"

#define windowTitle "ASCII Painter"
#define WSIZE_H 65		// default MAX Y
#define WSIZE_W 102		// default MAX X

COORD MaxWindowSize;

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.

void InitHandles() {
    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);
}

void SetWindowSize() {
	MaxWindowSize = GetLargestConsoleWindowSize(wHnd); // Get the maximum possible window size.
	MaxWindowSize.X = std::max(WSIZE_W, MaxWindowSize.X - 1), MaxWindowSize.Y = std::max(WSIZE_H, MaxWindowSize.Y - 1);
    SMALL_RECT windowSize = {0, 0, WSIZE_W, MaxWindowSize.Y - 1};
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);
	SetConsoleScreenBufferSize(wHnd, MaxWindowSize);
}

void SetCursorInfo() {
	CONSOLE_CURSOR_INFO cci{1, FALSE}; // Set the cursor visibility to hidden.
	SetConsoleCursorInfo(wHnd, &cci);
}

int main(int argc, char** argv) {
	char DrawLB, DrawRB, DrawMB;
	InitHandles();
    SetConsoleTitle(TEXT(windowTitle));
    SetWindowSize();
    SetCursorInfo();
	
    
	blankForm ToolPanel(0, 0, MaxWindowSize.X, 5, wHnd);
	ToolPanel.fillFormAttributes(BLACK, WHITE);
    charlist CharList(0, 0, &DrawLB, &DrawRB, &DrawMB, wHnd);
    drawboard DrawBoard(0, 5, MaxWindowSize.X, MaxWindowSize.Y - 5, wHnd, &DrawLB, &DrawRB, &DrawMB);
    
    
    DWORD numEvents = 1;
    DWORD numEventsRead = 1;
    
    bool appIsRunning = true;
    while (appIsRunning) {
        
//        GetNumberOfConsoleInputEvents(rHnd, &numEvents); // Find out how many console events have happened.
        if (WaitForSingleObject(rHnd, INFINITE) == WAIT_OBJECT_0) {
        	
            INPUT_RECORD *eventBuffer = new INPUT_RECORD[numEvents];
            ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);
            
            for (DWORD i = 0; i < numEventsRead; i++) {
                if (eventBuffer[i].EventType == KEY_EVENT) {
                    if (eventBuffer[i].Event.KeyEvent.wVirtualKeyCode==VK_ESCAPE) {
                        appIsRunning = false;
                    }
					else {
						DrawBoard.presskey(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode, eventBuffer[i].Event.KeyEvent.dwControlKeyState);
                        CharList.presskey(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode, eventBuffer[i].Event.KeyEvent.dwControlKeyState);
                    }
                }
				else if (eventBuffer[i].EventType == MOUSE_EVENT) {
                    
                    // Index of clicked pos:
                    short offsetPosX = eventBuffer[i].Event.MouseEvent.dwMousePosition.X, offsetPosY = eventBuffer[i].Event.MouseEvent.dwMousePosition.Y;
                    
                    // Mouse Button Input State:
                    DWORD MouseButtonState = eventBuffer[i].Event.MouseEvent.dwButtonState;
                    
                    CharList.click(offsetPosX, offsetPosY, MouseButtonState);
                    DrawBoard.click(offsetPosX, offsetPosY, MouseButtonState);
                    	
                }
            }
            delete[] eventBuffer;
        }
    }
    
	return 0;
}
