#ifndef DRAWBOARD_HPP
#define DRAWBOARD_HPP

#include "consoleForm.hpp"


class drawboard: public Form
{
    private:
        const char* _DrawLB;
        const char* _DrawRB;
        const char* _DrawMB;
        
    public:
        drawboard(short initX, short initY, short width, short height, HANDLE wHnd, const char* DrawLB, const char* DrawRB, const char* DrawMB);
        void click(short X, short Y, DWORD MouseButtonState);
        void presskey(WORD PressedKeyCode, DWORD ControlKeyState);
};

#endif

