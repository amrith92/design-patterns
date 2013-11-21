#include <iostream>
#include <vector>

using namespace std;

struct CommandHandler
{
  enum EventType {
    Click, Hover
  };

  virtual void handleRequest(EventType event) = 0;
};

struct ConcreteHandler1 : CommandHandler
{
  virtual void handleRequest(EventType event)
  {
    if (event == Click) {
      std::cout << "Handler 1 fired." << endl;
    }
  }
};

struct ConcreteHandler2 : CommandHandler
{
  virtual void handleRequest(EventType event)
  {
    if (event == Hover) {
      std::cout << "Handler 2 fired." << endl;
    }
  }
};

struct Client
{
  vector<CommandHandler *> handlers;

  void add(CommandHandler *handler)
  {
    handlers.push_back(handler);
  }

  void run(CommandHandler::EventType event)
  {
    vector<CommandHandler *>::const_iterator it;

    for (it = handlers.begin(); it != handlers.end(); ++it) {
      (*it)->handleRequest(event);
    }
  }
};

int main()
{
  ConcreteHandler1 one, two, three;
  ConcreteHandler2 four, five;

  Client c;
  c.add(&one);
  c.add(&two);
  c.add(&five);
  c.add(&four);
  c.add(&three);

  c.run(CommandHandler::Click);
  c.run(CommandHandler::Hover);

  return 0;
}
