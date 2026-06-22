#include <iostream>
#include "PlantManagement.h"
#include "WorkshopManagement.h"
#include "Procurement.h"

using namespace std;

int main()
{
    int choice,seat;
string name,workshop;
bool found;
double sunlight, water;
cout << "\t----------------------------------------\n";
cout << "\t====== GARDEN MANAGEMENT SYSTEM ======\n";
cout << "\t----------------------------------------\n";
cout << endl;

do {
	cout << "\t----- PROGRAM MENU -----\n";
	cout << "1. Add Plant.\n";
	cout << "2. Display All Plants\n";
	cout << "3. Update Plant Condition.\n";
	cout << "4. Show Struggling Plant.\n";
	cout << "5. Search Plant By Name.\n";
	cout << "6. Add Workshop.\n";
	cout << "7. Display All Workshop.\n";
	cout << "8. Book Workshop.\n";
	cout << "9. Cancel Booking.\n";
	cout << "10. Display All Bookings.\n";
	cout << "11. Search Booking of Workshop.\n";
	cout << "12. Search Booking By Username.\n";
	cout << "13. Display Waiting List of Workshop.\n";
	cout << "14. Display Workshop with Less Seats.\n";
	cout << "15. Efficient Resource Procurement.\n";
	cout << "16. Exit.\n";
	cout << "Enter Your Choice:";
	cin >> choice;

	if (cin.fail()) {
		cin.clear();
		cin.ignore(1000, '\n');
		cout << "Invalid Input!\n";
		continue;
	}

	cin.ignore();
	cout << endl;

	if (choice == 1) {
		cout << "\t+================================================+\n";
		cout << "\t|                INSERTING NEW PLANT              |\n";
		cout << "\t+================================================+\n";
		
		cout << "Enter Name of the Plant:";
		getline(cin, name);
		while (!isValidName(name)) {
			cout << "Invalid plant name! Only letters are allowed.\n";
			cout << "Enter Name of Plant Again:";
			getline(cin, name);
		}
		sunlight = getValidSunlight();
		water = getValidWater();
		root= insertPlant(root, name, sunlight, water);
		cout << "Plant with Name " << name << " Added Successfully.\n";
		cout << endl;

	}
	else if (choice == 2) {
		cout << "\t+================================================+\n";
		cout << "\t|                DISPLAY ALL PLANTS             |\n";
		cout << "\t+================================================+\n";
		
		displayAllPlant(root);
		cout << endl;
	}
	else if (choice == 3) {
		cout << "\t+================================================+\n";
		cout << "\t|            UPDATE PLANT GROWTH RATE             |\n";
		cout << "\t+================================================+\n";
		cout << "Enter Name of the Plant:";
		getline(cin, name);
		while (!isValidName(name)) {
			cout << "Invalid plant name! Only letters are allowed.\n";
			cout << "Enter Name of Plant Again:";
			getline(cin, name);
		}
		updateCondition(root, name);
		cout << endl;
	}
	else if (choice == 4) {
		found = false;
		cout << "\t+================================================+\n";
		cout << "\t|              SHOW STRUGGLING PLANT             |\n";
		cout << "\t+================================================+\n";
		
		showStrugglingPlant(root, found);

		if (!found) {
			cout << "No struggling plants found.\n";
		}
		cout << endl;
	}
	else if (choice == 5) {
		cout << "\t+================================================+\n";
		cout << "\t|               SEARCH PLANT BY NAME             |\n";
		cout << "\t+================================================+\n";

		cout << "Enter Plant Name: ";
		getline(cin, name);
		while (!isValidName(name)) {
			cout << "Invalid name! Only letters allowed.\n";
			cout << "Enter Plant Name again: ";
			getline(cin, name);
		}
		plantManagement* find = searchPlantByName(root, name);

		if (find == NULL) {
			cout << "Plant Not Found.\n";
		}
		else {
			cout << "Plant Name:" << find->plantName << " |Plant SunLight Requirment:" << find->sunlightRequired << 
				" |Plant Water Requirment:" << find->waterNeed << " |Plant Growth Rate:" << find->growthRate << " |Plant Status:" << find->status << endl;
		}

		cout << endl;
	}
	else if (choice == 6) {
		cout << "\t+================================================+\n";
		cout << "\t|                       ADD WORKSHOP             |\n";
		cout << "\t+================================================+\n";
		
		cout << "Enter name of the Workshop:";
		getline(cin, workshop);
		while (!isValidName(workshop)) {
			cout << "Invalid name! Only letters allowed.\n";
			cout << "Enter Workshop Name again: ";
			getline(cin, workshop);
		}
		cout << "Enter Number of Seats in Workshop:";
		cin >> seat;
		while (cin.fail() || seat < 0) {
			cin.clear();
			cin.ignore(1000, '\n');
			cout << "Invalid Input! Enter seats Again:";
			cin >> seat;
		}
		addWorkshop(workshop, seat);
		cout << endl;
	}
	else if (choice == 7) {
		cout << "\t+================================================+\n";
		cout << "\t|                       ALL WORKSHOPs            |\n";
		cout << "\t+================================================+\n";
		
		displayAllWorkshops();
		cout << endl;

	}
	else if (choice == 8) {
		cout << "\t+================================================+\n";
		cout << "\t|           BOOKING SEAT FOR WORKSHOP             |\n";
		cout << "\t+================================================+\n";
		
		cout << "Enter your name: ";
		getline(cin, name);
		while (!isValidName(name)) {
			cout << "Invalid name! Only letters allowed.\n";
			cout << "Enter your Name again: ";
			getline(cin, name);
		}

		cout << "Enter workshop name: ";
		getline(cin, workshop);
		while (!isValidName(workshop)) {
			cout << "Invalid name! Only letters allowed.\n";
			cout << "Enter Workshop Name again: ";
			getline(cin, workshop);
		}


		bookWorkshop(name, workshop);
		cout << endl;
	}
	else if (choice == 9) {
		cout << "\t+================================================+\n";
		cout << "\t|          CANCEL BOOKING OF WORKSHOP             |\n";
		cout << "\t+================================================+\n";

		cout << "Enter your name: ";
		getline(cin, name);
		while (!isValidName(name)) {
			cout << "Invalid name! Only letters allowed.\n";
			cout << "Enter your Name again: ";
			getline(cin, name);
		}

		cout << "Enter workshop name: ";
		getline(cin, workshop);
		while (!isValidName(workshop)) {
			cout << "Invalid name! Only letters allowed.\n";
			cout << "Enter Workshop Name again: ";
			getline(cin, workshop);
		}

		cancelWorkshop(name, workshop);
		cout << endl;
	}
	else if (choice == 10) {
		cout << "\t+================================================+\n";
		cout << "\t|                        ALL BOOKING             |\n";
		cout << "\t+================================================+\n";
	
		displayAllRegistration();
	}
	else if (choice == 11) {
		cout << "\n+================================================+\n";
		cout << "|        BOOKING FOR SPECIFIC WORKSHOP             |\n";
		cout << "+================================================+\n";
		
		cout << "Enter workshop name: ";
		getline(cin, workshop);
		while (!isValidName(workshop)) {
			cout << "Invalid name! Only letters allowed.\n";
			cout << "Enter Workshop Name again: ";
			getline(cin, workshop);
		}
		searchRegistrationOfWorkshop(workshop);
		cout << endl;
	}
	else if (choice == 12) {
		cout << "\t+================================================+\n";
		cout << "\t|           BOOKING OF SPECIFIC USER             |\n";
		cout << "\t+================================================+\n";
		
		cout << "Enter user name: ";
		getline(cin, name);
		while (!isValidName(name)) {
			cout << "Invalid name! Only letters allowed.\n";
			cout << "Enter your Name again: ";
			getline(cin, name);
		}
		searchUserRegistration(name);
		cout << endl;
	}
	else if (choice == 13) {
		cout << "\t+================================================+\n";
		cout << "\t|           WAITING LIST OF WORKSHOP             |\n";
		cout << "\t+================================================+\n";
		
		cout << "Enter workshop name: ";
		getline(cin, workshop);
		while (!isValidName(workshop)) {
			cout << "Invalid name! Only letters allowed.\n";
			cout << "Enter Workshop Name again: ";
			getline(cin, workshop);
		}
		displayWaitingList(workshop);
		cout << endl;
	}
	else if (choice == 14) {
		cout << "\t+================================================+\n";
		cout << "\t|           WORKSHOP WITH LESS SEATS              |\n";
		cout << "\t+================================================+\n";
		showWorkshopsWithLessSeats();
		cout << endl;
	}
	else if (choice == 15) {
		Supply supplies[] = {
	{ "Premium Seeds",           600,   10 },
	{ "Basic Seeds",             200,    4 },
	{ "Organic Fertilizer",      400,    7 },
	{ "Chemical Fertilizer",     300,    5 },
	{ "Digging Tools Set",       500,    8 },
	{ "Hand Trowel",             150,    3 },
	{ "Potting Soil (20kg)",     350,    6 },
	{ "Compost Mix",             250,    5 },
	{ "Drip Irrigation Kit",     700,   11 },
	{ "Watering Can",            100,    2 },
		};

		int n = sizeof(supplies) / sizeof(supplies[0]);

		cout << "\t================================================\n";
		cout << "\t|   Community Garden - Resource Procurement|\n";
		cout << "\t+================================================\n";

		cout << "\nAvailable Supply Items:";
		printItems(supplies, n);

		int budget;
		cout << "\nEnter your budget (PKR): ";
		cin >> budget;

		while (budget <= 0 || budget > 5000) {
			cout << "Please enter a valid budget between 1 and 5000: ";
			cin >> budget;
		}

		cout << "\nFinding best combination for PKR " << budget << "...\n";

		knapsack(supplies, n, budget);

		char choice;
		cout << "Would you like to try a different budget? (y/n): ";
		cin >> choice;

		while (choice == 'y' || choice == 'Y') {
			cout << "Enter new budget (PKR): ";
			cin >> budget;

			while (budget <= 0 || budget > 5000) {
				cout << "Please enter a valid budget between 1 and 5000: ";
				cin >> budget;
			}

			cout << "\nFinding best combination for PKR " << budget << "...\n";
			knapsack(supplies, n, budget);

			cout << "Would you like to try a different budget? (y/n): ";
			cin >> choice;
		}

		cout << "\nThank you for using the Garden Procurement System!\n\n";
		cout << endl;
	}
	else if (choice == 16) {
		cout << "Exit...\n";
	}
	else {
		cout << "Invalid Choice.\n";
	}
} while (choice != 16);

}