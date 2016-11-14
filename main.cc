#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <vector>
#include"Expression.h"

using namespace std;

// This program can read and evaluate arithmetic expressions
int main () {
  string s;
  // We organize Expressions using stack
  vector<Expression *> stack;
  int pos = 0;
  // Read and construct expression
  while (cin >> s) {
    istringstream ss(s);
    int n;
    if (ss >> n) {
      stack.emplace_back(new LoneInteger{n});
      ++pos;
    }
    else if (s == "NEG" || s == "ABS") {
      Expression *expr = stack[pos - 1];
      stack.pop_back();
      stack.emplace_back(new UnaryOperator{s, expr});
    }
    else if (s == "+" || s == "-" || s == "*" || s == "/") {
      Expression *expr_1 = stack[pos - 2];
      Expression *expr_2 = stack[pos - 1];
      stack.pop_back();
      stack.pop_back();
      stack.emplace_back(new BinaryOperator{s, expr_1, expr_2});
      --pos;
    }
    else if (s == "done") {
      cout << stack[0]->prettyprint() << endl;
      break;
    }
    else {
      stack.emplace_back(new Variable{s, 0, false});
      ++pos;
    }
  }
  Expression *expr = stack[0];
  // Command interpreter
  while (cin >> s) {
    if (s == "eval") {
      // Here may have an exception when the variable has no value
      try{
        cout << expr->evaluate() << endl;
      }
      catch(NoValue &excep){
        cout << excep.getvar() << " has no value." << endl;
      }
    }
    else if (s == "set") {
      string varname;
      int varvalue;
      cin >> varname;
      if(cin >> varvalue){
        expr->set(varname, varvalue);
      } else {
        return 1;
      }
    }
    else if (s == "unset") {
      string varname;
      cin >> varname;
      expr->unset(varname);
    }
    else if (s == "print") {
      cout << expr->prettyprint() << endl;
    }// q2
    else if (s == "copy"){
      Expression *theCopy = expr->createnew();
      cout << theCopy->prettyprint() << endl;
      theCopy->set("x", 1);
      cout << theCopy->prettyprint() << endl;
      try{
        cout << theCopy->evaluate() << endl;
      }
      catch(NoValue &excep){
        cout << excep.getvar() << " has no value." << endl;
      }
      delete theCopy;
    }
  }
  delete stack[0];
}
