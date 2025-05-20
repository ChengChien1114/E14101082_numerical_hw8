#include <iostream>
#include <cmath>
#include <iomanip>
#include <functional> // 加入這行

using namespace std;

// 積分上下限
const double a = -1.0, b = 1.0;
const int N = 1000; // 積分切分數（梯形法）

// 被逼近函數
double f(double x) {
    return 0.5 * cos(x) + 0.25 * sin(x);
}

// 修正：泛型函數接收 lambda
double integrate(const function<double(double)>& func, double a, double b) {
    double h = (b - a) / N;
    double sum = 0.5 * (func(a) + func(b));
    for(int i = 1; i < N; i++) {
        sum += func(a + i * h);
    }
    return sum * h;
}

// 單項式基底函數
double phi(int i, double x) {
    if (i == 0) return 1;
    if (i == 1) return x;
    if (i == 2) return x * x;
    return 0;
}

int main() {
    double A[3][3] = {};
    double B[3] = {};

    for(int i = 0; i < 3; ++i){
        for(int j = 0; j < 3; ++j){
            A[i][j] = integrate([=](double x) { return phi(i, x) * phi(j, x); }, a, b);
        }
        B[i] = integrate([=](double x) { return f(x) * phi(i, x); }, a, b);
    }

    // 高斯消去法解三元一次方程式
    for(int i = 0; i < 3; ++i){
        for(int j = i + 1; j < 3; ++j){
            double ratio = A[j][i] / A[i][i];
            for(int k = 0; k < 3; ++k)
                A[j][k] -= ratio * A[i][k];
            B[j] -= ratio * B[i];
        }
    }

    double c = B[2] / A[2][2];
    double b = (B[1] - A[1][2]*c) / A[1][1];
    double a_coef = (B[0] - A[0][2]*c - A[0][1]*b) / A[0][0];

    cout << fixed << setprecision(6);
    cout << "Second-degree Least Squares Approximation on [-1, 1]:" << endl;
    cout << "P(x) = " << a_coef << " + " << b << "*x + " << c << "*x^2" << endl;

    return 0;
}
