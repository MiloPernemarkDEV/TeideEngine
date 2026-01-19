#pragma once

#include "platform_windows.h"

LRESULT CALLBACK WindowProc (HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class TEIDE_API window
{
public:	
		
	window();
	window(const window&) = delete;
	window& operator =(const window&) = delete;
	~window();

	bool ProcessMessages();	

	HWND GetHWND() const;

private:
	HINSTANCE m_hInstance; // More connected to the actual application
	HWND m_hWnd; // Connected to the actual window instance 
};

