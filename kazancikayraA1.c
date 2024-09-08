#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "givenA1.h"

// Function to read data from a file into an array of Animal structs
int readFromFile(char fName[30], struct Animal dataZoo[NUM_SAMPLES]) {

    FILE *file = fopen(fName, "r");
    if (file == NULL) {
        printf("Error: Cannot open file %s\n", fName);
        return -1;
    }

    int index = 0;
    // Read data from the file into the dataZoo array
    while (fscanf(file, "%s", dataZoo[index].animalName) == 1) {
        for (int j = 0; j < NUM_FEATURES; j++) {
            if (fscanf(file, "%d", &dataZoo[index].features[j]) != 1) {
                printf("Error reading feature %d from file.\n", j + 1);
                return -1;
            }
        }

        if (fscanf(file, "%d", &dataZoo[index].classLabel) != 1) {
            printf("Error reading classLabel from file.\n");
            return -1;
        }
        index++;
    }

    fclose(file);

    return 1;
}


// Function to calculate mean and mode for a specific feature
int generateStatisticsFeatureX(struct Animal dataZoo[NUM_SAMPLES], int whichFeature, float *mean, int *mode) {

    if (whichFeature < 1 || whichFeature > NUM_FEATURES) {
        return -1;
    }

    int featureCount[NUM_SAMPLES] = {0};
    int maxCount = 0;
    int modeValue = -1;
    float sum = 0;

    // Calculate mean and mode for the specified feature
    for (int i = 0; i < NUM_SAMPLES; i++) {
        sum += dataZoo[i].features[whichFeature - 1];
        featureCount[dataZoo[i].features[whichFeature - 1]]++;
        if (featureCount[dataZoo[i].features[whichFeature - 1]] > maxCount) {
            maxCount = featureCount[dataZoo[i].features[whichFeature - 1]];
            modeValue = dataZoo[i].features[whichFeature - 1];
        }
    }

    *mean = sum / NUM_SAMPLES;
    *mode = modeValue;

    return 0;
}

// Function to display the class distribution in the dataZoo array
void classDistribution(struct Animal dataZoo[NUM_SAMPLES]) {

    int classCounts[10] = {0};
    int maxCount = 0;

    // Count the occurrences of each class in the dataZoo array
    for (int i = 0; i < NUM_SAMPLES; i++) {
        int classIndex = dataZoo[i].classLabel - 1;
        classCounts[classIndex]++;
    }

    // Display the class distribution using asterisks
    for (int i = 0; i < 10; i++) {
        if (classCounts[i] > maxCount) {
            maxCount = classCounts[i];
        }
    }

    // Display asterisks for each class distribution row
    for (int row = maxCount; row > 0; row--) {
        for (int col = 0; col < 10; col++) {
            if (classCounts[col] > 0) {
                if (row <= classCounts[col]) {
                    printf("   *       ");
                } else {
                    printf("           ");
                }
            }
        }
        printf("\n");
    }

    // Display the counts for each class
    for (int col = 0; col < 3; col++) {
        if (classCounts[col] > 0) {
            printf("  (%d)     ", classCounts[col]);
        }
    }

    for (int col = 3; col < 5; col++) {
        if (classCounts[col] > 0) {
            printf("   (%d)    ", classCounts[col]);
        }
    }

    for (int col = 5; col < 7; col++) {
        if (classCounts[col] > 0) {
            printf("    (%d)    ", classCounts[col]);
        }
    }
    printf("\n");

    // Display class labels
    for (int col = 0; col < 10; col++) {
        if (classCounts[col] > 0) {
            printf("Class %d    ", col + 1);
        }
    }
    printf("\n");
}

// Function to calculate the Euclidean distance between two feature vectors
float euclideanDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]) {

    float sum = 0.0;

    // Calculate the sum of squared differences for each feature
    for (int i = 0; i < NUM_FEATURES; i++) {
        float diff = vector1[i] - vector2[i];
        sum += diff * diff;
    }

    float distance = sqrt(sum);

    return distance;
}

// Function to calculate the Hamming distance between two feature vectors
int hammingDistance(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]) {

    int distance = 0;

    // Count the differing features between the two vectors
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (vector1[i] != vector2[i]) {
            distance++;
        }
    }

    return distance;
}

