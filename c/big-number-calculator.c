/* -----------
 * bignum_math.c
 * Project for CSCI 2021, Fall 2018, Professor Chris Dovolis
 * orginially written by Andy Exley
 * modified by Ry Wiese, Min Choi, Aaron Councilman
 * ---------- */

/* ----------
 * This program takes large numbers of any base, 2 to 36,
 * and can perform mathematic functions on those numbers.
 * The numbers can be any size, larger than standard int.
 * ---------- */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define false 0;
#define true 1;

typedef int bool;

/*
 * Returns true if the given char is a digit from 0 to 9
 */
bool is_digit(char c) {
	return c >= '0' && c <= '9';
}

/*
 * Returns true if lower alphabetic character
 */
bool is_lower_alphabetic(char c) {
	return c >= 'a' && c <= 'z';
}

/*
 * Returns true if upper alphabetic character
 */
bool is_upper_alphabetic(char c) {
	return c >= 'A' && c <= 'Z';
}

/*
 * Convert a string to an integer
 * returns 0 if it cannot be converted.
 */
int string_to_integer(char* input) {
	int result = 0;
	int length = strlen(input);
	int num_digits = length;
	int sign = 1;

	int i = 0;
	int factor = 1;

	if (input[0] == '-') {
		num_digits--;
		sign = -1;
	}

	for (i = 0; i < num_digits; i++, length--) {
		if (!is_digit(input[length-1])) {
			return 0;
		}
		if (i > 0) factor*=10;
		result += (input[length-1] - '0') * factor;
	}

	return sign * result;
}

/*
 * Returns true if the given base is valid.
 * that is: integers between 2 and 36
 */
bool valid_base(int base) {
	if(!(base >= 2 && base <= 36)) {
		return false;
	}
	return true;
}

/*
 * Returns true if the given string (char array) is a valid input,
 * that is: digits 0-9, letters A-Z, a-z
 * and it should not violate the given base and should not handle negative numbers
 * Determines if each character is digit or lower/upper alphabetic.
 * If it is a digit, checks for negativity or above base
 * If it is a letter, checks to make sure not above base
 * Returns false is character is not alphanumeric
 * If all characters pass the checks, return true
*/
bool valid_input(char* input, int base) {
	int test;
	int i;
	for (i=0; input[i] != '\0'; i++) {
		if(is_digit(input[i])) {
			test = input[i] - '0';
			if (test > (base-1) || test < 0 || test > 9) {
				return false;
			}
		}
		else if(is_lower_alphabetic(input[i])) {
			test = input[i] - 'a' + 10;
			if(test > (base-1)) {
				return false;
			}
		}
		else if(is_upper_alphabetic(input[i])) {
			test = input[i] - 'A' + 10;
			if(test > (base-1)) {
				return false;
			}
		}
		else {
			return false;
		}
	}
	return true;
}

/*
 * converts from an array of characters (string) to an array of integers
 */
int* string_to_integer_array(char* str) {
	int* result;
	int i, str_offset = 0;
	result = malloc((strlen(str) + 1) * sizeof(int));
	result[strlen(str)] = -1;
	for(i = str_offset; str[i] != '\0'; i++) {
		if(is_digit(str[i])) {
			result[i - str_offset] = str[i] - '0';
		} else if (is_lower_alphabetic(str[i])) {
			result[i - str_offset] = str[i] - 'a' + 10;
		} else if (is_upper_alphabetic(str[i])) {
			result[i - str_offset] = str[i] - 'A' + 10;
		} else {
			printf("I don't know how got to this point!\n");
		}
	}
	return result;
}

/*
 * finds the length of a bignum...
 * simply traverses the bignum until a negative number is found.
 */
int bignum_length(int* num) {
	int len = 0;
	while(num[len] >= 0) { len++; }
	return len;
}

/*
 * Converts each integer in the array to the corresponding ASCII character
 * Digits less than 10 are a simple conversion
 * Digits greater than 10 require being converted to an alphabetic character
 * Prints each converted character
 */
