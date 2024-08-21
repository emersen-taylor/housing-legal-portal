#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "Attorney.h"
#include "Student.h"
#include "User.h"

using namespace std;

void addStudent();
void searchStudent();
void updateStudent();
void deleteStudent();
void addAttorney();
void searchAttorney();
void updateAttorney();
void deleteAttorney();
bool fileExists(string);

int main() {

     char user_entry = '0';

     while (user_entry != '9') {
          //(void)system("clear");
          cout << "\n---------- Welcome to BMCC's Housing & Legal Assistance Portal "
               "----------";
          cout << "\n\n Menu:"
               << "\n\n 1. Search for student"
               << "\n\n 2. Add new student"
               << "\n\n 3. Update existing student"
               << "\n\n 4. Delete student record"
               << "\n\n\n\n 5. Search for attorney"
               << "\n\n 6. Add new attorney"
               << "\n\n 7. Update existing attorney"
               << "\n\n 8. Delete attorney record"
               << "\n\n\n 9. Exit"
               << "\n\nWhat would you like to do? Type your choice and hit enter: ";

          cin >> user_entry;

          while (user_entry < '1' || user_entry > '9') {
               cout << "Invalid selection. Please enter a choice from 1-9 and hit "
                    "enter: ";
               cin >> user_entry;
          }

          //(void)system("clear");
          switch (user_entry) {
          case '1':
               searchStudent();
               break;
          case '2':
               addStudent();
               break;
          case '3':
               updateStudent();
               break;
          case '4':
               deleteStudent();
               break;
          case '5':
               searchAttorney();
               break;
          case '6':
               addAttorney();
               break;
          case '7':
               updateAttorney();
               break;
          case '8':
               deleteAttorney();
               break;
          case '9':
               cout << "Thank you for using BMCC's Housing & Legal Assistance Portal!";
               return 0;
          }
     }
}

void addStudent() {
     Student new_student;
     new_student.insertData();

     // creates output file stream and sets up csv file with column headers as
     // necessary

     ofstream outFile;

     if (!fileExists("students.csv")) {
          outFile.open("students.csv", ios::out);
          outFile << "student_id,first_name,last_name,phone_number,email\n";
     }
     else {
          outFile.open("students.csv", ios::app);
          outFile << "\n";
     }

     // write the new student record to the output file using the overloaded
     // insertion operator
     outFile << new_student;

     outFile.close();

     cout << "\nNew student added. Hit Enter to return to the main menu.";
     cin.ignore();
     cin.get();
}

void searchStudent() {

     ifstream inFile;
     inFile.open("students.csv");

     try {
          // checks if there are student records to be searched through and, if not,
          // throws an exception
          if (!inFile)
               throw string(
                    "No records to search. Hit enter to return to the main menu.");

          bool found = false;
          string search_id;
          cout << "Enter the student ID: ";
          cin >> search_id;

          // the code below is meant to read a line from the CSV file and store each
          // entry into a vector this way, the function can access each "column" from
          // the "row" through the vector's indeces

          vector<string> row;
          string record, entry;

          while (!inFile.eof()) {

               row.clear();

               // first, stores a row from the csv file in the "record" string
               // then, creates a string stream from "record"
               // finally, parses the "record" string stream using a comma delimiter and
               // inserts each entry from the row into the string "entry"

               getline(inFile, record);
               stringstream ss(record);
               while (getline(ss, entry, ',')) {
                    row.push_back(entry);
               }

               if (search_id == row[0]) {
                    found = true;
                    cout << "\nResults for student id " << row[0] << ": \n\n";
                    cout << "Student name: " << row[1] << " " << row[2] << "\n";
                    cout << "Phone number: " << row[3] << "\n";
                    cout << "Email: " << row[4] << "\n\n";

                    cout << "Hit enter to return to the main menu.";
               }

               inFile.peek();
          }

          if (!found) {
               cout << "Student id not found. Hit enter to return to the main menu.";
          }

          inFile.close();
     }
     catch (string noFileString) {
          cout << noFileString;
     }

     cin.ignore();
     cin.get();
}

