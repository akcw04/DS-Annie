#ifndef CUSTOM_LISTS_HPP
#define CUSTOM_LISTS_HPP

#include <string>
#include <iostream>

// Forward declarations
struct Volunteer;
struct ReliefSite;

/**
 * Custom Singly Linked List for ReliefSites
 */
template<typename T>
struct ListNode {
    T data;
    ListNode* next;
    
    ListNode(const T& value) : data(value), next(nullptr) {}
};

template<typename T>
class CustomLinkedList {
private:
    ListNode<T>* head;
    ListNode<T>* tail;
    int count;

public:
    CustomLinkedList() : head(nullptr), tail(nullptr), count(0) {}
    
    ~CustomLinkedList() {
        clear();
    }
    
    // Copy constructor
    CustomLinkedList(const CustomLinkedList& other) : head(nullptr), tail(nullptr), count(0) {
        ListNode<T>* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }
    
    // Assignment operator
    CustomLinkedList& operator=(const CustomLinkedList& other) {
        if (this != &other) {
            clear();
            ListNode<T>* current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }
    
    void push_back(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }
    
    void push_front(const T& value) {
        ListNode<T>* newNode = new ListNode<T>(value);
        
        if (head == nullptr) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head = newNode;
        }
        count++;
    }
    
    bool empty() const {
        return head == nullptr;
    }
    
    int size() const {
        return count;
    }
    
    void clear() {
        while (head != nullptr) {
            ListNode<T>* temp = head;
            head = head->next;
            delete temp;
        }
        tail = nullptr;
        count = 0;
    }
    
    // Iterator-like access
    class Iterator {
    private:
        ListNode<T>* current;
        
    public:
        Iterator(ListNode<T>* node) : current(node) {}
        
        T& operator*() {
            return current->data;
        }
        
        const T& operator*() const {
            return current->data;
        }
        
        T* operator->() {
            return &(current->data);
        }
        
        const T* operator->() const {
            return &(current->data);
        }
        
        Iterator& operator++() {
            if (current) current = current->next;
            return *this;
        }
        
        Iterator operator++(int) {
            Iterator temp = *this;
            if (current) current = current->next;
            return temp;
        }
        
        bool operator==(const Iterator& other) const {
            return current == other.current;
        }
        
        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    
    Iterator begin() {
        return Iterator(head);
    }
    
    Iterator end() {
        return Iterator(nullptr);
    }
    
    const Iterator begin() const {
        return Iterator(head);
    }
    
    const Iterator end() const {
        return Iterator(nullptr);
    }
    
    // Array-like access by index
    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of bounds");
        }
        
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    const T& operator[](int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of bounds");
        }
        
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
    
    // Get element at index (safer version)
    T* at(int index) {
        if (index < 0 || index >= count) {
            return nullptr;
        }
        
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return &(current->data);
    }
    
    const T* at(int index) const {
        if (index < 0 || index >= count) {
            return nullptr;
        }
        
        ListNode<T>* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return &(current->data);
    }
};

/**
 * Custom Linked List for storing strings (for skill statistics)
 */
struct StringCountPair {
    std::string skill;
    int count;
    
    StringCountPair(const std::string& s, int c) : skill(s), count(c) {}
    StringCountPair() : skill(""), count(0) {}
};

/**
 * Custom Map-like structure using linked list
 */
class SkillCounter {
private:
    CustomLinkedList<StringCountPair> skillList;
    
public:
    void increment(const std::string& skill) {
        // Search for existing skill
        for (auto it = skillList.begin(); it != skillList.end(); ++it) {
            if (it->skill == skill) {
                it->count++;
                return;
            }
        }
        
        // If not found, add new skill with count 1
        skillList.push_back(StringCountPair(skill, 1));
    }
    
    int getCount(const std::string& skill) const {
        for (auto it = skillList.begin(); it != skillList.end(); ++it) {
            if (it->skill == skill) {
                return it->count;
            }
        }
        return 0;
    }
    
    // Iterator access for displaying
    CustomLinkedList<StringCountPair>::Iterator begin() {
        return skillList.begin();
    }
    
    CustomLinkedList<StringCountPair>::Iterator end() {
        return skillList.end();
    }
    
    bool empty() const {
        return skillList.empty();
    }
};

#endif // CUSTOM_LISTS_HPP