#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <conio.h>
using namespace std;

class Car {
public:
    int id;
    string name;
    string model;
    float pricePerDay;

    Car() {}

    Car(int id, string name, string model, float pricePerDay) {
        this->id = id;
        this->name = name;
        this->model = model;
        this->pricePerDay = pricePerDay;
    }

    void displayCar() {
        cout << "ID: " << id << ", Name: " << name << ", Model: " << model << ", Price/Day: $" << pricePerDay << endl;
    }
};

class User {
public:
    string name;
    string nationalid;

    User() {}

    User(string name, string nationalid) {
        this->name = name;
        this->nationalid = nationalid;
    }

    void displayUser() {
        cout << "Member Name: " << name << ", National Id: " << nationalid << endl;
    }
};

class Booking {
public:
    string userName;
    string nationalId;
    Car car;
    int days;

    Booking() {}

    Booking(string userName, string nationalId, Car car, int days) {
        this->userName = userName;
        this->nationalId = nationalId;
        this->car = car;
        this->days = days;
    }

    void displayBooking() {
        cout << "Booking Details:" << endl;
        cout << "User: " << userName << ", National ID: " << nationalId << endl;
        car.displayCar();
        cout << "Days: " << days << ", Total Cost: $" << car.pricePerDay * days << endl;
    }
};

class Admin {
private:
    vector<Car> cars;
    vector<User> users;
    vector<Booking> bookings;

    void saveCarsToFile() {
        ofstream outFile("cars.txt");
        for (Car &car : cars) {
            outFile << car.id << " " << car.name << " " << car.model << " " << car.pricePerDay << endl;
        }
        outFile.close();
    }

    void loadCarsFromFile() {
        ifstream inFile("cars.txt");
        if (!inFile) {
            return;
        }

        Car car;
        while (inFile >> car.id >> car.name >> car.model >> car.pricePerDay) {
            cars.push_back(car);
        }
        inFile.close();
    }

    void saveUsersToFile() {
        ofstream outFile("users.txt");
        for (User &user : users) {
            outFile << user.name << " " << user.nationalid << endl;
        }
        outFile.close();
    }

    void loadUsersFromFile() {
        ifstream inFile("users.txt");
        if (!inFile) {
            return;
        }

        User user;
        while (inFile >> user.name >> user.nationalid) {
            users.push_back(user);
        }
        inFile.close();
    }

    void saveBookingsToFile() {
        ofstream outFile("bookings.txt");
        for (Booking &booking : bookings) {
            outFile << booking.userName << " " << booking.nationalId << " " << booking.car.id << " " << booking.days << endl;
        }
        outFile.close();
    }

    void loadBookingsFromFile() {
        ifstream inFile("bookings.txt");
        if (!inFile) {
            return;
        }

        string userName, nationalId;
        int carId, days;
        Car bookedCar;

        while (inFile >> userName >> nationalId >> carId >> days) {
            for (Car &car : cars) {
                if (car.id == carId) {
                    bookedCar = car;
                    break;
                }
            }
            bookings.push_back(Booking(userName, nationalId, bookedCar, days));
        }
        inFile.close();
    }

public:
    Admin() {
        loadCarsFromFile();
        loadUsersFromFile();
        loadBookingsFromFile();
    }

    void addCar() {
        int id;
        string name, model;
        float price;
        cout << "Enter Car ID: ";
        cin >> id;
        cout << "Enter Car Name: ";
        cin >> name;
        cout << "Enter Car Model: ";
        cin >> model;
        cout << "Enter Price Per Day: ";
        cin >> price;
        cars.push_back(Car(id, name, model, price));
        saveCarsToFile();
        cout << "Car added successfully!" << endl;
    }

    void deleteCar() {
        int id;
        cout << "Enter Car ID to delete: ";
        cin >> id;
        for (size_t i = 0; i < cars.size(); i++) {
            if (cars[i].id == id) {
                cars.erase(cars.begin() + i);
                saveCarsToFile();
                cout << "Car deleted successfully!" << endl;
                return;
            }
        }
        cout << "Car not found!" << endl;
    }

    void searchCar() {
        int id;
        cout << "Enter Car ID to search: ";
        cin >> id;
        for (Car &car : cars) {
            if (car.id == id) {
                car.displayCar();
                return;
            }
        }
        cout << "Car not found!" << endl;
    }

    void editCar() {
        int id;
        cout << "Enter Car ID to edit: ";
        cin >> id;
        for (Car &car : cars) {
            if (car.id == id) {
                cout << "Enter new Name: ";
                cin >> car.name;
                cout << "Enter new Model: ";
                cin >> car.model;
                cout << "Enter new Price Per Day: ";
                cin >> car.pricePerDay;
                saveCarsToFile();
                cout << "Car details updated successfully!" << endl;
                return;
            }
        }
        cout << "Car not found!" << endl;
    }

    void displayCars() {
        if (cars.empty()) {
            cout << "No cars available!" << endl;
        } else {
            for (Car &car : cars) {
                car.displayCar();
            }
        }
    }

