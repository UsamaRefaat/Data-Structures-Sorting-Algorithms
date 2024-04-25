#include <iostream>
#include <fstream>
#include <cstdio>
#include <algorithm>
#include <string>
#include <vector>
#include <string>
#include <functional>
#include <chrono>
#include <utility>
using namespace std;
using namespace std::chrono;
class Student
{
private:
    string Id;
    string Name;
    double GPA;

public:
    Student() : Id(""), Name(""), GPA(0.0) {}
    Student(string Id, string Name, double GPA) : Id(Id), Name(Name), GPA(GPA) {}
    string GetName()
    {
        return Name;
    }
    double GetGPA()
    {
        return GPA;
    }
    string GetId()
    {
        return Id;
    }

    struct LessThanName
    {
        int &comparisons;

        LessThanName(int &comp) : comparisons(comp) {}

        bool operator()(const Student &a, const Student &b) const
        {
            comparisons++;
            return a.Name < b.Name;
        }
    };

    struct LessEqualName
    {
        int &comparisons;

        LessEqualName(int &comp) : comparisons(comp) {}

        bool operator()(const Student &a, const Student &b) const
        {
            comparisons++;
            return a.Name <= b.Name;
        }
    };

    struct GreaterThanGPA
    {
        int &comparisons;

        GreaterThanGPA(int &comp) : comparisons(comp) {}

        bool operator()(const Student &a, const Student &b) const
        {
            comparisons++;
            return a.GPA > b.GPA;
        }
    };

    struct GreaterEqualGPA
    {
        int &comparisons;

        GreaterEqualGPA(int &comp) : comparisons(comp) {}

        bool operator()(const Student &a, const Student &b) const
        {
            comparisons++;
            return a.GPA >= b.GPA;
        }
    };
};

template <class T, class Compare>
void SelectionSort(T arr[], int n, Compare compareFunction)
{
    int min_idx;
    for (int i = 0; i < n - 1; i++)
    {
        min_idx = i;
        for (int j = i + 1; j < n; j++)
        {
            if (compareFunction(arr[j], arr[min_idx]))
            {
                min_idx = j;
            }
        }
        swap(arr[i], arr[min_idx]);
    }
}

