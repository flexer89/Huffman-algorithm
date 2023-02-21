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
/// Funkcja wyznaczaj¹ca dane z pliku: litera, czêstotliwoœc (stworzenie wêz³ów, które potem bêd¹ ³¹czone ze sob¹) implementacja listy
/// </summary>
/// <param name="inputFileName"> - Nazwa pliku wejœciowego</param>
/// <returns>WskaŸnik na wêze³ pocz¹tkowy</returns>
Node* readFile(std::string inputFileName);

/// <summary>
/// Funkcja buduj¹ca drzewo (po³¹czenia pomiêdzy poszczególnymi wêz³ami)
/// </summary>
/// <param name="topNode"> - Wêze³ pocz¹tkowy</param>
/// <returns>WskaŸnik na wêze³ pocz¹tkowy</returns>
Node* buildTree(Node* topNode);

/// <summary>
/// Funkcja przypisuj¹ca odpowiedni kod (wartoœci 0 lub 1) do ka¿dej krawêdzi drzewa
/// </summary>
/// <param name="root"> - Korzeñ drzewa</param>
/// <param name="code"> - Wartoœæ kodowa</param>
/// <param name="outputFile"> - Referencja do pliku wyjœciowego</param>
void saveCode(Node* root, std::string code, std::ofstream& outputFile);

/// <summary>
/// Funkcja zapisuj¹ca wartoœci wêz³ów do pliku
/// </summary>
/// <param name="root"> - Korzeñ drzewa</param>
/// <param name="outputFileName"> - Nazwa pliku wyjœciowego</param>
void saveToFile(Node* root, std::string outputFileName);