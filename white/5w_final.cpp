#include <iostream>
#include <exception>
#include <string>
#include <vector>
#include <set>
#include <map>
#include <sstream>
#include <iomanip>

using namespace std;

//
// There is my solution without correction
//

class Date {
public:
	Date() {}
	Date(int year, int month, int day) {
		if (!(month >= 1 && month <= 12)) {
			throw runtime_error("Month value is invalid: " + to_string(month));
			// cout << "Wrong month: " + to_string(month) << endl;
		} else if (!(day >= 1 && day <= 31)) {
			throw runtime_error("Day value is invalid: " + to_string(day));
			// cout << "Wrong day: " + to_string(day) << endl;
		} else {
			db_year = year;
			db_month = month;
			db_day = day;
		}
	}
	int GetYear() const {
		return db_year;
	}
	int GetMonth() const {
		return db_month;
	}
	int GetDay() const {
		return db_day;
	}
private:
	int db_year, db_month, db_day;
};

bool operator<(const Date& lhs, const Date& rhs) {
	if (lhs.GetYear() < rhs.GetYear()) {
		return true;
	} else if (lhs.GetYear() > rhs.GetYear()) {
		return false;
	} else {

		if (lhs.GetMonth() < rhs.GetMonth()) {
			return true;
		} else if (lhs.GetMonth() > rhs.GetMonth()) {
			return false;
		} else {

			if (lhs.GetDay() < rhs.GetDay()) {
				return true;
			} else {
				return false;
			}
		}
	}
}

istream& operator>>(istream& stream, Date& date) {
	if (stream) {
		string input;
		stream >> input;

		// check size
		if (input.empty() || input.size() > 13) {
			throw runtime_error("Wrong date format: " + input);
		}

		// check symbols
		const set<char> expected = {'-','+','0','1','2','3','4','5','6','7','8','9'};
		for (auto& symbol : input) {
			if (!expected.count(symbol)) {
				throw runtime_error("Wrong date format: " + input);
			}
		}

		// parse input
		int year, month, day;
		char dlm1, dlm2;
		stringstream ss(input);

		if (!(ss >> year >> dlm1 >> month >> dlm2 >> day)) {
			throw runtime_error("Wrong date format: " + input);
		}

		// check delimiters
		if ( dlm1 == '-' && dlm2 == '-') {
			date = Date(year, month, day);
		} else {
			throw runtime_error("Wrong date format: " + input);
		}
	}
	return stream;
}

ostream& operator<<(ostream& stream, const Date& date) {
	stream << setw(4) << setfill('0') << abs(date.GetYear()) << "-";
	stream << setw(2) << setfill('0') << date.GetMonth() << "-";
	stream << setw(2) << setfill('0') << date.GetDay();
	return stream;
}

class Database {
public:
	void AddEvent(const Date& date, const string& event) {
		database[date].insert(event);
	}

	bool DeleteEvent(const Date& date, const string& event) {
		set<string> *events;

		try {
			events = &database.at(date);
		} catch (std::out_of_range&) {
			return false;
		}

		size_t events_count = events->size();
		if (events->count(event)) {
			if (events_count == 1) {
				database.erase(date);
			} else {
				events->erase(event);
			}
			return true;
		} else {
			return false;
		}
	}
	int  DeleteDate(const Date& date) {
		set<string> *events;

		try {
			events = &database.at(date);
		} catch (std::out_of_range&) {
			return 0;
		}

		int count = events->size();
		database.erase(date);
		return count;
	}

	void Find(const Date& date) const {
		bool exception_caught = true;
		const set<string> *events;

		try {
			events = &database.at(date);
			exception_caught = false;
		} catch (std::out_of_range&) {}

		if (!exception_caught) {
			if (!events->empty()) {
				for (const auto &event: *events) {
					cout << event << endl;
				}
			}
		}
	}

	void Print() const {
		for (auto& record : database) {
			if (!record.second.empty()) {
				for (const auto &event: record.second) {
					cout << record.first << " " << event << endl;
				}
			}
		}
	}

private:
	map<Date, set<string>> database;
};

template<typename T>
void SecureInput(istream& input_stream, T& var){
	try {
		input_stream >> var;
	} catch (runtime_error& err){
		cout << err.what() << endl;
		exit(1);
	} catch (...) {
		cout << "Unhandled Error" << endl;
		exit(1);
	}
}


int main() {
	Database database;
	string command;
	while (getline(cin, command)) {
		stringstream ss(command);
		string what;
		Date date;
		string event;
		SecureInput(ss, what);
		ss.ignore(1);

		if (what == "Add") {
			SecureInput(ss, date);
			ss.ignore(1);
			SecureInput(ss, event);
			database.AddEvent(date, event);

		} else if (what == "Del") {
			SecureInput(ss, date);
			ss.ignore(1);
			if (ss.peek() == EOF) {
				int deleted_count = database.DeleteDate(date);
				cout << "Deleted " << deleted_count << " events" << endl;
			} else {
				SecureInput(ss, event);
				bool is_deleted = database.DeleteEvent(date, event);
				cout << (is_deleted ? "Deleted successfully" : "Event not found") << endl;
			}

		} else if (what == "Find") {
			SecureInput(ss, date);
			database.Find(date);

		} else if (what == "Print") {
			database.Print();

		} else if (what.empty()) {
			continue;

		} else {
			cout << "Unknown command: " << command << endl;
			return 1;
		}
	}

	return 0;
}