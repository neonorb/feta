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

#endif /* INCLUDE_LIST_H_ */
