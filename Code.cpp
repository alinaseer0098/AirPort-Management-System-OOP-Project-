#include <iostream>
#include <string>
#include <fstream>
using namespace std;

// =========================
// PASSENGER CLASS
// =========================
class Passenger {
private:
    string name;
    string passport;
    string seatClass;
    int age;
    double fare;

public:
    Passenger() { 
        fare = 0;
        seatClass = "Economy";
        age = 0;
    }

    Passenger(string n, string p, string sc, int a, double f) {
        name = n;
        passport = p;
        seatClass = sc;
        age = a;
        fare = f;
    }

    void display() const {
        cout << name;
        for(int i = name.length(); i < 25; i++) cout << " ";
        cout << passport;
        for(int i = passport.length(); i < 15; i++) cout << " ";
        cout << seatClass;
        for(int i = seatClass.length(); i < 12; i++) cout << " ";
        cout << "PKR " << (int)fare << endl;
    }

    string getName() const { return name; }
    string getPassport() const { return passport; }
    string getSeatClass() const { return seatClass; }
    int getAge() const { return age; }
    double getFare() const { return fare; }
};

// =========================
// FLIGHT CLASS
// =========================
class Flight {
private:
    string flightID;
    string airline;
    string source;
    string destination;
    string departure;
    double ticketPrice;

    Passenger passengers[50];
    int passengerCount;
    
    double calculatePrice(string dest, string air) {
        double basePrice = 0;
        
        if (dest == "Karachi" || dest == "Lahore" || dest == "Islamabad") {
            basePrice = 8000;
        }
        else if (dest == "Quetta" || dest == "Peshawar" || dest == "Multan") {
            basePrice = 12000;
        }
        else if (dest == "Dubai" || dest == "Sharjah" || dest == "Abu Dhabi") {
            basePrice = 35000;
        }
        else if (dest == "Jeddah" || dest == "Riyadh" || dest == "Muscat") {
            basePrice = 40000;
        }
        else if (dest == "London" || dest == "Manchester" || dest == "Paris") {
            basePrice = 80000;
        }
        else if (dest == "New York" || dest == "Toronto" || dest == "Chicago") {
            basePrice = 120000;
        }
        else if (dest == "Bangkok" || dest == "Kuala Lumpur" || dest == "Singapore") {
            basePrice = 50000;
        }
        else {
            basePrice = 25000;
        }
        
        double multiplier = 1.0;
        if (air == "Emirates") multiplier = 1.8;
        else if (air == "FlyDubai") multiplier = 1.3;
        else if (air == "AirBlue") multiplier = 1.1;
        else if (air == "PIA") multiplier = 1.0;
        
        return basePrice * multiplier;
    }

public:
    Flight() { 
        passengerCount = 0;
        ticketPrice = 0;
    }

    Flight(string id, string air, string src, string dst, string dep) {
        flightID = id;
        airline = air;
        source = src;
        destination = dst;
        departure = dep;
        passengerCount = 0;
        ticketPrice = calculatePrice(destination, airline);
    }
    
    void saveToFile(ofstream &out) const {
        out << flightID << endl;
        out << airline << endl;
        out << source << endl;
        out << destination << endl;
        out << departure << endl;
        out << ticketPrice << endl;
        out << passengerCount << endl;
        for (int i = 0; i < passengerCount; i++) {
            out << passengers[i].getName() << "|" 
                << passengers[i].getPassport() << "|"
                << passengers[i].getSeatClass() << "|"
                << passengers[i].getAge() << "|"
                << passengers[i].getFare() << endl;
        }
    }

    void loadFromFile(ifstream &in) {
        getline(in, flightID);
        getline(in, airline);
        getline(in, source);
        getline(in, destination);
        getline(in, departure);
        in >> ticketPrice;
        in >> passengerCount;
        in.ignore();
        for (int i = 0; i < passengerCount; i++) {
            string line;
            getline(in, line);
            
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            size_t pos3 = line.find('|', pos2 + 1);
            size_t pos4 = line.find('|', pos3 + 1);
            
            string pname = line.substr(0, pos1);
            string ppass = line.substr(pos1 + 1, pos2 - pos1 - 1);
            string pclass = line.substr(pos2 + 1, pos3 - pos2 - 1);
            int page = stoi(line.substr(pos3 + 1, pos4 - pos3 - 1));
            double pfare = stod(line.substr(pos4 + 1));
            
            passengers[i] = Passenger(pname, ppass, pclass, page, pfare);
        }
    }

