#ifndef EXPRE_H
#define EXPRE_H

#include<iostream>
#include<string>

//******exception*****

class NoValue{
  std::string variable;
  public:
    NoValue(std::string);
    std::string getvar();
};

//******Expression******

// Expression is the superclass
class Expression{
  public:
    virtual Expression * createnew() = 0;
    virtual std::string prettyprint() = 0;
    virtual void set(std::string, int) = 0;
    virtual void unset(std::string) = 0;
    virtual int evaluate() = 0;
    virtual ~Expression() = 0;
};

class LoneInteger:public Expression{
  int num;
  public:
    LoneInteger(int);//why do we need it
    Expression * createnew() override;
    std::string prettyprint() override;
    void set(std::string, int) override;
    void unset(std::string) override;
    int evaluate() override;
};


class Variable:public Expression{
  std::string var;
  int value;
  bool haveSet;
  public:
    Expression * createnew() override;
    Variable(std::string, int, bool);
    std::string prettyprint() override;
    void set(std::string, int) override;
    void unset(std::string) override;
    int evaluate() override;
};

class UnaryOperator:public Expression{
  std::string op;
  Expression *expr;
  public:
    Expression * createnew() override;
    UnaryOperator(std::string, Expression *);
    std::string prettyprint() override;
    void set(std::string, int) override;
    void unset(std::string) override;
    int evaluate() override;
    ~UnaryOperator();
};

class BinaryOperator:public Expression{
  std::string op;
  Expression *expr_1;
  Expression *expr_2;
  public:
    Expression * createnew() override;
    BinaryOperator(std::string, Expression *, Expression *);
    std::string prettyprint() override;
    void set(std::string, int) override;
    void unset(std::string) override;
    int evaluate() override;
    ~BinaryOperator();
};
#endif
