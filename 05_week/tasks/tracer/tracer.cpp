#include <string>


class Tracer {
public:
    // Конструкторы и деструктор
    Tracer();
    Tracer(const std::string& name);
    Tracer(const Tracer& other); 
    Tracer(Tracer&& other) noexcept;
    ~Tracer();

    // Операторы присваивания
    Tracer& operator=(const Tracer& other);
    Tracer& operator=(Tracer&& other) noexcept;

    // Методы
    unsigned int Id() const noexcept;
    const std::string& Name() const noexcept;
    const char* Data() const noexcept;

    // Статические методы
    static void ResetStats() noexcept;

    // Счётчики
    static unsigned int count;        // Общее количество созданных объектов
    static unsigned int default_ctor; // Количество вызовов конструктора по умолчанию
    static unsigned int str_ctor;     // Количество вызовов конструктора от строки
    static unsigned int copy_ctor;    // Количество вызовов конструктора копирования
    static unsigned int move_ctor;    // Количество вызовов конструктора перемещения
    static unsigned int copy_assign;  // Количество вызовов оператора копирующего присваивания
    static unsigned int move_assign;  // Количество вызовов оператора перемещающего присваивания
    static unsigned int dtor;         // Количество вызовов деструктора
    static unsigned int alive;        // Количество живых объектов в данный момент

private:
    unsigned int id_;  // Идентификатор объекта 
    std::string name_; // Имя объекта
};

// Определяем статические счётчики
unsigned int Tracer::count = 0;
unsigned int Tracer::default_ctor = 0;
unsigned int Tracer::str_ctor = 0;
unsigned int Tracer::copy_ctor = 0;
unsigned int Tracer::move_ctor = 0;
unsigned int Tracer::copy_assign = 0;
unsigned int Tracer::move_assign = 0;
unsigned int Tracer::dtor = 0;
unsigned int Tracer::alive = 0;

// Определяем конструкторы и деструктор
Tracer::Tracer() : id_(++count), name_("obj_" + std::to_string(id_)) {
    ++default_ctor;
    ++alive;
}

Tracer::Tracer(const std::string& name) : id_(++count), name_(name + "_" + std::to_string(id_)) {
    ++str_ctor;
    ++alive;
}

Tracer::Tracer(const Tracer& other) : id_(++count), name_(other.name_) {
    ++copy_ctor;
    ++alive;
} 

Tracer::Tracer(Tracer&& other) noexcept : id_(++count), name_(std::move(other.name_)) {
    ++move_ctor;
    ++alive;
}

Tracer::~Tracer() { 
    ++dtor; 
    --alive;
}

// Операторы присваивания
Tracer& Tracer::operator=(const Tracer& other) {
    if (this == &other) {
        return *this;
    }
    name_ = other.name_;
    ++copy_assign;
    return *this;
}

Tracer& Tracer::operator=(Tracer&& other) noexcept {
    if (this == &other) {
        return *this;
    }
    name_ = std::move(other.name_);
    ++move_assign;
    return *this;
}

// Методы
unsigned int Tracer::Id() const noexcept { return id_; }

const std::string& Tracer::Name() const noexcept { return name_; }

const char* Tracer::Data() const noexcept { return name_.data(); }

void Tracer::ResetStats() noexcept {
    count = 0;
    default_ctor = 0;
    str_ctor = 0;
    copy_ctor = 0;
    move_ctor = 0;
    copy_assign = 0;
    move_assign = 0;
    dtor = 0;
    alive = 0;
}