#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Human {
public:
	Human(const string &name, const string &occupation)
			: Name(name)
			, Occupation(occupation) {}

	void DoSomething(const string &action) const {
		cout << Occupation << ": " << Name << " " << action << endl;
	}

	virtual void Walk(const string& destination) const {
		DoSomething("walks to: " + destination);
	}

	const string Name;
	const string Occupation;
};


class Student : public Human {
public:
	Student(const string &name, const string &favouriteSong)
			: Human(name, "Student")
			, FavouriteSong(favouriteSong) {}

	void Learn() const {
		DoSomething("learns");
	}

	void SingSong() const {
		DoSomething("sings a song: " + FavouriteSong);
	}

	void Walk(const string& destination) const override {
		Human::Walk(destination);
		SingSong();
	}

	const string FavouriteSong;
};


class Teacher : public Human {
public:
	Teacher(const string &name, const string &subject)
			: Human(name, "Teacher")
			, Subject(subject) {}

	void Teach() {
		DoSomething("teaches: " + Subject);
	}

	const string Subject;
};


class Policeman : public Human {
public:
	Policeman(const string &name)
			: Human(name, "Policeman") {}

	void Check(const Human &h) const {
		DoSomething("checks " + h.Occupation + ". " + h.Occupation + "'s name is: " + h.Name);
	}
};


void VisitPlaces(const Human &h, const vector<string> &places) {
	for (auto p : places) {
		h.Walk(p);
	}
}


int main() {
	Teacher t("Jim", "Math");
	Student s("Ann", "We will rock you");
	Policeman p("Bob");

	VisitPlaces(t, {"Moscow", "London"});
	p.Check(s);
	VisitPlaces(s, {"Moscow", "London"});
	return 0;
}
