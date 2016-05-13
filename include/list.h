/*
 * list.h
 *
 *  Created on: May 8, 2016
 *      Author: chris
 */

#ifndef INCLUDE_LIST_H_
#define INCLUDE_LIST_H_

#include <int.h>
#include <bool.h>

template<typename T> struct Element {
	T value;
	Element<T>* next;
};

template<typename T> class List {
private:
	Element<T>* first;
	Element<T>* getElement(uint64 index);
	uint64 length = 0;

public:
	uint64 size();
	bool isEmpty();

	bool isLast(uint64 index);
	uint64 indexOf(T item);

	T get(uint64 index);

	void add(Element<T>* element);
	void add(T item);
	void add(T item, uint64 index);

	T remove(uint64 index);
};

#include <list.h>
#include <memory.h>
#include <errors.h>

template<typename T>
uint64 List<T>::size() {
	return length;
}

template<typename T>
bool List<T>::isEmpty() {
	return size() == 0;
}

template<typename T>
bool List<T>::isLast(uint64 index) {
	return index == size() - 1;
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

template<typename T>
Element<T>* List<T>::getElement(uint64 index) {
	Element<T>* element = first;

	for (uint64 i = 0; i < index - 1; i++) {
		if (element->next == 0) {
			crash(INDEX_OUT_OF_BOUNDS);
		}
		element = element->next;
	}

	return element;
}

template<typename T>
T List<T>::get(uint64 index) {
	return getElement(index)->value;
}

template<typename T>
void List<T>::add(Element<T>* element) {
	if (size() == 0) {
		first = element;
	} else {
		getElement(size() - 1)->next = element;
	}
}

template<typename T>
void List<T>::add(T item) {
	Element<T>* element = getMemory(sizeof(Element<T> ));
	element->value = item;

	add(element);
}

template<typename T>
void List<T>::add(T item, uint64 index) {
	Element<T>* newElement = (Element<T>*)getMemory(sizeof(Element<T> ));

	newElement->value = item;

	// update references
	if (size() == 0) { // initial
		first = newElement;
	} else if (index == 0) { // at the beginning
		Element<T>* after = getElement(index);
		newElement->next = after;
		first = newElement;
	} else if (index == size() - 1) { // at the end
		Element<T>* before = getElement(index);
		before->next = newElement;
	} else { // in the middle
		Element<T>* before = getElement(index - 1);
		Element<T>* after = getElement(index);

		before->next = newElement;
		newElement->next = after;
	}

	length++;
}

template<typename T>
T List<T>::remove(uint64 index) {
	Element<T>* removed = getElement(index);
	T item = removed->value;

	free(removed, sizeof(Element<T>));
	length--;

	// update references
	if (size() == 0) {
		crash(INDEX_OUT_OF_BOUNDS);
	} else if (index == 0) { // at the beginning
		first = getElement(index + 1);
	} else if (index == size() - 1) { // at the end
		Element<T>* before = getElement(index - 1);
		before->next = 0;
	} else { // in the middle
		Element<T>* before = getElement(index - 1);
		Element<T>* after = getElement(index + 1);

		before->next = after;
	}

	return item;
}


#endif /* INCLUDE_LIST_H_ */