    void addPassenger(Passenger p) {
        if (passengerCount < 50) {
            passengers[passengerCount++] = p;
            cout << "\n[SUCCESS] Passenger added successfully!\n";
        } else {
            cout << "\n[FULL] Flight is full! No seats available.\n";
        }
    }

    void display() const {
        cout << "\n+------------------------------------------------+\n";
        cout << "  Flight: " << flightID << " | " << airline << endl;
        cout << "  Route: " << source << " -> " << destination << endl;
        cout << "  Departure: " << departure << endl;
        cout << "  Economy Fare: PKR " << (int)ticketPrice << endl;
        cout << "  Business Fare: PKR " << (int)(ticketPrice * 2.5) << endl;
        cout << "  Available Seats: " << (50 - passengerCount) << "/50\n";
        cout << "+------------------------------------------------+\n";
    }

    void displayPassengers() const {
        if (passengerCount == 0) {
            cout << "\nNo passengers on this flight.\n";
            return;
        }

        cout << "\n========== Passengers on " << flightID << " (" << airline << ") ==========\n";
        cout << "Route: " << source << " -> " << destination << endl;
        
        cout << "Name";
        for(int i = 4; i < 25; i++) cout << " ";
        cout << "Passport";
        for(int i = 8; i < 15; i++) cout << " ";
        cout << "Class";
        for(int i = 5; i < 12; i++) cout << " ";
        cout << "Fare\n";
        cout << string(70, '-') << endl;
        
        double totalRevenue = 0;
        for (int i = 0; i < passengerCount; i++) {
            passengers[i].display();
            totalRevenue += passengers[i].getFare();
        }
        cout << string(70, '-') << endl;
        cout << "Total Revenue: PKR " << (int)totalRevenue << endl;
    }
    
    void removePassengerByPassport(string pass) {
        bool found = false;
        for (int i = 0; i < passengerCount; i++) {
            if (passengers[i].getPassport() == pass) {
                cout << "\nRefund Amount: PKR " << (int)passengers[i].getFare() << endl;
                
                for (int j = i; j < passengerCount - 1; j++) {
                    passengers[j] = passengers[j + 1];
                }
                passengerCount--;
                found = true;
                cout << "[SUCCESS] Ticket cancelled & refund processed!\n";
                break;
            }
        }
        if (!found) {
            cout << "\n[ERROR] Passenger not found!\n";
        }
    }

    bool searchPassengerInFlight(string searchName) const {
        for (int i = 0; i < passengerCount; i++) {
            if (passengers[i].getName() == searchName) {
                passengers[i].display();
                return true;
            }
        }
        return false;
    }

    string getID() const { return flightID; }
    string getAirline() const { return airline; }
    string getDestination() const { return destination; }
    string getSource() const { return source; }
    double getTicketPrice() const { return ticketPrice; }
    int getPassengerCount() const { return passengerCount; }
    int getAvailableSeats() const { return 50 - passengerCount; }
};

// =========================
// AIRPORT SYSTEM CLASS
// =========================
class AirportSystem {
private:
    Flight flights[20];
    int flightCount;

public:
    AirportSystem() { flightCount = 0; }

