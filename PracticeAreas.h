#ifndef PRACTICEAREAS_H
#define PRACTICEAREAS_H

using namespace std;

class PracticeAreas {
private:
     bool eviction;
     bool unsafe_housing;
     bool dv;
public:
     void setAreas();
     friend ostream& operator<<(ostream& out, const PracticeAreas& add_practice);
};

#endif
