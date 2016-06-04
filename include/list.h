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

template<typename T> class Element: Deleteable {
public:
	T value;
	Element<T>* next;
};

template<typename T> class Iterator: Deleteable {
private:
	Element<T>* current;
public:
	Iterator(Element<T>* current);

	T next();
};

template<typename T> class List: Deleteable {
private:
	Element<T>* first;
	Element<T>* getElement(uint64 index);
	uint64 length = 0;

public:
	void destroy();

	uint64 size();bool isEmpty();bool isLast(uint64 index);
	uint64 indexOf(T item);

	T get(uint64 index);

	void addElement(Element<T>* element);
	void addElement(Element<T>* elemnt, uint64 index);
	void add(T item);
	void add(T item, uint64 index);

	T removeElement(Element<T>* element);
	T removeElement(uint64 index);
	T remove(uint64 index);
	T remove(T item);

	Iterator<T>* iterator();
};

// -- implementation --

#include <list.h>
#include <memory.h>
#include <errors.h>
#include <log.h>

template<typename T>
void List<T>::destroy() {
	Element<T>* element = first;

	do {
		removeElement(element);
	} while ((element = first->next) != NULL);
}

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
	} else {
		getElement(size() - 1)->next = element;
	}

	length++;
}

template<typename T>
void List<T>::add(T item) {
	Element<T>* element = (Element<T>*) malloc(sizeof(Element<T> ));
	element->value = item;

	addElement(element);
}

template<typename T>
void List<T>::addElement(Element<T>* element, uint64 index) {
	// update references
	if (size() == 0) { // initial
		first = element;
	} else if (index == 0) { // at the beginning
		Element<T>* after = getElement(index);
		element->next = after;
		first = element;
	} else if (index == size()) { // at the end
		Element<T>* before = getElement(index - 1);
		before->next = element;
	} else { // in the middle
		Element<T>* before = getElement(index - 1);
		Element<T>* after = getElement(index);

		before->next = element;
		element->next = after;
	}

	length++;
}

template<typename T>
void List<T>::add(T item, uint64 index) {
	Element<T>* element = (Element<T>*) malloc(sizeof(Element<T> ));
	element->value = item;

	addElement(element, index);

}

// ---- remove ----

template<typename T>
T List<T>::removeElement(Element<T>* element) {
	T item = element->value;

	delete element;

	return item;
}

template<typename T>
T List<T>::removeElement(uint64 index) {
	if (index >= size()) {
		debug("index", index);
		debug("size", size());
		crash(INDEX_OUT_OF_BOUNDS);
	}

	Element<T>* element = getElement(index);

	T item = element->value;

	delete element;

	// update references
	if (size() > 1) {
		if (index == 0) { // at the beginning and there is another element
			first = getElement(index + 1);
		} else if (isLast(index)) { // at the end
			Element<T>* before = getElement(index - 1);
			before->next = 0;
		} else { // in the middle
			Element<T>* before = getElement(index - 1);
			Element<T>* after = getElement(index + 1);

			before->next = after;
		}
	}
	length--;

	return item;
}

template<typename T>
T List<T>::remove(uint64 index) {
	return removeElement(removeElement(index));
}

template<typename T>
T List<T>::remove(T item) {
	for (uint64 i = 0; i < size(); i++) {
		if (get(i) == item) {
			return remove(i);
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
