#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

double f(double x) {
    return x * x * sin(x);
}

double computeRealIntegral() {
    return cos(1) + 2 * sin(1) - 2;
}

int main() {
    const int m = 16;
    const int S = 4;
    const double c = 0.0;
    const double d = 1.0;
    const int n = 2 * m;
    double step = (d - c) / (n - 1);

    vector<double> x(n), z(n);
    for (int i = 0; i < n; ++i) {
        x[i] = c + i * step;
        z[i] = M_PI * (2 * (x[i] - c) / (d - c) - 1);
    }

    vector<double> a(S + 1, 0.0), b(S + 1, 0.0);

    for (int k = 0; k <= S; ++k) {
        for (int j = 0; j < n; ++j) {
            a[k] += f(x[j]) * cos(k * z[j]) / m;
            b[k] += f(x[j]) * sin(k * z[j]) / m;
        }
    }

    auto S4 = [&](double z_val) {
        double sum = 0.5 * a[0];
        for (int k = 1; k <= S; ++k) {
            sum += a[k] * cos(k * z_val) + b[k] * sin(k * z_val);
        }
        return sum;
    };

    // Output (a)
    cout << fixed << setprecision(4);
    cout << "(a)\n";
    cout << "a0 = " << a[0] << endl;
    for (int i = 1; i <= S; ++i) {
        cout << "a" << i << " = " << a[i] << " , b" << i << " = " << b[i] << endl;
    }

    // Output (b)
    double integralS4 = 0.0;
    for (int i = 0; i < n - 1; ++i) {
        integralS4 += S4(z[i]) / (n - 1);
    }
    cout << "\n(b)\nAns: " << integralS4 << endl;

    // Output (c)
    double realIntegral = computeRealIntegral();
    double absErr = fabs(realIntegral - integralS4);
    double relErr = absErr / fabs(realIntegral) * 100;
    cout << "\n(c)\nAbsolute: " << absErr << " , Relative: " << relErr << "%" << endl;

    // Output (d)
    double E = 0.0;
    for (int i = 0; i < n; ++i) {
        E += pow(f(x[i]) - S4(z[i]), 2);
    }
    cout << "\n(d)\nError: " << E << endl;

    return 0;
}
