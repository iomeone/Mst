#ifndef GRAPH_H
#define GRAPH_H
#include<qlabel.h>
#include "Edge.h"
#include<vector>
#include<string>
#include<algorithm>
#include<fstream>
#include<Windows.h>
#define maxNodeNum 200
#define INF 0x4fffffff
using namespace std;

class Graph
{
private:
	int f[maxNodeNum];
	int Find(int i); //���鼯�Ĳ���
	bool Union(int a, int b); //���鼯�ĺϲ�
	bool cmp(const Edge& a, const Edge& b);
	vector<int> v;
public:
	int nodeNum; //�������
	int edgeNum; //�ߵ�����
	vector<Edge>* edges; //�߼�

	Graph();
	Graph(vector<Edge>& edge);

	Graph* getMst_Kruskal();
	Graph* getMst_Prim();
	void show(QLabel* label);
	QString toString();
	int getSum();
};

#endif // GRAPH_H
