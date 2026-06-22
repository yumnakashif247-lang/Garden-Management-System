#include "Procurement.h"
#include <iostream>
#include <iomanip>

using namespace std;

const int MAX_ITEMS = 20;
const int MAX_BUDGET = 5001;

int dp[MAX_ITEMS + 1][MAX_BUDGET];

int maxOf(int a, int b) {
	if (a > b) {
		return a;
	}
	else {
		return b;
	}

}

void printItems(Supply items[], int n) {
	cout << "\n+----------------------+--------+---------+\n";
	cout << "| Supply Item          |  Cost  | Benefit |\n";
	cout << "+----------------------+--------+---------+\n";
	for (int i = 0; i < n; i++) {
		cout << "| " << left << setw(21) << items[i].name
			<< "| " << right << setw(6) << items[i].cost
			<< " | " << setw(7) << items[i].benefit << " |\n";
	}
	cout << "+----------------------+--------+---------+\n";
}

void knapsack(Supply items[], int n, int budget) {

	for (int i = 0; i <= n; i++)
		for (int w = 0; w <= budget; w++)
			dp[i][w] = 0;

	for (int i = 1; i <= n; i++) {
		int c = items[i - 1].cost;
		int b = items[i - 1].benefit;

		for (int w = 0; w <= budget; w++) {
			dp[i][w] = dp[i - 1][w];
			if (c <= w)
				dp[i][w] = maxOf(dp[i][w], dp[i - 1][w - c] + b);
		}
	}

	int maxBenefit = dp[n][budget];

	Supply selected[MAX_ITEMS];
	int selCount = 0;
	int w = budget;

	for (int i = n; i >= 1; i--) {
		if (dp[i][w] != dp[i - 1][w]) {
			selected[selCount++] = items[i - 1];
			w -= items[i - 1].cost;
		}
	}

	int totalCost = 0;
	int totalBenefit = 0;

	cout << "+================================================+\n";
	cout << "|         OPTIMAL PROCUREMENT PLAN               |\n";
	cout << "+================================================+\n";
	cout << "\n  Selected Supplies:\n";
	cout << "  ------------------------------------------\n";
	for (int i = 0; i < selCount; i++) {
		cout << "  [+] " << left << setw(22) << selected[i].name
			<< "  Cost: " << setw(4) << selected[i].cost
			<< "  Benefit: " << selected[i].benefit << "\n";
		totalCost += selected[i].cost;
		totalBenefit += selected[i].benefit;
	}

	cout << "  ------------------------------------------\n";
	cout << "  Total Cost Spent  : " << totalCost << " / " << budget << " PKR\n";
	cout << "  Remaining Budget  : " << (budget - totalCost) << " PKR\n";
	cout << "  Maximum Benefit   : " << maxBenefit << "\n\n";
}

