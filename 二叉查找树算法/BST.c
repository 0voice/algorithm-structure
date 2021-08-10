//二叉查找树的创建
template<typename T>
void  BSTree<T>::createBSTreeByFile(ifstream &f){
    T e;
    queue<BSNode<T>*> q;

    while(!f.eof()){
        InputFromFile(f, e);
        Insert(root, e);
    }
}

template<typename T>
void BSTree<T>::Insert(BSNode<T>* &t, T x){//得用指针的引用，不然传参时由于形参实例化，并不能成功创建二叉树

    if(t==NULL){
        t = new BSNode<T>;
        t->data = x;
        t->lchild = t->rchild = NULL;
        return;
    }

    if(x<=t->data){
        Insert(t->lchild, x);
    }
    else{
        Insert(t->rchild, x);
    }
}

//前序遍历
template<typename T>
void BSTree<T>::PreOrderTraverse(void(*visit)(BSNode<T>&))const{
    stack<BSNode<T>*> s;
    BSNode<T> *t = root;
    while(NULL!=t || !s.empty()){
        if(NULL!=t){
            s.push(t);
            visit(*t);
            t = t->lchild;
        }
        else{
            t = s.top();
            s.pop();
            t = t->rchild;
        }
    }
    cout<<endl;
}

//中序遍历
template<typename T>
void BSTree<T>::InOrderTraverse(void(*visit)(BSNode<T>&))const{
    stack<BSNode<T>*> s;
    BSNode<T> *q;

    q = root;

    while(!s.empty()||q!=NULL){
        if(q!=NULL){
            s.push(q);
            q = q->lchild;
        }
        else{
            q = s.top();
            s.pop();
            visit(*q);
            q = q->rchild;
        }
    }
    cout<<endl;
}

//后序遍历
/*结构体部分*/
enum Tags{Left, Right};

template<typename T>struct StackElem
{
    BSNode<T> *p;
    Tags flag;
};

/*后序遍历代码部分*/
template<typename T>
void BSTree<T>::PostOrderTraverse(void(*visit)(BSNode<T>&))const{
    StackElem<T> se;
    stack<StackElem<T> > s;

    BSNode<T> *t;
    t = root;

    if(t==NULL){
        return;
    }
    while(t!=NULL||!s.empty()){
        while(t!=NULL){
            se.flag = Left;
            se.p = t;
            s.push(se);
            t = t->lchild;
        }
        se = s.top();
        s.pop();
        t = se.p;
        if(se.flag==Left){
            se.flag = Right;
            s.push(se);
            t = t->rchild;
        }
        else{
            visit(*t);
            t = NULL;
        }
    }
}

//递归前序遍历
template<typename T>
void BSTree<T>::PreTraverse(BSNode<T> *t, void(*visit)(BSNode<T>&))const{
    if(t==NULL){
        return;
    }
    else{
        visit(*t);
        PreTraverse(t->lchild, visit);
        PreTraverse(t->rchild, visit);
    }
}

//递归中序遍历
template<typename T>
void BSTree<T>::InTraverse(BSNode<T> *t, void(*visit)(BSNode<T>&))const{
    if(t==NULL){
        return;
    }
    else{
        InTraverse(t->lchild, visit);
        visit(*t);
        InTraverse(t->rchild, visit);
    }
}

//递归后序遍历
template<typename T>
void BSTree<T>::PostTraverse(BSNode<T> *t, void(*visit)(BSNode<T>&))const{
    if(t!=NULL){
        PostTraverse(t->lchild, visit);
        PostTraverse(t->rchild, visit);
        visit(*t);
    }
}
