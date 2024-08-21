#include <iostream>
#include "PracticeAreas.h"
using namespace std;

void PracticeAreas::setAreas() {
     int area1, area2, area3;

     cout << "\n\nIn what areas of the law does the attorney practice? Enter 1 (yes) or 0 (no) for the following: "
          << "\n\nEvictions: ";
     cin >> area1;
     while (area1 != 1 && area1 != 0) {
          cout << "Invalid input. Please enter 1 (yes) or no (0): ";
          cin >> area1;
     }
     cout << "\nUnsafe Housing: ";
     cin >> area2;
     while (area2 != 1 && area2 != 0) {
          cout << "Invalid input. Please enter 1 (yes) or no (0): ";
          cin >> area2;
     }
     cout << "\nDomestic Violence: ";
     cin >> area3;
     while (area3 != 1 && area3 != 0) {
          cout << "Invalid input. Please enter 1 (yes) or no (0): ";
          cin >> area3;
     }

     this->eviction = area1;
     this->unsafe_housing = area2;
     this->dv = area3;
}
