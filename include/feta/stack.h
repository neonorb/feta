/*
 * stack.h
 *
 *  Created on: Jun 6, 2016
 *      Author: chris
 */

#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

namespace feta {

template<typename T>
class Stack {
private:
	List<T> list = List<T>();
public:
	Stack();
	Stack(T initial);
	~Stack();

	int size();

	void push(T item);
	T pop();
	T peek();
	T peek(uint64 distance);
};

// ---- constructors ----
template<typename T>
Stack<T>::Stack() {

}

template<typename T>
Stack<T>::Stack(T initial) {
	push(initial);
}

template<typename T>
Stack<T>::~Stack() {
	list.clear();
}

// ---- methods ----

template<typename T>
int Stack<T>::size() {
	return list.size();
}

template<typename T>
void Stack<T>::push(T item) {
	list.add(item);
}

template<typename T>
T Stack<T>::pop() {
	if (list.size() == 0) {
		crash("no more elements to pop");
	}

	return list.remove(list.size() - 1);
}

template<typename T>
T Stack<T>::peek() {
	return peek(0);
}

template<typename T>
T Stack<T>::peek(uint64 distance) {
	if (list.size() - distance <= 0) {
		crash("not enough elements to peek here");
	}

	return list.get(list.size() - distance - 1);
}

}

#endif /* INCLUDE_STACK_H_ */
