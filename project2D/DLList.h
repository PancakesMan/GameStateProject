#pragma once

template <typename T>
class DLList
{
	template <typename T>
	class Node
	{
	public:
		Node(T _value = T()) {
			value = _value;
			previous = nullptr;
			next = nullptr;
		}

		T value;
		Node<T> *previous, *next;
	};

public:

	// Iterator for the DLList class
	class iterator {
	public:
		iterator() { iter = nullptr; }
		iterator(const iterator& copy) { iter = copy.iter; }
		iterator& operator=(iterator _iter) { iter = _iter.iter; return *this; }
		bool operator==(iterator _iter) { return iter == _iter.iter; }
		bool operator!=(iterator _iter) { return iter != _iter.iter; }
		void operator++() { iter = iter->next; }
		void operator--() { iter = iter->previous; }
		Node<T>* operator*() { return iter; }
		Node<T>* operator->() { return iter; }

		friend class DLList<T>;
	private:
		iterator(Node<T>* _iter) { iter = _iter; }
		Node<T>* iter;
	};

	DLList() { m_first = nullptr, m_last = nullptr, m_count = 0; };
	~DLList() {
		// Call clear to delete all the nodes
		clear();
	};

	// Add a new value to the front of the List
	void pushFront(T value) {
		if (m_first == nullptr) {
			// If the first node is null then the list is empty
			// Create a new node and set first and last to that node
			m_first = new Node<T>(value);
			m_last = m_first;
		} else {
			// Else the list has data in it and we
			// need to update the list accordingly

			// Create a node pointer and set it's value
			Node<T>* tmp = new Node<T>(value);

			// Set first nodes previous to the new node
			// and set the new nodes next to the first node
			m_first->previous = tmp;
			tmp->next = m_first;

			// Set the first node to the new node
			m_first = tmp;
		}

		// Increase the counter for the
		// number of elements by 1
		m_count++;
	}

	// Add a new value to the end of the list
	void pushBack(T value) {
		if (m_last == nullptr) {
			// If the last node is null then the list is empty
			// Create a new node and set first and last to that node
			m_last = new Node<T>(value);
			m_first = m_last;
		} else {
			// Else the list had data in it and we
			// need to update the list accordingly

			// Create a node pointer and set it's value
			Node<T>* tmp = new Node<T>(value);

			// Set the last nodes next to the new node
			// and set the new nodes previous to the last node
			m_last->next = tmp;
			tmp->previous = m_last;

			// Set the last node to the new node
			m_last = tmp;
		}

		// Increase the counter for the
		// number of elements by 1
		m_count++;
	}

	// Insert a new element after the iterator
	void insert(iterator it, T value) {
		// Create a new node with the value
		Node<T>* tmp = new Node<T>(value);

		// Set the new nodes next to the iterators next
		tmp->next = (*it)->next;

		// Set the new node's next's previous to the new node
		tmp->next->previous = tmp;

		// Set the iterators next to the new node
		(*it)->next = tmp;

		// Set the new nodes previous to the iterator's node
		tmp->previous = (*it);

		// Increase the counter for the
		// number of elements by 1
		m_count++;
	}

	// Remove an element from the list by it's iterator
	void erase(iterator it) {

		// If iterator is the first element in the list
		if ((*it) == m_first) {
			popFront();
		}
		// If iterator is the last element in the list
		else if ((*it) == m_last) {
			popBack();
		}
		// If iterator is between first and last
		else {
			// Set next node's previous to currents node's previous
			(*it)->next->previous = (*it)->previous;

			// Set previous node's next to current node's next
			(*it)->previous->next = (*it)->next;
		}
	}

	// Remove a node from the list by value
	void remove(T value) {
		// Create a new temp node and set it to nullptr
		Node<T>* tmp = nullptr;

		// Loop through the linked list and set temp node
		// to the node that has the value passed in
		for (iterator it = begin(); it != end(); ++it)
			if ((*it)->value == value)
				tmp = (*it);
		
		// If tmp is not null then we found the value
		if (tmp != nullptr) {

			// Set next node's previous to temp's previous
			tmp->next->previous = tmp->previous;

			// Set previous node's next to temp's next
			tmp->previous->next = tmp->next;

			// Delete the old node
			delete tmp;
		}
	}

	// Remove the node at the end of the list
	void popBack() {
		// If the list is empty, do nothing
		if (m_last == nullptr) return;

		// Otherwise create a pointer to the last element
		Node<T>* tmp = m_last;

		// Set the last element's previous' next to nullptr
		tmp->previous->next = nullptr;

		// Set the last element to the current
		// last element's previous
		m_last = tmp->previous;

		// Delete the old last node
		delete tmp;

		// Decrease the counter for the
		// number of elements by 1
		m_count--;
	}

	// Remove the node at the front of the list
	void popFront() {
		// If the list is empty, do nothing
		if (m_first == nullptr) return;

		// Otherwise create a pointer to the first element
		Node<T>* tmp = m_first;

		// Set the first element's next's previous to nullptr
		tmp->next->previous = nullptr;

		// Set the first element to the current
		// first element's next
		m_first = tmp->next;

		// Delete the old first node
		delete tmp;

		// Decrease the counter for the
		// number of elements by 1
		m_count--;
	}

	// Returns true if the list is empty, else false
	bool empty() {
		return m_count == 0;
	}

	// Remove all elements from the list
	void clear() {

		// Create a temporary node
		Node<T>* tmp;

		// While the list is not empty
		while (m_last != nullptr) {
			// tmp = last element
			tmp = m_last;

			// Set the last to the current last element's previous
			m_last = tmp->previous;

			// Delete the old last element
			delete tmp;
		}

		// List is cleared, but first still points
		// to a deleted node. Set first to nullptr
		m_first = nullptr;

		// Set the list's element count to 0
		m_count = 0;
	}

	// Returns the number of elements in the list
	int count() {
		return m_count;
	}

	void remove(bool(predicate)(T)) {
		for (iterator it = begin(); it != end();) {
			if (predicate(it->value)) {
				iterator tmp = it;
				++tmp;
				erase(it);

				it = tmp;
			}
			else {
				++it;
			}
		}
	}

	iterator begin() { return iterator(m_first); }
	iterator first() { return iterator(m_first); }
	iterator last() { return iterator(m_last); }
	iterator end() { return iterator(nullptr); }

private:
	Node<T> *m_first, *m_last;
	int m_count;
};