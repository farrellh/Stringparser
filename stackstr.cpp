#include "stackstr.h"
#include "lliststr.h"

StackStr::StackStr()
{

}

StackStr::~StackStr()
{

}

bool StackStr::empty() const
{
  return list_.empty();

}

int StackStr::size() const
{
  return list_.size();

}

void StackStr::push(const std::string &str)
{
  list_.insert(list_.size(), str);
  return;

}

std::string StackStr::top() const
{
  return list_.get(list_.size()-1);

}

void StackStr::pop()
{
  list_.remove(list_.size()-1);
  return;

}