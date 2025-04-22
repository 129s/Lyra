#include "gui.h"
#include <stdio.h>

#define ID_WAVE_COMBO 1001

GUI *gui_create(HINSTANCE hInstance, Synth *synth)
{
    GUI *gui = malloc(sizeof(GUI));
    gui->synth = synth; // 关联合成器
    gui->wave_sel_index = 0;
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

    // 初始化双缓冲
    GetClientRect(gui->hWnd, &gui->clientRect);
    HDC hdc = GetDC(gui->hWnd);
    gui->hdcBuffer = CreateCompatibleDC(hdc);
    gui->hbmBuffer = CreateCompatibleBitmap(hdc,
                                            gui->clientRect.right, gui->clientRect.bottom);
    SelectObject(gui->hdcBuffer, gui->hbmBuffer);
    ReleaseDC(gui->hWnd, hdc);

    ShowWindow(gui->hWnd, SW_SHOW);
    return gui;
}

void gui_update(GUI *gui, const Synth *synth)
{
    // 绘制到缓冲DC
    FillRect(gui->hdcBuffer, &gui->clientRect, (HBRUSH)(COLOR_WINDOW));

    // 绘制活动音符
    char text[64];
    int y = 60;
    for (int i = 0; i < MAX_VOICES; i++)
    {
        if (synth->voices[i].active)
        {
            sprintf(text, "Note %d: %dHz",
                    synth->voices[i].note,
                    (int)synth->voices[i].frequency);
            TextOut(gui->hdcBuffer, 20, y, text, strlen(text));
            y += 20;
        }
    }

    // 复制到窗口DC
    HDC hdc = GetDC(gui->hWnd);
    BitBlt(hdc, 0, 0, gui->clientRect.right, gui->clientRect.bottom,
           gui->hdcBuffer, 0, 0, SRCCOPY);
    ReleaseDC(gui->hWnd, hdc);
}

void gui_destroy(GUI *gui)
{
    DeleteDC(gui->hdcBuffer);
    DeleteObject(gui->hbmBuffer);
    DestroyWindow(gui->hWnd);
    free(gui);
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
                }
            }
        }
        break;

    case WM_PAINT:
        if (gui)
            gui_update(gui, gui->synth);
        break;

    case WM_CLOSE:
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        printf("QUIT");
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}