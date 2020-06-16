
#include <iostream>
#include <windows.h>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>


using namespace vizdoom;
using namespace cv;
using namespace std;


int main()
{
	DoomGame* game = new DoomGame;
	try {
		string path = "C:\\practice\\vizdoom";
		game->setViZDoomPath(path + "\\vizdoom.exe");
		game->setDoomGamePath(path + "\\freedoom2.wad");
		game->loadConfig(path + "\\scenarios\\basic.cfg");
		game->init();
	}
	catch (exception& e)
	{
		cout << e.what() << endl;
		return 0;
	}

	namedWindow("Control Window", WINDOW_AUTOSIZE);
	auto image = Mat(480, 640, CV_8UC3);

	unsigned int sleepTime = 1000 / DEFAULT_TICRATE;

	auto episodes = 10;

	std::vector<double> actions[3];
	actions[0] = { 1,0,0 };
	actions[1] = { 0,1,0 };
	actions[2] = { 0,0,1 };

	for (auto i = 0; i < episodes; i++) {
		game->newEpisode();

		while (!game->isEpisodeFinished()) {
			auto gamestate = game->getState();

			BufferPtr screenBuf = gamestate->screenBuffer;

			image.data = screenBuf->data();

			game->makeAction(actions[std::rand() % game->getAvailableButtonsSize()]);
			
			if (sleepTime) Sleep(sleepTime);

			waitKey(sleepTime);
		}
	}
	
	game->close();
	delete game;

}
