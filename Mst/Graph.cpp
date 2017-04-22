#include "Graph.h"

Graph::Graph(vector<Edge>& edge) :nodeNum(nodeNum), edgeNum(edgeNum)
{
	edges = new vector<Edge>();
	edges->clear();
	int book[maxNodeNum] = { 0 };
	for (vector<Edge>::iterator it = edge.begin(); it != edge.end(); it++)
	{
		edges->push_back(*it);
		book[it->nodeA]++;
		book[it->nodeB]++;
	}
	int cnt = 0;
	for (int i = 0; i < maxNodeNum; i++)
		if (book[i] != 0)
		{
			cnt++;
			v.push_back(i);
		}
	edgeNum = edge.size();
	nodeNum = cnt;
}

void Graph::show(QLabel * label)
{
	//���label
	label->clear();

	//����gv�ļ�
	ofstream file;
	file.open("graph.gv", ios::out);
	file << "graph graphname {" << endl;
	//file << "size=\"10, 3\";" << endl;
	for (vector<Edge>::iterator it = edges->begin(); it != edges->end(); it++)
		file << it->nodeA << "--" << it->nodeB << "[label=\"" << it->value << "\"]" << endl;
	// a--b[label="c"]
	file << "}" << endl;
	file.close();
	//����dot��������png
	//system("dot graph.gv -Tpng -o graph.png"); //���кڿ����һ�¡���
	WinExec("dot graph.gv -Tpng -o graph.png", SW_HIDE); //�����ڿ�򡣡�

	//��ʾpng
	QPixmap pix;
	pix.load("graph.png");
	label->setPixmap(pix);
	label->show();
}

QString Graph::toString()
{
	QString ret;
	for (vector<Edge>::iterator it = edges->begin(); it != edges->end(); it++)
	{
		ret.append(QString::number(it->nodeA, 10));
		ret.append(" ");
		ret.append(QString::number(it->nodeB, 10));
		ret.append(" ");
		ret.append(QString::number(it->value, 10));
		ret.append("\n");
	}
	return ret;
}

int Graph::getSum()
{
	int sum = 0;
	for (vector<Edge>::iterator it = edges->begin(); it != edges->end(); it++)
		sum += it->value;
	return sum;
}

Graph::Graph()
{
	edges = new vector<Edge>();
	this->edgeNum = 0;
	this->nodeNum = 0;
}



int Graph::Find(int i)
{
	if (i != f[i])
		f[i] = Find(f[i]); //·��ѹ��
	return f[i];
}

bool Graph::Union(int a, int b)
{
	int fa = Find(a);
	int fb = Find(b);
	if (fa != fb)
	{
		f[fa] = fb;
		return true;
	}
	else
		return false;
}
bool Graph::cmp(const Edge& a, const Edge& b)
{
	return a.value < b.value; //��Ȩ��С��������
}


Graph* Graph::getMst_Prim()
{
	if (nodeNum == edgeNum + 1)
		return new Graph(*edges);

	vector<Edge> tmp;
	//�����ڽӾ����ʾͼ
	int map[maxNodeNum][maxNodeNum];
	for (int i = 0; i < maxNodeNum; i++)
		for (int j = 0; j < maxNodeNum; j++)
			map[i][j] = INF;
	for (vector<Edge>::iterator it = edges->begin(); it != edges->end(); it++)
	{
		map[it->nodeA][it->nodeB] = min(it->value, map[it->nodeA][it->nodeB]);
		map[it->nodeB][it->nodeA] = min(it->value, map[it->nodeB][it->nodeA]);
	}

	//Prim�㷨
	int mincost[maxNodeNum], mst[maxNodeNum];
	mincost[v[0]] = 0;
	mst[v[0]] = 0;
	for (int i = 1; i < nodeNum; i++)
	{
		mincost[v[i]] = map[v[0]][v[i]];
		mst[v[i]] = 1;
	}
	for (int i = 1; i < nodeNum; i++)
	{
		int min = INF, minid;
		for (int j = 1; j < nodeNum; j++)
			if (mincost[v[j]] < min && mincost[v[j]] != 0)
			{
				min = mincost[v[j]];
				minid = v[j];
			}
		//cout << "(" << (char)(mst[minid] + 'A' - 1) << "," << (char)(minid + 'A' - 1) << ")";
		tmp.push_back(Edge(mst[minid], minid, min));
		mst[minid] = 0, mincost[minid] = 0;
		for (int j = 1; j < nodeNum; j++)
			if (map[minid][v[j]] < mincost[v[j]])
			{
				mincost[v[j]] = map[minid][v[j]];
				mst[v[j]] = minid;
			}
	}


	return new Graph(tmp);
}

Graph* Graph::getMst_Kruskal()
{
	if (nodeNum == edgeNum + 1)
		return new Graph(*edges);
	for (int i = 0; i < maxNodeNum; i++)
		f[i] = i; //��ʼ�����鼯
	vector<Edge>* edges_tmp = new vector<Edge>(*edges); //����һ�ݱ߼���
	vector<Edge> edges_result = vector<Edge>(); //���ڴ�Ž��
	sort(edges_tmp->begin(), edges_tmp->end());
	for (vector<Edge>::iterator it = edges_tmp->begin(); it != edges_tmp->end(); it++)
	{
		if (edges_result.size() == edges_tmp->size() - 1) //��С���������ҵ�
			break;
		if (Union(it->nodeA, it->nodeB))
			edges_result.push_back(*it);
	}
	Graph* result = new Graph(edges_result);
	delete edges_tmp; //�ͷ��ڴ�
	return result;
}