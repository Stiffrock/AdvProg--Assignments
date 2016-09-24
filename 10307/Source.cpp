#include <iostream>
#include <string>
#include <vector>
#include <queue>

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
};

vector<edge> edges;

void bfs(point startp, point endp)
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
		bfs(startp, endp[0]);
		edges;
		dist;
	}
	cin.get();
	return 0;
}