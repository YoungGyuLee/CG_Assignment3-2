#include <iostream> 
#include <stdio.h> 
#include <stdlib.h> 
#include <fstream> 
#include <vector>
#include "CShaderLoader.h" 
#include "game.h"
using namespace glm;

MCIDEVICEID mID;

void setObjectColor(int color) {
	switch (color)
	{
	case RED:
		glColor3f(1.0, 0.0, 0.0);
		break;
	case GREEN:
		glColor3f(0.0, 1.0, 0.0);
		break;
	case BLUE:
		glColor3f(0.0, 0.0, 1.0);
		break;
	case YELLOW:
		glColor3f(1.0, 1.0, 0.0);
		break;
	case JUMP:
		glColor3f(0.0, 0.0, 0.0);
		break;
	default:
		glColor3f(0.0, 0.0, 0.0);
		break;
	}
}

void message(bool success) {
	HWND hwnd;
	HINSTANCE hInstance = GetModuleHandle(NULL);
	hwnd = CreateWindow(lpszClass, lpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, NULL, (HMENU)NULL, hInstance, NULL);

	if (success) {
		sound.playsound(WIN);
		cout << "Win" << endl;
		MessageBoxA(hwnd, "Win", "Win", MB_OK);
	}
	else {
		sound.playsound(LOSE);
		cout << "Lose" << endl;
		MessageBoxA(hwnd, "Lose", "Lose", MB_OK);
	}

	exit(0);
}



void renderScene(void) {
	//cout << " eeeE" << endl;
	glClearColor(0.2, 0.3, 0.3, 1.0);//clear red 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //use the created program 
	glGenVertexArrays(21, VAO); // we can also generate multiple VAOs or buffers at the same time
	glGenBuffers(21, VBO);

	player.playerDraw(program, VAO, VBO);
	thief.thiefDraw(program, VAO, VBO);
	///wall.draw(program, VAO[20], VBO[20]);

	currentTickCount = GetTickCount64();
	if (currentTickCount - startTickCount >= interval) {
		walls.push_back(CWall());
		walls[total].setWallPositionX(walls[total].getWallPositionX() + interval / 1000.0 * total);
		walls[total].setWall(DEFAULT);
		walls[total].setWallColor(DEFAULT);
		startTickCount = currentTickCount;
		total++;
	}

	for (int i = front; i < total; i++)
		walls[i].draw(program, VAO[20], VBO[20]);

	glutSwapBuffers();

	//glFlush();

	//glutPostRedisplay();


	/*
	mat4 transform = mat4(1.0f);
	//transform = translate(transform, vec3(0.2, 0.2, 0.0));
	//transform = rotate(transform, 180.0f, vec3(0.0, 0.0, 1.0));


	int transformLoc = glGetUniformLocation(program, "transform");
	//괄호 안에 있는 것이 vertex shader의 변수 이름과 같아야 함.
	//다시 말해 program(shader)의 "transform1")을 가져오겠다는 뜻.
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, value_ptr(transform));
	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	glutSwapBuffers();
	*/
}

void Init() {
	glEnable(GL_DEPTH_TEST); //load and compile shaders 
	CShaderLoader shaderLoader;
	program = shaderLoader.createProgram("vertex1.glsl", "fragment1.glsl");
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	cheatMode = NO;
	velocity = initVelocity;
	currentVelocity = velocity;

	startTickCount = GetTickCount64();

	srand((unsigned int)time(NULL));
	thief.setThiefPose(rand() % 5);

	walls.push_back(CWall());

	sound.playsound(BGM);


}

void doSystemCheck() {
	//If the wall and the thief collide ...
	if (walls[now].getWallPositionX() < (thief.getThiefPositionX())) {

		//Wall - change to thief color
		walls[now].setWallColor(thief.getThiefPose());
		walls[now].setWall(thief.getThiefPose());

		//Thief - jump timer start
		if (walls[now].getWallColor() == JUMP) {
			jumpThiefTimer = 0;
			jumpingThief = true;
		}

		//Thief - change to new color
		thief.setThiefPose(rand() % 5);
		sound.playsound(THIEFPASS);
		now++;
	}

	//System - check if pass or fail
	if (walls[previous].getWallPositionX() <= (player.getPlayerPositionX())) {

		switch (cheatMode)
		{
		case NO:
			if (player.getPlayerPose() == walls[previous].getWallColor()) {
				sound.playsound(PLAYERPASS);
				cout << "Pass" << endl;
				velocity += 0.01;
				interval -= 300;
				previousPlayerPosition = player.getPlayerPositionX();
				//player.setPassCount(passCount++);
				////.setPassCount(passCount++);
				pass = true;
			}
			else {
				sound.playsound(PLAYERNONPASS);
				cout << "Fail" << endl;
				failCount++;
				if (failCount >= 3)
					message(false);
				pass = false;
			}
			previous++;
			break;

		case ALL_PASS:
			cout << "Pass" << endl;
			sound.playsound(PLAYERPASS);
			velocity += 0.01;
			interval -= 300;
			previousPlayerPosition = player.getPlayerPositionX();
			pass = true;
			//player.setPassCount(passCount++);
			//thief.setPassCount(passCount++);
			previous++;
			break;

		case ALL_FAIL:
			sound.playsound(PLAYERNONPASS);
			cout << "Fail" << endl;
			failCount++;
			if (failCount >= 3)
				message(false);
			pass = false;
			previous++;
			break;
		}
	}

	//System - WIN if the distance between player and thief is less than a "threshold"
	//"threshold" == player.getPlayerSize()
	if (thief.getThiefPositionX() <= player.getPlayerPositionX())
		message(true);

	//System - LOSE after 3 minutes in all pass mode
	//if ((cheatMode == ALL_PASS) && (GetTickCount64() - allPassTimer > 1000 * 60 * 3))
	//	message(false);

	//System - LOSE if the player is out of the view
	//if (player.getPlayerPositionX() < currentVelocity * 25)
	//	message(false);

	glutPostRedisplay();
}


