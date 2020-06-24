#include <iostream>
#include <opencv2/opencv.hpp>
#include <ViZDoom.h>
#include <vector>
#include <string>
#include "windows.h"
#include "math.h"


vizdoom::DoomGame* game = new vizdoom::DoomGame();
auto screenBuff = cv::Mat(480, 640, CV_8UC3);
unsigned int sleepTime = 30;
std::string path = "C:\\practice\\vizdoom";


void RunTaskTest(int episodes) {

	try
	{
		game->loadConfig(path + "\\scenarios\\basic.cfg");
		game->init();
	}
	catch (std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}

	std::vector<double> actions[3];
	actions[0] = { 1,0,1 };
	actions[1] = { 0,1,1 };
	actions[2] = { 0,0,1 };

	for (auto i = 0; i < episodes; i++)
	{
		game->newEpisode();
		std::cout << "episode " << i << std::endl;
		while (!game->isEpisodeFinished()) {

			auto gamestate = game->getState();
			auto screenBuf = gamestate->screenBuffer;
			for (int j = 0; j < 30; j++) {
				game->makeAction(actions[0]);
				Sleep(sleepTime);
			}
			for (int j = 0; j < 60; j++) {
				game->makeAction(actions[1]);
				Sleep(sleepTime);
			}
			
		}
	}
}

void RunTask1(int episodes) {

	float result = 0.0;

	try
	{
		game->setWindowVisible(true);
		game->setRenderWeapon(true);
		game->loadConfig(path + "\\scenarios\\task1.cfg");
		game->init();
	}
	catch (std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}

	std::vector<double> actions[3];
	actions[0] = { 1,0,0 };
	actions[1] = { 0,1,0 };
	actions[2] = { 0,0,1 };

	int start, end, center;
	start = -100;

	auto greyscale = cv::Mat(480, 640, CV_8UC1);
	for (auto i = 0; i < episodes; i++)
	{
		game->newEpisode();
		std::cout << "Episode #" << i + 1 << " ";

		while (!game->isEpisodeFinished())
		{
			const auto& gamestate = game->getState();
			std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());


			cv::extractChannel(screenBuff, greyscale, 2);
			cv::threshold(greyscale, greyscale, 150, 255, cv::THRESH_BINARY);
			//cv::GaussianBlur(greyscale, greyscale, cv::Size(21, 21), 0, 0);
			cv::imshow("Output Window", greyscale);


			//std::cout 


			for (int x = 0; x < 640; x++) {
				if (greyscale.at<unsigned char>(225, x) > 130) {
					if (start < 0) start = x;
					end = x;
				}
			}
			center = start + (end - start) / 2;
			if (center < 269) double reward = game->makeAction({ 1,0,0 });
			else if (center > 290) double reward = game->makeAction({ 0,1,0 });
			else if (center >= 269 && center <= 290) double reward = game->makeAction({ 0,0,1 });

			cv::waitKey(sleepTime);

			
		}
		std::cout <<  " reward " << game->getTotalReward() << std::endl;
		result += game->getTotalReward();

	}
	std::cout << "result " << result/10 << std::endl;
}


void RunTask2(int episodes) {
	float result = 0.0;

	try
	{
		game->setWindowVisible(true);
		game->setRenderWeapon(true);
		game->loadConfig(path + "\\scenarios\\task2.cfg");
		game->init();
	}
	catch (std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}


	int start, end, center;
	bool tmp = false;
	start = -100;

	auto greyscale = cv::Mat(480, 640, CV_8UC1);
	for (auto i = 0; i < episodes; i++)
	{
		game->newEpisode();
		std::cout << "Episode #" << i + 1<< " ";

		while (!game->isEpisodeFinished())
		{
			const auto& gamestate = game->getState();
			std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());


			cv::extractChannel(screenBuff, greyscale, 2);
			cv::threshold(greyscale, greyscale, 150, 255, cv::THRESH_BINARY);
			//cv::GaussianBlur(greyscale, greyscale, cv::Size(21, 21), 0, 0);
			cv::imshow("Output Window", greyscale);




			for (int x = 0; x < 640; x++) {
				if (greyscale.at<unsigned char>(225, x) > 130) {
					if (start < 0) start = x;
					end = x;
				}
			}
			center = start + (end - start) / 2;
			
			float tmp;
			tmp = asin((289.0 - center) / 190.14401)*(180/3.14159265358979323846);
			double tmp2 = (double)tmp;

			if (center < 269) double reward = game->makeAction({ 0,0,360 - tmp2,0 });
			else if (center > 290) double reward = game->makeAction({ 0,0,tmp2*-1,0 });
			else if (center >= 269 && center <= 290) double reward = game->makeAction({ 0,0,0,1 });

			cv::waitKey(sleepTime);
		}

		std::cout << " reward " << game->getTotalReward() << std::endl;
		result += game->getTotalReward();
	}
	std::cout << "result " << result / 10 << std::endl;
}

void RunTask3(int episodes)
{

	float result = 0.0;
	int counter = 0, r, c;

	for (auto i = 0; i < episodes; i++)
	{
		game->newEpisode();
		std::cout « "Episode #" « i + 1 « std::endl;

		while (!game->isEpisodeFinished())
		{

			const auto& gamestate = game->getState();
			std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());

			cv::extractChannel(screenBuff, red, 0);
			cv::threshold(red, red, 130, 255, cv::THRESH_BINARY);
			cv::imshow("Output Window", red); 
			while (counter == 0)
			{
				for (int i = 398; i > 0; i--)
				{
					for (int j = 0; j < 640; j++)
					{
						if (counter >= 10)
						{
							r = i;
							c = j;
							break;
						}
						else
						{
							if (red.at<uchar>(i, j) == (uchar)0xff) counter++;
							if (red.at<uchar>(i, j) == (uchar)0) counter = 0;
						}

					}

				} 
				if (counter == 0) double reward = game->makeAction({ 0,0,90,0 });

			}

			double reward_ = game->makeAction({ 0,0,std::atan(abs(320-c)/r* (180 / 3.14159265358979323846)),0 });

			double reward = 0;

			while (reward == 0)
			{

				reward = game->makeAction({ 0,0,0,1 });
				//std::cout « reward « std::endl;

			}

			//uchar px = screenBuff.at<uchar>(r, c);

		}

		std::cout « " reward " « game->getTotalReward() « std::endl;
		result += game->getTotalReward();

	} 
	std::cout « "result " « result / episodes « std::endl;

}

int main()
{
	game->setViZDoomPath(path + "\\vizdoom.exe");
	game->setDoomGamePath(path + "\\DOOM2.wad");
	game->setWindowVisible(true);
	game->setRenderWeapon(true);

	auto episodes = 10;
	//RunTask1(episodes);
	RunTask2(episodes);
	

	game->close();
	delete game;
}

