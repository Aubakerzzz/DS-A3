#include<iostream>
#include<iomanip>
#include<fstream>
#include<string>
using namespace std;

int tem = 0;
const int COUNT = INT_MAX;

void ShortestPathAlgorithm(int** , int, int, int);
string ShortestPathAlgorithm(int, int, int, int**);
void printCityPath(int*, int n, string& s);

class Node {
public:
	string city;
	Node* next;
	Node();

};

Node::Node() {
	city = "";
	next = NULL;
}

class AdjList {
public:
	Node* head;
	AdjList();
	void Insert(string);
	void remove(string);
	void Display();
	string& operator[](int n);
	int FindStr(string s);
};

AdjList::AdjList() {
	head = NULL;
}

void AdjList::Insert(string s) {
	Node* NewNode = new Node;
	NewNode->city = s;
	if (head == NULL) {
		head = NewNode;
		return;
	}
	Node* curr = head;
	while (curr->next != NULL) {
		curr = curr->next;
	}
	curr->next = NewNode;
}

void AdjList::remove(string s) {
	Node* curr = head;
	if (curr == NULL) {
		return;
		cout << "-1";
	}
	while (curr->next != NULL) {
		if (s == curr->next->city)
			break;
		curr = curr->next;
	}
	Node* NewNode = curr->next;
	curr->next = curr->next->next;
	delete NewNode;
}

void AdjList::Display() {
	Node* curr = head;
	if (curr == NULL)
		cout << "-1";
	while (curr != NULL) {
		cout << curr->city << endl;
		curr = curr->next;
	}
}

string& AdjList::operator[](int n) {

	if (n < tem) {
		Node* curr = head;
		for (int i = 0; i < n; i++)
			curr = curr->next;
		return curr->city;
	}
}
int AdjList::FindStr(string s) {
	Node* curr = head;
	if (curr == NULL) {
		cout << "-1";
	}
	int i = 0;
	while (curr != NULL) {
		if (s == curr->city)
			return i;
		curr = curr->next;
		i++;
	}
	return -1;
}

AdjList V;

class Graph {
public:
	int** arr;
	Graph();
	Graph(int**);
	Graph* addNode(string str);
	Graph* deleteNode(string str);
	Graph* addEdge(string, string , int);
	Graph* deleteEdge(string, string);
	void printGraph();
	string printsingleLink(string);
	void shortestPathfromOnetoall(string);
	void shortestPathfromalltoone(string);
	string ShortestRoutefrompair(string, string);
	void secondshortestPathfromOnetoall(string);
	void secondshortestPathfromalltoone(string);
	string secondShortestRoutefrompair(string, string);
};

Graph::Graph() {
	arr = new int* [tem];
	for (int i = 0; i < tem; i++)
		arr[i] = new int[tem] {};
}
Graph::Graph(int** array) {
	arr = new int* [tem];
	for (int i = 0; i < tem; i++)
		arr[i] = new int[tem] {};
	for (int i = 0; i < tem; i++) {
		for (int j = 0; j < tem; j++) {
			arr[i][j] = array[i][j];
		}
	}
}
Graph* Graph::addNode(string str) {
	tem++;
	V.Insert(str);
	int** temp = new int* [tem];
	for (int i = 0; i < tem; i++)
		temp[i] = new int[tem] {};
	for (int i = 0; i < tem; i++)
		for (int j = 0; j < tem; j++) {
			if (i == tem - 1 || j == tem - 1)
				temp[i][j] = 0;
			else
				temp[i][j] = arr[i][j];
		}

	for (int i = 0; i < tem - 1; i++)
		delete[] arr[i];
	delete[] arr;

	arr = new int* [tem];
	for (int i = 0; i < tem; i++)
		arr[i] = new int[tem] {};

	for (int i = 0; i < tem; i++)
		for (int j = 0; j < tem; j++) {
			arr[i][j] = temp[i][j];
		}
	return this;
}

