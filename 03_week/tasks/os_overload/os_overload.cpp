#include <sstream>
#include <vector>
#include <utility>


struct Coord2D {
    int x = 0;
    int y = 0;

    Coord2D(){}
    Coord2D(int x_val, int y_val) : x(x_val), y(y_val) {}
};


struct Circle {
    Coord2D coord;
    unsigned radius = 1;

    Circle(){}
    Circle(Coord2D c_val) : coord(c_val){}
    Circle(Coord2D c_val, unsigned r_val) : coord(c_val), radius(r_val) {}
};


using CircleRegion = std::pair<Circle, bool>;
using CircleRegionList = std::vector<CircleRegion>;


std::ostream& operator<<(std::ostream& os, const Coord2D& coord) {
    os << "(" << coord.x << ", " << coord.y << ")";
    return os;
}

std::ostream& operator<<(std::ostream& os, const Circle& circle) {
    if (circle.radius == 0) {
        os << "circle[]";
    } else {
        os << "circle[" << circle.coord << ", r = " << circle.radius << "]";
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegion& region) {
    os << (region.second ? '+' : '-') << region.first;
    return os;
}

std::ostream& operator<<(std::ostream& os, const CircleRegionList& list) {
    if (list.empty()) {
        os << "{}";
    } else {
        os << "{\n";
        for (size_t i = 0; i < list.size(); ++i) {
            os << "\t" << list[i];
            if (i < list.size() - 1) {
                os << ",\n";
            } else {
                os << "\n";
            }
        }
        os << "}";
    }
    return os;
}
