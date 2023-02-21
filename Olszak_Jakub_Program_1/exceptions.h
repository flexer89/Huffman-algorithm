#pragma once
#include <fstream>
#include <exception>
#include <string>

namespace EXCEPTIONS
{
	class InvalidArguments : public std::runtime_error
	{
	public:
		InvalidArguments() : runtime_error("Niepoprawne dane wejsciowe!"){}
		InvalidArguments(std::string msg) : runtime_error(msg.c_str()){}
	};
	class FileOpenException : public std::runtime_error {
	public:
		FileOpenException() : runtime_error("Nie mozna otworzyc pliku!") {
		}
		FileOpenException(std::string msg) : runtime_error(msg.c_str()) {
		}
	};

}