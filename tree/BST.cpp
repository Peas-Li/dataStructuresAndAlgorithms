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
        BSTree(Node *node = nullptr, Compare comp =  Compare()) 
            : root_(node)
            , comp_(comp) {}
        ~BSTree() 
        {
            if(root_ != nullptr)
            {
                queue<Node*> q;
                q.push(root_);
                while(!q.empty())
                {
                    Node *node = q.front();
                    q.pop();
                    if(node->left_ != nullptr)
                        q.push(node->left_);
                    if(node->right_ != nullptr)
                        q.push(node->right_);
                    delete node;
                }
            }
        }

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
            cout << "前序遍历[递  归]: ";
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
            cout << "中序遍历[递  归]: ";
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
            cout << "后序遍历[递  归]: ";
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
            cout << "层序遍历[递  归]: ";
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

        //求满足区间的元素
        void findValues(vector<T> &vec, const T &i, const T &j)
        {
            findValues(vec, i, j, root_);
        }

        //是否是 BST 树
        bool isBSTree()
        {
            Node *pre = nullptr;
            return isBSTree(root_, pre);
        }

        //是否是子树
        bool isChildTree(BSTree<int> &child)
        {
            if(child.root_ == nullptr)
                return true;
            
            Node *cur = root_;
            while(cur != nullptr)
            {
                if(comp_(child.root_->data_, cur->data_))
                    cur = cur->left_;
                else if(comp_(cur->data_, child.root_->data_))
                    cur = cur->right_;
                else
                    break;
            }

            if(cur == nullptr)
                return false;
            return isChildTree(cur, child.root_);
        }
    
        //求公共父节点
        const Node *getLCA(const T &val1, const T &val2)
        {
            /* 我的非递归实现，步骤繁琐，而且需要遍历到等于给定值的节点
            stack<Node *> s1;
            stack<Node *> s2;
            Node *cur = root_;
            while(cur != nullptr)
            {
                s1.push(cur);
                if(comp_(cur->data_, val1))
                    cur = cur->right_;
                else if(comp_(val1, cur->data_))
                    cur = cur->left_;
                else
                {
                    break;
                }
            }
            if(cur == nullptr)  return nullptr;

            cur = root_;
            while(cur != nullptr)
            {
                s2.push(cur);
                if(comp_(cur->data_, val2))
                    cur = cur->right_;
                else if(comp_(val2, cur->data_))
                    cur = cur->left_;
                else
                {
                    break;
                }
            }
            if(cur == nullptr)  return nullptr;

            while(s1.size() > s2.size())
            {
                s1.pop();
            }
            while(s1.size() < s2.size())
            {
                s2.pop();
            }

            while(s1.top()->data_ != s2.top()->data_)
            {
                s1.pop();
                s2.pop();
            }
            
            return s1.top(); */
            Node *node = getLCA(root_, val1, val2);
            return node;
        }

        //镜像翻转
        void mirror01()
        {
            mirror01(root_);
        }
    
        //判断是否是镜像对称
        bool mirror02()
        {
            if(root_ == nullptr)    return true;
            return mirror02(root_->left_, root_->right_);
        }
    
        //根据前中序遍历重建二叉树
        void rebuild(T pre[], int len1, T in[], int len2)
        {
            root_ = rebuild(pre, 0, len1 - 1, in, 0, len2 - 1);
        }
    
        //判断是否是 AVL 树
        bool isAVLTree()
        {
            //我的实现接口: bool isAVLTree(Node *); 效率不高
            //return isAVLTree(root_);
            int level = 0;
            bool flag = true;
            isAVLTree(root_, level, flag);
            return flag;
        }
    
        //求中序倒数第 K 个节点
        T getKVal(int k)
        {
            Node* node = getKVal(root_, k);
            if(node == nullptr)
                throw "没有找到倒数第 K 个节点";
            return node->data_;
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

        void findValues(vector<T> &vec, const T &i, const T &j, Node *root)
        {
            if(root == nullptr)
                return;
            if(root->data_ > i)
                findValues(vec, i, j, root->left_);
            if(root->data_ >= i && root->data_ <= j)
                vec.push_back(root->data_);
            if(root->data_ < j)
                findValues(vec, i, j, root->right_);
        }

        bool isBSTree(Node *root, Node *&pre)
        {
            if(root == nullptr)
                return true;
            bool l = isBSTree(root->left_, pre);
            if(!l)  
                return false;
            if(pre != nullptr && pre->data_ > root->data_)
                return false;
            pre = root;
            bool r = isBSTree(root->right_, root);
            return l && r;
        }

        bool isChildTree(Node *rootParent, Node *rootChild)
        {
            if(rootParent == nullptr && rootChild == nullptr)
                return true;
            if(rootParent == nullptr)   return false;
            if(rootChild == nullptr)    return true;
            
            return  (rootParent->data_ == rootChild->data_) &&
                    isChildTree(rootParent->left_, rootChild->left_) &&
                    isChildTree(rootParent->right_, rootChild->right_);
        }

        Node *getLCA(Node *root, const T &val1, const T &val2)
        {
            if(root == nullptr)
                return root;
            if(comp_(root->data_, val1) && comp_(root->data_, val2))
            {
                return getLCA(root->right_, val1, val2);
            }
            else if(comp_(val1, root->data_) && comp_(val2, root->data_))
            {
                return getLCA(root->left_, val1, val2);
            }
            else
            {
                return root;
            }
        }

        void mirror01(Node *root)
        {
            if(root == nullptr)
            {
                return ;
            }

            Node *tmp = root->left_;
            root->left_ = root->right_;
            root->right_ = tmp;

            mirror01(root->right_);
            mirror01(root->left_);
        }

        bool mirror02(Node *left, Node *right)
        {
            if(left == nullptr && right == nullptr)
            {
                return true;
            }
            if(left == nullptr || right == nullptr)     return false;
            return  (left->data_ == right->data_) &&
                    mirror02(left->left_, right->right_) &&
                    mirror02(left->right_, right->left_);
        }

        Node* rebuild(T pre[], int i, int j, T in[], int p, int q)
        {
            if(i > j)   return nullptr;
            if(i == j)  return  new Node(pre[i]);;
            Node *node = new Node(pre[i]);
            int left = p;
            for(; left <= q; left++)
            { 
                if(in[left] == pre[i])  break;
            }
            node->left_ = rebuild(pre, i + 1, i + left - p, in, p, left - 1);
            node->right_ = rebuild(pre, i + left - p + 1, j, in, left + 1, q);
            return node;
        }

        bool isAVLTree(Node *root)
        {
            if(root == nullptr)     return true;
            if(!isAVLTree(root->left_))     return false;
            if(!isAVLTree(root->right_))    return false;
            int leftH = high(root->left_);
            int rightH = high(root->right_);
            return  abs(leftH - rightH) <= 1;
        }

        int isAVLTree(Node *root, int level, bool &flag)
        {
            if(root == nullptr)
                return level;
            int leftH = isAVLTree(root->left_, level + 1, flag);
            if(!flag)   return leftH;
            int rightH = isAVLTree(root->right_, level + 1, flag);
            if(!flag)   return rightH;
            if(abs(leftH - rightH) > 1) flag = false;
            return leftH > rightH ? leftH : rightH;
        }

        Node* getKVal(Node *root, int &k)
        {
            if(root == nullptr)
                return nullptr;
            Node *right = getKVal(root->right_, k);
            if(right != nullptr)    //没有返回空那就是一定找到了节点，没找到的话一定会返回空，
                return right;       //因为他会遍历完右子树的所有节点后，返回右子树最左面节点指向的空节点
            if(--k == 0)   
                return root;
            return getKVal(root->left_, k);
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

    vector<int> record;
    cout << "查找 " << 40 << " ~ " << 70 << " 范围内的数字: ";
    bst.findValues(record, 40, 70);
    for(auto v : record)
    {
        cout << v << " ";
    }
    cout << endl;

    cout << "bst  是否是BST树: " << bst.isBSTree() << endl;
    Node<int> *tmp2 = new Node(8);
    tmp2->left_ = new Node(5);
    tmp2->left_->right_ = new Node(9);
    BSTree<int> bst2(tmp2);
    cout << "bst2 是否是BST树: " << bst2.isBSTree() << endl;

    int arr2[] = {67, 62, 61, 64, 69, 78};
    BSTree<int> bst3;
    for(int v : arr2)
    {
        bst3.n_insert(v);
    }
    cout << "bst3 是否是 bst 的子树:" << bst.isChildTree(bst3) << endl;

    const Node<int> *LCA = bst.getLCA(62, 69);
    if(LCA != nullptr)
        cout << "62 和 69 的公共父节点: " << LCA->data_ << endl;
    else
        cout << "62 和 69 不存在公共父节点！" << endl;

    bst.mirror01();
    cout << "bst 镜像翻转后: " << endl;
    bst.inOrder();
    bst.mirror01();

    Node<int> *tmp4 = new Node(8);
    tmp4->left_ = new Node(5);
    tmp4->left_->right_ = new Node(4);
    tmp4->right_ = new Node(5);
    tmp4->right_->left_ = new Node(4);
    BSTree<int> bst4(tmp4);
    cout << "bst  是否镜像对称: " << bst.mirror02() << endl;
    cout << "bst4 是否镜像对称: " << bst4.mirror02() << endl;

    cout << "根据前中序遍历结果重建 bst 树:" << endl;;
    int arrPre[12] = {58, 24, 0, 5, 34, 41, 67, 62, 61, 64, 69, 78};
    int arrIn[12] = {0, 5, 24, 34, 41 ,58, 61, 62, 64, 67, 69, 78};
    BSTree<int> bst5;
    bst5.rebuild(arrPre, 12, arrIn, 12);
    bst5.inOrder();

    cout << "bst 是否是 AVL 树：";
    cout << bst.isAVLTree() << endl;
    cout << "bst 插入 6 之后，是否是 AVL 树：";
    bst.insert(6);
    cout << bst.isAVLTree() << endl;

    cout << "bst 树的倒数第 11 个节点的值: " << bst.getKVal(11) << endl;

    /*提供 lambda 比较函数 */
    function<bool(int, int)>   tmp = [](int a, int b){ return a < b; };
    BSTree<int, function<bool(int, int)>> bst6(nullptr, [](int a, int b){ return a < b; });

    return 0;
}