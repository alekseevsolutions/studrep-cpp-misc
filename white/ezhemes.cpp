#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

	const vector<int> DAYS = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const int MONTH_COUNT = 12;
	int current_month = 0;
	vector<vector<string>> tasks(DAYS[current_month]);

	int q;

	std::cin >> q;

	for (int i = 0; i < q; ++i) {
		std::string operation;
		std::cin >> operation;

		if (operation == "ADD") {
			int day;
			std::string task;
			std::cin >> day >> task;
			tasks[--day].push_back(task);
		}

		if (operation == "DUMP") {
			int day;
			std::cin >> day;

			std::cout << tasks[day - 1].size();
			for (const std::string &task: tasks[day - 1]) {
				std::cout << " " << task;
			}
			std::cout << std::endl;
		}

		if (operation == "NEXT") {

			vector<vector<string>> new_tasks;

			const int prev_month = current_month;

			current_month = (prev_month + 1) % MONTH_COUNT;

			new_tasks = tasks;
			new_tasks.resize(DAYS[current_month]);

			if (DAYS[prev_month] > DAYS[current_month]) {

				vector<string>& last_day = new_tasks[DAYS[current_month] - 1];

				for (int d = DAYS[current_month]; d < DAYS[prev_month]; ++d) {
//					for (const string &task: tasks[d]) {
//						last_day->push_back(task);
//					}
					last_day.insert(end(last_day), begin(tasks[d]), end(tasks[d]));
				}
			}

			tasks.clear();
			tasks = new_tasks;
		}

	}

	return 0;
}
