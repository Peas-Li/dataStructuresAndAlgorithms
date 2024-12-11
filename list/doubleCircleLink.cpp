#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

struct Node
{
    Node(int data = 0)
        : data_(data)
        , next_(nullptr)
        , pre_(nullptr)
    {}
    int data_;
    Node* next_;
    Node* pre_;
};

class doubleLink
{
    private:
        Node* head_;
    public:
        doubleLink()
        {
            head_ = new Node;
            head_->next_ = head_;
            head_->pre_ = head_;
        }

        ~doubleLink()
        {
            head_->pre_->next_ = nullptr;
            Node* p = head_;
            while(p != nullptr)
            {
                head_ = head_->next_;
                delete p;
                p = head_;
            }
        }

    public:
        void insertHead(int val)
        {
            Node* p = new Node(val);
            p->next_ = head_->next_;
            p->next_->pre_ = p;
            head_->next_ = p;
            p->pre_ = head_;
        }

        void insertTail(int val)
        {
            Node* p = new Node(val);
            p->pre_ = head_->pre_;
            p->pre_->next_ = p;
            head_->pre_ = p;
            p->next_ = head_;
        }

        void remove(int val)
        {
            Node* p = head_->next_;
            Node* q = head_;
            while(p != head_)
            {
                if(p->data_ == val)
                {
                    p->pre_->next_ = p->next_;
                    p->next_->pre_ = p->pre_; 
                    q = p->next_;
                    delete p;
                    p = q;
                }
                else
                    p = p->next_;
            }
        }

        bool find(int val)
        {
            Node* p = head_->next_;
            while(p != head_ && p->data_ != val)
                p = p->next_;
            if(p != head_) return true;
            else return false;
        }

        void show()
        {
            Node* p = head_->next_;
            while(p != head_)
            {
                cout << p->data_ << " ";
                p = p->next_;
            }

            cout << endl;
        }
};

int main()
{
    srand(time(nullptr));

    doubleLink dlink;

    for(int i = 0; i < 10; i++)
        dlink.insertHead(rand() % 100);

    dlink.show();
    dlink.insertTail(100);
    dlink.insertTail(100);
    dlink.insertHead(99);
    dlink.insertHead(100);
    dlink.show();

    cout << dlink.find(100) << endl;
    cout << dlink.find(99) << endl;
    cout << dlink.find(1) << endl;;

    dlink.remove(100);
    dlink.remove(99);
    dlink.remove(1);
    dlink.show();

    cout << dlink.find(100) << endl;
    cout << dlink.find(99) << endl;
    cout << dlink.find(1) << endl;;

    return 0;
}