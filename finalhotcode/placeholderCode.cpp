#include <iostream>

template <typename T>
class Queue
{
private:
    struct Node
    {
        T data;
        Node *next;
        Node(const T &item) : data(item), next(nullptr) {}
    };

    Node *frontNode;
    Node *rearNode;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr) {}

    ~Queue()
    {
        while (frontNode)
        {
            Node *temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }

    bool isEmpty() const
    {
        return frontNode == nullptr;
    }

    void enqueue(const T &item)
    {
        Node *newNode = new Node(item);
        if (isEmpty())
        {
            frontNode = rearNode = newNode;
        }
        else
        {
            rearNode->next = newNode;
            rearNode = newNode;
        }
    }

    void dequeue()
    {
        if (!isEmpty())
        {
            Node *temp = frontNode;
            frontNode = frontNode->next;
            delete temp;
        }
    }

    T front() const
    {
        if (!isEmpty())
        {
            return frontNode->data;
        }
        else
        {
            throw std::runtime_error("Queue is empty.");
        }
    }
};

int main()
{
    Queue<int> myQueue;

    myQueue.enqueue(10);
    myQueue.enqueue(20);
    myQueue.enqueue(30);

    std::cout << "Front element: " << myQueue.front() << std::endl;

    myQueue.dequeue();

    std::cout << "Front element after dequeue: " << myQueue.front() << std::endl;

    return 0;
}
