#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>
#include <vector>
#include <string>
#include "windows.h"

using namespace vizdoom;
using namespace cv;
using namespace std;


int main()
{
	DoomGame* game = new DoomGame();
	try
	{
		string path = "C:\\practice\\vizdoom";
		game->setViZDoomPath(path + "\\vizdoom.exe");
		game->setDoomGamePath(path + "\\DOOM2.wad");
		game->loadConfig(path + "\\scenarios\\basic.cfg");
		game->setWindowVisible(true);
		game->setRenderWeapon(true);
		game->init();


	}
	catch (exception& err)
	{
		cout << err.what() << endl;
	}
	namedWindow("DOOM2", WINDOW_AUTOSIZE);
	auto image = Mat(480, 640, CV_8UC3);

	unsigned int sleepTime = 10;

	auto episodes = 10;

	vector<double> actions[3];
	actions[0] = { 1,0,1 };
	actions[1] = { 0,1,1 };
	actions[2] = { 0,0,1 };

	for (auto i = 0; i < episodes; i++)
	{
		game->newEpisode();
		cout << "episode " << i << endl;
		while (!game->isEpisodeFinished()) {
			
			auto gamestate = game->getState();
			auto screenBuf = gamestate->screenBuffer;
			for (int j = 0; j < 30; j++) {
				game->makeAction(actions[0]);
			}
			for (int j = 0; j < 60; j++) {
				game->makeAction(actions[1]);
			}
			Sleep(sleepTime);
		}
	}
	game->close();
	delete game;
}
