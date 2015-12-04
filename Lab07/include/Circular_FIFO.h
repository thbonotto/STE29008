/*
 * CircularBuffer.h
 *
 *  Created on: 24 de nov de 2015
 *      Author: arliones.hoeller
 */

#ifndef LIB_CIRCULARFIFO_H_
#define LIB_CIRCULARFIFO_H_
#include <stdlib.h>
// If SIZE >= 2
template<class T, int SIZE>
class Circular_FIFO {
public:
    Circular_FIFO() : in_pos(0), out_pos(0), size(0) {}
    virtual ~Circular_FIFO() {}

    void push(T d) {
        fifo[in_pos++] = d;
        if(in_pos == SIZE) in_pos = 0;
        size++;
    }
    volatile T pop() {
        T d = fifo[out_pos++];
        if(out_pos == SIZE) out_pos = 0;
        size--;
        return d;
    }

    bool has_data() {
        return size > 0;
    }

    int available() {
        return size;
    }

    void clear() {
        in_pos = out_pos = size = 0;
    }
    void operator delete(void * p) // or delete(void *, std::size_t)
    {
      free(p);
    }

private:
    T fifo[SIZE];
    int in_pos;
    int out_pos;
    int size;
};

//If SIZE == 1
template<class T>
class Circular_FIFO<T, 1> {
public:
    void push(T d) {
        data = d;
        _has_data = true;
    }
    T pop() {
        T d = data;
        _has_data = false;
        return d;
    }

    bool has_data() {
        return _has_data;
    }

    int available() {
        if(!has_data()) return 0;
        return 1;
    }

    void clear() {
        _has_data = false;
    }

private:
    bool _has_data;
    T data;
};

#endif /* LIB_CIRCULARFIFO_H_ */
