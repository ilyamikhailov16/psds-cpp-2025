#include <cstddef>

struct Date {
    unsigned year;
    unsigned month;
    unsigned day;

    Date(){this->year = 0u; this->month = 0u; this->day = 0u;}
    Date(unsigned year, unsigned month, unsigned day) : year(year), month(month), day(day){}

    bool operator==(Date other) const {
        if (this->year == other.year && this->month == other.month && this->day == other.day){
            return true;
        }
        return false;
    }

    bool operator!=(Date other) const {
        if (!this->operator==(other)){
            return true;
        }
        return false;
    }

    bool operator<(Date other) const {
        if (this->year < other.year){
            return true;
        } else if (this->year == other.year){
            if (this->month < other.month){
                return true;
            } else if (this->month == other.month){
                if (this->day < other.day){
                    return true;
                }
            }
        }

        return false;
    }
    
    bool operator>(Date other) const {
        if (this->year > other.year){
            return true;
        } else if (this->year == other.year){
            if (this->month > other.month){
                return true;
            } else if (this->month == other.month){
                if (this->day > other.day){
                    return true;
                }
            }
        }

        return false;
    }

    bool operator>=(Date other) const {
        if (this->operator>(other) || this->operator==(other)){
            return true;
        }
        return false;
    }

    bool operator<=(Date other) const {
        if (this->operator<(other) || this->operator==(other)){
            return true;
        }
        return false;
    }
};

struct StudentInfo {
    size_t id;
    char mark;
    int score;
    unsigned course;
    Date birth_date;

    StudentInfo(){}
    StudentInfo(size_t id, char mark, int score, unsigned course, Date birth_date) : 
    id(id), mark(mark), score(score), course(course), birth_date(birth_date){}

    bool operator==(StudentInfo other) const {
        if (this->mark == other.mark && this->score == other.score){
            return true;
        }
        return false;
    }

    bool operator!=(StudentInfo other) const {
        if (!this->operator==(other)){
            return true;
        }
        return false;
    }

    bool operator<(StudentInfo other) const {
        if (this->mark > other.mark){
            return true;
        } else if (this->mark == other.mark){
            if (this->score < other.score){
                return true;
            } else if (this->score == other.score){
                if (this->course > other.course){
                    return true;
                } else if (this->course == other.course){
                    if (this->birth_date < other.birth_date){
                        return true;
                    }
                }
            }
        }

        return false;
    }

    bool operator>(StudentInfo other) const {
        if (this->mark < other.mark){
            return true;
        } else if (this->mark == other.mark){
            if (this->score > other.score){
                return true;
            } else if (this->score == other.score){
                if (this->course < other.course){
                    return true;
                } else if (this->course == other.course){
                    if (this->birth_date > other.birth_date){
                        return true;
                    }
                }
            }
        }
    
        return false;
    }

    bool operator>=(StudentInfo other) const {
        if (this->operator>(other) || this->operator==(other)){
            return true;
        }
        return false;
    }

    bool operator<=(StudentInfo other) const {
        if (this->operator<(other) || this->operator==(other)){
            return true;
        }
        return false;
    }
};