Graph* Graph::deleteNode(string str) {
	tem--;
	int t = V.FindStr(str);
	V.remove(str);
	int** temp = new int* [tem];
	for (int i = 0; i < tem; i++)
		temp[i] = new int[tem];
	int k = 0, l = 0;
	for (int i = 0; i < tem + 1; i++) {
		l = 0;
		if (i != t) {
			for (int j = 0; j < tem + 1; j++)
				if (j != t) {
					temp[k][l] = arr[i][j];
					l++;
				}
			k++;
		}
	}
	for (int i = 0; i < tem + 1; i++)
		delete[] arr[i];
	delete[] arr;
	arr = new int* [tem];
	for (int i = 0; i < tem; i++)
		arr[i] = new int[tem];

	for (int i = 0; i < tem; i++)
		for (int j = 0; j < tem; j++) {
			arr[i][j] = temp[i][j];
		}
	return this;
}

Graph* Graph::addEdge(string s1, string s2, int n)
{
	int i = V.FindStr(s1);
	int j = V.FindStr(s2);
	arr[i][j] = n;
	arr[j][i] = n;
	return this;
}

Graph* Graph::deleteEdge(string s1, string s2)
{
	int i = V.FindStr(s1);
	int j = V.FindStr(s2);
	arr[i][j] = 0;
	arr[j][i] = 0;
	return this;
}

void Graph::printGraph()
{
	for (int i = 0; i < tem; i++)
	{
		cout << setw(15) << left << V[i] << " || ";

		for (int j = 0; j < tem; j++)
		{
			cout << setw(4) << arr[i][j];
		}
		cout << endl;
	}
}


string Graph::printsingleLink(string s) {
	int n = V.FindStr(s);
	string t;
	t += s;
	t += ":";
	bool flag = 1;
	for (int i = 0; i < tem; i++) {
		if (arr[n][i] != 0) {
			if (flag == 1) {
				t += " ";
				flag = 0;
			}
			t += "~> ";
			t += V[i];
		}
	}
	return t;
}

void Graph::shortestPathfromOnetoall(string str) {
	int n = V.FindStr(str);
	if (n != -1) {
		cout << endl << "SHORTEST FROM ONE  " << str << "TO ALL CITIES ARE  : " << endl << endl;
		int seq = 0;
		ShortestPathAlgorithm(arr, tem, n, seq);
	}
	else
		cout << str << "DOESN'T EXIT" << endl;
	
}

void Graph::shortestPathfromalltoone(string str)
{
	int n = V.FindStr(str);
	if (n != -1)
	{
		cout << "\nShortest Paths from ALL Cities to " << str << " are : " << endl << endl;
		int seq = 1;
		ShortestPathAlgorithm(arr, tem, n, seq);
	}
	else
	{
		cout << str << " does not exist" << endl;
	}
}
string Graph::ShortestRoutefrompair(string s1, string s2)
{
	int nFinder = V.FindStr(s1);
	int mFinder = V.FindStr(s2);
	if (nFinder != -1) {
		if (mFinder != -1) {
			return ShortestPathAlgorithm(tem, nFinder, mFinder, arr);
		}
	}
	else
		cout << "Path does not exist!! " << endl;

}

void Graph::secondshortestPathfromOnetoall(string s) {
	int n = V.FindStr(s);
	if (n != -1) {
		cout << endl << "Second Shortest Paths from " << s << " to ALL Cities are : " << endl << endl;
		string tempstr = "";
		for (int k = 0; k < tem; k++) {
			tempstr = secondShortestRoutefrompair(s, V[k]);
			cout << setw(10) << left << V[k] << " =>  " << setw(40) << tempstr << endl;
		}
	}
	else
		cout << s << " does not exist!!" << endl;
	
}

void Graph::secondshortestPathfromalltoone(string s) {
	int n = V.FindStr(s);
	if (n != -1) {
		cout << "Second Shortest Paths from ALL Cities to " << s << " are : " << endl << endl;
		string tempstr = "";
		for (int k = 0; k < tem; k++) {
			tempstr = secondShortestRoutefrompair(s, V[k]);
			for (int y = 0; y < tempstr.size(); y++)
				if (tempstr[y] == '>') {
					tempstr[y - 1] = '<';
					tempstr[y] = '-';
				}
			cout << endl << setw(10) << left << V[k] << " =>  " << setw(40) << tempstr << endl;
		}
	}
	else
		cout << s << " does not exist!!" << endl;
}

