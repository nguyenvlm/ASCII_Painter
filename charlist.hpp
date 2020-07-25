#ifndef charlist_h
#define charlist_h

#include "consoleForm.hpp"

class charlist: public Form
{
	private:
		char *_CharLB, *_CharRB, *_CharMB;
		CHAR_INFO _charContent[256]; 
		short _formBufferPosLB, _formBufferPosRB, _formBufferPosMB;
		
	protected:
		void updateCharContent();
		void updateSelectedChars();
		void selectChar(DWORD MouseButtonState, char c);
		
	public:
		charlist(short initX, short initY, char* CharLB, char* CharRB, char* CharMB, HANDLE wHnd);
		void click(short X, short Y, DWORD MouseButtonState);
        void presskey(WORD PressedKeyCode, DWORD ControlKeyState);
};

const std::string design = "\
//////////////////////////////////////////////////////////////////////////////////////////////////////\
/                                                                                      //   LEFT : i /\
/                                                                                      //  RIGHT : j /\
/                                                                                      // MIDDLE : k /\
//////////////////////////////////////////////////////////////////////////////////////////////////////";

#endif
