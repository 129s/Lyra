#include "gui.h"
#include <stdio.h>

#define ID_WAVE_COMBO 1001

GUI *gui_create(HINSTANCE hInstance, Synth *synth)
{
    GUI *gui = malloc(sizeof(GUI));
    gui->synth = synth; // 关联合成器
    gui->wave_sel_index = synth->wave_type;
    const char CLASS_NAME[] = "LyraWindowClass";

    WNDCLASS wc = {0};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    // 计算窗口居中位置
    int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    int screenHeight = GetSystemMetrics(SM_CYSCREEN);
    int windowWidth = 400;
    int windowHeight = 300;
    int posX = (screenWidth - windowWidth) / 2;
    int posY = (screenHeight - windowHeight) / 2;

    gui->hWnd = CreateWindowEx(
        0, CLASS_NAME, "Lyra Synth",
        WS_OVERLAPPEDWINDOW,
        posX, posY,
        windowWidth, windowHeight,
        NULL, NULL, hInstance, gui);

    // 创建波形选择下拉框
    CreateWindow("COMBOBOX", "",
                 WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST | WS_VSCROLL,
                 20, 20, 150, 100,
                 gui->hWnd, (HMENU)ID_WAVE_COMBO, hInstance, NULL);

    // 添加波形选项
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_ADDSTRING, 0, (LPARAM) "Sine");
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_ADDSTRING, 0, (LPARAM) "Square");
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_ADDSTRING, 0, (LPARAM) "Sawtooth");
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_ADDSTRING, 0, (LPARAM) "Triangle");
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_SETCURSEL, gui->wave_sel_index, 0);

    ShowWindow(gui->hWnd, SW_SHOW);
    return gui;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    GUI *gui = (GUI *)GetWindowLongPtr(hWnd, GWLP_USERDATA);

    switch (msg)
    {
    case WM_CREATE:
        gui = ((CREATESTRUCT *)lParam)->lpCreateParams;
        SetWindowLongPtr(hWnd, GWLP_USERDATA, (LONG_PTR)gui);
        break;

    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        EndPaint(hWnd, &ps);
        break;
    }

    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_WAVE_COMBO)
        {
            if (HIWORD(wParam) == CBN_SELCHANGE)
            {
                int sel = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
                if (sel != CB_ERR)
                {
                    gui->wave_sel_index = sel;
                    // 更新合成器波形类型
                    switch (sel)
                    {
                    case 0:
                        gui->synth->wave_type = WAVE_SINE;
                        break;
                    case 1:
                        gui->synth->wave_type = WAVE_SQUARE;
                        break;
                    case 2:
                        gui->synth->wave_type = WAVE_SAWTOOTH;
                        break;
                    case 3:
                        gui->synth->wave_type = WAVE_TRIANGLE;
                        break;
                    }
                    // 选择后焦点返回主窗口
                    SetFocus(gui->hWnd);
                }
            }
        }
        break;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}