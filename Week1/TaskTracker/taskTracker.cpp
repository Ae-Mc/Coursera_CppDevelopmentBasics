#include "types.h"
#include <algorithm>
#include <iostream>
#include <map>
#include <ostream>
#include <string>
#include <tuple>

class TeamTasks {
  public:
    const TasksInfo& GetPersonTasksInfo(const std::string& person) const {
      return tasks.at(person);
    }

    void AddNewTask(const std::string& person) {
      tasks[person][TaskStatus::NEW]++;
    }

    void AddNewTask(const std::string& person, int count) {
      tasks[person][TaskStatus::NEW] += count;
    }

    std::tuple<TasksInfo, TasksInfo> PerformPersonTasks(
        const std::string& person,
        int taskCount) {
      auto& curPersonTasks = tasks[person];
      int tasksLeft = taskCount;
      TasksInfo modifiedTasks;
      for (int i = 0; i < 3; i++) {
        auto taskStatus = static_cast<TaskStatus>(i);
        auto nextTaskStatus = static_cast<TaskStatus>(i + 1);
        if(curPersonTasks.find(taskStatus) != curPersonTasks.end()) {
          if (tasksLeft >= curPersonTasks[taskStatus]) {
            modifiedTasks[nextTaskStatus] = curPersonTasks[taskStatus];
            curPersonTasks.erase(taskStatus);
            tasksLeft -= modifiedTasks[nextTaskStatus];
            if (tasksLeft == 0) {
              break;
            }
          } else {
            curPersonTasks[taskStatus] -= tasksLeft;
            modifiedTasks[nextTaskStatus] = tasksLeft;
            break;
          }
        }
      }
      TasksInfo untouchedTasks = curPersonTasks;

      for(int i = 0; i < 4; i++) {
        auto taskStatus = static_cast<TaskStatus>(i);
        if (modifiedTasks.find(taskStatus) != modifiedTasks.end()) {
          curPersonTasks[taskStatus] += modifiedTasks[taskStatus];
        }
      }

      untouchedTasks.erase(TaskStatus::DONE);

      return {modifiedTasks, untouchedTasks};
    }

  private:
    std::map<std::string, TasksInfo> tasks;
};

std::ostream& operator<<(std::ostream& stream, TasksInfo tasksInfo) {
  bool needComma = false;
  stream << '{';
  if(tasksInfo.find(TaskStatus::NEW) != tasksInfo.end()) {
    stream << "NEW: " << tasksInfo[TaskStatus::NEW];
    needComma = true;
  }
  if(tasksInfo.find(TaskStatus::IN_PROGRESS) != tasksInfo.end()) {
    if (needComma) {
      stream << ", ";
    }
    stream << "IN_PROGRESS: " << tasksInfo[TaskStatus::IN_PROGRESS];
    needComma = true;
  }
  if(tasksInfo.find(TaskStatus::TESTING) != tasksInfo.end()) {
    if (needComma) {
      stream << ", ";
    }
    stream << "TESTING: " << tasksInfo[TaskStatus::TESTING];
    needComma = true;
  }
  if(tasksInfo.find(TaskStatus::DONE) != tasksInfo.end()) {
    if (needComma) {
      stream << ", ";
    }
    stream << "DONE: " << tasksInfo[TaskStatus::DONE];
    needComma = true;
  }
  return stream << '}';
}

// Принимаем словарь по значению, чтобы иметь возможность
// обращаться к отсутствующим ключам с помощью [] и получать 0,
// не меняя при этом исходный словарь
void PrintPerformPersonTasksResult(std::tuple<TasksInfo, TasksInfo> result) {
  const auto& [modifiedTasks, untouchedTasks] = result;
  std::cout << "[" << modifiedTasks << ", " << untouchedTasks << "]" << std::endl;
}

int main() {
  TeamTasks tasks;
  tasks.AddNewTask("Alice", 5);
  PrintPerformPersonTasksResult(tasks.PerformPersonTasks("Alice", 5));
  tasks.AddNewTask("Alice", 5);
  PrintPerformPersonTasksResult(tasks.PerformPersonTasks("Alice", 5));
  PrintPerformPersonTasksResult(tasks.PerformPersonTasks("Alice", 1));
  std::cout << tasks.GetPersonTasksInfo("Alice") << std::endl;
  tasks.AddNewTask("Alice", 5);
  PrintPerformPersonTasksResult(tasks.PerformPersonTasks("Alice", 2));
  std::cout << tasks.GetPersonTasksInfo("Alice") << std::endl;
  PrintPerformPersonTasksResult(tasks.PerformPersonTasks("Alice", 4));
  std::cout << tasks.GetPersonTasksInfo("Alice") << std::endl;
  return 0;
}