    void addUser() {
        string name, nationalid;
        cout << "Enter Member's Name: ";
        cin >> name;
        cout << "Enter National Id: ";
        cin >> nationalid;
        users.push_back(User(name, nationalid));
        saveUsersToFile();
        cout << "Member added successfully!" << endl;
    }

    void deleteUser() {
        string nationalId;
        cout << "Enter National ID of the user to delete: ";
        cin >> nationalId;

        for (size_t i = 0; i < users.size(); i++) {
            if (users[i].nationalid == nationalId) {
                users.erase(users.begin() + i);
                saveUsersToFile();
                cout << "User deleted successfully!" << endl;
                return;
            }
        }
        cout << "User not found!" << endl;
    }

    void deleteBooking() {
        string nationalId;
        cout << "Enter National ID of the booking to delete: ";
        cin >> nationalId;

        for (size_t i = 0; i < bookings.size(); i++) {
            if (bookings[i].nationalId == nationalId) {
                bookings.erase(bookings.begin() + i);
                saveBookingsToFile();
                cout << "Booking deleted successfully!" << endl;
                return;
            }
        }
        cout << "Booking not found!" << endl;
    }

    void displayUsers() {
        if (users.empty()) {
            cout << "No users found!" << endl;
        } else {
            for (User &user : users) {
                user.displayUser();
            }
        }
    }

    void bookCar() {
        string userName, nationalId;
        int carId, days;

        cout << "Enter your name: ";
        cin >> userName;
        cout << "Enter your National ID: ";
        cin >> nationalId;

        cout << "Enter Car ID to book: ";
        cin >> carId;

        bool carFound = false;
        for (Car &car : cars) {
            if (car.id == carId) {
                carFound = true;
                cout << "Enter number of days to rent: ";
                cin >> days;
                bookings.push_back(Booking(userName, nationalId, car, days));
                saveBookingsToFile();
                cout << "Car booked successfully!" << endl;
                break;
            }
        }

        if (!carFound) {
            cout << "Car not found!" << endl;
        }
    }

    void displayBookings() {
        if (bookings.empty()) {
            cout << "No bookings found!" << endl;
        } else {
            for (Booking &booking : bookings) {
                booking.displayBooking();
            }
        }
    }
};

int login() {
    string pass = "";
    char ch;
    cout << "\n\n\n\n\n\n\n\t\t\t\t\t  Kirmada Car Rental System Login";
    cout << "\n\n\n\n\n\n\n\t\t\t\t\t\tEnter Password: ";
    ch = _getch();
    while (ch != 13) {  
        pass.push_back(ch);
        cout << '*';
        ch = _getch();
    }
    if (pass == "pass") {
        cout << "\n\n\n\n\t\t\t\t\t  Access Granted! Welcome To Our System \n\n";
        system("PAUSE");
        system("CLS");
        return 1;  
    } else {
        cout << "\n\n\n\n\t\t\t\t\tAccess Aborted...Please Try Again!!\n";
        system("PAUSE");
        system("CLS");
        return 0;  
    }
}

int main() {
    Admin admin;
    int choice;

    do {
        cout << "\n1. Admin Login\n2. User View Cars\n3. User Book Car\n4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (login()) {  
                system("CLS");
                int adminChoice;
                do {
                    cout << "\nAdmin Menu:\n";
                    cout << "1. Add Car\n2. Delete Car\n3. Search Car\n4. Edit Car\n5. Display Cars\n";
                    cout << "6. Add Member\n7. Display Members\n8. Delete Member\n9. Display Bookings\n";
                    cout << "10. Delete Booking\n11. Logout\n";
                    cout << "Enter choice: ";
                    cin >> adminChoice;

                    switch (adminChoice) {
                    case 1:
                        system("CLS");
                        admin.addCar();
                        break;
                    case 2:
                        system("CLS");
                        admin.deleteCar();
                        break;
                    case 3:
                        system("CLS");
                        admin.searchCar();
                        break;
                    case 4:
                        system("CLS");
                        admin.editCar();
                        break;
                    case 5:
                        system("CLS");
                        admin.displayCars();
                        break;
                    case 6:
                        system("CLS");
                        admin.addUser();
                        break;
                    case 7:
                        system("CLS");
                        admin.displayUsers();
                        break;
                    case 8:
                        system("CLS");
                        admin.deleteUser();  
                        break;
                    case 9:
                        system("CLS");
                        admin.displayBookings();
                        break;
                    case 10:
                        system("CLS");
                        admin.deleteBooking();  
                        break;
                    case 11:
                        cout << "Logging out...\n";
                        break;
                    default:
                        system("CLS");
                        cout << "Invalid choice!" << endl;
                    }
                } while (adminChoice != 11);
            }
        } else if (choice == 2) {
            system("CLS");
            cout << "Available cars:\n";
            admin.displayCars();
        } else if (choice == 3) {
            system("CLS");
            admin.bookCar();
        } else if (choice != 4) {
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    system("CLS");
    cout << "Thank you for using the car rental system!" << endl<<"For more details contact (7988177468)"<<endl;
    return 0;
}