void updateStudent() {
     // in order to update or edit the file with student records, the original file
     // must be rewritten to a new file line by line and only changed when
     // rewriting the line that needs updating. the original file is then deleted
     // and the rewritten file is renamed to the original file name

     ifstream inFile;
     inFile.open("students.csv");

     try {
          // checks if there are student records to be searched through and, if not,
          // throws an exception
          if (!inFile)
               throw string(
                    "No records to search. Hit Enter to return to the main menu.");

          ofstream outFile;
          outFile.open("newstudents.csv");

          bool found = false;
          string search_id;

          cout << "Enter the student ID: ";
          cin >> search_id;

          // the code below is meant to read a line from the CSV file and store each
          // entry into a vector this way, the function can access each "column" from
          // the "row" through the vector's indeces

          vector<string> row;
          string record, entry, test;

          while (!inFile.eof()) {
               row.clear();

               // first, stores a row from the csv file in the "record" string
               // then, creates a string stream from "record"
               // finally, parses the "record" string stream using a comma delimiter and
               // inserts each entry from the row into the string "entry"

               getline(inFile, record);
               stringstream ss(record);
               while (getline(ss, entry, ',')) {
                    row.push_back(entry);
               }

               // gathers user input for updating the row that needs updating and writes
               // into new file
               if (search_id == row[0]) {
                    found = true;
                    string temp;
                    outFile << row[0] << ",";
                    cout << "Input new information for student id " << row[0] << ": \n";
                    cout << "First name: ";
                    cin >> temp;
                    outFile << temp << ",";
                    cout << "Last name: ";
                    cin >> temp;
                    outFile << temp << ",";
                    cout << "Phone number: ";
                    cin >> temp;
                    outFile << temp << ",";
                    cout << "Email: ";
                    cin >> temp;
                    outFile << temp << "\n";
               }

               // rewrites lines that do not need to be updated into the new file
               else {
                    for (int i = 0; i < 5; i++)
                         outFile << row[i] << ",";
                    outFile << "\n";
               }
               inFile.peek();
          }

          inFile.close();
          outFile.close();
          remove("students.csv");
          rename("newstudents.csv", "students.csv");

          if (!found) {
               cout << "\nStudent id not found. Hit enter to return to the main menu.";
          }
          else {
               cout << "\nStudent information updated. Hit enter to return to the main "
                    "menu.";
          }
     }

     catch (string noFileString) {
          cout << noFileString;
     }
     cin.ignore();
     cin.get();
}

void deleteStudent() {
     // in order to update or edit the file with student records, the original file
     // must be rewritten to a new file line by line and only changed by not
     // writing the record that is to be deleted. the original file is then deleted
     // and the rewritten file is renamed to the original file name

     ifstream inFile;
     inFile.open("students.csv");

     try {
          // checks if there are student records to be searched through and, if not,
          // throws an exception
          if (!inFile)
               if (!inFile)
                    throw string(
                         "No records to search. Hit Enter to return to the main menu.");

          ofstream outFile;
          outFile.open("newstudents.csv");

          bool found = false;
          string search_id;

          cout << "Enter the student ID: ";
          cin >> search_id;

          // the code below is meant to read a line from the CSV file and store each
          // entry into a vector this way, the function can access each "column" from
          // the "row" through the vector's indeces

          vector<string> row;
          string record, entry, test;

          while (!inFile.eof()) {

               row.clear();

               // first, stores a row from the csv file in the "record" string
               // then, creates a string stream from "record"
               // finally, parses the "record" string stream using a comma delimiter and
               // inserts each entry from the row into the string "entry"

               getline(inFile, record);
               stringstream ss(record);
               while (getline(ss, entry, ',')) {
                    row.push_back(entry);
               }

               // rewrites records that do not need to be deleted
               if (search_id != row[0]) {
                    for (int i = 0; i < 5; i++)
                         outFile << row[i] << ",";
                    outFile << "\n";
               }

               // does not rewrite the record that is to be deleted
               if (search_id == row[0])
                    found = true;

               inFile.peek();
          }

          inFile.close();
          outFile.close();
          remove("students.csv");
          rename("newstudents.csv", "students.csv");

          if (!found) {
               cout << "Student id not found. Hit enter to return to the main menu.";
          }
          else {
               cout << "Student record deleted. Hit enter to return to the main menu.";
          }
     }

     catch (string noFileString) {
          cout << noFileString;
     }
     cin.ignore();
     cin.get();
}

