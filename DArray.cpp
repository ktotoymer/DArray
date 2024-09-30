//
// Created by Mikhail Alexeev on 28.09.2024.
//

#include "DArray.h"

void DArray::_resize_array(int size_new) {
    if (size_new <= capacity) return;

    while (capacity < size_new) {
        capacity *= resize_factor;
        if (capacity > max_length_array) {
            capacity = max_length_array;
            break;
        }
    }

    int *p = new int[capacity];
    for (int i = 0; i < length; ++i)
        p[i] = data[i];

    delete[] data;
    data = p;
}

int DArray::size() const {
    return length;
}

int DArray::capacity_ar() const {
    return capacity;
}

const int *DArray::get_data() const {
    return data;
}

const DArray &DArray::operator=(const DArray &right) {
    if (this == &right) return right;

    length = right.length;
    capacity = right.capacity;

    delete[] data;
    data = new int[capacity];

    for (int i = 0; i < length; ++i)
        data[i] = right.data[i];

    return *this;
}

void DArray::push_back(int value) {
    if (length >= capacity)
        _resize_array(capacity * resize_factor);

    if (length < capacity)
        data[length++] = value;
}

int DArray::pop_back() {
    if (length > 0) return data[--length];
    return value_error;
}

int DArray::Item::operator=(int right) {
    if (index < 0 || index >= max_length_array) return right;

    if (index >= current->capacity) current->_resize_array(index);

    for (int i = current->length; i < index; ++i){
        current->data[i] = 0;
    }

    current->data[index] = right;

    if (index >= current->length)
        current->length = index + 1;

    return right;
}

DArray::Item::operator int() const{
    if (index < 0 || index >= current->length) return value_error;

    return current->data[index];
}

int DArray::Item::_assign_operator(int right, DArray::Item::type_assign t) {
    if (index >= current->capacity || index < 0) return value_error;
    switch (t) {
        case iadd_operator:
            current->data[index] += right;
            break;
        case imul_operator:
            current->data[index] *= right;
            break;
        case idiv_operator:
            current->data[index] /= right;
            break;
    }
    return current->data[index];
}

int DArray::Item::operator+=(int right) {
    return _assign_operator(right, iadd_operator);
}

int DArray::Item::operator*=(int right) {
    return _assign_operator(right, imul_operator);;
}

int DArray::Item::operator/=(int right) {
    return _assign_operator(right, idiv_operator);;
}
