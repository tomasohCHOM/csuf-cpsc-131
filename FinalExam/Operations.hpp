#pragma once
#include <algorithm>
#include <forward_list>
#include <list>
#include <map>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "SomeObject.hpp"









/***********************************************************************************************************************************
**  Insert operations
***********************************************************************************************************************************/
struct insert_at_back_of_vector
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the back of a vector, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (1) //////////////////////////////
      /// Write the lines of code to insert "object" at the back of "my_vector"
    my_vector.push_back(object);
    /////////////////////// END-TO-DO (1) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
};









struct insert_at_back_of_dll
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the back of a doubly linked list, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (2) //////////////////////////////
      /// Write the lines of code to insert "object" at the back of "my_dll"
    my_dll.push_back(object);
    /////////////////////// END-TO-DO (2) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
};









struct insert_at_back_of_sll
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the back of a singly linked list, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (3) //////////////////////////////
      /// Write the lines of code to insert "object" at the back of "my_sll". Since the SLL has no size() function and no tail pointer, you
      /// must walk the list looking for the last node. Hint:  Do not attempt to insert after "my_sll.end()"
    my_sll.insert_after(std::next(my_sll.before_begin(), std::distance(my_sll.begin(), my_sll.end())), object);
    /////////////////////// END-TO-DO (3) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
};









struct insert_at_front_of_vector
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the front of a vector, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (4) //////////////////////////////
      /// Write the lines of code to insert "object" at the front of "my_vector"
    my_vector.insert(my_vector.begin(), object);
    /////////////////////// END-TO-DO (4) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
};









struct insert_at_front_of_dll
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the front of a doubly linked list, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (5) //////////////////////////////
      /// Write the lines of code to insert "object" at the front of "my_dll"
    my_dll.push_front(object);
    /////////////////////// END-TO-DO (5) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
};









struct insert_at_front_of_sll
{
  // Function takes a constant SomeObject as a parameter, inserts that object at the front of a singly linked list, and returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (6) //////////////////////////////
      /// Write the lines of code to insert "object" at the front of "my_sll"
    my_sll.push_front(object);
    /////////////////////// END-TO-DO (6) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
};









struct insert_into_bst
{
  // Function takes a constant SomeObject as a parameter, inserts that object indexed by the object's key into a binary search tree, and
  // returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (7) //////////////////////////////
      /// Write the lines of code to insert the object's key and value pair into "my_bst". To obtain the object's key, determine
      /// SomeObject's base type and review your prior homework class interface. For example, if SomeObject's base type is a
      /// HotelReservation, you might obtain the reservation's key with object.reservationNumber().
    my_bst.insert({object.key(), object});
    /////////////////////// END-TO-DO (7) ////////////////////////////
  }

  std::map<std::string, SomeObject> & my_bst;                                                                     // binary search tree
};









struct insert_into_hash_table
{
  // Function takes a constant SomeObject as a parameter, inserts that object indexed by the object's key into a hash table, and returns
  // nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (8) //////////////////////////////
      /// Write the lines of code to insert the object's key and value pair into "my_hash_table". To obtain the object's key, determine
      /// SomeObject's base type and review your prior homework class interface. For example, if SomeObject's base type is a
      /// HotelReservation, you might obtain the reservation's key with object.reservationNumber().
    my_hash_table.insert({object.key(), object});
    /////////////////////// END-TO-DO (8) ////////////////////////////
  }

  std::unordered_map<std::string, SomeObject> & my_hash_table;                                                    // hash table
};


















/***********************************************************************************************************************************
**  Remove operations
***********************************************************************************************************************************/
struct remove_from_back_of_vector
{
  // Function takes no parameters, removes the object at the back of a vector, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (9) //////////////////////////////
      /// Write the lines of code to remove the object at the back of "my_vector". Remember, attempting to remove an object from an empty
      /// data structure is a logic error.  Include code to avoid that.
    if (my_vector.empty()) return;
    my_vector.pop_back();
    /////////////////////// END-TO-DO (9) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
};









struct remove_from_back_of_dll
{
  // Function takes no parameters, removes the object at the back of a doubly linked list, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (10) //////////////////////////////
      /// Write the lines of code to remove the object at the back of "my_dll". Remember, attempting to remove an object from an empty data
      /// structure is a logic error.  Include code to avoid that.
    if (my_dll.empty()) return;
    my_dll.pop_back();
    /////////////////////// END-TO-DO (10) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
};









struct remove_from_back_of_sll
{
  // Function takes no parameters, removes the object at the back of a singly linked list, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (11) //////////////////////////////
      /// Write the lines of code to remove the object at the back of "my_sll". Remember, attempting to remove an object from an empty data
      /// structure is a logic error.  Include code to avoid that.
    if (my_sll.empty()) return;
    my_sll.erase_after(std::next(my_sll.before_begin(), std::distance(++my_sll.begin(), my_sll.end())));
    /////////////////////// END-TO-DO (11) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
};









struct remove_from_front_of_vector
{
  // Function takes no parameters, removes the object at the front of a vector, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (12) //////////////////////////////
      /// Write the lines of code to remove the object at the front of "my_vector". Remember, attempting to remove an object from an empty
      /// data structure is a logic error.  Include code to avoid that.
    if (my_vector.empty()) return;
    my_vector.erase(my_vector.begin());
    /////////////////////// END-TO-DO (12) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
};









struct remove_from_front_of_dll
{
  // Function takes no parameters, removes the object at the front of a doubly linked list, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (13) //////////////////////////////
      /// Write the lines of code to remove the object at the front of "my_dll". Remember, attempting to remove an object from an empty data
      /// structure is a logic error.  Include code to avoid that.
    if (my_dll.empty()) return;
    my_dll.pop_front();
    /////////////////////// END-TO-DO (13) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
};









