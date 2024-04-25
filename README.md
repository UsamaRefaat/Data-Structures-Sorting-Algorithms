## C++ Student Data Sorting

**Features:**

* Reads student data from a text file ("student.txt").  
* Sorts student data by name (ascending order).  
* Sorts student data by GPA (descending order).  
* Uses various sorting algorithms: Selection Sort, Insertion Sort, Bubble Sort, Shell Sort , Merge Sort, Quick Sort.  
* Measures execution time and number of comparisons for each sorting algorithm.  
* Saves the sorted data with the name, running time, and number of comparisons for each sorting algorithm used to separate files.  

**Data Format**

The student data file ("student.txt") should be formatted as follows:

1. The first line specifies the total number of students.
2. Each subsequent line contains student information in the following order:
    * Name (string)
    * ID (string)
    * GPA (double)

**Example Data:**

```4
Sara Ahmed
78697
3.1
Ali
3541
3.5
Mariam
69712
3.7
Mohamed Kamal
97848
2.2
```
**Output Files:**

* **SortedByName.txt:** Contains student data sorted by name (ascending) with the name, running time, and number of comparisons for each sorting algorithm used.

**Example Output:**

```Algorithm: Insertion Sort
Number Of Comparisons: 5
Running Time: 0.001 milliseconds

Ali  
3541  
3.5
Mariam  
69712  
3.7
Mohamed Kamal  
97848  
2.2
Sara Ahmed  
78697  
3.1
```
* **SortedByGPA.txt:** Contains student data sorted by GPA (descending) with the name, running time, and number of comparisons for each sorting algorithm used.

**Example Output:** 

```Algorithm: Selection Sort  
Number Of Comparisons: 6  
Running Time: 0.004 milliseconds  
Mariam  
69712  
3.7
Ali  
3541  
3.5
Sara Ahmed  
78697  
3.1
Mohamed Kamal  
97848  
2.2
```
Thank you.

