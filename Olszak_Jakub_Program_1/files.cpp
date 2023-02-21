#include "Files.h"
#include "exceptions.h"

std::string extensionCheck(std::string fileName, std::string extension) 
{
	if (extension.length() < 0)
	{
		throw EXCEPTIONS::InvalidArguments();
	}
	//sprawdzenie czy .txt pojawia sie w podanej nazwie pliku
	size_t pos;
	pos = fileName.find(extension);
	if (pos != std::string::npos)
	{
		return fileName;
	}
	else
	{
		fileName += extension;
	}
	return fileName;
}