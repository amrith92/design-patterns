#include <iostream>
#include <vector>

using namespace std;

struct Iterator
{
  const int firstItem()
  {
    return data.front();
  }

  const int nextItem()
  {
    ++it;
    return *it;
  }

  bool isDone()
  {
    return (data.end() == it);
  }

  const int currentItem()
  {
    return *it;
  }

protected:
  vector<int> data;
  vector<int>::iterator it;
};

struct ConcreteIterator : Iterator
{
  ConcreteIterator(int collection[])
  {
    data = vector<int>(collection, collection + sizeof(collection)/sizeof(int));
    it = data.begin();
  }
};

struct Aggregate
{
  virtual Iterator *createIterator() = 0;

protected:
  int data[10], idx;
};

struct ConcreteAggregate : Aggregate
{
  ConcreteAggregate() {
    idx = 0;
  }

  virtual Iterator *createIterator()
  {
    return new ConcreteIterator(data);
  }

  void add(int n)
  {
    data[idx] = n;
    ++idx;
  }
};

int main()
{
  ConcreteAggregate agg;
  agg.add(5);
  agg.add(6);

  int i;
  Iterator *it = agg.createIterator();
  cout << "ITEM: " << it->currentItem() << endl;
  while ((i = it->nextItem())) {
    cout << "ITEM: " << i << endl;
  }

  delete it;

  return 0;
}
