#pragma once
#include <string>
#include <fstream>
#include <ctime>  //for timestamps

class GameLogger
{
public:
	~GameLogger();
	static void Log(std::string message);
private:
	GameLogger();
	static GameLogger * instance;
	std::ofstream fileHandle;
	std::string logFile = "Logs/game.log";
	std::string EOL = "\r\n"; //append at the end of log messages
	std::string TimeStamp();
	void WriteLog(std::string message);
};
