#include <iostream>
#include "Attorney.h"

void Attorney::insertData() {
     cout << "Enter the attorney's information below\n\n"
          << "Registration ID: ";
     cin >> id;
     cout << "\nFirst name: ";
     cin >> first_name;
     cout << "\nLast name: ";
     cin >> last_name;
     cout << "\nPhone number (enter without spaces or dashes): ";
     cin >> phone_number;
     cout << "\nEmail address: ";
     cin >> email;

     practice.setAreas();

}