template <class T, class Compare>
void InsertionSort(T arr[], int n, Compare compareFunction)
{
    T key{};
    int j{};
    for (int i = 1; i < n; i++)
    {
        key = arr[i];
        j = i - 1;
        while (j >= 0 && !compareFunction(arr[j], key))
        {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

template <class T, class Compare>
void BubbleSort(T arr[], int n, Compare compareFunction)
{
    bool no_swap = true;
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (!compareFunction(arr[j], arr[j + 1]))
            {
                swap(arr[j], arr[j + 1]);
                no_swap = false;
            }
        }
        if (no_swap)
        {
            break;
        }
    }
}

template <class T, class Compare>
void ShellSort(T arr[], int n, Compare compareFunction)
{
    for (int gap = n / 2; gap > 0; gap /= 2)
    {
        for (int i = gap; i < n; i++)
        {
            T key = arr[i];
            int j = i;
            while (j >= gap && !compareFunction(arr[j - gap], key))
            {
                arr[j] = arr[j - gap];
                j -= gap;
            }
            arr[j] = key;
        }
    }
}

template <class T, class Compare>
void Merge(T Array[], T LeftArray[], T RightArray[], int LeftSize, int RightSize, Compare compareFunction)
{
    int i = 0, j = 0, k = 0;
    while (i < LeftSize && j < RightSize)
    {
        if (compareFunction(LeftArray[i], RightArray[j]))
        {
            Array[k] = LeftArray[i];
            i++;
        }
        else
        {
            Array[k] = RightArray[j];
            j++;
        }
        k++;
    }

    while (i < LeftSize)
    {
        Array[k] = LeftArray[i];
        i++;
        k++;
    }
    while (j < RightSize)
    {
        Array[k] = RightArray[j];
        j++;
        k++;
    }
}

template <class T, class Compare>
void MergeSort(T Array[], int Size, Compare compareFunction)
{
    if (Size < 2)
        return;

    int MidIndex = Size / 2;
    T LeftArray[MidIndex];
    T RightArray[Size - MidIndex];

    for (int i = 0; i < MidIndex; i++)
    {
        LeftArray[i] = Array[i];
    }

    for (int i = MidIndex; i < Size; i++)
    {
        RightArray[i - MidIndex] = Array[i];
    }

    MergeSort(LeftArray, MidIndex, compareFunction);
    MergeSort(RightArray, (Size - MidIndex), compareFunction);
    Merge(Array, LeftArray, RightArray, MidIndex, Size - MidIndex, compareFunction);
}

template <typename T, typename Compare>
int Partition(T arr[] , int l, int r, Compare compareFunction)
{
    T pivot = arr[r];
    int i = l - 1;
    for (int j = l; j < r; j++)
    {
        if (compareFunction(arr[j], pivot))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[r]); 
    return i + 1; // index of pivot
}

template <typename T, typename Compare>
void QuickSort(T arr[] , int l, int r, Compare compareFunction)
{
    if (l < r)
    {
        int pivot = Partition(arr, l, r, compareFunction); // index of pivot
        QuickSort(arr, l, pivot - 1, compareFunction);
        QuickSort(arr, pivot + 1, r, compareFunction);
    }
}

pair<int, Student *> GetTheData()
{
    ifstream Data("student.txt");
    int NumberOfStudents;
    Data >> NumberOfStudents;
    Student *ArrayOfData = new Student[NumberOfStudents];
    string FirstLine;
    getline(Data, FirstLine); // skipping the number of students
    for (int i = 0; i < NumberOfStudents; i++)
    {
        string Name, Id, GPA;
        getline(Data, Name, '\n');
        getline(Data, Id, '\n');
        getline(Data, GPA, '\n');
        ArrayOfData[i] = Student(Id, Name, stod(GPA));
    }
    Data.close();
    return {NumberOfStudents, ArrayOfData};
}

void SaveTheOutput(const string FileName, Student arr[], int n, string AlgorithmName, double RunTime, int comparisons)
{
    ofstream Output(FileName, ios::app);
    Output << "Algorithm: " << AlgorithmName << endl;
    Output << "Number Of Comparisons: " << comparisons << endl;
    Output << "Running Time: " << RunTime << " milliseconds" << endl;
    for (int i = 0; i < n; i++)
    {
        Output << arr[i].GetName() << endl;
        Output << arr[i].GetId() << endl;
        Output << arr[i].GetGPA() << endl;
    }
    Output.close();
}
template <class Compare>
void SortAndSave(Student *Students, int NumberOfStudents, const string &fileName, string algorithmName, Compare compareFunction, int &comparisons)
{
    Student *Students_copy = new Student[NumberOfStudents];
    copy(Students, Students + NumberOfStudents, Students_copy);
    comparisons = 0;
    auto start = high_resolution_clock::now();
    if (algorithmName == "Selection Sort")
    {
        SelectionSort(Students_copy, NumberOfStudents, compareFunction);
        comparisons = compareFunction.comparisons;
    }
    else if (algorithmName == "Insertion Sort")
    {
        InsertionSort(Students_copy, NumberOfStudents, compareFunction);
        comparisons = compareFunction.comparisons;
    }
    else if (algorithmName == "Bubble Sort")
    {
        BubbleSort(Students_copy, NumberOfStudents, compareFunction);
        comparisons = compareFunction.comparisons;
    }
    else if (algorithmName == "Merge Sort")
    {
        MergeSort(Students_copy, NumberOfStudents, compareFunction);
        comparisons = compareFunction.comparisons;
    }
    else if (algorithmName == "Shell Sort")
    {
        ShellSort(Students_copy, NumberOfStudents, compareFunction);
        comparisons = compareFunction.comparisons;
    }
    else if (algorithmName == "Quick Sort")
    {
        QuickSort(Students_copy, 0, NumberOfStudents - 1, compareFunction);
        comparisons = compareFunction.comparisons;
    }
    else
    {
        cout << "Wrong Sorting algorithm name" << endl;
        return;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    double runtime = static_cast<double>(duration.count()) / 1000.0;
    SaveTheOutput(fileName, Students_copy, NumberOfStudents, algorithmName, runtime, comparisons);
    delete[] Students_copy;
}
int main()
{

    //---------------------------------------------------------------------------------------------------
    pair<int, Student *> data = GetTheData();
    int NumberOfStudents = data.first;
    Student *Students = data.second;
    int comparisons = 0;
    //---------------------------------------------------------------------------------------------------

    // sorting by Name
    SortAndSave(Students, NumberOfStudents, "SortedByName.txt", "Selection Sort", Student::LessThanName(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByName.txt", "Insertion Sort", Student::LessThanName(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByName.txt", "Bubble Sort", Student::LessThanName(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByName.txt", "Shell Sort", Student::LessThanName(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByName.txt", "Merge Sort", Student::LessEqualName(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByName.txt", "Quick Sort", Student::LessThanName(comparisons), comparisons);

    // Sorting by GPA
    SortAndSave(Students, NumberOfStudents, "SortedByGPA.txt", "Selection Sort", Student::GreaterThanGPA(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByGPA.txt", "Insertion Sort", Student::GreaterThanGPA(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByGPA.txt", "Bubble Sort", Student::GreaterThanGPA(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByGPA.txt", "Shell Sort", Student::GreaterThanGPA(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByGPA.txt", "Merge Sort", Student::GreaterEqualGPA(comparisons), comparisons);
    SortAndSave(Students, NumberOfStudents, "SortedByGPA.txt", "Quick Sort", Student::GreaterThanGPA(comparisons), comparisons);

    return 0;
}
