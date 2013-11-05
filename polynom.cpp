#include <iostream>
#include <string>
#include <cmath>
#include <stdexcept>
#include <vector>
using namespace std;
void solveUneven(double *x, double *y, int n, int, double*);
double eval(double *result, int n, double xres);
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
        double *result = new double[n];
        if (s=="u") {
            solveUneven(x,y,n,k,result);
        }
        for (int i=0; i<m; i++) {
            cout << "x" << i << " P'(" << k << ")(x" << i << ") = " << eval(result,n,xres[i]) << endl;
        }
        delete[] result;
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
        for (int i=0; i<n; i++) {
            if (aUsing[i]) {
                sum -= x[i];
            }
        }
        delete[] aUsing;
        return sum;
    }
    else {
        int iusing = 0;
        double sum = 0;
        int count = 0;
        int inum = n-indexes.size();
        for (int i=0; i<inum; i++) {
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

void solveUneven(double *x, double *y, int n, int iDer, double *l) {
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
        if (iDer==0) {
            for (int k=0; k<n; k++) {
                l[k] += mult*findMultValue(x,n,indexes,k);
            }
        }
        else if (iDer==1) {
            int il = 0;
            for (int j=0; j<n; j++) {
                indexes.push_back(j);
                for (int k=0; k<n; k++) {
                    if (k!=j) {
                        l[il+iDer] += mult*findMultValue(x,n,indexes,il);
                        ++il;
                    }
                }
                indexes.pop_back();
            }
        }
        else if (iDer==2) {
            int il = 0;
            for (int i=0; i<n; i++) {
                indexes.push_back(i);
                for (int j=0; j<n; j++) {
                    if (i==j) continue;
                    indexes.push_back(j);
                    for (int k=0; k<n; k++) {
                        if (k!=j && k!=i) {
                            l[il+iDer] += mult*findMultValue(x,n,indexes,il);
                            ++il;
                        }
                    }
                    indexes.pop_back();
                }
                indexes.pop_back();
            }
        }
    }
    for (int i=0; i<n; i++) {
        cout << l[i] <<' ';
    }
    cout << endl;
}

double eval(double *result, int n, double xres) {
    double sum = 0;
    for (int i=0; i<n; i++) {
        sum += result[i]*pow(xres,n-1-i);
    }
    return sum;
}
