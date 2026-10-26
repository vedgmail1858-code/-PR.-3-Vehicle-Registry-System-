
#include <iostream>
using namespace std;

private:
    int vehicleID;
    string manufacturer, model;
    int year;
    static int totalVehicles;

public:
    Vehicle() : vehicleID(0), manufacturer(""), model(""), year(0) {
        totalVehicles++;
    }

    Vehicle(int id, string make, string mdl, int yr)
        : vehicleID(id), manufacturer(make), model(mdl), year(yr) {
        totalVehicles++;
    }

    virtual ~Vehicle() {
        totalVehicles--;
    }

    int getVehicleID() const { return vehicleID; }
    string getManufacturer() const { return manufacturer; }
    string getModel() const { return model; }
    int getYear() const { return year; }

    void setVehicleID(int id) { vehicleID = id; }
    void setManufacturer(string make) { manufacturer = make; }
    void setModel(string mdl) { model = mdl; }
    void setYear(int yr) { year = yr; }

    static int getTotalVehicles() {
        return totalVehicles;
    }

    virtual string getType() const {
        return "Vehicle";
    }

    virtual void display() const {
        cout << "\nType: " << getType()
             << "\nID: " << vehicleID
             << "\nManufacturer: " << manufacturer
             << "\nModel: " << model
             << "\nYear: " << year << '\n';
    }
};

int Vehicle::totalVehicles = 0;


class Car : public Vehicle {
private:
    string fuelType;

public:
    Car(int id, string make, string mdl, int yr, string fuel)
        : Vehicle(id, make, mdl, yr), fuelType(fuel) {}

    string getFuelType() const { return fuelType; }
    void setFuelType(string fuel) { fuelType = fuel; }

    string getType() const override { return "Car"; }

    void display() const override {
        Vehicle::display();
        cout << "Fuel Type: " << fuelType << '\n';
    }
};

class ElectricCar : public Car {
private:
    double batteryCapacity;

public:
    ElectricCar(int id, string make, string mdl, int yr,
                string fuel, double battery)
        : Car(id, make, mdl, yr, fuel),
          batteryCapacity(battery) {}

    double getBatteryCapacity() const {
        return batteryCapacity;
    }

    void setBatteryCapacity(double battery) {
        batteryCapacity = battery;
    }

    string getType() const override { return "Electric Car"; }

    void display() const override {
        Car::display();
        cout << "Battery Capacity: " << batteryCapacity
             << " kWh\n";
    }
};

class SportsCar : public ElectricCar {
private:
    double topSpeed;

public:
    SportsCar(int id, string make, string mdl, int yr,
              string fuel, double battery, double speed)
        : ElectricCar(id, make, mdl, yr, fuel, battery),
          topSpeed(speed) {}

    double getTopSpeed() const { return topSpeed; }
    void setTopSpeed(double speed) { topSpeed = speed; }

    string getType() const override { return "Sports Car"; }

    void display() const override {
        ElectricCar::display();
        cout << "Top Speed: " << topSpeed << " km/h\n";
    }
};


class Aircraft {
private:
    double flightRange;

public:
    Aircraft(double range = 0) : flightRange(range) {}
    virtual ~Aircraft() = default;

    double getFlightRange() const { return flightRange; }
    void setFlightRange(double range) { flightRange = range; }
};


class FlyingCar : public Car, public Aircraft {
public:
    FlyingCar(int id, string make, string mdl, int yr,
              string fuel, double range)
        : Car(id, make, mdl, yr, fuel),
          Aircraft(range) {}

    string getType() const override { return "Flying Car"; }

    void display() const override {
        Car::display();
        cout << "Flight Range: " << getFlightRange()
             << " km\n";
    }
};

class Sedan : public Car {
public:
    Sedan(int id, string make, string mdl, int yr, string fuel)
        : Car(id, make, mdl, yr, fuel) {}

    string getType() const override { return "Sedan"; }

    void display() const override {
        Car::display();
    }
};

class SUV : public Car {
public:
    SUV(int id, string make, string mdl, int yr, string fuel)
        : Car(id, make, mdl, yr, fuel) {}

    string getType() const override { return "SUV"; }

    void display() const override {
        Car::display();
    }
};

class VehicleRegistry {
private:
    static const int MAX_VEHICLES = 100;
    Vehicle* vehicles[MAX_VEHICLES];
    int count;

public:
    VehicleRegistry() : count(0) {
        for (int i = 0; i < MAX_VEHICLES; i++)
            vehicles[i] = nullptr;
    }

