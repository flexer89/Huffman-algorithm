#include <iostream>
#include <fstream>
#include "files.h"
#include "huffman.h"

int main()
{
	//Stworzenie zmiennych plikowych
	int returnCode = 0;
	std::string inputFileName;
	std::string outputFileName;

	//Wczytanie nazw plików
	std::cout << "Podaj nazwe pliku wejsciowego: ";
	std::cin >> inputFileName;
	std::cout << "Podaj nazwe pliku wyjsciowego: ";
	std::cin >> outputFileName;

	//Sprawdzenie rozszerzenia plików
	try
	{
		inputFileName = extensionCheck(inputFileName, ".txt");
		outputFileName = extensionCheck(outputFileName, ".txt");
	}
	catch (std::exception& error)
	{
		returnCode = 1;
		std::cerr << error.what();
	}
	
	Node* topNode = nullptr;
	//Zapisanie do wierzchołka topNode danych (stworzenie węzłów, które potem będą łączone ze sobą) implementacja listy
	try
	{
		topNode = readFile(inputFileName);
	}
	catch (std::exception& error)
	{
		returnCode = 1;
		std::cerr << error.what();
	}
	
	//Zapisanie do węzła pierwotnego (korzenia) odpowiedniej struktury drzewa
	Node* root = buildTree(topNode);

	//Zapisanie wartości do pliku
	try
	{
		saveToFile(root, outputFileName);
	}
	catch (std::exception& error)
	{
		returnCode = 1;
		std::cerr << error.what();
	}
	
	return returnCode;
}

