/*
 * lambda.h
 *
 *  Created on: Oct 26, 2016
 *      Author: chris13524
 */

#ifndef INCLUDE_LAMBDA_H_
#define INCLUDE_LAMBDA_H_

template<typename Return, typename Argument>
class Lambda {
public:
	typedef Return (*LambdaFunction)(void*, Argument);
	Lambda() {
	}
	Lambda(void* capture, LambdaFunction function) {
		this->capture = capture;
		this->function = function;
	}

	Return operator()(Argument argument) {
		return function(capture, argument);
	}
private:
	void* capture;
	LambdaFunction function;
};

#endif /* INCLUDE_LAMBDA_H_ */
