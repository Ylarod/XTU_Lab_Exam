/**
 * @file linkedList.h
 * @author DoraLY<770848871@qq.com>
 * @brief
 * 双向链表的C++实现,因为linkedList是模板类,C++模板类的声明和实现分成两个文件会报错,所以放在一个.h文件里
 * @version 1.0
 * @date 2020-01-29
 *
 * @copyright Copyright (c) 2020
 *
 */
#ifndef __LINKEDLIST_H__  //标准头文件结构
#define __LINKEDLIST_H__  //防止重复声明
template <class T>
/**
 * @brief 链表节点
 * 
 */
class Node {
   public:
    T data;         //数据
    Node<T> *next;  //下一个节点
    Node<T> *prev;  //上一个节点
};

template <class T>
/**
 * @brief 链表类
 * 
 */
class linkedList {
   private:
    Node<T> *head;   //头结点
    Node<T> *tail;   //尾结点
    Node<T> *curse;  //光标
    int length;

   public:
    /**
     * @brief 构造函数,初始化链表
     * 
     */
    linkedList() {
        head = new Node<T>;
        tail = new Node<T>;
        head->next = tail;
        head->prev = nullptr;
        tail->next = nullptr;
        tail->prev = head;
        curse = head;
        length = 0;
    }

    /**
     * @brief 拷贝构造函数,复制链表
     * 
     * @param copy 
     */
    linkedList(const linkedList &copy) {
        Node<T> *p = copy.head->next;
        head = new Node<T>;
        Node<T> *h = head;
        while (p != nullptr) {
            Node<T> *t = new Node<T>;
            h->next = t;
            t->data = p->data;
            p = p->next;
            h = h->next;
        }
    }

    /**
     * @brief 析构函数,销毁链表
     * 
     */
    ~linkedList() {
        if (length == 0) {
            delete head;
            delete tail;
            head = nullptr;
            tail = nullptr;
            return;
        }
        while (head->next != nullptr) {
            Node<T> *temp = head;
            head = head->next;
            delete temp;
        }
        delete head;
        head = nullptr;
    }

    /**
     * @brief 向链表末尾添加数据
     * 
     * @param add_data 
     */
    void add(T add_data) {
        Node<T> *temp = this->tail;
        tail->data = add_data;
        tail->next = new Node<T>;
        Node<T> *p = tail;
        tail = tail->next;
        tail->prev = p;
        tail->next = nullptr;
        length++;
    }

    /**
     * @brief 查找结点(根据序号)
     * 
     * @param index 
     * @return T 
     */
    T find(int index) {
        if (length == 0) {
            throw "Error: linkedList is empty";
        }
        if (index >= length) {
            throw "Error: Out of bounds";
        }
        int i = 0;
        T data;
        Node<T> *p;
        if (index == 0) {
            return head->data;
        }
        if (index == length) {
            return tail->data;
        }
        //伪二分查找
        if (index < length / 2) {
            p = head->next;
            while (p->next != nullptr && i++ != index) {
                p = p->next;
            }
        } else {
            p = tail->prev;
            while (p->prev != nullptr && i++ != index) {
                p = p->prev;
            }
        }
        return p->data;
    }

    /**
     * @brief 链表是否为空
     * 
     * @return true 
     * @return false 
     */
    bool isEmpty() {
        if (length == 0) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @brief 取链表长度
     * 
     * @return int 
     */
    int size() { return length; }


    /**
     * @brief 移除某个结点
     * 
     * @param index 
     */
    void remove(T index) {
        if (length == 0) {
            throw "Error: linkedList is empty";
        }
        Node<T> *p = head;
        while (p->next != nullptr) {
            p = p->next;
            if (p->data == index) {
                Node<T> *temp = p->prev;
                temp->next = p->next;
                p->next->prev = temp;
                delete p;
                length--;
                return;
            }
        }
    }

    /**
     * @brief 移除全部结点
     * 
     */
    void removeAll() {
        if (length == 0) {
            return;
        }
        Node<T> *p = head->next;
        while (p != tail) {
            Node<T> *temp = p;
            p = p->next;
            delete temp;
        }
        head->next = tail;
        tail->prev = head;
        length = 0;
    }

    /**
     * @brief 把光标移动到指定节点处,并读取该节点的值
     * 
     * @param index 
     * @return T 
     */
    T curseTo(int index) {
        if (length == 0) {
            throw "Error: linkedList is empty";
        }
        if (index >= length) {
            throw "Error: Out of bounds";
        }
        int i = 0;
        T data;
        Node<T> *p;
        if (index == 0) {
            curse = head;
            return curse->data;
        }
        if (index == length) {
            curse = tail;
            return curse->data;
        }
        //伪二分查找
        if (index < length / 2) {
            p = head->next;
            while (p->next != nullptr && i++ != index) {
                p = p->next;
            }
        } else {
            p = tail->prev;
            while (p->prev != nullptr && i++ != index) {
                p = p->prev;
            }
        }
        curse = p;
        return curse->data;
    }

    /**
     * @brief 光标向前移动一个节点,并读取该节点的值
     * 
     * @return T 
     */
    T cursePrev() {
        if (curse->prev == nullptr) {
            throw "Error: already at head";
        }
        curse = curse->prev;
        return curse->data;
    }

    /**
     * @brief 光标向后移动一个节点,并读取该节点的值
     * 
     * @return T 
     */
    T curseNext() {
        if (curse->next == nullptr) {
            throw "Error: already at tail";
        }
        curse = curse->next;
        return curse->data;
    }

    /**
     * @brief 光标不移动,并读取该节点的值
     * 
     * @return T 
     */
    T curseRead() { return curse->data; }
};

#endif  // __LINKEDLIST_H__