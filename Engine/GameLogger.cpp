#include "GameLogger.h"

GameLogger * GameLogger::instance = 0;

GameLogger::GameLogger()
{
	fileHandle = std::ofstream(logFile, std::ios::out | std::ios::app);
}


GameLogger::~GameLogger()
{
	if (fileHandle)
	{
		fileHandle.close();
	}
}

void GameLogger::Log(std::string message)
{
	//initialize if we haven't already
	if (GameLogger::instance == 0)
	{
		GameLogger::instance = new GameLogger();
	}
	GameLogger::instance->WriteLog(message);
}

std::string GameLogger::TimeStamp()
{
	std::time_t now = std::time(0);
	std::tm * localTime = std::localtime(&now); //this gives us a warning, not sure if this is actually an issue or not
	//std::timeStamp = YYYY MM DD HH II SS
	std::string timeStamp;
	timeStamp.append(std::to_string(localTime->tm_year + 1900));
	timeStamp.append(":");
	timeStamp.append(std::to_string(localTime->tm_mon));
	timeStamp.append(":");
	timeStamp.append(std::to_string(localTime->tm_mday));
	timeStamp.append(" ");
	timeStamp.append(std::to_string(localTime->tm_hour));
	timeStamp.append(":");
	timeStamp.append(std::to_string(localTime->tm_min));
	timeStamp.append(":");
	timeStamp.append(std::to_string(localTime->tm_sec));
	timeStamp.append(" ");
	return timeStamp;
}

void GameLogger::WriteLog(std::string message)
{
	const std::string logMessage = TimeStamp() + message + EOL;
	fileHandle << logMessage;
}
