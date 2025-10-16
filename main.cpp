#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

int row, col;

void swapRows(vector<vector<double>>& matrix, int row1, int row2, int cols) {
    for (int j = 0; j < cols; j++) {
        double temp = matrix[row1][j];
        matrix[row1][j] = matrix[row2][j];
        matrix[row2][j] = temp;
    }
}

void PrintMatrix(const vector<vector<double>>& matrix) {
    cout << "Current matrix:\n";
    for (const auto& r : matrix) {
        for (double val : r) cout << val << "\t";
        cout << endl;
    }
    cout << "----------------------------------------------------\n";
}

string PrintSoultionStatus(const vector<vector<double>>& matrix)
{
    const double EPS=1e-12;
    int n =(int) matrix.size();
    int m =(int) matrix[0].size();
    int mainmatrix=m-1;

    bool flag=0;
    int zeroRows=0;
    for (int i = 0; i < n; i++)
    {
        bool AllZero=true;
        for (int j = 0; j < mainmatrix; j++)
        {
            if (fabs(matrix[i][j]) > EPS) //there is element != 0
            {
                AllZero=false;
                break;
            }
        }
        if ( AllZero)
        {
            if (fabs(matrix[i][m-1])>EPS)
            {
                flag = true;
            }
            else
            {
                zeroRows++;
            }
        }
    }
    if (flag)
    {
      //  cout<<"NO SOLUTION \n";
        return "NO_SOLUTION"  ;
    }

    if (zeroRows > 0)
    {
       // cout << "Infinite solutions\n";
        return "INFINITE";
    }

   return "UNIQUE";

}
int main() {
    cout << "==================================\n";
    cout << "    Gaussian Elimination    \n";
    cout << "===================================\n";

    cout << "Enter the number of rows: ";
    if (!(cin>> row))
    {
        cout << "Invalid input.\n";
        return 1;
    }
    cout << "Enter the number of coloums: ";
    if (!(cin>> col))
    {
        cout << "Invalid input.\n";
        return 1;
    }

    if (row <= 0 || col <= 0)
    { cout << "Rows and cols must be positive\n";
        return 1;
    }


    if (col != row + 1) {
        cout << "[!] Expect augmented matrix: columns must equal rows+1\n";
        return 1;
    }

    vector<vector<double>> matrix(row, vector<double>(col));

    cout << "Enter the matrix elements \n";
    for (int i = 0; i < row; i++) {
        cout<<"Enter row "<<i+1<<": ";
        for (int j = 0; j < col; j++) {
            if (!(cin >> matrix[i][j])) { cout << "Invalid matrix element\n"; return 1; }
        }
    }

    PrintMatrix(matrix);

    const double EPS = 1e-12; //.0000000000001

    for (int lead = 0; lead < row; lead++)
    {
        if (lead >= row || lead >= col)
            break;


        // if lead=0 we should swap wit row != 0
        bool swapped=false;
        if (fabs(matrix[lead][lead]) < EPS)
        {
            for (int i = lead+1; i < row; i++)
            {
                if (fabs(matrix[i][lead]) > EPS)
                {
                    swapRows(matrix, lead, i, col);
                    cout<<"Swapped row "<< lead << "with "<<i<<"\n";
                    PrintMatrix(matrix);
                    swapped=true;
                    break;
                }
            }

            if (!swapped) {
                cout << "Pivot at column " << lead << " is zero and no swap possible, skipping\n";
                continue;
            }
        }

        // make leading = 1
        double divisor = matrix[lead][lead];
        if (fabs(divisor) > EPS && fabs(divisor - 1) > EPS )
        {
            cout << "Dividing row " << lead << " by " << divisor << "\n";
            for (int j = 0; j < col; j++)
            {
                matrix[lead][j] /= divisor;
            }
            PrintMatrix(matrix);
        }

        //  convert rest elements in the coloum = 0
        for (int i = 0; i < row; i++)
        {
            if (i == lead) continue;
            if (fabs(matrix[i][lead]) < EPS) continue;
            if (fabs(matrix[lead][lead] -1) < EPS) //lead=1
            {
                double x= -matrix[i][lead];
                cout << "Eliminate row " << i << " using row " << lead << " with multiplier " << x << "\n";
                for (int j = 0; j < col; j++)
                {
                    matrix[i][j] = matrix[i][j] + matrix[lead][j] * x;
                }
                PrintMatrix(matrix);

            }
            else //lead != 1
            {
                double y = matrix[i][lead]/matrix[lead][lead];
                cout << "Eliminate row " << i << " using row " << lead << " with factor " << y << "\n";

                for (int j = 0; j < col; j++)
                {
                    matrix[i][j] = matrix[i][j] - matrix[lead][j] * y;
                }
                PrintMatrix(matrix);
            }
        }
    }


    cout << "\n==================================\n";
    cout << "        Gauss Complete!              \n";
    cout << "==================================\n";
    PrintMatrix(matrix);


    string status= PrintSoultionStatus(matrix);

    cout << "\n==================================\n";
    cout << "           SOLUTION               \n";
    cout << "==================================\n";
    if (status == "UNIQUE")
    for (int i = 0; i < row; i++) {
        cout << "x[" << i + 1 << "] = " << matrix[i][col - 1] << "\n";
    }
    else if (status=="INFINITE")
    {
        cout << "Infinity solution\n";
    }
    else
    {
        cout<<"No solution\n";
    }
    cout << "=======================================\n";

    return 0;
}
