1#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>

struct Expense {
    std::string date;
    std::string description;
    double amount;
};

void saveExpense(const Expense& expense, std::ofstream& file) {
    file << expense.date << ',' << expense.description << ',' << expense.amount << '\n';
}

void loadExpenses(std::vector<Expense>& expenses, std::ifstream& file) {
    Expense expense;
    std::string line;
    
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::getline(iss, expense.date, ',');
        std::getline(iss, expense.description, ',');
        iss >> expense.amount;
        expenses.push_back(expense);
    }
}

void displayExpenses(const std::vector<Expense>& expenses) {
    std::cout << "Date       | Description         | Amount\n";
    std::cout << "----------------------------------------\n";
    
    for (const Expense& expense : expenses) {
        std::cout << std::left << std::setw(11) << expense.date << "| "
                  << std::left << std::setw(20) << expense.description << "| "
                  << std::right << std::setw(10) << std::fixed << std::setprecision(2) << expense.amount << "\n";
    }
}

double calculateTotal(const std::vector<Expense>& expenses) {
    double total = 0.0;
    for (const Expense& expense : expenses) {
        total += expense.amount;
    }
    return total;
}

int main() {
    std::vector<Expense> expenses;
    
    std::ifstream expenseFile("expenses.csv");
    if (expenseFile) {
        loadExpenses(expenses, expenseFile);
        expenseFile.close();
    }
    
    while (true) {
        std::cout << "Expense Tracker\n";
        std::cout << "1. Add Expense\n";
        std::cout << "2. View Expenses\n";
        std::cout << "3. Calculate Total\n";
        std::cout << "4. Exit\n";
        
        int choice;
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        
        switch (choice) {
            case 1: {
                Expense expense;
                std::cout << "Enter date (YYYY-MM-DD): ";
                std::cin >> expense.date;
                std::cout << "Enter description: ";
                std::cin.ignore(); // Clear newline from previous input
                std::getline(std::cin, expense.description);
                std::cout << "Enter amount: ";
                std::cin >> expense.amount;
                expenses.push_back(expense);
                
                std::ofstream expenseFile("expenses.csv", std::ios::app);
                if (expenseFile) {
                    saveExpense(expense, expenseFile);
                    expenseFile.close();
                }
                
                break;
            }
            case 2:
                displayExpenses(expenses);
                break;
            case 3:
                std::cout << "Total Expenses: $" << calculateTotal(expenses) << "\n";
                break;
            case 4:
                std::cout << "Exiting...\n";
                return 0;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    }
    
    return 0;
}