// Function to calculate Jaccard similarity between two feature vectors
float jaccardSimilarity(int vector1[NUM_FEATURES], int vector2[NUM_FEATURES]) {

    int matches11 = 0;
    int matches00 = 0;

    // Count the matching 1-1 and 0-0 pairs for Jaccard similarity
    for (int i = 0; i < NUM_FEATURES; i++) {
        if (vector1[i] == 1 && vector2[i] == 1) {
            matches11++;
        }

        if (vector1[i] == 0 && vector2[i] == 0) {
            matches00++;
        }
    }

    if (NUM_FEATURES - matches00 == 0) {
        return 0.0;
    }

    return (float)matches11 / (NUM_FEATURES - matches00);
}


// Function to find k nearest neighbors for a new sample using a specified distance function
void findKNearestNeighbors(struct Animal dataZoo[NUM_SAMPLES], int newSample[NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors[NUM_SAMPLES]) {

    float distances[NUM_SAMPLES];

    // Calculate distances from the new sample to each dataZoo sample using the specified distance function
    for (int i = 0; i < NUM_SAMPLES; i++) {
        switch (whichDistanceFunction) {
            case 1:
                distances[i] = euclideanDistance(dataZoo[i].features, newSample);
                break;
            case 2:
                distances[i] = hammingDistance(dataZoo[i].features, newSample);
                break;
            case 3:
                distances[i] = jaccardSimilarity(dataZoo[i].features, newSample);
                break;
            default:
                printf("Invalid distance function index.\n");
                return;
        }
    }

    int indices[NUM_SAMPLES];
    for (int i = 0; i < NUM_SAMPLES; i++) {
        indices[i] = i;
    }

    // Sort the distances (code for sorting was inspired by code generated by ChatGPT) 
    // Alse keep track of the corresponding indices
    for (int i = 0; i < NUM_SAMPLES - 1; i++) {
        for (int j = 0; j < NUM_SAMPLES - i - 1; j++) {
            if (distances[j] > distances[j + 1]) {
                float tempDist = distances[j];
                distances[j] = distances[j + 1];
                distances[j + 1] = tempDist;
                int tempIndex = indices[j];
                indices[j] = indices[j + 1];
                indices[j + 1] = tempIndex;
            }
        }
    }

    // Store the indices of the k nearest neighbors
    for (int i = 0; i < k; i++) {
        kNearestNeighbors[i] = indices[i];
    }
}

// Function to predict the class of a new sample based on its k nearest neighbors
int predictClass(struct Animal dataZoo[NUM_SAMPLES], int neighborsForNewSample[NUM_SAMPLES], int newSample[NUM_FEATURES], int k) {

    int classCounts[10] = {0};

    // Count occurrences of each class among the k nearest neighbors
    for (int i = 0; i < k; i++) {
        int neighborIndex = neighborsForNewSample[i];
        int classLabel = dataZoo[neighborIndex].classLabel;
        classCounts[classLabel - 1]++;
    }

    // Find the class with the highest count and predict it as the class of the new sample
    int maxCount = 0;
    int predictedClass = -1;
    for (int i = 0; i < 10; i++) {
        if (classCounts[i] > maxCount) {
            maxCount = classCounts[i];
            predictedClass = i + 1;
        }
    }

    return predictedClass;
}

// Function to calculate the accuracy of the classification model using test data
float findAccuracy(struct Animal dataZoo[NUM_SAMPLES], struct Animal testData[NUM_TEST_DATA], int k) {

    int correctPredictions = 0;

    // Evaluate accuracy using test data
    for (int i = 0; i < NUM_TEST_DATA; i++) {
        struct Animal testSample = testData[i];
        int neighborsForNewSample[NUM_SAMPLES];
        findKNearestNeighbors(dataZoo, testSample.features, k, 1, neighborsForNewSample);
        int predictedClass = predictClass(dataZoo, neighborsForNewSample, testSample.features, k);

        if (predictedClass == testSample.classLabel) {
            correctPredictions++;
        }
    }

    float accuracy = ((float)correctPredictions / NUM_TEST_DATA) * 100.0;
    
    return accuracy;
}