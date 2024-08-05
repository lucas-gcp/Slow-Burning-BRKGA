#include <vector>
#include <string>
#include <algorithm>
using std::vector;

vector<vector<int>>::size_type graphSize(vector<vector<int>> graph);

vector<int> neighbouringVertex(vector<vector<int>> graph, int vertex);

vector<int> parseLine(std::string line);

vector<int> readGraphInfo(std::string filepath);

vector<vector<int>> readGraph(std::string filepath);
