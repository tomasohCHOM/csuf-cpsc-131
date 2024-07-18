///////////////////////// TO-DO (1) //////////////////////////////
  /// Include necessary header files
  /// Hint:  Include what you use, use what you include
  ///
  /// Do not put anything else in this section, i.e. comments, classes, functions, etc.  Only #include directives
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>

#include "WordFrequency.hpp"
/////////////////////// END-TO-DO (1) ////////////////////////////







// unnamed, anonymous namespace providing non-member private working area
namespace
{
  std::string sanitize( const std::string & word )
  {
    constexpr char bad_char[] = " \t\n\b\v_-\"'(){}+/*,=.!?:;";            // leading and trailing characters to be removed
    static std::locale locality;

    auto startIndex = word.find_first_not_of( bad_char );                  // start with the first non-bad character
    if( startIndex == std::string::npos ) startIndex = word.size();        // if the word contains only bad characters ...

    std::size_t count    = 0;                                              // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );              // end with the first non-bad character

    if( endIndex != std::string::npos ) count = endIndex - startIndex + 1; // number of characters to use in results

    auto result = word.substr( startIndex, count );                        // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );              // convert to lower case

    return result;
  }
}  // unnamed, anonymous namespace







// Implement WordFrequency::WordFrequency( std::istream ) - See requirements
///////////////////////// TO-DO (2) //////////////////////////////
WordFrequency::WordFrequency( std::istream & iStream ) {
  std::string word;
  // keep reading words until end of file
  while (iStream >> word) {
    word = sanitize(word);
    // Increment the value (frequency) associated with the key (word) by one
    if (_wordOccurrence.find(word) != _wordOccurrence.end()) {
      ++_wordOccurrence[word];
    }
    // Otherwise, insert that word with a value of 1 in the hash table
    else {
      _wordOccurrence.insert({word, 1});
    }
  }
}
/////////////////////// END-TO-DO (2) ////////////////////////////







// Implement WordFrequency::numberOfWords() const - See requirements
///////////////////////// TO-DO (3) //////////////////////////////
std::size_t WordFrequency::numberOfWords() const {
  // return the size of _wordOccurrence to get the number of unique number of words
  // an unordered_map only holds unique keys, so all the words stored as keys in the map will be unique
  return _wordOccurrence.size();
}
/////////////////////// END-TO-DO (3) ////////////////////////////







// Implement WordFrequency::wordCount( const std::string & ) const - See requirements
///////////////////////// TO-DO (4) //////////////////////////////
std::size_t WordFrequency::wordCount( const std::string & word ) const {
  // if the word is not found as a key, then return 0
  auto foundKey = _wordOccurrence.find(sanitize(word));
  if (foundKey == _wordOccurrence.end()) return 0;
  // otherwise, return the value associated to the key (word)
  return foundKey->second;
}
/////////////////////// END-TO-DO (4) ////////////////////////////







// Implement WordFrequency::mostFrequentWord() const - See requirements
///////////////////////// TO-DO (5) //////////////////////////////
std::string WordFrequency::mostFrequentWord() const {
  // if the hash table is empty, return an empty string
  if (_wordOccurrence.empty()) return "";
  // initialize const_iterator and use its key as our current maximum
  auto itr = _wordOccurrence.cbegin();
  std::string maxFrequentWord = itr->first;
  // loop through the hash table
  while (itr != _wordOccurrence.cend()) {
    // if our pair's value is greater than our current maximum, update
    if (itr->second > _wordOccurrence.at(maxFrequentWord)) {
      maxFrequentWord = itr->first;
    }
    ++itr;
  }
  return maxFrequentWord;
}
/////////////////////// END-TO-DO (5) ////////////////////////////







// Implement WordFrequency::maxBucketSize() const - See requirements
///////////////////////// TO-DO (6) //////////////////////////////
/// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map
std::size_t WordFrequency::maxBucketSize() const {
  // initialize currentMax to 0
  std::size_t currentMax = 0;
  // visit each bucket (from 0 till bucket_count)
  for (std::size_t i = 0; i < _wordOccurrence.bucket_count(); ++i) {
    // if the bucket size is greater than the current maximum, then update the current maximum to that value
    if (_wordOccurrence.bucket_size(i) > currentMax) {
      currentMax = _wordOccurrence.bucket_size(i);
    }
  }
  return currentMax;
}
/////////////////////// END-TO-DO (6) ////////////////////////////
