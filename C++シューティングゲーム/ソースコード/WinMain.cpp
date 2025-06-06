#pragma	comment(lib,"winmm")	//	儅儖僠儊僨傿傾奼挘婡擻傪巊梡偡傞偨傔偵昁梫
#include "MyPG.h"


LRESULT CALLBACK WndProc(HWND wnd_, UINT msg_, WPARAM wParam_, LPARAM lParam_);
HWND MyPG_CreateWindow(HINSTANCE inst_, const TCHAR cName_[], const TCHAR tName_[], RECT *wSize_, int showCmd_);

//-----------------------------------------------------------------------------
//僂傿儞儊僀儞
//婡擻奣梫丗僂傿儞僪僂僘僾儘僌儔儉偺儊僀儞娭悢
//-----------------------------------------------------------------------------
int __stdcall WinMain(	HINSTANCE inst_,	//
						HINSTANCE,			//
						LPSTR,				//
						int showCmd)		//
{
	ge = new MyPG::MyGameEngine( );

	HWND	wnd;								//	僂僀儞僪僂僴儞僪儖
	RECT	ws = { 0, 0, (LONG)(ge->screenWidth  * ge->viewScaleW), (LONG)(ge->screenHeight * ge->viewScaleH) };
	wnd = MyPG_CreateWindow(inst_, ge->windowClassName, ge->windowTitle, &ws, showCmd);
	if(wnd == nullptr){ return 0;}

//	僎乕儉娐嫬偺弶婜壔
	ge->B_Initialize(wnd);

//	儊僢僙乕僕儖乕僾
	MSG		msg = {};
	while (msg.message != WM_QUIT)
	{
		//儊僢僙乕僕偑棃偰偄傞偐
		if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
		{
			//儊僢僙乕僕偵墳偠偨張棟傪峴偆
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (GetActiveWindow() == wnd)
		{
			ge->B_Step(wnd);		//	僎乕儉張棟
		}
	}

	//	僎乕儉娐嫬偺攋婞
	delete ge;
	return 0;
}

//-----------------------------------------------------------------------------
//僂傿儞僪僂惗惉
//婡擻奣梫丗僂傿儞僪僂傪嶌傞偨傔偺奺庬愝掕傪峴偄丄僂傿儞僪僂傪惗惉偡傞
//-----------------------------------------------------------------------------
HWND MyPG_CreateWindow(HINSTANCE inst_, const TCHAR cName_[], const TCHAR tName_[], RECT* wSize_, int showCmd_)
{
	WNDCLASSEX wcex;						//	僂僀儞僪僂嶌惉偵巊梡
	HWND wnd;								//	僂僀儞僪僂僴儞僪儖

//	僨乕僞弶婜壔
	wcex.style			= (CS_HREDRAW | CS_VREDRAW);
	wcex.hIcon			= LoadIcon(inst_, IDI_APPLICATION);
	wcex.cbSize			= sizeof(WNDCLASSEX);
	wcex.hCursor		= LoadCursor(nullptr, IDC_ARROW);
	wcex.hIconSm		= LoadIcon(inst_, IDI_APPLICATION);
	wcex.hInstance		= inst_;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.lpfnWndProc	= (WNDPROC)WndProc;
	wcex.lpszMenuName	= nullptr;
	wcex.lpszClassName	= cName_;
	wcex.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
//	Windows偵搊榐
	if(!RegisterClassEx(&wcex))
	{
		MessageBox(nullptr, "僂僀儞僪僂搊榐偵幐攕", nullptr, MB_OK);
		return	nullptr;
	}
//	僂僀儞僪僂嶌惉
	DWORD dws = ge->screenMode ? WS_POPUP : (WS_CAPTION | WS_SYSMENU);
	AdjustWindowRectEx(wSize_, dws, false, WS_EX_APPWINDOW);

	wnd = CreateWindowEx(	WS_EX_APPWINDOW, 
							cName_,
							tName_,
							dws, 240, 100,
							(wSize_->right  - wSize_->left),
							(wSize_->bottom - wSize_->top),
							nullptr, nullptr, inst_, nullptr);
	if(!wnd)
	{
		MessageBox(nullptr, "僂僀儞僪僂惗惉偵幐攕", nullptr, MB_OK);
		return	nullptr;
	}

//	僂僀儞僪僂偺忬懺傪峏怴偡傞
	ShowWindow(wnd, showCmd_);
	UpdateWindow(wnd);

	return wnd;	//惉岟
}

//-----------------------------------------------------------------------------
//僂傿儞僪僂僾儘僔僕儍
//婡擻奣梫丗儊僢僙乕僕偵懳偡傞張棟傪峴偆
//-----------------------------------------------------------------------------
LRESULT CALLBACK WndProc(	HWND	wnd_,		//	僂傿儞僪僂僴儞僪儖
							UINT	msg_,		//	儊僢僙乕僕
							WPARAM	wParam_,	//	僷儔儊乕僞
							LPARAM	lParam_)	//	僷儔儊乕僞
{
	LRESULT ret = (LRESULT)0;
//	Windows偐傜憲怣偝傟偨儊僢僙乕僕傪挷傋傞
	switch(msg_){

	case WM_KEYDOWN:
		if(wParam_ == VK_BACK){
			static bool dm = true;
			ge->DebugMode( dm = !dm );
		}
		break;

	//	僂僀儞僪僂偑惗惉偝傟偨
		case WM_CREATE:
			break;

	//	偙偺僂僀儞僪僂偑傾僋僥傿僽偵側偭偨
		case WM_ACTIVATEAPP:
			break;

	//	亊儃僞儞偑墴偝傟偨
		case WM_CLOSE:
			ge->quitRequest = true;
			break;

	//	僂僀儞僪僂偑攋婞偝傟偨
		case WM_DESTROY:
			PostQuitMessage(0);
			break;

	//	偦偺懠偺儊僢僙乕僕偼Windows偵張棟傪擟偣傞
		default:
			ret = DefWindowProc(wnd_, msg_, wParam_, lParam_);
	}
	return ret;
}

