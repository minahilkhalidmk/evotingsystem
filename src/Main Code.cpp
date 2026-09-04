#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

// ==========================================
// 1. CANDIDATE CLASS
// ==========================================
class Candidate {
private:
    int id;
    string name;
    string party;
    int voteCount;

public:
    Candidate(int cId = 0, string cName = "", string cParty = "") 
        : id(cId), name(cName), party(cParty), voteCount(0) {}

    void setId(int cId) { id = cId; }
    void setName(string cName) { name = cName; }
    void setParty(string cParty) { party = cParty; }
    void incrementVote() { voteCount++; }
    void setVoteCount(int count) { voteCount = count; }

    int getId() const { return id; }
    string getName() const { return name; }
    string getParty() const { return party; }
    int getVoteCount() const { return voteCount; }

    void display() const {
        cout << "  [ID: " << id << "] " << left << setw(20) << name 
             << " | Party: " << setw(15) << party 
             << " | Votes: " << voteCount << endl;
    }
};

// ==========================================
// 2. ABSTRACT BASE CLASS: USER (Encapsulation & Abstraction)
// ==========================================
class User {
protected:
    string cnic;
    string password;
    string name;

public:
    User(string uCnic = "", string uPass = "", string uName = "") 
        : cnic(uCnic), password(uPass), name(uName) {}

    virtual ~User() {}

    void setCnic(string uCnic) { cnic = uCnic; }
    void setPassword(string uPass) { password = uPass; }
    void setName(string uName) { name = uName; }

    string getCnic() const { return cnic; }
    string getPassword() const { return password; }
    string getName() const { return name; }

    // Pure Virtual Function (Polymorphism)
    virtual string getRole() const = 0;

    bool authenticate(string inputCnic, string inputPass) const {
        return (cnic == inputCnic && password == inputPass);
    }
};

// ==========================================
// 3. DERIVED CLASS: VOTER (Inheritance)
// ==========================================
class Voter : public User {
private:
    bool hasVoted;
    int votedCandidateId;

public:
    Voter(string uCnic = "", string uPass = "", string uName = "") 
        : User(uCnic, uPass, uName), hasVoted(false), votedCandidateId(-1) {}

    string getRole() const override {
        return "Voter";
    }

    void setHasVoted(bool status) { hasVoted = status; }
    bool getHasVoted() const { return hasVoted; }

    void setVotedCandidateId(int cId) { votedCandidateId = cId; }
    int getVotedCandidateId() const { return votedCandidateId; }
};

// ==========================================
// 4. DERIVED CLASS: ADMIN (Inheritance)
// ==========================================
class Admin : public User {
private:
    string adminKey;

public:
    Admin(string uCnic = "", string uPass = "", string uName = "", string key = "ADM-2026") 
        : User(uCnic, uPass, uName), adminKey(key) {}

    string getRole() const override {
        return "Admin";
    }

    string getAdminKey() const { return adminKey; }
};

// ==========================================
// 5. ELECTION BASE CLASS & DERIVED CLASSES (Inheritance & Polymorphism)
// ==========================================
class Election {
protected:
    string type;
    int durationHours;
    int maxSeats;
    vector<Candidate> candidates;
    bool isActive;

public:
    Election(string eType = "General", int duration = 24, int seats = 5) 
        : type(eType), durationHours(duration), maxSeats(seats), isActive(true) {}

    virtual ~Election() {}

    void setType(string eType) { type = eType; }
    void setDuration(int d) { durationHours = d; }
    void setMaxSeats(int s) { maxSeats = s; }
    void setActive(bool status) { isActive = status; }

    string getType() const { return type; }
    int getDuration() const { return durationHours; }
    int getMaxSeats() const { return maxSeats; }
    bool getIsActive() const { return isActive; }

    virtual void displayElectionBanner() const {
        cout << "\n==========================================" << endl;
        cout << "    E-VOTING SYSTEM - " << type << " ELECTION" << endl;
        cout << "==========================================" << endl;
        cout << " Duration: " << durationHours << " Hours | Seats: " << maxSeats << endl;
    }

