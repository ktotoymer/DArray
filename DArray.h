//
// Created by Mikhail Alexeev on 28.09.2024.
//

#ifndef DARRAY_DARRAY_H
#define DARRAY_DARRAY_H


class DArray {
    enum {
        start_length_array = 8,
        resize_factor = 2,
        max_length_array = 30,
        value_error = 2123456789,
    };
    int *data{nullptr};
    int length{0};
    int capacity{0};

    void _resize_array(int size_new);

    class Item {
        enum type_assign {
            iadd_operator, imul_operator, idiv_operator
        };
        DArray *current{nullptr};
        int index{-1};

        int _assign_operator(int right, type_assign t);

    public:
        Item(DArray *obj, int idx) : current(obj), index(idx) {}

        int operator=(int right);

        operator int() const;

        int operator+=(int right);

        int operator*=(int right);

        int operator/=(int right);

    };

public:
    DArray() : length(0), capacity{start_length_array} {
        data = new int[capacity];
    }

    DArray(const DArray &other) : length(other.length), capacity(other.capacity) {
        data = new int[capacity];
        for (int i = 0; i < length; i++) {
            data[i] = other.data[i];
        }
    }

    ~DArray() {
        delete[] data;
    }

    int size() const;

    int capacity_ar() const;

    const int *get_data() const;

    const DArray &operator=(const DArray &right);

    Item operator[](int index) {
        return Item(this, index);
    }

    void push_back(int value);

    int pop_back();
};


#endif //DARRAY_DARRAY_H