    void addFlight() {
        if (flightCount >= 20) {
            cout << "\n[ERROR] Cannot add more flights!\n";
            return;
        }

        string id, airline, src, dst, dep;
        int airlineChoice, srcChoice, destChoice;

        cin.ignore();
        cout << "\n========== Add New Flight ==========\n";
        cout << "Enter Flight ID (e.g., PK304, EK602): ";
        getline(cin, id);
        
        cout << "\nSelect Airline:\n";
        cout << "1. PIA (Pakistan International Airlines)\n";
        cout << "2. Emirates (Premium)\n";
        cout << "3. FlyDubai (Budget Friendly)\n";
        cout << "4. AirBlue\n";
        cout << "Choice: ";
        cin >> airlineChoice;
        cin.ignore();
        
        switch(airlineChoice) {
            case 1: airline = "PIA"; break;
            case 2: airline = "Emirates"; break;
            case 3: airline = "FlyDubai"; break;
            case 4: airline = "AirBlue"; break;
            default: airline = "PIA"; break;
        }
        
        cout << "\nSelect Source City:\n";
        cout << "1. Karachi  2. Lahore  3. Islamabad  4. Dubai\n";
        cout << "Choice: ";
        cin >> srcChoice;
        cin.ignore();
        
        switch(srcChoice) {
            case 1: src = "Karachi"; break;
            case 2: src = "Lahore"; break;
            case 3: src = "Islamabad"; break;
            case 4: src = "Dubai"; break;
            default: src = "Karachi"; break;
        }
        
        cout << "\nSelect Destination:\n";
        cout << "DOMESTIC:\n";
        cout << "1. Karachi    2. Lahore      3. Islamabad\n";
        cout << "4. Quetta     5. Peshawar    6. Multan\n";
        cout << "\nMIDDLE EAST:\n";
        cout << "7. Dubai      8. Sharjah     9. Abu Dhabi\n";
        cout << "10. Jeddah    11. Riyadh     12. Muscat\n";
        cout << "\nINTERNATIONAL:\n";
        cout << "13. London    14. Manchester 15. Paris\n";
        cout << "16. New York  17. Toronto    18. Bangkok\n";
        cout << "Choice: ";
        cin >> destChoice;
        cin.ignore();
        
        switch(destChoice) {
            case 1: dst = "Karachi"; break;
            case 2: dst = "Lahore"; break;
            case 3: dst = "Islamabad"; break;
            case 4: dst = "Quetta"; break;
            case 5: dst = "Peshawar"; break;
            case 6: dst = "Multan"; break;
            case 7: dst = "Dubai"; break;
            case 8: dst = "Sharjah"; break;
            case 9: dst = "Abu Dhabi"; break;
            case 10: dst = "Jeddah"; break;
            case 11: dst = "Riyadh"; break;
            case 12: dst = "Muscat"; break;
            case 13: dst = "London"; break;
            case 14: dst = "Manchester"; break;
            case 15: dst = "Paris"; break;
            case 16: dst = "New York"; break;
            case 17: dst = "Toronto"; break;
            case 18: dst = "Bangkok"; break;
            default: dst = "Dubai"; break;
        }
        
        cout << "Enter Departure Time (e.g., 14:30): ";
        getline(cin, dep);
        
        Flight newFlight = Flight(id, airline, src, dst, dep);
        flights[flightCount++] = newFlight;
        
        cout << "\n[SUCCESS] Flight added successfully!\n";
        cout << "Economy Fare: PKR " << (int)newFlight.getTicketPrice() << endl;
        cout << "Business Fare: PKR " << (int)(newFlight.getTicketPrice() * 2.5) << endl;
    }
    
    void saveData() {
        ofstream out("flights.txt");
        out << flightCount << endl;
        for (int i = 0; i < flightCount; i++) {
            flights[i].saveToFile(out);
        }
        out.close();
    }
    
    void loadData() {
        ifstream in("flights.txt");
        if (!in) return;
        in >> flightCount;
        in.ignore();
        for (int i = 0; i < flightCount; i++) {
            flights[i].loadFromFile(in);
        }
        in.close();
    }

    void viewFlights() const {
        if (flightCount == 0) {
            cout << "\nNo flights available.\n";
            return;
        }

        cout << "\n========== All Available Flights ==========\n";
        for (int i = 0; i < flightCount; i++) {
            flights[i].display();
        }
    }

