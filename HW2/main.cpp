#include <exception>
#include <iostream>
#include <sstream>                                                                    // istringstream
#include <typeinfo>

#include "GroceryItem.hpp"
#include "GroceryList.hpp"




namespace
{
  void basicScenario()
  {
    // Let's start a grocery list
    GroceryList thingsToBuy = { { "milk"     },
                                { "hot dogs" },
                                { "eggs"     },
                                { "bread"    } };

    // Changed my mind, I want to make sure I can get eggs before running out of money so I'm going to move that to the top of my list
    thingsToBuy.moveToTop( { "eggs" } );

    // Let's see what's on the list so far
    std::cout << "My Grocery List" << thingsToBuy << "\n\n";



    // Hmm ..., no.  Need to add a few more things
    thingsToBuy += { { "bananas" },
                     { "apples"  } };




    // My roommate also has a grocery list
    GroceryList roommatesList = { { "potato chips", "Ruffles"    },
                                  { "potato chips", "Frito Lays" },
                                  { "beer",         "Bud Lite"   },
                                  { "eggs"                       },
                                  { "pretzels"                   } };

    std::cout << "My roommate's Grocery List" << roommatesList << "\n\n";

    // Let's combine the lists (if different) and go shopping
    if( thingsToBuy != roommatesList ) thingsToBuy += roommatesList;


    // Oops, forgot butter.  Let's add that right before bread.
    thingsToBuy.insert( { "butter", "Lakes 'Ole" }, thingsToBuy.find( { "bread" } ) );

    // And beer, really?  You should be studying!
    thingsToBuy.remove( { "beer", "Bud Lite" } );



    // Now let's see what's on the list
    std::cout << "Combined Grocery Lists" << thingsToBuy << "\n\n";



    // Did you get it right?
    //
    // I could construct "expectedResults" with the list of grocery items as above, but I want to exercise GroceryList's extraction
    // operator.  To do that, I could:
    //   1) read the list of grocery items from standard input and type the data at the keyboard, but that is time consuming and
    //      error prone.  That's easily handled by creating a text file with grocery item data then redirecting that text file to
    //      standard input at the command line when launching the program.  But then I would have to separately maintain that file
    //      and include it in the set of student files.  More importantly, that would prevent you from doing that in the TO-DO
    //      section below.
    //   2) open a text file directly using either command line arguments that supply the file's path and name, or hard coding the
    //      file's path and name.  But that would require using (and understanding) the standard's ifstream interface, which is easy
    //      enough given sufficient time, but I don't want to go down that rabbit hole in this course.
    //   3) create an in-memory text file (well, more accurately, an in-memory input stream) and read from there.  This allows me to
    //      exercise the extraction operator while avoiding the perils described in options 1) and 2) above.
    // So, as a design decision, let's chose option 3), create an in-memory input stream and read from there.
    //
    //                                            UPC | Brand Name   | Product Name   | Price
    //                                            ----+--------------+----------------+--------
    std::istringstream expectedResultsStream( R"( "",   "",            "eggs",          0.0
                                                  "",   "",            "milk",          0.0
                                                  "",   "",            "hot dogs",      0.0
                                                  "",   "Lakes 'Ole",  "butter",        0.0
                                                  "",   "",            "bread",         0.0
                                                  "",   "",            "bananas",       0.0
                                                  "",   "",            "apples",        0.0
                                                  "",   "Ruffles",     "potato chips",  0.0
                                                  "",   "Frito Lays",  "potato chips",  0.0
                                                  "",   "",            "pretzels",      0.0 )"   // multi-line raw string literal of grocery items
                                               );

    GroceryList expectedResults;
    expectedResultsStream >> expectedResults;

    std::cout << "\nExpected results:" << expectedResults << "\n\n"
              << "\nActual results:  " << thingsToBuy     << "\n\n"
              << "\nTest results:    " << ( thingsToBuy == expectedResults ? "PASS" : "FAIL" ) << '\n';
  }
}




