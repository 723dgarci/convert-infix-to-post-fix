#include <iostream>
#include "Stack.h"
#include <vector>
#include <string>
#include <cctype>
#include <cstring>
using namespace cop4530;
using namespace std;

Stack<string> in2post(string , bool&);

int precede(char p);

bool isTor(char o);

double ansr(Stack<string>&);
int main () {
    std::cout << "BOP\n" << std::endl;
    /*
    Stack<int> intstk;

    cout << "inserting 10 elements" << endl;
    for (unsigned int i = 0; i < 10; ++i)
        intstk.push(i);

    cout << "Size: " << intstk.size() << endl;

    cout << "elements: " << intstk << endl;

    cout << "emptying the stack" << endl;
    while (!intstk.empty()) {
        cout << intstk.top() << " ";
        intstk.pop();
    }
    cout << endl;

    cout << "Size: " << intstk.size() << endl;

    cout << "inserting 10 elements" << endl;

    for (unsigned int i = 0; i < 10; ++i)
        intstk.push(i);

    Stack<int> intstk1(intstk);
    Stack<int> intstk2;
    intstk2 = intstk;

    //     cout << intstk << endl;
         cout << intstk1 << endl;
         cout << intstk2 << endl;

    if (intstk1 == intstk2)
        cout << "Equal stacks" << endl;
    else
        cout << "ERROR: stacks are not equal" << endl;

    intstk1.pop();
    cout << intstk1 << endl;
    cout << intstk2 << endl;

    if (intstk1 == intstk2)
        cout << "Error: equal stacks" << endl;
    else
        cout << "Stacks are not equal" << endl;

    if (intstk1 <= intstk2)
        cout << "intstk1 is less than or equal to intstk2" << endl;
    else
        cout << "ERROR: wrong comparision" << endl;
    */
    vector<string> file;
    string str;
    Stack<string> post;
    bool eval = true;


    do{
        cout <<"Enter infix expression (\"exit\" to quit):";
        getline(cin,str, '\n');

        if(str != "exit") {
            post = in2post(str, eval);

            cout << "Postfix expression:" << post << "\teval:" << eval<< '\n';
            if(eval){
                post.rev();
                cout <<" post rev(): "<< post<<'\n';
                cout << ansr(post) << '\n';
            }
        }

    }while(str != "exit");



    std::cout << "\n\nEOP" << std::endl;
    return 0;
}

Stack<string> in2post(string v, bool& e) {
    //cout << "befor declarations\n";
    Stack<string> post;
    Stack<string> stk;
    string tok;
    unsigned int pos = 0;
    string del = " ";                                   //used to seperate string coming in
    //bool tor = false;
    //cout << "after declarations\n";

    //cout << "v : "<< v << ' ' << '\n';

    while ( v.size() != 0) {                            //splits string into substrings until size == 2 bc a string must have the last the null terminator
        //cout <<"GOING THROUGH WHILE\n";
        pos = v.find(del);                              //find position of deliminator of v
        tok = v.substr(0, pos);                         //make a token
        if(tok[tok.size()-1]=='\r')                     //takes care of strings with carriage return
            tok =tok.substr(0,tok.size()-1);
        //cout <<"tok :"<< tok << endl;
        v.erase(0,pos + del.length());                              //update the string being passed in
        //cout << "v after cut :"<< v;
        //cout << "\nv.size:"<<v.size() <<'\n';
        if (!isTor(tok[0])) {                 // if the first thing in the vector is and operator or parenthesis
            if(isalpha(tok[0]))                 //if any of the first chars of the operands is an alpha then the equation is not evaluable
                e = false;
            //cout << "print operand" << endl;
            //cout<<"STORE :" << tok << endl;
            post.push(tok);
            //cout <<"test2\n";
        } else if (tok[0] == '+' || tok[0] == '-' || tok[0] == '*' || tok[0] == '/' || tok[0] == '(') {
            if (!stk.empty()) {                                                                                                 //if stk is not empty
                //cout << "testing while " << (stk.top()[0] != '(') << ' ' << stk.top()[0] << " >= " << tok[0] << endl;
                while (!stk.empty() && stk.top()[0] != '(' && precede(stk.top()[0]) >= precede(tok[0])) {                       //if the precidence of the symbole on the stack is greater than the new one the print it (continue)
                    //cout << "in operator while print operator" << endl;
                    //cout<< "STORE :" << stk.top() << endl;
                    post.push(stk.top());
                    //cout << "in operator while pop stk" << endl;
                    stk.pop();
                }
            }
            //cout << "push operator\t"<< "tok :"<< tok << endl;
            stk.push(tok);
            if(v.size() ==0){                                       //if last input read in is an operator it is an error
                //cout << "first catch\n";        //delete
                //cout << "ERROR: last input was an operator\n";
                post.clear();
                post.push("ERROR: last input was an operator");
                e = false;
                return post;
            }
        } else if (tok[0] == ')') {
            //cout << ") if statement \n" << post.top() << endl;
            if (post.top()[0] == '+' || post.top()[0] == '-' || post.top()[0] == '*' || post.top()[0] == '/') {
                //cout << "ERROR: <operator> ) ";
                post.clear();
                post.push("ERROR: <operator> ) ");
                e = false;
                return post;
            } else {
                while (stk.top()[0] != '(') {
                    //cout << ") while loop printo stk top" << endl;
                    //cout <<"STORE :" << stk.top() << endl;
                    post.push(stk.top());
                    stk.pop();
                }
            }
        }

        //cout <<"post at end of while :"<<post<<'\n';
    } /////////////////end of while

    //cout << "end of for loop" << endl;
    if(!stk.empty()) {
        while (!stk.empty() ) {
            //cout << "in last while loop " << endl;
            //cout << "content os stk: "<< stk<<'\n';
            //cout << "stk.top() :"<< stk.top() << endl;
            //cout << "post b4:" << *post << '\n';
            if(stk.top()[0] != '(')                             //prevent parentheis from being in stack
                post.push(stk.top());
            //cout << "STORE post after:"<< *post << '\n';
            stk.pop();
        }
        //cout << "\nend of last while loop\n";
    }
    //cout<<*post<<'\n';
    return post;
    //cout << "\nend of in2post()\n";

} //////////////////////end of in2post


double ansr(Stack<string>& stk){

    Stack<double> junk;
    junk.push(stod(stk.top()));
    stk.pop();
    junk.push(stod(stk.top()));
    stk.pop();

    while(!stk.empty()){
        if(!isTor(stk.top()[0])){           //if operand
            junk.push(stod(stk.top()));
        }
        else{
            double a =junk.top();
            junk.pop();
            double b =junk.top();
            junk.pop();
            if(stk.top() == "+")
                junk.push(a+b);
            else if(stk.top() == "+")
                junk.push(a-b);
            else if(stk.top() == "*")
                junk.push(a*b);
            else if (stk.top() == "/")
                junk.push(a / b);
        }
        stk.pop();
    }


    return junk.top();
}
bool isTor(char o){
    return o == '-' || o == '+' || o == '/' || o == '*' || o == '(' ||o == ')';

}
int precede(char p){
    if(p == '(' ||p == ')' )
        return 3;
    else if(p == '*' ||p == '/' )
        return 2;
    else if(p == '+' ||p == '-' )
        return 1;
    else                //error case
        return 0;
}
