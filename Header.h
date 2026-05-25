#pragma once

#include <iostream>
#include <string>
#include <map>

class BracketsTest;

class Stack {
	char* arr = nullptr;
	size_t capacity = 0;
	int top_index = -1;
	int max_deep = 0;

public:
	Stack(size_t size);
	~Stack(void);

	bool is_empty(void) const;
	char top(void) const;
	void push(char ch);
	char pop(void);
	int get_max_deep(void) const;
	void print(void);

};


class BracketsTest{
	std::string str = "";
	size_t len = 0;
	const std::string alph = "<>{}[]()";
	const std::map<char, char> dict = {
		{'>', '<'},
		{'}', '{'},
		{']', '['},
		{')', '('}
	};

public:
	int first_error = -1;
	int count_pair = 0;
	int max_deep = 0;
	int type_error = -1;

	BracketsTest(std::string str);
	
	std::string get_type_error(void) const;
	std::string get_brackets_balance(void) const;
	bool in_alph(char ch) const;
	bool test(void);
	
};