#include <ios>
#include <iostream>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <set>

using namespace std;

class IgnoreSymbol {
  public:
    IgnoreSymbol(char symbol) { this->symbol = symbol; }

    friend istream& operator>>(
        istream& stream,
        const IgnoreSymbol& ignoreSymbol);

  private:
    char symbol;
};

struct Date {
  int year = 0, month = 0, day = 0;

  bool operator<(const Date& right) const {
    if (year > right.year)
      return false;
    if (year < right.year)
      return true;
    if (month > right.month)
      return false;
    if (month < right.month)
      return true;
    if (day > right.day)
      return false;
    if (day < right.day)
      return true;
    return false;
  }

  friend istream &operator>>(istream& stream, Date& date);
  friend ostream &operator<<(ostream& stream, const Date& date);
};


class DB {
  public:
    void Add(const Date& date, const string& event) { db[date].insert(event); }

    int Del(const Date& date) {
      int eventsCount = 0;
      if(db.count(date))
        eventsCount = db.at(date).size();
      db.erase(date);
      return eventsCount;
    }

    bool Del(const Date& date, const string& event) {
      if (db.count(date)) {
        return db.at(date).erase(event);
      }
      return false;
    }

    void Find(const Date& date) const {
      if (db.count(date))
        for(const auto& event : db.at(date))
          cout << event << endl;
    }

    void Print() const {
      for (auto const& [date, events] : db)
        for (const auto& event : events)
          cout << date << ' ' << event << endl;
    }

  private:
    map<Date, set<string>> db = {};
};

class Command {
  public:
    Command(DB &db) : db(db) {}

    friend istream& operator>>(istream& stream, const Command& command);

  private:
    DB &db;
};

///////////////////////// MAIN //////////////////////

int main() {
  DB db;
  Command command(db);
  while (!cin.eof()) {
    cin >> command;
  }
  return 0;
}

//////////////////////// /MAIN //////////////////////

// Realization

istream& operator>>(istream& stream, const IgnoreSymbol& ignoreSymbol) {
  char symbol;
  stream >> symbol;
  if (symbol != ignoreSymbol.symbol) {
    stream.setstate(ios_base::failbit);
  }
  return stream;
}

istream &operator>>(istream& stream, Date &date) {
  int year, month, day;
  string dateString;
  stream >> dateString;
  stringstream dateStream(dateString);
  if (dateStream >> year >> IgnoreSymbol('-') >> month >> IgnoreSymbol('-')
      >> day && dateStream.eof()) {
    if (month < 1 || month > 12) {
      cout << "Month value is invalid: " << month << endl;
      stream.setstate(ios_base::failbit);
    } else if (day < 1 || day > 31) {
      cout << "Day value is invalid: " << day << endl;
      stream.setstate(ios_base::failbit);
    } else
      date = {year, month, day};
  } else {
    cout << "Wrong date format: " << dateString << endl;
    stream.setstate(ios_base::failbit);
  }
  return stream;
}

ostream &operator<<(ostream& stream, const Date& date) {
  char ch = stream.fill();
  stream << setfill('0');
  stream << setw(4) << date.year << '-' << setw(2) << date.month
         << '-' << setw(2) << date.day;
  return stream << setfill(ch);
}

istream& operator>>(istream& stream, const Command& command) {
  string commandLine;
  std::getline(stream, commandLine);
  stringstream commandStream(commandLine);
  string commandName;
  Date date;
  commandStream >> commandName;
  if (commandName == "Add") {
    commandStream >> date;
    if (commandStream) {
      string event;
      commandStream >> event;
      command.db.Add(date, event);
    }
  } else if (commandName == "Del") {
    commandStream >> date;
    if (commandStream) {
      string event;
      if (commandStream >> event) {
        if(command.db.Del(date, event))
          cout << "Deleted successfully" << endl;
        else
          cout << "Event not found" << endl;
      } else {
        cout << "Deleted " << command.db.Del(date) << " events" << endl;
      }
    }
  } else if (commandName == "Find") {
    commandStream >> date;
    if (commandStream) {
      command.db.Find(date);
    }
  } else if (commandName == "Print") {
    string buf;
    if (!(commandStream >> buf))
      command.db.Print();
  } else if (commandName.size() > 0) {
    cout << "Unknown command: " << commandName << endl;
  }

  return stream;
}