    void bookTicket() {
        string id;
        cout << "\nEnter Flight ID to book: ";
        getline(cin, id);

        for (int i = 0; i < flightCount; i++) {
            if (flights[i].getID() == id) {
                if (flights[i].getAvailableSeats() == 0) {
                    cout << "\n[FULL] Sorry! This flight is fully booked.\n";
                    return;
                }
                
                string name, passport, seatClass;
                int classChoice, age;
                double fare, discount, originalFare;
                string discountType;

                flights[i].display();
                
                cout << "\n--- Passenger Details ---\n";
                cout << "Enter Passenger Name: ";
                getline(cin, name);
                
                cout << "Enter Passport Number: ";
                getline(cin, passport);
                
                cout << "Enter Passenger Age: ";
                cin >> age;
                cin.ignore();
                
                double economyPrice = flights[i].getTicketPrice();
                double businessPrice = economyPrice * 2.5;
                
                cout << "\nSelect Seat Class:\n";
                cout << "1. Economy  (PKR " << (int)economyPrice << ")\n";
                cout << "2. Business (PKR " << (int)businessPrice << ")\n";
                cout << "   * Extra legroom\n";
                cout << "   * Priority boarding\n";
                cout << "   * Complimentary meals\n";
                cout << "Choice: ";
                cin >> classChoice;
                cin.ignore();
                
                if (classChoice == 2) {
                    seatClass = "Business";
                    fare = businessPrice;
                } else {
                    seatClass = "Economy";
                    fare = economyPrice;
                }
                
                discount = 0;
                discountType = "";
                
                if (age >= 0 && age <= 2) {
                    discount = 0.90;
                    discountType = "Infant (90% OFF)";
                } 
                else if (age >= 3 && age <= 12) {
                    discount = 0.50;
                    discountType = "Child (50% OFF)";
                } 
                else if (age >= 60) {
                    discount = 0.20;
                    discountType = "Senior Citizen (20% OFF)";
                }
                
                originalFare = fare;
                if (discount > 0) {
                    fare = fare - (fare * discount);
                }

                Passenger p(name, passport, seatClass, age, fare);
                flights[i].addPassenger(p);
                
                cout << "\n+------------------------------------------------+\n";
                cout << "            E-TICKET CONFIRMATION               \n";
                cout << "|------------------------------------------------|\n";
                cout << "  Flight: " << flights[i].getID() << " | " << flights[i].getAirline() << "\n";
                cout << "  Route: " << flights[i].getSource() << " -> " 
                     << flights[i].getDestination() << "\n";
                cout << "  Passenger: " << name << " (Age: " << age << ")\n";
                cout << "  Passport: " << passport << "\n";
                cout << "  Class: " << seatClass << "\n";
                
                if (discount > 0) {
                    cout << "  ---------------------------------------------\n";
                    cout << "  Original Fare: PKR " << (int)originalFare << "\n";
                    cout << "  Discount: " << discountType << "\n";
                    cout << "  You Save: PKR " << (int)(originalFare - fare) << "\n";
                }
                
                cout << "  ---------------------------------------------\n";
                cout << "  Total Fare: PKR " << (int)fare << "\n";
                cout << "|------------------------------------------------|\n";
                cout << "  Thank you for choosing " << flights[i].getAirline() << "!\n";
                cout << "  Please arrive 2 hours before departure.\n";
                cout << "+------------------------------------------------+\n";
                
                saveData();
                return;
            }
        }

        cout << "\n[ERROR] Flight not found!\n";
    }
    
    void cancelTicket() {
        string id, passport;

        cout << "\n--- Cancel Ticket ---\n";
        cout << "Enter Flight ID: ";
        getline(cin, id);

        cout << "Enter Passport Number: ";
        getline(cin, passport);

        for (int i = 0; i < flightCount; i++) {
            if (flights[i].getID() == id) {
                flights[i].removePassengerByPassport(passport);
                saveData();
                return;
            }
        }

        cout << "\n[ERROR] Flight not found!\n";
    }
    