string Graph::secondShortestRoutefrompair(string s1, string s2) {
	string tempr = "PATH DOESN'T EXIT!!";
	int n = V.FindStr(s1);
	int m = V.FindStr(s2);
	if (n != -1 && m != -1) {
		string tempstr = "", str = "";
		int* ver = new int[tem];
		for (int i = 0; i < tem; i++)
			ver[i] = -1;
		int** temparr = new int* [tem];
		for (int i = 0; i < tem; i++)
			temparr[i] = new int[tem];
		tempstr = "";
		str = "";
		for (int x = 0; x < tem; x++)
			for (int y = 0; y < tem; y++) {
				temparr[x][y] = arr[x][y];
			}
		tempstr = ShortestRoutefrompair(s1, s2);
		int verArrCount = 0;
		ver[verArrCount++] = n;
		for (int k = 0; k < tempstr.size(); k++) {
			if (tempstr[k] == '>') {
				k++;
				for (int t = k + 1; t < tempstr.size(); t++) {
					if (tempstr[t] == ' ') {
						if (tempstr[t + 1] == '-') {
							ver[verArrCount++] = V.FindStr(str);
							str = "";
							t += 3;
						}
					}
					else
						str += tempstr[t];
				}
				break;
			}
		}
		ver[verArrCount] = m;
		for (int i = 0; i < verArrCount; i++) {
			temparr[ver[i]][ver[i + 1]] = COUNT;
			temparr[ver[i + 1]][ver[i]] = COUNT;
		}
		return ShortestPathAlgorithm(tem, n, m, temparr);
	}
	else
		return tempr;
}


int** ReadFromFile() {
	ifstream file("GraphData.csv");
	string str;
	string t = "";
	int x = 0, y = 0;
	getline(file, str);
	for (int i = 0; i < str.size(); i++)
		if (str[i] == ',')
			tem++;
	cout << tem << endl;
	int** arr = new int* [tem];
	for (int i = 0; i < tem; i++)
		arr[i] = new int[tem];
	int k = 0, j = 0;
	while (getline(file, str)) {
		t = "";
		k = 0;
		for (int i = 0; i < str.size(); i++) {
			if (str[i] != ',')
				t += str[i];
			if (str[i] == ',') {
				V.Insert(t);
				i++;
				t = "";
				for (; i < str.size(); i++) {
					if (str[i] == ',') {
						x = stoi(t);
						t = "";
						arr[j][k] = x;
						k++;
					}
					else
						t += str[i];

					if (i + 1 == str.size()) {
						y = stoi(t);
						t = "";
						arr[j][k] = y;
						k++;
					}
				}
				break;
			}

		}
		j++;
	}
	return arr;
}
int minimum(int* distance, bool* visited, int n) {
	int min = COUNT;
	int index = 0;
	for (int i = 0; i < n; i++) {
		if (visited[i] == false) {
			if (distance[i] < min) {
				min = distance[i];
				index = i;
			}
		}
	}
	return index;

}

void printCityPath(int* parent, int n, string& s) {
	if (n == 0)
		return;
	n = parent[n];
	printCityPath(parent, n, s);
	s += V[n];
	s += " ~> ";
}

void ShortestPathAlgorithm(int** arr, int n, int start, int seq) {
	int* distance = new int[n];
	bool* visited = new bool[n];
	int* parent = new int[n];
	for (int i = 0; i < n; i++) {
		parent[i] = i;
		distance[i] = COUNT;
		visited[i] = 0;
	}
	distance[start] = 0;
	for (int t = 0; t < n; t++) {
		int m = minimum(distance, visited, n);
		visited[m] = 1;
		for (int k = 0; k < n; k++) {
			if (visited[k] == false) {
				if (arr[m][k] != COUNT) {
					if (distance[m] != COUNT) {
						if ((distance[m] + arr[m][k]) < distance[k]) {
							parent[k] = m;
							distance[k] = distance[m] + arr[m][k];
						}
					}
				}
			}
		}

	}
	int temp = 0;
	string str = "";
	for (int i = 0; i < n; i++) {
		if (distance[i] != COUNT) {
			str = "";
			temp = parent[i];
			printCityPath(parent, temp, str);
			str += V[parent[i]];
			str += " ~> ";
			str += V[i];
			bool flag = 0;
			for (int k = 0; k < V[start].size(); k++) {
				if (str[k] != V[start][k]) {
					flag = 1;
					break;
				}
			}
			if (flag) {
				string tempstr = str;
				str = V[start];
				str += " ~> ";
				str += tempstr;
			}
			if (seq != 0) {
				for (int y = 0; y < str.size(); y++)
					if (str[y] == '>') {
						str[y - 1] = '<';
						str[y] = '-';
					}
			}
			cout << setw(10) << left << V[i] << " || " << setw(5) << distance[i] << " =>  " << setw(50) << str << endl;
		}
		else
			cout << setw(10) << left << V[i] << " || " << setw(5) << 0 << " =>   NO PATH" << endl;
	}


}

