#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int generate_random_within(int start, int end) {
    float number_generated = (float)rand() / RAND_MAX;
    return (int)(number_generated * (end - start + 1)) + start;
}

void print_points(int *points, int rows, int cols) {
    printf("x, y");
    if (cols == 3) {
        printf(", z");
    }
    printf("\n");
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d", points[i * cols + j]);
            if (j < cols - 1) {
                printf(", ");
            }
        }
        printf("\n");
    }
}

void get_axis_limits(int *limit_start, int *limit_end, char *axis_name) {
    char buffer[50];
    sprintf(buffer, "Enter Start Limit for %s: ", axis_name);
    printf("%s", buffer);
    scanf("%d", limit_start);

    sprintf(buffer, "Enter End Limit for %s: ", axis_name);
    printf("%s", buffer);
    scanf("%d", limit_end);
    if (*limit_start > *limit_end) {
        int temp = *limit_start;
        *limit_start = *limit_end;
        *limit_end = temp;
    }
}

void save_points_to_file(char *filename, int *points, int rows, int cols) {
    // .node files
    // First line: <# of vertices> <dimension (must be 2)> <# of attributes> <# of boundary markers (0 or 1)>
    // Remaining lines: <vertex #> <x> <y> [attributes] [boundary marker]
    FILE *filePointer = fopen(filename, "w");
    char header[20];
    sprintf(header, "%d %d 0 0\n", rows, cols);
    fprintf(filePointer, "%s", header);

    if (filePointer == NULL) {
        printf("Failed to write points in a file, try again.");
    } else {
        for (int i = 0; i < rows; i++) {
            fprintf(filePointer, "%d ", i + 1);
            for (int j = 0; j < cols; j++) {
                fprintf(filePointer, "%d", points[i * cols + j]);
                if (j < cols - 1) {
                    fprintf(filePointer, " ");
                }
            }
            fprintf(filePointer, "\n");
        }
        fclose(filePointer);
    }
    printf("Points Saved in File %s\n", filename);
}

int main(int argc, char **argv) {
    srand(0);

    printf("You have entered %d arguments:\n", argc);
    for (int i = 0; i < argc; ++i) {
        printf("%s\n", argv[i]);
    }

    int total_points = 0, dimensions = 0, x_limit_start = 0, x_limit_end = 0, y_limit_start = 0, y_limit_end = 0, z_limit_start = 0, z_limit_end = 0;

    // input total points
    printf("Enter Number of Points to Generate: ");
    scanf("%d", &total_points);
    if (total_points <= 0) {
        printf("Invalid input: number of points must be more then zero\n");
        return 0;
    }

    // input dimensions
    printf("Enter Number of Dimensions (2 or 3): ");
    scanf("%d", &dimensions);
    if (dimensions != 2 && dimensions != 3) {
        printf("Invalid input: dimensions must be 2 or 3\n");
        return 0;
    }

    get_axis_limits(&x_limit_start, &x_limit_end, "x-axis");
    get_axis_limits(&y_limit_start, &y_limit_end, "y-axis");
    get_axis_limits(&z_limit_start, &z_limit_end, "z-axis");

    int *points_array = (int *)malloc((total_points * dimensions) * sizeof(int));

    for (int i = 0; i < total_points; i++) {
        points_array[i * dimensions + 0] = generate_random_within(x_limit_start, x_limit_end);
        points_array[i * dimensions + 1] = generate_random_within(y_limit_start, y_limit_end);
        if (dimensions == 3) {
            points_array[i * dimensions + 2] = generate_random_within(z_limit_start, z_limit_end);
        }
    }

    print_points(points_array, total_points, dimensions);
    char *filename = "points.node";
    save_points_to_file(filename, points_array, total_points, dimensions);

    free(points_array);
    getchar();
    return 0;
}
