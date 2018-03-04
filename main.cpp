#include <iostream>
#include <fstream>
#include <cfloat>

using namespace std;

double critForce(double x, double a, double b);

void critParams(double x1, double y1, double x2, double y2, double &a, double &b);

int main()
{
    string filenameIn = "input.txt";

    ifstream fin;
    fin.open(filenameIn, ifstream::in);

    if (!fin.is_open())
    {
        cout << "Could not open \"" + filenameIn + "\"" << endl;
        system("pause");
        return 0;
    }

    int pointCount;
    fin >> pointCount;

    auto *px = (double *) malloc(pointCount * sizeof(double)); ///< points X coordinate
    auto *py = (double *) malloc(pointCount * sizeof(double)); ///< points Y coordinate

    for (int i = 0; i < pointCount; i++)
    {
        fin >> px[i] >> py[i];
    }

    // Find average function params

    double a, b;
    double aSum = 0.0, bSum = 0.0;

    for (int i = 0; i < pointCount; i++)
    {
        for (int j = 0; j < i; j++)
        {
            critParams(px[i], py[i], px[j], py[j], a, b);
            aSum += a;
            bSum += b;
        }
    }

    a = aSum / pointCount;
    b = bSum / pointCount;

    auto f = [a, b](double x) { return critForce(x, a, b); }; // Final function

    cout << "i:\tx:\ty:\tf(x):" << endl;
    for (int i = 0; i < pointCount; i++)
    {
        cout << i << ":\t" << px[i] << "\t" << py[i] << "\t" << f(px[i]) << endl;
    }

    system("pause");

    free(py);
    free(px);

    return 0;
}

/// Hyperbolic function with asymptotes: y=0; x=b
double critForce(double x, double a, double b)
{
    if (x == b) return DBL_MAX; // Prevent 0 division, make cost function high

    return a / (x - b);
}

/// Returns parameters for critForce given two points
void critParams(double x1, double y1, double x2, double y2, double &a, double &b)
{
    a = (y1 * y2 * (x2 - x1)) / (y1 - y2);
    b = (y1 * x1 - y2 * x2) / (y1 - y2);
}
