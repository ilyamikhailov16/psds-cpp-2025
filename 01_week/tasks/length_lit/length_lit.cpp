#include <string>


// Константы для преобразования
constexpr long double IN_TO_CM = 2.54L;
constexpr long double FT_TO_IN = 12.0L;
constexpr long double M_TO_CM = 100.0L;

// ft -> in
double operator"" _ft_to_in(long double ft_value) {
    return static_cast<double>(ft_value * FT_TO_IN);
}

// ft -> cm
double operator"" _ft_to_cm(long double ft_value) {
    return static_cast<double>(ft_value * FT_TO_IN * IN_TO_CM);
}

// ft -> m
double operator"" _ft_to_m(long double ft_value) {
    return static_cast<double>(ft_value * FT_TO_IN * IN_TO_CM / M_TO_CM);
}

// in -> ft
double operator"" _in_to_ft(long double in_value) {
    return static_cast<double>(in_value / FT_TO_IN);
}

// in -> cm
double operator"" _in_to_cm(long double in_value) {
    return static_cast<double>(in_value * IN_TO_CM);
}

// in -> m
double operator"" _in_to_m(long double in_value) {
    return static_cast<double>(in_value * IN_TO_CM / M_TO_CM);
}

// cm -> ft
double operator"" _cm_to_ft(long double cm_value) {
    return static_cast<double>(cm_value / IN_TO_CM / FT_TO_IN);
}

// cm -> in
double operator"" _cm_to_in(long double cm_value) {
    return static_cast<double>(cm_value / IN_TO_CM);
}

// cm -> m
double operator"" _cm_to_m(long double cm_value) {
    return static_cast<double>(cm_value / M_TO_CM);
}

// m -> ft
double operator"" _m_to_ft(long double m_value) {
    return static_cast<double>(m_value * M_TO_CM / IN_TO_CM / FT_TO_IN);
}

// m -> in
double operator"" _m_to_in(long double m_value) {
    return static_cast<double>(m_value * M_TO_CM / IN_TO_CM);
}

// m -> cm
double operator"" _m_to_cm(long double m_value) {
    return static_cast<double>(m_value * M_TO_CM);
}