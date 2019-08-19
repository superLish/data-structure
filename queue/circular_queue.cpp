// 循环队列的实现
#include<cassert>
#include<iostream>
using namespace std;


template<class T, size_t size = 10>
class cqueue {
public:
    cqueue():front(0), rear(0) {}
    virtual ~cqueue(){}
    bool empty() const {
        return front == rear;
    }

	// 在判断是否为满队列时，有不同的方法，这里采用少用一个元素空间，约定以队列头指针在队列尾指针的下一位置作为队列满的标志。
	// 当然，也可以采用一个独立的标识位标识，这里不采取这种方法。
    bool full() const {
        return front == (rear + 1) % (size + 1);
    }

    void push(const T& e) {
        if (this->full()) 
            return;
        rear = (rear + 1) % (size + 1);
        data[rear] = e;
    }

    void pop() {
        if (empty())
            return;
        front = (front + 1) % (size + 1);        
    }

    T top() const {
        assert(!empty());
        return data[(front + 1) % (size + 1)];
    }

    void clear() {
        front = rear = 0;
    }

protected:
    int front;
    int rear;
    T data[size + 1];   //额外加了1个元素空间是为了判断队列是否已满
};

int main() {
    cqueue<int, 3> q;
    q.push(1);
    q.push(2);
    q.push(3);
    assert(q.full());
    assert(q.top() == 1);
    q.pop();
    assert(!q.full());
    assert(q.top() == 2);

    return 0;
}