#include "Headerggg.h"
#include <iostream>
#include <fstream>

int main() {
    setlocale(LC_ALL, "RU");
    std::ifstream inputFile("input.txt");

    if (!inputFile) {
        std::cout << "Error opening input file!" << std::endl;
        return 1;
    }

    Ticket ticket;
    int ticketNumber = 1;

    while (inputFile >> ticket.movieName >> ticket.showTime >> ticket.ticketPrice >> ticket.row >> ticket.seat) {
        ticketsMap[ticketNumber] = ticket;
        ticketNumber++;
    }

    int choice;
    do {
        std::cout << "Choose an option:\n1. Choose a ticket\n2. Order a ticket\n3. Number of sold tickets\n4. Sum of sold tickets\n0. Exit" << std::endl;
        std::cin >> choice;

        switch (choice) {
        case 1:
            chooseTicket();
            break;
        case 2:
            int selectedTicketNumber;
            bool isChild;
            std::cout << "Enter the ticket number you want to order: ";
            std::cin >> selectedTicketNumber;
            std::cout << "Is it a child ticket? (1 for yes, 0 for no): ";
            std::cin >> isChild;
            orderTicket(selectedTicketNumber, isChild);
            break;
        case 3:
            numSoldTickets();
            break;
        case 4:
            sumSoldTickets();
            break;
        case 0:
            std::cout << "Exiting program..." << std::endl;
            break;
        default:
            std::cout << "Invalid option selected." << std::endl;
        }
    } while (choice != 0);

    inputFile.close();

    return 0;
}