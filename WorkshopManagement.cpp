#include "WorkshopManagement.h"
#include <iostream>

using namespace std;

workshops* head = NULL;
registrationOfWorkshops* headBooking = NULL;

void initializeQueue(queueVariable& q) {
	q.front = NULL;
	q.rear = NULL;
}

void enQueue(queueVariable& q, string name, string w) {
	QNode* newCustomer = new QNode();
	newCustomer->customerName = name;
	newCustomer->workShop = w;
	newCustomer->next = NULL;
	if (q.rear == NULL) {
		q.front = newCustomer;
		q.rear = newCustomer;
	}
	else {
		q.rear->next = newCustomer;
		q.rear = newCustomer;
	}
	cout << name << " Added in waiting Queue of workshop " << w << " due to houseful.\n";
	cout << endl;
}

string deQueue(queueVariable& q) {

	if (q.front == NULL) {
		return "";
	}

	QNode* temp = q.front;
	string name = temp->customerName;
	q.front = temp->next;
	if (q.front == NULL) {
		q.rear = NULL;
	}
	delete(temp);
	return name;
}


void addWorkshop(string name, int seat) {
	workshops* newWorkshop = new workshops();
	newWorkshop->workshopName = name;
	newWorkshop->seats = seat;
	newWorkshop->registeredCustomer = 0;
	newWorkshop->next = NULL;
	initializeQueue(newWorkshop->waitingList);
	if (head == NULL) {
		head = newWorkshop;
	}
	else {
		workshops* temp = head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newWorkshop;
	}
	cout << name << " workshop is added.\n";
}

void displayAllWorkshops() {
	if (head == NULL) {
		cout << "No Workshop Added Yet!";
		return;
	}
	workshops* ptr = head;
	while (ptr != NULL) {
		cout << "Workshop Name:" << ptr->workshopName << " |Workshop Seats:"
			<< ptr->seats << " |Registered Seats:" << ptr->registeredCustomer << endl;
		ptr = ptr->next;
	}
	cout << endl;
}
void registrationDo(string name, string WName) {
	registrationOfWorkshops* newBooking = new registrationOfWorkshops();
	newBooking->name = name;
	newBooking->nameWorkshop = WName;
	newBooking->next = NULL;
	if (headBooking == NULL) {
		headBooking = newBooking;
		return;
	}
	registrationOfWorkshops* temp = headBooking;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = newBooking;

}

bool deleteRegistration(string name, string WName) {
	if (headBooking == NULL) {
		cout << "No Booking Done Yet.\n";
		return false;
	}

	if (headBooking->name == name && headBooking->nameWorkshop == WName) {
		registrationOfWorkshops* temp = headBooking;
		headBooking = temp->next;
		delete(temp);
		cout << "Registration Cancel.\n";
		return true;
	}

	registrationOfWorkshops* temp = headBooking;
	while (temp->next != NULL) {
		if (temp->next->name == name && temp->next->nameWorkshop == WName) {

			registrationOfWorkshops* temp1 = temp->next;
			temp->next = temp1->next;
			delete(temp1);
			cout << "Registration Cancel.\n";
			return true;
		}
		temp = temp->next;
	}

	cout << name << " not Booked in this workshop.\n";
	return false;

}


workshops* findWorkshop(string name) {

	if (head == NULL) {
		return NULL;
	}

	workshops* ptr = head;
	while (ptr != NULL) {
		if (ptr->workshopName == name) {

			return ptr;
		}
		ptr = ptr->next;
	}

	return NULL;

}

void bookWorkshop(string name, string workshopname) {
	workshops* temp = findWorkshop(workshopname);
	if (temp == NULL) {
		cout << "Workshop You trying to Book Not Found!.\n";
		return;
	}
	if (temp->seats > temp->registeredCustomer) {
		temp->registeredCustomer++;
		registrationDo(name, workshopname);
		cout << name << " Successfully Book Seat of " << temp->workshopName << " .\n";
	}
	else {
		enQueue(temp->waitingList, name, workshopname);
	}
}

void cancelWorkshop(string name, string workshopname) {
	workshops* temp = findWorkshop(workshopname);
	if (temp == NULL) {
		cout << "Workshop Not Found!.\n";
		return;
	}
	if (deleteRegistration(name, workshopname)) {

		temp->registeredCustomer--;
		string nextPerson = deQueue(temp->waitingList);
		if (nextPerson == "") {
			cout << "No one in waiting list. Seats are available.\n";
		}
		else {
			temp->registeredCustomer++;
			cout << nextPerson << " seat is moving from waiting queue to Booked.\n";
			registrationDo(nextPerson, workshopname);
		}
	}
	else {
		cout << "Your Booking Not Found...\n";
	}
}

void displayAllRegistration() {
	if (headBooking == NULL) {
		cout << "No Book is Done Yet.\n";
		return;
	}
	registrationOfWorkshops* ptr = headBooking;
	while (ptr != NULL) {
		cout << "Name:" << ptr->name << " | Workshop Name:" << ptr->nameWorkshop << endl;
		ptr = ptr->next;
	}
	cout << endl;
}

void searchRegistrationOfWorkshop(string WName) {
	workshops* temp = findWorkshop(WName);
	if (temp == NULL) {
		cout << "Workshop Not Found!.\n";
		return;
	}
	if (headBooking == NULL) {
		cout << "No Book is Done Yet.\n";
		return;
	}
	registrationOfWorkshops* ptr = headBooking;
	bool found = false;
	while (ptr != NULL) {
		if (WName == ptr->nameWorkshop) {
			found = true;
			cout << "Name:" << ptr->name << " | Workshop Name:" << ptr->nameWorkshop << endl;
		}
		ptr = ptr->next;
	}
	if (!found) {
		cout << "No Booking is Done Yet.\n";
	}
	cout << endl;
}

void searchUserRegistration(string userName) {
	if (headBooking == NULL) {
		cout << "No Book is Done Yet.\n";
		return;
	}
	registrationOfWorkshops* ptr = headBooking;
	bool found = false;
	while (ptr != NULL) {
		if (userName == ptr->name) {
			found = true;
			cout << "Name:" << ptr->name << " | Workshop Name:" << ptr->nameWorkshop << endl;
		}
		ptr = ptr->next;
	}
	if (!found) {
		cout << "Booking Not Found!.\n";
	}
	cout << endl;
}

void displayWaitingList(string workshop) {
	workshops* temp = findWorkshop(workshop);
	if (temp == NULL) {
		cout << "Workshop Not Found!.\n";
		return;
	}
	QNode* ptr = temp->waitingList.front;
	if (ptr == NULL) {
		cout << "No one is in Waiting List.\n";
		return;
	}
	while (ptr != NULL) {
		cout << "Name:" << ptr->customerName << " |Workshop Name:" << ptr->workShop << endl;
		ptr=ptr->next;
	}
	cout << endl;
}

void showWorkshopsWithLessSeats() {
	if (head == NULL) {
		cout << "No Workshop Added Yet!";
		return;
	}
	workshops* ptr = head;
	bool found = false;
	while (ptr != NULL) {
		int remainingSeats = ptr->seats - ptr->registeredCustomer;
		if (remainingSeats <= 5) {
			found = true;
			cout << "Workshop Name:" << ptr->workshopName << " |Workshop Seats:"
				<< ptr->seats << " |Registered Seats:" << ptr->registeredCustomer << endl;
		}
		
		ptr = ptr->next;
	}
	if (!found) {
		cout << "No Workshop is Found with less seats.\n";
	}
	
	cout << endl;
}