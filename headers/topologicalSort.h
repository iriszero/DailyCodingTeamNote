//
//  topologicalSort.h
//  DailyCodingTeamNote
//
//  Created by MaybeS on 10/3/15.
//  Copyright (c) 2015 Maybe. All rights reserved.
//
#include <vector>
#include <utility>
#include <algorithm>

using namespace std;
//Toplogical Sort
//위상정렬. DAG가 아니면 빈 벡터 반환
template<typename type>
void topologicalSort_sub(size_t index, vector<type>& map, vector<type>& result, vector<type>& order)
{
	result[index] = 1;
	for(int i = 0; i < map.size(); i++)
		if(map[index][i] && !result[i])
			topologicalSort_sub(i,map,result,order);
	order.push_back(index);
}
template<typename type>
vector<type> topologicalSort(vector<type> map)
{
	vector<type> order, result(map.size(),0);
	for(int i = 0; i < map.size(); i++)
		if(!result[i])
			topologicalSort_sub(i,map,result,order);
	reverse(order.begin(), order.end());
	for(int i = 0; i < map.size(); i++)
		for(int j = i + 1; j < map.size(); j++)
			if(map[order[j]][order[i]])
				return vector<type>();
	return order;
}