
// Tomato.h : main header file for the PROJECT_NAME application
//

#pragma once

#ifndef __AFXWIN_H__
	#error "include 'pch.h' before including this file for PCH"
#endif

#if defined(_UNICODE) && !defined(UNICODE)
#define UNICODE
#endif
#if defined(UNICODE) && !defined(_UNICODE)
#define _UNICODE
#endif

#include <string>
#include <sstream>
#include <tchar.h>
typedef std::basic_string<TCHAR> tstring;
typedef std::basic_stringstream<TCHAR> tstringstream;

#include <map>

#include "resource.h"		// main symbols


// CTomatoApp:
// See Tomato.cpp for the implementation of this class
//

class CTomatoApp : public CWinApp
{
public:
	std::map<CString, int> works;
	CTomatoApp();

// Overrides
public:
	virtual BOOL InitInstance();

// Implementation

	DECLARE_MESSAGE_MAP()
};

extern CTomatoApp theApp;
