#include <iostream>
#include "BigRational.h"

using namespace std;

void printMenu(BigRational &a, BigRational &b);
void clearScreen();

int main()
{
    BigRational a, b;
    int choice;
    do
    {
        clearScreen();
        printMenu(a, b);
        cin >> choice;

        switch (choice)
        {
        case 1:
            cin >> a >> b;
            break;
        case 2:
            cout << a + b;
            break;
        case 3:
            //cout << a - b;
            break;
        case 4:
            cout << a * b;
            break;
        case 5:
            cout << "CMMDC a: " << a.getGCD();
            cout << "\nCMMDC b: " << b.getGCD();
            break;
        case 6:
            a.reduce();
            b.reduce();
            break;
        case 7:
            break;

        }
        cout << "\nApasati ENTER pentru a continua.";
        cin.ignore();
        cin.get();
    } while (choice != 7);
    return 0;
}

void printMenu(BigRational &a, BigRational &b)
{
    cout << "Numerele actuale:\nA = " << a << "\nB = " << b << "\n";
    cout << "1) Introduceti 2 perechi de numere mari (primul element - numaratorul, al doilea - numitorul)\n";
    cout << "2) Afisare suma\n";
    cout << "3) Afisare diferenta\n";
    cout << "4) Afisare produs\n";
    cout << "5) Afisare CMMDC\n";
    cout << "6) Transformare in fractii ireductibile\n";
    cout << "7) Iesire\n";
    cout << "Introduceti optiunea: ";
}

void clearScreen()
{
    for (int i = 1; i <= 100; i++)
        cout << "\n";
}
