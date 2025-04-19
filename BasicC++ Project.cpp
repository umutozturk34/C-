//**************************************************************
//*****         STUDENT NAME: MUSTAFA UMUT ÖZTÜRK          *****
//*****         STUDENT NUMBER: B221202039                 *****
//*****         ASSIGNMENT #: 1                            *****
//**************************************************************
#include<iostream>
#include<iomanip>
using namespace std;
int main() {
    //Declare the variables. a is the beginning of the interval, b is the ending of the interval n is the number of intervals.
    double a, b;
    int n;
    //Now make user enter a,b and n variables.
    cout << "a : "; cin >> a; cout << "b : "; cin >> b; cout << "n : "; cin >> n;
    //Now we declare new variables.
    //Deltax is the width of the x axis side of the rectangle.
    double deltax = (b - a) / n;
    //LHF , RHF and MF are the areas of the rectangles.
    double LHF, RHF, MF;
    //LHFT, RHFT and MFT are the sums of the areas above.
    double LHFT = 0, RHFT = 0, MFT = 0;
    //Now lets make the table step by step
    cout << string(76, '-') << endl;
    cout << setw(10) << "i" << setw(10) << "x[i]" << "     " << "epsilon[i]" << setw(10) << "LHF" << setw(10) << "RHF" << setw(10) << "MF" << endl;
    cout << string(76, '-') << endl;
    //We only need one for loop in order to calculate the areas of the rectangles.
    for (int i = 1; i <= n; i++)
    {
        //We once again declare some variables but this time inside the loop. Because some of the variables are changing by i variable.
        //xi is the beginning of the subinterval. xif is the ending of the subinterval. e is the middle of the subinterval.
        double xi = a + (i - 1) * deltax; double xif = a + (i)*deltax; double e = xi + deltax / 2;
        //Calculate the integrals 
        LHF = (xi * xi * xi + 4 * xi) * deltax; RHF = (xif * xif * xif + 4 * xif) * deltax; MF = (e * e * e + 4 * e) * deltax;
        //Then update the variables
        cout << setw(10) << i << setw(10) << xi << setw(10) << e << setw(15) << LHF << setw(10) << RHF << setw(12)<< MF << endl;
        //Lastly, for every loop sequence sum new data with the previous one and get the total.
        LHFT += LHF; RHFT += RHF; MFT += MF;
        //repeat until i = n
    }
    //Now complete the table and share the sums of the integrals with the user.
    cout << string(40, '-') << endl;
    cout << string(12, '-') << " INTEGRAL RESULTS " << string(10, '-') << endl;
    cout << "f(x) = x^3 + 4x from " << " [" << a << "," << b << "] " << " with " << n << " intervals" << endl;
    cout << string(40, '-') << endl;
    cout << "MIDPOINT RULE          : " << MFT << endl;//Sums of MF
    cout << "LEFT HAND RULE         : " << LHFT << endl;//Sums of LHF
    cout << "RIGHT HAND RULE        : " << RHFT << endl;//Sums of RHF
    cout << string(40, '-') << endl;
    return 0;
}