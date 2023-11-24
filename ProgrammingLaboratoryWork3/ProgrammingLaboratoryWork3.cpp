#include <ctime>
#include <iostream>
#include <Windows.h>
using namespace std;

const int sizeArray = 6;

void showArray(int(*A)[sizeArray]) {
    system("cls");
    HANDLE hStdout;
    COORD destCoord;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int i = 0; i < sizeArray; i++)
        for (int j = 0; j < sizeArray; j++)
        {
            destCoord.X = i * 4;
            destCoord.Y = j;
            SetConsoleCursorPosition(hStdout, destCoord);
            cout << A[i][j];
        }
    cout << "\n";
}

void fillSnake(int(*A)[sizeArray]) {
    for (int i = 0; i < sizeArray; i++)
        for (int j = 0; j < sizeArray; j++) {
            A[i][j] = 0;
        }

    showArray(A);

    int* end = A[0] + sizeArray * sizeArray - 1;

    HANDLE hStdout;
    COORD destCoord;
    hStdout = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int* pt = A[0], i = 0, x = 0, y = 0; pt <= end + (sizeArray - 1); pt++, i++, y++) {
        if (i % sizeArray == 0 && i != 0) {
            x++;
            y = 0;
            if (x % 2 == 0)
                pt = &A[x][y];
            else
                pt = &A[x][y + sizeArray - 1];
        }
        if (x % 2 == 0) {
            destCoord.X = x * 4;
            destCoord.Y = y;
            SetConsoleCursorPosition(hStdout, destCoord);
            *pt = 1 + rand() % (sizeArray * sizeArray);
            cout << *pt;
            Sleep(50);
        }
        else {
            destCoord.X = x * 4;
            destCoord.Y = sizeArray - y - 1;
            SetConsoleCursorPosition(hStdout, destCoord);
            *(pt - y - y) = 1 + rand() % (sizeArray * sizeArray);
            cout << *(pt - y - y);
            Sleep(50);
        }
    }

    cout << "\r";
    for (int i = 1; i <= sizeArray; i++)
        cout << "\n";
    system("pause");

}

void fillArray(int(*B)[sizeArray]) {
    for (int i = 0; i < sizeArray; i++)
        for (int j = 0; j < sizeArray; j++) {
            B[i][j] = 1 + rand() % (sizeArray * sizeArray);
        }

    showArray(B);

    system("pause");
}

void shakeA(int(*A)[sizeArray]) {
    for (int i = 0; i < (sizeArray / 2); i++) {
        for (int j = 0; j < sizeArray; j++) {
            swap(A[i][j], A[i + (sizeArray / 2)][j]);
        }
    }
    for (int i = 0; i < (sizeArray / 2); i++) {
        for (int j = 0; j < (sizeArray / 2); j++) {
            swap(A[i][j], A[i + (sizeArray / 2)][j + (sizeArray / 2)]);
        }
    }
}

void shakeB(int(*A)[sizeArray]) {
    for (int i = 0; i < (sizeArray / 2); i++) {
        for (int j = 0; j < sizeArray; j++) {
            if (j < (sizeArray / 2)) {
                swap(A[i][j], A[i + (sizeArray / 2)][j + (sizeArray / 2)]);
            }
            else {
                swap(A[i][j], A[i + (sizeArray / 2)][j - (sizeArray / 2)]);
            }
        }
    }
}

void shakeC(int(*A)[sizeArray]) {
    for (int i = 0; i < sizeArray; i++) {
        for (int j = 0; j < (sizeArray / 2); j++) {
            swap(A[i][j], A[i][j + (sizeArray / 2)]);
        }
    }
}

void shakeD(int(*A)[sizeArray]) {
    for (int i = 0; i < (sizeArray / 2); i++) {
        for (int j = 0; j < sizeArray; j++) {
            swap(A[i][j], A[i + (sizeArray / 2)][j]);
        }
    }
}

void sort(int(*A)[sizeArray]) {
    int* pt = A[0];
    bool sorted = false;

    while (sorted != true) {
        sorted = true;
        for (int i = 0; i < (sizeArray * sizeArray - 1); i++) {
            if (*(pt + i) > *(pt + i + 1)) {
                swap(*(pt + i), *(pt + i + 1));
                sorted = false;
            }
        }
    }
}

void sumArrays(int(*A)[sizeArray], int(*B)[sizeArray]) {
    for (int i = 0; i < sizeArray; i++)
        for (int j = 0; j < sizeArray; j++)
            A[i][j] += B[i][j];

    showArray(A);
}


int main() {
    setlocale(0, "");
    srand(time(0));

    int selectUserNum, chooseUser;

    int A[sizeArray][sizeArray];
    int B[sizeArray][sizeArray];

    /* Fill Snake Array*/
    fillSnake(A);
            
    /* Shake Array*/
    cout << "Please, choose a number for Shake:\n";
    cout << "\t 1 - Shake A - Circular\n";
    cout << "\t 2 - Shake B - Diagonal\n";
    cout << "\t 3 - Shake C - Vertical Mirror\n";
    cout << "\t 4 - Shake D - Horizontal Mirror\n";
    cout << "Number: ";
    cin >> chooseUser;
    cout << "\n";
    showArray(A);
    cout << "\nBefore Shake!\n";
    switch (chooseUser)
    {
    case 1:
        shakeA(A);
        break;

    case 2:
        shakeB(A);
        break;

    case 3:
        shakeC(A);
        break;

    case 4:
        shakeD(A);
        break;
    default:
        break;
    }
    Sleep(5000);
    system("cls");
    showArray(A);
    cout << "\nAfter Shake!\n";
    system("pause");
    

    /* Sorting Array */
    system("cls");
    showArray(A);
    Sleep(5000);
    sort(A);
    showArray(A);
    cout << "\n";
    system("pause");
    

    /* Mathematics Actions with Array */
    int input;
    string sign;
    cout << "Write me actions with array ('+', '-', '*', '/') and number\n";
    cout << "For example: '- 3'\n";
    cin >> sign >> input;

    if (sign == "+") {
        for (int i = 0; i < sizeArray; i++)
            for (int j = 0; j < sizeArray; j++)
                A[i][j] += input;
    }
    else if (sign == "-") {
        for (int i = 0; i < sizeArray; i++)
            for (int j = 0; j < sizeArray; j++)
                A[i][j] -= input;
    }
    else if (sign == "*") {
        for (int i = 0; i < sizeArray; i++)
            for (int j = 0; j < sizeArray; j++)
                A[i][j] *= input;
    }
    else if (sign == "/") {
        for (int i = 0; i < sizeArray; i++)
            for (int j = 0; j < sizeArray; j++)
                A[i][j] /= input;
    }
    else {
        cout << "Incorrect value or sign";
    }

    system("cls");
    showArray(A);
    system("pause");

    /* Individual Home Work - Sum two Arrays */
    system("cls");
    fillArray(B);
    sumArrays(A, B);
    cout << "\n";
}