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

// функция подсчёта растояния между двумя точками
int distance(const cv::Point2f& a, const cv::Point2f& b) {
	return round(sqrt(pow(abs(a.x - b.x), 2) + pow(abs(a.y - b.y), 2)));
}

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

void RunTask3(int episodes) {
	float result = 0.0;

	try
	{
		game->setWindowVisible(true);
		game->setRenderWeapon(true);
		game->loadConfig(path + "\\scenarios\\task3.cfg");
		game->init();
	}
	catch (std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}

	auto greyscale = cv::Mat(480, 640, CV_8UC1);
	for (auto i = 0; i < episodes; i++)
	{
		int id = 0;
		game->newEpisode();
		std::cout << "Episode #" << i + 1 << " ";
		while (!game->isEpisodeFinished())
		{
			std::cout << id << std::endl;
			std::vector < cv::Point2f > centers;
			cv::Mat clasters;
			const auto& gamestate = game->getState();
			std::vector <cv::Point2f> needs_point;
			int index;

			std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());
			cv::extractChannel(screenBuff, greyscale, 0);
			cv::threshold(greyscale, greyscale, 140, 255, cv::THRESH_BINARY);
			greyscale = greyscale(cv::Rect(0, 0, 640, 400));
			cv::imshow("Output Window", greyscale);
			cv::waitKey(sleepTime);

			//делаем вектор из белых точек
			for (int x = 0; x < (&greyscale)->cols; ++x) {
				for (int y = 0; y < (&greyscale)->rows; ++y)
					if (greyscale.at<unsigned char>(y, x) == 255) needs_point.push_back(cv::Point2f(x, y));
			}

			//кластерезируем
			if (needs_point.size() >= 5) {
				cv::kmeans(needs_point, 5, clasters, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 1000, 1.0), 5, cv::KMEANS_RANDOM_CENTERS, centers);



				//находим ближайшую аптечку в этом сигменте
				int minim = 999999;
				for (int j = 0; j < centers.size(); ++j) {
					int dis = distance(cvPoint(320, 1000), centers[j]);
					if (dis < minim) {
						minim = dis;
						index = j;
					}
				}
				//движемся к аптеке

				int x = centers[index].x;
				if (x < 300) {
					double reward = game->makeAction({ 1,0,0,0 });
				}
				else if (x > 340) {
					double reward = game->makeAction({ 0,1,0,0 });
				}
				else
				{
					double reward = game->makeAction({ 0,0,0,1 });
				}
			}
			else {
				double reward = game->makeAction({ 0,0,60,0 });
			}


			greyscale.convertTo(greyscale, CV_32F);
			greyscale.convertTo(greyscale, CV_8UC3);
			cv::waitKey(20);

		}

		std::cout << " reward " << game->getTotalReward() << std::endl;
		result += game->getTotalReward();
		std::cout << "resalt " << result / 10 << std::endl;

	}
}

