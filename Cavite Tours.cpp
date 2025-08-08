#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <chrono>
#include <thread>

using namespace std;

const string indents = "\t\t"; // An indents constant for creating an indent in the console

// Declare a TourPackage struct to store information about each package
struct TourPackage {
    string name;           // Fancy name of the tour
    string location_name;  // Name of the major location
    int days;              // Number of days of the tour
    int nights;            // Number of nights of the tour
    double price;          // Price of the tour (per person)
    string description;    // Short description of the tour

    // Default constructor with member initializer list for clarity
    TourPackage(string n, string loc, int d, int ni, double p, string desc) 
        : name(n), location_name(loc), days(d), nights(ni), price(p), description(desc) {}
};

// Declare a TourAddon struct to store information about each addon
struct TourAddon {
    string name; // Name of the addon
    string description; // Description of the addon
    double price; // Price of the addon
    double additional; // Additional price for each extra person
};

// Create the Tour Packages array with each initializer list matching the order and types of the structure
const TourPackage packages[] = {
    TourPackage("(HOT) Tagaytay Ridge Tour", 
                "Taal Volcano, Picnic Grove, People's Park in the Sky", 
                3, 2, 5000.00, 
                "Explore Tagaytay's famous spots, starting with the iconic Taal Volcano, a scenic visit to Picnic Grove, and a panoramic view at People's Park in the Sky."),

    TourPackage("(HOT) Historical Cavite Journey", 
                "Aguinaldo Shrine, Fort San Felipe, Corregidor Island", 
                3, 2, 4500.00, 
                "Delve into Cavite's historical sites, starting with the Aguinaldo Shrine, then Fort San Felipe, and finally a ferry ride to Corregidor Island for a rich WWII experience."),
    
    TourPackage("Tagaytay Leisure Tour", 
                "Sky Ranch, Mahogany Market", 
                3, 2, 3500.00, 
                "Spend a leisurely day at Sky Ranch’s amusement park followed by a stop at Mahogany Market to experience local cuisine and culture."),
    
    TourPackage("Island and Falls Escape", 
                "Patungan Beach Cove, Balite Falls", 
                3, 2, 3500.00, 
                "Enjoy a refreshing day at Patungan Beach Cove followed by a relaxing visit to the scenic Balite Falls in Amadeo."),
    
    TourPackage("Pico de Loro Day Trek", 
                "Pico de Loro Peak", 
                2, 1, 2500.00, 
                "Take on the challenge of hiking up Pico de Loro Peak for breathtaking views and an unforgettable adventure."),
    
    TourPackage("Maragondon Mountain Adventure", 
                "Mt. Buntis, Mt. Nagpatong", 
                2, 1, 2500.00, 
                "Hike the legendary mountains of Maragondon, famous for their historic significance and natural beauty."),
    
    TourPackage("Kawit Heritage Tour", 
                "Aguinaldo Shrine, St. Mary Magdalene Church", 
                2, 1, 1500.00, 
                "Immerse in Cavite’s heritage with visits to the Aguinaldo Shrine and the historic St. Mary Magdalene Church in Kawit."),
    
    TourPackage("Caleruega Garden Retreat", 
                "Caleruega Church and Gardens", 
                2, 1, 1500.00, 
                "Enjoy a peaceful day exploring the beautiful Caleruega Church, perfect for retreats and quiet reflection."),
                
    TourPackage("Silang Nature and Heritage Tour", 
                "Ilog Maria Honeybee Farm, Our Lady of Candelaria Church", 
                1, 0, 1800.00, 
                "Visit the serene Ilog Maria Honeybee Farm for a unique experience in organic farming and honey production, then enjoy the historic beauty of Our Lady of Candelaria Church."),

    TourPackage("Amadeo Coffee Culture Tour", 
                "Amadeo Coffee Farms, Cafe Amadeo", 
                1, 0, 1000.00, 
                "Discover the coffee capital of Cavite with a tour of Amadeo's lush coffee farms and a visit to Café Amadeo, where you can savor local coffee specialties and purchase fresh coffee beans.")

};


// Create the Addons
const TourAddon addons[] = {
    {"(HOT) Luxury Resort Reservation", "Automatically book a reservation for the top luxury resorts near your itinerary.", 12000.00, 3000.00},
    {"Personal Driver", "Skip the public transport lines and reserve your own Personal Driver!", 5000.00, 250.00},
    {"Public Tour Bus", "Don't worry about commuting and join in our Tour Bus!", 500.00, 500.00},
    {"Dinner Buffet", "Have a dinner with authentic local cuisine on your last night.", 1500.00, 250.00},
    {"Breakfast Buffet", "Have breakfast with authentic local cuisine on your last day", 1500.00, 250.00},
    {"Official Tourism Agency Merchandise", "Return home with official merchandise of the Tourism Agency. (Merchandise cycles per month)", 1500.00, 500.00}
};

