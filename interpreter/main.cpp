#include <iostream>
#include <string>

using namespace std;

struct Context
{
  enum Ctx {
   SkipWS, AckWS
  } flag;

  string data;
  int i;

  Context() : i(0) {}
};

struct AbstractExpression
{
  virtual void interpret(Context ctx) = 0;
};

struct TerminalExpression : AbstractExpression
{
  void interpret(Context ctx)
  {
    if (ctx.data[ctx.i] != ' ' && ctx.data[ctx.i] != '\n') {
      cout << "Terminal: '" << ctx.data[ctx.i] << "'" << endl;
    }

    if ((ctx.data[ctx.i] == ' ' || ctx.data[ctx.i] == '\n') && ctx.flag != Context::SkipWS) {
      cout << "Terminal: '" << ctx.data[ctx.i] << "'" << endl;
    }
  }
};

struct NonterminalExpression : AbstractExpression
{
  void interpret(Context ctx)
  {
    if (ctx.data[ctx.i] == '\0') {
      cout << "END" << endl;
    } else {
      TerminalExpression exp;
      exp.interpret(ctx);
      ++ctx.i;
      this->interpret(ctx);
    }
  }
};

int main()
{
  Context c;
  c.flag = Context::AckWS;
  c.data = "Bl  ah!\0";

  NonterminalExpression exp;

  exp.interpret(c);

  return 0;
}
