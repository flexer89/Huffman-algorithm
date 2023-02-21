#include "huffman.h"

Node* readFile(std::string inputFileName)
{
	Node* topNode = NULL;
	std::ifstream inputFile;
	inputFile.open(inputFileName);
	if (!inputFile.good())
	{
		throw EXCEPTIONS::FileOpenException();
	}
	if (inputFile.is_open())
	{
		//Wczytanie ilo�ci liter (warunek w p�tli)
		int letterAmount;
		inputFile >> letterAmount;
		for (int i = 0; i < letterAmount; i++)
		{
			//Stworzenie nowego w�z�a i przypisanie do odpowiednich wska�nik�w przechowywanej litery i cz�stotliwo�ci
			Node* newNode = new Node();
			inputFile >> newNode->letter;
			inputFile >> newNode->frequency;

			//Je�li wierzcho�ek pocz�tkowy nie istnieje, przypisz mu warto�ci
			if (topNode == nullptr)
			{
				topNode = newNode;
			}
			else
			{
				//Je�li cz�stotliwo�� nowego w�z�a jest mniejsza b�d� r�wna najmniejszej obecnie cz�stotliwo�ci
				//Ustaw nowy w�ze� na pocz�tku listy
				if (newNode->frequency <= topNode->frequency)
				{
					newNode->next = topNode;
					topNode = newNode;
				}
				else
				{
					//Szukamy miejsca do wstawienia
					//Tworzymy w�ze� pomocniczy, dzi�ki kt�rym przechodzimy przez list� do momentu
					//A� znajdziemy miejsce do wstawienia w�z�a (odpowiednia warto�� cz�stotliwo�ci)
					Node* temp = topNode;
					while (temp->next != nullptr && temp->next->frequency < newNode->frequency)
					{
						temp = temp->next;
					}
					//Wstawiamy w�ze� w �rodek istniej�cej listy pomi�dzy (temp), a (temp->next)
					newNode->next = temp->next;
					temp->next = newNode;
				}
			}
		}
	}
	inputFile.close();

	return topNode;
}

Node* buildTree(Node* topNode)
{
	//Stworzenie pomocniczych w�z��w do sumowania
	Node* v1;
	Node* v2;

	while (true)
	{
		//Zapisanie w�z��w pomocniczych jako dw�ch w�z��w o najmniejszej cz�stotliwo�ci
		v1 = topNode;
		v2 = topNode->next;

		//Gdy dojdziemy do momentu, �e pozosta� tylko jeden w�ze� (korze�) zako�cz p�tl�
		if (v2 == nullptr)
		{
			break;
		}

		//Od teraz pierwszym elementem jest trzeci kolejny element
		topNode = v2->next;

		//Tworzymy nowy w�ze�, b�d�cego sum� dw�ch najmniejszych wez��w
		Node* newNode = new Node();

		//Od teraz nowy w�ze� ma pod sob� dwa najmniejsze w�z�y
		newNode->left = v1;
		newNode->right = v2;

		//A jego cz�stotliwo�c to suma cz�stotliwo�ci w�z��w sk�adowych
		newNode->frequency = v1->frequency + v2->frequency;

		//Je�li korze� jest pusty, lub nowy w�ze� ma najmniejsz� cz�stotliwo�� wstawiamy go na pocz�tek
		if (topNode == nullptr || (newNode->frequency <= topNode->frequency))
		{
			newNode->next = topNode;
			topNode = newNode;
		}
		else
		{
			//Szukamy miejsca do wstawienia
			//Tworzymy w�ze� pomocniczy, dzi�ki kt�rym przechodzimy przez list� do momentu
			//A� znajdziemy miejsce do wstawienia w�z�a (odpowiednia warto�� cz�stotliwo�ci)
			//Podobnie jak w funkcji wczytuj�cej dane
			Node* temp = topNode;
			while (temp->next != nullptr && (newNode->frequency > temp->next->frequency))
			{
				temp = temp->next;
			}
			//Wstawiamy w�ze� w �rodek istniej�cej listy pomi�dzy (temp), a (temp->next)
			newNode->next = temp->next;
			temp->next = newNode;
		}
	}
	return topNode;
}


void saveCode(Node* root, std::string code, std::ofstream& outputFile)
{
	//Je�li wska�nik korzenia wskazuje na nullptr to znaczy, �e mamy do czynienia z pustym drzewem
	if (root->left == nullptr)
	{
		outputFile << root->letter << " = " << code << std::endl;
	}
	//Wywo�ujemy rekurencyjnie funkcj� kt�ra w zale�no�ci od pozycji do kt�rej si� przemieszczamy (kraw�dzi drzewa)
	//Przypisuje jej odpowiedni kod (0 lub 1)
	if (root->left != nullptr)
	{
		saveCode(root->left, code + "0", outputFile);
	}
	if (root->right != nullptr)
	{
		saveCode(root->right, code + "1", outputFile);
	}
}

void saveToFile(Node* root, std::string outputFileName)
{
	std::ofstream outputFile;
	outputFile.open(outputFileName);
	if (!outputFile.good())
	{
		throw EXCEPTIONS::FileOpenException();
	}
	if (outputFile.is_open())
	{
		saveCode(root, "", outputFile);
	}
	outputFile.close();
}
