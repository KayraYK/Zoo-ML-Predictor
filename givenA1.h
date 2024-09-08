
/*
Student Name: Kayra Kazanci
Student ID: 1276539
Due Date: February 2, 2024
Course: CIS*2500
I have exclusive control over this submission via my password.
By including this header comment, I certify that:
1) I have read and understood the policy on academic integrity.
2) I have completed Moodle's module on academic integrity.
3) I have achieved at least 80% on the academic integrity quiz
I assert that this work is my own. I have appropriate acknowledged
any and all material that I have used, be it directly quoted or
paraphrased. Furthermore, I certify that this assignment was written
by me in its entirety.
*/


#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NUM_FEATURES 16   // not including animal name and class label
#define NUM_SAMPLES 100      // total number of samples / rows in the given zoo dataset
#define NUM_CLASSES 7        // total number of class labels in zoo dataset
#define NUM_TEST_DATA 20     // total number of samples / rows in the test dataset - you need this for task 9
#define MAX_LENGTH_ANIMAL_NAME 50

struct Animal {
   
   char animalName [MAX_LENGTH_ANIMAL_NAME];
   int features [NUM_FEATURES];
   int classLabel;
   
};

/* Task 1 */
int readFromFile (char fName [30], struct Animal dataZoo [NUM_SAMPLES]) ;

/* Task 2 */
int generateStatisticsFeatureX (struct Animal dataZoo [NUM_SAMPLES], int whichFeature, float * mean, int * mode);

/* Task 3 */
void classDistribution (struct Animal dataZoo [NUM_SAMPLES]);

/* Task 4 */
float euclideanDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]);

/* Task 5 */
int hammingDistance (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]);

/* Task 6 */
float jaccardSimilarity (int vector1 [NUM_FEATURES], int vector2 [NUM_FEATURES]);

/* Task 7 */
void findKNearestNeighbors (struct Animal dataZoo [NUM_SAMPLES], int newSample [NUM_FEATURES], int k, int whichDistanceFunction, int kNearestNeighbors [NUM_SAMPLES]);

/* Task 8 */
int predictClass (struct Animal dataZoo [NUM_SAMPLES], int neighborsForNewSample [NUM_SAMPLES], int newSample [NUM_FEATURES], int k);

/* Task 9 */
float findAccuracy (struct Animal dataZoo [NUM_SAMPLES], struct Animal testData [NUM_TEST_DATA], int k);