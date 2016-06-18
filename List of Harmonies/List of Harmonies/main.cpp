#include < stdio.h >
#include "GL\freeglut.h"
#include "lkn_library\camera.h"
#include "lkn_library\graphics_manager.h"
#include "lkn_engine\game_object.h"
#include "game\manager.h"
#include "lkn_library\input_manager.h"

//----------------------------------------------------
// 関数プロトタイプ（後に呼び出す関数名と引数の宣言）
//----------------------------------------------------
void init(void);
void display(void);
void timer(int value);
void keyboard(unsigned char _key, int _x, int _y);
void keyboardUp(unsigned char _key, int x, int y);

//----------------------------------------------------
// メイン関数
//----------------------------------------------------
int main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(800, 600);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);
	glutCreateWindow(argv[0]);

	glutKeyboardFunc(keyboard); //void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	glutKeyboardUpFunc(keyboardUp); //void (GLUTCALLBACK *func)(unsigned char key, int x, int y)
	glutIgnoreKeyRepeat(GL_TRUE);//(int ignore)

	glutTimerFunc(100, timer, 0);
	glutDisplayFunc(display);
	init();
	glutMainLoop();
	return 0;
}

// 60fps ( 1/60 秒 ) ごとに実行される関数 
void timer(int value) {

	glutPostRedisplay();
	// 1000ミリ秒で 1 秒
	glutTimerFunc(1000 / 60, timer, 0);

}


//----------------------------------------------------
// 初期設定の関数
//----------------------------------------------------
void init(void) {

	lkn::Camera* camera = lkn::GraphicsManager::getInstance()->camera;
	camera->pos.z = 10.0f;
	camera->pos.y = 5.0f;

}
//----------------------------------------------------
// 描画の関数
//----------------------------------------------------
void display(void) {

	game::GameManager::getInstance()->update();
	lkn::GameObject::system_update();
	lkn::GraphicsManager::getInstance()->render();

	for (int i = 0; i < 256; i++) {
		lkn::InputManager::getInstance()->last_keys[i] = lkn::InputManager::getInstance()->keys[i];
	}
}

void keyboard(unsigned char _key, int _x, int _y) {
	//lkn::InputManager::getInstance()->last_keys[_key] = lkn::InputManager::getInstance()->keys[_key];
	lkn::InputManager::getInstance()->keys[_key] = true;
}

void keyboardUp(unsigned char _key, int x, int y) {
	lkn::InputManager::getInstance()->keys[_key] = false;
}