    ~VehicleRegistry() {
        for (int i = 0; i < count; i++)
            delete vehicles[i];
    }

    bool idExists(int id) const {
        for (int i = 0; i < count; i++) {
            if (vehicles[i]->getVehicleID() == id)
                return true;
        }
        return false;
    }

    bool addVehicle(Vehicle* v) {
        if (count >= MAX_VEHICLES || idExists(v->getVehicleID())) {
            delete v;
            return false;
        }

        vehicles[count++] = v;
        return true;
    }

    void displayAll() const {
        if (count == 0) {
            cout << "\nNo vehicles registered.\n";
            return;
        }

        cout << "\n========== VEHICLE REGISTRY ==========\n";
        for (int i = 0; i < count; i++) {
            cout << "\nVehicle " << i + 1 << " of " << count;
            vehicles[i]->display();
            cout << "--------------------------------------\n";
        }

        cout << "Registered vehicles: " << count << '\n';
    }

    void searchByID(int id) const {
        for (int i = 0; i < count; i++) {
            if (vehicles[i]->getVehicleID() == id) {
                cout << "\nVehicle found:\n";
                vehicles[i]->display();
                return;
            }
        }

        cout << "\nVehicle ID not found.\n";
    }
};

// ==================== INPUT HELPERS ====================
int readInt(const string& prompt) {
    int value;

    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Enter a whole number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

double readDouble(const string& prompt) {
    double value;

    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Invalid input. Enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

string readString(const string& prompt) {
    string value;
    cout << prompt;
    getline(cin, value);
    return value;
}

// ==================== ADD VEHICLE ====================
void addVehicle(VehicleRegistry& registry) {
    cout << "\nSelect Vehicle Type:\n"
         << "1. Car\n"
         << "2. Electric Car\n"
         << "3. Sports Car\n"
         << "4. Flying Car\n"
         << "5. Sedan\n"
         << "6. SUV\n";

    int type = readInt("Enter choice: ");

    if (type < 1 || type > 6) {
        cout << "Invalid vehicle type.\n";
        return;
    }

    int id = readInt("Enter Vehicle ID: ");

    if (registry.idExists(id)) {
        cout << "This ID already exists.\n";
        return;
    }

    string make = readString("Enter Manufacturer: ");
    string model = readString("Enter Model: ");
    int year = readInt("Enter Manufacturing Year: ");
    string fuel = readString("Enter Fuel Type: ");

    Vehicle* v = nullptr;

    switch (type) {
        case 1:
            v = new Car(id, make, model, year, fuel);
            break;

        case 2: {
            double battery = readDouble(
                "Enter Battery Capacity (kWh): ");
            v = new ElectricCar(
                id, make, model, year, fuel, battery);
            break;
        }

        case 3: {
            double battery = readDouble(
                "Enter Battery Capacity (kWh): ");
            double speed = readDouble(
                "Enter Top Speed (km/h): ");
            v = new SportsCar(
                id, make, model, year, fuel, battery, speed);
            break;
        }

        case 4: {
            double range = readDouble(
                "Enter Flight Range (km): ");
            v = new FlyingCar(
                id, make, model, year, fuel, range);
            break;
        }

        case 5:
            v = new Sedan(id, make, model, year, fuel);
            break;

        case 6:
            v = new SUV(id, make, model, year, fuel);
            break;
    }

    if (v != nullptr && registry.addVehicle(v))
        cout << "\nVehicle added successfully!\n";
    else
        cout << "\nRegistry full. Vehicle could not be added.\n";
}


int main() {
    VehicleRegistry registry;
    int choice;

    do {
        cout << "\n====================================\n"
             << "       VEHICLE REGISTRY SYSTEM\n"
             << "====================================\n"
             << "1. Add Vehicle\n"
             << "2. View All Vehicles\n"
             << "3. Search Vehicle by ID\n"
             << "4. Total Active Vehicles\n"
             << "5. Exit\n";

        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addVehicle(registry);
                break;

            case 2:
                registry.displayAll();
                break;

            case 3: {
                int id = readInt("Enter Vehicle ID to search: ");
                registry.searchByID(id);
                break;
            }

            case 4:
                cout << "Total active vehicles: "
                     << Vehicle::getTotalVehicles() << '\n';
                break;

            case 5:
                cout << "\nExiting Vehicle Registry System.\n";
                break;

            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
