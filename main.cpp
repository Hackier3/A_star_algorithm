#include <iostream>
#include <vector>

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
	return map;
}

void print_map(vector<vector<int>> map)
{
	for (auto itr = map.begin(); itr != map.end(); ++itr)
	{
		for (auto value = itr->begin(); value != itr->end(); value++)
			cout << *value << " ";
		cout << endl;
	}
}