string ShortestPathAlgorithm(int n, int start, int end, int** arr) {

	string newnew = " PATH INVALID";
	int* distance = new int[n];
	bool* visited = new bool[n];
	int* parent = new int[n];

	for (int i = 0; i < n; i++) {
		parent[i] = i;
		distance[i] = COUNT;
		visited[i] = 0;
	}
	distance[start] = 0;
	for (int t = 0; t < n; t++) {
		int m = minimum(distance, visited, n);
		visited[m] = 1;
		for (int k = 0; k < n; k++) {
			if (visited[k] == false) {
				if (arr[m][k] != COUNT) {
					if (distance[m] != COUNT) {
						if ((distance[m] + arr[m][k]) < distance[k]) {
							parent[k] = m;
							distance[k] = distance[m] + arr[m][k];
						}
					}
				}
			}
		}

	}
	int temp = 0;
	string str = "";
	if (distance[end] != COUNT) {
		str = "";
		temp = parent[end];
		printCityPath(parent, temp, str);
		str += V[parent[end]];
		str += " ~>";
		str += V[end];
		bool flag = 0;
		for (int k = 0; k < V[start].size(); k++) {
			if (str[k] != V[start][k]) {
				flag = 1;
				break;
			}
		}

		if (flag) {
			string tempstr = str;
			str = V[start];
			str += " ~> ";
			str += tempstr;
		}
		return str;
	}
	else
		return newnew;

}


int main() {

	Graph g(ReadFromFile());
	cout << "========================================================================================================================" << endl;
	cout << "**************************************************PRINTING GRAPH*******************************************************" << endl << endl << endl;
	g.printGraph();

	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "**************************************************PRINTING GRAPH*******************************************************" << endl << endl << endl;

	g.deleteNode("Multan");
	g.printGraph();
	
	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "**************************************************PRINTING GRAPH*******************************************************" << endl << endl << endl;

	g.addNode("Swat");
	g.printGraph();

	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "**************************************************PRINTING GRAPH*******************************************************" << endl << endl << endl;

	g.addEdge("Karachi", "Peshawar", 200);
	g.printGraph();

	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "**************************************************PRINTING GRAPH*******************************************************" << endl << endl << endl;

	g.deleteEdge("Quetta", "Khuzdar");
	g.printGraph();

	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "**************************************************SECOND SHORTEST FROM ALL TO ONE*******************************************************" << endl << endl << endl;

	g.secondshortestPathfromalltoone("Mansehra");

	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "**************************************************SHORTEST FROM ALL TO ONE*******************************************************" << endl << endl << endl;

	g.shortestPathfromalltoone("Mansehra");

	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "**************************************************SECOND SHORTEST FROM ONE TO ALL *******************************************************" << endl << endl << endl;

	g.secondshortestPathfromOnetoall("Mansehra");

	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "**************************************************SHORTEST PATH FROM ONE TO ALL*******************************************************" << endl << endl << endl;

	g.shortestPathfromOnetoall("Mansehra");

	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "*********************************************SHORTEST ROUTE BETWEEN PAIRS***********************************************" << endl << endl << endl;


	cout<< g.ShortestRoutefrompair("Mansehra", "Islamabad") << endl;

	cout << "========================================================================================================================" << endl << endl << endl;
	cout << "***************************************SECOND SHORTEST PATH BETWEEN PAIRS***********************************************" << endl << endl << endl;


	cout<< g.secondShortestRoutefrompair("Mansehra", "Islamabad")<< endl;

}