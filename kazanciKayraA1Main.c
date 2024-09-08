#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "givenA1.h"

int main() {
    
    int choice; // Variable to store user's choice
    struct Animal dataZoo[NUM_SAMPLES]; // Array to store animal data
    int k = 5; // Number of nearest neighbors to consider
    int vector1[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1}; // First feature vector
    int vector2[NUM_FEATURES] = {1, 0, 0, 1, 0, 0, 1, 1, 1, 1, 0, 0, 4, 0, 0, 1}; // Second feature vector
    int newSample[NUM_FEATURES] = {1, 1, 1, 0, 1, 0, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1}; // New sample feature vector
    int whichDistanceFunction = 3; // Index of the distance function to use
    int kNearestNeighbors[NUM_SAMPLES]; // Array to store indices of k nearest neighbors

    // Declare variables used in the switch cases
    char fileName[30];
    float mean, distance, similarity, accuracy;
    int mode, distance2, predictedClass;
    struct Animal testData[NUM_TEST_DATA];
    FILE *testFile; // Declare testFile here

    int result; // Declare result variable here
    int result2; // Declare result2 variable here

    do {

        printf("\n\nMenu:\n");
        // Display menu options
        printf("1. Read from file.\n");
        printf("2. Generate statistics for a feature.\n");
        printf("3. Display class distribution.\n");
        printf("4. Calculate Euclidean distance.\n");
        printf("5. Calculate Hamming distance.\n");
        printf("6. Calculate Jaccard similarity.\n");
        printf("7. Find k-nearest neighbors.\n");
        printf("8. Predict class for a new sample.\n");
        printf("9. Calculate accuracy of k-nearest neighbor algorithm.\n");
        printf("10. Exit.\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:

                // Read data from file into dataZoo array
                strcpy(fileName, "a1Data.txt");
                result = readFromFile(fileName, dataZoo);

                if (result == 1) {
                    printf("File read successfully.\n");
                } else {
                    printf("File read failed.\n");
                }
                printf("\n\n");

                break;

            case 2:

                // Generate statistics for a feature
                result2 = generateStatisticsFeatureX(dataZoo, 15, &mean, &mode);

                if (result2 == 0) {
                    printf("Mean of feature: %.2f\n", mean);
                    printf("Mode of feature: %d\n", mode);
                } else {
                    printf("Invalid feature number.\n");
                }

                printf("\n\n");

                break;

            case 3:

                // Display class distribution
                classDistribution(dataZoo);
                printf("\n\n");

                break;

            case 4:

                // Calculate Euclidean distance between two feature vectors
                distance = euclideanDistance(vector1, vector2);

                printf("Euclidean distance between dataZoo[0] and dataZoo[1]: %.2f\n", distance);
                printf("\n\n");

                break;

            case 5:

                // Calculate Hamming distance between two feature vectors
                distance2 = hammingDistance(vector1, vector2);

                printf("Hamming distance: %d\n", distance2);
                printf("\n\n");

                break;

            case 6:

                // Calculate Jaccard similarity between two feature vectors
                similarity = jaccardSimilarity(vector1, vector2);

                printf("Jaccard Similarity: %.2f\n", similarity);
                printf("\n\n");

                break;

            case 7:

                // Find k-nearest neighbors for a new sample
                findKNearestNeighbors(dataZoo, newSample, k, whichDistanceFunction, kNearestNeighbors);

                printf("Indices of %d nearest neighbors: ", k);

                for (int i = 0; i < k; i++) {
                    printf("%d ", kNearestNeighbors[i]);
                }

                printf("\n\n");

                break;

            case 8:

                // Predict class for a new sample based on its k-nearest neighbors
                predictedClass = predictClass(dataZoo, kNearestNeighbors, newSample, k);

                printf("Predicted class for the new sample: %d\n", predictedClass);
                printf("\n\n");

                break;

            case 9:

                // Calculate accuracy of the k-nearest neighbor algorithm using test data
                testFile = fopen("testData.csv", "r");

                if (testFile == NULL) {
                    printf("Error: Cannot open testData.csv\n");
                    return 1;
                }

                int index = 0;

                // Read test data from file
                while (fscanf(testFile, "%49[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\n",
                              testData[index].animalName,
                              &testData[index].features[0], &testData[index].features[1], &testData[index].features[2],
                              &testData[index].features[3], &testData[index].features[4], &testData[index].features[5],
                              &testData[index].features[6], &testData[index].features[7], &testData[index].features[8],
                              &testData[index].features[9], &testData[index].features[10], &testData[index].features[11],
                              &testData[index].features[12], &testData[index].features[13], &testData[index].features[14],
                              &testData[index].features[15], &testData[index].classLabel) == 18) {
                    index++;
                    if (index >= NUM_TEST_DATA) {
                        break;
                    }
                }

                fclose(testFile);

                // Calculate accuracy of k-nearest neighbor algorithm
                accuracy = findAccuracy(dataZoo, testData, k);
                printf("Accuracy of the k-nearest-neighbor algorithm: %.2f%%\n", accuracy);

                break;
        }

    } while(choice != 10); // Continue until user selects to exit

    return 0;
}