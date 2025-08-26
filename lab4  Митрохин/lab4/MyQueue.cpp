#include <iostream>
#include <fstream>
#include <concepts>
#include "MyQueue.h"

using namespace std;

TQueue::TQueue() {
	Size = 0;
	head = nullptr;
}

TQueue::~TQueue() {
	ClearQueue();
}

void TQueue::ClearQueue() {
	while (!isEmpty()) {
		front();
	}
}

void TQueue::push(Interface* data) {
	if (head == nullptr) {
		head = new Node(data);
	}
	else {
		Node* current = this->head;
		while (current->pNext != nullptr) {
			current = current->pNext;
		}
		current->pNext = new Node(data);
	}
	Size++;
}

void TQueue::front() {
	if (isEmpty()) {
		cout << "Error";
		return;
	}
	Node* temp = head;
	head = head->pNext;
	delete temp;
	Size--;
}

void TQueue::Output() const {
	Node* current = head;
	while (current != nullptr) {
		current->data->Output();
		current = current->pNext;
	}
	cout << endl;
}

void TQueue::Serialize(ostream& os) const {
	os << Size << '\n';

	Node* current = head;
	while (current != nullptr) {
		os << typeid(*(current->data)).name() << ' ';
		current->data->Serialize(os);
		os << '\n';
		current = current->pNext;
	}
}

void TQueue::Deserialize(istream& is) {
	ClearQueue();

	size_t stackSize;
	is >> stackSize;

	for (size_t i = 0; i < stackSize; ++i) {
		string objectType;
		is >> objectType;
		is >> objectType;

		Interface* item = nullptr;
		if (objectType == "Phone") {
			item = new Phone();
		}
		else if (objectType == "OS") {
			item = new OS();
		}
		else if (objectType == "design") {
			item = new design();
		}
		else if (objectType == "matrix") {
			item = new matrix();
		}
		else {
			cerr << "Unknown object type during deserialization: " << objectType << endl;
			continue;
		}

		item->Deserialize(is);
		push(item);
	}
}