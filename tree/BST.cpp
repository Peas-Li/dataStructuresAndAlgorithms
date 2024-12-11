#include <iostream>
#include <functional>

using namespace std;

template<class T>
struct Node
{
    Node(T data = T())
        : data_(data)
        , left_(nullptr)
        , right_(nullptr)
    {

    }
    T data_;
    Node *left_;
    Node *right_;
};

template<typename T, typename Compare = less<T>>
class BSTree
{
    typedef Node<T> Node;

    private:
        Node *root_;
        Compare comp_;

    public:
        BSTree() : root_(nullptr), comp_(Compare()) {}
        ~BSTree() {}

        void insert(const T &val)
        {
            if(root_ == nullptr)
            {
                root_ = new Node(val);
                return ;
            }

            Node *parent = nullptr;
            Node *node = root_;
            while(node != nullptr)
            {
                if(comp_(val, node->data_)) 
                {
                    parent = node;
                    node = node->left_;
                }
                else if(comp_(node->data_, val)) 
                 {
                    parent = node;
                    node = node->right_;
                }
                else
                    return;
            }
            if(comp_(val, parent->data_))
                parent->left_ = new Node(val);
            else
                parent->right_ = new Node(val);
        }

        void remove(const T &val)
        {
            if(root_ == nullptr)
            {
                return ;
            }

            Node *parent = nullptr;
            Node *cur = root_;
            while(cur != nullptr)
            {
                if(comp_(val, cur->data_))
                {
                    parent = cur;
                    cur = cur->left_;
                }
                if(comp_(cur->data_, val))
                {
                    parent = cur;
                    cur = cur->right_;
                }
                else
                    break;
            }

            if(cur == nullptr) return;

            if(cur->left_ != nullptr && cur->right_ != nullptr)
            {
                parent = cur;
                Node *pre = cur->left_;
                while(pre->right_ != nullptr)
                {
                    parent = pre;
                    pre = pre->right_;
                }
                cur->data_ = pre->data_;
                cur = pre;
            }
            Node *child = cur->left_;
            if(child == nullptr)
                child = cur->right_;

            if(parent == nullptr)
            {
                root_ = child;
            }
            else
            {
                if(parent->left_ == cur)
                    parent->left_ = child;
                else
                    parent->right_ = child;
            }
            delete cur;
        }

        bool query(const T &val)
        {
            Node *cur = root_;
            while(cur != nullptr)
            {
                if(comp_(cur->data_, val))
                    cur = cur->right_;
                else if(comp_(val, cur->data_))
                    cur = cur->left_;
                else
                    return true;
            }
            return false;
        }

        void preOrder()
        {
            cout << "前序遍历: ";
            preOrder(root_);
            cout << endl;
        }

        void inOrder()
        {
            cout << "前序遍历:  ";
            inOrder(root_);
            cout << endl;
        }

        void postOrder()
        {
            cout << "前序遍历:  ";
            postOrder(root_);
            cout << endl;
        }

    private:
        void preOrder(Node *root)
        {
            if(root != nullptr)
            {
                cout << root->data_ << " ";
                preOrder(root->left_);
                preOrder(root->right_);
            }
        }

        void inOrder(Node *root)
        {
            if(root != nullptr)
            {
                inOrder(root->left_);
                cout << root->data_ << " ";
                inOrder(root->right_);
            }
        }

        void postOrder(Node *root)
        {
            if(root != nullptr)
            {
                postOrder(root->left_);
                postOrder(root->right_);
                cout << root->data_ << " ";
            }
        }
};

int main()
{
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78};
    BSTree<int> bst;
    for(int v : arr)
    {
        bst.insert(v);
    }

    bst.preOrder();
    bst.inOrder();
    bst.postOrder();

    bst.insert(12);
    bst.remove(67);
    bst.remove(64);
    bst.remove(58);

    cout << bst.query(100) << endl;
    cout << bst.query(58) << endl;
    cout << bst.query(12) << endl;

    return 0;
}