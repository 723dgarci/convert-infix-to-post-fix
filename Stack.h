//
// Created by WorkD on 10/19/2017.
//

#ifndef ASSIGNMENT3_STACK_H
#define ASSIGNMENT3_STACK_H
#include <iostream>
#include <list>
namespace cop4530 {
    template <typename T, class Con = std::list<T> >
    class Stack {
    protected:
        Con C;
    public:
        Stack();                                //  zero argument constructor

        ~Stack ();                              // destructor
        Stack (const Stack<T,Con>&);                // copy constructor.
        Stack(Stack<T,Con> &&);                     // move constructor.

        Stack<T,Con>& operator= (const Stack <T,Con>&); // copy assignment operator=.
        Stack<T,Con> & operator=(Stack<T,Con> &&);      // move assignment operator=

        bool empty() const;                     // returns true if the Stack contains no elements, and false otherwise.

        void clear();                           // delete all elements from the stack.

        void push(const T& x);                  // adds  x  to the Stack.   copy version.

        void push(T && x);                      // adds x to the Stack. move version.

        void pop();                             // removes and discards the most recently added element of the Stack.

        T& top() ;                               // returns a reference to the most recently added element of the Stack

                                                // (as a modifiable L-value).

        const T& top() const;                   // accessor that returns the most recently added element of the Stack
                                                // (as a const reference)

        int size() const;                       // returns the number of elements stored in the Stack.

        void rev();
        // print elements of Stack to ostream os. ofc is the separator between elements in
        // the stack when they are printed out. Note that print() prints elements in the
        // opposite order of the Stack (that is, the oldest element should be printed first).
         void print(std::ostream& os, char ofc = ' ') const;

    };
        // invokes the print() method to print the Stack<T> a in the specified ostream
        template<typename T, class Con = std::list<T>>
        std::ostream& operator<< (std::ostream& os, const Stack<T,Con>& a);

        // returns true if the two compared Stacks have the same elements, in the same
        // order, and false otherwise
        template<typename T, class Con = std::list<T>>
        bool operator== (const Stack<T,Con>&, const Stack <T,Con>&);

        // opposite of operator==().
        template<typename T, class Con = std::list<T>>
        bool operator!= (const Stack<T,Con>&, const Stack <T,Con>&);

        // returns true if every element in Stack is smaller than or equal to the
        // corresponding element of Stack b, i.e., if repeatedly invoking top() and pop()
        // on both a and b,  we will generate a sequence of elements ai from a and bi
        // from b, and for every i,  ai ≤ bi, until a is empty.
        template<typename T, class Con = std::list<T>>
        bool operator<= (const Stack<T,Con>& a, const Stack <T,Con>& b);

#include "stack.hpp"
}//end of namespace

#endif //ASSIGNMENT3_STACK_H
