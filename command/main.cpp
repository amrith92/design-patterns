#include <iostream>

using namespace std;

struct CommandClient
{
   virtual void action() = 0;
};

struct Receiver : CommandClient
{
   void action()
   {
     cout << "Received." << endl;
   }
};

struct Command
{
  CommandClient *client;

  void attach(CommandClient *r)
  {
    this->client = r;
  }

  virtual void execute() = 0;
};

struct ConcreteCommand : Command
{
  virtual void execute()
  {
     cout << "ConcreteCommand executed." << endl;
     this->client->action();
  }
};

struct ReceiverInvoker
{
  ConcreteCommand cmd;

  ReceiverInvoker()
  {
    Receiver r;
    cmd.attach(&r);
  }

  void invoke()
  {
    cmd.execute();
  }
};

int main()
{
  ReceiverInvoker inv;

  inv.invoke();
  return 0;
}
