#include <bits/stdc++.h>

using namespace std;

#define db double
const int N = 50;

const db eps = 1e-10;

int dcmp(db x) {
    if (fabs(x) < eps) return 0;
    else return x < 0 ? -1 : 1;
}

int n, c, m;

struct Point {
    db x, y;
    Point() {}
    Point(db x, db y) : x(x), y(y) {}
    void read() {
        cin >> x >> y;
    }
    Point operator + (const Point &p) const {
        return Point(x + p.x, y + p.y);
    }
    Point operator / (const db div) const {
        return Point(x / div, y / div);
    }
    Point operator * (const db div) const {
        return Point(x * div, y * div);
    }
    Point operator - (const Point &p) const {
        return Point(x - p.x, y - p.y);
    }
    bool operator == (const Point &p) const {
        return dcmp(x - p.x) == 0 && dcmp(y - p.y) == 0;
    }
};

typedef pair<Point, Point> Segment;
typedef Point Vector;

db Dot(Vector A, Vector B) {
    return A.x * B.x + A.y * B.y;
}

db Length(Vector A) {
    return sqrt(Dot(A, A));
}

db Cross(Vector A, Vector B) {
    return A.x * B.y - A.y * B.x;
}

db DistanceToLine(Point P, Point A, Point B) {
    Vector v1 = B-A, v2 = P-A;
    return fabs(Cross(v1, v2)) / Length(v1);
}

db DistanceToSegment(Point P, Point A, Point B) {
    if (A == B) return Length(P-A);
    Vector v1 = B-A, v2 = P-A, v3 = P-B;
    if (dcmp(Dot(v1, v2)) < 0) return Length(v2);
    else if (dcmp(Dot(v1, v3)) > 0) return Length(v3);
    else return DistanceToLine(P, A, B);
}

Point GetLineProjection(Point P, Point A, Point B) {
    Vector v = B-A;
    return A+v*(Dot(v, P-A) / Dot(v, v));
}

bool isPointOnSegment(Point P, Point A1, Point A2) {
    return dcmp(Cross(A1-P, A2-P)) == 0 && dcmp(Dot(A1-P, A2-P)) < 0;
}

struct Land {
    Point corner[N];
    int sz;
    bool In(Point &p) {
        int wn = 0;
        for (int i = 0; i < sz; i++) {
            if (isPointOnSegment(p, corner[i], corner[(i + 1) % sz])) {
                return true;
            }
            int k = dcmp(Cross(corner[(i + 1) % sz] - corner[i], p - corner[i]));
            int d1 = dcmp(corner[i].y - p.y);
            int d2 = dcmp(corner[(i + 1) % sz].y - p.y);
            if (k > 0 && d1 <= 0 && d2 > 0) {
                wn++;
            }
            if (k < 0 && d2 <= 0 && d1 > 0) {
                wn--;
            }
        }
        if (!wn) {
            return false; // out
        } else {
            return true; // in
        }
    }
} land[N];

struct Route {
    Point turn[N];
} route; 

db ans = 0;

Point closestPoint(Point &p) {
    db opt = 1e9;
    Point ret;
    for (int i = 0; i < c; i++) {
        if (land[i].In(p)) {
            ret = p;
            break;
        } else {
            for (int j = 0; j < land[i].sz; j++) {
                Point &p1 = land[i].corner[j], &p2 = land[i].corner[(j + 1) % land[i].sz];
                db dis = DistanceToSegment(p, p1, p2);
                if (dcmp(dis - Length(p - p1)) == 0) {
                    if (dcmp(dis - opt) < 0) {
                        opt = dis;
                        ret = p1;
                    }
                } else 
                if (dcmp(dis - Length(p - p2)) == 0) {
                    if (dcmp(dis - opt) < 0) {
                        opt = dis;
                        ret = p2;
                    }
                } else {
                    Point p3 = GetLineProjection(p, p1, p2);
                    if (dcmp(dis - opt) < 0) {
                        opt = dis;
                        ret = p3;
                    }
                }
            }
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> c >> n;
    for (int i = 0; i < n; i++) {
        route.turn[i].read();
    }
    for (int i = 0; i < c; i++) {
        cin >> m;
        land[i].sz = m;
        for (int j = 0; j < m; j++) {
            land[i].corner[j].read();
        }
    }
    queue<Segment> q;
    for (int i = 0; i < n-1; i++) {
        q.push(make_pair(route.turn[i], route.turn[i+1]));
    }
    while (!q.empty()) {
        Segment seg = q.front(); q.pop();
        Point end1 = seg.first, end2 = seg.second;
        Point p1 = closestPoint(end1), p2 = closestPoint(end2);
        int cnt = 0;
        while (++cnt <= 30) {
            Point mid = (end1 + end2) / 2.0;
            if (dcmp(Length(mid - p1) - Length(mid - p2)) > 0) {
                end2 = mid;
            } else {
                end1 = mid;
            }
        }
        if (dcmp(max(Length(end1 - p1), Length(end2 - p2)) - ans - 0.00005) > 0) {
            Point mid = (seg.first + seg.second) / 2.0;
            q.push(make_pair(seg.first, mid));
            q.push(make_pair(mid, seg.second));
            ans = max(ans, Length(mid - closestPoint(mid)));
        }
    }
    cout << fixed << setprecision(2) << ans << endl;
    return 0;
}