void bignum_print(int* num) {
	int i;
	if(num == NULL) { return; }

	i = bignum_length(num);

	for(i = 0; num[i] >= 0; i++) {
		if(num[i] < 10) {
			char temp = num[i] + '0';
			printf("%c",temp);
		}
		else {
			char temp = num[i] + 39 + '0';
			printf("%c",temp);
		}
	}
	printf("\n");
}

/*
 *	Helper for reversing the result that we built backward.
 *  see add(...) below
 */
void reverse(int* num) {
	int i, len = bignum_length(num);
	for(i = 0; i < len/2; i++) {
		int temp = num[i];
		num[i] = num[len-i-1];
		num[len-i-1] = temp;
	}
}

/*
 * addition of input1 and input2
 */
int* add(int* input1, int* input2, int base) {
	int len1 = bignum_length(input1);
	int len2 = bignum_length(input2);
	int resultlength = ((len1 > len2)? len1 : len2) + 2;
	int* result = (int*) malloc (sizeof(int) * resultlength);
	int r = 0;
	int carry = 0;
	int sign = input1[len1];
	int num1, num2;

	len1--;
	len2--;

	while (len1 >= 0 || len2 >= 0) {
    if (len1 >= 0) {
  	    num1 = input1[len1];
    } else {
  	    num1 = 0;
  	}

		if (len2 >= 0) {
		    num2 = input2[len2];
		} else {
		    num2 = 0;
		}

		result[r] = (num1 + num2 + carry) % base;
		carry = (num1 + num2 + carry) / base;

		len1--;
		len2--;
		r++;
	}
	if (carry > 0) {
		result[r] = carry;
		r++;
    	}
	result[r] = sign;
	reverse(result);
	return result;
}


/*
 * return true if input1 < input2, and false otherwise
 * Checks the lengths of each bignum first
 * A smaller length means definitely less than, a bigger one means definitely not
 * If lengths are the same, compares each digit one by one
 * A smaller digit means it is less than, a larger one means it is not
 * If they are equal, moves to the next digit
 * If the end of the number is reached, it is assumed they are equal and returns false
*/
bool less_than(int* input1, int* input2) {
	int i;
	int len1 = bignum_length(input1);
	int len2 = bignum_length(input2);
	if (len1 < len2) {
		return true;
	}
	else if (len1 > len2) {
		return false;
	}
	for (i=0; input1[i] > 0 || input2[i] > 0; i++) {
		if (input1[i] < input2[i]) {
			return true;
		}
		else if (input1[i] > input2[i]) {
			return false;
		}
	}
	return false;
}


/*
 * return true if input1 > input2, and false otherwise
 * Checks the lengths of each bignum first
 * A bigger length means definitely greater than, a smaller one means definitely not
 * If lengths are the same, compares each digit one by one
 * A larger digit means it is less than, a smaller one means it is not
 * If they are equal, moves to the next digit
 * If the end of the number is reached, it is assumed they are equal and returns false
 */
bool greater_than(int* input1, int* input2) {
	int i;
	int len1 = bignum_length(input1);
	int len2 = bignum_length(input2);
	if (len1 > len2) {
		return true;
	}
	else if (len1 < len2) {
		return false;
	}
	for (i=0; input1[i] > 0 || input2[i] > 0; i++) {
		if (input1[i] > input2[i]) {
			return true;
		}
		else if (input1[i] < input2[i]) {
			return false;
		}
	}
	return false;
}

/*
 * return true if input1 == input2, and false otherwise
 * Checks to make sure if lengths of bignums are the same first, not equal if they are not
 * Then compares each digit one by one
 * If they are not equal, returns false
 * If each digit is compared and found to be equal, returns true
 */
bool equal_to(int* input1, int* input2) {
	int i;
	int len1 = bignum_length(input1);
	int len2 = bignum_length(input2);
	if (len1 != len2) {
		return false;
	}
	for (i=0; input1[i] > 0 || input2[i] > 0; i++) {
		if (input1[i] != input2[i]) {
			return false;
		}
	}
	return true;
}


/*
 * multiply input1 * input2
 * Uses addition to find result
 * Starts by finding the lower of the two numbers, to save time
 * Sets the result and a counter to 0 to start
 * Counter counts up by 1 until it equals the lower of the two numbers
 * At the same time, the higher of the two numbers is added to the result
 */