    void viewPassengers() {
        string id;
        cout << "\nEnter Flight ID: ";
        getline(cin, id);

        for (int i = 0; i < flightCount; i++) {
            if (flights[i].getID() == id) {
                flights[i].displayPassengers();
                return;
            }
        }

        cout << "\n[ERROR] Flight not found!\n";
    }
    
    void searchByDestination() {
        string dest;
        int destChoice;
        
        cout << "\nSelect Destination to Search:\n";
        cout << "DOMESTIC:\n";
        cout << "1. Karachi    2. Lahore      3. Islamabad\n";
        cout << "4. Quetta     5. Peshawar    6. Multan\n";
        cout << "\nMIDDLE EAST:\n";
        cout << "7. Dubai      8. Jeddah      9. Riyadh\n";
        cout << "\nINTERNATIONAL:\n";
        cout << "10. London    11. New York   12. Bangkok\n";
        cout << "Choice: ";
        cin >> destChoice;
        cin.ignore();
        
        switch(destChoice) {
            case 1: dest = "Karachi"; break;
            case 2: dest = "Lahore"; break;
            case 3: dest = "Islamabad"; break;
            case 4: dest = "Quetta"; break;
            case 5: dest = "Peshawar"; break;
            case 6: dest = "Multan"; break;
            case 7: dest = "Dubai"; break;
            case 8: dest = "Jeddah"; break;
            case 9: dest = "Riyadh"; break;
            case 10: dest = "London"; break;
            case 11: dest = "New York"; break;
            case 12: dest = "Bangkok"; break;
            default: dest = "Dubai"; break;
        }
        
        bool found = false;
        cout << "\n========== Flights to " << dest << " ==========\n";
        
        for (int i = 0; i < flightCount; i++) {
            if (flights[i].getDestination() == dest) {
                flights[i].display();
                found = true;
            }
        }
        
        if (!found) {
            cout << "No flights found to this destination.\n";
        }
    }
    
    void findCheapestFlight() {
        string dest;
        int destChoice;
        
        cout << "\nSelect Destination to Find Cheapest Flight:\n";
        cout << "DOMESTIC:\n";
        cout << "1. Karachi    2. Lahore      3. Islamabad\n";
        cout << "4. Quetta     5. Peshawar    6. Multan\n";
        cout << "\nMIDDLE EAST:\n";
        cout << "7. Dubai      8. Jeddah      9. Riyadh\n";
        cout << "\nINTERNATIONAL:\n";
        cout << "10. London    11. New York   12. Bangkok\n";
        cout << "Choice: ";
        cin >> destChoice;
        cin.ignore();
        
        switch(destChoice) {
            case 1: dest = "Karachi"; break;
            case 2: dest = "Lahore"; break;
            case 3: dest = "Islamabad"; break;
            case 4: dest = "Quetta"; break;
            case 5: dest = "Peshawar"; break;
            case 6: dest = "Multan"; break;
            case 7: dest = "Dubai"; break;
            case 8: dest = "Jeddah"; break;
            case 9: dest = "Riyadh"; break;
            case 10: dest = "London"; break;
            case 11: dest = "New York"; break;
            case 12: dest = "Bangkok"; break;
            default: dest = "Dubai"; break;
        }
        
        int cheapestIndex = -1;
        double cheapestPrice = 999999;
        
        for (int i = 0; i < flightCount; i++) {
            if (flights[i].getDestination() == dest) {
                if (flights[i].getTicketPrice() < cheapestPrice) {
                    cheapestPrice = flights[i].getTicketPrice();
                    cheapestIndex = i;
                }
            }
        }
        
        if (cheapestIndex == -1) {
            cout << "\n[ERROR] No flights found to " << dest << endl;
            return;
        }
        
        cout << "\n+------------------------------------------------+\n";
        cout << "         CHEAPEST FLIGHT TO " << dest << "\n";
        cout << "+------------------------------------------------+\n";
        flights[cheapestIndex].display();
        
        cout << "\n--- Price Comparison ---\n";
        for (int i = 0; i < flightCount; i++) {
            if (flights[i].getDestination() == dest) {
                cout << flights[i].getAirline() << " (" << flights[i].getID() << "): PKR " 
                     << (int)flights[i].getTicketPrice();
                if (i == cheapestIndex) {
                    cout << " <- BEST DEAL!";
                }
                cout << endl;
            }
        }
    }
    
