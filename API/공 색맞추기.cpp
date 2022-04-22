#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <TCHAR.H>
#include <time.h>
#include <math.h>
#include <iostream>
#include <string>
#define ActorCount 30
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);
HWND MainWnd;
TCHAR tmp[128];
TCHAR tmp2[128];
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
    HWND hwnd; // handle window
    MSG msg;   // message
    WNDCLASS WndClass;                                            // window class
    WndClass.style = CS_HREDRAW | CS_VREDRAW;                     // 출력 형태
    WndClass.lpfnWndProc = WndProc;                               // 프로시저 함수 등록
    WndClass.cbClsExtra = 0;                                      // 클래스 여분 메모리
    WndClass.cbWndExtra = 0;                                      // 윈도우 여분 메모리
    WndClass.hInstance = hInstance;                               // 윈도 인스턴스
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);             // 아이콘
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);               // 커서
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH); // 윈도우 초기 배경색 지정
    WndClass.lpszMenuName = NULL;                                 // 메뉴 이름
    WndClass.lpszClassName = _T("WindowClass_1");                 // 클래스 이름
    RegisterClass(&WndClass);
    hwnd = CreateWindow(_T("WindowClass_1"), _T("WindowProgramming Study"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    MainWnd = hwnd;
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

struct vec2
{
    int x;
    int y;
};
struct cRGB
{
    int r, g, b;
};
struct Ball
{
    vec2 pos;
    int radius;
    cRGB color;
};
int second = 0;
int greenBall = 30;
int redBall = 0;
Ball pawn;
Ball Actor[ActorCount];
void checking() { // 공 갯수 체크
    int checknum = 0;
    for (int i = 0; i < 30; i++)
    {
        if (Actor[i].color.r == 255)
        {
            checknum++;
        }
    }
    redBall = checknum;
    greenBall = 30 - redBall;

}

bool isHit_btb(Ball ball, Ball ball2) //공겹쳤을때 판별하는 소스2
{
    float length = sqrt(((ball2.pos.x - ball.pos.x) * (ball2.pos.x - ball.pos.x)) + ((ball2.pos.y - ball.pos.y) * (ball2.pos.y - ball.pos.y)));
    if (length <= ball2.radius + ball.radius)
    {
        return true;
    }
    return false;
}

void InitActor(RECT area, Ball* ActorList, int Count)//공생성하는 소스
{
    srand((unsigned int)time(NULL));
    for (int i = 0; i < Count; i++)
    {
        ActorList[i].pos.x = rand() % (area.right - 19) + 20;
        ActorList[i].pos.y = rand() % (area.bottom - 19) + 20;
        ActorList[i].radius = rand() % 31 + 20;


        for (int a = 0; a <= i; a++)//공안겹치게 하는 소스
        {
            if (a != i)
            {
                if (isHit_btb(ActorList[i], ActorList[a]) || isHit_btb({ { 20, 20 }, 20, { 255, 255, 255 } }, ActorList[a]))
                {
                    ActorList[i].pos.x = rand() % (area.right - 19) + 20;
                    ActorList[i].pos.y = rand() % (area.bottom - 19) + 20;
                    ActorList[i].radius = rand() % 31 + 20;
                    a = 0;
                }
            }
        }
        ActorList[i].color = { 0, 255, 0 };
    }
}
void newgame() {//새로 그려주는 소스

    static RECT area;
    second = 0;
    redBall = 0;
    greenBall = 30;
    GetClientRect(MainWnd, &area);
    pawn = { { 20, 20 }, 20, { 255, 255, 255 } };
    InitActor(area, Actor, ActorCount);
    SetTimer(MainWnd, 1, 1, NULL);
    InvalidateRect(MainWnd, NULL, true);
}
DWORD WINAPI timecounting(LPVOID temp)//시간, 공갯수 출력해주는 스레드
{
    HDC hdc;

    hdc = GetDC(MainWnd);
    wsprintf(tmp, TEXT("시간 : %d초 빨간색 공 : %d개/초록색 공 : %d개 "), second / 100, redBall, greenBall);
    TextOut(hdc, 10, 10, tmp, lstrlen(tmp));
    ReleaseDC(MainWnd, hdc);
    return 0;
}
LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    PAINTSTRUCT ps;
    static RECT area;
    static HBRUSH brush;
    static bool bActive;
    static bool bEnd;
    DWORD ThreadID;
    HANDLE hThread;
    switch (iMsg)
    {
    case WM_CREATE:
        GetClientRect(hwnd, &area);
        pawn = { { 20, 20 }, 20, { 255, 255, 255 } };
        InitActor(area, Actor, ActorCount);
        SetTimer(hwnd, 1, 1, NULL);

        break;
    case WM_KEYDOWN:

        switch (wParam) {
        case VK_LEFT:
            pawn.pos.x -= 10;
            break;
        case VK_RIGHT:
            pawn.pos.x += 10;
            break;
        case VK_UP:
            pawn.pos.y -= 10;
            break;
        case VK_DOWN:
            pawn.pos.y += 10;
            break;
        }

        InvalidateRect(hwnd, NULL, true);
        if (redBall == 30)
        {
            KillTimer(MainWnd, 1);
            wsprintf(tmp2, TEXT("Game Over!! \n시간 : %d초 \n다시하시겠습니까?"), second / 100);

            int gostop = MessageBox(MainWnd, tmp2, TEXT("Game Over"), MB_YESNO);
            if (gostop == IDNO) {
                PostQuitMessage(0);
                break;
            }
            else if (gostop == IDYES)
            {
                newgame();
            }
        }
    case WM_PAINT:
        hdc = BeginPaint(hwnd, &ps);
        for (auto actor : Actor)
        {
            brush = CreateSolidBrush(RGB(actor.color.r, actor.color.g, actor.color.b));
            SelectObject(hdc, brush);
            Ellipse(hdc, actor.pos.x - actor.radius, actor.pos.y - actor.radius, actor.pos.x + actor.radius, actor.pos.y + actor.radius);
            DeleteObject(brush);
        }
        brush = CreateSolidBrush(RGB(pawn.color.r, pawn.color.g, pawn.color.b));
        SelectObject(hdc, brush);
        Ellipse(hdc, pawn.pos.x - pawn.radius, pawn.pos.y - pawn.radius, pawn.pos.x + pawn.radius, pawn.pos.y + pawn.radius);
        DeleteObject(brush);
        EndPaint(hwnd, &ps);
        break;
    case WM_TIMER:
        switch (wParam) {
        case 1:
            hThread = CreateThread(NULL, 0, timecounting, NULL, 0, &ThreadID);
            second++;
            POINT pt;
            RECT WindowPos;
            GetCursorPos(&pt);
            GetWindowRect(hwnd, &WindowPos);
            for (int i = 0; i < ActorCount; i++)
            {
                if (isHit_btb(pawn, Actor[i]))
                {
                    Actor[i].color = { 255, 0, 0 };
                    checking();
                }
            }
            break;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return DefWindowProc(hwnd, iMsg, wParam, lParam);
}
