#include "lliststr.h"
#include <iostream>


LListStr::LListStr()
{
	head_ = NULL;
	tail_ = NULL;
	size_ = 0;
}

LListStr::~LListStr()
{
	Item *temp = head_;
	for(int i=0; i < size_; i++) { 
		temp = head_;
		head_ = head_ -> next;
		delete temp;
	}
}

// Returns the current number of items in the list

int LListStr::size() const
{
	return size_;

}

// Returns true if the list is empty, false otherwise

bool LListStr::empty() const
{
	return size_ == 0;
}

/*
 * Inserts val so it appears at the index given as pos. If the
 * index pos is invalid, this function should return without
 * modifying the list.
 */

void LListStr::insert(int pos, const std::string &val)
{
	
	// empty list

	if(empty() && pos==0 )
	{

		Item *temp = new Item();
		temp -> val = val;
		temp -> next = temp;
		temp -> prev = temp;

		size_ = 1;
		head_ = temp;
		tail_ = temp;

		return;
	}

	// out of bounds

	if(pos < 0 || pos > size_)
	{
		return;
	}

	// insert at beginning of list

	if (!empty() && pos == 0)
	{
		Item *temp = new Item();
		temp -> val = val;
		temp -> next = head_;
		temp -> prev = tail_;

		tail_ -> next = temp;
		head_ -> prev = temp;

		size_ = size_ + 1;
		head_ = temp;

		return;
	}

	// insert at end of list

	if(!empty() && pos == size_)
	{
		Item *temp = new Item();

		temp -> val = val;
		temp -> next = head_;
		tail_->next = temp;
		temp -> prev = tail_;

		size_ = size_ + 1; 
		tail_ = temp;


		return;
	}

	// insert anywhere inbetween list

	if(!empty() && pos != 0 && pos != size_)
	{

		Item *temp = new Item();

		temp -> val = val;

		Item* iter = head_;
		for (int i = 0; i < pos; i++)
		{
			iter = iter -> next;
		}

		Item* itersprev = iter->prev;
		itersprev->next = temp;
		temp->prev = itersprev;
		iter->prev = temp;
		temp->next = iter;

		size_ = size_ + 1;

		return;
	}
	

}

 /*
   * Removes the value at the index given by pos. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */

void LListStr::remove(int pos)
{

	// empty list

	if(empty())
	{
		return;
	}

	// out of bounds 

	if(pos < 0 || pos >= size_)
	{
		return;
	}

	// Create temp variable

	Item *temp = head_;

	// remove at beginning

	if(pos == 0)
	{
		head_ = head_ -> next;
		head_->prev = tail_;
		tail_->next = head_;
		size_ = size_ - 1;
	}

	// remove at end

	else if(pos == size_ - 1)
	{
		temp = tail_;
		tail_ = tail_ -> prev;
		tail_->next = head_;
		head_->prev = tail_;
		size_ = size_ - 1;
	}

	// remove anywhere inbetween

	else if(pos != 0 && pos != size_ - 1)
	{

		for (int i = 0; i < pos; i++)
		{
			temp = temp -> next;
		}

		temp -> prev -> next = temp -> next;
		temp -> next -> prev = temp -> prev;

		size_ = size_ - 1;

	} 
	delete temp;
	return;

}

 /*
   * Overwrites the old value at the index given by pos with val. If the
   * index pos is invalid, this function should return without
   * modifying the list.
   */

void LListStr::set(int pos, const std::string &val)
{
	// empty list

	if(empty())
	{
		return;
	}

	// out of bounds

	if(pos < 0 || pos >= size_)
	{
		return;
	}

	// not empty

	if(!empty() && pos >= 0 && pos <= size_ - 1)
	{
		Item* iter = head_;
		for (int i = 0; i < pos; i++)
		{
			iter = iter -> next;
		}

		iter -> val = val;

		return;
	}

}

 /*
   * Returns the value at the index given by pos. If the index pos is invalid,
   * then you should return the empty string.
   */

std::string LListStr::get(int pos) const
{
	// empty list

	if(empty())
	{
		return "";
	}

	// out of bounds

	if(pos < 0 || pos >= size_)
	{
		return "";
	}

	// not empty

	if(pos >= 0 && pos <= size_ - 1)
	{
		Item* iter = head_;
		for (int i = 0; i < pos; i++)
		{
			iter = iter -> next;
		}
		
		return iter -> val;
	}

	return "";

}
