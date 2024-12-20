
/**
 * @file KitchenStation.cpp
 * @brief This file contains the implementation of the KitchenStation class in a virtual bistro simulation.
 * 
 *This file contains the implementation of the KitchenStation class in a virtual bistro simulation. It  stores pointers to Dish objects a "station" can make and holds an ingredient stock vector.
 *Stations contian information like ingredient stock and have functions which signify if a Station can complete an order for a food. 
 * @date [11/1/2024]
 * @author [Marcin Zarkowski]
 */


#include "KitchenStation.hpp"

/**
* Default Constructor
* @post: Initializes an empty kitchen station with default values.
*/
KitchenStation::KitchenStation(){
    station_name_ = "Kitchen Station";
    dishes_ = std::vector<Dish*>();
    ingredients_stock_ = std::vector<Ingredient>();
}

/**
* Parameterized Constructor
* @param station_name A string representing the station's name.
* @post: Initializes a kitchen station with the given name.
*/
KitchenStation::KitchenStation(std::string station_name){
    this->station_name_ = station_name;
    dishes_ = std::vector<Dish*>();
    ingredients_stock_ = std::vector<Ingredient>();
}

/**
* Destructor
* @post: Deallocates all dynamically allocated dishes in the
station.
*/
KitchenStation::~KitchenStation(){
    for(size_t i =0; i<dishes_.size(); i++){
        delete dishes_[i];
        dishes_[i] = nullptr;
    }
    dishes_.clear();
}

/**
* Retrieves the name of the kitchen station.
* @return: The name of the station.
*/
std::string KitchenStation::getName(){
    return station_name_;
}

/**
* Sets the name of the kitchen station.
* @param name A string representing the new station name.
* @post: Updates the station's name.
*/
void KitchenStation::setName(std::string name){
    station_name_ = name;
}

/**
* Retrieves the list of dishes assigned to the kitchen station.
* @return A vector of pointers to Dish objects assigned to the station.
*/
std::vector<Dish*> KitchenStation::getDishes(){
    return dishes_;
}

/**
* Retrieves the ingredient stock available at the kitchen station.
* @return A vector of Ingredient objects representing the station's
ingredient stock.
*/
std::vector<Ingredient> KitchenStation::getIngredientsStock(){
    return ingredients_stock_;
}

/**
* Assigns a dish to the station.
* @param dish A pointer to a Dish object.
* @post: Adds the dish to the station's list of dishes if not
already present.
* @return: True if the dish was added successfully; false
otherwise.
*/
bool KitchenStation::assignDishToStation(Dish* dish){
    
    for (size_t i = 0; i < dishes_.size(); i++){
        if (dishes_[i] && dishes_[i]->getName() == dish->getName()) {
            return false;
        }
    }
    
    dishes_.push_back(dish);
   
    return true;
}

/**
* Replenishes the station's ingredient stock.
* @param ingredient An Ingredient object.
* @post: Adds the ingredient to the station's stock or updates the
quantity if it already exists.
*/
void KitchenStation::replenishStationIngredients(Ingredient ingredient){
    for (size_t i = 0; i < ingredients_stock_.size(); i++){
        if(ingredients_stock_[i].name == ingredient.name){
            ingredients_stock_[i].quantity += ingredient.quantity;
            return;
        }
    }
    ingredients_stock_.push_back(ingredient);
    return;
}

/**
* Checks if the station can complete an order for a specific dish.
* @param dish_name A string representing the name of the dish.
* @return: True if the station has the dish assigned and all
required ingredients are in stock; false otherwise.
*/
bool KitchenStation::canCompleteOrder(const std::string& dish_name) {
    bool found = false;

    for (size_t i = 0; i < dishes_.size(); i++) {
        if (dishes_[i]->getName() == dish_name) {
            found = true;
            std::vector<Ingredient> dish_ingredients = dishes_[i]->getIngredients();
            std::vector<Ingredient> copy_of_ingredients_stock = ingredients_stock_;

            for (const auto& dish_ingredient : dish_ingredients) {
                bool ingredient_found = false;

                // Search for each ingredient in the stock copy, if exists set found to true
                for (auto& stock_ingredient : copy_of_ingredients_stock) {
                    if (stock_ingredient.name == dish_ingredient.name) {
                        // Check if the stock has enough quantity
                        //if (stock_ingredient.quantity < dish_ingredient.quantity) {
                        //   return false;
                        // }
                        ingredient_found = true;
                        //stock_ingredient.quantity -= dish_ingredient.quantity;
                        break;
                    }
                }

                //if not found can't complete order so return false
                if (!ingredient_found) {
                    return false; // Ingredient not found in stock
                }
            }
        }
    }
    return found; // Return true only if the dish was found and can be completed
}

/**
* Prepares a dish if possible.
* @param dish_name A string representing the name of the dish.
* @post: If the dish can be prepared, reduce the quantities of the
used ingredients accordingly. If the stock ingredient is depleted to
0, remove the ingredient from the Kitchen Station.
* @return: True if the dish was prepared successfully; false otherwise.
*/
bool KitchenStation::prepareDish(const std::string& dish_name) {

    //check if the station has ingredients needed for the dish
    if (!canCompleteOrder(dish_name)) {
        return false;
    }
    
    Dish* dish = nullptr;
    for (auto* d : dishes_) {
        if (d && d->getName() == dish_name) {  // Ensure d is not nullptr
            dish = d;//set dish when dish is found in station
            break;
        }
    }
    //ensure dish is not nullptr
    if (!dish) {
        return false;
    }
    
    
    
    std::vector<Ingredient> dish_ingredients = dish->getIngredients();

    //first loop to see if there is sufficient amounts of each ingredient in stock.
    for (size_t i=0; i<dish_ingredients.size(); i++) {

        for(size_t j=0; j < ingredients_stock_.size(); j++)  {

            if (ingredients_stock_[j].name == dish_ingredients[i].name) {

                if (ingredients_stock_[j].quantity < dish_ingredients[i].required_quantity) {
                    
                    return false;
                }
            }
        }
    }

    //subtract ingredients quantity needed for dish from stock and delete ingredient from stock if its quantity reaches 0.
    for (size_t i=0; i<dish_ingredients.size(); i++) {

        for(size_t j=0; j < ingredients_stock_.size(); j++) {

            if (ingredients_stock_[j].name == dish_ingredients[i].name) {
                ingredients_stock_[j].quantity -= dish_ingredients[i].required_quantity;
                if (ingredients_stock_[j].quantity == 0) {
                    ingredients_stock_.erase(ingredients_stock_.begin() + j);
                }         
                break;
            } 
        }
    }

    
    //if not enough ingredients, that means the dish cannot be made and we need to replenish the stock according to what we subtracted from the stock earlier. 
    //if (!enoughIngredients) {//we loop through the dish ingredients and stock and replenish the stock according to the subtracted values of the dish ingredients.
    //    for (const auto& dish_ingredient : dish_ingredients) {
    //        replenishStationIngredients(dish_ingredient);
     //   }   
    //}

    return true;//return true if we have enough ingredients to make the dish, false otherwise.

}