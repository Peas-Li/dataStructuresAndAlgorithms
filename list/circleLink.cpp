#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr) {}
    int data_;
    Node* next_;
};

class circleLink
{
    private:
        Node* head_;
        Node* tail_;

    public:
        circleLink()
        {
            head_ = new Node();
            tail_ = head_;
            head_->next_ = head_;
        }

        ~circleLink()
        {

            Node* p = head_->next_; 
            while(p != head_)
            {
                head_->next_ = p->next_;
                delete(p);
                p = head_->next_;
            }
            delete(head_);
        }

    public:

        void insertTail(int val)
        {
            Node* node = new Node(val);
            node->next_ = head_;
            tail_->next_ = node;
            tail_ = node;
        }

        void insertHead(int val)
        {
            Node* node = new Node(val);
            node->next_ = head_->next_;
            head_->next_ = node;
            if(node->next_ == head_)
                tail_ = node;
        }

        void remove(int val)
        {
            Node* q = head_;
            Node* p = head_->next_;
            while(p != head_)
            {
                if(p->data_ == val)
                {
                    q->next_ = q->next_->next_;
                    delete(p);
                    if(q->next_ == head_)
                        tail_ = q;
                    return;
                }
                p = p->next_;
                q = q->next_;
            }
        }

        bool find(int val) const
        {
            Node* p = head_->next_;
            while(p != head_)
            {
                if(p->data_ == val)
                    return true;
                p = p->next_;
            }
            return false;
        }

        void show() const
        {
            Node* p = head_->next_;
            while(p != head_)
            {
                cout << p->data_ << " ";
                p = p->next_;
            }
            cout << endl;
        }

        void josephus(int k, int m)
        {
            Node* q = head_;
            Node* p = head_;
            int count = m;
            while(k--)
            {
                q = p;
                p = p->next_;
            }
            while(head_->next_ != head_)
            {
                count = m;
                while(--count)
                {
                    q = p;
                    p = p->next_;
                    if(p == head_)
                    {
                        q = p;
                        p = p->next_;
                    }
                }
                q->next_ = p->next_;
                cout << p->data_ << " ";
                delete(p);
                p = q->next_;
                if(p == head_)
                {
                    q = p;
                    p = p->next_;
                }
            }

            cout << endl;
        }
};

int main()
{
    circleLink clink1;
    srand(time(0));

    for(int i = 0; i < 10; i++)
    {
        clink1.insertHead(rand() % 100);
    }
    clink1.show();

    clink1.insertTail(100);
    clink1.show();

    clink1.remove(100);
    clink1.show();

    clink1.josephus(1, 2);

    circleLink clink2;
    for(int i = 1; i <= 8; i++)
        clink2.insertTail(i);
    clink2.josephus(1, 3);

    return 0;
}
