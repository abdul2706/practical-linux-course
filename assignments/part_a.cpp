#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int generate_random_within(int start, int end) {
    float number_generated = (float)rand() / RAND_MAX;
    return (int)(number_generated * (end - start + 1)) + start;
}

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

void get_axis_limits(int *limit_start, int *limit_end, string axis_name) {
    cout << "Enter Start Limit for " << axis_name << ": ";
    cin >> *limit_start;
    cout << "Enter End Limit for" << axis_name << ": ";
    cin >> *limit_end;
    if (*limit_start > *limit_end) {
        int temp = *limit_start;
        *limit_start = *limit_end;
        *limit_end = temp;
    }
}

void save_points_to_file(string filename, int *points, int rows, int cols) {
    // .node files
    // First line: <# of vertices> <dimension (must be 2)> <# of attributes> <# of boundary markers (0 or 1)>
    // Remaining lines: <vertex #> <x> <y> [attributes] [boundary marker]
    // FILE *filePointer = fopen(filename, "w");
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
                // fprintf(filePointer, "%d", points[i * cols + j]);
                filePointer << points[i * cols + j];
                if (j < cols - 1) {
                    // fprintf(filePointer, " ");
                    filePointer << " ";
                }
            }
            filePointer << endl;
        }
    }
    filePointer.close();
    // cout << "Points Saved in File " << filename << endl;
}

int main(int argc, char **argv) {
    srand(0);

    int total_points = 5000, dimensions = 2, x_limit_start = -10, x_limit_end = 10, y_limit_start = -10, y_limit_end = 10, z_limit_start = -10, z_limit_end = 10;
    int *points_array = (int *)malloc((total_points * dimensions) * sizeof(int));
    int rows;

    for (int i = 1; i <= total_points; i++) {
        rows = i;
        for (int i = 1; i <= rows; i++) {
            points_array[i * dimensions + 0] = generate_random_within(x_limit_start, x_limit_end);
            points_array[i * dimensions + 1] = generate_random_within(y_limit_start, y_limit_end);
            if (dimensions == 3) {
                points_array[i * dimensions + 2] = generate_random_within(z_limit_start, z_limit_end);
            }
        }

        // print_points(points_array, total_points, dimensions);
        string filename = "part_a-files/" + to_string(i) + ".node";
        cout << filename << endl;
        save_points_to_file(filename, points_array, rows, dimensions);
    }
    free(points_array);

    getchar();
    return 0;
}
