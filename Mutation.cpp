#include <iostream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

const double X_Left_limit = 0;
const double X_Right_limit = 2;
const double Y_Left_limit = -2;
const double Y_Right_limit = 2;
const int Points = 6;
const double Mutation_Probability = 0.2;


double Function(const double x, const double y)
{
    return (sin(x) * sin(y))/(1+x * x+y * y);
}

struct Coordinate{
    double X;
    double Y;
};

double Random(const double left, const double right)
{
    return left + rand() * 1./RAND_MAX * (right - left);
}


bool operator <(const Coordinate& lhs, const Coordinate& rhs)
{
    return Function(lhs.X, lhs.Y) < Function(rhs.X, rhs.Y);
}

Coordinate Random_Coordinate(const double X_Left_Limit, const double X_Right_Limit, const double Y_Left_Limit, const double Y_Right_Limit)
{
    return {Random(X_Left_Limit, X_Right_Limit), Random(Y_Left_Limit, Y_Right_Limit)};
}

using Population = vector<Coordinate>;

void Print1()
{
    cout << '+' << string(5, '-') << '+' << string(12, '-')
         << '+' << string(12, '-') << '+' << string(12, '-')
         << '+' << string(12, '-') << '+' << string(12, '-')<< '+' << endl;
}

void Print2()
{
    Print1();
    cout << '|' << "  N  " << '|' << "     X      "
         << '|' << "     Y      " << '|' << "    FIT     "
         << '|' << "    Max     " << '|' << "   Middle   "<< '|' << endl;
    Print1();
}

void Print3(const int Generation, const Population& Population)
{
    for (size_t i = 0; i < Population.size(); ++i)
    {
        if (i == 0)
        {
            cout << '|' << setw(4) << Generation << " | ";
        } else {
            cout << '|' << setw(7) << " | ";
        }
        cout << setw(10) << Population[i].X << " | "<< setw(10) << Population[i].Y << " | "
             << setw(10) << Function(Population[i].X, Population[i].Y) << " | ";

        if (i == 0)
        {
            double max = Function(Population[0].X, Population[0].Y), Average = 0;
            for (auto i : Population)
            {
                if (Function(i.X, i.Y) > max) max = Function(i.X, i.Y);
                Average =  Average + Function(i.X, i.Y);
            }
            Average = Average / Population.size();
            cout << setw(10) << max << " | "<< setw(10) << Average <<" | "<<endl;
        } else {
            cout << setw(12) << '|' << setw(14) <<"|"<<endl;
        }
    }
    Print1();
}

void Genetic_Algorithm(const double X_Left, const double X_Right,const double Y_Left, const double Y_Right,
                       const int coordinate, const int Generations_coordinate,const double mutation_probability)
{
    Population Inital_Population;

    for (size_t i = 0; i < coordinate; ++i)
    {
        Inital_Population.push_back(Random_Coordinate(X_Left, X_Right, Y_Left, Y_Right));
    }

    sort(Inital_Population.rbegin(), Inital_Population.rend());

    const double e = 0.5;

    Print2();
    for(int i = 1; i <= Generations_coordinate; ++i)
    {
        Print3(i - 1, Inital_Population);

        Population New_Population;
        New_Population.push_back(Coordinate{Inital_Population[0].X, Inital_Population[1].Y});
        New_Population.push_back(Coordinate{Inital_Population[1].X, Inital_Population[0].Y});
        New_Population.push_back(Coordinate{Inital_Population[0].X, Inital_Population[2].Y});
        New_Population.push_back(Coordinate{Inital_Population[2].X, Inital_Population[0].Y});
        New_Population.push_back(Coordinate{Inital_Population[0].X, Inital_Population[3].Y});
        New_Population.push_back(Coordinate{Inital_Population[3].X, Inital_Population[0].Y});


        for (size_t k = 0; k < coordinate; ++k)
        {
            double probability = Random(0., 1.);
            if (probability < mutation_probability) {
                double d_X = Random(-e/2, e/2);
                double d_Y = Random(-e/2, e/2);
                New_Population[k].X += d_X;
                if (New_Population[k].X < X_Left)  New_Population[k].X = X_Left;
                if (New_Population[k].X > X_Right) New_Population[k].X = X_Right;
                New_Population[k].Y += d_Y;
                if (New_Population[k].Y < Y_Left)  New_Population[k].Y = Y_Left;
                if (New_Population[k].Y > Y_Right) New_Population[k].Y = Y_Right;
            }
        }

        sort(New_Population.rbegin(), New_Population.rend());
        Inital_Population = New_Population;
    }
    Print3(Generations_coordinate, Inital_Population);
}
