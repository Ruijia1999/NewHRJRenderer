// HRJRenderer.cpp : Defines the entry point for the application.
//

#include "HRJRenderer.h"
#include "Renderer/Draw.h"
#include "Renderer/Model.h"
#include "Renderer/Camera.h"
#include "Math/Quaternion.h"
#include "Input/Input.h"
#include "Renderer/Light.h"
#include "Renderer/Color.h"
#include <windowsx.h>
#define MAX_LOADSTRING 100
#define IDB_DRAWMODE  3301
#define IDB_FLAT   3302  
#define IDB_GOURAUD     3303  
#define DRAW_MESH 101
#define DRAW_COLOR 102

static HRJRenderer::Camera s_camera;
HRJRenderer::Input::InputStatus s_input;
// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HRJRenderer::Model model("C:\\Users\\rjhua\\Desktop\\New folder\\HRJRenderer\\Resources\\head.obj");
HRJRenderer::Light::LightSetting lightSetting;

int drawMode = DRAW_COLOR;
int shaderType = 1001;

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    
     UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);
    //Initialize
   
    HRJRenderer::Draw::Initialize(500, 500);
    s_camera.position = HRJRenderer::Vector3 (0, 0, 1.5);
    lightSetting.diffuseLight.direction = HRJRenderer::Vector3(0, 0, 1);
    lightSetting.diffuseLight.lightColor = HRJRenderer::Color(1, 1, 1,1);
    // TODO: Place code here.
    LPPOINT point;
    // Initialize global strings
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_HRJRENDERER, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HRJRENDERER));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}


HWND btn_DrawMode;
HWND btn_Flat;
HWND btn_Gouraud;

//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HRJRENDERER));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
    wcex.lpszMenuName   = MAKEINTRESOURCEW(IDC_HRJRENDERER);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
       CW_USEDEFAULT, CW_USEDEFAULT, 630, 550, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

void Paint(HDC hdc) {
    
    HDC hMemeDC;
    HBITMAP hbmp = CreateCompatibleBitmap(hdc, 500, 500);
    hMemeDC = CreateCompatibleDC(hdc);
    SelectObject(hMemeDC, hbmp); 
    HRJRenderer::Draw::ClearColor(500, 500);
    HRJRenderer::Draw::SubmitCamera(HRJRenderer::Math::CreateWorldToCameraTransform(s_camera.rotate, s_camera.position), HRJRenderer::Math::CreateCameraToProjectedTransform_perspective(1.5708, 1, 1, 10), HRJRenderer::Math::Matrix_transform(HRJRenderer::Math::Quaternion(), HRJRenderer::Vector3(0,0,0)));
    HRJRenderer::Draw::SubmitLight(lightSetting, model);
   
    //HRJRenderer::DrawTiangle(HRJRenderer::Vector2(0, 0), HRJRenderer::Vector2(300, 300), HRJRenderer::Vector2(0, 300), RGB(255, 0, 0), hMemeDC);
if(drawMode==DRAW_MESH)
    HRJRenderer::Draw::DrawModelMesh(model, HRJRenderer::Color(1, 1, 1, 1), hMemeDC);
else if(drawMode == DRAW_COLOR)
    HRJRenderer::Draw::DrawModel(HRJRenderer::Color(1, 1, 1,1), shaderType, hMemeDC);

    BitBlt(hdc, 0, 0, 500, 500, hMemeDC, 0, 0, SRCCOPY);
    DeleteDC(hMemeDC);

}
//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_CREATE:
    {
        HBITMAP MemBitmap;
        btn_DrawMode = CreateWindowW(L"Button", L"Mesh", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 500, 0, 115, 30, hWnd, (HMENU)IDB_DRAWMODE, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        btn_Flat = CreateWindowW(L"Button", L"Flat Shading", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 500, 50, 115, 30, hWnd, (HMENU)IDB_FLAT, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        btn_Gouraud = CreateWindowW(L"Button", L"Gouraud Shading", BS_PUSHBUTTON | WS_CHILD | WS_VISIBLE, 500, 80, 115, 30, hWnd, (HMENU)IDB_GOURAUD, ((LPCREATESTRUCT)lParam)->hInstance, NULL);
        
        
    }
    break;
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_EXIT:
                DestroyWindow(hWnd);
                break;
            case IDB_DRAWMODE:
                if (drawMode == DRAW_COLOR) {
                    drawMode = DRAW_MESH;
                    SendMessage(btn_DrawMode, WM_SETTEXT, 0, (LPARAM)L"Color");
                }
                else if (drawMode == DRAW_MESH) {
                    drawMode = DRAW_COLOR;
                    SendMessage(btn_DrawMode, WM_SETTEXT, 0, (LPARAM)L"Mesh");
                }

                InvalidateRect(hWnd, NULL, true);
                SendMessage(hWnd, WM_PAINT, wParam, lParam);
                break;
            case IDB_FLAT:
            {
                shaderType = 1001;
                InvalidateRect(hWnd, NULL, true);
                SendMessage(hWnd, WM_PAINT, wParam, lParam);
            }
            break;
            case IDB_GOURAUD:
            {
                shaderType = 1002;
                InvalidateRect(hWnd, NULL, true);
                SendMessage(hWnd, WM_PAINT, wParam, lParam);
            }
            break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_SETTEXT:
    {
       
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDB_DRAWMODE:
                int i = 0;
            }
    }
    break;
    case WM_ERASEBKGND:
        return TRUE;
    case WM_LBUTTONDOWN:
    {
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);
        s_input.StartDrag(xPos,yPos);
    }
        
        break;
    case WM_LBUTTONUP:
    {
        s_input.isLeftPressed = false;
    }

    break;
    case WM_PAINT:
        {
            
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hWnd, &ps);
        
        Paint( hdc);
        
        EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    case WM_MOUSEMOVE:
    {
        int xPos = GET_X_LPARAM(lParam);
        int yPos = GET_Y_LPARAM(lParam);
        if (s_input.isLeftPressed) {
            HRJRenderer::Vector2 moveVec = s_input.GetDragVec(xPos, yPos)/500;
            s_camera.position.x += moveVec.x;
            s_camera.position.y -= moveVec.y;
            InvalidateRect(hWnd, NULL, true);
            SendMessage(hWnd, WM_PAINT, wParam, lParam);
        }
    }
    break;
   
    default:
        
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}


// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}
