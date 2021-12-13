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
        filePointer << rows << ' ' << cols << ' 0 0' << endl;
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
    cout << "Points Saved in File " << filename << endl;
}

int main(int argc, char **argv) {
    srand(0);

    // cout << "You have entered " << argc << "arguments" << endl;
    // for (int i = 0; i < argc; ++i) {
    //     cout << argv[i] << endl;
    // }

    // int total_points = 0, dimensions = 0, x_limit_start = 0, x_limit_end = 0, y_limit_start = 0, y_limit_end = 0, z_limit_start = 0, z_limit_end = 0;
    int total_points = 10, dimensions = 2, x_limit_start = -10, x_limit_end = 10, y_limit_start = -10, y_limit_end = 10, z_limit_start = -10, z_limit_end = 10;

    // // input total points
    // cout << "Enter Number of Points to Generate: ";
    // cin >> total_points;
    // if (total_points <= 0) {
    //     cout << "Invalid input: number of points must be more then zero" << endl;
    //     return 0;
    // }

    // // input dimensions
    // cout << "Enter Number of Dimensions (2 or 3): ";
    // cin >> dimensions;
    // if (dimensions != 2 && dimensions != 3) {
    //     cout << "Invalid input: dimensions must be 2 or 3" << endl;
    //     return 0;
    // }

    // get_axis_limits(&x_limit_start, &x_limit_end, "x-axis");
    // get_axis_limits(&y_limit_start, &y_limit_end, "y-axis");
    // get_axis_limits(&z_limit_start, &z_limit_end, "z-axis");

    int *points_array = (int *)malloc((total_points * dimensions) * sizeof(int));

    for (int i = 0; i < total_points; i++) {
        points_array[i * dimensions + 0] = generate_random_within(x_limit_start, x_limit_end);
        points_array[i * dimensions + 1] = generate_random_within(y_limit_start, y_limit_end);
        if (dimensions == 3) {
            points_array[i * dimensions + 2] = generate_random_within(z_limit_start, z_limit_end);
        }
    }

    print_points(points_array, total_points, dimensions);
    string filename = "part_a-files/" + to_string(time(NULL)) + ".node";
    cout << filename << endl;
    save_points_to_file(filename, points_array, total_points, dimensions);

    free(points_array);

    getchar();
    return 0;
}
