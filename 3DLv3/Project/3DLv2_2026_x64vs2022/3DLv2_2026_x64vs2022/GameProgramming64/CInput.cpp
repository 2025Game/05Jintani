#include "CInput.h"
#include <stdio.h>

CInput::CInput()
{
	printf("入力インスタンスが生まれました\n");
}

bool CInput::Key(char key)
{
	return GetAsyncKeyState(key) < 0;
}

// ウィンドウのポインタ
GLFWwindow* CInput::spWindow = nullptr;
void CInput::Window(GLFWwindow* pwindow)
{
	spWindow = pwindow;
}
void CInput::MouseGetPosition(double* x, double* y)
{
	//マウス座標を取得する
	glfwGetCursorPos(spWindow, x, y);
}
void CInput::MouseShowCursor(bool isShow)
{
	//マウスカーソルの表示設定する
	glfwSetInputMode
	(
		spWindow,
		GLFW_CURSOR,
		isShow ? GLFW_CURSOR_NORMAL :
		GLFW_CURSOR_DISABLED
	);
}