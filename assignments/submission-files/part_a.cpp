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

void save_points_to_file(string filename, int *points, int rows, int cols) {
    // .node files
    // First line: <# of vertices> <dimension (must be 2)> <# of attributes> <# of boundary markers (0 or 1)>
    // Remaining lines: <vertex #> <x> <y> [attributes] [boundary marker]
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

void save_settings(int *total_points, int *dimensions, int *x_limit_start, int *x_limit_end, int *y_limit_start, int *y_limit_end, int *z_limit_start, int *z_limit_end) {
    string filename = "settings.txt";
    ofstream filePointer;
    filePointer.open(filename);
    if (filePointer == NULL) {
        cout << "Failed to write settings in a file, try again.";
        exit(0);
    } else {
        filePointer << *total_points << endl;
        filePointer << *dimensions << endl;
        filePointer << *x_limit_start << endl;
        filePointer << *x_limit_end << endl;
        filePointer << *y_limit_start << endl;
        filePointer << *y_limit_end << endl;
        filePointer << *z_limit_start << endl;
        filePointer << *z_limit_end << endl;
    }
    filePointer.close();
    cout << "Settings Saved in a file " << filename << endl;
}

void load_settings(int *total_points, int *dimensions, int *x_limit_start, int *x_limit_end, int *y_limit_start, int *y_limit_end, int *z_limit_start, int *z_limit_end) {
    string filename = "settings.txt";
    ifstream settings_file;
    settings_file.open(filename);

    if (settings_file == NULL) {
        cout << "Failed to open settings file, try again.";
        exit(0);
    } else {
        settings_file >> *total_points;
        settings_file >> *dimensions;
        settings_file >> *x_limit_start;
        settings_file >> *x_limit_end;
        settings_file >> *y_limit_start;
        settings_file >> *y_limit_end;
        settings_file >> *z_limit_start;
        settings_file >> *z_limit_end;
    }

    settings_file.close();
}

int main(int argc, char **argv) {
    srand(0);

    int total_points = 1000, dimensions = 2, x_limit_start = -10, x_limit_end = 10, y_limit_start = -10, y_limit_end = 10, z_limit_start = -10, z_limit_end = 10;

    if (argc == 1) {
        // load saved settings if not given by user
        load_settings(&total_points, &dimensions, &x_limit_start, &x_limit_end, &y_limit_start, &y_limit_end, &z_limit_start, &z_limit_end);
    } else {
        // initialize variables either using argv (which can be either given by user or loaded from settings file)
        string argv_i;
        for (int i = 1; i < argc; ++i) {
            argv_i = string(argv[i]);
            string key = argv_i.substr(0, argv_i.find('=', 0));
            int value = stoi(argv_i.substr(argv_i.find('=', 0) + 1));
            if (strcmp(key.c_str(), "n") == 0) {
                total_points = value;
            } else if (strcmp(key.c_str(), "d") == 0) {
                dimensions = value;
            } else if (strcmp(key.c_str(), "xmin") == 0) {
                x_limit_start = value;
            } else if (strcmp(key.c_str(), "xmax") == 0) {
                x_limit_end = value;
            } else if (strcmp(key.c_str(), "ymin") == 0) {
                y_limit_start = value;
            } else if (strcmp(key.c_str(), "ymax") == 0) {
                y_limit_end = value;
            } else if (strcmp(key.c_str(), "zmin") == 0) {
                z_limit_start = value;
            } else if (strcmp(key.c_str(), "zmax") == 0) {
                z_limit_end = value;
            }
        }
        save_settings(&total_points, &dimensions, &x_limit_start, &x_limit_end, &y_limit_start, &y_limit_end, &z_limit_start, &z_limit_end);
    }

    cout << "Settings:" << endl;
    cout << "\ttotal_points: " << total_points << endl;
    cout << "\tdimensions: " << dimensions << endl;
    cout << "\tx_limit_start: " << x_limit_start << endl;
    cout << "\tx_limit_end: " << x_limit_end << endl;
    cout << "\ty_limit_start: " << y_limit_start << endl;
    cout << "\ty_limit_end: " << y_limit_end << endl;
    if (dimensions == 3) {
        cout << "\tz_limit_start: " << z_limit_start << endl;
        cout << "\tz_limit_end: " << z_limit_end << endl;
    }

    int *points_array = (int *)malloc((total_points * dimensions) * sizeof(int));

    for (int i = 1; i <= total_points; i++) {
        points_array[i * dimensions + 0] = generate_random_within(x_limit_start, x_limit_end);
        points_array[i * dimensions + 1] = generate_random_within(y_limit_start, y_limit_end);
        if (dimensions == 3) {
            points_array[i * dimensions + 2] = generate_random_within(z_limit_start, z_limit_end);
        }
    }

    string filename = "random_points.node";
    save_points_to_file(filename, points_array, total_points, dimensions);
    cout << total_points << " random points save to file " << filename << endl;
    free(points_array);

    cout << "(Press Enter key to close the program...)" << endl;
    getchar();
    return 0;
}
