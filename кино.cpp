#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <Windows.h>
#include <set>
using namespace std;
double totalSales = 0.0; // Глобальная переменная для хранения общей суммы продаж
int totalticket = 0; // Глобальная переменная для хранения общей суммы продаж
struct Ticket {
    string movieName;
    string showTime;
    double ticketPrice;
    int row;
    int seat;
};
map<int, Ticket> ticketsMap; // Хранение билетов по номеру
set<int> soldTickets;
void chooseTicket() {
    SetConsoleOutputCP(CP_UTF8);
    cout << "Available tickets:" << endl;
    for (const auto& entry : ticketsMap) {
        if (soldTickets.find(entry.first) == soldTickets.end()) {
            cout << entry.first << ": " << entry.second.movieName << " - " << entry.second.showTime <<" Price "<<entry.second.ticketPrice<<"$ " << " row " << entry.second.row << " seat " << entry.second.seat << endl;
        }
    }
}

void orderTicket(int ticketNumber, bool isChild) {
    if (soldTickets.find(ticketNumber) == soldTickets.end()) {
        Ticket selectedTicket = ticketsMap[ticketNumber];
        ofstream outputFile("purchased_tickets.txt", ios::app); // Открываем файл для добавления выбранного билета
        outputFile << "Movie: " << selectedTicket.movieName << endl;
        outputFile << "Show Time: " << selectedTicket.showTime << endl;
        outputFile << "Ticket Price: $" << (isChild ? selectedTicket.ticketPrice / 2 : selectedTicket.ticketPrice) << endl;
        if (isChild == true) {
            outputFile << "Childticket" << endl;
        }
        else {
            outputFile << "Adultticket" << endl;
        }
        outputFile << "Seat: Row " << selectedTicket.row << ", Seat " << selectedTicket.seat << endl;
        outputFile << "-------------------------" << endl;
        double ticketPrice = isChild ? selectedTicket.ticketPrice / 2 : selectedTicket.ticketPrice;

        // Добавляем цену билета к общей сумме продаж
        totalSales += ticketPrice;
        totalticket += 1;
        soldTickets.insert(ticketNumber);
        cout << "Ticket(s) purchased successfully!" << endl;
    }
    else {
        cout << "Error: This ticket has already been sold." << endl;
    }
}


void numSoldTickets() {
    cout << "total tickets sold : " << totalticket << endl;
}

void sumSoldTickets() {
    cout << "Total sales: $" << totalSales << endl;

}

int main() {
    setlocale(LC_ALL, "RU");
    ifstream inputFile("input.txt");

    if (!inputFile) {
        cout << "Error opening input file!" << endl;
        return 1;
    }


    Ticket ticket;
    int ticketNumber = 1; // Начальное значение номера билета

    while (inputFile >> ticket.movieName >> ticket.showTime >> ticket.ticketPrice >>  ticket.row >> ticket.seat) {
        ticketsMap[ticketNumber] = ticket; // Добавляем билет в карту по его номеру
        ticketNumber++;
    }

    int choice;
    do {
        cout << "Choose an option:\n1. Choose a ticket\n2. Order a ticket\n3. Number of sold tickets\n4. Sum of sold tickets\n0. Exit" << endl;
        cin >> choice;

        switch (choice) {
        case 1:
            chooseTicket();
            break;
        case 2:
            int selectedTicketNumber;
            bool isChild;
            cout << "Enter the ticket number you want to order: ";
            cin >> selectedTicketNumber;
            cout << "Is it a child ticket? (1 for yes, 0 for no): ";
            cin >> isChild;
            orderTicket(selectedTicketNumber, isChild);
            break;
        case 3:
            numSoldTickets();
            break;
        case 4:
            sumSoldTickets();
            break;
        case 0:
            cout << "Exiting program..." << endl;
            break;
        default:
            cout << "Invalid option selected." << endl;
        }
    } while (choice != 0);

    inputFile.close();

    return 0;
}
