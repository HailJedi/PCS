#include <bits/stdc++.h>

using namespace std;

const double PI = acos(-1);
const double INF = 1e9;
const double eps = 1e-7;
const int N = 600+5;
const int M = 4000+5;
typedef pair<double, double> pdd;
typedef pair<int, int> pii;
typedef pdd Point;
typedef Point Vector;
typedef pii HalfEdge;
#define x first
#define y second
map<Point, int> point_id;
map<HalfEdge, int> half_edge_id;
Point troops_pos[N], points[N+M*2];
HalfEdge half_edge[M*2];
int ct, n, m, bie;
double x_1, x_2, y_1, y_2;
vector<int> adj_point[M*2];
vector<int> attack[N];
int tery[M*2];
bool vis[M*2];

double cross(Vector a, Vector b) 
{
	return a.x * b.y - a.y * b.x;
}

double dot(Vector a, Vector b) 
{
	return a.x * b.x + a.y * b.y;
}

double len(Vector a) 
{
	return sqrt(dot(a, a));
}

Vector operator + (Vector a, Vector b) 
{
	return make_pair(a.x + b.x, a.y + b.y);
}

Vector operator - (Vector a, Vector b) 
{
	return make_pair(a.x - b.x, a.y - b.y);
}

Vector operator / (Vector a, double b) 
{
	return make_pair(a.x / b, a.y / b);
}

double p2p(Point &a, Point &b) 
{
	return len(a - b);
}

double p2s(Point &p, Point &a, Point &b) {
	if (dot(a - b, p - b) < 0) 
	{
		return p2p(p, b);
	} else 
	if (dot(b - a, p - a) < 0) 
	{
		return p2p(p, a);
	} else 
	{
		return fabs(cross(a - b, p - b)) / p2p(a, b);
	}
}

bool toright(Vector &a, Vector &b) 
{
	return cross(a, b) > 0;
}

double angle(Vector &a, Vector &b) 
{
	double ret = 0;
	if (toright(b, a)) 
	{
		ret = PI;
		b = b / -1;
	}
	return ret + acos(dot(a, b) / len(a) / len(b));
}

Point intersection(Point &p, Point &a, Point &b) 
{
	if ((p.y - a.y) * (p.y - b.y) > 0) 
	{
		return make_pair(-INF, -INF);
	} 
	if (a.x == b.x) 
	{
		return make_pair(a.x, p.y);
	}
	if (a.y == b.y) 
	{
		return make_pair((a.x + b.x) / 2, p.y);
	}
	return make_pair(a.x + (b.x - a.x) * (a.y - p.y) / (a.y - b.y), p.y);
}

void dfs(int u, int &t) 
{
	vis[u] = true;
	if (points[u].x < points[t].x) 
	{
		t = u;
	}
	for (int i = 0; i < adj_point[u].size(); i++) 
	{
		int v = adj_point[u][i];
		if (!vis[v]) 
		{
			dfs(v, t);
		}
	}
}

void addedge(int u, int v) 
{
	adj_point[u].push_back(v);
	HalfEdge half_edge_0 = make_pair(u, v);
	half_edge[bie] = half_edge_0;
	half_edge_id[half_edge_0] = bie++;
}

int main() 
{
	ios::sync_with_stdio(false);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	for (int i = 1; i <= n; i++) 
	{
		cin >> troops_pos[i].x >> troops_pos[i].y;
		Point p = make_pair(troops_pos[i].x, troops_pos[i].y);
		point_id[p] = ++ct;
		points[ct] = p;
	}
	int ctb = ct+1;
	for (int i = 1; i <= m; i++) 
	{
		cin >> x_1 >> y_1 >> x_2 >> y_2;
		Point p1 = make_pair(x_1, y_1);
		Point p2 = make_pair(x_2, y_2);
		if (!point_id.count(p1)) 
		{
			point_id[p1] = ++ct;
			points[ct] = p1;
		}
		if (!point_id.count(p2)) 
		{
			point_id[p2] = ++ct;
			points[ct] = p2;
		}
		int mp1 = point_id[p1], mp2 = point_id[p2];
		addedge(mp1, mp2);
		addedge(mp2, mp1);
	}
	for (int i = ctb; i <= ct; i++) 
	{
		if (!vis[i]) 
		{
			int t = i;
			dfs(i, t);
			Point left_most = points[t];
			double least_dist = INF;
			int target_edge_id = -1; 
			for (int j = 0; j < bie; j += 2) 
			{
				Point in = intersection(left_most, points[half_edge[j].x], points[half_edge[j].y]);
				if (in.x != -INF && in.x < left_most.x) 
				{
					double dist = p2p(in, left_most);
					if (dist < least_dist && dist != 0) 
					{
						least_dist = dist;
						target_edge_id = j;
					}
				}
			}
			if (target_edge_id != -1) 
			{
				addedge(t, half_edge[target_edge_id].x);
				addedge(half_edge[target_edge_id].x, t);
			}
		} 	
	}
	for (int i = 1; i <= n; i++) 
	{
		double max_dist = INF;
		int start_edge_id = -1;
		Point p = troops_pos[i];
		for (int j = 0; j < bie; j += 2) 
		{
			Point in = intersection(p, points[half_edge[j].x], points[half_edge[j].y]);
			if (in.x != -INF) 
			{
				double dist = p2p(in, p);
				if (dist < max_dist) 
				{
					max_dist = dist;
					start_edge_id = j;
				}
			}
		}
		int x_id = half_edge[start_edge_id].x, y_id = half_edge[start_edge_id].y;
		int start_point_id = p2p(points[x_id], p) < p2p(points[y_id], p) ? x_id : y_id;
		int last_point_id = point_id[p];
		int cur_point_id = start_point_id;
		map<pii, bool> vised;
		int next_point_id;
		do 
		{	
			vised[make_pair(last_point_id, cur_point_id)] = true;
			Point cur_point = points[cur_point_id];
			Point last_point = points[last_point_id];
			Vector previous_vector = last_point - cur_point;
			double sharpest_angle = 100;
			for (int k = 0; k < adj_point[cur_point_id].size(); k++) 
			{
				int candidate_point_id = adj_point[cur_point_id][k];
				if (candidate_point_id != last_point_id) 
				{
					Point candidate_point = points[candidate_point_id];
					Vector candidate_vector = candidate_point - cur_point;
					double their_angle = angle(previous_vector, candidate_vector);
					if (their_angle < sharpest_angle) 
					{
						sharpest_angle = their_angle;
						next_point_id = candidate_point_id;
					}
				}
			}
			last_point_id = cur_point_id;
			tery[half_edge_id[make_pair(cur_point_id, next_point_id)]] = i;
			cur_point_id = next_point_id;
		} while (!vised[make_pair(last_point_id, cur_point_id)]);
	}
	for (int i = 0; i < bie; i++) 
	{
		if (tery[i ^ 1] != 0 && tery[i ^ 1] != tery[i]) {
			attack[tery[i]].push_back(tery[i ^ 1]);
		}
	} 
	for (int i = 1; i <= n; i++) 
	{
		sort(attack[i].begin(), attack[i].end());
		attack[i].resize(unique(attack[i].begin(), attack[i].end()) - attack[i].begin());
		cout << attack[i].size() << ' ';
		for (int j = 0; j < attack[i].size(); j++) 
		{
			cout << attack[i][j] << ' ';
		}
		cout << endl;
	}
	return 0;
}