    void searchPassengerByName() {
        string searchName;
        cout << "\nEnter Passenger Name to Search: ";
        getline(cin, searchName);
        
        bool found = false;
        
        cout << "\n+------------------------------------------------+\n";
        cout << "         PASSENGER SEARCH RESULTS               \n";
        cout << "+------------------------------------------------+\n";
        
        for (int i = 0; i < flightCount; i++) {
            if (flights[i].searchPassengerInFlight(searchName)) {
                cout << "\n[FOUND] Found on Flight: " << flights[i].getID() << " (" 
                     << flights[i].getAirline() << ")\n";
                cout << "Route: " << flights[i].getSource() << " -> " 
                     << flights[i].getDestination() << "\n";
                found = true;
            }
        }
        
        if (!found) {
            cout << "\n[ERROR] No bookings found for passenger: " << searchName << endl;
        }
    }
    
    void displayStatistics() {
        if (flightCount == 0) {
            cout << "\nNo data available.\n";
            return;
        }
        
        int totalPassengers = 0;
        int mostBookedIndex = 0;
        
        for (int i = 0; i < flightCount; i++) {
            totalPassengers += flights[i].getPassengerCount();
            if (flights[i].getPassengerCount() > flights[mostBookedIndex].getPassengerCount()) {
                mostBookedIndex = i;
            }
        }
        
        double loadPercent = (flightCount > 0 ? (double)totalPassengers*100/(flightCount*50) : 0);
        
        cout << "\n+------------------------------------------------+\n";
        cout << "              AIRPORT STATISTICS                \n";
        cout << "|------------------------------------------------|\n";
        cout << "  Total Flights: " << flightCount << "\n";
        cout << "  Total Passengers: " << totalPassengers << "\n";
        cout << "  Total Available Seats: " << (flightCount * 50 - totalPassengers) << "\n";
        cout << "  Average Load: " << (int)loadPercent << "%\n";
        cout << "  \n";
        cout << "  Most Popular Flight:\n";
        cout << "  > " << flights[mostBookedIndex].getID() << " ("
             << flights[mostBookedIndex].getSource() << " to "
             << flights[mostBookedIndex].getDestination() << ")\n";
        cout << "  > " << flights[mostBookedIndex].getPassengerCount() << " bookings\n";
        cout << "+------------------------------------------------+\n";
    }
};

// =========================
// MAIN MENU
// =========================
int main() {
    AirportSystem airport;
    airport.loadData();
    int choice;

    do {
        cout << "\n+------------------------------------------------+\n";
        cout << "       AIRPORT MANAGEMENT SYSTEM                \n";
        cout << "|------------------------------------------------|\n";
        cout << "  1. Add Flight\n";
        cout << "  2. View All Flights\n";
        cout << "  3. Book Ticket\n";
        cout << "  4. View Passengers of a Flight\n";
        cout << "  5. Cancel Ticket\n";
        cout << "  6. Search Flights by Destination\n";
        cout << "  7. Find Cheapest Flight\n";
        cout << "  8. Search Passenger by Name\n";
        cout << "  9. Display Statistics\n";
        cout << "  10. Exit\n";
        cout << "+------------------------------------------------+\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: airport.addFlight(); break;
            case 2: airport.viewFlights(); break;
            case 3: airport.bookTicket(); break;
            case 4: airport.viewPassengers(); break;
            case 5: airport.cancelTicket(); break;
            case 6: airport.searchByDestination(); break;
            case 7: airport.findCheapestFlight(); break;
            case 8: airport.searchPassengerByName(); break;
            case 9: airport.displayStatistics(); break;
            case 10: 
                airport.saveData();
                cout << "\n[SUCCESS] Data saved. Thank you for using our system!\n"; 
                break;
            default: 
                cout << "\n[ERROR] Invalid option! Please try again.\n";
        }

    } while (choice != 10);

    return 0;

}

