/*
 * CommandLineParser.cpp
 *
 *  Created on: Mar 16, 2017
 *      Author: root
 */

#include "CommandLineParser.hpp"
#include "ColorDetection.hpp"
#include "DetectShape.hpp"
#include "MainApplication.hpp"

#include "VideoCapture.hpp"

CommandLineParser::CommandLineParser():exit(false)
{
	// TODO Auto-generated constructor stub
}

CommandLineParser::~CommandLineParser() {
	// TODO Auto-generated destructor stub
}

std::vector<std::string> CommandLineParser::readFile(char* aFileName)
{
	std::ifstream file(aFileName);
	std::string line;
	std::vector<std::string> content;

	if (file.is_open())
	{
		while (getline(file, line))
		{
			if(line.find("#")==std::string::npos) content.push_back(line);
		}
		file.close();
	}
	else
	{
		throw std::invalid_argument
		{ "given file could not be opened or does not exist" };
	}
	return content;
}

void CommandLineParser::parseContent(std::vector<std::string> aFile)
{
	std::regex e("([[:w:]]+)[[:space:]]+([[:w:]]+)");
		std::smatch matchResults;

		std::for_each(aFile.begin(),aFile.end(),[&e,&matchResults](std::string& s)
				{
					if(std::regex_search(s, matchResults, e))
					{
						auto shape = stringToshape.find(matchResults.str(1));

						if(shape!=stringToshape.end())
						{
							auto colour = stringTocolor.find(matchResults.str(2));

							if(colour!=stringTocolor.end())
							{
								MainApplication m(shape->second,colour->second);
								if(m.run(VideoCapture::getInstance().getFrame()))
								{
									std::cout<<"Shape found in: ";
								}
								else {
									std::cout<<"Shape not found in: ";
								}
								//cv::imshow("h",VideoCapture::getInstance().getFrame());
							}
							//else throw std::runtime_error{"invalid colour request"};
							else std::cout<<"invalid colour request"<<std::endl;
						}
						//else throw std::runtime_error{"invalid shape request"};
						else std::cout<<"invalid shape request"<<std::endl;
					}

				});
}

void CommandLineParser::parseFile(char* aFileName)
{
	parseContent(readFile(aFileName));
}

bool CommandLineParser::isExit() const
{
	return exit;
}

void CommandLineParser::parseCommandLine(std::string& input)
{
	if(input == "exit")
	{
		exit = true;
		VideoCapture::getInstance().close();
		return;
	}
	std::vector<std::string> aInput = {input};
	parseContent(aInput);

}
