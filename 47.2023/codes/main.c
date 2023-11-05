#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

// Custom power function to calculate 2^(x+y+2)
double custom_pow(int base, int exponent) {
    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

// Probability mass function p(x, y) with c = 3/2
double pmf(int x, int y) {
    return 1.5 / custom_pow(2, x + y + 2);
}

// Compute the cumulative distribution function (CDF) for p(x, y)
void compute_cdf(double cdf[3][3]) {
    cdf[0][0] = pmf(0, 0);
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (x == 0 && y == 0) {
                continue;
            }
            cdf[x][y] = cdf[x][y - 1] + cdf[x - 1][y] - cdf[x - 1][y - 1] + pmf(x, y);
        }
    }
}

// Generate a random value for X based on the CDF
int generate_random_x(double cdf[3][3], double rand_val) {
    for (int x = 0; x < 3; x++) {
        for (int y = 0; y < 3; y++) {
            if (cdf[x][y] > rand_val) {
                return x;
            }
        }
    }
    return 2; // Default to the maximum value
}

// Generate a random value for Y based on the CDF
int generate_random_y(int x, double cdf[3][3], double rand_val) {
    for (int y = 0; y < 3; y++) {
        if (cdf[x][y] > rand_val) {
            return y;
        }
    }
    return 2; // Default to the maximum value
}

int main() {
    double cdf[3][3];
    compute_cdf(cdf);

    // Seed the random number generator
    srand(time(NULL));

    // Simulate and store data in a data file
    FILE *data_file = fopen("simulated_data.dat", "w");
    if (data_file == NULL) {
        printf("Error opening the data file for writing.\n");
        return 1;
    }

    int num_simulations = 1000; // You can adjust the number of simulations as needed

    for (int i = 0; i < num_simulations; i++) {
        double rand_val = (double)rand() / RAND_MAX; // Generate a random number between 0 and 1
        int x = generate_random_x(cdf, rand_val);

        rand_val = (double)rand() / RAND_MAX;
        int y = generate_random_y(x, cdf, rand_val);

        fprintf(data_file, "%d %d\n", x, y);
    }

    fclose(data_file);

    printf("Simulated data has been saved to 'simulated_data.dat'\n");

    return 0;
}

