#include <iostream>
#include <string>
#include <sstream>
#include <string.h>
#include <cmath>
#include <stdexcept>
using namespace std;
int main(int argc, char **argv) {
        int type;
        int n;
        double **matrix;
        double **b;
        cin >>type >> n;
        matrix=new double*[n];
        double eps=1e-6;
        cout.precision(-log10(eps));
        cout << "matrix input:\n";
        for(int i=0;i<n;i++)
        {
                matrix[i]= new double[n];
                for(int j=0;j<n;j++) {
                        cin >> matrix[i][j];
                        cout << matrix[i][j] << ' ';
                }
                cout << endl;
        }
        double epsf=0;
        double *epsv = new double[n];
        try {
            double **result;
            double **P;
            double **s;
            if(type==1) {
               P=findP(n,matrix,&s);
               findLa(n,P,eps,matrix,s);
               
            }
            for (int i=0; i<n; i++) {
                delete[] matrix[i];
                delete[] s[i];
                delete[] P[i];
            }
            delete[] matrix;
            delete[] P;
            delete[] s;
        }
        catch (invalid_argument &e) {
            cerr << e.what() << endl;
        }
                
        return 0;
}
