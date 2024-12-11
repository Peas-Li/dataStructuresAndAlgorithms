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
            head_->next_ = nullptr;
            head_->pre_ = nullptr;
        }

        ~doubleLink()
        {
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
            if(p->next_ != nullptr)
                p->next_->pre_ = p;
            head_->next_ = p;
            p->pre_ = head_;
        }

        void insertTail(int val)
        {
            Node* p = head_;
            Node* q = new Node(val);
            while(p->next_ != nullptr)
                p = p->next_;
            q->next_ = p->next_; //不是很需要，q初始化后，next_指向的就是nullptr
            p->next_ = q;
            q->pre_ = p;
        }

        void remove(int val)
        {
            Node* p = head_->next_;
            Node* q = nullptr;
            while(p != nullptr)
            {
                if(p->data_ == val)
                {
                    p->pre_->next_ = p->next_;
                    if(p->next_ != nullptr)
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
            while(p != nullptr && p->data_ != val)
                p = p->next_;
            if(p != nullptr) return true;
            else return false;
        }

        void show()
        {
            Node* p = head_->next_;
            while(p != nullptr)
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
    dlink.insertHead(99);
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