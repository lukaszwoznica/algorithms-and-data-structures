#include <iostream>
#include <unistd.h>

using namespace std;

const int N = 9999999;

int main() {
    int width, length;
    double x, y, height, avg_height = 0, height_sum = 0, result = 0;
    cin >> width >> length;

    for (int i = 0; i < N; i++) {
        x = ((double)rand() / RAND_MAX) * width;
        y = ((double)rand() / RAND_MAX) * length;
        height = d(x, y);
        if(height > 0)
            height_sum = height_sum + height;
    }

    avg_height = height_sum / N;
    result = avg_height * (width * length);

    cout << (int)result << endl;
    return 0;
}