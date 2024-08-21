#include "User.h"

int User::getID() {
     return id;
}

void User::setID(int id) {
     this->id = id;
}

string User::getFirstName() {
     return first_name;
}

void User::setFirstName(string first_name) {
     this->first_name = first_name;
}

string User::getLastName() {
     return last_name;
}

void User::setLastName(string last_name) {
     this->last_name = last_name;
}

string User::getPhoneNumber() {
     return phone_number;
}

void User::setPhoneNumber(string phone_number) {
     this->phone_number = phone_number;
}

string User::getEmail() {
     return email;
}

void User::setEmail(string email) {
     this->email = email;
}
