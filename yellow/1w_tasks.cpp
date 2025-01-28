#include <iostream>
#include <stdexcept>
#include <vector>
#include <map>
#include <set>
#include <tuple>

using namespace std;

// Перечислимый тип для статуса задачи
enum class TaskStatus {
	NEW,          // новая
	IN_PROGRESS,  // в разработке
	TESTING,      // на тестировании
	DONE          // завершена
};

// Объявляем тип-синоним для map<TaskStatus, int>,
// позволяющего хранить количество задач каждого статуса
using TasksInfo = map<TaskStatus, int>;


class TeamTasks {
public:
	// Получить статистику по статусам задач конкретного разработчика
	const TasksInfo& GetPersonTasksInfo(const string& person) const {
		return task_base.at(person);
	}

	// Добавить новую задачу (в статусе NEW) для конкретного разработчитка
	void AddNewTask(const string& person) {
		++task_base[person][TaskStatus::NEW];
	}

	// Обновить статусы по данному количеству задач конкретного разработчика,
	// подробности см. ниже
	tuple<TasksInfo, TasksInfo> PerformPersonTasks(
			const string& person, int task_count) {

		TasksInfo updated, untouched;

		try {
			task_base.at(person);
		} catch (out_of_range&) {
			return tie(updated, untouched);
		}

		int task_to_change = 0;

		for (const auto& task : task_base[person]) {
			task_to_change += task.second;
		}

		task_to_change = min(task_to_change, task_count);

		while (task_to_change != 0) {
			if (is_ready_to_upd(task_base[person], TaskStatus::NEW)) {
				--task_base[person][TaskStatus::NEW];
				++updated[TaskStatus::IN_PROGRESS];
			} else if (is_ready_to_upd(task_base[person], TaskStatus::IN_PROGRESS)) {
				--task_base[person][TaskStatus::IN_PROGRESS];
				++updated[TaskStatus::TESTING];
			} else if (is_ready_to_upd(task_base[person], TaskStatus::TESTING)) {
				--task_base[person][TaskStatus::TESTING];
				++updated[TaskStatus::DONE];
			}
			--task_to_change;
		}

		// сохраняем untouched
		untouched = task_base[person];

		// чистим untouched от done
		for (const auto& task : task_base[person]) {
			if (task.first == TaskStatus::DONE) {
				untouched.erase(task.first);
			}
		}

		for (const auto& task : updated) {
			task_base[person][task.first] += task.second;
		}
		delete_zeros(updated);
		delete_zeros(untouched);
		delete_zeros(task_base[person]);

		return tie(updated, untouched);
	}

private:
	map<string, TasksInfo> task_base;

	void delete_zeros(TasksInfo& tasks_info) {
		TasksInfo tasks_info_copy = tasks_info;
		for (const auto& task : tasks_info_copy) {
			if (!task.second) {
				tasks_info.erase(task.first);
			}
		}
	}

	bool is_ready_to_upd(const TasksInfo& tasks_info, const TaskStatus& task_status) {
		try {
			return static_cast<bool>(tasks_info.at(task_status));
		} catch (out_of_range&) {
			return false;
		}
	}
};


// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintTasksInfo(TasksInfo tasks_info) {
	cout << tasks_info[TaskStatus::NEW] << " new tasks" <<
		 ", " << tasks_info[TaskStatus::IN_PROGRESS] << " tasks in progress" <<
		 ", " << tasks_info[TaskStatus::TESTING] << " tasks are being tested" <<
		 ", " << tasks_info[TaskStatus::DONE] << " tasks are done" << endl;
}

int main() {
	TeamTasks tasks;
	tasks.AddNewTask("Ilia");
	for (int i = 0; i < 3; ++i) {
		tasks.AddNewTask("Ivan");
	}
	cout << "Ilia's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ilia"));
	cout << "Ivan's tasks: ";
	PrintTasksInfo(tasks.GetPersonTasksInfo("Ivan"));

	TasksInfo updated_tasks, untouched_tasks;

	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	tie(updated_tasks, untouched_tasks) =
			tasks.PerformPersonTasks("Ivan", 2);
	cout << "Updated Ivan's tasks: ";
	PrintTasksInfo(updated_tasks);
	cout << "Untouched Ivan's tasks: ";
	PrintTasksInfo(untouched_tasks);

	return 0;
}