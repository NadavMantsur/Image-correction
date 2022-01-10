/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <math.h>


/*-------------------------------------------------------------------------
  Constants and definitions:
--------------------------------------------------------------------------*/

#define N 50
#define M 50
#define RECT 4


/* put your #defines and typedefs here*/
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]);

int sum_rect(int integral_image[][M], int rect[RECT]);

void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]);

void print_array(int a[N][M], int n, int m);


/*-------------------------------------------------------------------------
  Your implementation of the functions (describe what each function does)
 -------------------------------------------------------------------------*/



/*-------------------------------------------------------------------------
  The main program
 -------------------------------------------------------------------------*/

int main() {
    int n = 0, m = 0;
    printf("Enter image dimensions:\n");
    scanf("%d%d", &n, &m);

    int image[N][M] = {{0}};
    printf("Enter image:\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            scanf("%d", &image[i][j]);
        }
    }

    int h = 0, w = 0;
    printf("Enter sliding window dimensions:\n");
    scanf("%d%d", &h, &w);

    int integral_image[N][M];
    compute_integral_image(image, n, m, integral_image);
    printf("Integral image is:\n");
    print_array(integral_image, n, m);

    int average[N][M];
    sliding_average(integral_image, n, m, h, w, average);
    printf("Smoothed image is:\n");
    print_array(average, n, m);

    return 0;
}

void print_array(int a[N][M], int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            printf("%d", a[i][j]);
            if (j != m - 1) {
                printf(" ");
            }
        }
        printf("\n");
    }
}

//A
//computes the integral image of image
void compute_integral_image(int image[][M], int n, int m, int integral_image[][M]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i == 0 && j == 0) {
                integral_image[i][j] = image[i][j];
            } else if (i == 0 && j < 0) {
                integral_image[i][j] = image[i][j] + integral_image[i][j - 1];
            } else if (i > 0 && j == 0) {
                integral_image[i][j] = image[i][j] + integral_image[i - 1][j];
            } else {
                integral_image[i][j] = image[i][j] + integral_image[i][j - 1] + integral_image[i - 1][j] - integral_image[i - 1][j - 1];
            }
        }
    }
}

//B
//𝑅𝑒𝑐𝑡=(𝑖𝑡𝑜𝑝,𝑗𝑙𝑒𝑓𝑡,𝑖𝑏𝑜𝑡𝑡𝑜𝑚,𝑗𝑟𝑖𝑔ℎ𝑡)
//cumputes the sum of a rectangle in the integral image
int sum_rect(int integral_image[][M], int rect[RECT]) {
    int sum = 0;
    sum = integral_image[rect[2]][rect[3]] - integral_image[rect[0] - 1][rect[3]] - integral_image[rect[2]][rect[1] - 1] +
          integral_image[rect[0] - 1][rect[1] - 1];
    return sum;
}

//C
//computes the average of a sliding rectangle of image
void sliding_average(int integral_image[][M], int n, int m, int h, int w, int average[][M]) {
    int i_top, j_left, i_bottom, j_right;
    int calc_size_of_picture = h * w;
    int row_down = (h - 1) / 2;
    int row_up = row_down + 1;
    int col_left = (w + 1) / 2;
    int col_right = col_left - 1;
    double calc = 0;

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            i_top = i - row_up;
            j_left = j - col_left;
            i_bottom = i + row_down;
            j_right = j + col_right;
            //deal with bottom
            if (i_bottom >= n) {
                i_bottom = n - 1;
            }
            if (j_right >= m) {
                j_right = m - 1;
            }
            //deal with top
            if (j_left < 0 && i_top < 0) {
                calc = (double)(integral_image[i_bottom][j_right]) / calc_size_of_picture;
            } else if (j_left < 0) {
                calc =(double)(integral_image[i_bottom][j_right] - integral_image[i_top][j_right]) / calc_size_of_picture;
            } else if (i_top < 0) {
                calc =(double)(integral_image[i_bottom][j_right] - integral_image[i_bottom][j_left]) / calc_size_of_picture;
            } else {
                int rect[RECT] = {i_top+1, j_left+1, i_bottom, j_right};
                calc =(double)(sum_rect(integral_image, rect)) / calc_size_of_picture;

            }
            average[i][j] = round(calc);
        }
    }
}