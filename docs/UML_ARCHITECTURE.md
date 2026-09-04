# 🏛️ Architecture & UML Class Matrix — AuraVote E-Voting System

This document provides a detailed technical specification of the **Object-Oriented Software Architecture** powering **AuraVote**, implemented in pure **C++20** and accompanied by an interactive **Glassmorphic Web Visualizer**.

---

## 🎯 1. The 4 Core Pillars of Object-Oriented Design

```
                     ┌──────────────────────────────┐
                     │ 4 Core Pillars of OOP Design │
                     └──────────────┬───────────────┘
          ┌─────────────────┬───────┴─────────┬─────────────────┐
          ▼                 ▼                 ▼                 ▼
   1. Encapsulation  2. Inheritance    3. Polymorphism    4. Abstraction
  (Data Protection) (Code Reusability) (Dynamic Dispatch) (Contract Design)
```

### 1.1 🔒 Encapsulation (Data Protection & Invariant Enforcement)
- **Data Hiding**: In `Candidate`, `User`, `Voter`, and `Election`, internal state variables (`cnic`, `password`, `voteCount`, `hasVoted`, `votedCandidateId`) are guarded under `private` or `protected` specifiers.
- **Accessors & Mutators**: State transitions occur strictly through validated methods:
  - `Candidate::incrementVote()` atomically increments the ballot count.
  - `Voter::setHasVoted(true)` permanently enforces the single-vote invariant.
  - `User::authenticate(cnic, pass)` provides read-only credential comparison without leaking raw passwords.

### 1.2 🧬 Inheritance (Hierarchical Code Reusability)
- **User Hierarchy**:
  ```
  User (Abstract Base)
   ├── Voter (Specialized voter attributes: hasVoted, votedCandidateId)
   └── Admin (Specialized administrative privileges: adminKey, candidate registry)
  ```
- **Election Hierarchy**:
  ```
  Election (Base Class: duration, seats, candidate vector)
   ├── LocalElection    (Local Municipal Election: 24h duration, 5 seats)
   ├── RegionalElection (Provincial/State Election: 36h duration, 8 seats)
   └── NationalElection (Federal General Election: 48h duration, 12 seats)
  ```

### 1.3 ⚡ Polymorphism (Runtime Dynamic Dispatch)
- **Pure Virtual Functions**: Base class `User` declares:
  ```cpp
  virtual string getRole() const = 0;
  ```
  Derived classes implement their specialized roles at runtime (`"Voter"`, `"Admin"`).
- **Virtual Method Overriding**: Base class `Election` declares `virtual void displayElectionBanner() const`, allowing polymorphic pointers (`Election* currentElection`) to dynamically invoke:
  - `LocalElection::displayElectionBanner()`
  - `RegionalElection::displayElectionBanner()`
  - `NationalElection::displayElectionBanner()`

### 1.4 🧩 Abstraction (Contract Specification & Complexity Hiding)
- High-level business logic interacts with `User*` and `Election*` pointers rather than low-level concrete implementations.
- Consumers of the `Election` class do not need to know whether candidates are stored in an array or a `std::vector<Candidate>` — they interact purely through public contracts like `addCandidate()` and `displayResults()`.

---

## 📐 2. Complete UML Class Diagram