void addAttorney() {
     Attorney new_attorney;
     new_attorney.insertData();

     // creates output file stream and sets up csv file with column headers as
     // necessary
     ofstream outFile;
     if (!fileExists("attorneys.csv")) {
          outFile.open("attorneys.csv", ios::out);
          outFile << "registration_id,first_name,last_name,phone_number,"
               << "email,eviction,unsafe_housing,dv\n";
     }
     else {
          outFile.open("attorneys.csv", ios::app);
          outFile << "\n";
     }

     // writes the new attorney record to the output file using the overloaded
     // insertion operator. an additional line for the attorney's practice areas is
     // necessary so that the insertion operator can be used for all user records
     // that are writing basic user information to a file (id, first name, last
     // name, phone number, and email)
     outFile << new_attorney;
     outFile << new_attorney.getPractice();

     outFile.close();

     cout << "\nNew attorney added. Hit Enter to return to the main menu.";
     cin.ignore();
     cin.get();
}

void searchAttorney() {
     ifstream inFile;
     inFile.open("attorneys.csv");

     try {
          // checks if there are attorney records to be searched through and, if not,
          // throws an exception
          if (!inFile)
               throw string(
                    "No records to search. Hit enter to return to the main menu.");

          bool found = false;
          string search_id;
          cout << "Enter the attorney's registration ID: ";
          cin >> search_id;

          // the code below is meant to read a line from the CSV file and store each
          // entry into a vector this way, the function can access each "column" from
          // the "row" through the vector's indeces
          vector<string> row;
          string record, entry, temp;

          while (!inFile.eof()) {

               row.clear();

               // first, stores a row from the csv file in the "record" string
               // then, creates a string stream from "record"
               // finally, parses the "record" string stream using a comma delimiter and
               // inserts each entry from the row into the string "entry"

               getline(inFile, record);
               stringstream ss(record);
               while (getline(ss, entry, ',')) {
                    row.push_back(entry);
               }

               if (search_id == row[0]) {
                    found = true;
                    cout << "\nResults for attorney registration id " << row[0] << ": \n\n";
                    cout << "Attorney name: " << row[1] << " " << row[2] << "\n";
                    cout << "Phone number: " << row[3] << "\n";
                    cout << "Email: " << row[4] << "\n\n";
                    cout << "Practice Areas:\n";
                    cout << (row[5] == "1" ? "Eviction\n" : "");
                    cout << (row[6] == "1" ? "Unsafe Housing\n" : "");
                    cout << (row[7] == "1" ? "Domestic Violence\n" : "");

                    cout << "\nHit enter to return to the main menu.";
                    cin.get();
               }
          }

          if (!found) {
               cout << "Attorney registration id not found. Hit enter to return to the "
                    "main menu.";
          }

          inFile.close();
     }
     catch (string noFileString) {
          cout << noFileString;
     }
     cin.ignore();
     cin.get();
}

