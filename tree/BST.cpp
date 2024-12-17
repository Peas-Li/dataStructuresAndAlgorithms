#include <iostream>
#include <functional>
#include <queue>
#include <stack>

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

        void n_insert(const T &val)
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

        void n_remove(const T &val)
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

        bool n_query(const T &val)
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

        void insert(const T &val)
        {
            root_ = insert(root_, val);
        }

        void remove(const T &val)
        {
            root_ = remove(root_, val);
        }

        bool query(const T &val)
        {
            return query(root_, val);
        }

        void n_preOrder()
        {
            cout << "前序遍历[非递归]: ";
            if(root_ == nullptr)
                return;
            stack<Node*> s;
            s.push(root_);
            while(!s.empty())
            {
                Node *node = s.top();
                cout << node->data_ << " ";
                s.pop();
                if(node->right_ != nullptr)
                    s.push(node->right_);
                if(node->left_ != nullptr)
                    s.push(node->left_);
            }
            cout << endl;
        }

        void preOrder()
        {
            cout << "前序遍历[递归]: ";
            preOrder(root_);
            cout << endl;
        }

        void n_inOrder()
        {
            cout << "中序遍历[非递归]: ";
            if(root_ == nullptr)
                return;
            stack<Node*> s;
            Node *cur = root_;

            while(!s.empty() || cur != nullptr)
            {
                if(cur != nullptr)
                {
                    s.push(cur);
                    cur = cur->left_;
                }
                else
                {
                    Node *node = s.top();
                    cout << node->data_ << " ";
                    s.pop();
                    cur = node->right_;
                }
            }
            cout << endl;
        }

        void inOrder()
        {
            cout << "中序遍历[递归]: ";
            inOrder(root_);
            cout << endl;
        }

        void n_postOrder()
        {
            if(root_ == nullptr)
            {
                return;
            }
            cout << "后序遍历[非递归]: ";
            /*
            //我的实现
            struct tag                      //记录左右状态，即左子树右子树是否遍历，避免右子树遍历完后返回父节点重复左子树遍历
            {                               //0 即为还没有遍历，1 即为已经遍历
                tag(int x = 0, int y = 0)   //都为1，则能出栈访问；
                    : right_(x)
                    , left_(y)
                { }
                int right_ = 0;
                int left_ = 0;
            };
            int n = 0;
            tag state[number()];
            stack<Node *> s;
            s.push(root_);

            while(!s.empty())
            {
                Node *node = s.top();;
                if(node->left_ != nullptr && state[n].left_ == 0)
                {
                    s.push(node->left_);
                    state[n].left_ = 1;
                    n++;
                }
                else
                {
                    
                    state[n].left_ = 1;
                    if(state[n].right_ == 1)
                    {
                        cout << node->data_ << " ";
                        s.pop();
                        state[n].left_ = 0;
                        state[n].right_ = 0;
                        n--;
                    }
                    else if(node->right_ == nullptr)
                    {
                        state[n].right_ = 1;
                    }
                    else
                    {
                        s.push(node->right_);
                        state[n].right_ = 1;
                        n++;
                    }
                }
            }*/
           
            stack<Node *> s1;
            stack<Node *> s2;
            s1.push(root_);
            while(!s1.empty())
            {
                Node *node = s1.top();
                s1.pop();
                s2.push(node);
                if(node->left_ != nullptr)
                    s1.push(node->left_);
                if(node->right_ != nullptr)
                    s1.push(node->right_);
            }
            while(!s2.empty())
            {
                Node *node = s2.top();
                s2.pop();
                cout << node->data_ << " ";
            }
            cout << endl;
        }

        void postOrder()
        {
            cout << "后序遍历[递归]: ";
            postOrder(root_);
            cout << endl;
        }

        void n_levelOrder()
        {
            cout << "层序遍历[非递归]: ";
            if(root_ == nullptr)
                return;
            queue<Node*> q;
            q.push(root_);
            while(!q.empty())
            {
                Node *node = q.front();
                cout << node->data_ << " ";
                q.pop();
                if(node->left_ != nullptr)
                    q.push(node->left_);
                if(node->right_ != nullptr)
                    q.push(node->right_);
            }
            cout << endl;
        }

        void levelOrder()
        {
            cout << "层序遍历[递归]: ";
            int h = high();
            for(int i = 0; i < h; i++)
            {
                levelOrder(root_, i);
            }
            cout << endl;
        }

        int high()
        {
            return high(root_);
        }

        int number()
        {
            return number(root_);
        }

    private:
        Node* insert(Node *root, const T &val)
        {
            if(root == nullptr)
                return new Node(val);
            if(comp_(root->data_, val))
            {
                root->right_ = insert(root->right_, val);
                return root;
            }
            else if(comp_(val, root->data_))
            {
                root->left_ = insert(root->left_, val);
                return root;
            }
            else
            {
                return root;
            }
        }

        Node* remove(Node *root, const T &val)
        {
            if(root == nullptr)
                return nullptr;
            if(comp_(root->data_, val))
            {
                root->right_ = remove(root->right_, val);
                return root;
            }
            else if(comp_(val, root->data_))
            {
                root->left_ = remove(root->left_, val);
                return root;
            }
            else
            {
                if(root->left_ != nullptr && root->right_ != nullptr)
                {
                    Node *parent = root->left_;
                    Node *leftTreeMax = root->left_;
                    while(leftTreeMax->right_ != nullptr)
                    {
                        parent = leftTreeMax;
                        leftTreeMax = leftTreeMax->right_;
                    }
                    root->data_ = leftTreeMax->data_;
                    if(parent == leftTreeMax)
                        root->left_ = remove(parent, leftTreeMax->data_);
                    else
                        leftTreeMax = remove(leftTreeMax, leftTreeMax->data_);
                    return root;
                }
                /*
                或者是
                if(root->left_ != nullptr && root->right_ != nullptr)
                {
                    Node *leftTreeMax = root->left_;
                    while(leftTreeMax->right_ != nullptr)
                    {
                        leftTreeMax = leftTreeMax->right_;
                    }
                    root->data_ = leftTreeMax->data_;
                    root->left_ = remove(root->left_, leftTreeMax->data_);
                    return root;
                }
                 */
                Node *child = root->left_;
                if(child == nullptr)
                    child = root->right_;
                delete root;
                return child;
            }
        }

        bool query(Node *root, const T &val)
        {
            if(root == nullptr)
                return false;
            if(comp_(root->data_, val))
            {
                return query(root->right_, val);
            }
            else if(comp_(val, root->data_))
            {
                return query(root->left_, val);
            }
            else
            {
                return true;
            }
        }

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
        
        void levelOrder(Node *root, int depth)
        {
            if(root == nullptr)
                return;
            if(depth == 0)
            {
                cout << root->data_ << " ";
                return;
            }
            levelOrder(root->left_, depth - 1);
            levelOrder(root->right_, depth - 1);
        }

        int high(Node *root)
        {
            if(root == nullptr)
                return 0;
            int leftLevel = high(root->left_) + 1 ;
            int rightLevel = high(root->right_) + 1 ;
            return leftLevel > rightLevel ? leftLevel : rightLevel;
        }

        int number(Node *root)
        {
            if(root == nullptr)
                return 0;
            return number(root->left_) + number(root->right_) + 1;
        }
};

int main()
{
    int arr[] = {58, 24, 67, 0, 34, 62, 69, 5, 41, 64, 78, 61};
    BSTree<int> bst;
    for(int v : arr)
    {
        bst.n_insert(v);
    }

    bst.preOrder();
    bst.n_preOrder();
    bst.inOrder();
    bst.n_inOrder();
    bst.postOrder();
    bst.n_postOrder();
    bst.levelOrder();
    bst.n_levelOrder();
    cout << "二叉树的高度: " << bst.high() << endl;
    cout << "二叉树的节点个数: " << bst.number() << endl;

    return 0;
}