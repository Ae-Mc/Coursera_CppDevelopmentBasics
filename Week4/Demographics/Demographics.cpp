#include <algorithm>
#include <vector>
#include <iostream>
// #include "utils.h"

using namespace std;

void PrintStats(vector<Person> persons) {
    cout << "Median age = " << ComputeMedianAge(persons.begin(), persons.end()) << endl;

    auto malesStart = partition(persons.begin(), persons.end(), [](auto person) {
        return person.gender == Gender::FEMALE;
    });
    cout << "Median age for females = " << ComputeMedianAge(persons.begin(), malesStart) << endl;
    cout << "Median age for males = " << ComputeMedianAge(malesStart, persons.end()) << endl;

    auto unemployedFemalesStart = partition(persons.begin(), malesStart, [](auto female) {
        return female.is_employed;
    });
    cout << "Median age for employed females = " << ComputeMedianAge(persons.begin(), unemployedFemalesStart) << endl;
    cout << "Median age for unemployed females = " << ComputeMedianAge(unemployedFemalesStart, malesStart) << endl;

    auto unemployedMalesStart = partition(malesStart, persons.end(), [](auto male) {
        return male.is_employed;
    });
    cout << "Median age for employed males = " << ComputeMedianAge(malesStart, unemployedMalesStart) << endl;
    cout << "Median age for unemployed males = " << ComputeMedianAge(unemployedMalesStart, persons.end()) << endl;
}

/*
int main() {
  vector<Person> persons = {
      {31, Gender::MALE, false},
      {40, Gender::FEMALE, true},
      {24, Gender::MALE, true},
      {20, Gender::FEMALE, true},
      {80, Gender::FEMALE, false},
      {78, Gender::MALE, false},
      {10, Gender::FEMALE, false},
      {55, Gender::MALE, true},
  };
  PrintStats(persons);
  return 0;
}
*/
