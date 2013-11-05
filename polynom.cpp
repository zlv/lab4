#include <iostream>
#include <string>
//#include <sstream>
//#include <cmath>
#include <stdexcept>
#include <vector>
using namespace std;
void solveUneven(double *x, double *y, int n);
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
        if (s=="u") {
            solveUneven(x,y,n);
        }
        delete[] x;
        delete[] y;
        delete[] xres;
    }
    catch (invalid_argument &e) {
        cerr << e.what() << endl;
    }
            
    return 0;
}

double findMultValue(double *x, int n, vector<int> &indexes, int k) {
    if (k==0) {
        return 1;
    }
    bool *aUsing = new bool[n];
    for (int i=0; i<n; i++) {
        aUsing[i] = 1;
    }
    for (vector<int>::iterator iter=indexes.begin(); iter!=indexes.end(); ++iter) {
        aUsing[*iter] = 0;
    }
    if (k==1) {
        double sum = 0;
        cerr << "sum : ";
        for (int i=0; i<n; i++) {
            if (aUsing[i]) {
                cerr << x[i] << ' ';
                sum -= x[i];
            }
        }
        cerr << endl;
        delete[] aUsing;
        return sum;
    }
    else {
        int iusing = 0;
        double sum = 0;
        int count = 0;
        for (int i=0; i<n-indexes.size(); i++) {
            while (!aUsing[iusing]) ++iusing;
            indexes.push_back(iusing);
            sum -= x[iusing]*findMultValue(x,n,indexes,k-1);
            ++iusing;
            ++count;
        }
        indexes.erase(indexes.end()-count,indexes.end());
        return sum;
    }
}

void solveUneven(double *x, double *y, int n) {
    double *l = new double[n];
    for (int k=0; k<n; k++) {
        l[k] = 0;
    }
    for (int i=0; i<n; i++) {
        double denom = 1;
        for (int j=0; j<n; j++) {
            if (i!=j) {
                denom *= x[i]-x[j];
            }
        }
        double mult = y[i]/denom;
        vector<int> indexes; //исключаемые индексы
        indexes.push_back(i);
        cerr << i << "mult : " << mult << " denom: " << denom << endl;
        for (int k=0; k<n; k++) {
            l[k] += mult*findMultValue(x,n,indexes,k);
            cerr << "l " << k << " " << l[k] << endl;
        }
    }
    for (int i=0; i<n; i++) {
        cout << l[i] <<' ';
    }
    cout << endl;
    delete[] l;
}
