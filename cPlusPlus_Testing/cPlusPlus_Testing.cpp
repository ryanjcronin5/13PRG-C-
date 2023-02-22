#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class vars {
public:
    string descript;
    int price;
    string myText;

    void myMethod() {
        ofstream MyFile("GarageSale.txt");

        cout << "Enter description of the item: ";
        getline(cin, descript);
        cin.clear();
        cin.sync();

        cout << "Enter the items price: ";
        getline(cin, price);

        MyFile << descript + " ";
        MyFile << price;

        MyFile.close();
    }
};

int main() {
    vars myObj;
    myObj.myMethod();

    ifstream MyReadFile("GarageSale.txt");
    while (getline (MyReadFile, myObj.myText)) {
        cout << myObj.myText << endl;
    }
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