    bool addCandidate(const Candidate& c) {
        if ((int)candidates.size() < maxSeats) {
            candidates.push_back(c);
            return true;
        }
        return false;
    }

    const vector<Candidate>& getCandidates() const {
        return candidates;
    }

    Candidate* getCandidateById(int id) {
        for (auto &c : candidates) {
            if (c.getId() == id) return &c;
        }
        return nullptr;
    }

    void displayCandidates() const {
        cout << "\n--- OFFICIAL CANDIDATE BALLOT LIST ---" << endl;
        if (candidates.empty()) {
            cout << "No candidates registered yet." << endl;
            return;
        }
        for (const auto &c : candidates) {
            c.display();
        }
    }

    int getTotalVotes() const {
        int total = 0;
        for (const auto &c : candidates) {
            total += c.getVoteCount();
        }
        return total;
    }

    void displayResults() const {
        cout << "\n==========================================" << endl;
        cout << "       ELECTION RESULTS SUMMARY (" << type << ")" << endl;
        cout << "==========================================" << endl;
        int total = getTotalVotes();
        cout << " Total Cast Ballots: " << total << endl << endl;

        for (const auto &c : candidates) {
            double pct = total > 0 ? (double)c.getVoteCount() / total * 100.0 : 0.0;
            cout << " Candidate " << setw(18) << left << c.getName() 
                 << " [" << setw(12) << left << c.getParty() << "] : " 
                 << setw(5) << c.getVoteCount() << " votes (" 
                 << fixed << setprecision(1) << pct << "%)\n";
        }
        cout << "==========================================" << endl;
    }
};

class LocalElection : public Election {
public:
    LocalElection() : Election("Local Municipal", 12, 4) {}
    void displayElectionBanner() const override {
        cout << "\n[LOCAL ELECTION] Municipal Council & District Voting Platform" << endl;
    }
};

class RegionalElection : public Election {
public:
    RegionalElection() : Election("Regional Provincial", 24, 6) {}
    void displayElectionBanner() const override {
        cout << "\n[REGIONAL ELECTION] Provincial Assembly Voting System" << endl;
    }
};

class NationalElection : public Election {
public:
    NationalElection() : Election("National General", 48, 10) {}
    void displayElectionBanner() const override {
        cout << "\n[NATIONAL ELECTION] General National Parliamentary Voting Platform" << endl;
    }
};

// ==========================================
// 6. E-VOTING MANAGEMENT SYSTEM
// ==========================================
class EVotingSystem {
private:
    vector<Voter> voters;
    vector<Admin> admins;
    Election* currentElection;

public:
    EVotingSystem() {
        currentElection = new NationalElection();
        seedInitialData();
    }

    ~EVotingSystem() {
        delete currentElection;
    }

    void seedInitialData() {
        // Seed default Admin
        admins.push_back(Admin("11111-1111111-1", "admin123", "System Administrator"));

        // Seed default Voters
        voters.push_back(Voter("35202-1234567-1", "voter123", "Alice Johnson"));
        voters.push_back(Voter("35202-7654321-2", "voter123", "Bob Smith"));
        voters.push_back(Voter("35202-9999999-3", "voter123", "Charlie Brown"));

        // Seed Candidates
        currentElection->addCandidate(Candidate(101, "Dr. Eleanor Vance", "Progressive Front"));
        currentElection->addCandidate(Candidate(102, "Marcus Aurelius Sterling", "Unity Alliance"));
        currentElection->addCandidate(Candidate(103, "Sophia Lin", "Green Tomorrow"));
        currentElection->addCandidate(Candidate(104, "David K. Miller", "Civic Liberty"));
    }

