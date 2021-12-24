#include <Windows.h>

LRESULT CALLBACK wndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)

{
    //1.윈도우 클래스 등록, 허가(운영체제)
    WNDCLASSW wc;
    ZeroMemory(&wc, sizeof(WNDCLASSW));
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = wndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"kgca_sample";
    RegisterClass(&wc);
    //2.윈도우 생성
    CreateWindow();

    MessageBox(NULL, L"test",L"kgca", MB_OK);
    return 1;
}
LRESULT CALLBACK wndProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
    switch (msg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    default:
        break;
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
}