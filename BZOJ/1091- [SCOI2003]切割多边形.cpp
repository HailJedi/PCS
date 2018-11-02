#include <bits/stdc++.h>

using namespace std;

const double INF = 1e18;
const int P = 10;
int order[P];

typedef pair<double, double> Point;
typedef Point Vector;
typedef pair<Point, Point> Line;
#define Point(x, y) make_pair(x, y)
#define Line(x, y) make_pair(x, y)
#define x first
#define y second
#define p1 first
#define p2 second

Point pt[P];
int n, m, p;
set<Line> line;

double slope(Line ln) {
	if (ln.p1.x == ln.p2.x) {
		return INF;
	}
	return (ln.p1.y - ln.p2.y) / (ln.p1.x - ln.p2.x);
}

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0); 
	
	cin >> n >> m >> p;
	for (int i = 0; i < p; i++) {
		cin >> pt[i].x >> pt[i].y;
		order[i] = i;
	}
	
	double ans = 1e18;

	while (true) {
		line.clear();
		line.insert(Line(Point(0, 0), Point(n, 0)));
		line.insert(Line(Point(n, 0), Point(n, m)));
		line.insert(Line(Point(n, m), Point(0, m)));
		line.insert(Line(Point(0, m), Point(0, 0)));

		for (int i = 0; i < p; i++) {
			Line cut = Line(pt[i], pt[(i+1)%p]);
			for (set<Line>::iterator it = line.begin(); it != line.end(); ++it) {
				Line edge = *it;
				if (slope(cut) != slope(edge)) {
					Point cr = intersect(cur, edge);
					
				} 
			}
		}

		if (!next_permutation(order+1, order+1+n)) {
			break;
		}
	}
	cout << ans << endl;
	return 0;
}