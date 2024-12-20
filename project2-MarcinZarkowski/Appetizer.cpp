//Marcin Zarkowski
//csci235
//09/22/2024
//This file implements the Appetizer class which is a subclass of the Dish class.

#include <string>
#include <vector>
#include "Appetizer.hpp"



/**
 * Default constructor.
Accessors and Mutators:
* Initializes all private members with default values.
*/
Appetizer::Appetizer():Dish(){
    serving_style_ = ServingStyle::PLATED;
    spiciness_level_ = 0;
    vegetarian_ = false;
};
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
Appetizer::Appetizer( 
    const std::string& name, 
    const std::vector<std::string>& ingredients, 
    int prep_time, 
    double price, 
    CuisineType cuisine_type, 
    ServingStyle serving_style, 
    int spiciness_level, 
    bool vegetarian):Dish(name, ingredients,  prep_time, price, cuisine_type){
        serving_style_ = serving_style;
        spiciness_level_ = spiciness_level;
        vegetarian_ = vegetarian;
    };

/**
* Sets the serving style of the appetizer.
* @param serving_style The new serving style.
* @post Sets the private member `serving_style_` to the value of the
parameter.
*/
void Appetizer::setServingStyle(const ServingStyle& serving_style){
    serving_style_ = serving_style;
}

/**
* @return The serving style of the appetizer (as an enum).
*/
Appetizer::ServingStyle Appetizer::getServingStyle() const{
    return serving_style_;
}

/**
* Sets the spiciness level of the appetizer.
* @param spiciness_level An integer representing the spiciness level of
the appetizer.
The MainCourse Class
The MainCourse class is a subclass of Dish that represents a main course dish.
The MainCourse class must define the following types INSIDE the class definition:
* @post Sets the private member `spiciness_level_` to the value of the
parameter.
*/
void Appetizer::setSpicinessLevel(const int& spiciness_level){
    spiciness_level_ = spiciness_level;
}

/**
* @return The spiciness level of the appetizer. 
*/
int Appetizer::getSpicinessLevel() const{
    return spiciness_level_ ;
}

/**
* Sets the vegetarian flag of the appetizer.
* @param vegetarian A boolean indicating if the appetizer is
vegetarian.
* @post Sets the private member `vegetarian_` to the value of the
parameter.
*/
void Appetizer::setVegetarian(const bool& vegetarian){
    vegetarian_ = vegetarian;
}

/**
* @return True if the appetizer is vegetarian, false otherwise.
*/
bool Appetizer::isVegetarian() const {
    return vegetarian_;
}
    


