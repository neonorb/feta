/*
 * stack.h
 *
 *  Created on: Jun 6, 2016
 *      Author: chris
 */

#ifndef INCLUDE_STACK_H_
#define INCLUDE_STACK_H_

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
	return list.remove(list.size() - 1);
}

template<typename T>
T Stack<T>::peek() {
	return peek(1);
}

template<typename T>
T Stack<T>::peek(uint64 distance) {
	return list.get(list.size() - distance);
}

#endif /* INCLUDE_STACK_H_ */
