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

void selectionSort(int arr[], int n) {
    int i, j, min_idx;

    for (i = 0; i < n - 1; i++) {

        min_idx = i;
        for (j = i + 1; j < n; j++)
            if (arr[j] < arr[min_idx])
                min_idx = j;

        swap(&arr[min_idx], &arr[i]);
    }
}

int main(int argc, char **argv) {
    srand(0);

    int N, D, extra;
    string filename = "Random Points.node";
    ifstream randomPointsFile;
    randomPointsFile.open(filename);
    randomPointsFile >> N;
    randomPointsFile >> D;
    randomPointsFile >> extra >> extra;
    int *points = (int *)malloc((N * D) * sizeof(int));
    for (int i = 0; i < N; i++) {
        randomPointsFile >> extra;
        for (int j = 0; j < D; j++) {
            randomPointsFile >> points[i * D + j];
        }
    }
    randomPointsFile.close();

    clock_t start, end;
    double timeTaken;

    ofstream logFile;
    logFile.open("Time Logs.csv");
    if (logFile == NULL) {
        cout << "Failed to open log file, try again.";
        exit(0);
    }
    logFile << "n, timeTaken" << endl;

    for (int i = 1; i < N; i++) {

        start = clock();
        selectionSort(points, i);
        end = clock();

        timeTaken = ((double)(end - start)) / CLOCKS_PER_SEC;
        cout << "Time Taken by " << i << " points = " << timeTaken << endl;
        logFile << i << ", " << timeTaken << endl;
    }
    free(points);
    logFile.close();

    cout << "(Press Enter key to close the program...)" << endl;
    getchar();
    return 0;
}
