#include <iostream>
#include <vector>
#include <cstdlib>
#include <cstdio>
#include <ctime>

using namespace std;

vector<vector<int>> generate_map(int size);
void print_map(vector<vector<int>> map);

int main()
{
	vector<vector<int>> map = generate_map(20);
	print_map(map);
	return 0;
}

vector<vector<int>> generate_map(int size)
{
	vector<vector<int>> map(size, vector<int>(size, 0));
	int drawRight = 0;
	int drawDown = 0;
	srand(time(NULL));

	for (int i = 0; i < map.size(); i++)
	{
		for (int j = 0; j < map.size(); j++)
		{
			if (drawRight != 0)
			{
				map[i][j] = 5;
				drawRight--;
			}
			else if (rand() % (map.size() * 3) == 1)
			{
				map[i][j] = 5;
				drawRight = rand() % (map.size() / 2);
			}

			if (drawDown != 0)
			{
				map[i][j] = 5;
				drawDown--;
			}
			else if (rand() % (map.size() * 3) == 1)
			{
				map[i][j] = 5;
				drawDown = rand() % (map.size() / 2);
			}
		}
	}

	return map;
}

void print_map(vector<vector<int>> map)
{
	for (auto itr = map.begin(); itr != map.end(); itr++)
	{
		for (auto value = itr->begin(); value != itr->end(); value++)
			cout << *value << " ";
		cout << endl;
	}
}