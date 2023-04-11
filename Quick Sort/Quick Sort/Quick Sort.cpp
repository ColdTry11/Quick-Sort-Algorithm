#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include "Employee.h"


using namespace std;

int partition(Employee** A, int p, int r, int n, int& comparison) {
    auto x = A[r];
    auto i = p - 1;
    for (int j = p; j <= r - 1; j++) {
        comparison++;
        if (A[j]->getID() <= x->getID()) {
            i++;
            auto temp = A[j];
            A[j] = A[i];
            A[i] = temp;
            //Comment out for big input
            // Print IDs
            for (int z = 0; z < n; z++) {
                cout << A[z]->getID() << " ";
            }
            cout << endl;
        }
    }
    // Swap r and i
    auto temp2 = A[r];
    A[r] = A[i + 1];
    A[i + 1] = temp2;
    return i + 1;
}

// Randomized Partition
int randomizedPartition(Employee** A, int p, int r, int n, int& comparison) {
    // Choose random number
    auto i = p + rand() % (r - p + 1);
    // Exchange r and i
    auto temp = A[r];
    A[r] = A[i];
    A[i] = temp;
    return partition(A, p, r, n, comparison);
}

// Randomized Quick Sort
void randomizedQuickSort(Employee** A, int p, int r, int n, int& comparison) {
    if (p < r) {
        int q = randomizedPartition(A, p, r, n, comparison);
        randomizedQuickSort(A, p, q - 1, n, comparison);
        randomizedQuickSort(A, q + 1, r, n, comparison);
    }
}

// Tail Recursive QuickSort
void tailRecursiveQuickSort(Employee** A, int p, int r, int n, int& comparison) {
    while (p < r) {
        auto q = partition(A, p, r, n, comparison);
        tailRecursiveQuickSort(A, p, q - 1, n, comparison);
        p = q + 1;
    }
}

// Quik Sort
void quickSort(Employee** A, int p, int r, int n, int& comparison)
{
    if (p < r) {
        int q = partition(A, p, r, n, comparison);
        quickSort(A, p, q - 1, n, comparison);
        quickSort(A, q + 1, r, n, comparison);
    }
}


int main(int argc, char** argv)
{
    //Check for command line error
    if (argc == 1) {
        cout << "You forgot the command line parameter" << endl;
        exit(0);
    }

    //Check for file
    ifstream ifs;
    ifs.open(argv[1], ios::in);
    if (!ifs) {
        cout << "could not find file " << argv[1] << endl;
        exit(0);
    }

    //Get how many lines
    string line;
    getline(ifs, line);
    int n = stoi(line);

    //initializing an array
    Employee** employee = new Employee * [n];

    //loop through file
    for (int i = 0; i < n; i++) {
        int age;
        int id;
        int year;
        string name;
        string job;
        string ids;
        string a;
        string y;
        getline(ifs, name, '|');
        getline(ifs, ids, '|');
        getline(ifs, a, '|');
        getline(ifs, job, '|');
        getline(ifs, y);
        id = stoi(ids);
        age = stoi(a);
        year = stoi(y);
        Employee* emp = new Employee(name, id, age, job, year);

        //Add to array
        employee[i] = emp;

    }

    int comparison = 0;

    // Quick Sort
    //quickSort(employee, 0, n - 1, n, comparison);

    // Randomized Quick Sort
    // Base random on time
    srand(time(nullptr));
    randomizedQuickSort(employee, 0, n - 1, n, comparison);

    // Tail Recursive Quick Sort
    //tailRecursiveQuickSort(employee, 0, n - 1, n, comparison);

    // Print Final sort
    for (int z = 0; z < n; z++) {
        cout << employee[z]->getID() << " ";
    }
    cout << endl;
    //Print total comparison
    cout << "It took " << comparison << " comparisons to sort this list." << endl;

    ofstream ofs;
    ofs.open("C:/Users/kylem/Desktop/output.txt", ios::out); //store result into a file
    for (int i = 0; i < n; i++) {
        ofs << employee[i]->saveFile();
    }
    ofs.close();

}