int* multiply(int* input1, int* input2, int base) {
	int len1 = bignum_length(input1);
	int len2 = bignum_length(input2);
	int resultlength = len1 + len2 + 2;
	int* result = (int*) malloc (sizeof(int) * resultlength);
	int* zeroA = string_to_integer_array("0");
	int* oneA = string_to_integer_array("1");
	int* counter = zeroA;
	if (less_than(input1,input2)) {
		result = add(zeroA,zeroA,base);
		counter = add(zeroA,zeroA,base);
		while (!equal_to(counter,input1)) {
			result = add(input2,result,base);
			counter = add(counter,oneA,base);
		}
	}
	else {
		result = add(zeroA,zeroA,base);
		counter = add(zeroA,zeroA,base);
		while (!equal_to(counter,input2)) {
			result = add(input1,result,base);
			counter = add(counter,oneA,base);
		}
	}
	return result;
}

/*
 * Checks for which valid operator has been passed into the function
 * Calls the corresponding operator function
 * Then stores the result of the corresponding operation
 * Prints result and frees data if necessary
 */
void perform_operation(int* input1, int* input2, char op, int base) {
	if(op == '+') {
		int* result = add(input1, input2, base);
		printf("Result: ");
		bignum_print(result);
		printf("\n");
		free(result);
	}
	else if (op == '<') {
		bool result = less_than(input1, input2);
		printf("Result: ");
		if (result) {
			printf("true");
		}
		else {
			printf("false");
		}
		printf("\n");
	}
	else if (op == '>') {
		bool result = greater_than(input1, input2);
		printf("Result: ");
		if (result) {
			printf("true");
		}
		else {
			printf("false");
		}
		printf("\n");
	}
	else if (op == '=') {
		bool result = equal_to(input1, input2);
		printf("Result: ");
		if (result) {
			printf("true");
		}
		else {
			printf("false");
		}
		printf("\n");
	}
	else if(op == '*') {
		int* result = multiply(input1, input2, base);
		printf("Result: ");
		bignum_print(result);
		printf("\n");
		free(result);
	}
	else {
		printf("You managed to do something quite wrong!\n");
	}
}

/*
 * Print to "stderr" and exit program
 */
void print_usage(char* name) {
	fprintf(stderr, "----------------------------------------------------\n");
	fprintf(stderr, "Usage: %s base input1 operation input2\n", name);
	fprintf(stderr, "base must be number between 2 and 36, inclusive\n");
	fprintf(stderr, "input1 and input2 are arbitrary-length integers\n");
	fprintf(stderr, "Permited operations are allowed '+', '*', '<', '>', and '='\n");
	fprintf(stderr, "----------------------------------------------------\n");
	exit(1);
}


/*
 * MAIN: Run the program and tests your functions.
 * sample command: ./bignum 4 12 + 13
 * Result: 31
 */
int main(int argc, char** argv) {

	int input_base;

	int* input1;
	int* input2;

	if(argc != 5) {
		print_usage(argv[0]);
	}

	input_base = string_to_integer(argv[1]);

	if(!valid_base(input_base)) {
		fprintf(stderr, "Invalid base: %s\n", argv[1]);
		print_usage(argv[0]);
	}


	if(!valid_input(argv[2], input_base)) {
		fprintf(stderr, "Invalid input1: %s\n", argv[2]);
		print_usage(argv[0]);
	}

	if(!valid_input(argv[4], input_base)) {
		fprintf(stderr, "Invalid input2: %s\n", argv[4]);
		print_usage(argv[0]);
	}

	char op = argv[3][0];
	if(op != '+' && op != '*' && op != '<' && op != '>' && op != '=') {
		fprintf(stderr, "Invalid operation: %s\n", argv[3]);
		print_usage(argv[0]);
	}

	input1 = string_to_integer_array(argv[2]);
	input2 = string_to_integer_array(argv[4]);

	perform_operation(input1, input2, op, input_base);

	free(input1);
	free(input2);

	exit(0);
}
