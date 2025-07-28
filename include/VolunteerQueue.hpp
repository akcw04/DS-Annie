#ifndef VOLUNTEER_QUEUE_HPP
#define VOLUNTEER_QUEUE_HPP

#include <string>

/**
 * Volunteer struct to store volunteer information
 */
struct Volunteer {
    std::string name;
    std::string contact;
    std::string skill;
    
    // Constructor for easy initialization
    Volunteer(const std::string& n = "", const std::string& c = "", const std::string& s = "")
        : name(n), contact(c), skill(s) {}
};

/**
 * Node struct for singly-linked list implementation
 */
struct Node {
    Volunteer data;
    Node* next;
    
    // Constructor
    Node(const Volunteer& volunteer) : data(volunteer), next(nullptr) {}
};

/**
 * Relief site struct for deployment tracking
 */
struct ReliefSite {
    std::string name;
    int currentCount;
    int maxCapacity;
    
    // Constructor
    ReliefSite(const std::string& n = "", int current = 0, int max = 0)
        : name(n), currentCount(current), maxCapacity(max) {}
};

/**
 * VolunteerQueue class - FIFO queue implementation using singly-linked list
 * No STL containers used for the core queue functionality
 */
class VolunteerQueue {
private:
    Node* head;  // Points to the front of the queue (first to be dequeued)
    Node* tail;  // Points to the rear of the queue (last enqueued)
    
public:
    /**
     * Constructor - initializes empty queue
     */
    VolunteerQueue();
    
    /**
     * Destructor - cleans up all allocated memory
     */
    ~VolunteerQueue();
    
    /**
     * Adds a volunteer to the rear of the queue
     * @param v The volunteer to add
     */
    void enqueue(const Volunteer& v);
    
    /**
     * Removes and returns the volunteer at the front of the queue
     * @return The volunteer at the front
     * @throws std::runtime_error if queue is empty
     */
    Volunteer dequeue();
    
    /**
     * Checks if the queue is empty
     * @return true if queue is empty, false otherwise
     */
    bool isEmpty() const;
    
    /**
     * Displays all volunteers in the queue from front to rear
     */
    void displayAll() const;
    
    /**
     * Returns the number of volunteers in the queue
     * @return The size of the queue
     */
    int size() const;
};

#endif // VOLUNTEER_QUEUE_HPP
