#include <iostream>

struct Node
{
    int data;
    Node* next;
};

void Insert(int data, int n)
{
    Node* temp1 = new Node();
    temp1 -> data = data;
    temp1 -> next = NULL;
    if (n==1)
    {
      temp1 ->next = head;
      head = temp1;
      return;
    }
    Node* temp2 = head;
    for (int i = 0; i < n-2; i++)
    {
        temp2 = temp2 ->next;
    }
    temp1 ->next = temp2 ->next;
    temp2 ->next = temp1;
}

void Delete(int n)
{
    Node* temp1 = head;
    if (n == 1)
    {
        head = temp1 -> next;
        delete(temp1);
        return;
    }
    
    for (int i = 0; i < n-2; i++)
    {
        temp1 = temp1 -> next;
    }
    Node* temp2 = temp1 -> next;
    temp1 -> next = temp2 -> next;
    delete(temp2);
}

void Reverse()
{
    Node *current, *prev, *next;
    current = head;
    prev = NULL;
    while(current != NULL)
    {
        next = current ->next;
        current -> next = prev;
        prev = current;
        current = next;

    }
    head = prev;
}

void Print(Node* p)
{
    if(p == NULL)
    {
        return;
    }
    std::cout << p->data << " ";
    Print(p->next);

}

// This function is not defined
void InsertEnd()
{
    
}

// This function is not defined
void PrintReverse(Node* head)
{
    
}

// Initializing head to NULL
Node* head = NULL;

int main()
{
    Insert(1,1);
    Insert(2,2);
    Insert(3,3);
    Print(head);
    return 0;
}
