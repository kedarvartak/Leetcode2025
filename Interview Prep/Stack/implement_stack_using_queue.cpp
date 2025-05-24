
class QueueStack {
    queue<int> q;  

public:
    QueueStack() {} 

    void push(int x) {
        int s = q.size();
        q.push(x);

        for (int i = 0; i < s; i++) {
            q.push(q.front());
            q.pop();
        }
    }

    int pop() {
        if (q.empty()) return -1;  
        int n = q.front();
        q.pop();
        return n;
    }

    int top() {
        if (q.empty()) return -1;  
        return q.front();
    }

    bool isEmpty() {
        return q.empty();
    }
};