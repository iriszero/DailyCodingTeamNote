#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>
#include <utility>

template <typename type>
class BFS_DFS {
private:
	unsigned long vertex_number;
	std::vector < std::pair< type, type> > vec;
	std::vector <bool> clear;
	std::vector <type> res;
	std::queue <type> qu;
	std::function<void(int)> DFS_ramda;
	std::function<void(int)> BFS_ramda;
public:
	BFS_DFS() : DFS_ramda([this](int start)->void {
		if (clear[start]) return;
		clear[start] = true;
		res.push_back(start);
		for (const std::pair<type, type> arg : vec)
			if (arg.first == start && !clear[arg.second])
				DFS_ramda(arg.second);
	}), BFS_ramda([this](int start)->void {
		if (clear[start]) return;
		qu.push(start);
		clear[qu.front()] = true;
		res.push_back(qu.front());
		while (qu.size())
		{
			for (const std::pair<type, type> arg : vec)
				if (arg.first == qu.front() && !clear[arg.second])
				{
					clear[arg.second] = true;
					res.push_back(arg.second);
					qu.push(arg.second);
				}
			qu.pop();
		}
	})
	{}
	void assign(std::vector< std::pair< type, type> > vec, unsigned long vertex_number)
	{
		this->vec = vec;
		this->vertex_number = vertex_number;
		vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
	}
	std::vector<type> result_BFS(type value)
	{
		res.clear();
		clear.assign(this->vec.size(), false);
		DFS_ramda(value);
		for (int i = 1; i < this->vertex_number; i++)
			DFS_ramda(i);
		return this->res;
	}
	std::vector<type> result_DFS(type value)
	{
		res.clear();
		clear.assign(this->vec.size(), false);
		BFS_ramda(value);
		for (int i = 1; i < this->vertex_number; i++)
			BFS_ramda(i);
		return this->res;
	}
};
template <typename type>
void vertex_output(std::vector<type> vec)
{
	for (const type arg : vec)
	{
		std::cout << arg;
		if (arg - vec.at(vec.size() - 1))
			std::cout << " ";
	}
	std::cout << std::endl;
}
template <typename type>
std::vector<std::pair<type, type> > vertex_input(int number)
{
	std::vector< std::pair<type, type> > vec;
	type p, q;
	for (int i = 0; i < number; i++)
	{
		std::cin >> p >> q;
		vec.push_back({ p, q });
	}
	return vec;
}
/*usage

int main()
{
	int vertex_number, line_number, vertex_start;
	std::cin >> vertex_number >> line_number >> vertex_start;
	BFS_DFS<int> fs;
	fs.assign(vertex_input<int>(line_number), vertex_number);
	vertex_output<int>(fs.result_BFS(vertex_start));
	vertex_output<int>(fs.result_DFS(vertex_start));
}

*/