    void registerVoter() {
        string cnic, pass, name;
        cout << "\n--- VOTER REGISTRATION ---" << endl;
        cout << "Enter CNIC (e.g., 35202-0000000-0): ";
        cin >> cnic;
        cout << "Enter Full Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Password: ";
        cin >> pass;

        for (const auto &v : voters) {
            if (v.getCnic() == cnic) {
                cout << "[ERROR] CNIC already registered!\n";
                return;
            }
        }

        voters.push_back(Voter(cnic, pass, name));
        
        // Save to users.txt
        ofstream file("users.txt", ios::app);
        if (file.is_open()) {
            file << "Voter," << cnic << "," << name << "," << pass << "\n";
            file.close();
        }

        cout << "[SUCCESS] Registration successful for " << name << "!\n";
    }

    Voter* authenticateVoter(string cnic, string pass) {
        for (auto &v : voters) {
            if (v.authenticate(cnic, pass)) return &v;
        }
        return nullptr;
    }

    Admin* authenticateAdmin(string cnic, string pass) {
        for (auto &a : admins) {
            if (a.authenticate(cnic, pass)) return &a;
        }
        return nullptr;
    }

    void voterMenu(Voter* voter) {
        int choice;
        while (true) {
            cout << "\n--- VOTER PORTAL (" << voter->getName() << ") ---" << endl;
            cout << "1. View Active Election & Candidates\n";
            cout << "2. Cast Vote\n";
            cout << "3. View Voting Receipt\n";
            cout << "4. Logout\n";
            cout << "Select Option: ";
            cin >> choice;

            if (choice == 1) {
                currentElection->displayElectionBanner();
                currentElection->displayCandidates();
            }
            else if (choice == 2) {
                if (voter->getHasVoted()) {
                    cout << "\n[WARNING] You have already cast your vote in this election!\n";
                } else {
                    currentElection->displayCandidates();
                    int cId;
                    cout << "\nEnter Candidate ID to vote for: ";
                    cin >> cId;
                    Candidate* cand = currentElection->getCandidateById(cId);
                    if (cand) {
                        cand->incrementVote();
                        voter->setHasVoted(true);
                        voter->setVotedCandidateId(cId);

                        // Save vote to votes.txt
                        ofstream vFile("votes.txt", ios::app);
                        if (vFile.is_open()) {
                            vFile << voter->getCnic() << "," << cId << "," << cand->getName() << "\n";
                            vFile.close();
                        }

                        cout << "\n[SUCCESS] Vote cast successfully for " << cand->getName() << "!\n";
                    } else {
                        cout << "\n[ERROR] Invalid Candidate ID!\n";
                    }
                }
            }
            else if (choice == 3) {
                if (!voter->getHasVoted()) {
                    cout << "\n[INFO] You have not cast a vote yet.\n";
                } else {
                    Candidate* cand = currentElection->getCandidateById(voter->getVotedCandidateId());
                    cout << "\n==========================================" << endl;
                    cout << "       DIGITAL VOTING RECEIPT" << endl;
                    cout << "==========================================" << endl;
                    cout << " Voter Name : " << voter->getName() << endl;
                    cout << " Voter CNIC : " << voter->getCnic() << endl;
                    cout << " Voted For  : " << (cand ? cand->getName() : "Unknown") << endl;
                    cout << " Status     : CONFIRMED & AUDITED" << endl;
                    cout << "==========================================" << endl;
                }
            }
            else if (choice == 4) {
                cout << "Logging out...\n";
                break;
            }
            else {
                cout << "Invalid choice!\n";
            }
        }
    }

