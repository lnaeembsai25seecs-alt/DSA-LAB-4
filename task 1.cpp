#include <iostream>
#include <string>
using namespace std;

// Node structure for a song
struct Node {
	int songID;
	string songName;
	string duration;

	Node* prev;
	Node* next;
};

// Playlist class
class Playlist {
private:
	Node* head;
	Node* tail;
	Node* current;

public:
	// Constructor
	Playlist() {
		head = nullptr;
		tail = nullptr;
		current = nullptr;
	}

	// 1. Add Song
	void addSong(int id, string name, string duration) {
		Node* newNode = new Node;

		newNode->songID = id;
		newNode->songName = name;
		newNode->duration = duration;
		newNode->prev = nullptr;
		newNode->next = nullptr;

		// If playlist is empty
		if (head == nullptr) {
			head = tail = current = newNode;
		}
		else {
			// Insert at the end
			newNode->prev = tail;
			tail->next = newNode;
			tail = newNode;
		}

		cout << "Song added successfully!\n";
	}

	// 2. Delete Song
	void deleteSong(int id) {
		Node* temp = head;

		while (temp != nullptr && temp->songID != id) {
			temp = temp->next;
		}

		if (temp == nullptr) {
			cout << "Song with ID " << id << " not found.\n";
			return;
		}

		// If deleting head
		if (temp == head) {
			head = temp->next;

			if (head != nullptr)
				head->prev = nullptr;
		}
		else {
			temp->prev->next = temp->next;
		}

		// If deleting tail
		if (temp == tail) {
			tail = temp->prev;

			if (tail != nullptr)
				tail->next = nullptr;
		}
		else {
			temp->next->prev = temp->prev;
		}

		// Move current if the deleted node was current
		if (current == temp) {
			if (temp->next != nullptr)
				current = temp->next;
			else
				current = temp->prev;
		}

		delete temp;

		// If playlist becomes empty
		if (head == nullptr)
			current = nullptr;

		cout << "Song deleted successfully!\n";
	}

	// 3. Display Playlist Forward
	void displayForward() {
		if (head == nullptr) {
			cout << "Playlist is empty.\n";
			return;
		}

		Node* temp = head;

		cout << "\n--- Playlist Forward ---\n";

		while (temp != nullptr) {
			cout << "ID: " << temp->songID
				<< " | Song: " << temp->songName
				<< " | Duration: " << temp->duration;

			if (temp == current)
				cout << "  <-- Currently Playing";

			cout << endl;

			temp = temp->next;
		}
	}

	// 4. Display Playlist Backward
	void displayBackward() {
		if (tail == nullptr) {
			cout << "Playlist is empty.\n";
			return;
		}

		Node* temp = tail;

		cout << "\n--- Playlist Backward ---\n";

		while (temp != nullptr) {
			cout << "ID: " << temp->songID
				<< " | Song: " << temp->songName
				<< " | Duration: " << temp->duration;

			if (temp == current)
				cout << "  <-- Currently Playing";

			cout << endl;

			temp = temp->prev;
		}
	}

	// 5. Search Song
	void searchSong(int id) {
		Node* temp = head;

		while (temp != nullptr) {
			if (temp->songID == id) {
				cout << "\nSong Found!\n";
				cout << "Song ID: " << temp->songID << endl;
				cout << "Song Name: " << temp->songName << endl;
				cout << "Duration: " << temp->duration << endl;
				return;
			}

			temp = temp->next;
		}

		cout << "Song with ID " << id << " not found.\n";
	}

	// 6a. Play Next Song
	void playNext() {
		if (current == nullptr) {
			cout << "Playlist is empty.\n";
			return;
		}

		if (current->next != nullptr) {
			current = current->next;

			cout << "\nNow Playing: "
				<< current->songName
				<< " (" << current->duration << ")\n";
		}
		else {
			cout << "Already at the last song.\n";
		}
	}

	// 6b. Play Previous Song
	void playPrevious() {
		if (current == nullptr) {
			cout << "Playlist is empty.\n";
			return;
		}

		if (current->prev != nullptr) {
			current = current->prev;

			cout << "\nNow Playing: "
				<< current->songName
				<< " (" << current->duration << ")\n";
		}
		else {
			cout << "Already at the first song.\n";
		}
	}

	// 7. Reverse Playlist
	void reversePlaylist() {
		if (head == nullptr) {
			cout << "Playlist is empty.\n";
			return;
		}

		Node* temp = nullptr;
		Node* currentNode = head;

		// Swap next and prev pointers of every node
		while (currentNode != nullptr) {
			temp = currentNode->prev;
			currentNode->prev = currentNode->next;
			currentNode->next = temp;

			currentNode = currentNode->prev;
		}

		// Swap head and tail
		temp = head;
		head = tail;
		tail = temp;

		cout << "Playlist reversed successfully!\n";
	}
};

// Main function
int main() {
	Playlist playlist;

	int choice;
	int id;
	string name;
	string duration;

	do {
		cout << "\n====================================\n";
		cout << "       PLAYLIST MANAGEMENT SYSTEM\n";
		cout << "====================================\n";
		cout << "1. Add Song\n";
		cout << "2. Delete Song\n";
		cout << "3. Display Playlist Forward\n";
		cout << "4. Display Playlist Backward\n";
		cout << "5. Search Song\n";
		cout << "6. Play Next Song\n";
		cout << "7. Play Previous Song\n";
		cout << "8. Reverse Playlist\n";
		cout << "9. Exit\n";
		cout << "====================================\n";

		cout << "Enter your choice: ";
		cin >> choice;

		switch (choice) {

		case 1:
			cout << "Enter Song ID: ";
			cin >> id;

			cin.ignore();

			cout << "Enter Song Name: ";
			getline(cin, name);

			cout << "Enter Duration (mm:ss): ";
			cin >> duration;

			playlist.addSong(id, name, duration);
			break;

		case 2:
			cout << "Enter Song ID to delete: ";
			cin >> id;

			playlist.deleteSong(id);
			break;

		case 3:
			playlist.displayForward();
			break;

		case 4:
			playlist.displayBackward();
			break;

		case 5:
			cout << "Enter Song ID to search: ";
			cin >> id;

			playlist.searchSong(id);
			break;

		case 6:
			playlist.playNext();
			break;

		case 7:
			playlist.playPrevious();
			break;

		case 8:
			playlist.reversePlaylist();
			break;

		case 9:
			cout << "Exiting program...\n";
			break;

		default:
			cout << "Invalid choice! Please try again.\n";
		}

	} while (choice != 9);

	return 0;
}