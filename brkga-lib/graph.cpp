#include "graph.h"
#include <fstream>

vector<int> parseLine(std::string line)
{
	vector<int> parsed_line;
	std::string parser;
	for (auto i: line) {
		if (i != ' ') {
			parser.push_back(i);
		} else {
			parsed_line.push_back(stoi(parser));
			parser = std::string();
		}
	}
	parsed_line.push_back(stoi(parser));

	return parsed_line;
}

vector<int> readGraphInfo(std::string filepath)
{
	std::ifstream graph_txt(filepath);
	vector<int> info;
	std::string line;
	std::getline(graph_txt, line);
	info = parseLine(line);

	return info;
}

vector<vector<int>> readGraph(std::string filepath)
{
	std::ifstream graph_txt(filepath);
	vector<vector<int>> graph;
	std::string line;
	std::getline(graph_txt, line);
	while (std::getline(graph_txt, line))
		graph.push_back(parseLine(line));

	return graph;
}