const double AdditionalDiscount = 0.05;

void PRINT_HEADER(int header_type);
void displayTourPackages();
void confirmPackageChoice(int choice);
void calculatePeopleDiscount(int choice, int amountOfPeople, double &discount, double &finalPrice);
void getAmountOfPeople(int choice);
void chooseAddons(int choice, int amountOfPeople);
void displayTourAddons(vector<int> &addonChoices, int amountOfPeople);
void selectAddon(vector<int>& addonChoices, int choice);
void finishBooking(vector<int> addonChoices, int choice, int amountOfPeople);
void thankYou();
void pauseAndClearScreen();

int main() {
    PRINT_HEADER(3);
    cout << indents << "Welcome to Cavite Tours!" << "\n"
         << indents << "Discover the rich history and scenic spots Cavite has to offer, with tours changing by the season." << "\n"
         << indents << "Our current tour packages feature must-see sites around Tagaytay and historical landmarks!" << "\n"
         << indents << "(Note: Due to HIGH DEMAND, we recommend booking several months in advance.)" << "\n"\
         << indents << "\n\t\tPress ENTER to explore our exciting tour packages for this season!" << "\n"
         << indents;
    cin.ignore(); // Wait for ENTER key press

    pauseAndClearScreen();

    displayTourPackages();

    return 0;
}

void PRINT_HEADER(int header_type) {
    cout << indents;
    switch (header_type) {
        case 1: std::cout << R"(
                                                        ,-----.                  ,--.  ,--.             ,--------.                             
                                                       '  .--./ ,--,--.,--.  ,--.`--',-'  '-. ,---.     '--.  .--',---. ,--.,--.,--.--. ,---.  
                                                       |  |    ' ,-.  | \  `'  / ,--.'-.  .-'| .-. :       |  |  | .-. ||  ||  ||  .--'(  .-'  
                                                       '  '--'\\ '-'  |  \    /  |  |  |  |  \   --.       |  |  ' '-' ''  ''  '|  |   .-'  `) 
                                                        `-----' `--`--'   `--'   `--'  `--'   `----'       `--'   `---'  `----' `--'   `----'
	)" << '\n'; 
		cout << "\t\t=========================================================================== VACATION PACKAGES ==============================================================\n"; break;
        case 2: std::cout << R"(
                                                        ,-----.                  ,--.  ,--.             ,--------.                             
                                                       '  .--./ ,--,--.,--.  ,--.`--',-'  '-. ,---.     '--.  .--',---. ,--.,--.,--.--. ,---.  
                                                       |  |    ' ,-.  | \  `'  / ,--.'-.  .-'| .-. :       |  |  | .-. ||  ||  ||  .--'(  .-'  
                                                       '  '--'\\ '-'  |  \    /  |  |  |  |  \   --.       |  |  ' '-' ''  ''  '|  |   .-'  `) 
                                                        `-----' `--`--'   `--'   `--'  `--'   `----'       `--'   `---'  `----' `--'   `----'
	)" << '\n'; 
		cout << "\t\t=========================================================================== ADDONS =========================================================================\n"; break;
        case 3: std::cout << R"(
                        ,-----.                  ,--.  ,--.             ,--------.                             
                       '  .--./ ,--,--.,--.  ,--.`--',-'  '-. ,---.     '--.  .--',---. ,--.,--.,--.--. ,---.  
                       |  |    ' ,-.  | \  `'  / ,--.'-.  .-'| .-. :       |  |  | .-. ||  ||  ||  .--'(  .-'  
                       '  '--'\\ '-'  |  \    /  |  |  |  |  \   --.       |  |  ' '-' ''  ''  '|  |   .-'  `) 
                        `-----' `--`--'   `--'   `--'  `--'   `----'       `--'   `---'  `----' `--'   `----'
	)" << '\n'; 
		cout << "\t\t======================================================================================================\n"; break;
        default: cout << "_____________________________________________________________________________________________\n"; break;
    }
    cout << endl; 
}

void displayTourPackages() {
    PRINT_HEADER(1);
    int size = sizeof(packages) / sizeof(packages[0]);
    cout << indents << "Here are our current selection of tour packages. Our packages changes every season and availability.\n";
    cout << indents <<"These packages are priced per head/person\n";

    cout << indents << setw(40) << left << "Name" << setw(4) << " "
         << setw(72) << left << "Location" << setw(4) << " "
         << setw(12) << left << "Price" << setw(4) << " "
         << setw(32) << left << "Duration" << "\n" << endl;

    for (int i = 0; i < size; i++) {
        const TourPackage &package = packages[i];
        cout << indents << setw(4) << left << i + 1
             << setw(40) << left << package.name << setw(4)
             << setw(76) << left << package.location_name << setw(4)
             << "PHP " << setw(12) << left << package.price;
        
        // Check for 1-day, 0-night tour
        if (package.days == 1 && package.nights == 0) {
            cout << "1 Day (Day Tour)";
        } else {
            cout << package.days << (package.days > 1 ? " Days and " : " Day and ")
                 << package.nights << (package.nights > 1 ? " Nights" : " Night");
        }
        cout << endl;
    }

    cout << "\n" << indents << "Press the number of the package you want to book: ";
    int c;
    while (!(cin >> c) || c < 1 || c > size) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice. Please try again: ";
    }

    pauseAndClearScreen();
    confirmPackageChoice(c - 1);
}

