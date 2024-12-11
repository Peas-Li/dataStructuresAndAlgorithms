#include <iostream>

using namespace std;

struct Node
{
    Node(int data = 0) : data_(data), next_(nullptr)
    {
    }
    int data_;
    Node *next_;
};

class Clink
{
  public:
    Clink()
    {
        head_ = new Node;
    }

    ~Clink()
    {
        Node* p = head_;
        while(p != nullptr)
        {
            head_ = head_->next_;
            delete(p);
            p = head_;
        }
    }

    void insertTail(int val)
    {
        Node *p = head_;
        while (p->next_ != nullptr)
            p = p->next_;
        Node *node = new Node(val);
        p->next_ = node;
    }

    void insertHead(int val)
    {
        Node *node = new Node(val);
        node->next_ = head_->next_;
        head_->next_ = node;
    }

    void remove(int val)
    {
        Node *p = head_;
        Node *q = head_->next_;
        while (q!= nullptr)
        {
            if (q->data_ == val)
            {
                p->next_ = q->next_;
                delete q;
                return;
            }
            p = q;
            q = q->next_;
        }
    }

    void removeAll(int val)
    {
        Node *p = head_;
        Node *q = head_->next_;
        while (q!= nullptr)
        {
            if (q->data_ == val)
            {
                p->next_ = q->next_;
                delete q;
                q = p->next_;
            }
            else
            {
                p = q;
                q = q->next_;
            }
        }
        return;
    }

    void show()
    {
        Node *p = head_->next_;
        while (p != nullptr)
        {
            cout << p->data_ << " ";
            p = p->next_;
        }
        cout << endl;
    }

    bool find(int val)
    {
        Node* p= head_->next_;
        while(p != nullptr)
        {
            if(p->data_ == val)
            {
                return true;
            }
            p = p->next_;
        }
        return false;
    }

  private:
    Node *head_;
};

int main()
{
    Clink link;

    srand(time(0));
    for (int i = 0; i < 10; i++)
    {
        link.insertTail(rand() % 100);
    }
    link.show();

    link.insertHead(100);
    link.insertHead(100);
    link.insertHead(100);
    link.show();

    link.remove(100);
    link.show();

    link.removeAll(100);
    link.show();

    cout << link.find(100) << endl;

    return 0;
}
