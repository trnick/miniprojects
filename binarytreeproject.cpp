#include<iostream>
#include<fstream>
using namespace std;

class Node //class Node
{
public:
	Node* left;
	Node* right;
	string name;
	int weight;


	Node() // default constructor
	{
		name = "";
		weight = 0;
		left = NULL;
		right = NULL;
	}

	Node(string n, int val) //parameterized constructor
	{
		name = n;
		weight = val;
		left = NULL;
		right = NULL;
	}
};

class tree //class tree
{
private:
	void preorder(Node* leaf) //prints tree in preorder traversal
	{
		if (leaf != NULL)
		{
			cout << leaf->name << " ";
			preorder(leaf->left);
			preorder(leaf->right);
		}
	}

	void inorder(Node* leaf) //prints tree in inorder traversal
	{
		if (leaf != NULL)
		{
			preorder(leaf->left);
			cout << leaf->name << " ";
			preorder(leaf->right);
		}
	}

	void postorder(Node* leaf) //prints tree in postorder traversal
	{
		if (leaf != NULL)
		{
			postorder(leaf->left);
			postorder(leaf->right);
			cout << leaf->name << " ";
		}
	}

	int findHeight(Node* leaf) //increments through tree and finds the largest height from either the right or left side of the tree
	{
		if (leaf == NULL)
		{
			return 0;
		}

		int lHeight = findHeight(leaf->left);
		int rHeight = findHeight(leaf->right);

		if (lHeight > rHeight)
			return lHeight + 1;
		else
			return rHeight + 1;
	}

	//stackoverflow
	int findLeaves(Node* leaf) //returns the total number of leaves in the tree
	{
		if (leaf == NULL) //checks if leaf is empty
			return 0;
		if (leaf->left == NULL && leaf->right == NULL) //checks if leaf is connected to any other node/leaf
			return 1;
		else
			return findLeaves(leaf->left) + findLeaves(leaf->right); //returns the cumulative value
	}

	int minW(Node* leaf) //traverses through the tree and determines the smalles value of 'weight'
	{
		if (leaf == NULL) { //checks if leaf node is empty
			return 0;
		}
		Node* searchW = leaf;
		int currentW = searchW->weight;
		//recursive calls
		int currR = minW(searchW->right);
		int currL = minW(searchW->left);

		if (searchW != NULL) { //interates through entire tree and checks if the values are greater or less than each other
			if (currR > currL) {
				currentW = currL;
			}
			else if (currL > currR) {
				currentW = currR;
			}
		}
		return currentW;
	}

	void searchN(Node* leaf, string name) // searches for the name through the tree using recursion, until match is confirmed
	{
		if (leaf->name == name) //if the current leaf name is equal to the search name
		{
			cout << leaf->name << " has weight: " << leaf->weight << endl;
		}
		else if (leaf->name < name && leaf->right == NULL) //if the current leaf name is less than search name, AND the right node of the current leaf is NULL
		{
			cout << endl << "No match " << endl;
		}
		else if (leaf->name > name && leaf->left == NULL) //if the current leaf name is greater than search name, AND the left node of the current leaf is NULL
		{
			cout << "No match " << endl;
		}
		else if (leaf->name < name) //if the search name is less than current leaf name
		{
			searchN(leaf->right, name);
		}
		else if (leaf->name > name) //if the search name is greater than current leaf name
		{
			searchN(leaf->left, name);
		}
	}

	string firstN(Node* leaf) //goes through the left side of the tree until it finds the first name
	{
		Node* current = leaf;

		while (current->left != NULL)
		{
			current = current->left;
		}
		return current->name;
	}

public:
	Node* root;

	tree() //default constructor
	{
		root = NULL;
	}

