## 双向链表

双链表是链表的一种，由节点组成，每个数据结点中都有两个指针，分别指向直接后继和直接前驱。

![image](https://user-images.githubusercontent.com/87458342/129358264-8c0ac9a9-6b01-4759-aad0-31f09d17c5bc.png)

## 双向链表类的基本结构

```C++
template <typename T>
class DualLinkedList:public List<T>
{
protected:
  struct Node:public Object
  {
    T value;//数据域
    Node* next;//后继指针域
    Node* pre;//前驱
  };
  mutable struct:public Object
  {
    char reserved[sizeof(T)];//占位空间
    Node* next;
    Node* pre;
  }m_header;
  int m_length;
  int m_step;
  Node* m_current;
}
```

## 双向链表的操作
![image](https://user-images.githubusercontent.com/87458342/129358571-c3c9eef1-bded-4b4e-b47f-9c9e2c7b1b25.png)

![image](https://user-images.githubusercontent.com/87458342/129358650-a9adde6b-ee7e-42c7-955b-e1cd21b1a8ee.png)

