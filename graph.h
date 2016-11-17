//graph.h
#include <climits>
#include <vector>
#include <fstream>

using namespace std;

template<typename T>
class Graph
{
	private:
		//int max_size ;		//��󶥵��� 
		vector<T> vertexList;	//�����
		vector< vector<int> > edge;//�ڽӾ���
		//int currentEdges;		//��ǰ����	
		
		bool findVertex(const T& v);
		int getVertexPosition(const T& v);
		
	public:
		
//		Graph();		
		bool isEmpty();
		void printGraph();		
		int getNumberOfVertex();
		int getWeight(const T& v1, const T& v2);
		int getFirstNeighbor(int v);
		int getNextNeighbor(int v1,int v2);
		
		void insertVertex(const T& v);
		void deleteVertex(const T& v);
		void insertEdge(const T& v1, const T& v2, int w);
		void deleteEdge(const T& v1, const T& v2);
		
		void readGraph(string fileName);
};

//�Ծ������ʽ���ͼ 
template <typename T>
void Graph<T>:: printGraph()
{
	for(int i=0; i<vertexList.size(); i++)
	{
		cout<<vertexList[i]<<": [ ";
		for(int j=0; j<vertexList.size(); j++)
		{
			if(edge[i][j] < INT_MAX)
				cout<<edge[i][j]<<" ";
			else
				cout<<" ��"<<" ";
		}
		cout<<"]"<<endl;
	}
	cout<<endl<<endl;
}

//���ͼ�Ƿ�Ϊ��
template <typename T>
bool Graph<T>:: isEmpty()
{
	return vertexList.empty();
}

//����ͼ�Ķ������
template <typename T>
int Graph<T>:: getNumberOfVertex()
{
	return vertexList.size();
}

//���ض���vertex�ڶ�����е�λ�ã���ţ�
template <typename T>
int Graph<T>:: getVertexPosition(const T& v)
{
	for(int i=0; i<vertexList.size(); i++)
	{
		if(vertexList[i] == v)//
		{
			return i;
		}
	}
	return -1;
}

//��鶥��vertex�Ƿ����ڶ������
template <typename T>
bool Graph<T>:: findVertex(const T& v)
{
	if(getVertexPosition(v) != -1)
	{
		return true;
	}
	return false;	
}

//����ָ���ߵ�Ȩֵ
template <typename T>
int Graph<T>:: getWeight(const T& v1, const T& v2)
{
	int pos1 = getVertexPosition(v1);
	int pos2 = getVertexPosition(v2);
	
	if(pos1 != -1 && pos2 != -1)
		return edge[pos1][pos2];
	else
		return INT_MAX;//ʵ��Ӧ�ý����쳣���� 
}

//�������Ϊv�Ķ���ĵ�һ���ڽӶ�������
template <typename T>
int Graph<T>:: getFirstNeighbor(int v)
{
	for(int i=0; i<vertexList.size(); i++)
	{
		if(edge[v][i] > 0 && edge[v][i] < INT_MAX)
		{
			return i;
		}
	}
	return -1;
}

//�������Ϊv1�Ķ�����������Ϊv2�Ķ������һ���ڽӶ�������
template <typename T>
int Graph<T>:: getNextNeighbor(int v1,int v2)
{
	if(v1 != -1 && v2 != -1)
	{
		for(int i = v2+1; i<vertexList.size(); i++)
		{
			if(edge[v1][i] > 0 && edge[v1][i] < INT_MAX)
			{
				return i;
			}
		}
	}
	return -1;
}

//����һ������
template <typename T>
void Graph<T>:: insertVertex(const T& v)
{
	if(findVertex(v))//�Ѵ��ڸö��� 
		return;
	//������ 
	for(int i=0; i<vertexList.size(); i++)
	{
		edge[i].push_back(INT_MAX);
	}
	//������
	vector<int> column(vertexList.size(), INT_MAX);
	column.push_back(0);
	edge.push_back(column);
	//���붥��� 
	vertexList.push_back(v); 
}

/*��ͼ��ɾȥ����v����������������ı�
*ɾ����pos�к͵�pos�� 
*Ȼ��Ӷ������ɾ������ 
*/
template <typename T>
void Graph<T>:: deleteVertex(const T& v)
{
	int pos = getVertexPosition(v);
	
	if(pos == -1)
		return;

	//ɾ����pos�� 
	for(int i=0; i<vertexList.size(); i++)
	{
		edge[i].erase(edge[i].begin() + pos);
	}
	//ɾ����pos��
	edge.erase(edge.begin() + pos);
	//�Ӷ������ɾ��
	vertexList.erase(vertexList.begin() + pos);	  
}

/*����һ���ߣ�v1,v2),��ȨֵΪw
 *����֮ǰ�����Ѵ��� 
*/
template <typename T>
void Graph<T>:: insertEdge(const T& v1, const T& v2, int w)
{
	int pos1 = getVertexPosition(v1);
	int pos2 = getVertexPosition(v2);
	
	if(pos1 != -1 && pos2 != -1)
	{
		edge[pos1][pos2] = w;
		edge[pos2][pos1] = w;
	}
}

/*��ͼ��ɾȥ��
 *��ɾ���ı߹��������������Ѵ��� 
*/
template <typename T>
void Graph<T>:: deleteEdge(const T& v1, const T& v2)
{
	if(v1 == v2)
		return;
		
	int pos1 = getVertexPosition(v1);
	int pos2 = getVertexPosition(v2);
	
	if(pos1 != -1 && pos2 != -1)
	{
		edge[pos1][pos2] = INT_MAX;
		edge[pos2][pos1] = INT_MAX;
	}
}

//���ļ��е����ݹ���ͼ
template <typename T>
void Graph<T>:: readGraph(string fileName)
{
	int vertexNumber;
	T vertex;
	T v1,v2;
	int weight;
	
	ifstream in(fileName.c_str(),ios_base::in);
	if(!in)
	{
		cout<<"file open error!"<<endl;
		exit(1);
	}
	in>>vertexNumber;
	for(int i=0; i<vertexNumber; i++)
	{
		in>>vertex;
		insertVertex(vertex);//���붥��
	}
	while(in>>v1>>v2>>weight)
	{
		insertEdge(v1, v2, weight);//����� 
	}
} 