	void add(Node* newT) //adds a new node with name and weight
	{
		if (root == NULL) //if the tree is empty
		{
			root = newT;
		}
		else
		{
			Node* leaf = root;

			while (leaf != NULL) //increments through tree
			{
				if (newT->name == leaf->name) // if name is equal to already existing leaf name
				{
					cout << "Error, use another name " << endl;
					return;
				}
				else if ((newT->name < leaf->name) && (leaf->left == NULL)) //checks if left is empty or if existing leaf is greater than user inputted name
				{
					leaf->left = newT;
					break;
				}
				else if (newT->name < leaf->name) //moves towards the left of the tree
				{
					leaf = leaf->left;
				}
				else if ((newT->name > leaf->name) && (leaf->right == NULL)) //checks if right is empty or if existing leaf is less than user inputted name
				{
					leaf->right = newT;
					break;
				}
				else //moves towards the right of the tree
				{
					leaf = leaf->right;
				}
			}
		}
	}

	//allows private functions to be called publicly

	  //calls private preorder function
	void preorder() { preorder(root); }

	//calls private inorder function
	void inorder() { inorder(root); }

	//calls private postorder function
	void postorder() { postorder(root); }

	//prints private height function
	void findHeight() { cout << findHeight(root); }

	//prints leaves of tree from private function
	void findL() { cout << findLeaves(root); }

	//calls private searchN function
	void searchN(string name) { searchN(root, name); }

	//calls private minW functions
	void lowestweight() { cout << minW(root); }

	//calls private firstN function
	void firstname() { cout << firstN(root); }
};

int main()
{
	tree a; //declare tree variable 'a'
	int num=0;
	int val = 0;
	string name;
	string searchVar;

	cout << "1 to add vname and value" << endl;
	cout << "2 to print (preorder, inorder, postorder)" << endl;
	cout << "3 to print height, number of leaves, first name, and lowest weight" << endl;
	cout << "4 to search for a specific name" << endl;
	cout << "5 to terminate" << endl;

	do
	{
		cout << "Enter a number: ";
		cin >> num;

		Node* newT = new Node();

		//stackoverflow
		switch (num) //switch statement
		{
		case 1:
			cout << "Enter a name:  ";
			cin >> name;
			cout << "Enter a value: ";
			cin >> val;

			newT->name = name;
			newT->weight = val;

			a.add(newT);
			cout << "\n\n";
			break;
		case 2:
			cout << "Preorder: \n";
			a.preorder();
			cout << endl << "Inorder: \n";
			a.inorder();
			cout << endl << "Postorder: \n";
			a.postorder();
			cout << "\n\n";
			break;
		case 3:
			cout << "Height: ";
			a.findHeight();
			cout << "\n";
			cout << "Number of Leaves: ";
			a.findL();
			cout << "\n";
			cout << "First name: ";
			a.firstname();
			cout << "\n";
			cout << "Lowest Weight: ";
			a.lowestweight();
			cout << "\n\n";
			break;
		case 4:
			cout << "Enter name you want to search: ";
			cin >> searchVar;
			a.searchN(searchVar);
			cout << "\n\n";
			break;
		case 5:
			cout << "Terminated." << endl;
			break;
		default:
			cout << "Something went wrong. Enter another number :" << endl;
			break;
		}
	} while (num != 5);

	return 0;
}

/*
OUTPUT:
1 to add vname and value
2 to print (preorder, inorder, postorder)
3 to print height, number of leaves, first name, and lowest weight
4 to search for a specific name
5 to terminate
Enter a number: 1
Enter a name:  Nick
Enter a value: 150


Enter a number: 1
Enter a name:  Tran
Enter a value: 200


Enter a number: 1
Enter a name:  Long
Enter a value: 250


Enter a number: 2
Preorder:
Nick Long Tran
Inorder:
Long Nick Tran
Postorder:
Long Tran Nick

Enter a number: 3
Height: 2
Number of Leaves: 2
First name: Long
Lowest Weight: 150

Enter a number: 4
Enter name you want to search: Nick
Nick has weight: 150


Enter a number: 5
Terminated.
*/
