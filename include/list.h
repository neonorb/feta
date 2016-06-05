/*
 * list.h
 *
 *  Created on: May 8, 2016
 *      Author: chris
 */

#ifndef INCLUDE_LIST_H_
#define INCLUDE_LIST_H_

// -- declaration --

#include <int.h>
#include <bool.h>
#include <string.h>
#include <memory.h>

template<typename T> class Element {
public:
	T value;
	Element<T>* next;
	Element<T>* previous;
};

template<typename T> class Iterator {
private:
	Element<T>* current;
public:
	Iterator(Element<T>* current);

	T next();
};

template<typename T> class List{
private:
	Element<T>* first;
	Element<T>* last;
	uint64 length = 0;

public:
	List<T>* destroy();

	uint64 size();bool isEmpty();
	uint64 indexOf(T item);

	bool isFirst(uint64 index);bool isFirst(Element<T>* element);bool isFirst(
			T item);

	bool isLast(uint64 index);bool isLast(Element<T>* element);bool isLast(
			T item);

	T get(uint64 index);
	Element<T>* getElement(uint64 index);

	void addElement(Element<T>* element);
	void addElement(Element<T>* elemnt, uint64 index);
	void add(T item);
	void add(T item, uint64 index);

	void removeElement(Element<T>* element);
	Element<T>* removeElement(uint64 index);
	T remove(uint64 index);
	void remove(T item);

	Iterator<T>* iterator();
};

// -- implementation --

#include <list.h>
#include <memory.h>
#include <errors.h>
#include <log.h>

template<typename T>
List<T>* List<T>::destroy() {
	Element<T>* element = first;
	Element<T>* next;

	do {
		removeElement(element);
		next = element->next;
		delete element;
	} while ((element = next) != NULL);

	return this;
}

// ---- simple stuffs ----

template<typename T>
uint64 List<T>::size() {
	return length;
}

template<typename T>
bool List<T>::isEmpty() {
	return size() == 0;
}

template<typename T>
uint64 List<T>::indexOf(T item) {
	for (uint64 i = 0; i < size(); i++) {
		if (get(i) == item) {
			return i;
		}
	}

	return -1;
}

// ---- isFirst ----

template<typename T>
bool List<T>::isFirst(Element<T>* element) {
	return first == element;
}

// ---- isLast -----

template<typename T>
bool List<T>::isLast(uint64 index) {
	return index == size() - 1;
}

template<typename T>
bool List<T>::isLast(Element<T>* element) {
	return last == element;
}

// ---- get ----

template<typename T>
Element<T>* List<T>::getElement(uint64 index) {
	if (index >= size()) {
		debug("index", index);
		debug("size", size());
		crash(INDEX_OUT_OF_BOUNDS);
	}

	Element<T>* element = first;

	for (uint64 i = 0; i < index; i++) {
		element = element->next;
	}

	return element;
}

template<typename T>
T List<T>::get(uint64 index) {
	return getElement(index)->value;
}

// ---- add ----

template<typename T>
void List<T>::addElement(Element<T>* element) {
	if (size() == 0) {
		first = element;
		last = element;
	} else {
		last->next = element;
	}

	length++;
}

template<typename T>
void List<T>::add(T item) {
	Element<T>* element = new Element<T>();
	element->value = item;

	addElement(element);
}

template<typename T>
void List<T>::addElement(Element<T>* element, uint64 index) {
	// update references
	if (size() == 0) { // initial
		first = element;
		last = element;
	} else {
		Element<T>* existingElement = getElement(index);
		if (isFirst(index)) { // at the beginning
			Element<T>* after = existingElement;
			element->next = after;
			first = element;
		} else if (index == size()) { // append at the end, cannot use isLast()
			last->next = element;
		} else { // in the middle
			Element<T>* before = existingElement->previous;
			Element<T>* after = element;

			before->next = element;
			element->next = after;
		}
	}

	length++;
}

template<typename T>
void List<T>::add(T item, uint64 index) {
	Element<T>* element = new Element<T>();
	element->value = item;

	addElement(element, index);

}

// ---- remove ----

template<typename T>
void List<T>::removeElement(Element<T>* element) {
	if (size() > 1) {
		if (isFirst(element)) { // at the beginning and there is another element
			first = element->next;
		} else if (isLast(element)) { // at the end
			Element<T>* before = element->previous;
			before->next = 0;
			last = before;
		} else { // in the middle
			Element<T>* before = element->previous;
			Element<T>* after = element->next;

			before->next = after;
		}
	}
	length--;
}

template<typename T>
Element<T>* List<T>::removeElement(uint64 index) {
	if (index >= size()) {
		debug("index", index);
		debug("size", size());
		crash(INDEX_OUT_OF_BOUNDS);
	}

	Element<T>* element = getElement(index);
	removeElement(element);
	return element;
}

template<typename T>
T List<T>::remove(uint64 index) {
	Element<T>* element = removeElement(index);
	T item = element->value;
	delete element;
	return item;
}

template<typename T>
void List<T>::remove(T item) { // TODO optomize
	for (uint64 i = 0; i < size(); i++) {
		if (get(i) == item) {
			remove(i);
		}
	}
}

// ---- iterator ----

template<typename T>
Iterator<T>* List<T>::iterator() {
	return new Iterator<T>(first);
}

template<typename T>
Iterator<T>::Iterator(Element<T>* current) {
	this->current = current;
}

template<typename T>
T Iterator<T>::next() {
	T value = current->value;
	current = current->next;

	return value;
}

#endif /* INCLUDE_LIST_H_ */
