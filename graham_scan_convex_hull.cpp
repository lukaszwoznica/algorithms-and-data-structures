#include <iostream>
#include <stack>
#include <cmath>
#include <algorithm>
#include <iomanip>

using namespace std;

struct Point{
    int x, y;
};

Point p0;

int orient(Point p1, Point p2, Point p3) {
    int val = (p2.y - p1.y) * (p3.x - p2.x) - (p2.x - p1.x) * (p3.y - p2.y);

    if (val == 0)
        return 0;
    else if (val > 0)
        return 1;
    else
        return 2;
}

int squareDist(Point p1, Point p2) {
    return pow((p1.x - p2.x), 2) + pow((p1.y - p2.y), 2);
}

struct Compare {
    bool operator()(Point &p1, Point &p2) {
        int o = orient(p0, p1, p2);
        if (o == 0) {
            int square_dist_p1 = squareDist(p0,p1);
            int square_dist_p2 = squareDist(p0,p2);

            if (square_dist_p2 <= square_dist_p1)
                return false;
            else
                return true;
        }
        if (o == 2)
            return true;
        else
            return false;
    }
};

Point secondFromStack(stack<Point> &stack) {
    Point p1, p2;
    p1 = stack.top();
    stack.pop();
    p2 = stack.top();
    stack.push(p1);
    return p2;
}

double grahamAlgorithm(Point *points, int size){
    int min_y = points[0].y;
    int min = 0, m = 1;
    double result = 0;
    Point temp1, temp2, stack_top;
    stack<Point> stack;

    for (int i = 1; i < size; i++) {
        int y = points[i].y;
        if (y < min_y || (min_y == y && points[i].x < points[min].x)) {
            min_y = points[i].y;
            min = i;
        }
    }

    swap(points[0], points[min]);
    p0 = points[0];
    sort(&points[1], &points[size], Compare());

    for (int i = 1; i < size; i++) {
        while (i < size - 1 && orient(p0, points[i], points[i + 1]) == 0)
            i++;
        points[m] = points[i];
        m++;
    }

    stack.push(points[0]);
    stack.push(points[1]);
    stack.push(points[2]);

    for (int i = 3; i < m; i++) {
        while (orient(secondFromStack(stack), stack.top(), points[i]) != 2)
            stack.pop();
        stack.push(points[i]);
    }

    stack_top = stack.top();
    temp1 = stack_top;
    stack.pop();

    while (!stack.empty()) {
        temp2 = stack.top();
        stack.pop();
        result = result + sqrt(squareDist(temp2, temp1));
        temp1 = temp2;
    }
    result = result + sqrt(squareDist(stack_top, temp2));

    return result;
}

int main() {
    std::ios::sync_with_stdio(false);
    int pins_number;
    Point *points;

    cin >> pins_number;
    points = new Point[pins_number];

    for(int i = 0; i < pins_number; i++)
        cin >> points[i].x >> points[i].y;

    cout << fixed << setprecision(2) << grahamAlgorithm(points, pins_number) << endl;

    return 0;
}