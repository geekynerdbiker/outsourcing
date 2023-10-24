#include "Student.h"
#include "Time.h"

ostream& operator<<(ostream& fout, Student& st) {
    fout << "Student [reg_id (" << setw(5) << st.get_regID() << "), ";
    fout.setf(ios::left);
    fout << setw(7) << st.get_name() << ", ";
    fout.setf(ios::right);
    fout << setw(6) << st.get_nation() << ", st_id (" << setw(6) << st.get_StID() << "), DoB" << st.get_DoB() << ", ArvTime" << st.get_ArrivalTime() << ", GPA (" << setw(4) << st.get_GPA() << ") ]";
    
    return fout;
}

Student::Student() {
    set_StID(0);
    set_GPA(0.0);
    set_ArrivalTime(Time(0, 0, 0));
    set_KeyAttr(REG_ID);
}

Student::Student(int reg_id, string n, int st_id, string country, double gpa) : Person(n) {
    set_StID(0);
    set_GPA(0.0);
    set_ArrivalTime(Time(0, 0, 0));
    set_KeyAttr(REG_ID);
}

bool Student::operator<(const Student& other) const {
    switch (this->keyAttr) {
        case REG_ID:
            if (this->get_regID() < other.get_regID())
                return true;
            return false;
        case NAME:
            if (this->get_name() < other.get_name())
                return true;
            
        case ST_ID:
            if (this->get_StID() < other.get_StID())
                return true;
            
        case NATION:
            if (this->get_nation() < other.get_nation())
                return true;
            
        case DOB:
            if (this->get_DoB() < other.get_DoB())
                return true;
            
        case ARRV_TIME:
            if (this->get_ArrivalTime() < other.get_ArrivalTime())
                return true;
            
        case GPA:
            if (this->get_GPA() < other.get_GPA())
                return true;
            
        default:
            break;
    }
    return false;
}

bool Student::operator<=(const Student& other) const {
    switch (this->keyAttr) {
        case REG_ID:
            if (this->get_regID() < other.get_regID())
                return true;
            return false;
        case NAME:
            if (this->get_name() < other.get_name())
                return true;
            
        case ST_ID:
            if (this->get_StID() < other.get_StID())
                return true;
            
        case NATION:
            if (this->get_nation() < other.get_nation())
                return true;
            
        case DOB:
            if (this->get_DoB() < other.get_DoB())
                return true;
            
        case ARRV_TIME:
            if (this->get_ArrivalTime() <= other.get_ArrivalTime())
                return true;
            
        case GPA:
            if (this->get_GPA() < other.get_GPA())
                return true;
            
        default:
            break;
    }
    return false;
}

bool Student::operator>(const Student& other) const {
    switch (this->keyAttr) {
        case REG_ID:
            if (this->get_regID() > other.get_regID())
                return true;
            return false;
        case NAME:
            if (this->get_name() > other.get_name())
                return true;
            
        case ST_ID:
            if (this->get_StID() > other.get_StID())
                return true;
            
        case NATION:
            if (this->get_nation() > other.get_nation())
                return true;
            
        case DOB:
            if (this->get_DoB() > other.get_DoB())
                return true;
            
        case ARRV_TIME:
            if (this->get_ArrivalTime() > other.get_ArrivalTime())
                return true;
            
        case GPA:
            if (this->get_GPA() > other.get_GPA())
                return true;
            
        default:
            break;
    }
    return false;
}

bool Student::operator>=(const Student& other) const {
    switch (this->keyAttr) {
        case REG_ID:
            if (this->get_regID() >= other.get_regID())
                return true;
            return false;
        case NAME:
            if (this->get_name() >= other.get_name())
                return true;
            
        case ST_ID:
            if (this->get_StID() >= other.get_StID())
                return true;
            
        case NATION:
            if (this->get_nation() >= other.get_nation())
                return true;
            
        case DOB:
            if (this->get_DoB() >= other.get_DoB())
                return true;
            
        case ARRV_TIME:
            if (this->get_ArrivalTime() >= other.get_ArrivalTime())
                return true;
            
        case GPA:
            if (this->get_GPA() >= other.get_GPA())
                return true;
            
        default:
            break;
    }
    return false;
}

bool Student::operator==(const Student& other) const {
    switch (this->keyAttr) {
        case REG_ID:
            if (this->get_regID() == other.get_regID())
                return true;
            return false;
        case NAME:
            if (this->get_name() == other.get_name())
                return true;
            
        case ST_ID:
            if (this->get_StID() == other.get_StID())
                return true;
            
        case NATION:
            if (this->get_nation() == other.get_nation())
                return true;
            
        case DOB:
            if (this->get_DoB() == other.get_DoB())
                return true;
            
        case ARRV_TIME:
            if (this->get_ArrivalTime() == other.get_ArrivalTime())
                return true;
            
        case GPA:
            if (this->get_GPA() == other.get_GPA())
                return true;
            
        default:
            break;
    }
    return false;
}

