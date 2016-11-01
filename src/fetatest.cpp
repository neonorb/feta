/*
 * test.cpp
 *
 *  Created on: Nov 1, 2016
 *      Author: chris13524
 */

#ifdef ALLOW_TEST
#include <fetatest.h>
#include <stack.h>

using namespace feta;

void assert(bool b, String message) {
	if(!b) {
		crash(message);
	}
}

namespace fetatest {

	static void list() {
		log("  - list");

		List<char> list;

		assert(list.size() == 0, "list size is not 0");

		list.add(5);
		assert(list.size() == 1, "list size is not 1");
		assert(list.get(0) == 5, "value @ 0 is not 5");

		Iterator<char> iterator = list.iterator();
		bool didFirst = false;
		while(iterator.hasNext()) {
			char value = iterator.next();
			didFirst = true;
			assert(value == 5, "iterator value is not 5");
		}
		assert(didFirst, "iterator didn't do first");

		assert(list.remove((uinteger) 0) == 5, "removed value is not 5");
		assert(list.size() == 0, "list size is not 0 (2)");

		list.add('a');
		list.add('b');
		list.add('c');
		list.add('d');
		list.add('e');
		list.add('f');
		list.add('g');
		list.add('h');

		assert(list.size() == 8, "list size is not 3");
		assert(list.get(2) == 'c', "value @ 2 is not c");
		assert(list.get(7) == 'h', "value @ 7 is not h");

		list.clear();
	}

	static void stack() {
		log("  - stack");

		Stack<int> stack;

		assert(stack.size() == 0, "stack size is not 0");

		stack.push(5);
		assert(stack.size() == 1, "stack size is not 1");
		assert(stack.peek() == 5, "peeked value is not 5");

		assert(stack.pop() == 5, "popped value is not 5");
		assert(stack.size() == 0, "stack size is not 0 (2)");

		stack.push(10);
		stack.push(11);
		stack.push(12);
		stack.push(13);
		assert(stack.size() == 4, "stack size is not 4");
		assert(stack.peek() == 13, "peeked value is not 13");

		stack.pop();
		assert(stack.size() == 3, "stack size is not 3");
	}

	static void string() {
		log("  - string");

		String first = substring("__print", 2, 7);
		String second = "print"_H;

		assert(strequ(first, second), "string not equal");

		delete first;
		delete second;
	}

	void test() {
		list();
		stack();
		string();
	}

}
#endif
