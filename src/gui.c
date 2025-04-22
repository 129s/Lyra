#include "gui.h"
#include <stdio.h>

#define ID_WAVE_COMBO 1001

GUI *gui_create(HINSTANCE hInstance)
{
    GUI *gui = malloc(sizeof(GUI));
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
        posX, posY, // 修改位置参数
        windowWidth, windowHeight,
        NULL, NULL, hInstance, NULL);

    // 创建波形选择下拉框
    CreateWindow("COMBOBOX", "", WS_CHILD | WS_VISIBLE | CBS_DROPDOWNLIST,
                 20, 20, 150, 200, gui->hWnd, (HMENU)ID_WAVE_COMBO, hInstance, NULL);

    // 添加波形选项
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_ADDSTRING, 0, (LPARAM) "Square");
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_ADDSTRING, 0, (LPARAM) "Sine");
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_ADDSTRING, 0, (LPARAM) "Sawtooth");
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_ADDSTRING, 0, (LPARAM) "Triangle");
    SendDlgItemMessage(gui->hWnd, ID_WAVE_COMBO, CB_SETCURSEL, 0, 0);

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
    FillRect(gui->hdcBuffer, &gui->clientRect, (HBRUSH)(COLOR_WINDOW + 1));

    // 绘制八度信息
    char text[64];
    SetBkMode(gui->hdcBuffer, TRANSPARENT);
    sprintf(text, "Current Octave: %d", (gui->octave / 12) + 3);
    TextOut(gui->hdcBuffer, 20, 60, text, strlen(text));

    // 绘制活动音符
    int y = 100;
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
    static GUI *gui = NULL;

    switch (msg)
    {
    case WM_CREATE:
        gui = ((CREATESTRUCT *)lParam)->lpCreateParams;
        break;

    case WM_COMMAND:
        if (LOWORD(wParam) == ID_WAVE_COMBO && HIWORD(wParam) == CBN_SELCHANGE)
        {
            int sel = SendMessage((HWND)lParam, CB_GETCURSEL, 0, 0);
            // 更新全局合成器波形类型（需在外部处理）
        }
        break;

    case WM_PAINT:
        if (gui)
            gui_update(gui, NULL);
        break;

    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProc(hWnd, msg, wParam, lParam);
}