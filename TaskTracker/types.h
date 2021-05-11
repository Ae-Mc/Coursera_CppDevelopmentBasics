#include <map>

enum class TaskStatus {
  NEW,
  IN_PROGRESS,
  TESTING,
  DONE
};

typedef std::map<TaskStatus, int> TasksInfo;
