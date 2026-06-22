#include "PlantManagement.h"
#include <iostream>

using namespace std;

plantManagement* root = NULL;

plantManagement* addPlant(string name, double sunLight, double water) {
	plantManagement* newPlant = new plantManagement;
	newPlant->plantName = name;
	newPlant->growthRate = 5;
	newPlant->sunlightRequired = sunLight;
	newPlant->waterNeed = water;
	newPlant->status = "Thriving";
	newPlant->left = NULL;
	newPlant->right = NULL;
	newPlant->height = 0;

	return newPlant;
}

int getHeight(plantManagement* root) {
	if (root == NULL) {
		return -1;
	}

	return root->height;
}

int maxHeight(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}

int getBalance(plantManagement* root) {
	if (root == NULL) {
		return 0;
	}

	return getHeight(root->left) - getHeight(root->right);
}

plantManagement* rightRotation(plantManagement* root) {
	if (root == NULL || root->left == NULL)
		return root;
	plantManagement* child = root->left;
	plantManagement* childRight = child->right;

	child->right = root;
	root->left = childRight;

	root->height = 1 + maxHeight(getHeight(root->left), getHeight(root->right));
	child->height = 1 + maxHeight(getHeight(child->left), getHeight(child->right));

	return child;
}

plantManagement* leftRotation(plantManagement* root) {
	if (root == NULL || root->right == NULL)
		return root;
	plantManagement* child = root->right;
	plantManagement* childLeft = child->left;

	child->left = root;
	root->right = childLeft;

	root->height = 1 + maxHeight(getHeight(root->left), getHeight(root->right));
	child->height = 1 + maxHeight(getHeight(child->left), getHeight(child->right));

	return child;
}
plantManagement* insertPlant(plantManagement* root, string name, double sunLight, double water) {
	if (root == NULL) {
		return addPlant(name, sunLight, water);
	}

	if (name < root->plantName) {
		root->left = insertPlant(root->left, name, sunLight, water);
	}

	else if (name > root->plantName) {
		root->right = insertPlant(root->right, name, sunLight, water);
	}
	else {
		return root;
	}

	root->height = 1 + maxHeight(getHeight(root->left), getHeight(root->right));

	int balance = getBalance(root);



	//LL Case
	if (balance > 1 && name < root->left->plantName) {
		return rightRotation(root);
	}
	//LR Case
	if (balance > 1 && name > root->left->plantName) {
		root->left = leftRotation(root->left);
		return rightRotation(root);
	}

	//RR Case
	if (balance < -1 && name>root->right->plantName) {
		return leftRotation(root);
	}
	//RL Case
	if (balance < -1 && name < root->right->plantName) {
		root->right = rightRotation(root->right);
		return leftRotation(root);
	}

	return root;

}

plantManagement* searchPlantByName(plantManagement* root, string name) {
	if (root == NULL) {
		return NULL;
	}

	if (root->plantName == name) {
		return root;
	}

	if (root->plantName > name) {
		return searchPlantByName(root->left, name);
	}

	else {
		return searchPlantByName(root->right, name);
	}
}

double getValidSunlight() {
	double actualSunLight;
	cout << "Enter the SunLight:";
	cin >> actualSunLight;
	while (cin.fail() || actualSunLight < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input.Enter the SunLight:";
		cin >> actualSunLight;
	}

	return actualSunLight;
}

double getValidWater() {
	double actualWater;
	cout << "Enter the Water:";
	cin >> actualWater;
	while (cin.fail() || actualWater < 0) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input.Enter the Water:";
		cin >> actualWater;
	}
	return actualWater;
}
void updateCondition(plantManagement* root, string name) {
	plantManagement* temp = searchPlantByName(root, name);
	if (temp == NULL) {
		cout << "Plant Not Found.\n";
		return;
	}
	double actualWater, actualSunLight;

	actualSunLight = getValidSunlight();

	actualWater = getValidWater();


	if (temp->sunlightRequired == actualSunLight && actualWater == temp->waterNeed) {
		temp->growthRate = 5;
	}
	else if (temp->sunlightRequired == actualSunLight || actualWater == temp->waterNeed) {
		temp->growthRate = 2.5;
	}
	else {
		temp->growthRate = 0;
	}

	if (temp->growthRate == 5) {
		temp->status = "Thriving";
	}
	else if (temp->growthRate == 2.5) {
		temp->status = "Struggling";
	}
	else {
		temp->status = "Dead";

	}
	cout << "Updation Done SucessFully.\n";
}

void displayAllPlant(plantManagement* root) {
	if (root != NULL) {
		displayAllPlant(root->left);
		cout << "Plant Name:" << root->plantName << " |Plant SunLight Requirment:" << root->sunlightRequired <<
			" |Plant Water Requirment:" << root->waterNeed << " liter |Plant Growth Rate:" << root->growthRate << " |Plant Status:" << root->status << endl;
		displayAllPlant(root->right);
	}
}

void showStrugglingPlant(plantManagement* root, bool& found) {
	if (root != NULL) {
		showStrugglingPlant(root->left, found);
		if (root->status == "Struggling") {
			cout << "Plant Name:" << root->plantName << " |Plant SunLight Requirment:" << root->sunlightRequired << 
				" |Plant Water Requirment:" << root->waterNeed << " liter |Plant Growth Rate:" << root->growthRate << " |Plant Status:" << root->status << endl;
			found = true;
		}
		showStrugglingPlant(root->right, found);
	}
}

bool isValidName(string name) {
	if (name.empty()) return false;

	for (int i = 0; i < name.length(); i++) {
		char c = name[i];


		if (!((c >= 'A' && c <= 'Z') ||
			(c >= 'a' && c <= 'z') ||
			c == ' ')) {
			return false;
		}
	}

	return true;
}