void RunTask5(int episodes) {
	float result = 0.0;

	try
	{
		game->setWindowVisible(true);
		game->setRenderWeapon(true);
		game->loadConfig(path + "\\scenarios\\task5.cfg");
		game->init();
	}
	catch (std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}

	auto greyscale = cv::Mat(480, 640, CV_8UC1);
	auto greyscale2 = cv::Mat(480, 640, CV_8UC1);
	for (auto i = 0; i < episodes; i++)
	{
		int id = 0;
		float Left;
		float Right;
		int LeftCount;
		int RightCount;

		int RightWall;
		int LeftWall;
		game->newEpisode();
		std::cout << "Episode #" << i + 1 << " ";
		while (!game->isEpisodeFinished())
		{
			std::vector < cv::Point2f > centers;
			cv::Mat clasters;
			const auto& gamestate = game->getState();
			std::vector <cv::Point2f> needs_point;
			int index;

			std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());
			cv::GaussianBlur(greyscale, greyscale, cv::Size(21, 21), 0, 0);
			cv::extractChannel(screenBuff, greyscale, 2);
			cv::threshold(greyscale, greyscale, 230, 255, cv::THRESH_BINARY);
			greyscale = greyscale(cv::Rect(0, 0, 640, 400));
			
			std::vector < cv::Point2f > centers2;
			cv::Mat clasters2;
			std::vector <cv::Point2f> needs_point2;
			
			std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());
			cv::GaussianBlur(greyscale2, greyscale2, cv::Size(21, 21), 0, 0);
			cv::extractChannel(screenBuff, greyscale2, 2);
			cv::threshold(greyscale2, greyscale2, 130, 255, cv::THRESH_BINARY);
			greyscale2 = greyscale2(cv::Rect(0, 0, 640, 400));

			//делаем вектор из белых точек
			for (int x = 0; x < (&greyscale)->cols; ++x) {
				for (int y = 0; y < (&greyscale)->rows; ++y) {
					if (greyscale.at<unsigned char>(y, x) == 255) needs_point.push_back(cv::Point2f(x, y));
					if (greyscale2.at<unsigned char>(y, x) == 255) needs_point2.push_back(cv::Point2f(x, y));
				}
			}

			if (needs_point.size() >= 5)
				cv::kmeans(needs_point, 5, clasters, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 1000, 1.0), 10, cv::KMEANS_RANDOM_CENTERS, centers);
			cv::kmeans(needs_point2, 2, clasters2, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 1000, 1.0), 10, cv::KMEANS_RANDOM_CENTERS, centers2);

			index = 0;
			int minim = 999999;
			for (int j = 0; j < centers.size(); ++j) {
				int dis = distance(cvPoint(centers[j].x, 480), centers[j]);
				if (dis < minim) {
					minim = dis;
					index = j;
				}
			}
			if (needs_point.size() >= 5) {
				cv::Rect rect(centers[index].x, centers[index].y, 20, 20);
				cv::rectangle(greyscale, rect, cv::Scalar(0, 255, 0));
			}
			Left = 0.0;
			Right = 0.0;
			LeftCount = 0;
			RightCount = 0;
			for (int j = 0; j < centers.size(); j++) {
				if (j!=index) {
					if (centers[j].x < centers[index].x) {
						Left += distance(cvPoint(centers[j].x, 480), centers[j]);
					}
					else
					{
						Right += distance(cvPoint(centers[j].x, 480), centers[j]);
					}
				}
			}
			if (LeftCount != 0)Left /= LeftCount;
			else Left = 0;
			if (RightCount != 0)Right /= RightCount;
			else Right = 0;


			//не у стены ли мы????
			LeftWall = 320;
			RightWall = 320;
			for (int j = 0; j < centers2.size(); j++) {
				if (centers2[j].x > LeftWall) LeftWall = centers2[j].x;
				if (centers2[j].x > RightWall) RightWall = centers2[j].x;
			}
			if (minim <= 290 ) {
				if (centers[index].x<=200) {
					double reward = game->makeAction({ 0,1 }); //двигаемся вправо

				}
				else if (centers[index].x >= 440)
				{
					double reward = game->makeAction({ 1,0 }); //двигаемся влево
				}
				else {
					if (Left > Right) {
						double reward = game->makeAction({ 0,1 });
					}
					else if (Left < Right)
					{
						double reward = game->makeAction({ 1,0 });
					}
					else
					{
						if (centers[index].x < 330) {
							double reward = game->makeAction({ 0,1 }); //двигаемся вправо

						}
						else if (centers[index].x >= 330)
						{
							double reward = game->makeAction({ 1,0 }); //двигаемся влево
						}
					}
				}
			}
			else
			{
				if (LeftWall > 530) double reward = game->makeAction({ 1,0 });
				if (RightWall < 110) double reward = game->makeAction({ 0,1});
				double reward = game->makeAction({ 0,0 });
			}
			double reward = game->makeAction({ 0,0 });
			cv::imshow("Output Window", greyscale);
			greyscale.convertTo(greyscale, CV_32F);
			greyscale.convertTo(greyscale, CV_8UC3);

			cv::imshow("Output Window2", greyscale2);
			greyscale.convertTo(greyscale2, CV_32F);
			greyscale.convertTo(greyscale2, CV_8UC3);
			cv::waitKey(sleepTime);

		}

		std::cout << " reward " << game->getTotalReward() << std::endl;
		result += game->getTotalReward();
		std::cout << "resalt " << result / 10 << std::endl;

	}
}
void RunTask6(int episodes) {
	float result = 0.0;

	try
	{
		game->setWindowVisible(true);
		game->setRenderWeapon(true);
		game->loadConfig(path + "\\scenarios\\task6.cfg");
		game->init();
	}
	catch (std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}

	auto greyscale = cv::Mat(480, 640, CV_8UC1);
	auto greyscale2 = cv::Mat(480, 640, CV_8UC1);
	for (auto i = 0; i < episodes; i++)
	{
		int id = 0;
		float Left;
		float Right;
		int LeftCount;
		int RightCount;

		int RightWall;
		int LeftWall;
		game->newEpisode();
		std::cout << "Episode #" << i + 1 << " ";
		while (!game->isEpisodeFinished())
		{
			std::vector < cv::Point2f > centers;
			cv::Mat clasters;
			const auto& gamestate = game->getState();
			std::vector <cv::Point2f> needs_point;
			int index;

			std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());
			cv::GaussianBlur(greyscale, greyscale, cv::Size(21, 21), 0, 0);
			cv::extractChannel(screenBuff, greyscale, 2);
			cv::threshold(greyscale, greyscale, 230, 255, cv::THRESH_BINARY);
			greyscale = greyscale(cv::Rect(0, 0, 640, 400));
			
			std::vector < cv::Point2f > centers2;
			cv::Mat clasters2;
			std::vector <cv::Point2f> needs_point2;
			
			std::memcpy(screenBuff.data, gamestate->screenBuffer->data(), gamestate->screenBuffer->size());
			cv::GaussianBlur(greyscale2, greyscale2, cv::Size(21, 21), 0, 0);
			cv::extractChannel(screenBuff, greyscale2, 2);
			cv::threshold(greyscale2, greyscale2, 130, 255, cv::THRESH_BINARY);
			greyscale2 = greyscale2(cv::Rect(0, 0, 640, 400));

			//делаем вектор из белых точек
			for (int x = 0; x < (&greyscale)->cols; ++x) {
				for (int y = 0; y < (&greyscale)->rows; ++y) {
					if (greyscale.at<unsigned char>(y, x) == 255) needs_point.push_back(cv::Point2f(x, y));
					if (greyscale2.at<unsigned char>(y, x) == 255) needs_point2.push_back(cv::Point2f(x, y));
				}
			}

			if (needs_point.size() >= 5)
				cv::kmeans(needs_point, 5, clasters, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 1000, 1.0), 10, cv::KMEANS_RANDOM_CENTERS, centers);
			cv::kmeans(needs_point2, 2, clasters2, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 1000, 1.0), 10, cv::KMEANS_RANDOM_CENTERS, centers2);

			index = 0;
			int minim = 999999;
			for (int j = 0; j < centers.size(); ++j) {
				int dis = distance(cvPoint(centers[j].x, 480), centers[j]);
				if (dis < minim) {
					minim = dis;
					index = j;
				}
			}
			if (needs_point.size() >= 5) {
				cv::Rect rect(centers[index].x, centers[index].y, 20, 20);
				cv::rectangle(greyscale, rect, cv::Scalar(255, 255, 255));
				cv::Rect rect2(200, 0, 5, 480);
				cv::rectangle(greyscale, rect2, cv::Scalar(255, 255, 255));
				cv::Rect rect3(440, 0, 5, 480);
				cv::rectangle(greyscale, rect3, cv::Scalar(255, 255, 255));
				cv::Rect rect4(330, 0, 5, 480);
				cv::rectangle(greyscale, rect4, cv::Scalar(255, 255, 255));
			}
			Left = 0.0;
			Right = 0.0;
			LeftCount = 0;
			RightCount = 0;
			for (int j = 0; j < centers.size(); j++) {
				if (j!=index) {
					if (centers[j].x < centers[index].x) {
						Left += distance(cvPoint(centers[j].x, 480), centers[j]);
						LeftCount++;
					}
					else
					{
						RightCount++;
						Right += distance(cvPoint(centers[j].x, 480), centers[j]);
					}
				}
			}
			std::cout << Left << " " << Right << "\n";

			if (LeftCount != 0)Left /= LeftCount;
			else Left = 0;
			if (RightCount != 0)Right /= RightCount;
			else Right = 0;


			std::cout << Left << " " << Right << "\n";
			//не у стены ли мы????
			LeftWall = 320;
			RightWall = 320;
			for (int j = 0; j < centers2.size(); j++) {
				if (centers2[j].x > LeftWall) LeftWall = centers2[j].x;
				if (centers2[j].x < RightWall) RightWall = centers2[j].x;
			}
			if (minim <= 290 ) {
				if (centers[index].x<=200) {
					double reward = game->makeAction({ 0,1 }); //двигаемся вправо
					if (LeftWall > 530) double reward = game->makeAction({ 1,0 });
				}
				else if (centers[index].x >= 440)
				{
					double reward = game->makeAction({ 1,0 }); //двигаемся влево
					if (RightWall < 110) double reward = game->makeAction({ 0,1 });
				}
				else {
					if (Left > Right) {
						double reward = game->makeAction({ 0,1 });
						if (LeftWall > 530) double reward = game->makeAction({ 1,0 });
					}
					else if (Left < Right)
					{
						double reward = game->makeAction({ 1,0 });
						if (RightWall < 110) double reward = game->makeAction({ 0,1 });
					}
					else
					{
						if (centers[index].x < 330) {
							double reward = game->makeAction({ 0,1 }); //двигаемся вправо
							if (LeftWall > 530) double reward = game->makeAction({ 1,0 });
						}
						else if (centers[index].x >= 330)
						{
							double reward = game->makeAction({ 1,0 }); //двигаемся влево
							if (RightWall < 110) double reward = game->makeAction({ 0,1 });
						}
					}
				}
			}
			else
			{
				if (LeftWall > 530) double reward = game->makeAction({ 1,0 });
				if (RightWall < 110) double reward = game->makeAction({ 0,1});
				double reward = game->makeAction({ 0,0 });
			}
			
			double reward = game->makeAction({ 0,0 });
			cv::imshow("Output Window", greyscale);
			greyscale.convertTo(greyscale, CV_32F);
			greyscale.convertTo(greyscale, CV_8UC3);

			cv::imshow("Output Window2", greyscale2);
			greyscale2.convertTo(greyscale2, CV_32F);
			greyscale2.convertTo(greyscale2, CV_8UC3);
			cv::waitKey(sleepTime);

		}

		std::cout << " reward " << game->getTotalReward() << std::endl;
		result += game->getTotalReward();
		std::cout << "resalt " << result / 10 << std::endl;

	}
}