int main()
{
  try
  {
    basicScenario();


    ///////////////////////// TO-DO (1) //////////////////////////////
     /// Create, manipulate, and display your own GroceryList object here.  Not looking for anything specific but don't just repeat
     /// what I've already done above.  Be imaginative and create your own story.  Maybe you're restocking a depleted food bank, or
     /// preparing for a holiday meal, or catering a banquette, or planning an all night study session, or ...  You *must* use all
     /// the functions of the GroceryList interface, including the insertion, extraction, and relational operators.  Try inserting
     /// grocery items from both the top and the bottom of the lists using the enumerated position values TOP and BOTTOM as well as
     /// indexed offsets.  Remove grocery items from the top, middle, and bottom.  Create, concatenate, rearrange, and compare
     /// several (more than two) lists. Have some fun with it!  The purpose is to show me you, as a GroceryList class consumer
     /// (i.e., the client) understand how to *use* the GroceryList.



    std::cout << "My extended family is coming home, and I need to greet them with an awesome meal. I am thinking of preparing "
              << "an Argentinian-style barbecue, so I naturally need to buy meat. Of course, I need some side dishes and sauces "
              << "as well, so I take those into consideration.\n";

    // Let's create my grocery list of ingredients. I will get some beef to barbecue and vegetables to make a salad.
    GroceryList ingredientsForDinner = {{"rib-eye steak", "Wild Fork"},
                                        {"lettuce"},
                                        {"short ribs", "Wild Fork"},
                                        {"tomatoes"}};

    // I think short ribs are the most important part of this meal, so I will move it to the top.
    ingredientsForDinner.moveToTop({"short ribs"});
    std::cout << "My Grocery List for Dinner:" << ingredientsForDinner << "\n\n";

    std::cout << "I definitely need more stuff for this meal. I'm thinking of combining this Argentinian barbecue with some "
              << "Korean side dishes. Kimchi pancakes will go well with the meat. I ran out of kimchi at home, so I will grab some along "
              << "with additional ingredients.\n";
    ingredientsForDinner += {{"kimchi"}, {"spring onion"}, {"carrots"}, {"spinach"}};

    std::cout << "Let's see what we got so far.\n";
    std::cout << "\nMy Grocery List for Dinner:" << ingredientsForDinner << "\n\n";
    std::cout << "Current size of List: " << ingredientsForDinner.size() << "\n\n";

    std::cout << "My mom went shopping with me as well. I want to combine both of our lists into mine if they are not equal.\n";
    GroceryList momsList = {{"lettuce"}, {"carrots"}, {"potatoes"}, {"olive oil"}, {"parsley"}, {"kimchi"}};
    std::cout << "Mom's Grocery List for Dinner:" << momsList << "\n\n";

    if (!(ingredientsForDinner == momsList)) {
      ingredientsForDinner += momsList;
    }

    // Both of our lists combined into one.
    std::cout << "Combined Grocery List for Dinner:" << ingredientsForDinner << "\n\n";

    std::cout << "Is the size of my list full now? Do I have 11 items already? Let me check.\n";
    std::cout << "Current size of List: " << ingredientsForDinner.size() << "\n\n";
    
    // Yep... Let me remove some things then. I will remove the item at the bottom of my list, as well as the item
    // at index 5. I will also move "potatoes" to the top and remove them as well. Guess no mashed potatoes today...

    ingredientsForDinner.remove(ingredientsForDinner.size() - 1); // Remove the item at the bottom.

    ingredientsForDinner.remove(5); // Remove the item at index 5.

    ingredientsForDinner.moveToTop({"potatoes"}); // Move potatoes to the top and remove it.
    ingredientsForDinner.remove(0);

    std::cout << "My Grocery List after removing some items:" << ingredientsForDinner << "\n\n";

    // My young sister has an empty list, so I told her to get three items that I DON'T have already.
    GroceryList sistersList;
    sistersList.insert({"Hot cheetos", "Cheetos"}, 0);
    sistersList.insert({"chocolate", "Hershey's"}, GroceryList::Position::BOTTOM);
    sistersList.insert({"Cinnamon Toast Crunch", "General Mills"}, GroceryList::Position::TOP); // She really likes her cereal

    // Not the most useful list for dinner, I think I will have to discard her items.
    std::cout << "Sister's Grocery List:" << sistersList << "\n\n";

    // I want the user to input some final items.
    GroceryList inputList;
    std::cout << "Give me a three-item grocery list that I could use for dinner (in the order of UPC code, brand name, "
              << "product name, and the price - strings are enclosed with quotes and fields are separated by commas).\n";
    std::cin >> inputList;
    std::cout << "Your inputted Grocery List:" << inputList << "\n\n";

    // I will check that the inputted list is less than or equal to 3, so that it fits in my grocery list.
    if (inputList.size() <= 3) {
      // I will do a three-way comparison of my list with the inputted list. If they are not equal, I will append
      // that list to the mine.
      if (auto result = ingredientsForDinner <=> inputList; result != 0) {
        ingredientsForDinner += inputList;
      }
    } else {
      std::cout << "Oops! Your items will not fit in my Grocery List due to capacity.\n\n";
    }

    // Finally! The List of ingredients is done and we can start 
    std::cout << "Final Grocery List for Dinner:" << ingredientsForDinner << "\n\n";
    /////////////////////// END-TO-DO (1) ////////////////////////////
  }

  catch( const std::exception & ex )
  {
    std::cerr << "Fatal Error:  unhanded exception \"" << typeid( ex ).name() << "\"\n"
              << ex.what() << '\n';
  }
}
