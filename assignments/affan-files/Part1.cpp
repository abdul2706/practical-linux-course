#include <fstream>
#include <iostream>
#include <string>

using namespace std;

void save_points_to_file(string filename, int *points, int rows, int cols) {
    ofstream filePointer;
    filePointer.open(filename);
    if (filePointer == NULL) {
        cout << "Failed to write points in a file, try again.";
        exit(0);
    } else {
        filePointer << rows << " " << cols << " 0 0" << endl;
        for (int i = 0; i < rows; i++) {
            filePointer << i + 1 << " ";
            for (int j = 0; j < cols; j++) {
                filePointer << points[i * cols + j];
                if (j < cols - 1) {
                    filePointer << " ";
                }
            }
            filePointer << endl;
        }
    }
    filePointer.close();
    cout << "Points Saved in File " << filename << endl;
}

int generateRandomNumber(int start, int end) {
    float number_generated = (float)rand() / RAND_MAX;
    return (int)(number_generated * (end - start + 1)) + start;
}

void getAxisLimitsFromUser(int *limit_start, int *limit_end, string axis_name) {
    cout << "Enter Start Limit for " << axis_name << ": ";
    cin >> *limit_start;
    cout << "Enter End Limit for " << axis_name << ": ";
    cin >> *limit_end;
    if (*limit_start > *limit_end) {
        int temp = *limit_start;
        *limit_start = *limit_end;
        *limit_end = temp;
    }
}

int main() {
    srand(0);
    int N = 10000, D = 2, xmin = -10000, xmax = 10000, ymin = -10000, ymax = 10000, zmin = -10000, zmax = 10000;

    cout << "Enter Number of Points to Generate: ";
    cin >> N;
    if (N <= 0) {
        cout << "Invalid input: number of points must be more then zero" << endl;
        return 0;
    }

    cout << "Enter Number of Dimensions (2 or 3): ";
    cin >> D;
    if (D != 2 && D != 3) {
        cout << "Invalid input: Dimensions must be 2 or 3" << endl;
        return 0;
    }

    getAxisLimitsFromUser(&xmin, &xmax, "x-axis");
    getAxisLimitsFromUser(&ymin, &ymax, "y-axis");
    getAxisLimitsFromUser(&zmin, &zmax, "z-axis");

    int *points = (int *)malloc((N * D) * sizeof(int));

    for (int i = 0; i < N; i++) {
        points[i * D + 0] = generateRandomNumber(xmin, xmax);
        points[i * D + 1] = generateRandomNumber(ymin, ymax);
        if (D == 3) {
            points[i * D + 2] = generateRandomNumber(zmin, zmax);
        }
    }

    string filename = "Random Points.node";
    cout << filename << endl;
    save_points_to_file(filename, points, N, D);
    free(points);

    getchar();
    return 0;
}
