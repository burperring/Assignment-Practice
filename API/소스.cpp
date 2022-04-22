#include <windows.h>
#include <math.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg,WPARAM wParam, LPARAM lparam);
LPCTSTR lpszClass=TEXT("Class");

HINSTANCE g_hInst;
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPTSTR lpszCmdLine, int nCmdShow)
{
    HWND hwnd;
    MSG msg;
    WNDCLASS WndClass;

    g_hInst = hInstance;

    WndClass.style = CS_HREDRAW | CS_VREDRAW;
    WndClass.lpfnWndProc = WndProc;
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.hInstance = hInstance;
    WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
    WndClass.lpszMenuName = NULL;
    WndClass.lpszClassName = lpszClass;
    RegisterClass(&WndClass);
    hwnd = CreateWindow(lpszClass, lpszClass,
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        NULL,
        NULL,
        hInstance,
        NULL
    );
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);
    while (GetMessage(&msg, NULL, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}

#define PI 3.141592
#define BULLET_SIZE 100
#define BULLET_SPEED 10

struct Bullet
{
    int posx;
    int posy;
    int velx;
    int vely;

    int isUse;
};

struct Bullet bullets[BULLET_SIZE] = { 0, };

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    PAINTSTRUCT ps;
    HDC hdc;
    static int addDEGREE = 0;
    static int POSX = 0;
    static int POSY = 0;
    static int DEGREE = 0;
    static float radian = 0;
    static float lineLength = 0;
    static float x = 0;
    static float y = 0;

    static int posX = 0;
    static int posY = 0;
    static int radius = 0;


    switch (message)
    {
    case WM_CREATE:
        SetTimer(hWnd, 0, 20, NULL);//���� ���� �����(20/1000�� ���� WM_TIMER�޼����� �߻�)
        break;
    case WM_PAINT:
    {
        hdc = BeginPaint(hWnd, &ps);

        Ellipse(hdc, posX - radius, posY - radius, posX + radius, posY + radius);
        MoveToEx(hdc, posX, posY, NULL);
        LineTo(hdc, posX + x * lineLength, posY + y * lineLength);

        //�Ѿ˱׷��ֱ�
        for (int i = 0;i < BULLET_SIZE;i++)
        {
            if (bullets[i].isUse == 1)//�Ѿ��� ������϶��� �׷��ֱ�
            {
                Ellipse(hdc, bullets[i].posx - 5, bullets[i].posy - 5, bullets[i].posx + 5, bullets[i].posy + 5);
            }
        }

        EndPaint(hWnd, &ps);
        break;
    }
    case WM_KEYDOWN:
        switch (wParam)
        {
        case VK_RIGHT:    addDEGREE += 10;  break;
        case VK_LEFT:     addDEGREE -= 10;  break;
        case VK_UP:       addDEGREE -= 10;  break;
        case VK_DOWN:     addDEGREE += 10;  break;

        case VK_SPACE:
            if (DEGREE)
            {
                POSX += x * 10;
                POSY += y * 10;
            }   break;
        }
        InvalidateRect(hWnd, NULL, true);
        break;
    case WM_LBUTTONDOWN:
    {
        int i;
        for (i = 0;i < BULLET_SIZE;i++)
        {
            if (bullets[i].isUse == 0)//��������� �ʴ� �Ѿ� �˾Ƴ���
            {
                break;
            }
        }

        if (i < BULLET_SIZE)//��������� �ʴ� �Ѿ��� �ִٸ�
        {
            bullets[i].isUse = 1;//��������� �ٲ��ְ�
            bullets[i].posx = posX + x * lineLength;
            bullets[i].posy = posY + y * lineLength;//�Ѿ��� ������ġ

            bullets[i].velx = x * BULLET_SPEED;
            bullets[i].vely = y * BULLET_SPEED;//�Ѿ� ������ ��
        }
        break;
    }

    case WM_TIMER:
    {
        DEGREE = 30 + addDEGREE;
        float onedegree = PI / 180;
        radian = onedegree * DEGREE;
        x = cosf(radian);
        y = sinf(radian);
        lineLength = 100.0f;
        posX = 100 + POSX;
        posY = 100 + POSY;
        radius = 30;

        RECT rect;

        GetClientRect(hWnd, &rect);//ȭ�� ũ�� ������

        //�Ѿ� �����̱�
        int i;
        for (i = 0;i < BULLET_SIZE;i++)
        {
            if (bullets[i].isUse == 1)//�������(�����̰� �ִ� �Ѿ��̶��)
            {
                bullets[i].posx += bullets[i].velx;
                bullets[i].posy += bullets[i].vely;//�Ѿ��� ������

                if (bullets[i].posx < 0 || bullets[i].posx > rect.right &&
                    bullets[i].posy < 0 || bullets[i].posy > rect.bottom)//�Ѿ��� ȭ���� �����
                {
                    bullets[i].isUse = 0;//�������
                }
            }
        }

    }
    InvalidateRect(hWnd, NULL, TRUE);
    break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}