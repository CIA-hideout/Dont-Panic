#include "game.h"

//=============================================================================
// Constructor
//=============================================================================
Game::Game()
{
	// additional initialization is handled in later call to input->initialize()
	paused = false;             // game is not paused
	graphics = NULL;
	initialized = false;
}

//=============================================================================
// Destructor
//=============================================================================
Game::~Game()
{
	deleteAll();                // free all reserved memory
	ShowCursor(true);           // show cursor
}

//=============================================================================
// Window message handler
//=============================================================================
LRESULT Game::messageHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, msg, wParam, lParam);    // let Windows handle it
}

//=============================================================================
// Initializes the game
// throws GameError on error
//=============================================================================
void Game::initialize(HWND hw)
{
	hwnd = hw;                                  // save window handle

	input = new Input(hw);

	// initialize graphics
	graphics = new Graphics();
	// throws GameError
	graphics->initialize(hwnd, GAME_WIDTH, GAME_HEIGHT, FULLSCREEN);

	// attempt to set up high resolution timer
	if (QueryPerformanceFrequency(&timerFreq) == false)
		throw(GameError(gameErrorNS::FATAL_ERROR, "Error initializing high resolution timer"));

	QueryPerformanceCounter(&timeStart);        // get starting time

	initialized = true;

	D3DXCreateTeapot(graphics->get3Ddevice(), &teapot, 0);

	// projection matrix
	D3DXMATRIX proj;
	D3DXMatrixPerspectiveFovLH(&proj, D3DX_PI * 0.5f, graphics->viewPort.Width / graphics->viewPort.Height, 1.0f, 1000.0f);
	graphics->get3Ddevice()->SetTransform(D3DTS_PROJECTION, &proj);
	
	// world matrix. reference point 0, 0, 0
	D3DXMATRIX worldMat;
	D3DXMatrixIdentity(&worldMat);
	D3DXMatrixTranslation(&worldMat, 0, 0, 0);
	graphics->get3Ddevice()->SetTransform(D3DTS_WORLD, &worldMat);

	graphics->get3Ddevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

//=============================================================================
// Render game items
//=============================================================================
void Game::renderGame() {

	graphics->get3Ddevice()->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);
	graphics->get3Ddevice()->BeginScene();
	graphics->get3Ddevice()->SetFVF(CUSTOMFVF);

	render();           // call render() in derived object

	graphics->get3Ddevice()->EndScene();
	graphics->get3Ddevice()->Present(NULL, NULL, NULL, NULL);

	D3DXMATRIX viewMat;

	graphics->camera->getViewMatrix(&viewMat);
	graphics->get3Ddevice()->SetTransform(D3DTS_VIEW, &viewMat);
}

//=============================================================================
// Handle lost graphics device
//=============================================================================
void Game::handleLostGraphicsDevice()
{
	// test for and handle lost device
	hr = graphics->getDeviceState();
	if (FAILED(hr))                  // if graphics device is not in a valid state
	{
		// if the device is lost and not available for reset
		if (hr == D3DERR_DEVICELOST)
		{
			Sleep(100);             // yield cpu time (100 mili-seconds)
			return;
		}
		// the device was lost but is now available for reset
		else if (hr == D3DERR_DEVICENOTRESET)
		{
			releaseAll();
			hr = graphics->reset(); // attempt to reset graphics device
			if (FAILED(hr))          // if reset failed
				return;
			resetAll();
		}
		else
			return;                 // other device error
	}
}

//=============================================================================
// Call repeatedly by the main message loop in WinMain
//=============================================================================
void Game::run(HWND hwnd) {
	if (graphics == NULL)            // if graphics not initialized
		return;

	// calculate elapsed time of last frame, save in deltaTime
	QueryPerformanceCounter(&timeEnd);
	deltaTime = (float)(timeEnd.QuadPart - timeStart.QuadPart) / (float)timerFreq.QuadPart;

	// Power saving code, requires winmm.lib
	// if not enough time has elapsed for desired frame rate
	if (deltaTime < MIN_FRAME_TIME)
	{
		sleepTime = (DWORD)((MIN_FRAME_TIME - deltaTime) * 1000);
		timeBeginPeriod(1);         // Request 1mS resolution for windows timer
		Sleep(sleepTime);           // release cpu for sleepTime
		timeEndPeriod(1);           // End 1mS timer resolution
		return;
	}

	if (deltaTime > MAX_FRAME_TIME) // if frame rate is very slow
		deltaTime = MAX_FRAME_TIME; // limit maximum deltaTime

	timeStart = timeEnd;

	update();                   // update all game items
	ai();                       // artificial intelligence
	collisions();               // handle collisions

	renderGame();
}

void Game::releaseAll() {
}

void Game::resetAll()
{}

//=============================================================================
// Delete all reserved memory
//=============================================================================
void Game::deleteAll() {
	releaseAll();               // call onLostDevice() for every graphics item
	SAFE_DELETE(graphics);
	SAFE_DELETE(input);
	initialized = false;
}

void Game::updateMouse() {

}

void Game::updateKeyboard() {

}