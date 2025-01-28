#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;



int main() {

	size_t size;
	cin >> size;
	vector<int> temps(size);
	for (auto& temp : temps) {
		cin >> temp;
	}

	int64_t temp_sum = 0;
	for (size_t i = 0; i < size; ++i){
		temp_sum += temps[i];
	}

	int64_t average = temp_sum / (int) size;

	vector<int> result;
	for (size_t i = 0; i < size; ++i){
		if (temps[i] > average) {
			result.push_back((int) i);
		}
	}

	cout << result.size() << endl;

	if (!result.empty()){
		cout << result[0];
		for (size_t i = 1; i < result.size(); ++i){
			cout << " " << result[i];
		}
	}

	return 0;
}