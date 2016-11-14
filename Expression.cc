#include<iostream>
#include<string>
#include<utility>
#include<sstream>
#include<stdexcept>
#include"Expression.h"

using namespace std;


//*************Exception**************
string NoValue::getvar(){
  return variable;
}

NoValue::NoValue(string v): variable{v} {}

//*************Expression**************

Expression::~Expression(){}


//*************LoneInterger*************

Expression * LoneInteger::createnew(){
  Expression *ptr = new LoneInteger{num};
  return ptr;
}

LoneInteger::LoneInteger(int n):
  num{n} {}

std::string LoneInteger::prettyprint(){
  ostringstream ss;
  ss << num;
  return ss.str();
}

void LoneInteger::set(std::string v, int newvalue) {
  return;
}

void LoneInteger::unset(std::string v){
  return;
}

int LoneInteger::evaluate() {
  return num;
}


//************Variable******************
Expression * Variable::createnew(){
  Expression *ptr = new Variable{var, value, haveSet};
  return ptr;
}

Variable::Variable(string v, int newvalue, bool checkset = false):
  var{v}, value{newvalue}, haveSet{checkset}{}

std::string Variable::prettyprint() {
  if(haveSet){
    ostringstream ss;
    ss << value;
    return ss.str();
  } else {
    return var;
  }
}

void Variable::set(std::string v, int newvalue){
  if(var == v){
    value = newvalue;
    haveSet = true;
  } else {
    return;
  }
}

void Variable::unset(std::string v){
  if(var == v){
    haveSet = false;
    value = 0;
  } else {
    return;
  }
}

int Variable::evaluate(){
  if(haveSet){
    return value;
  } else {
    throw NoValue{var};
  }
}


//***************UnaryOperator***************
Expression * UnaryOperator::createnew(){
  Expression *ptr = new UnaryOperator{op, expr->createnew()};
  return ptr;
}

UnaryOperator::UnaryOperator(string sign, Expression * ex):
  op{sign}, expr{ex} {}

std::string UnaryOperator::prettyprint(){
  ostringstream ss;
  if(op == "ABS"){
    ss << '|' << expr->prettyprint() << '|';
  } else {
    ss << '-' << expr->prettyprint();
  }
  return ss.str();
}

void UnaryOperator::set(std::string v, int newvalue) {
  expr->set(v, newvalue);
  return;
}

void UnaryOperator::unset(std::string v){
  expr->unset(v);
  return;
}

int UnaryOperator::evaluate() {
  int pre_result = expr->evaluate();
  if(op == "ABS"){
    if(pre_result < 0){
      pre_result = -pre_result;
    }
    return pre_result;
  } else {
    pre_result = - pre_result;
    return pre_result;
  }
}


UnaryOperator::~UnaryOperator(){
  delete expr;
}


//*************BinaryOperator************

Expression * BinaryOperator::createnew(){
  Expression *ptr = new
    BinaryOperator{op, expr_1->createnew(), expr_2->createnew()};
  return ptr;
}


BinaryOperator::BinaryOperator(string sign, Expression * ex_1, Expression * ex_2):
  op{sign}, expr_1{ex_1}, expr_2{ex_2} {}

std::string BinaryOperator::prettyprint() {
  ostringstream ss;
  ss << '(';
  ss << expr_1->prettyprint();
  ss << ' ' << op << ' ';
  ss << expr_2->prettyprint();
  ss << ')';
  return ss.str();
}

void BinaryOperator::set(std::string v, int newvalue) {
  expr_1->set(v, newvalue);
  expr_2->set(v, newvalue);
  return;
}

void BinaryOperator::unset(std::string v) {
  expr_1->unset(v);
  expr_2->unset(v);
  return;
}

int BinaryOperator::evaluate() {
  int eval_1 = expr_1->evaluate();
  int eval_2 = expr_2->evaluate();
  if(op == "+"){
    return eval_1 + eval_2;
  } else if(op == "-"){
    return eval_1 - eval_2;
  } else if(op == "*"){
    return eval_1 * eval_2;
  } else {
    return eval_1 / eval_2;
  }
}


BinaryOperator::~BinaryOperator(){
  delete expr_1;
  delete expr_2;
}
