// SolarSystem.cpp : 애플리케이션에 대한 진입점을 정의합니다.
//

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

#include <d3d9.h>
#include <d3dx9.h>
#include "framework.h"
#include "SolarSystem.h"

#define MAX_LOADSTRING 100

// 전역 변수:
WCHAR szTitle[MAX_LOADSTRING];                  // 제목 표시줄 텍스트입니다.
WCHAR szWindowClass[MAX_LOADSTRING];            // 기본 창 클래스 이름입니다.

D3DXMATRIXA16 g_MatEarth, g_MatMoon, g_MatSun;

// 이 코드 모듈에 포함된 함수의 선언을 전달합니다:
ATOM                MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);

//함수 선언부
HRESULT InitD3D(HWND);
void CleanUp();
void Render();
HRESULT InitVertexBuffer();
void SetUpMatrices();
HRESULT InitIndexBuffer();
void Update();
void DrawMesh(const D3DXMATRIXA16& matrix);

//함수 선언부 종료

LPDIRECT3DVERTEXBUFFER9 g_pVB = NULL;   //정점 버퍼 저장
struct CUSTOMVERTEX
{
    float x, y, z;
    DWORD color;
};
#define D3DFVF_CUSTOM (D3DFVF_XYZ | D3DFVF_DIFFUSE)

#define Deg2Rad 0.017453293f

LPDIRECT3DINDEXBUFFER9 g_pIB = NULL;    //인덱스 버퍼 저장
struct INDEX
{
    WORD _0, _1, _2;
};


//함수 정의부
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
    _In_opt_ HINSTANCE hPrevInstance,
    _In_ LPWSTR    lpCmdLine,
    _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: 여기에 코드를 입력합니다.

    // 전역 문자열을 초기화합니다.
    LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    LoadStringW(hInstance, IDC_SOLARSYSTEM, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    WNDCLASSEXW wcex = { sizeof(WNDCLASSEX), CS_HREDRAW | CS_VREDRAW, WndProc, 0, 0, hInstance,
        0, 0, 0, NULL, szWindowClass, NULL };
    RegisterClassExW(&wcex);

    // 애플리케이션 초기화를 수행합니다:
    HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_SYSMENU | WS_MINIMIZEBOX,
        CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

    if (!hWnd)
    {
        return FALSE;
    }

    if (SUCCEEDED(InitD3D(hWnd)))
    {
        if (SUCCEEDED(InitVertexBuffer()))
        {
            if (SUCCEEDED(InitIndexBuffer()))
            {
                ShowWindow(hWnd, nCmdShow);
                UpdateWindow(hWnd);

                MSG msg;
                ZeroMemory(&msg, sizeof(msg));
                ULONGLONG frameTime, LimitFrameTime = GetTickCount64();

                // 게임 루프.:
                while (WM_QUIT != msg.message)
                {
                    if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE))
                    {
                        TranslateMessage(&msg);
                        DispatchMessage(&msg);
                    }
                    else
                    {
                        Update();
                        Render();
                    }
                }
            }
        }
    }

    return 0;

    //return (int) msg.wParam;
}



//
//  함수: MyRegisterClass()
//
//  용도: 창 클래스를 등록합니다.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc = WndProc;
    wcex.cbClsExtra = 0;
    wcex.cbWndExtra = 0;
    wcex.hInstance = hInstance;
    wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SOLARSYSTEM));
    wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wcex.lpszMenuName = 0;
    wcex.lpszClassName = szWindowClass;
    wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

    return RegisterClassExW(&wcex);
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_DESTROY:
        CleanUp();
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

LPDIRECT3D9 g_pD3D = NULL;
LPDIRECT3DDEVICE9 g_pd3dDevice = NULL;

HRESULT InitD3D(HWND hWnd)
{
    if (NULL == (g_pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
        return E_FAIL;

    D3DPRESENT_PARAMETERS d3dpp;
    ZeroMemory(&d3dpp, sizeof(d3dpp));

    d3dpp.Windowed = TRUE;
    d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
    d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
    d3dpp.EnableAutoDepthStencil = TRUE;
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    DWORD Level;
    for (auto type = (int)D3DMULTISAMPLE_16_SAMPLES; 0 < type; type--)
    {
        if (SUCCEEDED(g_pD3D->CheckDeviceMultiSampleType(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, D3DFMT_D16,
            FALSE, (D3DMULTISAMPLE_TYPE)type, &Level)))
        {
            d3dpp.MultiSampleQuality = Level - 1;
            d3dpp.MultiSampleType = (D3DMULTISAMPLE_TYPE)type;
            break;
        }
    }

    //device 생성
    if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &d3dpp, &g_pd3dDevice)))
    {
        return E_FAIL;
    }

    g_pd3dDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
    g_pd3dDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
    g_pd3dDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
    g_pd3dDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, (0 < d3dpp.MultiSampleType));

    return S_OK;
}

void CleanUp()
{
    if (NULL != g_pIB)
        g_pIB->Release();
    if (NULL != g_pVB)
        g_pVB->Release();   //이거 맨 위에 둬야하는 거 아닌가
    if (NULL != g_pd3dDevice)
        g_pd3dDevice->Release();
    if (NULL != g_pD3D)
        g_pD3D->Release();
}

void Render()
{
    if (NULL == g_pd3dDevice)
        return;

    if (SUCCEEDED(g_pd3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 255), 1.0f, 0)))
    {
        SetUpMatrices();

        if (SUCCEEDED(g_pd3dDevice->BeginScene()))
        {
            //g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
            //g_pd3dDevice->SetFVF(D3DFVF_CUSTOM);
            ////g_pd3dDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
            //g_pd3dDevice->SetIndices(g_pIB);
            //g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
            DrawMesh(g_MatSun);
            DrawMesh(g_MatEarth);
            DrawMesh(g_MatMoon);
            g_pd3dDevice->EndScene();
        }

        g_pd3dDevice->Present(NULL, NULL, NULL, NULL);
    }
}

