#include <vector>
#include <stack>
#include <algorithm>


class Queue {
    std::vector<int> input;
    std::vector<int> output;

    bool eqArrays(const std::vector<int>& a, const std::vector<int>& b) const;
    std::vector<int> unionArrays(const std::vector<int>& input, const std::vector<int>& output) const;

public:
    Queue(){};
    Queue(std::vector<int> vector);
    Queue(std::stack<int> stack);
    Queue(const std::initializer_list<int>& list);
    Queue(const size_t& size);

    void Push(const int& value);

    bool Pop();

    int& Front();
    const int& Front() const;

    int& Back();
    const int& Back() const;

    bool Empty() const;

    int Size() const;

    void Clear();

    void Swap(Queue& other);

    bool operator==(const Queue& other) const;
    bool operator!=(const Queue& other) const;
};


Queue::Queue(std::vector<int> vector) : output(std::move(vector)) {
    std::reverse(output.begin(), output.end());
}

Queue::Queue(std::stack<int> stack) {
    while (!stack.empty()) {
        output.push_back(stack.top());
        stack.pop();
    }
}

Queue::Queue(const std::initializer_list<int>& list) : output(list) {
    std::reverse(output.begin(), output.end());
}

Queue::Queue(const size_t& size){
    input.reserve(size);
}

void Queue::Push(const int& value){
    input.push_back(value);
}

bool Queue::Pop(){
    if (input.empty() && output.empty()){
        return false;
    }

    if (output.empty()){
        output.reserve(input.size());
        while (!input.empty()){
            output.push_back(input.back());
            input.pop_back();
        }
    }
    
    output.pop_back();
    return true;
}

int& Queue::Front(){
    if (output.empty()){
        return input.front();
    } else {
        return output.back();
    }
}

const int& Queue::Front() const {
    if (output.empty()){
        return input.front();
    } else {
        return output.back();
    }
}

int& Queue::Back(){
    if (input.empty()){
        return output.front();
    } else {
        return input.back();
    }
}

const int& Queue::Back() const {
    if (input.empty()){
        return output.front();
    } else {
        return input.back();
    }
}

bool Queue::Empty() const {
    return (input.empty()) && (output.empty());
}

int Queue::Size() const {
    return input.size() + output.size();
}

void Queue::Clear(){
    input.clear();
    output.clear();
}

void Queue::Swap(Queue& other){
    std::vector<int> tmpInput = std::move(input);
    std::vector<int> tmpOutput = std::move(output);
    input = std::move(other.input);
    output = std::move(other.output);
    other.input = std::move(tmpInput);
    other.output = std::move(tmpOutput);
}

bool Queue::eqArrays(const std::vector<int>& a, const std::vector<int>& b) const{
    if (a.size() != b.size()){ return false; }
    if (a.empty() && b.empty()){ return true; }

    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            return false;
        }
    }
    return true;
}

std::vector<int> Queue::unionArrays(const std::vector<int>& input, const std::vector<int>& output) const {
    std::vector<int> unionArray;
    unionArray.reserve(input.size() + output.size()); 
    
    for (auto it = output.rbegin(); it != output.rend(); ++it) {
        unionArray.push_back(*it);
    }

    for (size_t i=0; i < input.size(); ++i){
        unionArray.push_back(input[i]);
    }

    return unionArray;
}

bool Queue::operator==(const Queue& other) const {
    return eqArrays(unionArrays(input, output), unionArrays(other.input, other.output));
}

bool Queue::operator!=(const Queue& other) const {
    if (*this == other){
        return false;
    }
    return true;
}