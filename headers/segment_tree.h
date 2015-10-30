//
// segment_tree.h
//
// segment_tree class with lazy propagation
//
// INPUT: vector 
//
// OUTPUT: query 
//
// Time: 	O(Q(logN)^2) 
//			Q: query, N vectors
//
// Init: segment_tree tree(vector,[](int a, int b){return a+b; });
// 		in this case(sum), INF must be 0(must not interfere)

//INF Should not interfere Process
#define SEG_INF 0

#include <vector>
#include <iterator>
#include <algorithm>
#include <functional>

using namespace std;
template<typename type>
class segment_tree
{
private:
	std::vector<type> vector, tree, lazy;
	std::function <type(type, type)> process;
	
	size_t initilize_(size_t index, size_t start, size_t end)
	{
		if (start == end)
			return this->tree[index] = this->vector[start];
		else
			return this->tree[index] = this->process(
				this->initilize_(index * 2, start, (start + end) / 2),
				this->initilize_(index * 2 + 1, (start + end) / 2 + 1, end));
	}
	type query_(size_t index, size_t start, size_t end, size_t qstart, size_t qend)
	{
		if (start > end || end < qstart || start > qend)
			return SEG_INF;

		if (this->lazy[index])
		{
			this->tree[index] += (end - start + 1) * this->lazy[index];

			if (start != end)
			{
				this->lazy[index * 2] += this->lazy[index];
				this->lazy[index * 2 + 1] += this->lazy[index];
			}

			this->lazy[index] = 0;
		}

		if (qstart <= start && qend >= end)
			return this->tree[index];

		return this->process(
			this->query_(2 * index, start, (start + end) / 2, qstart, qend),
			this->query_(2 * index + 1, (start + end) / 2 + 1, end, qstart, qend));
	}
	void update_(size_t index, size_t start, size_t end, size_t ustart, size_t uend, type value)
	{
		if (this->lazy[index])
		{
			this->tree[index] += (end - start + 1) * this->lazy[index];

			if (start != end)
			{
				this->lazy[index * 2] += this->lazy[index];
				this->lazy[index * 2 + 1] += this->lazy[index];
			}

			this->lazy[index] = 0;
		}

		if (start > end || start > uend || end < ustart)
			return;

		if (start >= ustart && end <=uend)
		{
			this->tree[index] += (end - start + 1) * value;

			if (start != end)
			{
				this->lazy[index * 2] += value;
				this->lazy[index * 2 + 1] += value;
			}
			return;
		}

		this->update_(index * 2, start, (start + end) / 2, ustart, uend, value);
		this->update_(index * 2 + 1, (start + end) / 2 + 1, end, ustart, uend, value);

		this->tree[index] = this->process(this->tree[index*2], this->tree[index*2+1]);
		return;
	}
public:
	segment_tree() {}
	segment_tree(const std::vector<type>& vector)
	{
		this->vector = vector;
	}
	segment_tree(const std::vector<type>& vector, std::function<type(type, type)> proc)
	{
		this->vector = vector;
		this->process = proc;
	}
	void vectorize(const std::vector<type>& vector)
	{
		this->vector = vector;
	}
	void initilize()
	{
		this->tree.assign(1 + 2 * (size_t)pow(2, (size_t)ceil(log2(this->vector.size()))), 0);
		this->lazy = this->tree;

		this->initilize_(1, 0, this->vector.size() - 1);
	}
	type query(size_t start, size_t end)
	{
		if (start < 0 || end > this->vector.size() - 1 || start>end)
			return -1;
		return this->query_(1, 0, this->vector.size() - 1, start, end);
	}
	void update(size_t target, type value)
	{
		this->update(target, target, value);
	}
	void update(size_t start, size_t end, type value)
	{
		if (start < 0 || end > this->vector.size() - 1 || start > end)
			return;
		this->update_(1, 0, this->vector.size() - 1, start, end, value);
	}
	~segment_tree() {}
};

/*#include <iostream>
int main()
{
	
	vector<long long int> v;
	int n, m, k; cin >> n >> m >> k;
	while (n--)
	{
		int temp; cin >> temp;
		v.push_back(temp);
	}

	segment_tree<long long int> tree(v, [](double a, double b)->double {return a + b;});
	tree.initilize();
	int q = m + k;
	int mc = 0, kc = 0;
	while (q--)
	{
		int start,end,value,qu; cin >> qu;

		if (qu - 1)
		{
			cin >> start >> end;
			cout << tree.query(--start, --end) << endl;
			if (mc == m)
				return 0;
			mc++;
		}
		else
		{
			cin >> start >> end >> value;
			tree.update(--start, --end, value);
			if (kc == k)
				return 0;
			kc++;
		}
	}
	return 0;
}*/