#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <list>
#include <map>

#define SIZE 19

using namespace std;


vector<vector<int>> generate_map(int size);
void print_map(vector<vector<int>>& map);
void findPath(int recentX, int recentY, vector<vector<int>>& map);

int main()
{
	vector<vector<int>> map = generate_map(SIZE + 1);
	findPath(0, 0, map);

	return 0;
}

vector<vector<int>> generate_map(int size)
{
	vector<vector<int>> map(size, vector<int>(size, 0));
	int drawRight = 0;
	int drawDown = 0;
	srand(time(0));

	for (int i = 1; i < map.size(); i++)
	{
		for (int j = 0; j < map.size() - 1; j++)
		{
			if (drawRight == 0)
			{
				map[i][j] = 5;
				drawRight--;
			}
			else if (rand() % (map.size() * 3) == 1)
			{
				map[i][j] = 5;
				drawRight = rand() % (map.size() / 2);
			}

			if (drawDown == 0)
			{
				map[j][i] = 5;
				drawDown--;
			}
			else if (rand() % (map.size() * 3) == 1)
			{
				map[j][i] = 5;
				drawDown = rand() % (map.size() / 2);
			}
		}
	}

	return map;
}

void print_map(vector<vector<int>>& map)
{
	for (int i = SIZE; i >= 0; i--)
	{
		for (int j = 0; j < SIZE; j++)
			cout << map[j][i] << " ";
		cout << endl;
	}
}

void findPath(int recentX, int recentY, vector<vector<int>>& map)
{
	struct FieldProperties
	{
		list<int> parentCoos;
		double value;
	};

	// klucz to wpolrzedne pola, reszta to info o nim
	std::map<list<int>, FieldProperties> visitedFields, expansionFields;


	map[recentX][recentY] = 1;
	print_map(map);

	

	while (recentX != SIZE && recentY != SIZE)
	{
		cout << visitedFields[{5,5}].value;
		// dodaj do listy otwartej nowe wspolrzedne
		//									 IF TO POLE JESZCZE NIE MA VALUE TOOOOOOOOOOOOOOOOOOOO ......
		if (recentX >= 1 && recentX <= SIZE - 1 && recentY >= 1 && recentY <= SIZE -1)
		{	
			if (map[recentX][recentY - 1] != 5 && visitedFields[{recentX, recentY - 1}].value == 0) expansionFields[{recentX, recentY - 1}].parentCoos = { recentX, recentY }; // DOL
			if (map[recentX + 1][recentY] != 5 && visitedFields[{recentX + 1, recentY}].value == 0) expansionFields[{recentX + 1, recentY}].parentCoos = { recentX, recentY }; // PRAWO
			if (map[recentX][recentY + 1] != 5 && visitedFields[{recentX, recentY + 1}].value == 0) expansionFields[{recentX, recentY + 1}].parentCoos = { recentX, recentY }; // GORA
			if (map[recentX - 1][recentY] != 5 && visitedFields[{recentX - 1, recentY}].value == 0) expansionFields[{recentX - 1, recentY}].parentCoos = { recentX, recentY }; // LEWO
		}
		else if (recentY == 0)
		{
			if (map[recentX][recentY + 1] != 5 && visitedFields[{recentX, recentY + 1}].value == 0) expansionFields[{recentX, recentY + 1}].parentCoos = { recentX, recentY };
			// DOLNY LEWY ROG
			if (recentX == 0 && map[recentX][recentY] != 5 && visitedFields[{recentX, recentY}].value == 0)
				expansionFields[{recentX + 1, recentY}].parentCoos = { recentX, recentY };
			// DOLNY PRAWY ROG
			else if (recentX == SIZE && map[recentX - 1][recentY] != 5 && visitedFields[{recentX - 1, recentY}].value == 0)
				expansionFields[{recentX - 1, recentY}].parentCoos = { recentX, recentY };
			// DOLNA LINIA NIE SKAJNA NA WSP X
			else
			{
				if (map[recentX + 1][recentY] != 5 && visitedFields[{recentX + 1, recentY}].value == 0) expansionFields[{recentX + 1, recentY}].parentCoos = { recentX, recentY };
				if (map[recentX - 1][recentY] != 5 && visitedFields[{recentX - 1, recentY}].value == 0) expansionFields[{recentX - 1, recentY}].parentCoos = { recentX, recentY };
			}
		}
		else if(recentY == SIZE)
		{
			if(map[recentX][recentY - 1] != 5 && visitedFields[{recentX, recentY - 1}].value == 0) expansionFields[{recentX, recentY - 1}].parentCoos = { recentX, recentY };
			// GORNY LEWY ROG
			if(recentX == 0 && map[recentX + 1][recentY] != 5 && visitedFields[{recentX + 1, recentY}].value == 0)
				expansionFields[{recentX + 1, recentY}].parentCoos = { recentX, recentY };
			// GORNY PRAWY ROG
			else if(recentX == SIZE && map[recentX - 1][recentY] != 5 && visitedFields[{recentX - 1, recentY}].value == 0)
				expansionFields[{recentX - 1, recentY}].parentCoos = { recentX, recentY };
			else
			{ 
				if(map[recentX + 1][recentY] != 5 && visitedFields[{recentX + 1, recentY}].value == 0) expansionFields[{recentX + 1, recentY}].parentCoos = { recentX, recentY };
				if(map[recentX - 1][recentY] != 5 && visitedFields[{recentX - 1, recentY}].value == 0) expansionFields[{recentX - 1, recentY}].parentCoos = { recentX, recentY };
			}
		}

		// oblicz wartosci wpolrzednych dodanych do otwartej listy
		for (auto it = expansionFields.begin(); it != expansionFields.end(); it++)
		{ 
			it->second.value = sqrt(pow(it->first.front() - SIZE, 2) + pow(it->first.back() - SIZE, 2));
		}
		// szukamy przyleglej kratki o najmniejszej wartosci
		int lowestValue;
		lowestValue = 10000; // bardzo duza liczba
		list<int> lowValCoos;

		for (auto it = expansionFields.begin(); it != expansionFields.end(); it++)
			if (it->second.value < lowestValue)
			{
				lowestValue = it->second.value;
				lowValCoos.clear();
				lowValCoos.push_back(it->first.front());
				lowValCoos.push_back(it->first.back());
			}
		
		// pole z najmniejsza wartoscia dodajemy do mapy visitedFIelds, a
		int parentX = recentX;
		int parentY = recentY;
											cout << "------------------------------------------------------\n";
		auto it = lowValCoos.begin();
		recentX = *it;
		advance(it, 1);
		recentY = *it;
											
		visitedFields[{recentX, recentY}].value = lowestValue;
		visitedFields[{recentX, recentY}].parentCoos = { parentX, parentY };
		expansionFields.erase({ recentX, recentY });

		map[recentX][recentY] = 1;

		//cout << "\n";
		//cout << recentX << "\n" << recentY << "\n";
		//for (auto it = expansionFields.begin(); it != expansionFields.end(); it++)
		//	cout << it->second.value << "  ";
		//cout << endl;

		print_map(map);
	}
}

// SPAWDZANIE CZY KRATKA MA JUZ WARTOSC
// OBSLUGA BLEDOW