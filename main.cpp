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
void findPath(int recentX, int recentY, int metaX, int metaY, vector<vector<int>>& map);

int main()
{
	vector<vector<int>> map = generate_map(SIZE + 1);
	print_map(map);
	findPath(0, 0, 19, 19, map);
	
	return 0;
}

vector<vector<int>> generate_map(int size)
{
	vector<vector<int>> map(size, vector<int>(size, 0));
	bool drawRight = true;
	bool drawDown = true;
	srand(time(NULL));

	for (int i = 0; i < map.size() - 1; i++)
	{
		for (int j = 0; j < map.size() - 1; j++)
		{
			if (rand() % (map.size() / 2) == 1)
			{
				map[i][j] = 5;
				drawRight = rand() % (map.size())*3;
			}
			else if (drawRight == false)
			{
				map[i][j] = 5;
				drawRight = !drawRight;
			}

			if (rand() % (map.size() / 2) == 1)
			{
				map[j][i] = 5;
				drawDown = rand() % (map.size())*3;
			}
			else if (drawDown == false)
			{
				map[j][i] = 5;
				drawDown = !drawDown;
			}
		}
	}

	return map;
}

void print_map(vector<vector<int>>& map)
{
	cout << "\n\n";

	for (int i = SIZE; i >= 0; i--)
	{
		for (int j = 0; j < SIZE; j++)
			cout << map[j][i] << " ";
		cout << "\n";
	}
}

void findPath(int recentX, int recentY, int metaX, int metaY, vector<vector<int>>& map)
{
	struct FieldProperties
	{
		list<int> parentCoos;
		double value;
	};

	// klucz to wpolrzedne pola, reszta to info o nim
	std::map<list<int>, FieldProperties> visitedFields, expansionFields;

	int startX = recentX;
	int startY = recentY;

	if (map[metaX][metaY] == 5)
		cout << "\n\nna koncu trasy jest przeszkoda!\n\n";
	else if (map[startX][startY] == 5)
		cout << "\n\nna poczatku trasy jest przeszkoda!\n\n";
	else
	{
		while (recentX != metaX || recentY != metaY)
		{
			// dodaj do listy otwartej nowe wspolrzedne
			if (recentX >= 1 && recentX <= SIZE - 1 && recentY >= 1 && recentY <= SIZE - 1)
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
				if (recentX == 0 && map[recentX + 1][recentY] != 5 && visitedFields[{recentX + 1, recentY}].value == 0)
					expansionFields[{recentX + 1, recentY}].parentCoos = { recentX, recentY };
				// DOLNY PRAWY ROG
				else if (recentX == SIZE && map[recentX - 1][recentY] != 5 && visitedFields[{recentX - 1, recentY}].value == 0)
					expansionFields[{recentX - 1, recentY}].parentCoos = { recentX, recentY };
				// DOLNA LINIA NIE SKAJNA NA WSP X
				else if (recentX <= SIZE - 1 && recentX >= 1)
				{
					if (map[recentX + 1][recentY] != 5 && visitedFields[{recentX + 1, recentY}].value == 0) expansionFields[{recentX + 1, recentY}].parentCoos = { recentX, recentY };
					if (map[recentX - 1][recentY] != 5 && visitedFields[{recentX - 1, recentY}].value == 0) expansionFields[{recentX - 1, recentY}].parentCoos = { recentX, recentY };
				}
			}
			else if (recentY == SIZE)
			{
				if (map[recentX][recentY - 1] != 5 && visitedFields[{recentX, recentY - 1}].value == 0) expansionFields[{recentX, recentY - 1}].parentCoos = { recentX, recentY };
				// GORNY LEWY ROG
				if (recentX == 0 && map[recentX + 1][recentY] != 5 && visitedFields[{recentX + 1, recentY}].value == 0)
					expansionFields[{recentX + 1, recentY}].parentCoos = { recentX, recentY };
				// GORNY PRAWY ROG
				else if (recentX == SIZE && map[recentX - 1][recentY] != 5 && visitedFields[{recentX - 1, recentY}].value == 0)
					expansionFields[{recentX - 1, recentY}].parentCoos = { recentX, recentY };
				else if (recentX <= SIZE - 1 && recentX >= 1)
				{
					if (map[recentX + 1][recentY] != 5 && visitedFields[{recentX + 1, recentY}].value == 0) expansionFields[{recentX + 1, recentY}].parentCoos = { recentX, recentY };
					if (map[recentX - 1][recentY] != 5 && visitedFields[{recentX - 1, recentY}].value == 0) expansionFields[{recentX - 1, recentY}].parentCoos = { recentX, recentY };
				}
			}
			// jesli nie da sie zrobic ani jedno kroku ku szukaniu drogi, zakoncz wykonywac algorytm
			if (expansionFields.empty())
				break;

			// oblicz wartosci wpolrzednych dodanych do otwartej listy
			for (auto it = expansionFields.begin(); it != expansionFields.end(); it++)
			{
				it->second.value = sqrt(pow(it->first.front() - metaX, 2) + pow(it->first.back() - metaY, 2));
			}
			// szukamy przyleglej kratki o najmniejszej wartosci
			double lowestValue;
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

			// pole z najmniejsza wartoscia dodajemy do mapy visitedFIelds
			int parentX = recentX;
			int parentY = recentY;

			recentX = lowValCoos.front();
			recentY = lowValCoos.back();

			visitedFields[{recentX, recentY}].value = lowestValue;
			visitedFields[{recentX, recentY}].parentCoos = { expansionFields[{recentX, recentY}].parentCoos };
			expansionFields.erase({ recentX, recentY });
		}

		// drukowanie mapy ze znaleziona sciezka
		if (recentX == metaX && recentY == metaY)
		{
			while (recentX != startX || recentY != startY)
			{
				int helpX = recentX;
				recentX = visitedFields[{recentX, recentY}].parentCoos.front();
				recentY = visitedFields[{helpX, recentY}].parentCoos.back();
				map[recentX][recentY] = 1;
			}

			print_map(map);
		}
		else
			cout << "\n\ndroga jest zablokowana!\n\n";
	}
}