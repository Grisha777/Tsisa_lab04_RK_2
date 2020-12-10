#include <iostream>
#include <algorithm>

#include "Mutation.cpp"

using namespace std;

int main()
{
    cout <<"Variant 5" << endl;
    cout <<"Function: sin(x) * sin(y) / (1 + x * x + y * y), D: ("<< X_Left_limit << "," << X_Right_limit << ") x (" << Y_Left_limit << "," << Y_Right_limit << ")"<<endl;
    srand(time(nullptr));

    cout << "For 10 Generations: "<<endl;
    Genetic_Algorithm(X_Left_limit, X_Right_limit, Y_Left_limit, Y_Right_limit, Points, 10, Mutation_Probability);
    cout<<endl;

    cout << "For 100 Generations: "<<endl;
    Genetic_Algorithm(X_Left_limit, X_Right_limit, Y_Left_limit, Y_Right_limit, Points,100, Mutation_Probability);

    return 0;
}