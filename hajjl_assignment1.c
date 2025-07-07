/*
 * Author: hajjl@oregonstate.edu
 * Date: 07/6/25
 * Description: Program to calculate total surface area and volume of n spherical segments,
 * validate user input, and compute average results.
 */

#include <stdio.h>
#include <math.h>

#define PI 3.14159

/*
 * Function: getSegments
 * Description: Ask the user how many segments they want and check if it's valid.
 * Parameters: None.
 * Returns: The number of segments n.
 */
int getSegments() {
    int n;
    do {
        printf("How many spherical segments you want to evaluate [2-10]?\n");
        scanf("%d", &n);
    } while (n < 2 || n > 10);
    return n;
}

/*
 * Function: getData
 * Description: Prompts the user for data needed to calculate areas and volume, and 
 * check to make sure data is valid
 * Parameters:
 *   index: The segment number being processed.
 *   R_ptr: Pointer to store the radius of the sphere.
 *   ha_ptr: Pointer to store the height of the top area of the segment.
 *   hb_ptr: Pointer to store the height of the bottom area of the segment.
 * Returns: None
 */
void getData(int index, float * R_ptr, float *ha_ptr, float *hb_ptr) {
    while (1) {
        printf("Obtaining data for spherical segment number %d\n", index);

        printf("What is the radius of the sphere (R)?\n");
        scanf("%f", R_ptr);

        printf("What is the height of the top area of the spherical segment (ha)?\n");
        scanf("%f", ha_ptr);

        printf("What is the height of the bottom area of the spherical segment (hb)?\n");
        scanf("%f", hb_ptr);

        printf("Entered data: R = %.2f ha = %.2f hb = %.2f.\n", *R_ptr, *ha_ptr, *hb_ptr);

        //check if all data is valid
        if (*R_ptr > 0 && *ha_ptr > 0 && *hb_ptr > 0 && *ha_ptr <= *R_ptr && *hb_ptr <= *R_ptr && *ha_ptr >= *hb_ptr) {
            break; // Valid input
        } else {
            printf("Invalid Input.\n");
        }
    }
}

/*
 * Function: computeArea
 * Description: Computes the bottom area.
 * Parameters:
 *   R: The radius of the sphere.
 *   h: The height from the sphere center to the cap.
 * Returns: The bottom area.
 */
float computeArea(float R, float h) {
    float a = sqrt(R * R - h * h);
    return PI * a * a;
}

/*
 * Function: computeLateral
 * Description: Computes the lateral surface area of the spherical segment.
 * Parameters:
 *   R: The radius of the sphere.
 *   ha: The height of the top area of the segment.
 *   hb: The height of the bottom area of the segment.
 * Returns: The computed lateral surface area.
 */
float computeLateral(float R, float ha, float hb) {
    float h = ha - hb;
    return 2 * PI * R * h;
}

/*
 * Function: computeTotal
 * Description: Computes the total surface area.
 * Parameters:
 *   topArea: Area of the top cap.
 *   bottomArea: Area of the bottom cap.
 *   lateralArea: Lateral surface area of the segment.
 * Returns: The sum total of the surface areas.
 */
float computeTotal(float topArea, float bottomArea, float lateralArea) {
    return topArea + bottomArea + lateralArea;
}

/*
 * Function: computeVolume
 * Description: Computes the volume of the spherical segment.
 * Parameters:
 *   R: The radius of the sphere.
 *   ha: The height of the top area.
 *   hb: The height of the bottom area.
 * Returns: The computed volume of the segment.
 */
float computeVolume(float R, float ha, float hb) {
    float a = sqrt(R * R - ha * ha);
    float b = sqrt(R * R - hb * hb);
    float h = ha - hb;
    return (PI * h / 6) * (3 * a * a + 3 * b * b + h * h);
}

/*
 * Function: printAverages
 * Description: Computes and prints the average surface area and average volume of all spherical segments.
 * Parameters:
 *   totalArea: The sum of surface areas of all segments.
 *   totalVolume: The sum of volumes of all segments.
 *   n: The total number of segments.
 * Returns: None
 */
void printAverages(float totalArea, float totalVolume, int n) {
    float averageArea = totalArea / n;
    float averageVolume = totalVolume / n;
    printf("Total average results:\n");
    printf("Average Surface Area = %.2f Average Volume = %.2f.\n", averageArea, averageVolume);
}

int main() {

    //Initialize variables
    float sumArea = 0.0, sumVolume = 0.0;
    float topArea = 0.0, bottomArea = 0.0, totalArea = 0.0, lateralArea = 0.0, volume = 0.0;
    float R, ha, hb;

    //Get the number of segments from the user 
    int n = getSegments();

    //Iterate through the segments and compute individual and total areas and volumes.
    for (int i = 1; i <= n; i++) {
        //Get the needed data: sphere radius, bottom and top heights
        getData(i, &R, &ha, &hb);

        //Compute areas of top, bottom, lateral, and total using provided data
        topArea = computeArea(R, ha);
        bottomArea = computeArea(R, hb);
        lateralArea = computeLateral(R, ha, hb);
        totalArea = computeTotal(topArea, bottomArea, lateralArea);
        //compute volume
        volume = computeVolume(R, ha, hb);
        //print total area and volume for each segment
        printf("Total Surface Area = %.2f Volume = %.2f.\n", totalArea, volume);

        //Add areas and volumes across segements
        sumArea += totalArea;
        sumVolume += volume;
    }

    //print average area and volume across all segments
    printAverages(sumArea, sumVolume, n);

    return 0;
}
