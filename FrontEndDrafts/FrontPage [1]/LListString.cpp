#include "lliststring.h"
#include <cstdlib>
#include <stdexcept> // See the comment directly below.

//---------------------------------------------
//-------------CONSTRUCTORS--------------------
//---------------------------------------------
// Function: DEFAULT CONSTRUCTOR
// Purpose:
// Inputs:
// Returns: N/A
LListString::LListString()
{
  head_ = NULL;
  tail_ = NULL;
  size_ = 0;
}

// Function: COPY CONSTRUCTOR ****
// Purpose:
// Inputs:
// Returns:
 LListString::LListString (const LListString& other)
 {
 	this->size_ = other.size();
 	for (int i = 0; i < other.size(); i++) {
		this->insert(i, other.get(i));
	}
 }

// Function: DESTRUCTOR
// Purpose:
// Inputs:
// Returns: N/A
LListString::~LListString()
{
  clear();
}

//---------------------------------------------
//---------------OPERATORS---------------------
//---------------------------------------------

// Function: CONCATENATION OPERATOR
// Purpose:
// Inputs:
// Returns:
 LListString LListString::operator+ (const LListString& other) const
{

}

// Function: ACCESS OPERATOR
// Purpose:
// Inputs:
// Returns:
 std::string const & operator[] (int pos) const
{

}

// Function: ASSIGNMENT OPERATOR
// Purpose:
// Inputs:
// Returns:
 LListString & LListString::operator= (const LListString& other)
{
	clear();
	this->size_ = other.size();
	for (int i = 0; i < other.size(); i++) {
		this->insert(i, other.get(i));
	}
}

//---------------------------------------------
//---------------------------------------------
//---------------------------------------------

// Function: EMPTY
// Purpose:
// Inputs:
// Returns: N/A
bool LListString::empty() const
{
  return (size_ == 0);
}

// Function: SIZE
// Purpose:
// Inputs:
// Returns: N/A
int LListString::size() const
{
  return size_;
}

// Function: INSERT
// Purpose:
// Inputs: int pos
// Returns: N/A
void LListString::insert(int pos, const std::string& val)
{
  if (pos > size_ || pos < 0) {
    return;
  }

  else {
    Item * temp = NULL;

    // Empty List
    if (size_ == 0) {
      temp = new Item;
      temp->val = val;
      temp->prev = NULL;
      temp->next = NULL;
      head_ = temp;
      tail_ = temp;
    }

    // New Head
    else if (pos == 0) {
      temp = new Item;
      temp->val = val;
      head_->prev = temp;
      temp->prev = NULL;
      temp->next = head_;
      head_ = temp;
    }

    // New Tail
    else if (pos == size_) {
      temp = new Item;
      temp->val = val;
      tail_->next = temp;
      temp->prev = tail_;
      temp->next = NULL;
      tail_ = temp;
    }

    // Insert Middle
    else if (pos > 0 && pos < size_) {
      temp = new Item;
      temp->val = val;

      Item * temp2 = this->getNodeAt(pos-1);

      temp->prev = temp2;
      temp->next = temp2->next;
      (temp2->next)->prev = temp;
      temp2->next = temp;

      // this->getNodeAt(pos-1)->next = temp;
      // temp->prev = this->getNodeAt(pos-1);
      // this->getNodeAt(pos)->prev = temp;
      // temp->next = this->getNodeAt(pos);
    }
    size_++;
  }
}

// Function: REMOVE
// Purpose:
// Inputs: int pos
// Returns: N/A
void LListString::remove(int pos)
{
  if (pos < 0 || pos > size_ - 1) {
    return;
  }
  else {
    Item * temp = NULL;

    // Empty List
    if (size_ == 0) {
      return;
    }

    // Remove Head
    else if (pos == 0) {
      temp = this->getNodeAt(0);
      head_ = this->getNodeAt(1);

      // set prev to null
      delete temp;
    }

    // Remove Tail
    else if (pos = size_ - 1) {
      temp = this->getNodeAt(size_ - 1);
      tail_ = this->getNodeAt(size_ - 2);
      delete temp;
    }

    // Remove In Middle
    else if (pos > 0 && pos < size_ - 2) {

      // find only one node and use its prev
      Item * temp2 = this->getNodeAt(pos-1);
      temp = this->getNodeAt(pos);
      temp2->next = temp->next;
      (temp->next)->prev = temp2;

      // this->getNodeAt(pos-1)->next = this->getNodeAt(pos+1);
      // this->getNodeAt(pos+1)->prev = this->getNodeAt(pos-1);
      delete temp;
      temp2 = NULL;
    }
    size_ --;
  }
}

//---------------------------------------------
//----------------SETTERS----------------------
//---------------------------------------------

// Function: SET
// Purpose:
// Inputs:
// Returns:
void LListString::set(int pos, const std::string& val)
{
  if(pos >= 0 && pos < size_) {
  	Item *temp = getNodeAt(pos);
    temp->val = val;
  }
}

//---------------------------------------------
//----------------GETTERS----------------------
//---------------------------------------------

// Function: GET
// Purpose:
// Inputs:
// Returns:
std::string& LListString::get(int pos)
{
  if(pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(pos);
  return temp->val;
}

// Function: GET
// Purpose:
// Inputs:
// Returns:
std::string const & LListString::get(int pos) const
{
  if(pos < 0 || pos >= size_) {
    throw std::invalid_argument("bad location");
  }
  Item *temp = getNodeAt(pos);
  return temp->val;
}

// Function: GETNODEAT
// Purpose:
// Inputs: int pos
// Returns: item *
LListString::Item* LListString::getNodeAt(int pos) const
{
  // TODO: complete the getNodeAt function.
  if (head_ == NULL || pos >= size_) {
    return NULL;
  }
  else {
    Item * temp = head_;
    for (int i = 0; i < pos; i++) {
      temp = temp->next;
    }
    return temp;
  }
}

//---------------------------------------------
//-----------------CLEAR-----------------------
//---------------------------------------------

// Function: CLEAR
// Purpose:
// Inputs:
// Returns:
void LListString::clear()
{
  while(head_ != NULL) {
    Item *temp = head_->next;
    delete head_;
    head_ = temp;
  }
  tail_ = NULL;
  size_ = 0;
}