    void adminMenu(Admin* admin) {
        int choice;
        while (true) {
            cout << "\n--- ADMIN CONTROL PANEL (" << admin->getName() << ") ---" << endl;
            cout << "1. Add New Candidate\n";
            cout << "2. View Live Results\n";
            cout << "3. Switch Election Type (Local / Regional / National)\n";
            cout << "4. View All Registered Voters\n";
            cout << "5. Logout\n";
            cout << "Select Option: ";
            cin >> choice;

            if (choice == 1) {
                int id;
                string name, party;
                cout << "Enter Candidate ID: ";
                cin >> id;
                cout << "Enter Candidate Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Party Name: ";
                getline(cin, party);

                if (currentElection->addCandidate(Candidate(id, name, party))) {
                    cout << "[SUCCESS] Candidate registered successfully!\n";
                } else {
                    cout << "[ERROR] Maximum seats reached for this election!\n";
                }
            }
            else if (choice == 2) {
                currentElection->displayResults();
            }
            else if (choice == 3) {
                int typeChoice;
                cout << "1. Local Municipal Election\n";
                cout << "2. Regional Provincial Election\n";
                cout << "3. National General Election\n";
                cout << "Select Election Type: ";
                cin >> typeChoice;

                delete currentElection;
                if (typeChoice == 1) currentElection = new LocalElection();
                else if (typeChoice == 2) currentElection = new RegionalElection();
                else currentElection = new NationalElection();

                // Re-add default candidates
                currentElection->addCandidate(Candidate(101, "Dr. Eleanor Vance", "Progressive Front"));
                currentElection->addCandidate(Candidate(102, "Marcus Aurelius Sterling", "Unity Alliance"));
                currentElection->addCandidate(Candidate(103, "Sophia Lin", "Green Tomorrow"));

                cout << "[SUCCESS] Switched to " << currentElection->getType() << " Election!\n";
            }
            else if (choice == 4) {
                cout << "\n--- REGISTERED VOTERS LIST ---" << endl;
                for (const auto &v : voters) {
                    cout << " CNIC: " << setw(18) << left << v.getCnic() 
                         << " | Name: " << setw(20) << v.getName() 
                         << " | Has Voted: " << (v.getHasVoted() ? "YES" : "NO") << endl;
                }
            }
            else if (choice == 5) {
                cout << "Logging out admin...\n";
                break;
            }
            else {
                cout << "Invalid choice!\n";
            }
        }
    }

    void start() {
        int choice;
        while (true) {
            cout << "\n=============================================" << endl;
            cout << "   WELCOME TO AURA-VOTE E-VOTING SYSTEM      " << endl;
            cout << "=============================================" << endl;
            cout << "1. Voter Login\n";
            cout << "2. Voter Registration\n";
            cout << "3. Admin Login\n";
            cout << "4. View Current Election Results (Public)\n";
            cout << "5. Exit System\n";
            cout << "Choose an option: ";
            cin >> choice;

            if (choice == 1) {
                string cnic, pass;
                cout << "Enter CNIC: ";
                cin >> cnic;
                cout << "Enter Password: ";
                cin >> pass;

                Voter* v = authenticateVoter(cnic, pass);
                if (v) {
                    cout << "\n[SUCCESS] Login successful! Welcome " << v->getName() << endl;
                    voterMenu(v);
                } else {
                    cout << "\n[ERROR] Invalid CNIC or Password!\n";
                }
            }
            else if (choice == 2) {
                registerVoter();
            }
            else if (choice == 3) {
                string cnic, pass;
                cout << "Enter Admin CNIC: ";
                cin >> cnic;
                cout << "Enter Admin Password: ";
                cin >> pass;

                Admin* a = authenticateAdmin(cnic, pass);
                if (a) {
                    cout << "\n[SUCCESS] Admin access granted! Welcome " << a->getName() << endl;
                    adminMenu(a);
                } else {
                    cout << "\n[ERROR] Invalid Admin credentials!\n";
                }
            }
            else if (choice == 4) {
                currentElection->displayResults();
            }
            else if (choice == 5) {
                cout << "\nThank you for using AuraVote E-Voting System. Goodbye!\n";
                break;
            }
            else {
                cout << "Invalid choice! Please try again.\n";
            }
        }
    }
};

// ==========================================
// MAIN FUNCTION
// ==========================================
int main() {
    EVotingSystem system;
    system.start();
    return 0;
}