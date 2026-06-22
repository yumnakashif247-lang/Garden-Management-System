#ifndef WORKSHOPMANAGEMENT_H
#define WORKSHOPMANAGEMENT_H

#include <string>
using namespace std;

struct QNode {
    string customerName;
    string workShop;
    QNode* next;
};

struct queueVariable {
    QNode* front;
    QNode* rear;
};

struct workshops {
    string workshopName;
    int seats;
    int registeredCustomer;

    queueVariable waitingList;
    workshops* next;
};

struct registrationOfWorkshops {
    string name;
    string nameWorkshop;
    registrationOfWorkshops* next;
};

extern workshops* head;
extern registrationOfWorkshops* headBooking;

void addWorkshop(string name, int seat);
void displayAllWorkshops();
void bookWorkshop(string name, string workshopname);
void cancelWorkshop(string name, string workshopname);
void displayAllRegistration();
void searchRegistrationOfWorkshop(string WName);
void searchUserRegistration(string userName);
void displayWaitingList(string workshop);
void showWorkshopsWithLessSeats();

#endif