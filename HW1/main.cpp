#include <iomanip>
#include <iostream>
#include <utility>
#include <vector>

#include "GroceryItem.hpp"

int main () {
    // A vector holding pointers of GroceryItem
    std::vector<GroceryItem*> shopping_cart;

    // fixed and setprecision(2) should output all floating point numbers with two numbers after the dot
    // Example: 23.43, 100.00, 434.99
    std::cout << std:: fixed << std::setprecision(2)
              << "Welcome to Kroger.  Place grocery items into your shopping cart by entering each item's information.\n"
              << "enclose string entries in quotes, separate fields with comas\n"
              << "for example:  \"00016000306707\", \"Betty Crocker\", \"Betty Crocker Double Chocolate Chunk Cookie Mix\", 17.1"
              << "Enter CTL-Z (Windows) or CTL-D (Linux) to quit\n";

    // Loop until the user 
    while (true) {
        std::cout << "Enter UPC, Product Brand, Product Name, and Price\n";
        GroceryItem item;
        // If the inputted parameters do not match our item, then we break from the loop
        if (!(std::cin >> item)) break;
        // Otherwise, we insert our locally created item as a new GroceryItem inside our shopping cart
        shopping_cart.push_back(new GroceryItem(std::move(item)));
        std::cout << "Item added to shopping cart: " << *shopping_cart.back() << '\n';
    }

    // crbegin will iterate in reverse. crend is the element before the first element
    std::cout << "Here is an itemized list of the items in your shopping cart:\n";
    for (auto i = shopping_cart.crbegin(); i < shopping_cart.crend(); i++) {
        std::cout << **i;
    }
    // Let's deallocate memory by deleting each of our items inside our shopping cart
    for (const auto item : shopping_cart) delete item;

    return 0;
}
