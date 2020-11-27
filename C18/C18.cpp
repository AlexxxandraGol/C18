#define _CRT_SECURE_NO_WARNINGS
#include<Windows.h>
#include<tchar.h>
#include"Resource.h"

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HWND staticTextField, staticTextFieldTwo;
HWND hwnd;

const int HNUM = 10, VNUM = 100;
const int List_size = 20, Combo_size = 20;
const int INTERVAL = 20;
INT_PTR CALLBACK Dialog1(HWND, UINT, WPARAM, LPARAM);
TCHAR szAppName[] = _T("BigDialog");
HINSTANCE hInst;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	HWND hWnd;
	WNDCLASSEX wc;
	MSG lpMsg;
	hInst = hInstance;
	wc.cbSize = sizeof(wc);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = szAppName;
	wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	if (!RegisterClassEx(&wc)) return 0;
	hWnd = CreateWindow(szAppName, _T("Демонстрация списков"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, (HWND)NULL, (HMENU)NULL,
		hInstance, (LPSTR)NULL);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	while (GetMessage(&lpMsg, NULL, 0, 0)) {
		TranslateMessage(&lpMsg);
		DispatchMessageW(&lpMsg);
	}
	return (int)lpMsg.wParam;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {

	PAINTSTRUCT ps;
	HDC hdc;

	HMENU hMenu, hPopupMenu;

	TCHAR str0[] = _T("Диалог");
	TCHAR str1[] = _T("Открыть");
	switch (msg)
	{
	case WM_CREATE:
		hMenu = CreateMenu();
		hPopupMenu = CreatePopupMenu();
		AppendMenu(hPopupMenu, MF_STRING, ID_STDDIALOG, str1);
		AppendMenu(hMenu, MF_POPUP, (UINT)hPopupMenu, str0);
		SetMenu(hwnd, hMenu);
		break;
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case ID_STDDIALOG:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hwnd, Dialog1);
			break;
		case IDM_EXIT:
			DestroyWindow(hwnd);
			break;
		default:
			return DefWindowProc(hwnd, msg, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

INT_PTR CALLBACK Dialog1(HWND hDlg, UINT msg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	HBRUSH hBrushStatic = CreateSolidBrush(RGB(140, 26, 36));
	HBRUSH hBrushStatic1 = CreateSolidBrush(RGB(32, 178, 170));
	switch (msg)
	{
	case WM_CTLCOLORDLG:
		GetSysColor(CTLCOLOR_DLG);
		return (int)GetStockObject(NULL_BRUSH);
	case WM_CTLCOLORSTATIC:
		hdc = (HDC)wParam;
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_STATIC))
		{
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(140, 26, 36));
			return (int)GetStockObject(NULL_BRUSH);
		}
		if ((HWND)lParam == GetDlgItem(hDlg, IDC_SCROLLBAR2))
		{
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(32, 178, 170));
			return (int)GetStockObject(NULL_BRUSH);
		}
		//GetSysColor(CTLCOLOR_DLG);
		return (int)GetStockObject(NULL_BRUSH);
	case WM_COMMAND:
		switch (LOWORD(wParam))
		{
		case IDOK:
			return EndDialog(hDlg, 0);
		case IDCANCEL:
			return EndDialog(hDlg, 0);
		}
		return TRUE;
	default:
		return FALSE;
	}
	return FALSE;
}