void updateAttorney() {
     // in order to update or edit the file with attorney records, the original
     // file must be rewritten to a new file line by line and only changed when
     // rewriting the line that needs updating. the original file is then deleted
     // and the rewritten file is renamed to the original file name

     ifstream inFile;
     inFile.open("attorneys.csv");

     try {
          // checks if there are attorney records to be searched through and, if not,
          // throws an exception
          if (!inFile)
               throw string(
                    "No records to search. Hit Enter to return to the main menu.");

          ofstream outFile;
          outFile.open("newattorneys.csv");

          bool found = false;
          string search_id;

          cout << "Enter the attorney registration ID: ";
          cin >> search_id;

          // the code below is meant to read a line from the CSV file and store each
          // entry into a vector this way, the function can access each "column" from
          // the "row" through the vector's indeces

          vector<string> row;
          string record, entry, test;

          while (!inFile.eof()) {
               row.clear();

               // first, stores a row from the csv file in the "record" string
               // then, creates a string stream from "record"
               // finally, parses the "record" string stream using a comma delimiter and
               // inserts each entry from the row into the string "entry"
               getline(inFile, record);
               stringstream ss(record);
               while (getline(ss, entry, ',')) {
                    row.push_back(entry);
               }

               // gathers user input for updating the row that needs updating and writes
               // into new file
               if (search_id == row[0]) {
                    found = true;
                    string temp;
                    outFile << row[0] << ",";
                    cout << "Input new information for attorney registration id " << row[0]
                         << ": \n";
                    cout << "First name: ";
                    cin >> temp;
                    outFile << temp << ",";
                    cout << "Last name: ";
                    cin >> temp;
                    outFile << temp << ",";
                    cout << "Phone number: ";
                    cin >> temp;
                    outFile << temp << ",";
                    cout << "Email: ";
                    cin >> temp;
                    outFile << temp << ",";
                    cout << "Enter 1 (yes) or 0 (no) for the following practice areas\n"
                         << "Eviction: ";
                    cin >> temp;
                    outFile << temp << ",";
                    cout << "Unsafe housing: ";
                    cin >> temp;
                    outFile << temp << ",";
                    cout << "Domestic Violence: ";
                    cin >> temp;
                    outFile << temp << "\n";
               }

               // rewrites lines that do not need to be updated into the new file
               else {
                    for (int i = 0; i < 8; i++)
                         outFile << row[i] << ",";
                    outFile << "\n";
               }
               inFile.peek();
          }

          inFile.close();
          outFile.close();
          remove("attorneys.csv");
          rename("newattorneys.csv", "attorneys.csv");

          if (!found) {
               cout << "Attorney registration id not found. Hit enter to return to the "
                    "main menu.";
          }
          else {
               cout << "Attorney information updated. Hit enter to return to the main "
                    "menu.";
          }
     }

     catch (string noFileString) {
          cout << noFileString;
     }
     cin.ignore();
     cin.get();
}

void deleteAttorney() {
     // in order to update or edit the file with attorney records, the original
     // file must be rewritten to a new file line by line and only changed by not
     // rewriting the record that is to be deleted. the original file is then
     // deleted and the rewritten file is renamed to the original file name
     ifstream inFile;
     inFile.open("attorneys.csv");

     try {
          // checks if there are attorney records to be searched through and, if not,
          // throws an exception
          if (!inFile)
               if (!inFile)
                    throw string(
                         "No records to search. Hit Enter to return to the main menu.");

          ofstream outFile;
          outFile.open("newattorneys.csv");

          bool found = false;
          string search_id;

          cout << "Enter the attorney registration ID: ";
          cin >> search_id;

          // the code below is meant to read a line from the CSV file and store each
          // entry into a vector this way, the function can access each "column" from
          // the "row" through the vector's indeces

          vector<string> row;
          string record, entry, test;

          while (!inFile.eof()) {
               row.clear();

               // first, stores a row from the csv file in the "record" string
               // then, creates a string stream from "record"
               // finally, parses the "record" string stream using a comma delimiter and
               // inserts each entry from the row into the string "entry"

               getline(inFile, record);
               stringstream ss(record);
               while (getline(ss, entry, ',')) {
                    row.push_back(entry);
               }

               // rewrites records that do not need to be deleted

               if (search_id != row[0]) {
                    for (int i = 0; i < 5; i++)
                         outFile << row[i] << ",";
                    outFile << "\n";
               }

               // does not rewrite the record that is to be deleted
               if (search_id == row[0])
                    found = true;

               inFile.peek();
          }

          inFile.close();
          outFile.close();
          remove("attorneys.csv");
          rename("newattorneys.csv", "attorneys.csv");

          if (!found) {
               cout << "Attorney registration id not found. Hit enter to return to the "
                    "main menu.";
          }
          else {
               cout << "Attorney record deleted. Hit enter to return to the main menu.";
          }
     }

     catch (string noFileString) {
          cout << noFileString;
     }
     cin.ignore();
     cin.get();
}

bool fileExists(string file_name) {
     ifstream file;
     file.open(file_name, ios::in);
     if (!file)
          return false;
     else
          return true;
}

ostream& operator<<(ostream& out, const User& add_user) {
     out << add_user.id << "," << add_user.first_name << "," << add_user.last_name
          << "," << add_user.phone_number << "," << add_user.email;
     return out;
}

ostream& operator<<(ostream& out, const PracticeAreas& add_practice) {
     out << "," << add_practice.eviction << "," << add_practice.unsafe_housing
          << "," << add_practice.dv;
     return out;
}