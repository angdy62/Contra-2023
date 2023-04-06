/* =============================================================
	INTRODUCTION TO GAME PROGRAMMING SE102
	
	SAMPLE 02 - SPRITE AND ANIMATION

	This sample illustrates how to:

		1/ Render a sprite (within a sprite sheet)
		2/ How to manage sprites/animations in a game
		3/ Enhance CGameObject with sprite animation
================================================================ */

#include <Windows.h>
#include <d3d10.h>
#include <d3dx10.h>

#include "debug.h"
#include "Game.h"
#include "Textures.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Animation.h"
#include "Animations.h"


#include "Mario.h"


#define WINDOW_CLASS_NAME L"SampleWindow"
#define MAIN_WINDOW_TITLE L"02 - Sprite animation"
#define WINDOW_ICON_PATH L"mario.ico"

#define BACKGROUND_COLOR D3DXCOLOR(200.0f/255, 200.0f/255, 255.0f/255,0.0f)
#define SCREEN_WIDTH 320
#define SCREEN_HEIGHT 240

#define ID_TEX_MARIO 0
#define ID_TEX_ENEMY 10
#define ID_TEX_MISC 20

#define TEXTURES_DIR L"textures"
#define TEXTURE_PATH_MARIO TEXTURES_DIR "\\mario.png"
#define TEXTURE_PATH_MISC TEXTURES_DIR "\\misc_transparent.png"
#define TEXTURE_PATH_ENEMIES TEXTURES_DIR "\\enemies.png"

CMario *mario;
#define MARIO_START_X 10.0f
#define MARIO_START_Y 130.0f
#define MARIO_START_VX 0.1f

CBrick *brick;

