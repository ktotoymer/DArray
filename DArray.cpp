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

const DArray &DArray::operator+=(const DArray &right) {
    int size_new = length + right.length;
    if (size_new > max_length_array)
        size_new = max_length_array;

    _resize_array(size_new);

    for (int i = length, j = 0; i < size_new; ++i, ++j)
        data[i] = right.data[j];

    length = size_new;
    return *this;
}

int DArray::Item::operator=(int right) {
    if (index < 0 || index >= max_length_array) return right;

    if (index >= current->capacity) current->_resize_array(index);

    for (int i = current->length; i < index; ++i) {
        current->data[i] = 0;
    }

    current->data[index] = right;

    if (index >= current->length)
        current->length = index + 1;

    return right;
}

DArray::Item::operator int() const {
    if (index < 0 || index >= current->length) return value_error;

    return current->data[index];
}

DArray DArray::operator+(const DArray &other) {
    int size_new = length + other.length;
    if (size_new > max_length_array) size_new = max_length_array;
    DArray arr_new = *this;
    for (int i = arr_new.length, j = 0; i < size_new; i++, j++) arr_new.data[i] = other.data[j];
    arr_new.length = size_new;
    return arr_new;
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

int DArray::Item::operator++() {
    return _increment_operator(inc_pref);
}

int DArray::Item::operator--() {
    return _increment_operator(dec_pref);
}

int DArray::Item::operator++(int) {
    return _increment_operator(inc_post);
}

int DArray::Item::operator--(int) {
    return _increment_operator(dec_post);
}

int DArray::Item::_increment_operator(DArray::Item::type_increment t) {
    if (index > current->length || index < 0) return value_error;

    int value = current->data[index];

    switch (t) {
        case inc_pref:
            current->data[index]++;
            return current->data[index];
        case dec_pref:
            current->data[index]--;
            return current->data[index];
        case inc_post:
            current->data[index]++;
            return value;
        case dec_post:
            current->data[index]--;
            return value;
        default:
            return value_error;
    }
}