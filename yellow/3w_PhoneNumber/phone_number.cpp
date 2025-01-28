#include <sstream>

#include "yellow/3w_PhoneNumber/phone_number.h"
#include "test_runner.h"

using namespace std;


PhoneNumber::PhoneNumber(const string &international_number) {
	stringstream ss(international_number);

	bool check = true;
	char sign;

	ss >> sign;

	check = sign == '+';

	check = check && getline(ss, country_code_, '-');

	check = check && getline(ss, city_code_, '-');

	check = check && getline(ss, local_number_);

	if (!check) {
		throw invalid_argument("Invalid number");
	}

}

string PhoneNumber::GetCountryCode() const {
	return country_code_;
}
string PhoneNumber::GetCityCode() const {
	return city_code_;
}
string PhoneNumber::GetLocalNumber() const {
	return local_number_;

}
string PhoneNumber::GetInternationalNumber() const {
	ostringstream os;
	os << "+" << country_code_ << "-" << city_code_ << "-" << local_number_;
	return os.str();
}


void TestPhoneNumberPositive() {
	struct Number{
		string country_code;
		string city_code;
		string local_number;
	};

	vector<Number> pn = {
			Number{"7","495", "111-22-33"},
			Number{"7","495", "1112233"},
			Number{"323", "22", "460002"},
			Number{"1", "2", "coursera-cpp"}
	};

	for (const Number& n : pn) {
		ostringstream os;
		os << "+" << n.country_code << "-" << n.city_code << "-" << n.local_number;
		PhoneNumber number(os.str());
		AssertEqual(number.GetCountryCode(), n.country_code);
		AssertEqual(number.GetCityCode(), n.city_code);
		AssertEqual(number.GetLocalNumber(), n.local_number);
		AssertEqual(number.GetInternationalNumber(), os.str());
	}
}

void TestPhoneNumberNegative() {
	vector<string> bad_numbers = {
			"1-2-333",
			"+7-1233",
			"0-0-0-0-0-0",
			" -0-0",
			" ",
	};

	for (const auto& n : bad_numbers) {
		try {
			PhoneNumber pn(n);
			Assert(false, "Not raised: " + n);
		} catch (invalid_argument&) {}
	}
}


int main() {
	TestRunner runner;
	runner.RunTest(TestPhoneNumberPositive, "TestPhoneNumberPositive");
	runner.RunTest(TestPhoneNumberNegative, "TestPhoneNumberNegative");

	return 0;
}
