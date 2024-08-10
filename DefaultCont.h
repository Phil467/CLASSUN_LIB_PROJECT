#ifndef DEFAULTCONT_H
#define DEFAULTCONT_H


#define _WIN32_WINNT   0x0501
#include <windows.h>
LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
HWND csf_initialization(HINSTANCE hThisInstance, const char* appName);
int csf_close();
void initLists(int n);

#endif // DEFAULTCONT_H
