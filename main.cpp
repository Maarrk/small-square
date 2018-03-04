#include <iostream>
#include <fstream>
#include <cfloat>

using namespace std;

double critForce(double x, double a, double b);

void critParams(double x1, double y1, double x2, double y2, double &a, double &b);

double meanSquare(double *px, double *py, double a, double b, int n);

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

    cout << "i:\tx:\ty:\tf(x):" << endl;
    for (int i = 0; i < pointCount; i++)
    {
        cout << i << ":\t" << px[i] << "\t" << py[i] << "\t" << critForce(px[i], a, b) << endl;
    }

    cout << "a: " << a << endl << "b: " << b << endl << "MSE: " << meanSquare(px, py, a, b, pointCount) << endl << endl;

    char direction = 0, failedCount = 0;
    int stepCount = 300, divideCount = 0, maxDivides = 20;
    double dist = 1, divisor = 2;
    double aNew, bNew;
    double costCurrent = meanSquare(px, py, a, b, pointCount), costNew;

    for (int stepIndex = 0; divideCount < maxDivides; ++stepIndex)
    {
        switch (direction % 4)
        {
            case 0:
            default:
                aNew = a + dist;
                bNew = b;
                break;
            case 1:
                aNew = a;
                bNew = b + dist;
                break;
            case 2:
                aNew = a - dist;
                bNew = b;
                break;
            case 3:
                aNew = a;
                bNew = b - dist;
                break;
        }


        costNew = meanSquare(px, py, aNew, bNew, pointCount);

        cout << stepIndex << ". New cost " << costNew << " in direction " << (int) direction % 4 << endl;

        if (costNew == 0.0)
        {
            cout << "Found max accuracy" << endl;
            break;
        } else if (costNew < costCurrent)
        {
            a = aNew;
            b = bNew;
            costCurrent = costNew;
            failedCount = 0;

            cout << "Going a dist" << endl;
        } else
        {
            failedCount += 1;
            direction += 1;

            if (failedCount >= 4)
            {
                dist /= divisor;
                divideCount += 1;
                cout << "Setting dist to " << dist << endl;
            }
        }
    }

    cout << "Ended" << endl;

//    system("pause");

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

double meanSquare(double *const px, double *const py, double a, double b, int n)
{
    double sum = 0.0;
    double diff;

    for (int i = 0; i < n; ++i)
    {
        diff = critForce(px[i], a, b) - py[i];
        sum += diff * diff;
    }

    return sum;
}
