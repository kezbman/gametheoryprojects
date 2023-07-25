#include <iostream>
using namespace std;
struct Node
{
    int data;
    Node *next;
};
Node *removeFirstNode(struct Node *head)
{
    if (head == NULL)
        return NULL;

    // Move the head pointer to the next node
    Node *temp = head;
    head = head->next;

    delete temp;

    return head;
}
struct Node *newNode(int data)
{
    Node *node = new Node;
    node->data = data;
    node->next = NULL;
    return node;
}
void insertNewNode(Node **root, int data)
{
    Node *node = newNode(data);
    Node *ptr;
    if (*root == NULL)
    {
        *root = node;
    }
    else
    {
        ptr = *root;
        while (ptr->next != NULL)
        {
            ptr = ptr->next;
        }
        ptr->next = node;
    }
}
Node *createLinkedList(int arr[], int n)
{
    Node *root = NULL;
    for (int i = 0; i < n; i++)
    {
        insertNewNode(&root, arr[i]);
    }
    return root;
}
int main()
{
    int agentsNum;
    cout << "Enter the number of agents: ";
    cin >> agentsNum;
    int *matching = new int[agentsNum];
    for (int i = 0; i < agentsNum; i++)
        matching[i] = -1;
    Node **roots = new Node *[agentsNum];
    int **prefs = new int *[agentsNum];
    for (int i = 0; i < agentsNum; i++)
        prefs[i] = new int[agentsNum];
    cout << "Enter the preferences for agents: " << endl;
    for (int i = 0; i < agentsNum; i++)
    {
        cout << "\n\tagent " << i + 1 << endl;
        for (int j = 0; j < agentsNum; j++)
        {
            cout << j + 1 << ": ";
            cin >> prefs[i][j];
            while (prefs[i][j] < 1 || prefs[i][j] > agentsNum)
            {
                cout << "Invalid number. Please try again:  ";
                cin >> prefs[i][j];
            }
        }
        cout << "-----------------";
    }
    for (int i = 0; i < agentsNum; i++)
    {
        roots[i] = createLinkedList(prefs[i], agentsNum);
    }
    delete[] prefs;
    int current = 0;
    bool *visited = new bool[agentsNum];
    for (int i = 0; i < agentsNum; i++)
        visited[i] = false;
    while (1)
    {
        if (visited[current] == true)
        { // found a cycle

            int temp = current;
            while (roots[current]->data - 1 != temp)
            {
                matching[current] = roots[current]->data - 1;
                current = roots[current]->data - 1;
            }
            matching[current] = roots[current]->data - 1; // for the last one
            current = temp;
            for (int i = 0; i < agentsNum; i++)
            {
                if (matching[i] == -1 && roots[i]->data - 1 == current)
                {
                    // deleting the first preference or the first element of the linked list
                    roots[i] = roots[i]->next;
                    break;
                }
            }
            for (int i = 0; i < agentsNum; i++)
            {
                if (matching[i] == -1)
                {
                    current = i;
                    break;
                }
            }
            for (int i = 0; i < agentsNum; i++)
                visited[i] = false;
        }
        if (matching[roots[current]->data - 1] != -1)
        { // this is the last one
            matching[current] = current;
            break;
        }
        visited[current] = true;
        current = roots[current]->data - 1;
    }
    for (int i = 0; i < agentsNum; i++)
    {
        cout << "Agent " << i + 1 << " is in room " << matching[i] + 1 << endl;
    }
    return 0;
}
