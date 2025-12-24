Airport Management System - Professional Flight Booking & Management Solution
A feature-rich console-based airport management system developed in C++ that simulates real-world airline operations. This project demonstrates advanced object-oriented programming principles and practical software design patterns for managing flights, passengers, and booking operations.
Core Functionality:
The system provides a complete flight management ecosystem with intuitive menu-driven navigation. Airlines can add flights with customizable routes spanning domestic and international destinations including major cities like Karachi, Dubai, London, and New York. Each flight supports multiple airlines (PIA, Emirates, FlyDubai, AirBlue) with dynamic pricing algorithms that calculate fares based on destination distance and airline premium.
Booking & Passenger Management:
Passengers can book tickets across two service classes - Economy and Business - with the system automatically tracking seat availability (50 seats per flight). The booking process includes intelligent discount mechanisms offering 90% off for infants, 50% for children, and 20% for senior citizens. Each booking generates a detailed e-ticket with comprehensive flight information, pricing breakdown, and savings calculation.
Advanced Features:

Search & Filter: Find flights by destination or locate the cheapest option for budget travelers
Passenger Tracking: Search for passengers across all flights by name
Cancellation System: Process refunds automatically when tickets are cancelled
Analytics Dashboard: View comprehensive statistics including total passengers, load percentages, and most popular routes
Data Persistence: All flight and passenger data is saved to files, ensuring information survives between program sessions

Technical Implementation:
Built using clean OOP architecture with three main classes (Passenger, Flight, AirportSystem), the code emphasizes encapsulation, inheritance concepts, and proper data management. File I/O operations enable persistent storage, while robust input validation ensures system reliability.
Educational Value:
This project serves as an excellent learning resource for understanding class design, data structures, file handling, and building practical business logic in C++. The codebase is well-structured with clear separation of concerns, making it ideal for students and developers looking to understand real-world application development.
