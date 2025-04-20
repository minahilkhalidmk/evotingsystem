//1stPush
#include<iostream>
using namespace std;
class User {
private:
	string cnic;
	string password;
public:
	User(string u="", string p="") :cnic(u), password(p) {}
	~User(){}

	void setcnic(string u)     { cnic = u; }
	void setpassword(string p) { password = p; }

	string getcnic()           { return cnic; }
	string getpassword()       { return password; }

};

class Voter : protected User {
private:
	bool status;
public:
	Voter():status(false){}
	~Voter(){}

	void setstatustrue() { status = true; }
	bool getstatus()     { return status; }

};


class Admin :protected User {
public:
	void createelection() {

	}
	void addcandidate() {

	}
	void viewvoting() {

	}
};
class Candidate {
	string name;
public:
	Candidate(string n=""):name(n) {}
	~Candidate(){}

};
class Election {
private:
	string type;
	int duration;
	int maxseats;
	Candidate *candidates;

public:
	Election(string t="", int d=0,int m):type(t),duration(d),maxseats(m){
		if (maxseats > 0)
		{
			candidates = new Candidate[maxseats];
	}
		else
		{
			candidates = nullptr;
		}
	}
	~Election(){}

	void settype(string t)     { type = t; }
	void setduration(int d) { duration = d; }
	void setmaxseats(int m) { maxseats=m; }
	void setcandidates(Candidate& c,int index) {
			if (index >= 0 && index < maxseats) {
				candidates[index] = c;
			}
			else {
				cout << "Invalid Index";
			}
		}
	string gettyoe()  { return type; }
	int getduration() { return duration; }
	int getmaxseats() { return maxseats; }
	//define later by name or index
	Candidate getcandidates(int index){
		return candidates[index];
	}

};

class LocalElection:protected Election {
public:
	LocalElection() { settype("Local"); }
	~LocalElection() {}
};


class RegionalElection:protected Election{
public:
	RegionalElection() { settype("Regional"); }
	RegionalElection() {}
};

class NationalElection:protected Election{
public:
	NationalElection() { settype("National"); }
	NationalElection() {}
};
 
void displayresults() {

}

int main() {
	cout << "start";
}