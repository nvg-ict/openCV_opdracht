/*
 * webcam.hpp
 *
 *  Created on: Feb 17, 2017
 *      Author: nico
 */

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include "CommandLineParser.hpp"
#include "VideoCapture.hpp"

#include <thread>

int main(int argc, char **argv)
{
	//freopen("/dev/null","W",stderr);
	try
	{

		CommandLineParser parser;
		if (argc > 1)
		{
			parser.parseFile(argv[1]);
		}
		else
		{

			std::thread t2([&parser]()
			{
				while(!parser.isExit())
				{
					std::string input;
					getline(std::cin, input);
					parser.parseCommandLine(input);
				}
			});
			//t2.detach();

			//std::thread t1([]()
			//{
			VideoCapture::getInstance().capture();

			t2.join();
			//t1.join();
		}
	} catch (std::exception& e)
	{
		std::cout << "Exception: " << e.what() << std::endl;
	}

	return 0;
}
