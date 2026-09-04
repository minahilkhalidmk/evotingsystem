//#include <iostream>
//#include <fstream>
//#include <string>
//
//using namespace std;
//
//// ======= Base Class =======
//class User {
//protected:
//    string username;
//    string password;
//
//public:
//    User() {}
//    User(string uname, string pword) : username(uname), password(pword) {}
//
//    virtual string getRole() = 0;
//
//    string getUsername() { return username; }
//
//    bool authenticate(string uname, string pword) {
//        return (uname == username && pword == password);
//    }
//};
//
//// ======= Derived Classes =======
//class Voter : public User {
//public:
//    Voter(string uname, string pword) : User(uname, pword) {}
//
//    string getRole() override {
//        return "Voter";
//    }
//};
//
//class Admin : public User {
//public:
//    Admin(string uname, string pword) : User(uname, pword) {}
//
//    string getRole() override {
//        return "Admin";
//    }
//};
//
//// ======= Register Function =======
//void registerUser(const string& role, const string& uname, const string& pword) {
//    ofstream file("users.txt", ios::app); // open in append mode
//    if (file.is_open()) {
//        file << role << "," << uname << "," << pword << "\n";
//        file.close();
//        cout << "User registered successfully!\n";
//    }
//    else {
//        cout << "Error opening file for writing.\n";
//    }
//}
//
//// ======= Authenticate Function (Manual Parsing) =======
//User* authenticateUser(const string& uname, const string& pword) {
//    ifstream file("users.txt");
//    string line;
//
//    if (!file.is_open()) {
//        cout << "Error opening file for reading.\n";
//        return nullptr;
//    }
//
//    while (getline(file, line)) {
//        string role = "", fileUname = "", filePword = "";
//        int i = 0;
//
//        // Read role
//        while (line[i] != ',') {
//            role += line[i];
//            i++;
//        }
//        i++; // skip comma
//
//        // Read username
//        while (line[i] != ',') {
//            fileUname += line[i];
//            i++;
//        }
//        i++; // skip comma
//
//        // Read password
//        while (i < line.length()) {
//            filePword += line[i];
//            i++;
//        }
//
//        // Check if credentials match
//        if (fileUname == uname && filePword == pword) {
//            if (role == "Voter") return new Voter(uname, pword);
//            if (role == "Admin") return new Admin(uname, pword);
//        }
//    }
//
//    return nullptr; // No match
//}
//
//// ======= Main Program =======
//int main() {
//    int choice;
//    string uname, pword, role;
//
//    cout << "1. Register\n2. Login\nChoose an option: ";
//    cin >> choice;
//
//    cout << "Username: ";
//    cin >> uname;
//    cout << "Password: ";
//    cin >> pword;
//
//    if (choice == 1) {
//        cout << "Role (Voter/Admin): ";
//        cin >> role;
//        registerUser(role, uname, pword);
//    }
//    else if (choice == 2) {
//        User* user = authenticateUser(uname, pword);
//        if (user) {
//            cout << "Login successful as " << user->getRole() << "!\n";
//            // Proceed to your project logic
//            delete user;
//        }
//        else {
//            cout << "Invalid username or password.\n";
//        }
//    }
//    else {
//        cout << "Invalid choice.\n";
//    }
//
//    return 0;
//}