struct remove_from_front_of_sll
{
  // Function takes no parameters, removes the object at the front of a singly linked list, and returns nothing.
  void operator()( const auto & )
  {
    ///////////////////////// TO-DO (14) //////////////////////////////
      /// Write the lines of code to remove the object at the front of "my_sll". Remember, attempting to remove an object from an empty data
      /// structure is a logic error.  Include code to avoid that.
    if (my_sll.empty()) return;
    my_sll.pop_front();
    /////////////////////// END-TO-DO (14) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
};









struct remove_from_bst
{
  // Function takes a constant SomeObject as a parameter, finds and removes from the binary search tree the object with a matching key, and
  // returns nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (15) //////////////////////////////
      /// Write the lines of code to remove the object from "my_bst" that has a matching key. Remember, attempting to remove an object from
      /// an empty data structure is a logic error.  Include code to avoid that.
    if (my_bst.empty()) return;
    my_bst.erase(std::move(object.key()));
    /////////////////////// END-TO-DO (15) ////////////////////////////
  }

  std::map<std::string, SomeObject> & my_bst;                                                                     // binary search tree
};









struct remove_from_hash_table
{
  // Function takes a constant SomeObject as a parameter, finds and removes from the hash table the object with a matching key, and returns
  // nothing.
  void operator()( const SomeObject & object )
  {
    ///////////////////////// TO-DO (16) //////////////////////////////
      /// Write the lines of code to remove the object from "my_hash_table" that has a matching key. Remember, attempting to remove an
      /// object from an empty data structure is a logic error.  Include code to avoid that.
    if (my_hash_table.empty()) return;
    my_hash_table.erase(std::move(object.key()));
    /////////////////////// END-TO-DO (16) ////////////////////////////
  }

  std::unordered_map<std::string, SomeObject> & my_hash_table;                                                    // hash table
};















/***********************************************************************************************************************************
**  Search operations
***********************************************************************************************************************************/
struct search_within_vector
{
  // Function takes no parameters, searches a vector for an object with a key matching the target key, and returns a pointer to that found
  // object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (17) //////////////////////////////
      /// Write the lines of code to search for the object within "my_vector" with a key matching "target_key".  Return a pointer to that
      /// object immediately upon finding it, or a null pointer when you know the object is not in the container.
    auto itr = my_vector.begin();
    while (itr != my_vector.end()) {
      if (itr->key() == target_key) return &*itr;
      ++itr;
    }
    return nullptr;
    /////////////////////// END-TO-DO (17) ////////////////////////////
  }

  std::vector<SomeObject> & my_vector;                                                                            // extendable vector
  const std::string         target_key;
};









struct search_within_dll
{
  // Function takes no parameters, searches a doubly linked list for an object with a key matching the target key, and returns a pointer to
  // that found object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (18) //////////////////////////////
      /// Write the lines of code to search for the object within "my_dll" with a key matching "target_key".  Return a pointer to that
      /// object immediately upon finding it, or a null pointer when you know the object is not in the container.
    auto itr = my_dll.begin();
    while (itr != my_dll.end()) {
      if (itr->key() == target_key) return &*itr;
      ++itr;
    }
    return nullptr;
    /////////////////////// END-TO-DO (18) ////////////////////////////
  }

  std::list<SomeObject> & my_dll;                                                                                 // doubly linked list
  const std::string       target_key;
};









struct search_within_sll
{
  // Function takes no parameters, searches a singly linked list for an object with a key matching the target key, and returns a pointer to
  // that found object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (19) //////////////////////////////
      /// Write the lines of code to search for the object within "my_sll" with a key matching "target_key".  Return a pointer to that
      /// object immediately upon finding it, or a null pointer when you know the object is not in the container.
    auto itr = my_sll.begin();
    while (itr != my_sll.end()) {
      if (itr->key() == target_key) return &*itr;
      ++itr;
    }
    return nullptr;
    /////////////////////// END-TO-DO (19) ////////////////////////////
  }

  std::forward_list<SomeObject> & my_sll;                                                                         // singly linked list
  const std::string               target_key;
};









struct search_within_bst
{
  // Function takes no parameters, searches a binary search tree for an object with a key matching the target key, and returns a pointer to
  // that found object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (20) //////////////////////////////
      /// Write the lines of code to search for the object within "my_bst" with a key matching "target_key".  Return a pointer to that
      /// object immediately upon finding it, or a null pointer when you know the object is not in the container.
    auto pair = my_bst.find(std::move(target_key));
    if (pair == my_bst.end()) return nullptr;
    return &pair->second;
    /////////////////////// END-TO-DO (20) ////////////////////////////
  }

  std::map<std::string, SomeObject> & my_bst;                                                                     // binary search tree
  const std::string                   target_key;
};









struct search_within_hash_table
{
  // Function takes no parameters, searches a hash table for an object with a key matching the target key, and returns a pointer to that
  // found object if such an object is found, nullptr otherwise.
  SomeObject * operator()( const auto & )
  {
    ///////////////////////// TO-DO (21) //////////////////////////////
      /// Write the lines of code to search for the object within "my_hash_table" with a key matching "target_key".  Return a pointer to
      /// that object immediately upon finding it, or a null pointer when you know the object is not in the container.
    auto pair = my_hash_table.find(std::move(target_key));
    if (pair == my_hash_table.end()) return nullptr;
    return &pair->second;
    /////////////////////// END-TO-DO (21) ////////////////////////////
  }

  std::unordered_map<std::string, SomeObject> & my_hash_table;                                                    // hash table
  const std::string                             target_key;
};
