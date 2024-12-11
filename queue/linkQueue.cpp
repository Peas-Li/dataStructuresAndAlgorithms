#include <iostream>

using namespace std;

class linkQueue
{
    private:
        struct Node
        {
            Node* pre_;
            Node* next_;
            int data_;

            Node(int val = 0)
                : pre_(nullptr)
                , next_(nullptr)
                , data_(val)
            {

            }
        };

        Node* head_;
        int size_;

    public:
        linkQueue() : size_(0)
        {
            head_ = new Node;
            head_->next_ = head_;
            head_->pre_ = head_;
        }

        ~linkQueue()
        {
            Node* p = head_->next_;

            while(p != head_)
            {
                head_->next_ = p->next_;
                p->next_->pre_ = head_;
                delete p;
                p = head_->next_;
            }
            delete head_;
            head_ = nullptr;
        }

        void push(int val)
        {
            Node* newNode = new Node(val);
            head_->pre_->next_ = newNode;
            newNode->pre_ = head_->pre_;
            newNode->next_ = head_;
            head_->pre_ = newNode;
            size_++;
        }

        void pop()
        {
            if(empty())
                throw "queue is empty!";
            Node* p = head_->next_;
            head_->next_ = p->next_;
            p->next_->pre_ = head_;
            delete p;
            size_--;
        }

        int back() const
        {
            if(empty())
                throw "queue is empty!";
            return head_->pre_->data_;
        }

        int front() const
        {
            if(empty())
                throw "queue is empty!";
            return head_->next_->data_;
        }

        bool empty() const
        {
            return head_->next_ == head_;
        }

        int size() const
        {
            return size_;
        }

        void show() const
        {
            for(Node* p = head_->next_; p != head_; p = p->next_)
            {
                cout << p->data_ << ' ';
            }

            cout << endl;
        }
};

int main()
{
    int arr[] = {12, 5, 46, 95, 48, 325, 56};
    linkQueue s;

    for(auto v : arr)
        s.push(v);

    cout << s.front() << endl;
    cout << s.back() << endl;
    s.show();

    s.pop();
    s.push(100);
    cout << s.front() << endl;
    cout << s.back() << endl;
    s.show();

    cout << s.size() << endl;

    return 0;
}