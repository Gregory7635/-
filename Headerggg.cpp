#include "Headerggg.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
void chooseTicket() {
    SetConsoleOutputCP(CP_UTF8);
    std::cout << "Available tickets:" << std::endl;
    for (const auto& entry : ticketsMap) {
        if (soldTickets.find(entry.first) == soldTickets.end()) {
            std::cout << entry.first << ": " << entry.second.movieName << " - " << entry.second.showTime << " Price " << entry.second.ticketPrice << "$ " << " row " << entry.second.row << " seat " << entry.second.seat << std::endl;
        }
    }
}
double totalSales = 0;
int totalticket = 0;
std::map<int, Ticket> ticketsMap;
std::set<int> soldTickets;
void orderTicket(int ticketNumber, bool isChild) {
    if (soldTickets.find(ticketNumber) == soldTickets.end()) {
        Ticket selectedTicket = ticketsMap[ticketNumber];
        std::ofstream outputFile("purchased_tickets.txt", std::ios::app);
        outputFile << "Movie: " << selectedTicket.movieName << std::endl;
        outputFile << "Show Time: " << selectedTicket.showTime << std::endl;
        outputFile << "Ticket Price: $" << (isChild ? selectedTicket.ticketPrice / 2 : selectedTicket.ticketPrice) << std::endl;
        if (isChild == true) {
            outputFile << "Childticket" << std::endl;
        }
        else {
            outputFile << "Adultticket" << std::endl;
        }
        outputFile << "Seat: Row " << selectedTicket.row << ", Seat " << selectedTicket.seat << std::endl;
        outputFile << "-------------------------" << std::endl;
        double ticketPrice = isChild ? selectedTicket.ticketPrice / 2 : selectedTicket.ticketPrice;
        totalSales += ticketPrice;
        totalticket += 1;
        soldTickets.insert(ticketNumber);
        std::cout << "Ticket(s) purchased successfully!" << std::endl;
    }
    else {
        std::cout << "Error: This ticket has already been sold." << std::endl;
    }
}

void numSoldTickets() {
    std::cout << "total tickets sold : " << totalticket << std::endl;
}

void sumSoldTickets() {
    std::cout << "Total sales: $" << totalSales << std::endl;
}