#include <iostream>
#include "BigRational.h"

using namespace std;

template <class T>
void printMenu(BigRational<T> &a, BigRational<T> &b);

void clearScreen();

int main()
{
    BigRational<int> a;
    BigRational<int> b;

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
            // slow for big numbers because of repeated substractions
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
            cout << "Optiunea not available in the menu.";

        }
        cout << "\nPress ENTER to continue.";
        cin.ignore();
        cin.get();
    } while (choice != 6);

    return 0;
}

template <class T>
void printMenu(BigRational<T> &a, BigRational<T> &b)
{
    cout << "Actual numbers:\nA = " << a << "\nB = " << b << "\n";
    cout << "1) Enter 2 pairs of big numbers \n(for a pair: first = numerator, second = denominator)\n";
    cout << "2) Print sum\n";
    cout << "3) Print product\n";
    cout << "4) Print GCD\n";
    cout << "5) Convert to irreducible fractions\n";
    cout << "6) Exit\n";
    cout << "Enter your option: ";
}

void clearScreen()
{
    for (int i = 1; i <= 100; i++)
        cout << "\n";
}

