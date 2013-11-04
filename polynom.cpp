#include <iostream>
#include <string>
#include <sstream>
#include <cmath>
#include <stdexcept>
using namespace std;
int main(int argc, char **argv) {
    try {
        int k; // 0 – вычисляется сам полином, 1 – его первая производная, 2 – вторая производная
        int n; //порядок полинома
        string s; //e -- even, u -- uneven
        double a,b; //– границы отрезка (при равномерной сетке);
        cin >> k >> n;
        getline(cin,s);
        getline(cin,s);
        double *x = new double[n];
        double *y = new double[n];
        if (s=="e") {
            cin >> a >> b;
        }
        else {
            for (int i=0; i<n; i++) {
                cin >> x[i];
            }
        }
        for (int i=0; i<n; i++) {
            cin >> y[i];
        }
        int m; //количество интервалов в результирующей сетке (т.е. количество узлов – m + 1, что сделано для унификации с узлами исходной сетки);
        cin >> m;
        double *xres = new double[m];
        for (int i=0; i<m; i++) {
            cin >> xres[i];
        }
        string t; //'y' -- expression known, 'n' -- otherwise
        getline(cin,t);
        getline(cin,t);
        string sexpr;
        if (t=="y") {
            getline(cin,sexpr);
            getline(cin,sexpr);
        }
        //cerr << "n " << n << " t " << t << " a " << a << " b " << b << " s " << s << endl;
        delete[] x;
        delete[] y;
        delete[] xres;
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
    }
            
    return 0;
}
