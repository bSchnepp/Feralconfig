#include <queue>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <filesystem>

void InterpFile(std::queue<std::filesystem::path> &Files, 
	std::filesystem::path Current)
{
	/* May not work on NT... */
	std::ifstream Stream(Current.c_str(), std::ios::in);

	std::string Contents;
	if (Stream.is_open())
	{
		std::ostringstream SStream;
		SStream << Stream.rdbuf();
		Contents = SStream.str();
	}

	Stream.close();

}

int main(int argc, char **argv)
{
	std::queue<std::filesystem::path> ToBuild;

	std::filesystem::directory_iterator Iterator(".");
	for (std::filesystem::path Path : Iterator)
	{
		std::filesystem::path NormPath = Path.lexically_normal();
		std::string U8Path = std::filesystem::absolute(NormPath).u8string();
		std::cout << U8Path << std::endl;
		if (U8Path.find("Buildcfg") != std::string::npos)
		{
			InterpFile(ToBuild, U8Path);
		}
	}

	return 0;
}
