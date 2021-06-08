#include"Karp.h"
#include <fstream>

void Karp::readList(string fileName) {
	fstream file;
	char firstName, secondName;
	int weight;
	file.open(fileName, ios::in);
	int countStr;
	file >> Vertices >> countStr;
	if (file.eof() || Vertices == 0) throw out_of_range("Graph is empty");

	VerticesName = new char[Vertices];
	int CountVerticesName = 0;
	int** arr_check;
	arr_check = (int**)malloc(sizeof(int*) * Vertices);
	if (!arr_check) {
		throw std::out_of_range("Allocation error");
		return;
	}
	else {
		Graph_Matrix = arr_check;
	}
	int** arr_check_1;
	arr_check_1 = (int**)malloc(sizeof(int*) * Vertices);
	if (!arr_check_1) {
		throw std::out_of_range("Allocation error");
		return;
	}
	else {
		maxStream = arr_check_1;
	}
	for (size_t i = 0; i < Vertices; i++)
	{
		arr_check[i] = (int*)malloc(Vertices * sizeof(int));
		arr_check_1[i] = (int*)malloc(Vertices * sizeof(int));
		if (!arr_check[i]) { throw std::out_of_range("Allocation error"); return; }
		else Graph_Matrix[i] = arr_check[i];
		if (!arr_check_1[i]) { throw std::out_of_range("Allocation error"); return; }
		else maxStream[i] = arr_check_1[i];
		for (size_t j = 0; j < Vertices; j++) {
			Graph_Matrix[i][j] = 0;
			maxStream[i][j] = 0;
		}
	}

	int found1, found2;
	for (size_t i = 0; i < countStr; i++)
	{
		file >> firstName >> secondName >> weight;

		found1 = -1;
		for (size_t j = 0; j < CountVerticesName; j++)
			if (VerticesName[j] == firstName)
				found1 = j;
		if (found1 == -1)
		{
			VerticesName[CountVerticesName] = firstName;
			found1 = CountVerticesName;
			CountVerticesName++;
		}

		found2 = -1;
		for (size_t j = 0; j < CountVerticesName; j++)
			if (VerticesName[j] == secondName)
				found2 = j;
		if (found2 == -1)
		{
			VerticesName[CountVerticesName] = secondName;
			found2 = CountVerticesName;
			CountVerticesName++;
		}

		Graph_Matrix[found1][found2] = weight;
	}
	for (size_t i = 0; i < Vertices; i++)
	{
		if (VerticesName[i] == 'S')
			from = i;
		else if (VerticesName[i] = 'T')
			to = i;
	}
}

int Karp::MaxFlow() {
	resultStream = 0;
	int toAdd;
	do
	{
		toAdd = findFlow();
		cout << toAdd << endl;
		resultStream += toAdd;
	} while (toAdd > 0);
	return resultStream;
}

int Karp::findFlow() {
	List path;
	path.push_back(from);
	int* flow = new int[Vertices];
	int* beforeVer = new int[Vertices];
	for (size_t i = 0; i < Vertices; i++)
	{
		flow[i] = 0;
		beforeVer[i] = 0;
	}
	beforeVer[to] = -1;
	flow[from] = INT_MAX;
	int curVer;
	while ((beforeVer[to] == -1) && (!path.isEmpty()))
	{
		curVer = path.at(0);
		for (size_t i = 0; i < Vertices; i++)
		{
			if (((Graph_Matrix[curVer][i] - maxStream[curVer][i]) > 0) && (flow[i] == 0))
			{
				path.push_back(i);
				beforeVer[i] = curVer;
				if ((Graph_Matrix[curVer][i] - maxStream[curVer][i]) < flow[curVer])
					flow[i] = Graph_Matrix[curVer][i];
				else
					flow[i] = flow[curVer];
			}
		}
		path.pop_front();
	}
	if (beforeVer[to] == -1)
		return 0;
	curVer = to;
	while (curVer != from)
	{
		maxStream[beforeVer[curVer]][curVer] += flow[to];
		curVer = beforeVer[curVer];
	}
	return flow[to];
}