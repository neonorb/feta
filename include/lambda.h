/*
 * lambda.h
 *
 *  Created on: Oct 26, 2016
 *      Author: chris13524
 */

#ifndef INCLUDE_LAMBDA_H_
#define INCLUDE_LAMBDA_H_

/*template<typename Return, typename Argument>
 class Lambda {
 public:
 typedef Return (*LambdaFunction)(void*, Argument);
 Lambda() {
 }
 Lambda(void* capture[], LambdaFunction function) {
 this->capture = capture;
 this->function = function;
 }

 Return operator()(Argument argument) {
 return function(capture, argument);
 }
 private:
 void* capture[];
 LambdaFunction function;
 };

 template<typename Argument>
 class VoidLambda {
 public:
 typedef void (*LambdaFunction)(Argument);
 VoidLambda() {
 }
 VoidLambda(void* capture[], LambdaFunction function) {
 this->capture = capture;
 this->function = function;
 }

 void operator()(Argument argument) {
 function(capture, argument);
 }
 private:
 void* capture[];
 LambdaFunction function;
 };*/

template<class T> class Lambda {
};

template<class Res, class ... ArgTypes>
class Lambda<Res(ArgTypes...)> // Parsing the Lambda type
{
	union Pointers // An union to hold different kind of pointers
	{
		Res (*func)(void*, ArgTypes...); // void (*)(Funny*, int)
		Res (*mem_func)(ArgTypes...); // void (Funny::*)(int)
	};
	typedef Res Callback(Pointers&, void*, ArgTypes...);

	Pointers ptrs;
	Callback* callback;

	static Res call_func(Pointers& ptrs, void* obj, ArgTypes ... args) {
		return (*ptrs.func)(&obj, args...); // void (*)(Funny*, int)
	}
	static Res call_mem_func(Pointers& ptrs, void* obj, ArgTypes ... args) {
		return (obj.*(ptrs.mem_func))(args...); // void (Funny::*)(int)
	}

public:

	Lambda() :
			callback(0) {
	}
	Lambda(Res (*func)(void*, ArgTypes...)) // void (*)(Funny*, int)
			{
		ptrs.func = func;
		callback = &call_func;
	}
	Lambda(Res (*mem_func)(ArgTypes...)) // void (Funny::*)(int)
			{
		ptrs.mem_func = mem_func;
		callback = &call_mem_func;
	}
	Lambda(const Lambda& Lambda) {
		ptrs = Lambda.ptrs;
		callback = Lambda.callback;
	}
	Lambda& operator=(const Lambda& Lambda) {
		ptrs = Lambda.ptrs;
		callback = Lambda.callback;
		return *this;
	}
	Res operator()(void* obj, ArgTypes ... args) {
		return (*callback)(ptrs, obj, args...);
	}
};

// ==================

class Object {
public:
	void hello(int x) {

	}
};

template<class T> class Functionn {

};
template<class Return, class ... Args>
class Functionn<Return(Args...)> {
public:
	typedef Return (void::*Func)(Args...);

	Functionn(void* object, Func function) {
		this->object = object;
		this->function = function;
	}

	void operator()(Args ... args) {
		(*function)(object, args...);
	}
private:
	void* object;
	Func function;
};

void hi() {
	Object* obj;
	Functionn<void(int)> func = Functionn<void(int)>(obj, &Object::hello);
	func(10);
}

#endif /* INCLUDE_LAMBDA_H_ */
