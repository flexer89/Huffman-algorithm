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
		//Wczytanie iloœci liter (warunek w pêtli)
		int letterAmount;
		inputFile >> letterAmount;
		for (int i = 0; i < letterAmount; i++)
		{
			//Stworzenie nowego wêz³a i przypisanie do odpowiednich wskaŸników przechowywanej litery i czêstotliwoœci
			Node* newNode = new Node();
			inputFile >> newNode->letter;
			inputFile >> newNode->frequency;

			//Jeœli wierzcho³ek pocz¹tkowy nie istnieje, przypisz mu wartoœci
			if (topNode == nullptr)
			{
				topNode = newNode;
			}
			else
			{
				//Jeœli czêstotliwoœæ nowego wêz³a jest mniejsza b¹dŸ równa najmniejszej obecnie czêstotliwoœci
				//Ustaw nowy wêze³ na pocz¹tku listy
				if (newNode->frequency <= topNode->frequency)
				{
					newNode->next = topNode;
					topNode = newNode;
				}
				else
				{
					//Szukamy miejsca do wstawienia
					//Tworzymy wêze³ pomocniczy, dziêki którym przechodzimy przez listê do momentu
					//A¿ znajdziemy miejsce do wstawienia wêz³a (odpowiednia wartoœæ czêstotliwoœci)
					Node* temp = topNode;
					while (temp->next != nullptr && temp->next->frequency < newNode->frequency)
					{
						temp = temp->next;
					}
					//Wstawiamy wêze³ w œrodek istniej¹cej listy pomiêdzy (temp), a (temp->next)
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
	//Stworzenie pomocniczych wêz³ów do sumowania
	Node* v1;
	Node* v2;

	while (true)
	{
		//Zapisanie wêz³ów pomocniczych jako dwóch wêz³ów o najmniejszej czêstotliwoœci
		v1 = topNode;
		v2 = topNode->next;

		//Gdy dojdziemy do momentu, ¿e pozosta³ tylko jeden wêze³ (korzeñ) zakoñcz pêtlê
		if (v2 == nullptr)
		{
			break;
		}

		//Od teraz pierwszym elementem jest trzeci kolejny element
		topNode = v2->next;

		//Tworzymy nowy wêze³, bêd¹cego sum¹ dwóch najmniejszych wez³ów
		Node* newNode = new Node();

		//Od teraz nowy wêze³ ma pod sob¹ dwa najmniejsze wêz³y
		newNode->left = v1;
		newNode->right = v2;

		//A jego czêstotliwoœc to suma czêstotliwoœci wêz³ów sk³adowych
		newNode->frequency = v1->frequency + v2->frequency;

		//Jeœli korzeñ jest pusty, lub nowy wêze³ ma najmniejsz¹ czêstotliwoœæ wstawiamy go na pocz¹tek
		if (topNode == nullptr || (newNode->frequency <= topNode->frequency))
		{
			newNode->next = topNode;
			topNode = newNode;
		}
		else
		{
			//Szukamy miejsca do wstawienia
			//Tworzymy wêze³ pomocniczy, dziêki którym przechodzimy przez listê do momentu
			//A¿ znajdziemy miejsce do wstawienia wêz³a (odpowiednia wartoœæ czêstotliwoœci)
			//Podobnie jak w funkcji wczytuj¹cej dane
			Node* temp = topNode;
			while (temp->next != nullptr && (newNode->frequency > temp->next->frequency))
			{
				temp = temp->next;
			}
			//Wstawiamy wêze³ w œrodek istniej¹cej listy pomiêdzy (temp), a (temp->next)
			newNode->next = temp->next;
			temp->next = newNode;
		}
	}
	return topNode;
}


void saveCode(Node* root, std::string code, std::ofstream& outputFile)
{
	//Jeœli wskaŸnik korzenia wskazuje na nullptr to znaczy, ¿e mamy do czynienia z pustym drzewem
	if (root->left == nullptr)
	{
		outputFile << root->letter << " = " << code << std::endl;
	}
	//Wywo³ujemy rekurencyjnie funkcjê która w zale¿noœci od pozycji do której siê przemieszczamy (krawêdzi drzewa)
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
