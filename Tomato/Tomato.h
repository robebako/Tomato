
// Tomato.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#include "resource.h"		// main symbols


// CTomatoApp:
// See Tomato.cpp for the implementation of this class
//

class CTomatoApp : public CWinApp
{
public:
	CTomatoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTomatoApp theApp;
