#ifndef USER_H
#define USER_H

#include <string>
using namespace std;

class User {
protected:
     int id;
     string first_name;
     string last_name;
     string phone_number;
     string email;
public:
     friend ostream& operator<<(ostream& out, const User& add_user);

     virtual void insertData() = 0;

     int getID();

     void setID(int);

     string getFirstName();

     void setFirstName(string);

     string getLastName();

     void setLastName(string);

     string getPhoneNumber();

     void setPhoneNumber(string);

     string getEmail();

     void setEmail(string);
};

#endif