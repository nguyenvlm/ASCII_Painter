/* 
 * Header: consoleForm.hpp
 * Description:
 * This header defined the abstract class "Form" which is generally used as a base class for any GUI-like class of win console applications.
 * 
 */

#ifndef consoleForm_h
#define consoleForm_h

#include <Windows.h>
#include <cstdlib>
#include <string>

enum COLOR{BLACK, BLUE, GREEN, AQUA, RED, PURPLE, YELLOW, WHITE, GRAY, LBLUE, LGREEN, LAQUA, LRED, LPURPLE, LYELLOW, LWHITE};

class Form
{
	private:
		// Basic elements:
		HANDLE _wHnd;
		COORD _initPos;
		COORD _bufferSize;
		CHAR_INFO *_content;
    	SMALL_RECT _writeArea;

    protected:
    	CHAR_INFO getBufferCell(int pos);
    	void editBufferCell(int pos, char c);
    	void editBufferCell(int pos, DWORD F_Attr, DWORD B_Attr);			// Edit the CHAR_INFO buffer using the formula:
    	void editBufferCell(int pos, char c, DWORD F_Attr, DWORD B_Attr);	// pos = correctX + form_width * correctY
    	void editBufferCell(int pos, CHAR_INFO copycell);
		void update();
		void update(short X, short Y);	// Update the cell (X,Y) on the screen buffer. (X Y is the COORD of the screen buffer, not the CHAR_INFO buffer)
		short correctX(short X); 		// Get the real X of the form's CHAR_INFO buffer from the X of the screen buffer.
		short correctY(short Y); 		// Get the real Y of the form's CHAR_INFO buffer from the Y of the screen buffer.
		void writeString(short X, short Y, std::string write_content, size_t len);
		void writeString(int pos, std::string write_content, size_t len);
        void fillChar(char c);
		void putChar(short X, short Y, char c);
		void setCellAttribute(short X, short Y, DWORD F_Attr, DWORD B_Attr);
        void clear();

	public:
		// COORDs (X,Y) in public group are all COORDs of the screen buffer.
		// They should be converted to COORD of the form's CHAR_INFO buffer by correctX and correctY functions.
		Form(short initX, short initY , short width, short height, HANDLE wHnd);
		virtual ~Form();
		short getinitX();
		short getinitY();
		short getwidth();
		short getheight();
		bool isInside(short X, short Y);
        void fillFormAttributes(DWORD foreground, DWORD background);
		void bringToFront();
		virtual void click(short X, short Y, DWORD MouseButtonState) = 0;
        virtual void presskey(WORD PressedKeyCode, DWORD ControlKeyState) = 0;
		
};

class blankForm: public Form
{
    public:
        blankForm(short initX, short initY , short width, short height, HANDLE wHnd) : Form(initX, initY , width, height, wHnd) {};
        void click(short X, short Y, DWORD MouseButtonState) {};
        void presskey(WORD PressedKeyCode, DWORD ControlKeyState) {};
};

#endif
