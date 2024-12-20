/**
 * @file Dessert.cpp
 * @brief This file contains the implementation of the Dessert class in a virtual bistro simulation.
 * 
 *The Dessert class is a virtual bistro dish. It overides the virtual methods of the Dish class (display and make accomidations).
 * Implements other get and set methods for the Dessert class.
 * 
 * @date [10/25/2024]
 * @author [Marcin Zarkowski]
 */

#include "Dessert.hpp"
#include <set>
#include <iostream>
#include <iomanip>  
#include <vector>   
#include <string>   
/**
 * Default constructor.
 * Initializes all private members with default values.
 */
Dessert::Dessert()
    : Dish(), flavor_profile_(SWEET), sweetness_level_(0), contains_nuts_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the dessert.
 * @param ingredients The ingredients used in the dessert.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the dessert.
 * @param cuisine_type The cuisine type of the dessert.
 * @param flavor_profile The flavor profile of the dessert.
 * @param sweetness_level The sweetness level of the dessert.
 * @param contains_nuts Flag indicating if the dessert contains nuts.
 */
Dessert::Dessert(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const FlavorProfile &flavor_profile, const int &sweetness_level, const bool &contains_nuts)
    : Dish(name, ingredients, prep_time, price, cuisine_type), flavor_profile_(flavor_profile), sweetness_level_(sweetness_level), contains_nuts_(contains_nuts) {}

/**
 * Sets the flavor profile of the dessert.
 * @param flavor_profile The new flavor profile.
 * @post Sets the private member `flavor_profile_` to the value of the parameter.
 */
void Dessert::setFlavorProfile(const FlavorProfile &flavor_profile) {
    flavor_profile_ = flavor_profile;
}

/**
 * @return The flavor profile of the dessert.
 */
Dessert::FlavorProfile Dessert::getFlavorProfile() const {
    return flavor_profile_;
}

/**
 * Sets the sweetness level of the dessert.
 * @param sweetness_level An integer representing the sweetness level of the dessert.
 * @post Sets the private member `sweetness_level_` to the value of the parameter.
 */
void Dessert::setSweetnessLevel(const int &sweetness_level) {
    sweetness_level_ = sweetness_level;
}

/**
 * @return The sweetness level of the dessert.
 */
int Dessert::getSweetnessLevel() const {
    return sweetness_level_;
}

/**
 * Sets the contains_nuts flag of the dessert.
 * @param contains_nuts A boolean indicating if the dessert contains nuts.
 * @post Sets the private member `contains_nuts_` to the value of the parameter.
 */
void Dessert::setContainsNuts(const bool &contains_nuts) {
    contains_nuts_ = contains_nuts;
}

/**
 * @return True if the dessert contains nuts, false otherwise.
 */
bool Dessert::containsNuts() const {
    return contains_nuts_;
}

/**
* Displays the dessert's details.
* @post Outputs the dessert's details, including name, ingredients,
preparation time, price, cuisine type, flavor profile, sweetness level, and
whether it contains nuts.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients]
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Flavor Profile: [Flavor profile: Sweet, Bitter, Sour, Salty, or Umami]
* Sweetness Level: [Sweetness level]
* Contains Nuts: [Yes/No]
*/
void Dessert::display() const {
    std::cout << "Dish Name: " << getName() << std::endl;

    //dont make a copy, just the original vector
    const auto& ingredients = getIngredients();
    std::cout << "Ingredients: ";

    //loop through the ingredients vector and print each element, if not the last element, add a comma to the end of element
    for (size_t i = 0; i < ingredients.size(); i++) {
        std::cout << ingredients[i];
        if (i != ingredients.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << std::endl;

    std::cout << "Preparation Time: " << getPrepTime() << " minutes" << std::endl;
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << getPrice() << std::endl;
    std::cout << "Cuisine Type: " << getCuisineType() << std::endl;

    // Print flavor profile with default case
    switch (getFlavorProfile()) {
        case SWEET:
            std::cout << "Flavor Profile: Sweet" << std::endl;
            break;
        case BITTER:
            std::cout << "Flavor Profile: Bitter" << std::endl;
            break;
        case SOUR:
            std::cout << "Flavor Profile: Sour" << std::endl;
            break;
        case SALTY:
            std::cout << "Flavor Profile: Salty" << std::endl;
            break;
        case UMAMI:
            std::cout << "Flavor Profile: Umami" << std::endl;
            break;
    }

    std::cout << "Sweetness Level: " << getSweetnessLevel() << std::endl;

    
    std::cout << "Contains Nuts: " << (containsNuts() ? "Yes" : "No") << std::endl;
}



/**
* Modifies the dessert based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the dessert's attributes to meet the specified dietary
needs.
* - If `request.nut_free` is true:
* - Sets `contains_nuts_` to false.
* - Removes nuts from `ingredients_`.
* Nuts are: "Almonds", "Walnuts", "Pecans", "Hazelnuts",
"Peanuts", "Cashews", "Pistachios".
* - If `request.low_sugar` is true:
* - Reduces `sweetness_level_` by 3 (minimum of 0).
* - If `request.vegan` is true:
* - Removes dairy and egg ingredients from `ingredients_`.
* Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
*/
void Dessert::dietaryAccommodations(Dish::DietaryRequest request){
    std::set<std::string> nuts={"Almonds", "Walnuts", "Pecans", "Hazelnuts", "Peanuts", "Cashews", "Pistachios"};
    std::set<std::string> dairy={"Milk", "Eggs", "Cheese","Butter", "Cream", "Yogurt"};

    if (request.low_sugar){
        if (sweetness_level_>=3){
            sweetness_level_-=3;
        }
        else{
            sweetness_level_=0;
        }
    }
    if (request.nut_free || request.vegan){
        if (request.nut_free){
            contains_nuts_=false;
        }
        std::vector<std::string> ingredients =getIngredients();
        
        size_t i=0;

        //loops through whole ingredients to see if there are nuts or dairy
        while ( i < ingredients.size()){
            bool removed =false;
            
            //searches for nuts and removes them from ingredients if nut_free is true.
            //if a request is true and an ingredient is in the respective set, it removes it from the vector.
            if( request.nut_free && (nuts.find(ingredients[i]) != nuts.end())){ 
                ingredients.erase(ingredients.begin() + i);
                removed=true;// so it checks the ingredient that replaced the last one
            }
            if ( !removed && (request.vegan && (dairy.find(ingredients[i])!= dairy.end()))){
                ingredients.erase(ingredients.begin() + i);
                removed=true;// so it checks the ingredient that replaced the last one
            }

            if (!removed){//only increment if it wasn't removed in order to not skip over an ingredient that replaced the last one
                i++;
            }
            
        }


        setIngredients(ingredients);//set ingr

    }

    
}
   
