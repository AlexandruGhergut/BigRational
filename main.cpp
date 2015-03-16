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
            // merge greu pentru numere mari datorita scaderilor repetate
            cout << a + b;
            break;
        case 3:
            cout << a * b;
            break;
        case 4:
            cout << "CMMDC a: " << a.getGCD();
            cout << "\nCMMDC b: " << b.getGCD();
            break;
        case 5:
            a.reduce();
            b.reduce();
            break;
        case 6:
            break;
        default:
            cout << "Optiunea nu este prezenta in meniu.";

        }
        cout << "\nApasati ENTER pentru a continua.";
        cin.ignore();
        cin.get();
    } while (choice != 6);

    return 0;
}

void printMenu(BigRational &a, BigRational &b)
{
    cout << "Numerele actuale:\nA = " << a << "\nB = " << b << "\n";
    cout << "1) Introduceti 2 perechi de numere mari (primul element - numaratorul, al doilea - numitorul)\n";
    cout << "2) Afisare suma\n";
    cout << "3) Afisare produs\n";
    cout << "4) Afisare CMMDC\n";
    cout << "5) Transformare in fractii ireductibile\n";
    cout << "6) Iesire\n";
    cout << "Introduceti optiunea: ";
}

void clearScreen()
{
    for (int i = 1; i <= 100; i++)
        cout << "\n";
}
