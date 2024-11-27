#ifndef BUFFER_H
#define BUFFER_H

#include <Arduino.h>

class buffer {
private:
    static const int MAX_SIZE = 100;
    int data[MAX_SIZE];
    int count;
    int sum;

public:
    buffer();

    void add(int number);
    void clear();
    double get_average();
    int get_count();
    int get_sum();
};

buffer::buffer() {
    count = 0;
    sum = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        data[i] = 0;
    }
}



void buffer::add(int number) {
    if (count < MAX_SIZE) {
        data[count] = number;
        count += 1;
        sum += number;
    } 
    
}

void buffer::clear() {
    count = 0;
    sum = 0;
    for (int i = 0; i < MAX_SIZE; i++) {
        data[i] = 0;
    }
}

double buffer::get_average() {
    if (count == 0) {
        return 0.0;
    }
    return (double)sum / count;
}

int buffer::get_count(){
    return count;
}

int buffer::get_sum(){
    return sum;
}



#endif
