
#include <iostream>
using namespace std;


struct Node {
	int personID;
	Node* next;
};


class CircularLinkedList {
private:
	Node* head;

public:

	CircularLinkedList() {
		head = nullptr;
	}

	// 1. Create Circle
	void createCircle(int N) {
		if (N <= 0) {
			cout << "Number of people must be greater than 0.\n";
			return;
		}

		Node* last = nullptr;

		for (int i = 1; i <= N; i++) {
			Node* newNode = new Node;
			newNode->personID = i;

			if (head == nullptr) {
				head = newNode;
				last = newNode;
				newNode->next = head;
			}
			else {
				newNode->next = head;
				last->next = newNode;
				last = newNode;
			}
		}

		cout << "Circular linked list created successfully.\n";
	}

	// 2. Elimination Process
	void eliminate(int k) {
		if (head == nullptr) {
			cout << "Circle is empty.\n";
			return;
		}

		if (k <= 0) {
			cout << "Step count must be greater than 0.\n";
			return;
		}

		Node* current = head;
		Node* previous = nullptr;

		cout << "\nEliminated Order: ";

		while (current->next != current) {

		
			previous = current;

			for (int count = 1; count < k; count++) {
				previous = current;
				current = current->next;
			}

			cout << current->personID << " ";

			previous->next = current->next;

		
			if (current == head) {
				head = current->next;
			}

			Node* temp = current;
			current = current->next;

			delete temp;
		}

		
		cout << "\n\nSurvivor: " << current->personID << endl;

		delete current;
		head = nullptr;
	}
};

int main() {
	CircularLinkedList circle;

	int N, k;

	// Input
	cout << "Enter number of people (N): ";
	cin >> N;

	cout << "Enter step count (k): ";
	cin >> k;

	// Create the circular linked list
	circle.createCircle(N);

	// Perform Josephus elimination
	circle.eliminate(k);

	return 0;
}

