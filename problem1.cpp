#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

const int n = 8;
double x[n] = {4.0, 4.2, 4.5, 4.7, 5.1, 5.5, 5.9, 6.3};
double y[n] = {102.6, 113.2, 130.1, 142.1, 167.5, 195.1, 224.9, 256.8};

// (a) 二次多項式 y = ax^2 + bx + c
void quadraticFit() {
    double Sx=0, Sx2=0, Sx3=0, Sx4=0;
    double Sy=0, Sxy=0, Sx2y=0;
    
    for(int i = 0; i < n; ++i){
        Sx   += x[i];
        Sx2  += x[i]*x[i];
        Sx3  += x[i]*x[i]*x[i];
        Sx4  += pow(x[i],4);
        Sy   += y[i];
        Sxy  += x[i]*y[i];
        Sx2y += x[i]*x[i]*y[i];
    }

    double A[3][4] = {
        {Sx4, Sx3, Sx2, Sx2y},
        {Sx3, Sx2, Sx,  Sxy},
        {Sx2, Sx,  n,   Sy}
    };

    // 高斯消去法解三元一次方程式
    for(int i = 0; i < 3; i++) {
        for(int j = i+1; j < 3; j++) {
            double ratio = A[j][i]/A[i][i];
            for(int k = 0; k < 4; k++) {
                A[j][k] -= ratio * A[i][k];
            }
        }
    }

    double c = A[2][3]/A[2][2];
    double b = (A[1][3] - A[1][2]*c)/A[1][1];
    double a = (A[0][3] - A[0][2]*c - A[0][1]*b)/A[0][0];

    cout << fixed << setprecision(6);
    cout << "(a) Quadratic Fit: y = " << a << "x^2 + " << b << "x + " << c << endl;

    double error = 0;
    for(int i = 0; i < n; i++){
        double yi = a*x[i]*x[i] + b*x[i] + c;
        error += pow(y[i] - yi, 2);
    }
    cout << "    Error: " << error << endl;
}

// (b) 指數型 y = b * e^(a * x)
void exponentialFit() {
    double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
    for(int i = 0; i < n; i++){
        double Y = log(y[i]);
        Sx += x[i];
        Sy += Y;
        Sxx += x[i]*x[i];
        Sxy += x[i]*Y;
    }

    double a = (n*Sxy - Sx*Sy) / (n*Sxx - Sx*Sx);
    double A = (Sy - a*Sx) / n;
    double b = exp(A);

    cout << "(b) Exponential Fit: y = " << b << " * e^(" << a << "x)" << endl;

    double error = 0;
    for(int i = 0; i < n; i++){
        double yi = b * exp(a * x[i]);
        error += pow(y[i] - yi, 2);
    }
    cout << "    Error: " << error << endl;
}

// (c) 冪次型 y = b * x^a
void powerFit() {
    double Sx = 0, Sy = 0, Sxx = 0, Sxy = 0;
    for(int i = 0; i < n; i++){
        double X = log(x[i]);
        double Y = log(y[i]);
        Sx += X;
        Sy += Y;
        Sxx += X*X;
        Sxy += X*Y;
    }

    double a = (n*Sxy - Sx*Sy) / (n*Sxx - Sx*Sx);
    double A = (Sy - a*Sx) / n;
    double b = exp(A);

    cout << "(c) Power Fit: y = " << b << " * x^" << a << endl;

    double error = 0;
    for(int i = 0; i < n; i++){
        double yi = b * pow(x[i], a);
        error += pow(y[i] - yi, 2);
    }
    cout << "    Error: " << error << endl;
}

int main() {
    quadraticFit();
    exponentialFit();
    powerFit();
    return 0;
}
