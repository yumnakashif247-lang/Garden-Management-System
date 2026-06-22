#ifndef PLANTMANAGEMENT_H
#define PLANTMANAGEMENT_H

#include <string>
using namespace std;

struct plantManagement {
    string plantName;
    double growthRate, sunlightRequired, waterNeed;
    int height;
    string status;

    plantManagement* right;
    plantManagement* left;
};

extern plantManagement* root;

plantManagement* insertPlant(plantManagement* root, string name, double sunLight, double water);
plantManagement* searchPlantByName(plantManagement* root, string name);

double getValidSunlight();
double getValidWater();

void updateCondition(plantManagement* root, string name);
void displayAllPlant(plantManagement* root);
void showStrugglingPlant(plantManagement* root, bool& found);

bool isValidName(string name);

#endif