#include<iostream>
#include<stdlib.h>
#include<queue>
#include<omp.h>

using namespace std;

class node
{
public:
    node *left, *right;
    int data;
};

// Function to insert node in binary tree
node* insert(node *root, int data)
{
    if(!root)
    {
        root = new node;
        root->left = NULL;
        root->right = NULL;
        root->data = data;
        return root;
    }

    queue<node *> q;
    q.push(root);

    while(!q.empty())
    {
        node *temp = q.front();
        q.pop();

        if(temp->left == NULL)
        {
            temp->left = new node;
            temp->left->left = NULL;
            temp->left->right = NULL;
            temp->left->data = data;
            return root;
        }
        else
        {
            q.push(temp->left);
        }

        if(temp->right == NULL)
        {
            temp->right = new node;
            temp->right->left = NULL;
            temp->right->right = NULL;
            temp->right->data = data;
            return root;
        }
        else
        {
            q.push(temp->right);
        }
    }

    return root;
}

// BFS Traversal using OpenMP
void bfs(node *head)
{
    if(head == NULL)
        return;

    queue<node*> q;
    q.push(head);

    while(!q.empty())
    {
        int qSize = q.size();

        #pragma omp parallel for
        for(int i = 0; i < qSize; i++)
        {
            node* currNode;

            #pragma omp critical
            {
                currNode = q.front();
                q.pop();

                cout << currNode->data << " ";
            }

            #pragma omp critical
            {
                if(currNode->left)
                    q.push(currNode->left);

                if(currNode->right)
                    q.push(currNode->right);
            }
        }
    }
}

int main()
{
    node *root = NULL;
    int data;
    char ans;

    do
    {
        cout << "\nEnter data: ";
        cin >> data;

        root = insert(root, data);

        cout << "Insert more nodes? (y/n): ";
        cin >> ans;

    } while(ans == 'y' || ans == 'Y');

    cout << "\nBFS Traversal: ";
    bfs(root);

    return 0;
}


//bfs_openmp.cpp
//g++ bfs_openmp.cpp -fopenmp -o bfs
// ./bfs

//windows
//g++ bfs_openmp.cpp -fopenmp -o bfs.exe
//bfs.exe
// ./bfs.exe


//Enter data: 1
//Insert more nodes? (y/n): y

//Enter data: 2
//Insert more nodes? (y/n): y

//Enter data: 3
//Insert more nodes? (y/n): y

//Enter data: 4
//Insert more nodes? (y/n): n

//BFS Traversal: 1 2 3 4