HRESULT InitVertexBuffer()
{
    //정점 버퍼 선언 함수
    
    CUSTOMVERTEX vertices[] =
    {
        { -1, 1, 1, 0xffffffff },
        { 1, 1, 1, 0x00000000 },
        { 1, 1, -1, 0xffffffff },
        { -1, 1, -1, 0x00000000 },

        { -1, -1, 1, 0xffffffff },
        { 1, -1, 1, 0x00000000 },
        { 1, -1, -1, 0xffffffff },
        { -1, -1, -1, 0x00000000 }
    };

    if (FAILED(g_pd3dDevice->CreateVertexBuffer(sizeof(vertices), 0, D3DFVF_CUSTOM, D3DPOOL_DEFAULT, &g_pVB, NULL)))
    {
        return E_FAIL;
    }

    LPVOID pVertices;
    if (FAILED(g_pVB->Lock(0, sizeof(vertices), (void**)&pVertices, 0)))
        return E_FAIL;
    memcpy(pVertices, vertices, sizeof(vertices));
    g_pVB->Unlock();

    return S_OK;
}

HRESULT InitIndexBuffer()
{
    //인덱스 버퍼 선언 함수

    INDEX Indices[] =
    {
        { 0, 1, 2 }, { 0, 2, 3 },
        { 4, 6, 5 }, { 4, 7, 6 },
        { 0, 3, 7 }, { 0, 7, 4 },
        { 1, 5, 6 }, { 1, 6, 2 },
        { 3, 2, 6 }, { 3, 6, 7 },
        { 0, 4, 5 }, { 0, 5, 1 },
    };

    if (FAILED(g_pd3dDevice->CreateIndexBuffer(sizeof(Indices), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &g_pIB,
        NULL)))
        return E_FAIL;

    LPVOID pIndices;
    if (FAILED(g_pIB->Lock(0, sizeof(Indices), (void**)&pIndices, 0)))
        return E_FAIL;
    memcpy(pIndices, Indices, sizeof(Indices));
    g_pIB->Unlock();

    return S_OK;
}

void SetUpMatrices()
{
    //D3DXMATRIXA16 MatWorld;
    //
    //D3DXMatrixIdentity(&MatWorld);
    //
    //g_pd3dDevice->SetTransform(D3DTS_WORLD, &MatWorld);

    //카메라 처리 함수

    D3DXVECTOR3 vEyePt(0.0f, 20.0f, -2.0f);
    D3DXVECTOR3 vLookAtPt(0.0f, 0.0f, 0.0f);
    D3DXVECTOR3 vUpVector(0.0f, 1, 0.0f);

    D3DXMATRIXA16 MatView;
    D3DXMatrixLookAtLH(&MatView, &vEyePt, &vLookAtPt, &vUpVector);

    g_pd3dDevice->SetTransform(D3DTS_VIEW, &MatView);

    D3DXMATRIXA16 MatProj;
    D3DXMatrixPerspectiveFovLH(&MatProj, 45 * Deg2Rad, 1.77f, 1.0f, 100.0f);
    g_pd3dDevice->SetTransform(D3DTS_PROJECTION, &MatProj);
}

void Update()
{
    auto AngleSun = GetTickCount64() * 0.001f;  //태양의 자전 주기
    auto AngleEarth = GetTickCount64() * 0.001f;  //지구의 공전 주기
    auto AngleMoon = GetTickCount64() * 0.002f;  //달의 공전 주기

    D3DXMATRIXA16 MatSunTr, MatSunRo;
    D3DXMATRIXA16 MatEarthTr, MatEarthRo, MatEarthSc;
    D3DXMATRIXA16 MatMoonTr, MatMoonRo, MatMoonSc;

    D3DXMatrixIdentity(&MatSunTr);
    //D3DXMatrixRotationX(&MatSunRo, AngleSun * 5);
    D3DXMatrixRotationY(&MatSunRo, AngleSun);

    g_MatSun = MatSunRo * MatSunTr;

    
    D3DXMatrixScaling(&MatEarthSc, 0.3f, 0.3f, 0.3f);
    D3DXMatrixRotationY(&MatEarthRo, AngleEarth);
    D3DXMatrixTranslation(&MatEarthTr, 8, 0, 0);

    g_MatEarth = MatEarthSc * MatEarthRo * MatEarthTr * MatEarthRo * g_MatSun;

    D3DXMatrixScaling(&MatMoonSc, 0.3f, 0.3f, 0.3f);
    D3DXMatrixRotationY(&MatMoonRo, AngleMoon); //달의 자전 주기=달의 공전 주기
    D3DXMatrixTranslation(&MatMoonTr, 5, 0, 0);

    g_MatMoon = MatMoonSc * MatMoonTr * MatMoonRo * g_MatEarth;
}

void DrawMesh(const D3DXMATRIXA16& matrix)
{
    g_pd3dDevice->SetTransform(D3DTS_WORLD, &matrix);
    g_pd3dDevice->SetStreamSource(0, g_pVB, 0, sizeof(CUSTOMVERTEX));
    g_pd3dDevice->SetFVF(D3DFVF_CUSTOM);
    g_pd3dDevice->SetIndices(g_pIB);
    g_pd3dDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
}

//태양을 중심으로 도는 지구와 달
//태양을 지금 지구 크기로 두고 지구를 좀 줄이고 달도 줄이고
//카메라를 탑뷰로 고치고 싶다 태양계 돌아가는 꼴 좀 잘 보게