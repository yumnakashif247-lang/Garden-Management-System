#ifndef PROCUREMENT_H
#define PROCUREMENT_H

struct Supply {
    char name[30];
    int cost;
    int benefit;
};

void printItems(Supply items[], int n);
void knapsack(Supply items[], int n, int budget);

#endif