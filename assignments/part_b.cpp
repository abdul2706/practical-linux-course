#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void print_points(int *points, int rows, int cols) {
    cout << "x, y";
    if (cols == 3) {
        cout << ", z";
    }
    cout << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << points[i * cols + j];
            if (j < cols - 1) {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

// void linear_function(int *points, int rows, int cols) {
//     for (int i = 0; i < n; i++) {
//     }
// }

// void quadratic_function(int *points, int rows, int cols) {
//     for (int i = 0; i < n; i++) {
//         for (int j = 0; j < n; j++) {
//         }
//     }
// }

void average_function(int *points, int rows, int cols) {
    float average_x = 0, average_y = 0, average_z = 0;
    for (int i = 0; i < rows; i++) {
        average_x += (float)points[i * cols + 0];
        average_y += (float)points[i * cols + 0];
        if (cols == 3) {
            average_z += (float)points[i * cols + 0];
        }
    }
    average_x /= rows;
    average_y /= rows;
    average_z /= rows;
    // float output[3] = {average_x, average_y, average_z};
    // return output;
}

void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

// void bubbleSort(int arr[], int n) {
void bubbleSort(int *points, int rows, int cols) {
    // sort on x-coordinates
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (points[j * cols + 0] > points[(j + 1) * cols + 0]) {
                swap(&points[j * cols + 0], &points[(j + 1) * cols + 0]);
            }
        }
    }

    // sort on y-coordinates
    for (int i = 0; i < rows - 1; i++) {
        for (int j = 0; j < rows - i - 1; j++) {
            if (points[j * cols + 0] > points[(j + 1) * cols + 0]) {
                swap(&points[j * cols + 0], &points[(j + 1) * cols + 0]);
            }
        }
    }

    if (cols == 3) {
        // sort on z-coordinates
        for (int i = 0; i < rows - 1; i++) {
            for (int j = 0; j < rows - i - 1; j++) {
                if (points[j * cols + 0] > points[(j + 1) * cols + 0]) {
                    swap(&points[j * cols + 0], &points[(j + 1) * cols + 0]);
                }
            }
        }
    }
}

void merge(int *array, int const left, int const mid, int const right) {
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    int *leftArray = new int[subArrayOne];
    int *rightArray = new int[subArrayTwo];

    for (int i = 0; i < subArrayOne; i++) {
        leftArray[i] = array[left + i];
    }
    for (int j = 0; j < subArrayTwo; j++) {
        rightArray[j] = array[mid + 1 + j];
    }

    int indexOfSubArrayOne = 0;
    int indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo]) {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        } else {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
}

// void mergeSort(int array[], int const begin, int const end) {
void mergeSort(int *points, int const begin, int const end) {
    if (begin >= end) {
        return;
    }

    int mid = begin + (end - begin) / 2;
    mergeSort(points, begin, mid);
    mergeSort(points, mid + 1, end);
    merge(points, begin, mid, end);
}

int main(int argc, char **argv) {
    srand(0);

    int total_points, dimensions, x_limit_start, x_limit_end, y_limit_start, y_limit_end, z_limit_start, z_limit_end;
    int *points_array = (int *)malloc((total_points * dimensions) * sizeof(int));
    string filename;
    int currentNumber, rows, cols, extra;

    clock_t start, end;
    double cpu_time_used;

    ofstream logFilePointer;
    logFilePointer.open("log-merge-sort.csv");
    if (logFilePointer == NULL) {
        cout << "Failed to open log file, try again.";
        exit(0);
    }
    // write header in log file
    logFilePointer << "filename, n, cpu_time_used" << endl;

    // loop over all files generated in part-a
    for (int i = 1; i <= 2500; i++) {
        filename = "part_a-files/" + to_string(i) + ".node";
        ifstream randomNumberFile;
        randomNumberFile.open(filename);
        // read first number in first row
        randomNumberFile >> total_points;
        // read second number in first row
        randomNumberFile >> dimensions;
        // neglect 0 0 in first row
        randomNumberFile >> extra >> extra;
        // loop through all points in this file and store them in points_array
        for (int j = 0; j < total_points; j++) {
            // neglect point number
            randomNumberFile >> extra;
            // read x-coordinate
            randomNumberFile >> points_array[j * dimensions + 0];
            // read y-coordinate
            randomNumberFile >> points_array[j * dimensions + 1];
            // read z-coordinate
            if (dimensions == 3) {
                randomNumberFile >> points_array[j * dimensions + 2];
            }
        }
        randomNumberFile.close();

        // apply algorithm and note time taken
        start = clock();
        // bubbleSort(points_array, total_points, dimensions);
        mergeSort(points_array, 0, total_points - 1);
        end = clock();
        cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "Time Taken by " << i << ".node file: " << cpu_time_used << endl;
        logFilePointer << i << ".node"
                       << ", " << i << ", " << cpu_time_used << endl;
    }
    // print_points(points_array, total_points, dimensions);
    free(points_array);
    logFilePointer.close();

    // getchar();
    return 0;
}
