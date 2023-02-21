#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "exceptions.h"

struct Node
{
	std::string letter;
	double frequency = 0;
	Node* next = nullptr;
	Node* left = nullptr;
	Node* right = nullptr;
};

/// <summary>
/// Funkcja wyznaczaj�ca dane z pliku: litera, cz�stotliwo�c (stworzenie w�z��w, kt�re potem b�d� ��czone ze sob�) implementacja listy
/// </summary>
/// <param name="inputFileName"> - Nazwa pliku wej�ciowego</param>
/// <returns>Wska�nik na w�ze� pocz�tkowy</returns>
Node* readFile(std::string inputFileName);

/// <summary>
/// Funkcja buduj�ca drzewo (po��czenia pomi�dzy poszczeg�lnymi w�z�ami)
/// </summary>
/// <param name="topNode"> - W�ze� pocz�tkowy</param>
/// <returns>Wska�nik na w�ze� pocz�tkowy</returns>
Node* buildTree(Node* topNode);

/// <summary>
/// Funkcja przypisuj�ca odpowiedni kod (warto�ci 0 lub 1) do ka�dej kraw�dzi drzewa
/// </summary>
/// <param name="root"> - Korze� drzewa</param>
/// <param name="code"> - Warto�� kodowa</param>
/// <param name="outputFile"> - Referencja do pliku wyj�ciowego</param>
void saveCode(Node* root, std::string code, std::ofstream& outputFile);

/// <summary>
/// Funkcja zapisuj�ca warto�ci w�z��w do pliku
/// </summary>
/// <param name="root"> - Korze� drzewa</param>
/// <param name="outputFileName"> - Nazwa pliku wyj�ciowego</param>
void saveToFile(Node* root, std::string outputFileName);