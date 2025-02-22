#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

class FunctionPart {
public:
	FunctionPart(const char& new_operation, const double& new_value) {
		operation = new_operation;
		value = new_value;
	}
	double Apply(double source_value) const {
		if (operation == '+') {
			return source_value + value;
		} else if (operation == '-') {
			return source_value - value;
		} else if (operation == '/') {
			return source_value / value;
		} else {
			return source_value * value;
		}
	}
	void Invert() {
		if (operation == '+') {
			operation = '-';
		} else if (operation == '-') {
			operation = '+';
		} else if (operation == '/') {
			operation = '*';
		} else {
			operation = '/';
		}
	}
private:
	char operation;
	double value;
};

class Function {
public:
	void AddPart(char sign, double value) {
		formula.push_back({sign, value});
	}
	void Invert() {
		for (auto& item : formula) {
			item.Invert();
		}
		reverse(begin(formula), end(formula));
	}
	double Apply(double value) const {
		for (auto& item : formula) {
			value = item.Apply(value);
		}
		return value;
	}
private:
	vector<FunctionPart> formula;
};

//struct Image {
//	double quality;
//	double freshness;
//	double rating;
//};
//
//struct Params {
//	double a;
//	double b;
//	double c;
//};
//
//Function MakeWeightFunction(const Params& params,
//							const Image& image) {
//	Function function;
//	function.AddPart('*', params.a);
//	function.AddPart('-', image.freshness * params.b);
//	function.AddPart('+', image.rating * params.c);
//	return function;
//}
//
//double ComputeImageWeight(const Params& params, const Image& image) {
//	Function function = MakeWeightFunction(params, image);
//	return function.Apply(image.quality);
//}
//
//double ComputeQualityByWeight(const Params& params,
//							  const Image& image,
//							  double weight) {
//	Function function = MakeWeightFunction(params, image);
//	function.Invert();
//	return function.Apply(weight);
//}
//
//int main() {
//	Image image = {10, 2, 6};
//	Params params = {4, 2, 6};
//	cout << ComputeImageWeight(params, image) << endl;
//	cout << ComputeQualityByWeight(params, image, 52) << endl;
//	return 0;
//}


