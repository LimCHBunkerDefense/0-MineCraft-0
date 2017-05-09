#pragma once

#define INPUT cInputManager::GetInstance()

#define KEY_COUNT		256
#define MOUSE_COUNT		3

enum KEY_STATE
{
	KEY_NONE, KEY_DOWN, KEY_UP, KEY_PRESS,
};

enum MOUSE_STATE
{
	MOUSE_NONE, MOUSE_DOWN, MOUSE_UP, MOUSE_PRESS, MOUSE_DRAG,
};

enum MOUSE_BUTTON
{
	MOUSE_LEFT, MOUSE_CENTER, MOUSE_RIGHT,
};

enum BUTTON_STATE
{
	BUTTON_STATE_NONE,
	BUTTON_STATE_OVER,
	BUTTON_STATE_CLICK,
	BUTTON_STATE_SELECTED,
};

class cInputManager
{
public:
	SINGLETONE(cInputManager);

private:
	HWND m_hWnd;
	KEY_STATE m_keyStates[KEY_COUNT];
	MOUSE_STATE m_mouseStates[MOUSE_COUNT];

	POINT m_mousePrevPos;
	POINT m_mouseCurrentPos;
	POINT m_mouseDeltaPos;

	void UpdateKeyState();
	void UpdateMouseState();

public:
	void Setup();
	void Update();

	KEY_STATE GetKeyState(int key) { return m_keyStates[key]; }
	MOUSE_STATE GetMouseState(MOUSE_BUTTON btn) { return m_mouseStates[btn]; }

	POINT GetMousePos() { return m_mouseCurrentPos; }
	POINT GetMouseDelta() { return m_mouseDeltaPos; }

	bool IsKeyDown(int key) { return GetKeyState(key) == KEY_DOWN; }
	bool IsKeyUp(int key) { return GetKeyState(key) == KEY_UP; }
	bool IsKeyPress(int key) { return GetKeyState(key) == KEY_PRESS; }

	bool IsMouseDown(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_DOWN; }
	bool IsMouseUp(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_UP; }
	bool IsMousePress(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_PRESS || GetMouseState(btn) == MOUSE_DRAG; }
	bool IsMouseDrag(MOUSE_BUTTON btn) { return GetMouseState(btn) == MOUSE_DRAG; }

	bool IsCollided(D3DXVECTOR2 leftTop, D3DXVECTOR2 rightBottom);
};

