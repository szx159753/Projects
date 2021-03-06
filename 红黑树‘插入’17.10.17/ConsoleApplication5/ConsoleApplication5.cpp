// 二叉搜索树.cpp: 定义控制台应用程序的入口点。
//
#include "stdafx.h"
#include<iostream>
#include<queue>
using namespace std;
queue<int> q;
int a[1000], l[1000], r[1000], p[1000],c[1000];
int root = 0;
int change(int i, int j);
int turn(int m, int i)
{
	int pi = p[i];
	if (!m)
	{
		change(pi,i);
		int li = l[i];
		l[i] = pi;
		p[pi] = i;
		r[pi] = li;
		p[li] = pi;//左旋
	}
	else
	{
		change(pi,i);
		int ri = r[i];
		r[i] = pi;
		p[pi] = i;
		l[pi] = ri;
		p[ri] = pi;//右旋
	}
	p[0] = 0;
	l[0] = 0;
	r[0] = 0;
	c[0] = 0;
	return 0;
}
int color1(int i)
{
	if (i == root||!i)
	{
		c[i] = 0;
		return 0;
	}
	c[i] = 1;
	if (!c[p[i]])return 0;
	else
	{
		if (l[p[p[i]]] == p[i])
		{
			if (c[r[p[p[i]]]] == 1)
			{
				c[p[i]] = 0;
				c[p[p[i]]] = 1;
				c[r[p[p[i]]]] = 0;
				//case 1
			}
			else
			{
				if (r[p[i]] == i)
				{
					turn(0, i);//case 2
				}
				if (i == root)return 0;
				turn(1, i);
				c[i] = 1;
				c[l[i]] = 0;
				c[r[i]] = 0;
				//case 3
			}
		}
		else
		{
			if (c[l[p[p[i]]]] == 1)
			{
				c[p[i]] = 0;
				c[p[p[i]]] = 1;
				c[l[p[p[i]]]] = 0;
				//case 1
			}
			else
			{
				if (l[p[i]] == i)
				{
					turn(1, i);//case 2
				}
				if (i == root)return 0;
				turn(0, i);
				c[i] = 1;
				c[l[i]] = 0;
				c[r[i]] = 0;
				//case 3
			}
		}
		p[0] = 0;
		l[0] = 0;
		r[0] = 0;
		c[0] = 0;
		color1(p[p[i]]);
	}
}
int insert(int i)
{
	if (!root)
	{
		root = i;
		c[i] = 0;
		return 0;
	}
	else
	{
		int num = root;
		int pnum = num;
		while (num)
		{
			pnum = num;
			if (a[num] < a[i])
			{
				num = r[num];
			}
			else
			{
				num = l[num];
			}
		}
		p[i] = pnum;
		if (a[pnum] < a[i])
		{
			r[pnum] = i;
		}
		else
		{
			l[pnum] = i;
		}
	}
	color1(i);
}
int paint()
{
	q.push(root);
	while (!q.empty())
	{
		int n = q.size();
		for (int i = 1; i <= n; i++)
		{
			int num = q.front();
			q.pop();
			if (num)
			{
				q.push(l[num]);
				q.push(r[num]);
			}

			cout << num << "\t";
		}
		cout << endl;
	}
	return 0;
}
int find(int x)
{
	int num = root;
	while (a[num] != x)
	{
		if (num == 0)
		{
			return 0;
		}
		if (a[num] < x)num = r[num];
		else if (a[num] > x)num = l[num];
	}
	return num;
}
int next1(int i)
{
	int num = i;
	if (r[num])
	{
		num = r[num];
		while (l[num])
		{
			num = l[num];
		}
		return num;
	}
	else
	{
		while (num != l[p[num]] && num)
		{
			num = p[num];
		}
		return p[num];
	}
}
int change(int i, int j)
{
	if (i == root)root = j;
	if (i == l[p[i]])
	{
		l[p[i]] = j;
		p[j] = p[i];
	}
	else
	{
		r[p[i]] = j;
		p[j] = p[i];
	}
	return 0;
}
int del(int i)
{
	if (!l[i] || !r[i])
	{
		if (!l[i])
		{
			change(i, r[i]);
		}
		else
		{
			change(i, l[i]);
		}
	}
	else
	{
		int num = next1(i);
		del(num);
		a[i] = a[num];
	}
	return 0;
}
int out(int num)
{
	if (l[num])out(l[num]);
	cout << a[num] << " ";
	if (r[num])out(r[num]);
	return 0;
}
int main()
{
	int n;
	cin >> n;
	memset(a, 0, sizeof(a));
	memset(l, 0, sizeof(l));
	memset(r, 0, sizeof(r));
	memset(p, 0, sizeof(p));
	for (int i = 1; i <= n; i++)
	{
		a[i] = rand();
		insert(i);
	}
	//paint();
	//del(7);
	paint();
	out(root);
	return 0;
}