void doAnimation(int value) {
	//cout << thief.getThiefPositionX() + 1.8 << endl;

	currentVelocity = velocity;

	//cout << value << endl;
	//Wall - move wall in "currentVelocity"
	for (int i = 0; i < total; i++) {
		walls[i].setWallPositionX(walls[i].getWallPositionX() - currentVelocity);
		if (walls[i].getWallPositionX() + walls[i].getWallWidth() < -10) {
			walls[i].setWallPositionX(-10);
			front = i;
		}
	}

	//Thief - jump
	//부동소수점 오차를 무시하면 점프할 때마다 일정 거리만큼 왼쪽으로 가게 됨
	jumpThiefTimer++;
	if (jumpThiefTimer < (initVelocity / currentVelocity * 20) && jumpingThief)
	{
		thief.setThiefPositionX(thief.getThiefPositionX() - currentVelocity / 15.0f);
		thief.setThiefPositionY(thief.getThiefPositionY() + currentVelocity * 4.0f);
	}
	else if (jumpThiefTimer < (initVelocity / currentVelocity * 130) && jumpingThief)
	{
		thief.setThiefPositionX(thief.getThiefPositionX() - currentVelocity / 15.0f);

	}
	else if (jumpThiefTimer < (initVelocity / currentVelocity * 150) && jumpingThief)
	{
		thief.setThiefPositionX(thief.getThiefPositionX() - currentVelocity / 15.0f);
		thief.setThiefPositionY(thief.getThiefPositionY() - currentVelocity * 4.0f);

	}
	else if (jumpingThief)
	{
		thief.setThiefPositionY(-0.5f);
		jumpingThief = false;

	}

	//Player - jump
	//부동소수점 오차를 무시하면 점프할 때마다 일정 거리만큼 왼쪽으로 가게 됨
	jumpPlayerTimer++;
	if (jumpPlayerTimer < (initVelocity / currentVelocity * 20) && jumpingPlayer)
	{
		player.setPlayerPositionX(player.getPlayerPositionX() - currentVelocity / 15.0f);
		player.setPlayerPositionY(player.getPlayerPositionY() + currentVelocity * 4.0f);
	}
	else if (jumpPlayerTimer < (initVelocity / currentVelocity * 130) && jumpingPlayer)
	{
		player.setPlayerPositionX(player.getPlayerPositionX() - currentVelocity / 15.0f);
	}
	else if (jumpPlayerTimer < (initVelocity / currentVelocity * 150) && jumpingPlayer)
	{
		player.setPlayerPositionX(player.getPlayerPositionX() - currentVelocity / 15.0f);
		player.setPlayerPositionY(player.getPlayerPositionY() - currentVelocity * 4.0f);
	}
	else if (jumpingPlayer)
	{
		player.setPlayerPositionY(-0.5f);
		player.setPlayerPose(DEFAULT);
		jumpingPlayer = false;
	}

	//Player - move toward thief with moving animation
	if (pass) {
		player.setPlayerPositionX(player.getPlayerPositionX() + playerDistance);
		if ((player.getPlayerPositionX() - previousPlayerPosition) >= 0.3) {
			previousPlayerPosition = 0.0;
			pass = false;
			//cameraZoomIn();
		}
	}

	glutPostRedisplay();

	glutTimerFunc(1, doAnimation, 1);
}




void selectPose(int key, int x, int y) {
	sound.playsound(CHANGE);
	switch (key) {
	case GLUT_KEY_LEFT: //RED
		player.setPlayerPose(RED);
		break;
	case GLUT_KEY_RIGHT: //GREEN
		player.setPlayerPose(GREEN);
		break;
	case GLUT_KEY_UP: //BLUE
		player.setPlayerPose(BLUE);
		break;
	case GLUT_KEY_DOWN: //YELLOW
		player.setPlayerPose(YELLOW);
		break;
	}

	glutPostRedisplay();
}

void doKeyboard(unsigned char key, int x, int y) {

	cout << "in " << endl;
	switch (key)
	{
	case 32: // Space bar
		if (!jumpingPlayer)
		{
			//Plaer - jump timer start
			player.setPlayerPose(JUMP);
			jumpPlayerTimer = 0;
			jumpingPlayer = true;
			cout << "jump" << endl;
		}
		return;
	}

	switch (key) {
	case 'c':
		if (cheatMode == ALL_PASS)
			cheatMode = NO;
		else
			cheatMode = ALL_PASS;
		break;
	case 'f':
		if (cheatMode == ALL_FAIL)
			cheatMode = NO;
		else
			cheatMode = ALL_FAIL;
		break;
	}

	if (cheatMode == ALL_PASS) {
		cout << "All Pass Mode" << endl;
		allPassTimer = GetTickCount64();
	}
	else if (cheatMode == ALL_FAIL)
		cout << "All Fail Mode" << endl;
	else
		cout << "No Cheat" << endl;

	glutPostRedisplay();
}






int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1200, 800);
	glutCreateWindow("Drawing my first triangle");
	glewInit();
	//여기까지는 판 까는 과정. 이전과 크게 다를 게 없음.

	Init(); // register callbacks 
	glutDisplayFunc(renderScene);

	glutTimerFunc(0, doAnimation, 1);

	glutIdleFunc(doSystemCheck);

	glutKeyboardFunc(doKeyboard);
	glutSpecialFunc(selectPose);

	//glutTimerFunc(0, timerFunc, 1);
	glutMainLoop();
	glDeleteProgram(program);
	return 0;
}
