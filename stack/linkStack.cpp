#include <iostream>

using namespace std;

class linkStack
{
    private:
        struct Node
        {
            Node(int data = 0) : data_(data), next_(nullptr) {}
            int data_;
            Node* next_;
        };

        Node* head_;
        int size_;

    public:
        linkStack()
        {
            head_ = new Node;
            size_ = 0;
        }

        ~linkStack()
        {
            Node* p = head_;
            while(p != nullptr)
            {
                head_ = head_->next_;
                delete(p);
                p = head_;
            }
        }

        void push(int val)
        {
            Node* p = new Node(val);
            p->next_ = head_->next_;
            head_->next_ = p;
            size_++;
        }

        void pop()
        {
            if(head_->next_ == nullptr)
                throw "stack is empty!";
            Node* p = head_->next_;
            head_->next_ = p->next_;
            delete(p);
            size_--;
        }

        int& top() const
        {
            if(head_->next_ == nullptr) 
                throw "stck is empty!";
            return head_->next_->data_;
        }

        bool empty() const
        {
            return head_->next_ == nullptr;
        }

        int size() const
        {
            return size_;
        }
};

int main()
{
    int arr[] = {12, 5, 46, 95, 48, 325, 56};
    linkStack s;

    for(auto v : arr)
        s.push(v);

    cout << s.top() << endl;
    s.pop();
    cout << s.top() << endl;
    s.push(100);
    cout << s.top() << endl;
    cout << s.size() << endl;
    cout << s.empty() << endl;

    while(!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    //cout << s.top() << endl;

    return 0;
}