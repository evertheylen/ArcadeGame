

#ifndef _H_dispatch_base
#define _H_dispatch_base

template <typename ReturnT, typename... ArgBaseType>
class Dispatcher {
public:
	
	virtual ReturnT operator()(ArgBaseType... args) {
		return doRule(getRule(args...), args...);
	}
	
	virtual int getRule(ArgBaseType... args) = 0;
	
	virtual ReturnT doRule(int a, ArgBaseType... args) = 0;
	
	virtual ~Dispatcher() {}
};

template <typename ReturnT, typename Arg1T, typename Arg2T>
class SymmetricDoubleDispatcher: public Dispatcher<ReturnT, Arg1T, Arg2T> {
public:
	ReturnT operator()(Arg1T arg1, Arg2T arg2) {
		int normal_priority = this->getRule(arg1, arg2);
		int inverse_priority = this->getRule(arg2, arg1);
		
		if (normal_priority <= inverse_priority) {
			return this->doRule(normal_priority, arg1, arg2);
		} else {
			return this->doRule(inverse_priority, arg2, arg1);
		}
	}
};

#endif
