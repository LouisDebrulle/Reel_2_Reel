#ifndef MV_AVERAGE_FILTER_H
#define MV_AVERAGE_FILTER_H

template <typename T, int MAX_SIZE>
class mv_average_filter {
private:
    T data[MAX_SIZE];
    int count;

public:
    mv_average_filter() : count(0) {}

    void push(T value) {
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

    T get_average() const {
        if (count == 0) return T(); // Return default value if filter is empty
        T sum = 0;
        for (int i = 0; i < count; ++i) {
            sum += data[i];
        }
        return sum / count;
    }
};

#endif
