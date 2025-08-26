#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "Phone.h"

class TQueue {
public:
	TQueue();
	~TQueue();
	void push(Interface* data);
	void front();
	int GetSize() { return Size; }
	// Interface* GetFront();
	void Output() const;
	bool isEmpty() { return Size == 0; }
	void ClearQueue();

	void Serialize(ostream& os) const;
	void Deserialize(istream& is);

private:
	struct Node {
		Node* pNext;
		Interface* data;

		Node(Interface* data = nullptr, Node* pnext = nullptr) {
			this->data = data;
			this->pNext = pnext;
		}
	};
	int Size;
	Node* head;
};