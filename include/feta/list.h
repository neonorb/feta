/*
 * list.h
 *
 *  Created on: May 8, 2016
 *      Author: chris
 */

#ifndef INCLUDE_LIST_H_
#define INCLUDE_LIST_H_

namespace feta {

template<typename T> class Element;
template<typename T> class Iterator;
template<typename T> class List;

}

#include <feta.h>

namespace feta {

void _abort(String message);
void _outOfBounds(uinteger index, uinteger size);

template<typename T> class Element {
public:
	T value;
	Element<T>* next;
	Element<T>* previous;
};

template<typename T> class Iterator {
private:
	Element<T>* current;
	List<T>* list;
public:
	Iterator();
	Iterator(Element<T>* current, List<T>* list);

	bool hasNext();
	T peekNext();
	T next();
};

template<typename T> class List {
private:
	Element<T>* first;
	Element<T>* last;
	uinteger length;

public:
	List();
	~List();

	List<T>& operator=(List<T>& other);

	bool dirty;

	uinteger size();
	bool isEmpty();
	uinteger indexOf(T item);

	bool isFirst(uinteger index);
	bool isFirst(Element<T>* element);
	bool isFirst(T item);

	bool isLast(uinteger index);
	bool isLast(Element<T>* element);
	bool isLast(T item);

	T& get(uinteger index);
	Element<T>* getElement(uinteger index);
	T getLast();

	void addElement(Element<T>* element);
	void addElement(Element<T>* elemnt, uinteger index);
	void add(T item);
	void add(uinteger index, T item);
	void addAll(List<T>& items);

	void removeElement(Element<T>* element);
	T remove(uinteger index);
	void remove(T item);
	void clear();

	Iterator<T> iterator();
};

}

// -- implementation --

namespace feta {

template<typename T>
List<T>::List() {
	length = 0;
	first = NULL;
	last = NULL;
	dirty = false;
}

template<typename T>
List<T>::~List() {
	clear();
}
extern void debug(String);
template<typename T>
List<T>& List<T>::operator=(List<T>& other) {
	clear();
	addAll(other);

	return *this;
}

// ---- simple stuffs ----

template<typename T>
uinteger List<T>::size() {
	return length;
}

template<typename T>
bool List<T>::isEmpty() {
	return size() == 0;
}

template<typename T>
uinteger List<T>::indexOf(T item) {
	for (uinteger i = 0; i < size(); i++) {
		if (get(i) == item) {
			return i;
		}
	}

	return -1;
}

// ---- isFirst ----

template<typename T>
bool List<T>::isFirst(uinteger index) {
	return index == 0;
}

template<typename T>
bool List<T>::isFirst(Element<T>* element) {
	return first == element;
}

template<typename T>
bool List<T>::isFirst(T item) {
	return first->value == item;
}

// ---- isLast -----

template<typename T>
bool List<T>::isLast(uinteger index) {
	return index == size() - 1;
}

template<typename T>
bool List<T>::isLast(Element<T>* element) {
	return last == element;
}

template<typename T>
bool List<T>::isLast(T item) {
	return last->value == item;
}

// ---- get ----

template<typename T>
Element<T>* List<T>::getElement(uinteger index) {
	// TODO optimize for searching from last element too
	if (index >= size()) {
	}

	Element<T>* element = first;

	for (uinteger i = 0; i < index; i++) {
		element = element->next;
	}

	return element;
}

template<typename T>
T& List<T>::get(uinteger index) {
	return getElement(index)->value;
}

template<typename T>
T List<T>::getLast() {
	return last->value;
}

// ---- add ----

template<typename T>
void List<T>::addElement(Element<T>* element) {
	addElement(element, length);
}

template<typename T>
void List<T>::add(T item) {
	Element<T>* element = new Element<T>();
	element->value = item;

	addElement(element);
}

template<typename T>
void List<T>::addElement(Element<T>* element, uinteger index) {
	// TODO make addElementAfter and addElementBefore methods, call those from here
	// update references
	if (length == 0) { // initial
		first = element;
		last = element;
		element->next = NULL;
		element->previous = NULL;
	} else {
		if (index == 0) { // at the beginning
			Element<T>* newSecond = first;
			newSecond->previous = element;

			first = element;
			element->previous = NULL;
			element->next = newSecond;
		} else if (index == length) { // at the end
			Element<T>* newSecondToLast = last;
			newSecondToLast->next = element;

			last = element;
			element->previous = newSecondToLast;
			element->next = NULL;
		} else { // in the middle
			Element<T>* elementInTheWay = getElement(index);
			Element<T>* stillBefore = elementInTheWay->previous;

			stillBefore->next = element;

			element->previous = stillBefore;
			element->next = elementInTheWay;

			elementInTheWay->previous = element;
		}
	}

	length++;
	dirty = true;
}

template<typename T>
void List<T>::add(uinteger index, T item) {
	Element<T>* element = new Element<T>();
	element->value = item;

	addElement(element, index);
}

template<typename T>
void List<T>::addAll(List<T>& items) {
	Iterator<T> iterator = items.iterator();
	while (iterator.hasNext()) {
		add(iterator.next());
	}
}

// ---- remove ----

template<typename T>
void List<T>::removeElement(Element<T>* element) {
	if (length > 1) {
		if (first == element) { // at the beginning and there is another element
			Element<T>* newFirst = element->next;
			first = newFirst;
			newFirst->previous = NULL;
		} else if (last == element) { // at the end
			Element<T>* newLast = element->previous;
			newLast->next = NULL;
			last = newLast;
		} else { // in the middle
			Element<T>* samePrevious = element->previous;
			Element<T>* newReplacement = element->next;

			samePrevious->next = newReplacement;
			newReplacement->previous = samePrevious;
		}
	} else {
		// remove only element
		first = NULL;
		last = NULL;
	}
	length--;
	dirty = true;
}

template<typename T>
T List<T>::remove(uinteger index) {
	if (index >= size()) {
		_outOfBounds(index, size());
	}

	Element<T>* element = getElement(index);
	T item = element->value;

	removeElement(element);
	delete element;

	return item;
}

template<typename T>
void List<T>::remove(T item) {
	Iterator<T> itemIterator = iterator();
	uinteger i = 0;
	while (itemIterator.hasNext()) {
		T it = itemIterator.next();
		if (it == item) {
			break;
		}
		i++;
	}
	remove(i);
}

template<typename T>
void List<T>::clear() {
	while (size() > 0) {
		remove((uinteger) 0);
	}
}

// ---- iterator ----

template<typename T>
Iterator<T> List<T>::iterator() {
	dirty = false;
	return Iterator<T>(first, this);
}

template<typename T>
Iterator<T>::Iterator() {
	this->current = NULL;
	this->list = NULL;
}

template<typename T>
Iterator<T>::Iterator(Element<T>* current, List<T>* list) {
	this->current = current;
	this->list = list;
}

template<typename T>
bool Iterator<T>::hasNext() {
	if (list->dirty) {
		_abort("concurrent modification");
	}
	return current != NULL;
}

template<typename T>
T Iterator<T>::peekNext() {
	if (list->dirty) {
		_abort("concurrent modification");
	}
	if (!hasNext()) {
		_abort("there is no next element");
	}

	return current->value;
}

template<typename T>
T Iterator<T>::next() {
	T value = peekNext();
	current = current->next;

	return value;
}

}

#endif /* INCLUDE_LIST_H_ */
