#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

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

int main(int argc, char **argv) {
    srand(0);

    int total_points, dimensions, extra;
    int *points_array = (int *)malloc((total_points * dimensions) * sizeof(int));
    string filename = "random_points.node";
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

    clock_t start, end;
    double cpu_time;
    ofstream log_file_pointer;
    log_file_pointer.open("log-merge-sort.csv");
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
        end = clock();

        // take time difference and save the logs
        cpu_time = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "Time Taken by " << i << " points = " << cpu_time << endl;
        log_file_pointer << i << ", " << cpu_time << endl;
    }

    free(points_array);
    log_file_pointer.close();

    cout << "(Press Enter key to close the program...)" << endl;
    getchar();
    return 0;
}
