/*
 * Author: hajjl@oregonstate.edu
 * Date: 07/6/25
 * Description: Program to calculate total surface area and volume of n spherical segments,
 * validate user input, and compute average results.
 */

#include <stdio.h>
#include <math.h>

#define PI 3.14159265359


// Function: Ask the user how many segments they want and check if it's valid
int getNumberOfSegments() {
    int n;
    do {
        printf("How many spherical segments you want to evaluate [2-10]?\n");
        scanf("%d", &n);
    } while (n < 2 || n > 10);
    return n;
}

// Function: Ask the user for data about one segment and check if it’s valid
void getSegmentData(int index, float * R_ptr, float *ha_ptr, float *hb_ptr) {
    while (1) {
        printf("Obtaining data for spherical segment number %d\n", index);

        printf("What is the radius of the sphere (R)?\n");
        scanf("%f", R_ptr);

        printf("What is the height of the top area of the spherical segment (ha)?\n");
        scanf("%f", ha_ptr);

        printf("What is the height of the bottom area of the spherical segment (hb)?\n");
        scanf("%f", hb_ptr);

        printf("Entered data: R = %.2f ha = %.2f hb = %.2f.\n", *R_ptr, *ha_ptr, *hb_ptr);

        if (*R_ptr > 0 && *ha_ptr > 0 && *hb_ptr > 0 && *ha_ptr <= *R_ptr && *hb_ptr <= *R_ptr && *ha_ptr >= *hb_ptr) {
            break; // Valid input
        } else {
            printf("Invalid Input.\n");
        }
    }
}

// Function: Calculates top surface area using a = sqrt(R^2 - ha^2)
float calculateTopSurfaceArea(float R, float ha) {
    float a = sqrt(R * R - ha * ha);
    return PI * a * a;
}

// Function: Calculates bottom surface area using b = sqrt(R^2 - hb^2)
float calculateBottomSurfaceArea(float R, float hb) {
    float b = sqrt(R * R - hb * hb);
    return PI * b * b;
}

// Function: Calculates lateral surface area using h = ha - hb
float calculateLateralSurfaceArea(float R, float ha, float hb) {
    float h = ha - hb;
    return 2 * PI * R * h;
}

// Function: Calculates total surface area by summing top, bottom, lateral
float calculateTotalSurfaceArea(float topSA, float bottomSA, float lateralSA) {
    return topSA + bottomSA + lateralSA;
}

// Function: Calculates volume using h, a, b
float calculateVolume(float R, float ha, float hb) {
    float a = sqrt(R * R - ha * ha);
    float b = sqrt(R * R - hb * hb);
    float h = ha - hb;
    return (PI * h / 6) * (3 * a * a + 3 * b * b + h * h);
}

// Function: Prints average results
void printAverageResults(float totalSA, float totalVolume, int n) {
    float averageSA = totalSA / n;
    float averageVolume = totalVolume / n;
    printf("Total average results:\n");
    printf("Average Surface Area = %.2f Average Volume = %.2f.\n", averageSA, averageVolume);
}

int main() {
    int n = getNumberOfSegments();

    float sumSurfaceArea = 0.0;
    float sumVolume = 0.0;

    for (int i = 1; i <= n; i++) {
        float R, ha, hb;

        getSegmentData(i, &R, &ha, &hb);

        float topSA = calculateTopSurfaceArea(R, ha);
        float bottomSA = calculateBottomSurfaceArea(R, hb);
        float lateralSA = calculateLateralSurfaceArea(R, ha, hb);
        float totalSA = calculateTotalSurfaceArea(topSA, bottomSA, lateralSA);
        float volume = calculateVolume(R, ha, hb);

        printf("Total Surface Area = %.2f Volume = %.2f.\n", totalSA, volume);

        sumSurfaceArea += totalSA;
        sumVolume += volume;
    }

    printAverageResults(sumSurfaceArea, sumVolume, n);

    return 0;
}
