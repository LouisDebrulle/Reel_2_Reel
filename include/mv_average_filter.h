#ifndef MV_AVERAGE_FILTER_H
#define MV_AVERAGE_FILTER_H

class mv_average_filter {
private:
    int MAX_SIZE; 
    double* data;
    int count;

public:
    mv_average_filter(int _max_size) : count(0), MAX_SIZE(_max_size) {
        data = new double[MAX_SIZE];
    }

    void push(double value) {
        if (count == MAX_SIZE) {
            for (int i = MAX_SIZE - 1; i > 0; --i) {
                data[i] = data[i - 1];
            }
            data[0] = value; 
        } else {
            for (int i = count; i > 0; --i) {
                data[i] = data[i - 1];
            }
            data[0] = value;
            count++;
        }
    }

    int get_size() const {
        return count;
    }

    double get_average() const {
        if (count == 0) return 0.0; 
        double sum = 0.0;
        for (int i = 0; i < count; ++i) {
            sum += data[i];
        }
        return sum / count;
    }

    void init() {
        count = 0; 
        for (int i = 0; i < MAX_SIZE; ++i) {
            data[i] = 0.0;
        }
    }
};

#endif
