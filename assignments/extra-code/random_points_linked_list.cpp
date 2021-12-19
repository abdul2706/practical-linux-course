#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void print_points(char **numbers_string, int numbers) {
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

struct node {
    int data;
    int key;
    struct node *next;
};

struct LinkedList {
    struct node *head;
    struct node *current;
} ll1;

// void load_points_from_file(char *filename, struct LinkedList *points_list)
// {
//     // .node files
//     // First line: <# of vertices> <dimension (must be 2)> <# of attributes> <# of boundary markers (0 or 1)>
//     // Remaining lines: <vertex #> <x> <y> [attributes] [boundary marker]
//     FILE *filePointer = fopen(filename, "r");
//     char header[20];
//     fprintf(filePointer, "%s", header);

//     if (filePointer == NULL)
//     {
//         printf("Failed to write points in a file, try again.");
//     }
//     else
//     {

//         char ch;
//         while ((ch = fgetc(filePointer)) != EOF)
//         {
//             printf("%c", ch);
//         }
//         for (int i = 0; i < rows; i++)
//         {
//             fprintf(filePointer, "%d ", i + 1);
//             for (int j = 0; j < cols; j++)
//             {
//                 fprintf(filePointer, "%d", points[i * cols + j]);
//                 if (j < cols - 1)
//                 {
//                     fprintf(filePointer, " ");
//                 }
//             }
//             fprintf(filePointer, "\n");
//         }
//         fclose(filePointer);
//     }
//     printf("Points Saved in File %s\n", filename);
// }

// //display the list
// void printList()
// {
//     struct node *ptr = head;
//     printf("\n[ ");

//     //start from the beginning
//     while (ptr != NULL)
//     {
//         printf("(%d,%d) ", ptr->key, ptr->data);
//         ptr = ptr->next;
//     }

//     printf(" ]");
// }

// //insert link at the first location
// void insertFirst(int key, int data)
// {
//     //create a link
//     struct node *link = (struct node *)malloc(sizeof(struct node));

//     link->key = key;
//     link->data = data;

//     //point it to old first node
//     link->next = head;

//     //point first to new first node
//     head = link;
// }

// int length()
// {
//     int length = 0;
//     struct node *current;

//     for (current = head; current != NULL; current = current->next)
//     {
//         length++;
//     }

//     return length;
// }

int main(int argc, char **argv) {
    srand(0);

    struct LinkedList points_list;

    FILE *filePointer = fopen("points.node", "r");
    int rows = 0, cols = 0, attributes = 0, boundary_flag = 0;
    fscanf(filePointer, "%d %d %d %d\n", &rows, &cols, &attributes, &boundary_flag);
    printf("rows: %d, cols: %d\n", rows, cols);

    printf("%d\n", '0');
    printf("%d\n", '9');
    printf("%d\n", '-');
    printf("%d\n", ' ');

    int row_count = 0, col_count = 0, digit_count = 0;
    char ch;
    // char numbers_string[rows * cols][20];
    char *numbers_string = (int *)malloc((total_points * dimensions) * sizeof(int));
    for (int i = 0; i < rows * cols; i++) {
        sprintf(numbers_string[i], "");
    }

    int index = 0;
    while ((ch = fgetc(filePointer)) != EOF) {
        int ascii = ch;
        // printf("%c %d\n", ch, ascii);
        if (ascii == 10) {
            row_count += 1;
            col_count = 0;
            digit_count = 0;
            // printf("row_count: %d\n", row_count);
            continue;
        }
        if (ascii == 32) {
            col_count += 1;
            digit_count = 0;
            // printf("col_count: %d\n", col_count);
            continue;
        }

        // sprintf(numbers_string[row_count * col_count], "%c", ch);
        index = row_count * (cols + 1) + col_count;
        numbers_string[index][digit_count] = ch;
        digit_count += 1;
        numbers_string[index][digit_count] = '\0';
        // printf("%d >> %s\n", index, numbers_string[index]);
    }

    getchar();
    return 0;
}
