/**
 * @file Appetizer.cpp
 * @brief This file contains the implementation of the Appetizer class in a virtual bistro simulation.
 * 
 *The Appetizer class is a virtual bistro dish. It overides the virtual methods of the Dish class (display and make accomidations).
 * Implements other get and set methods for the Appetizer class.
 * 
 * @date [10/25/2024]
 * @author [Marcin Zarkowski]
 */

#include "Appetizer.hpp"
#include <set>
/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Appetizer::Appetizer()
    : Dish(), serving_style_(PLATED), spiciness_level_(0), vegetarian_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the appetizer.
 * @param ingredients The ingredients used in the appetizer.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the appetizer.
 * @param cuisine_type The cuisine type of the appetizer.
 * @param serving_style The serving style of the appetizer.
 * @param spiciness_level The spiciness level of the appetizer.
 * @param vegetarian Flag indicating if the appetizer is vegetarian.
 */
Appetizer::Appetizer(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const ServingStyle &serving_style, const int &spiciness_level, const bool &vegetarian)
    : Dish(name, ingredients, prep_time, price, cuisine_type), serving_style_(serving_style), spiciness_level_(spiciness_level), vegetarian_(vegetarian) {}

/**
 * Sets the serving style of the appetizer.
 * @param serving_style The new serving style.
 * @post Sets the private member `serving_style_` to the value of the parameter.
 */
void Appetizer::setServingStyle(const ServingStyle &serving_style) {
    serving_style_ = serving_style;
}

/**
 * @return The serving style of the appetizer.
 */
Appetizer::ServingStyle Appetizer::getServingStyle() const {
    return serving_style_;
}

/**
 * Sets the spiciness level of the appetizer.
 * @param spiciness_level An integer representing the spiciness level of the appetizer.
 * @post Sets the private member `spiciness_level_` to the value of the parameter.
 */
void Appetizer::setSpicinessLevel(const int &spiciness_level) {
    spiciness_level_ = spiciness_level;
}

/**
 * @return The spiciness level of the appetizer.
 */
int Appetizer::getSpicinessLevel() const {
    return spiciness_level_;
}

/**
 * Sets the vegetarian flag of the appetizer.
 * @param vegetarian A boolean indicating if the appetizer is vegetarian.
 * @post Sets the private member `vegetarian_` to the value of the parameter.
 */
void Appetizer::setVegetarian(const bool &vegetarian) {
    vegetarian_ = vegetarian;
}

/**
 * @return True if the appetizer is vegetarian, false otherwise.
 */
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}

/**
* Displays the appetizer's details.
* @post Outputs the appetizer's details, including name, ingredients,
preparation time, price, cuisine type, serving style, spiciness level, and
vegetarian status, to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients]
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Serving Style: [Serving style: Plated, Family Style, or Buffet]
* Spiciness Level: [Spiciness level]
* Vegetarian: [Yes/No]
*/

void Appetizer::display() const {
    std::cout << "Dish Name: " << getName() << "\n";

    //dont make a copy, just the original vector
    const auto& ingredients = getIngredients();
    std::cout << "Ingredients: ";

    //loop through ingredients and print them if it is not the last ingredient print a comma after it
    for (size_t i = 0; i < ingredients.size(); i++) {
        std::cout << ingredients[i];
        if (i != ingredients.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";  // Ensure a newline after the list
    

    std::cout << "Preparation Time: " << getPrepTime() << " minutes\n";
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << getPrice() << "\n";
    std::cout << "Cuisine Type: " << getCuisineType() << "\n";

    //switch statement to print the serving style
    switch (getServingStyle()) {
        case PLATED:
            std::cout << "Serving Style: Plated\n";
            break;
        case FAMILY_STYLE:
            std::cout << "Serving Style: Family Style\n";
            break; 
        case BUFFET:
            std::cout << "Serving Style: Buffet\n";
            break; 
    }

    std::cout << "Spiciness Level: " << getSpicinessLevel() << "\n";
    std::cout << "Vegetarian: " << (isVegetarian() ? "Yes" : "No") << "\n";  // Ternary operator for cleaner output
}

/**
* Modifies the appetizer based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the appetizer's attributes to meet the specified
MainCourse Class
dietary needs.
* - If `request.vegetarian` is true:
* - Sets `vegetarian_` to true.
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
* - If `request.low_sodium` is true:
* - Reduces `spiciness_level_` by 2 (minimum of 0).
* - If `request.gluten_free` is true:
* - Removes gluten-containing ingredients from
`ingredients_`.
* Gluten-containing ingredients are: "Wheat", "Flour",
"Bread", "Pasta", "Barley", "Rye", "Oats", "Crust".
*/

void Appetizer::dietaryAccommodations(Dish::DietaryRequest request) {
    std::set<std::string> meats = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
    std::set<std::string> gluten = {"Wheat", "Flour", "Bread", "Pasta", "Barley", "Rye", "Oats", "Crust"};
    std::vector<std::string> meat_sub = {"Beans", "Mushrooms"};

    std::vector<std::string> ingredients = getIngredients();

    size_t meat_counter = 0;

    if (request.vegetarian) {
        vegetarian_ = true;
    }

    size_t i = 0;
    if (request.vegetarian || request.gluten_free) {
        while (i < ingredients.size()) {
            bool removed = false;

            // Handle vegetarian replacements and removal
            if (request.vegetarian && meats.find(ingredients[i]) != meats.end()) {
                if (meat_counter < 2) {
                    ingredients[i] = meat_sub[meat_counter];
                    meat_counter++;
                } else {
                    ingredients.erase(ingredients.begin() + i); //remove ingredient and shift others down (keeps order intact since only first and second instances of meat should be changed to Beans and Mushrooms)                 
                    removed = true;
                }
            }

            // Handle gluten-free removal, only if not already removed
            if (!removed && request.gluten_free && gluten.find(ingredients[i]) != gluten.end()) {
                ingredients.erase(ingredients.begin() + i);//remove ingredient and shift others down (keeps order intact since only first and second instances of meat should be changed to Beans and Mushrooms)
                removed = true;
            }

            if (!removed) {
                i++;
            }
        }
    }

    setIngredients(ingredients);//set ingredients back to the new vector

    if (request.low_sodium) {
        spiciness_level_ = std::max(0, spiciness_level_ - 2);
    }
}