```mermaid
classDiagram
    direction TB

    class User {
        <<Abstract>>
        #string cnic
        #string password
        #string name
        +User(cnic, password, name)
        +virtual ~User()
        +setCnic(string) void
        +setPassword(string) void
        +setName(string) void
        +getCnic() string
        +getPassword() string
        +getName() string
        +virtual getRole() string*
        +authenticate(cnic, password) bool
    }

    class Voter {
        -bool hasVoted
        -int votedCandidateId
        +Voter(cnic, password, name)
        +getRole() string
        +setHasVoted(bool) void
        +getHasVoted() bool
        +setVotedCandidateId(int) void
        +getVotedCandidateId() int
    }

    class Admin {
        -string adminKey
        +Admin(cnic, password, name, adminKey)
        +getRole() string
        +getAdminKey() string
        +validateKey(string) bool
    }

    class Candidate {
        -int id
        -string name
        -string party
        -int voteCount
        +Candidate(id, name, party)
        +setId(int) void
        +setName(string) void
        +setParty(string) void
        +incrementVote() void
        +setVoteCount(int) void
        +getId() int
        +getName() string
        +getParty() string
        +getVoteCount() int
        +display() void
    }

    class Election {
        #string type
        #int durationHours
        #int maxSeats
        #vector~Candidate~ candidates
        +Election(type, durationHours, maxSeats)
        +virtual ~Election()
        +virtual displayElectionBanner() void
        +addCandidate(Candidate) bool
        +displayCandidates() void
        +displayResults() void
        +getCandidateById(int) Candidate*
        +getCandidates() vector~Candidate~
        +getType() string
        +getDurationHours() int
        +getMaxSeats() int
    }

    class LocalElection {
        +LocalElection()
        +displayElectionBanner() void
    }

    class RegionalElection {
        +RegionalElection()
        +displayElectionBanner() void
    }

    class NationalElection {
        +NationalElection()
        +displayElectionBanner() void
    }

    class EVotingSystem {
        -vector~Voter~ voters
        -vector~Admin~ admins
        -Election* currentElection
        +EVotingSystem()
        +~EVotingSystem()
        +loadData() void
        +saveData() void
        +authenticateVoter(cnic, pass) Voter*
        +authenticateAdmin(cnic, pass) Admin*
        +registerVoter() void
        +voterMenu(Voter*) void
        +adminMenu(Admin*) void
        +start() void
    }

    User <|-- Voter : Inherits
    User <|-- Admin : Inherits
    Election <|-- LocalElection : Inherits
    Election <|-- RegionalElection : Inherits
    Election <|-- NationalElection : Inherits
    Election "1" *-- "many" Candidate : Composition
    EVotingSystem "1" o-- "many" Voter : Aggregates
    EVotingSystem "1" o-- "many" Admin : Aggregates
    EVotingSystem "1" o-- "1" Election : Manages
```

---

## 🔄 3. Sequence Flow: Voting & Audit Receipt

```mermaid
sequenceDiagram
    autonumber
    actor Voter as 👤 Voter
    participant System as ⚙️ EVotingSystem
    participant Elec as 🗳️ Current Election
    participant Cand as 🎯 Candidate Object
    participant File as 📄 votes.txt Stream

    Voter->>System: 1. Login (CNIC & Password)
    System->>System: 2. Authenticate against vector<Voter>
    System-->>Voter: 3. Authentication Success (Voter session active)

    Voter->>System: 4. Request Ballot Candidates
    System->>Elec: 5. displayCandidates()
    Elec-->>Voter: 6. Output Candidate ID, Name, Party

    Voter->>System: 7. Cast Vote (Candidate ID: 101)
    System->>System: 8. Check voter->getHasVoted() == false
    System->>Elec: 9. getCandidateById(101)
    Elec->>Cand: 10. incrementVote()
    Cand-->>Elec: 11. voteCount++
    System->>System: 12. voter->setHasVoted(true)
    System->>File: 13. Append record: "CNIC,101,Dr. Eleanor Vance"
    File-->>System: 14. File I/O Confirmed

    System-->>Voter: 15. Render Digital Audit Receipt
```

---

## 💾 4. File I/O Persistence Stream Specifications

| File Name | Format / Schema | Trigger Event | Security Invariant |
| :--- | :--- | :--- | :--- |
| `votes.txt` | `[CNIC],[CANDIDATE_ID],[CANDIDATE_NAME]` | Appended on successful vote cast | Append-only; each CNIC appears at most once |
| `voters.txt` | `[CNIC],[PASSWORD_HASH],[FULL_NAME],[HAS_VOTED]` | Updated upon new voter registration or vote | Loaded into memory during system startup |

---

## 🛡️ 5. Security & Invariant Matrix

1. **One-Person One-Vote Invariant**:
   - Stored in memory via `Voter::hasVoted`.
   - Verified before displaying ballot options.
   - Any attempt to cast a second ballot emits an immediate `[WARNING] Duplicate vote rejected` alert.
2. **Abstract Role Security**:
   - `User::getRole()` is pure virtual, making direct instantiation of generic `User` objects impossible at compile time.
3. **Admin Privilege Boundary**:
   - Candidate management and election switching are restricted strictly to authenticated `Admin` sessions verifying the administrative secret key.
