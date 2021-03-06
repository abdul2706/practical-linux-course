#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void print_points(int *points, int rows, int cols) {
    for (int i = 0; i < cols; i++) {
        cout << "x" << i + 1 << ((i < cols - 1) ? ", " : "");
    }
    cout << endl;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << points[i * cols + j] << ((j < cols - 1) ? ", " : "");
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

// void average_function(int *points, int rows, int cols) {
//     float average_x = 0, average_y = 0, average_z = 0;
//     for (int i = 0; i < rows; i++) {
//         average_x += (float)points[i * cols + 0];
//         average_y += (float)points[i * cols + 0];
//         if (cols == 3) {
//             average_z += (float)points[i * cols + 0];
//         }
//     }
//     average_x /= rows;
//     average_y /= rows;
//     average_z /= rows;
// }

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

    int total_points, dimensions;

    int *points_array = (int *)malloc((total_points * dimensions) * sizeof(int));
    string filename = "random_points.node";
    int extra;
    ifstream random_points_file;
    random_points_file.open(filename);

    // read first number in first row
    random_points_file >> total_points;
    // read second number in first row
    random_points_file >> dimensions;
    // neglect 0 0 in first row
    random_points_file >> extra >> extra;

    for (int i = 0; i < total_points; i++) {
        // neglect point number
        random_points_file >> extra;
        for (int j = 0; j < dimensions; j++) {
            // read jth coordinate
            random_points_file >> points_array[i * dimensions + j];
        }
    }
    random_points_file.close();

    // print_points(points_array, 10, dimensions);

    clock_t start, end;
    double cpu_time;

    ofstream log_file_pointer;
    log_file_pointer.open("log-bubble-sort.csv");
    if (log_file_pointer == NULL) {
        cout << "Failed to open log file, try again.";
        exit(0);
    }
    // write header in log file
    log_file_pointer << "n, cpu_time" << endl;

    // loop over all files generated in part-a
    for (int i = 1; i < total_points; i++) {
        // apply algorithm and note time taken
        start = clock();
        bubbleSort(points_array, i, dimensions);
        // mergeSort(points_array, 0, i);
        end = clock();

        // take time difference and save the logs
        cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "Time Taken by " << i << " points = " << cpu_time << endl;
        log_file_pointer << i << ", " << cpu_time << endl;
    }
    // print_points(points_array, total_points, dimensions);
    free(points_array);
    log_file_pointer.close();

    cout << "(Press Enter key to close the program...)" << endl;
    getchar();
    return 0;
}
