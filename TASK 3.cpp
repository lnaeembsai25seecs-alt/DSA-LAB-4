
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

// Node for each binary bit
struct Node {
	int bit;
	Node* next;
	Node* prev;

	Node(int b) {
		bit = b;
		next = nullptr;
		prev = nullptr;
	}
};

// Doubly Linked List for binary numbers
class BinaryDLL {
private:
	Node* head;
	Node* tail;

public:
	// Constructor
	BinaryDLL() {
		head = nullptr;
		tail = nullptr;
	}

	// Destructor
	~BinaryDLL() {
		clear();
	}

	
	void clear() {
		Node* temp = head;

		while (temp != nullptr) {
			Node* nextNode = temp->next;
			delete temp;
			temp = nextNode;
		}

		head = nullptr;
		tail = nullptr;
	}

	// Copy constructor
	BinaryDLL(const BinaryDLL& other) {
		head = nullptr;
		tail = nullptr;

		Node* temp = other.head;

		while (temp != nullptr) {
			append(temp->bit);
			temp = temp->next;
		}
	}

	
	BinaryDLL& operator=(const BinaryDLL& other) {
		if (this != &other) {
			clear();

			Node* temp = other.head;

			while (temp != nullptr) {
				append(temp->bit);
				temp = temp->next;
			}
		}

		return *this;
	}

	
	void append(int bit) {
		Node* newNode = new Node(bit);

		if (head == nullptr) {
			head = tail = newNode;
		}
		else {
			tail->next = newNode;
			newNode->prev = tail;
			tail = newNode;
		}
	}

	
	void prepend(int bit) {
		Node* newNode = new Node(bit);

		if (head == nullptr) {
			head = tail = newNode;
		}
		else {
			newNode->next = head;
			head->prev = newNode;
			head = newNode;
		}
	}

	
	bool isEmpty() const {
		return head == nullptr;
	}

	
	int size() const {
		int count = 0;
		Node* temp = head;

		while (temp != nullptr) {
			count++;
			temp = temp->next;
		}

		return count;
	}

	
	void removeLeadingZeros() {
		while (head != nullptr &&
			head->bit == 0 &&
			head != tail) {

			Node* temp = head;
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
	}

	
	bool storeBinary(string binary) {
		clear();

		if (binary.empty()) {
			return false;
		}

		
		for (char c : binary) {
			if (c != '0' && c != '1') {
				return false;
			}
		}

	
		int firstOne = binary.find('1');

		if (firstOne == string::npos) {
			binary = "0";
		}
		else {
			binary = binary.substr(firstOne);
		}

		
		for (char c : binary) {
			append(c - '0');
		}

		return true;
	}

	void display() const {
		Node* temp = head;

		while (temp != nullptr) {
			cout << temp->bit;
			temp = temp->next;
		}
	}


	void displayGrouped() const {
		int length = size();

	
		int padding = (8 - (length % 8)) % 8;

		for (int i = 0; i < padding; i++) {
			cout << "0";
		}

		Node* temp = head;
		int count = padding;

		while (temp != nullptr) {
			cout << temp->bit;
			count++;

			if (count % 8 == 0 && temp->next != nullptr) {
				cout << " ";
			}

			temp = temp->next;
		}
	}

	// 1's Complement
	BinaryDLL onesComplement() const {
		BinaryDLL result;

		Node* temp = head;

		while (temp != nullptr) {
			result.append(temp->bit == 0 ? 1 : 0);
			temp = temp->next;
		}

		return result;
	}

	// 2's Complement
	BinaryDLL twosComplement() const {
		
		BinaryDLL result = onesComplement();

		
		Node* temp = result.tail;
		int carry = 1;

		while (temp != nullptr && carry == 1) {

			if (temp->bit == 0) {
				temp->bit = 1;
				carry = 0;
			}
			else {
				temp->bit = 0;
				carry = 1;
			}

			temp = temp->prev;
		}

		
		if (carry == 1) {
			result.prepend(1);
		}

		return result;
	}


	static BinaryDLL add(const BinaryDLL& a,
		const BinaryDLL& b) {

		BinaryDLL result;

		Node* p = a.tail;
		Node* q = b.tail;

		int carry = 0;

		
		while (p != nullptr ||
			q != nullptr ||
			carry != 0) {

			int bitA = 0;
			int bitB = 0;

			if (p != nullptr) {
				bitA = p->bit;
				p = p->prev;
			}

			if (q != nullptr) {
				bitB = q->bit;
				q = q->prev;
			}

			int sum = bitA + bitB + carry;

			
			result.prepend(sum % 2);

			carry = sum / 2;
		}

		result.removeLeadingZeros();

		return result;
	}

	
	void shiftLeft(int positions) {
		for (int i = 0; i < positions; i++) {
			append(0);
		}
	}

	static BinaryDLL multiply(const BinaryDLL& a,
		const BinaryDLL& b) {

		BinaryDLL result;
		result.append(0);

		
		Node* multiplier = b.tail;

		int shift = 0;

		while (multiplier != nullptr) {

			if (multiplier->bit == 1) {

				BinaryDLL shifted = a;

				
				shifted.shiftLeft(shift);

				
				result = add(result, shifted);
			}

			multiplier = multiplier->prev;
			shift++;
		}

		result.removeLeadingZeros();

		return result;
	}

	// Convert binary to decimal
	unsigned long long toDecimal() const {

		unsigned long long decimal = 0;

		Node* temp = head;

		while (temp != nullptr) {
			decimal = decimal * 2 + temp->bit;
			temp = temp->next;
		}

		return decimal;
	}
};


// Main function
int main() {

	BinaryDLL binary1;
	BinaryDLL binary2;

	string input1;
	string input2;

	int choice;

	do {

		cout << "\n============================================\n";
		cout << "       BINARY ARITHMETIC USING DLL\n";
		cout << "============================================\n";
		cout << "1. Store Binary Number\n";
		cout << "2. 1's Complement\n";
		cout << "3. 2's Complement\n";
		cout << "4. Binary Addition\n";
		cout << "5. Binary Multiplication\n";
		cout << "6. Conversion to Decimal\n";
		cout << "7. Exit\n";
		cout << "============================================\n";

		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {

			// 1. Store Binary Number
		case 1:

			cout << "\nEnter first binary number: ";
			cin >> input1;

			if (binary1.storeBinary(input1)) {
				cout << "Binary number stored successfully.\n";
				cout << "Stored in 8-bit groups: ";
				binary1.displayGrouped();
				cout << endl;
			}
			else {
				cout << "Invalid binary number!\n";
			}

			break;


			// 2. 1's Complement
		case 2:

			if (binary1.isEmpty()) {
				cout << "Please store a binary number first.\n";
				break;
			}

			{
				BinaryDLL result = binary1.onesComplement();

				cout << "\nOriginal: ";
				binary1.display();

				cout << "\n1's Complement: ";
				result.display();

				cout << endl;
			}

			break;


			// 3. 2's Complement
		case 3:

			if (binary1.isEmpty()) {
				cout << "Please store a binary number first.\n";
				break;
			}

			{
				BinaryDLL result = binary1.twosComplement();

				cout << "\nOriginal: ";
				binary1.display();

				cout << "\n2's Complement: ";
				result.display();

				cout << endl;
			}

			break;


			// 4. Binary Addition
		case 4:

			cout << "\nEnter first binary number: ";
			cin >> input1;

			cout << "Enter second binary number: ";
			cin >> input2;

			if (!binary1.storeBinary(input1) ||
				!binary2.storeBinary(input2)) {

				cout << "Invalid binary number!\n";
				break;
			}

			{
				BinaryDLL result =
					BinaryDLL::add(binary1, binary2);

				cout << "\nFirst Number: ";
				binary1.display();

				cout << "\nSecond Number: ";
				binary2.display();

				cout << "\nSum: ";
				result.display();

				cout << endl;
			}

			break;


			// 5. Binary Multiplication
		case 5:

			cout << "\nEnter first binary number: ";
			cin >> input1;

			cout << "Enter second binary number: ";
			cin >> input2;

			if (!binary1.storeBinary(input1) ||
				!binary2.storeBinary(input2)) {

				cout << "Invalid binary number!\n";
				break;
			}

			{
				BinaryDLL result =
					BinaryDLL::multiply(binary1, binary2);

				cout << "\nFirst Number: ";
				binary1.display();

				cout << "\nSecond Number: ";
				binary2.display();

				cout << "\nProduct: ";
				result.display();

				cout << endl;
			}

			break;


			// 6. Binary to Decimal
		case 6:

			if (binary1.isEmpty()) {
				cout << "Please store a binary number first.\n";
				break;
			}

			cout << "\nBinary: ";
			binary1.display();

			cout << "\nDecimal: "
				<< binary1.toDecimal()
				<< endl;

			break;


			// 7. Exit
		case 7:

			cout << "Exiting program...\n";
			break;


		default:

			cout << "Invalid choice! Please try again.\n";
		}

	} while (choice != 7);

	return 0;
}