void confirmPackageChoice(int choice) {
    PRINT_HEADER(1);

    const TourPackage &package = packages[choice];
    cout << indents << "Confirm choice of " << package.name << "?\n"
         << indents << "\"" << package.description << "\"\n\n"
         << indents << "PHP " << package.price << " per person with a "
         << AdditionalDiscount * 100 << "% discount for every additional person\n"
         << indents << "Your input: (Y/N) ";

    char c;
    while (true) {
        cin >> c;
        if (c == 'y' || c == 'Y' || c == 'n' || c == 'N') break;
        cout << "Invalid choice. Please try again (Y/N): ";
    }

    pauseAndClearScreen();

    if (c == 'y' || c == 'Y') {
        getAmountOfPeople(choice);
    } else {
        displayTourPackages();
    }
}

void getAmountOfPeople(int choice) {
    PRINT_HEADER(1);

    const TourPackage &package = packages[choice];
    cout << indents << "How many people (not including you) are going with you on the " << package.name << "?\n"
         << indents << "\"" << package.description << "\"\n\n"
         << indents << "PHP " << package.price << " per person with "
         << AdditionalDiscount * 100 << "% discount for every additional person\n"
         << indents << "Your input: (Number) ";

    int amountOfPeople;
    while (!(cin >> amountOfPeople) || amountOfPeople < 0) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "\t\tInvalid input. Please enter a valid number: ";
    }

    double discount = 0;
    double finalPrice = 0;
    calculatePeopleDiscount(choice, amountOfPeople, discount, finalPrice);

    pauseAndClearScreen();

    chooseAddons(choice, amountOfPeople + 1);
}

void calculatePeopleDiscount(int choice, int amountOfPeople, double &discount, double &finalPrice) {
    const TourPackage &package = packages[choice];
    discount = package.price * min(0.5, AdditionalDiscount * amountOfPeople);
    finalPrice = package.price * (1 + amountOfPeople) - discount;

    cout << indents << "You currently have " << amountOfPeople + 1 << " people with a "
         << discount << " PHP discount, totaling PHP " << finalPrice << ".\n";
}

void chooseAddons(int choice, int amountOfPeople) {
    PRINT_HEADER(2);
    cout << indents << "Choose addons for " << packages[choice].name << "\n\n";

    vector<int> addonChoices;
    displayTourAddons(addonChoices, amountOfPeople);
}

void displayTourAddons(vector<int> &addonChoices, int amountOfPeople) {
    int size = sizeof(addons) / sizeof(addons[0]);

    for (int i = 0; i < size; i++) {
        const TourAddon &addon = addons[i];
        cout << indents << i + 1 << ". " << addon.name << "\n"
             << indents << "\tBase Price: PHP " << addon.price
             << " with an additional PHP " << addon.additional
             << " per extra person.\n"
             << indents << "\t" << addon.description << "\n\n";
    }

    cout << indents << "Enter the number of each addon you'd like to add (0 to finish): ";

    while (true) {
        int choice;
        cin >> choice;
        if (choice == 0) break;
        selectAddon(addonChoices, choice - 1);
          cout << indents << "Enter the number of each addon you'd like to add (0 to finish): "; // Prompt again
    }

    finishBooking(addonChoices, 0, amountOfPeople); // Assuming a dummy value for demonstration
}

void selectAddon(vector<int>& addonChoices, int choice) {
    if (find(addonChoices.begin(), addonChoices.end(), choice) == addonChoices.end()) {
        addonChoices.push_back(choice);
    }
}


