#include <iostream>

using namespace std;

template<class K,class V,size_t M>
struct BTreeNode
{
    //孩子的数量笔关键字的数量多一个
    pair<K,V>         _kvs[M-1];
    BTreeNode<K,V,M>* _subs[M];
    BTreeNode<K,V,M>* _parent;

    size_t _kvSize;
    BTreeNode() : _kvSize(0),_parent(nullptr)
    {
        for(size_t i = 0; i < M+1; ++i)
            _subs[i] = nullptr;
    }
};

template<class K,class V,size_t M>
class BTree
{
    typedef BTreeNode<K,V,M> Node;
    public:
    //第i个key的左孩子是subs[i]
    //第i个key的右孩子是subs[i+1]
    pair<Node*,int> Find(const K& key)
    {
        Node* parent = nullptr;
        Node* cur = _root;
        while(cur)
        {
            size_t i = 0;
            while(i < cur->_kvSize)//如果M比较大，则可以变为二分查找
            {
                if(cur->_kvs[i].first < key) // key大于当前的位置，像右走
                    ++i;
                else if(cur->_kvs[i].first > key) //如果key小于当前位置，则找左孩子
                    break;
                else 
                    return make_pair(cur,i);
            }
            parent = cur;
            cur = cur->_subs[i];
        }

        //没有找到
        return make_pair(parent,-1);
    }

    bool Insert(const pair<K,V>& kv)
    {
        if(_root == nullptr)
        {
            _root = new Node;
            _root->_kvs[0] = kv;
            _root->_kvSize = 1;

            return true;
        }

        pair<Node*,int> ret = Find(kv.first);
        //已经有了，不能插入（当前如果允许插入则就是mutil版本）
        if(ret.second >= 0)
            return false;

        //往cur中插入一个newkv
        //1. 如果cur没满就结束
        //2. 如果满了就分裂，分裂出兄弟后，往父亲插入一个关键字和孩子
        //   再满了还要继续分裂

        Node* cur = ret.first;
        pair<K,V> newkv = kv;

        Node* sub = nullptr;
        while(1)
        {
            InsertKV(cur,newkv,sub);
            if(cur->_kvSize < M) //没满，就结束
                return true;
            else
            {
                //满了，需要分裂
                //分裂出兄弟节点
                Node* newnode = new Node;

                //1.给分裂的兄弟节点拷走一半的节点
                int mid = M / 2;
                int j = 0;
                int i = mid + 1;
                for(; i < M ; ++i)
                {
                    newnode->_kvs[j] = cur->_kvs[i];
                    newnode->_subs[j] = cur->_subs[i];

                    if(newnode->_subs[j])
                        newnode->_subs[j]->_parent = newnode;
                    j++;
                    newnode->_kvSize++;
                    // ... 还要拷贝孩子
                    
                }
                //还剩最后一个右孩子
                newnode->_subs[j] = cur->_subs[i];
                if(newnode->_subs[j])
                    newnode->_subs[j]->_parent = newnode;

                cur->_kvSize = cur->_kvSize - newnode->_kvSizei - 1;
                newkv = cur->_kvs[mid];

                //1.如果cur没有父亲，则cur就是根，产生新的根
                //2.如果cur有父亲，那么就有转化成往cur的父亲中插入一个key和一个newnode 
                //3.最坏的情况就是分裂到根，原来的根分裂，产生出新的根,就结束了
                //也就是说，最多分裂高度次，因此这里的while(1)并不致命
                if(cur->_parent == nullptr)
                {
                    _root = new Node;
                    _root->_kvs[0] = newkv; 
                    _root->subs[0] = cur;
                    _root->subs[1] = newnode;
                    cur->_parent = _root;
                    newnode->_parent = _root;
                    _root->_kvSize = 1;
                    return true;
                }
                else
                {
                    //往父亲去插入newkv和newnode，转化成迭代逻辑
                    sub = newnode;
                    cur = cur->_parent;
                }
            }

        }
        return  true;
    }
    //往cur插入一个kv和sub
    void InsertKV(Node* cur,const pair<K,V>& kv,Node* sub)
    {
        int i = cur->_kvSize - 1;
        for(; i >= 0;)
        {
            //将kv找到合适的位置插入进去
            if(cur->_kvs[i].first < kv.first)
            {
                break;
            }
            else
            {
                //kv往后挪动，kv[i]的右孩子也往后挪动
                cur->_kvs[i+1] = cur->_kvs[i];
                cur->_subs[i+2] = cur->_subs[i+1];
                --i;
            }


        }
        cur->_kvs[i+1] = kv;
        cur->_subs[i+2] = sub;
        cur->_kvSize++;
        if(sub)
            sub->_parent = cur;
    }
    private:
    Node* _root = nullptr;

};
