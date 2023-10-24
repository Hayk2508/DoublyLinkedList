#include <cstddef>
#include <iostream>
template <typename T> class List {
    struct Node {
        T data;
        Node* next;
        Node* prev;
    };

    Node* head;
    Node* tail;
    size_t size_;

public:
    class iterator {
        Node* current;

    public:
        using value_type = T;
        using reference = T&;
        using pointer = T*;
        using difference_type = std::ptrdiff_t;
        using iterator_category = std::bidirectional_iterator_tag;

        iterator() : current(nullptr) {};
        iterator(Node* node) : current(node) {};
        reference operator*() const { return current->data; };
        pointer operator->() const { return current; }
        iterator& operator++() {
            if (current != nullptr) {
                current = current->next;
            }
            return *this;
        }

        iterator operator++(int) {
            iterator temp = *this;
            if (current != nullptr) {
                current = current->next;
            }
            return temp;
        }

        iterator& operator--() {
            if (current != nullptr) {
                current = current->prev;
            }
            return *this;
        }
        iterator& operator--(int) {
            iterator temp = *this;
            if (current != nullptr) {
                current = current->prev;
            }
            return temp;
        }
        friend bool operator==(iterator lhs, iterator rhs) {
            return lhs->current == rhs.current;
        }

        friend bool operator!=(iterator lhs, iterator rhs) {
            return !(lhs->current == rhs.current);
        }
    };

    List() : head(nullptr), tail(nullptr), size_(0) {};
    List(size_t count, const T& value = T())
        : head(nullptr), tail(nullptr), size_(0) {
        for (size_t i = 0; i < count; ++i) {
            push_back(value);
        }
    }
    List(const List& other) : size_(0), head(nullptr), tail(nullptr) {
        Node* current_ = other.head;
        while (current_) {
            push_back(current_->data);
            current_ = current_->next;
        }
    }
    List(List&& other) : size_(other.size_), head(other.head), tail(other.head) {
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;
    }
    List(std::initializer_list<T> ilist)
        : size_(0), head(nullptr), tail(nullptr) {
        for (const T& element : ilist) {
            push_back(element);
        }
    }

    ~List() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
        tail = nullptr;
        size_ = 0;
    }

    List& operator=(const List& other) {
        if (this == &other) {
            return *this;
        }
        Node* current_ = other.head;
        while (current_) {
            push_back(current_->data);
            current_ = current_->next;
        }
        return *this;
    }

    List& operator=(List&& other) {
        if (this == &other) {
            return *this;
        }
        head = other.head;
        tail = other.tail;
        size_ = other.size_;
        other.head = nullptr;
        other.tail = nullptr;
        other.size_ = 0;

        return *this;
    }
    List& operator=(std::initializer_list<T> ilist) {
        head = nullptr;
        tail = nullptr;
        size_ = 0;
        for (const T& element : ilist) {
            push_back(element);
        }
        return *this;
    }

    // Element access
    T& front() { return head->data; }
    const T& front() const { return head->data; }
    T& back() { return tail->data; }
    const T& back() const { return tail->data; }

    // Capacity
    bool empty() const { return size_ == 0; };
    size_t size() const {
        return size_;
    }

    ;

    // Modifiers chi stacvel
    // iterator insert(iterator pos, const T& value) {}
    // iterator insert(iterator pos, T&& value);
    //  iterator insert(iterator pos, std::initializer_list<T> ilist);

    void push_front(const T& value) {
        Node* tmp = new Node;
        tmp->data = value;
        tmp->next = head;
        tmp->prev = nullptr;
        if (head != nullptr) {
            head->prev = tmp;
        }
        head = tmp;
    }
    void push_front(T&& value) {
        Node* tmp = new Node;
        tmp->data = std::move(value);
        tmp->next = head;
        tmp->prev = nullptr;
        if (head != nullptr) {
            head->prev = tmp;
        }
        head = tmp;
        if (tail == nullptr) {
            tail = tmp;
        }
        ++size_;
    }
    void push_back(const T& value) {
        Node* tmp = new Node;
        tmp->data = value;
        tmp->next = nullptr;
        if (tail != nullptr) {
            tail->next = tmp;
        }
        tail = tmp;
        if (head == nullptr) {
            head = tmp;
        }
        ++size_;
    }

    void push_back(T&& value) {
        Node* tmp = new Node;
        tmp->data = std::move(value);
        tmp->next = nullptr;
        if (tail != nullptr) {
            tail->next = tmp;
        }
        tail = tmp;
        if (head == nullptr) {
            head = tmp;
        }
        ++size_;
    }

    void pop_front() {
        if (head != nullptr) {
            Node* oldHead = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            delete oldHead;
        }
        --size_;
    }
    void pop_back() {
        if (tail != nullptr) {
            Node* oldTail = tail;
            tail = tail->prev;
        }
        if (tail != nullptr) {
            tail->next = nullptr;
        }
        --size_;
    }

    // Iterators
    iterator begin() {
        iterator begin(head);
        return begin;
    }
    iterator end() {
        iterator end(tail);
        return end;
    }

    // Comparison
    friend bool operator==(const List<T>& lhs, const List<T>& rhs) {
        if (&lhs == &rhs) {
            return true;
        }
        if (lhs.size() != rhs.size()) {
            return false;
        }
        while (lhs.head) {
            if (lhs->head.data != rhs->head.data) {
                return false;
            }
            lhs->head = lhs->head->next;
            rhs->head = rhs->head->next;
        }
        return true;
    }
};
int main() {


}