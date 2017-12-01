#include "stack.h"
using namespace cop4530;
template <typename T, class Con >
Stack<T,Con>::Stack(): C(0){}                                               //  zero argument constructor

template <typename T, class Con>
Stack<T,Con>::~Stack (){ clear();}                                          // destructor

template <typename T, class Con>
Stack<T,Con>::Stack (const Stack<T,Con>& l) { C = l.C;}                     // copy constructor.

 template <typename T, class Con>
Stack<T,Con>::Stack(Stack<T,Con> && r){ C = r.C;}                           // move constructor.

template <typename T, class Con>
Stack<T,Con> & Stack<T,Con>::operator= (const Stack <T,Con>& l) {    // copy assignment operator=.
    if(this != &l) {
        clear();
        C = l.C;
    }
    return *this;
}
 template <typename T, class Con>
Stack<T,Con> & Stack<T,Con>::operator=(Stack<T,Con> && r) {         // move assignment operator=
     C = std::move(r.C);
     return *this;
 }
template <typename T, class Con>
bool Stack<T,Con>::empty() const{ return C.empty();}                 // returns true if the Stack contains no elements, and false otherwise.

template <typename T, class Con>
void Stack<T,Con>::clear(){ C.clear();}                             // delete all elements from the stack.

template <typename T, class Con>
void Stack<T,Con>::push(const T& x) {                               // adds  x  to the Stack.   copy version.
    C.push_back(x);
}

template <typename T, class Con>
void Stack<T,Con>::rev(){
    if(!empty()){
        auto i = C.begin();           //start iterator at beginning
        while( i != C.end()) {        //while the end is not reached..
            C.push_front(*i);         //add the first element to the front of the list
            i = C.erase(i);           //remove the element at current position, and return the next element
        }
    }
}
template <typename T, class Con>
void Stack<T,Con>::push(T && x){
    C.push_back(std::move(x));
}                   // adds x to the Stack. move version.

template <typename T, class Con>
void Stack<T,Con>::pop() { C.pop_back();}                           // removes and discards the most recently added element of the Stack.

template <typename T, class Con>
T& Stack<T,Con>::top(){return C.back();}                            // returns a reference to the most recently added element of the Stack
                                                                    // (as a modifiable L-value).

template <typename T, class Con>
const T& Stack<T,Con>::top() const{ return C.back();}                   // accessor that returns the most recently added element of the Stack
                                                                        // (as a const reference)

template <typename T, class Con>
int Stack<T,Con>::size() const{return C.size();}                       // returns the number of elements stored in the Stack.

// print elements of Stack to ostream os. ofc is the separator between elements in
// the stack when they are printed out. Note that print() prints elements in the
// opposite order of the Stack (that is, the oldest element should be printed first).
template <typename T, class Con>
void Stack<T,Con>::print(std::ostream& os, char ofc ) const{
    for(auto x = C.begin(); x != C.end(); x++){
        //std::cout<< "in print x : "<< *x<<'\n';   //delete
        os<< *x;
        if(x != --C.end())
            os<< ofc;
    }
}

// invokes the print() method to print the Stack<T> a in the specified ostream
template<typename T, class Con = std::list<T>>
std::ostream& operator<< (std::ostream& os, const Stack<T,Con>& a){
    a.print(os);
    return os;
}

// returns true if the two compared Stacks have the same elements, in the same
// order, and false otherwise
template<typename T, class Con = std::list<T>>
bool operator== (const Stack<T,Con>& x , const Stack <T,Con>& y){
    if(x.size() == y.size()) {
        auto tx = x, ty =y;
        while(!tx.empty()){
            if(tx.top() != ty.top())
                return false;
            tx.pop();
            ty.pop();
        }
        return true;
    }
    return false;
}

// opposite of operator==().
template<typename T, class Con = std::list<T>>
bool operator!= (const Stack<T,Con>&x, const Stack <T,Con>&y){
    return !(x == y);
}

// returns true if every element in Stack is smaller than or equal to the
// corresponding element of Stack b, i.e., if repeatedly invoking top() and pop()
// on both a and b,  we will generate a sequence of elements ai from a and bi
// from b, and for every i,  ai ≤ bi, until a is empty.

template<typename T, class Con = std::list<T>>
bool operator<= (const Stack<T,Con>& a, const Stack <T,Con>& b){

    if(a.size() > b.size()){
        return false;
    }
    Stack<T,Con> tx = a, ty =b;
    if(ty.size() > tx.size()){
        int i = 0;
        int s = ty.size() - tx.size();
        while (i < s) {
            ty.pop();
            i++;
        }
    }
    if(tx.size() == ty.size()) {
        while(!tx.empty()){
            if(tx.top() > ty.top()) {
                return false;
            }
            tx.pop();
            ty.pop();
        }
        return true;
    }
     return false;
}
