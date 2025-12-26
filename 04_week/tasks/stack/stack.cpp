#include <vector>


class Stack {
    std::vector<int> stack;

public:
    void Push(const int& value);

    int& Top();
    const int& Top() const;

    int Pop();

    bool Empty() const;   

    int Size() const;   

    void Clear();
    
    void Swap(Stack& other);   

    bool operator==(const Stack& other) const;

    bool operator!=(const Stack& other) const;
};

void Stack::Push(const int& value){
    stack.push_back(value);
}

int& Stack::Top() {
    return stack.back();
}

const int& Stack::Top() const {
    return stack.back();
}

int Stack::Pop(){
    if (!Empty()){
        int value = stack.back();
        stack.pop_back();
        return value;
    }
    return 0;
}

bool Stack::Empty() const {
    return stack.empty();
}

int Stack::Size() const {
    return stack.size();
}

void Stack::Clear(){
    stack.clear();
}

void Stack::Swap(Stack& other){
    Stack tmp = std::move(*this);
    *this = std::move(other);
    other = std::move(tmp);
}

bool Stack::operator==(const Stack& other) const {
    if (Size() != other.Size()){ return false; }
    for (int i = 0; i < Size(); ++i) {
        if (stack[i] != other.stack[i]) {
            return false;
        }
    }
    return true;
}

bool Stack::operator!=(const Stack& other) const {
    return !(*this == other);
}
