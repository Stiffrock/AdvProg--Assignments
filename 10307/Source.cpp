#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

char A[50][50];
int dist[50][50];
bool visited[50][50];

int c, n, m;


struct point
{
	int x, y;
};

struct edge
{
	point u, v;
	int d;

	bool operator < (const edge& e1) const
	{
		return d < e1.d;
	}
};

vector<edge> edges;

void bfs(point startp, vector<point> endp) // point endp)
{
	for (int i = 0; i < 50; i++)
		for (int j = 0; j < 50; j++)
		{
			visited[i][j] = false;
			dist[i][j] = INT_MAX;
		}

	queue<point> q;
	q.push(startp);
	visited[startp.x][startp.y] = true;
	dist[startp.x][startp.y] = 0;

	while (!q.empty())
	{
		point u = q.front();
		visited[u.x][u.y] = true;
		point v;
		edge e;
		q.pop();

	/*	if (u.x == endp.x && u.y == endp.y)
		{
			return;
		}*/
		
		if (u.x >= 0 && u.x < n && A[u.x + 1][u.y] != '#'&& A[u.x + 1][u.y] != '\0' && visited[u.x +1][u.y] == false)
		{
			v.x = u.x + 1; v.y = u.y;	
			e.d = dist[u.x + 1][u.y] = dist[u.x][u.y] + 1;
			e.u = u; e.v = v;
			edges.push_back(e);
			q.push(v);
		}

		if (u.y >= 0 && u.y < m && A[u.x][u.y + 1] != '#' && A[u.x][u.y + 1] != '\0' && visited[u.x][u.y + 1] == false)
		{
			v.x = u.x; v.y = u.y + 1;
			e.d = dist[u.x][u.y + 1] = dist[u.x][u.y] + 1;
			e.u = u; e.v = v;
			edges.push_back(e);
			q.push(v);
		}

		if (u.x > 0 && u.x <= n && A[u.x - 1][u.y] != '#' && A[u.x - 1][u.y] != '\0' && visited[u.x - 1][u.y] == false)
		{
			v.x = u.x - 1; v.y = u.y;
			e.d = dist[u.x - 1][u.y] = dist[u.x][u.y] + 1;
			e.u = u; e.v = v;
			edges.push_back(e);
			q.push(v);
		}

		if (u.y > 0 && u.y <= n && A[u.x][u.y - 1] != '#' && A[u.x][u.y - 1] != '\0' && visited[u.x][u.y - 1] == false)
		{
			v.x = u.x; v.y = u.y - 1;
			e.d = dist[u.x][u.y - 1] = dist[u.x][u.y] + 1;
			e.u = u; e.v = v;
			edges.push_back(e);
			q.push(v);
		}		
	}
}


struct DisjointSets
{
	int *parent, *rank;
	int n;

	DisjointSets(int n)
	{
		this->n = n;
		parent = new int[n + 1];
		rank = new int[n + 1];

		for (int i = 0; i < n; i++) //samma som untion find init
		{
			rank[i] = 0;
			parent[i] = i;
		}
	}

	int find(int u)
	{
		if (u != parent[u])
			parent[u] = find(parent[u]);
		return parent[u];	
	}

	void merge(int x, int y)
	{
		x = find(x), y = find(y);

		if (rank[x] > rank[y])
			parent[y] = x;
		else
			parent[x] = y;
		if (rank[x] == rank[y])
			rank[y]++;
	}
};


int Kruskal()
{
	int mst_weight = 0;
	sort(edges.begin(), edges.end());
	vector<edge> MST;

	DisjointSets ds(edges.size());

	for (int i = 0; i < edges.size(); i++)
	{
		int u = edges[i].u.x;
		int v = edges[i].u.y;
		int set_u = ds.find(u);
		int set_v = ds.find(v);


		//Check if edge is creating a cycle or not.
		//Cycle is created if u and v belong to same set.
		if (set_u != set_v)
		{
			mst_weight += i;
		}
		ds.merge(set_u, set_v);
	}
	return mst_weight;
}

int main()
{
	cin >> c;
	while (c--)
	{
		cin >> n >> m;
		vector<point> endp;
		point startp;
		string input;
		cin.get();
		for (int i = 0; i < n; i++)
		{
			getline(cin, input);
			for (int j = 0; j < m; j++)
			{
				A[i][j] = input[j];
				if (input[j] == 'S')
					startp.x = i; startp.y = j;
				if (input[j] == 'A')
				{
					point p;
					p.x = i; p.y = j;
					endp.push_back(p);
				}
			}
		}
		/*for (int i = 0; i < endp.size(); i++)
			bfs(startp, endp[i]);*/

		bfs(startp, endp); // Du ska använda endp och göra en union find ner till startp, för alla aliens. Efter sortering..
		edges;
		int ans = Kruskal();
		cout << ans;
	}
	cin.get();
	return 0;
}