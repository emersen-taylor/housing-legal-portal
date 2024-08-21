#include <iostream>
#include "Student.h"

void Student::insertData() {
     cout << "Enter the student's information below\n\n"
          << "Student ID: ";
     cin >> id;
     cout << "\nFirst name: ";
     cin >> first_name;
     cout << "\nLast name: ";
     cin >> last_name;
     cout << "\nPhone number (enter without spaces or dashes): ";
     cin >> phone_number;
     cout << "\nEmail address: ";
     cin >> email;
}