LRESULT CALLBACK WinProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message) {
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

/*
	Load all game resources 
	In this example: load textures, sprites, animations and mario object
*/
void LoadResources()
{
	CTextures * textures = CTextures::GetInstance();

	textures->Add(ID_TEX_MARIO, TEXTURE_PATH_MARIO);
	//textures->Add(ID_ENEMY_TEXTURE, TEXTURE_PATH_ENEMIES, D3DCOLOR_XRGB(156, 219, 239));
	textures->Add(ID_TEX_MISC, TEXTURE_PATH_MISC);


	CSprites * sprites = CSprites::GetInstance();
	
	LPTEXTURE texMario = textures->Get(ID_TEX_MARIO);

	// readline => id, left, top, right 
	//Bill Walk
	/*sprites->Add(10001, 25,	24,	44,	59, texMario);
	sprites->Add(10002, 90,	27,	110, 58, texMario);
	sprites->Add(10003, 157, 25, 173, 59, texMario);
	sprites->Add(10004, 220, 25, 238, 59, texMario);
	sprites->Add(10005, 285, 27, 305, 58, texMario);
	sprites->Add(10006, 353, 24, 369, 59, texMario);*/

	//Bill Jump
	sprites->Add(10011, 805, 98, 821, 118, texMario);
	sprites->Add(10012, 868, 99, 887, 115, texMario);
	sprites->Add(10013, 935, 96, 951, 116, texMario);
	sprites->Add(10014, 999, 99, 1018, 115, texMario);

	//Bill Swim

	sprites->Add(10001, 1065, 435, 1081, 448, texMario);
	sprites->Add(10002, 1132, 428, 1148, 442, texMario);
	sprites->Add(10003, 1197, 427, 1213, 441, texMario);
	sprites->Add(10004, 1260, 424, 1280, 441, texMario);

	//Lance Walk
	/*sprites->Add(10001, 25,	292, 44, 327, texMario);
	sprites->Add(10002, 90, 295, 110, 326, texMario);
	sprites->Add(10003, 157, 293, 173, 327, texMario);
	sprites->Add(10004, 220, 293, 238, 327, texMario);
	sprites->Add(10005, 285, 295, 305, 326, texMario);
	sprites->Add(10006, 353, 292, 369, 327, texMario);
	//Lance Jump
	sprites->Add(10011, 186, 154, 200, 181, texMario);
	sprites->Add(10012, 155, 154, 171, 181, texMario);
	sprites->Add(10013, 125, 154, 141, 181, texMario);*/

	//RD008 Walk
	/*sprites->Add(10001, 1063, 24, 1083, 58, texMario);
	sprites->Add(10002, 1127, 25, 1148, 59, texMario);
	sprites->Add(10003, 1195, 24, 1210, 58, texMario);
	sprites->Add(10004, 1258, 24, 1275, 58, texMario);
	sprites->Add(10005, 1321, 25, 1343, 58, texMario);
	sprites->Add(10006, 1392, 24, 1408, 58, texMario);
	//RD008 Jump
	sprites->Add(10011, 1845, 102, 1861, 118, texMario);
	sprites->Add(10012, 1910, 102, 1926, 118, texMario);
	sprites->Add(10013, 1975, 102, 1991, 118, texMario);
	sprites->Add(10014, 2040, 102, 2056, 118, texMario);*/

	//RC011 Walk
	/*sprites->Add(10001, 1063, 292, 1083, 326, texMario);
	sprites->Add(10002, 1127, 293, 1148, 327, texMario);
	sprites->Add(10003, 1195, 292, 1210, 326, texMario);
	sprites->Add(10004, 1258, 292, 1275, 326, texMario);
	sprites->Add(10005, 1322, 293, 1343, 327, texMario);
	sprites->Add(10006, 1392, 292, 1408, 326, texMario);*/
	//RC011 Jump
	/*sprites->Add(10011, 1845, 370, 1861, 386, texMario);
	sprites->Add(10012, 1910, 370, 1926, 386, texMario);
	sprites->Add(10013, 1975, 370, 1991, 386, texMario);
	sprites->Add(10014, 2040, 370, 2056, 386, texMario);*/


	CAnimations * animations = CAnimations::GetInstance();
	LPANIMATION ani;

	ani = new CAnimation(100);
	ani->Add(10001);
	ani->Add(10002);
	ani->Add(10003);
	ani->Add(10004);
	/*ani->Add(10005);
	ani->Add(10006);*/

	animations->Add(500, ani);



	ani = new CAnimation(100);
	ani->Add(10011);
	ani->Add(10012);
	ani->Add(10013);
	animations->Add(501, ani);



	LPTEXTURE texMisc = textures->Get(ID_TEX_MISC);


	sprites->Add(20001, 300, 117, 317, 133, texMisc);
	sprites->Add(20002, 318, 117, 335, 133, texMisc);
	sprites->Add(20003, 336, 117, 353, 133, texMisc);
	sprites->Add(20004, 354, 117, 371, 133, texMisc);



	ani = new CAnimation(100);
	ani->Add(20001,1000);
	ani->Add(20002);
	ani->Add(20003);
	ani->Add(20004);
	animations->Add(510, ani);
	
	
	mario = new CMario(MARIO_START_X, MARIO_START_Y, MARIO_START_VX);
	//brick = new CBrick(100.0f, 100.0f);
}

/*
	Update world status for this frame
	dt: time period between beginning of last frame and beginning of this frame
*/
void Update(DWORD dt)
{
	mario->Update(dt);
}

void Render()
{
	CGame* g = CGame::GetInstance();

	ID3D10Device* pD3DDevice = g->GetDirect3DDevice();
	IDXGISwapChain* pSwapChain = g->GetSwapChain();
	ID3D10RenderTargetView* pRenderTargetView = g->GetRenderTargetView();
	ID3DX10Sprite* spriteHandler = g->GetSpriteHandler();

	if (pD3DDevice != NULL)
	{
		// clear the background 
		pD3DDevice->ClearRenderTargetView(pRenderTargetView, BACKGROUND_COLOR);

		spriteHandler->Begin(D3DX10_SPRITE_SORT_TEXTURE);

		// Use Alpha blending for transparent sprites
		FLOAT NewBlendFactor[4] = { 0,0,0,0 };
		pD3DDevice->OMSetBlendState(g->GetAlphaBlending(), NewBlendFactor, 0xffffffff);

		//brick->Render();
		mario->Render();

		// Uncomment this line to see how to draw a porttion of a texture  
		//g->Draw(10, 10, texMisc, 300, 117, 316, 133);


		spriteHandler->End();
		pSwapChain->Present(0, 0);
	}
}

HWND CreateGameWindow(HINSTANCE hInstance, int nCmdShow, int ScreenWidth, int ScreenHeight)
{
	WNDCLASSEX wc;
	wc.cbSize = sizeof(WNDCLASSEX);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.hInstance = hInstance;

	wc.lpfnWndProc = (WNDPROC)WinProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = (HICON)LoadImage(hInstance, WINDOW_ICON_PATH, IMAGE_ICON, 0, 0, LR_LOADFROMFILE);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = WINDOW_CLASS_NAME;
	wc.hIconSm = NULL;

	RegisterClassEx(&wc);

	HWND hWnd =
		CreateWindow(
			WINDOW_CLASS_NAME,
			MAIN_WINDOW_TITLE,
			WS_OVERLAPPEDWINDOW, // WS_EX_TOPMOST | WS_VISIBLE | WS_POPUP,
			CW_USEDEFAULT,
			CW_USEDEFAULT,
			ScreenWidth,
			ScreenHeight,
			NULL,
			NULL,
			hInstance,
			NULL);

	if (!hWnd)
	{
		DWORD ErrCode = GetLastError();
		DebugOut(L"[ERROR] CreateWindow failed! ErrCode: %d\nAt: %s %d \n", ErrCode, _W(__FILE__), __LINE__);
		return 0;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	SetDebugWindow(hWnd);

	return hWnd;
}

int Run()
{
	MSG msg;
	int done = 0;
	ULONGLONG frameStart = GetTickCount64();
	ULONGLONG tickPerFrame = 1000 / MAX_FRAME_RATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		ULONGLONG now = GetTickCount64();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		ULONGLONG dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;
			Update((DWORD)dt);
			Render();
		}
		else
			Sleep((DWORD)(tickPerFrame - dt));
	}

	return 1;
}

int WINAPI WinMain(
	_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPSTR lpCmdLine,
	_In_ int nCmdShow
) {
	HWND hWnd = CreateGameWindow(hInstance, nCmdShow, SCREEN_WIDTH, SCREEN_HEIGHT);

	CGame *game = CGame::GetInstance();
	game->Init(hWnd);

	LoadResources();

	SetWindowPos(hWnd, 0, 0, 0, SCREEN_WIDTH * 2, SCREEN_HEIGHT * 2, SWP_NOMOVE | SWP_NOOWNERZORDER | SWP_NOZORDER);

	Run();

	return 0;
}