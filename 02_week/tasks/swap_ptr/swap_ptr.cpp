template<typename T>
void SwapPtr(T*& ptr1, T*& ptr2) {
    T* temp = ptr2;
    ptr2 = ptr1;
    ptr1 = temp;
}