void RunTask7(int episodes) {

	float result = 0.0;

	try
	{
		game->setWindowVisible(true);
		game->setRenderWeapon(false);
		game->loadConfig(path + "\\scenarios\\task7.cfg");
		game->init();
	}
	catch (std::exception& err)
	{
		std::cout << err.what() << std::endl;
	}


	auto greyscale = cv::Mat(480, 640, CV_8UC1);
	int flag=0;
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
			greyscale = greyscale(cv::Rect(0, 0, 640, 280));

			std::vector <cv::Point2f> needs_point;
			std::vector < cv::Point2f > centers;
			cv::Mat clasters;
			


			
			for (int x = 0; x < (&greyscale)->cols; ++x) {
				for (int y = 0; y < (&greyscale)->rows; ++y) {
					if (greyscale.at<unsigned char>(y, x) == 255) needs_point.push_back(cv::Point2f(x, y));
				}
			}

			

			if (needs_point.size() >= 5) {
				cv::kmeans(needs_point, 5, clasters, cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::COUNT, 1000, 1.0), 10, cv::KMEANS_RANDOM_CENTERS, centers);
			}
			
			int index = 0;
			int minim = 999999;
			for (int j = 0; j < centers.size(); ++j) {
				int dis = distance(cvPoint(320, 480), centers[j]);
				if (dis < minim) {
					index = j;
					minim = dis;
				}
			}
			if ((minim < 260 && minim > 200 && centers[index].x >280 && centers[index].x < 320) || (minim < 210 && centers[index].x > 240 && centers[index].x < 400))  {
				if (flag >= 5) {
					double reward = game->makeAction({ 0,0,0,1 });
					flag = 0;
				}
				else
				{
					flag++;
					double reward = game->makeAction({ 0,0,0,0 });
				}
			}
			else
			{
				flag++;
				double reward = game->makeAction({ 0,1,0,0 });
			}
			//double reward = game->makeAction({ 1,0,0,0 });

			std::cout << minim << std::endl;
			cv::Rect rect(280, 0, 3, 480);
			cv::rectangle(greyscale, rect, cv::Scalar(255, 255, 255));
			cv::Rect rect2(320, 0, 3, 480);
			cv::rectangle(greyscale, rect2, cv::Scalar(255, 255, 255));
			if (needs_point.size() >= 5) {
				cv::Rect rect3(centers[index].x, centers[index].y, 20, 20);
				cv::rectangle(greyscale, rect3, cv::Scalar(255, 255, 255));
			}

			//std::cout << minim << "\n";
			greyscale.convertTo(greyscale, CV_32F);
			greyscale.convertTo(greyscale, CV_8UC3);
			cv::imshow("pinki", greyscale);
			cv::waitKey(10);

		}
		std::cout << " reward " << game->getTotalReward() << std::endl;
		result += game->getTotalReward();

	}
	std::cout << "resalt " << result / 10 << std::endl;
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