void finishBooking(vector<int> addonChoices, int choice, int amountOfPeople) {
    pauseAndClearScreen();
    
    PRINT_HEADER(1);

    cout << indents << "Thank you for booking with us! Here are the details:\n\n";

    const TourPackage &package = packages[choice];
    
    // Calculate the total price for the tour package
    double discount = 0;
    double finalPrice = 0;
    calculatePeopleDiscount(choice, amountOfPeople - 1, discount, finalPrice); // amountOfPeople - 1 for the user
    
    // Apply senior citizen discount
    double seniorDiscountRate = 0.20; // 20% discount
    int numSeniors;
    cout << indents << "How many senior citizens are in your group? ";
    cin >> numSeniors;

    vector<string> seniorIDs;  // Store senior citizen IDs

    if (numSeniors > 0 && numSeniors <= amountOfPeople) {
        // Collect Senior Citizen IDs
        cout << indents << "\n\t\tPlease enter the Senior Citizen ID for each senior in your group:\n";
        for (int i = 0; i < numSeniors; ++i) {
            string seniorID;
            cout << indents << "Senior Citizen " << (i + 1) << " ID: ";
            cin >> seniorID;
            seniorIDs.push_back(seniorID);
        }

        double seniorDiscount = finalPrice * seniorDiscountRate * numSeniors;
        finalPrice -= seniorDiscount;
        cout << indents << "Senior Citizen Discount (20% per senior): -PHP " << seniorDiscount << "\n";
    } else if (numSeniors > amountOfPeople) {
        cout << indents << "Invalid input. Seniors count cannot exceed total people. Setting seniors to 0.\n";
        numSeniors = 0;
    }

    // Total cost for addons
    double totalAddons = 0.0;
    for (int addonChoice : addonChoices) {
        const TourAddon &addon = addons[addonChoice];
        double addonTotal = addon.price + (addon.additional * (amountOfPeople - 1)); // calculate addon cost for each person
        totalAddons += addonTotal;
        cout << indents << "\n\t\tADDON: " << addon.name << ", Base Price: PHP " << addon.price
             << ", Additional Price per person: PHP " << addon.additional
             << ", Total for Addon: PHP " << addonTotal << "\n";
    }

    // Calculate grand total
    double grandTotal = finalPrice + totalAddons;

    cout << indents << "\n\t\tTotal for Tour Package: PHP " << finalPrice << "\n"
         << indents << "Total for Addons: PHP " << totalAddons << "\n"
         << indents << "GRAND TOTAL: PHP " << grandTotal << "\n\n";

    // Collect user information
    string name, vacationDate, email;
    cout << indents << "Please enter your full name: ";
    cin.ignore(); // Clear any leftover newline from previous input
    getline(cin, name);

    cout << indents << "Enter your preferred vacation date (MM/DD/YYYY): ";
    getline(cin, vacationDate);

    cout << indents << "Enter your email address: ";
    getline(cin, email);

    // Confirm user information
    cout << "\n" << indents << "Review your information:\n"
         << indents << "Name: " << name << "\n"
         << indents << "Vacation Date: " << vacationDate << "\n"
         << indents << "Email: " << email << "\n\n";

    cout << indents << "Is this information correct? (Y/N): ";
    char confirm;
    while (true) {
        cin >> confirm;
        if (confirm == 'y' || confirm == 'Y' || confirm == 'n' || confirm == 'N') break;
        cout << indents << "Invalid choice. Please try again (Y/N): ";
    }

    if (confirm == 'n' || confirm == 'N') {
        finishBooking(addonChoices, choice, amountOfPeople); // Restart the function to re-enter details
        return;
    }

    // Prompt for payment method
    cout << "\n" << indents << "Choose your payment method (Cash or Credit (Credit Card)): ";
    string paymentMethod;
    while (true) {
        cin >> paymentMethod;
        if (paymentMethod == "Cash" || paymentMethod == "cash" ||
            paymentMethod == "Credit" || paymentMethod == "credit") {
            break;
        }
        cout << indents << "Invalid choice. Please enter 'Cash' or 'Credit': ";
    }

    if (paymentMethod == "Credit" || paymentMethod == "credit") {
        // Prompt for credit card details
        string cardNumber, cvv, birthday;

        cout << indents << "Enter your credit card number: ";
        cin >> cardNumber;
        
        cout << indents << "Enter your CVV: ";
        cin >> cvv;
        
        cout << indents << "Enter the expiration date  (MM/DD/YYYY): ";
        cin >> birthday;

        cout << indents << "Processing credit card payment...\n";
        
        cout << indents;
        std::this_thread::sleep_for(std::chrono::seconds(2));
         for (int i = 0; i < 3; ++i) {
                cout << ".";
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
		cout << "\n\n";
        cout << indents << "Payment successful!\n";
        cout << indents << "PLEASE CHECK YOUR EMAIL FOR FURTHER INSTRUCTIONS\n";
    } else {
    	cout << "\n\n";
        cout << indents << "Payment will be collected before the vacation date\n";
        cout << indents << "PLEASE CHECK YOUR EMAIL FOR FURTHER INSTRUCTIONS\n";
    }
    
    thankYou();

}


void thankYou() {
    cout << indents << "\n\t\tThank you for booking with Cavite Tours, We hope you enjoy your experience!\n";
}

void pauseAndClearScreen() {
  system("cls");
}

