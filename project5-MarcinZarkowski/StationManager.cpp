/**
 * @file KitchenManager.cpp
 * @brief This file contains the implementation of the KitchenManager class in a virtual bistro simulation.
 * 
 *This file contains the implementation of the KitchenManager class in a virtual bistro simulation. It derives from LinkedList and stores pointer to KitchenStation objects in a linked list.
 *This manages KitchenStation objects and provides methods to add and remove them, adjust them etc.
 * @date [11/1/2024]
 * @author [Marcin Zarkowski]
 */



#include "StationManager.hpp"



/**
* Default Constructor
* @post: Initializes an empty station manager.
*/
StationManager::StationManager(){
}

/**
* Destructor
* @post: Deallocates all kitchen stations and clears the list.
*/
StationManager::~StationManager(){
    clear();
}

/**
* Adds a new station to the station manager.
* @param station A pointer to a KitchenStation object.
* @post: Inserts the station into the linked list.
* @return: True if the station was successfully added; false
otherwise.
*/
bool StationManager::addStation(KitchenStation* station){
    int position=getLength();
    return insert(position, station);
}

/**
* Removes a station from the station manager by name.
* @param station_name A string representing the station's name.
* @post: Removes the station from the list and deallocates it.
* @return: True if the station was found and removed; false
otherwise.
*/
bool StationManager::removeStation(std::string station_name){
    int length=getLength();
    
    //loop through the list to find station and remove if its name is the same as the one passed in
    for(int i=0; i<length; i++){
        if(getEntry(i)->getName()==station_name){
            return remove(i); 
        }
    }
    return false;
}

/**
* Finds a station in the station manager by name.
* @param station_name A string representing the station's name.
* @return: A pointer to the KitchenStation if found; nullptr
otherwise.
*/
KitchenStation* StationManager::findStation(std::string station_name){
    int length=getLength();

    //loop through the list to find station and return if its name is the same as the one passed in
    for(int i=0; i<length; i++){
        KitchenStation* entry = getEntry(i);
        if (entry==nullptr){
            continue;
        }
        if(entry->getName()==station_name){
            return entry; 
        }
    }
    return nullptr;
}

/**
* Moves a specified station to the front of the station manager
list.
* @param station_name A string representing the station's name.
* @post: The station is moved to the front of the list if it
exists.
* @return: True if the station was found and moved; false
otherwise.
*/
bool StationManager::moveStationToFront(std::string station_name){

    KitchenStation* station_ptr = findStation(station_name);//find station
    if (station_ptr == nullptr){
        return false;
    }
    //KitchenStation station = *station_ptr;
    bool removed= removeStation(station_name);//remove station
    if(!removed){
        return false;
    }
    return insert(0, station_ptr);//add it and return the bool value from insert
}

/**
* Merges the dishes and ingredients of two specified stations.
* @param station_name1 The name of the first station.
* @param station_name2 The name of the second station.
* @post: The second station is removed from the list, and its
contents are added to the first station.
* @return: True if both stations were found and merged; false
otherwise.
*/
bool StationManager::mergeStations(std::string station_name1, std::string station_name2){
    
    //find the stations
    KitchenStation* station1_ptr = findStation(station_name1);
    KitchenStation* station2_ptr = findStation(station_name2);

    //if any doesnt exist return false
    if(station1_ptr==nullptr || station2_ptr==nullptr){
        return false;
    }

    
    std::vector<Dish*> station2_dishes = station2_ptr->getDishes();
    std::vector<Ingredient> station2_ingredients = station2_ptr->getIngredientsStock();

    //find longer value to complete additions to station 1 in one loop
    size_t longer = station2_dishes.size() > station2_ingredients.size() ? station2_dishes.size(): station2_ingredients.size();//get the length of the longer vector

    //loop through both vectors and assign the contents to the first vector
    for (size_t i = 0; i < longer; i++){
        if (i<station2_dishes.size()){
            station1_ptr->assignDishToStation(station2_dishes[i]); 
        }
        if (i<station2_ingredients.size()){
            station1_ptr->replenishStationIngredients(station2_ingredients[i]) ; 
        }
    }

    bool removed=removeStation(station2_ptr->getName());//remove station after merging from it

    if(!removed){
        return false;
    }
    return true;
}

/**
* Assigns a dish to a specific station.
* @param station_name A string representing the station's name.
* @param dish A pointer to a Dish object.
* @post: Assigns the dish to the specified station.
* @return: True if the station was found and the dish was assigned;
false otherwise.
*/
bool StationManager::assignDishToStation(std::string station_name, Dish* dish){

    KitchenStation* station_ptr = findStation(station_name);

    if (station_ptr == nullptr){
        return false;
    }
    bool assigned = station_ptr->assignDishToStation(dish);

    return assigned;
}

/**
* Replenishes an ingredient at a specific station.
* @param station_name A string representing the station's name.
* @param ingredient An Ingredient object.
* @post: Replenishes the ingredient stock at the specified station.
* @return: True if the station was found and the ingredient was
replenished; false otherwise.
*/
bool StationManager::replenishIngredientAtStation(std::string station_name, Ingredient ingredient){

    KitchenStation* station_ptr = findStation(station_name);

    if (station_ptr == nullptr){
        return false;
    }

    station_ptr->replenishStationIngredients(ingredient);

    return true;
}

/**
* Checks if any station in the station manager can complete an
order for a specific dish.
* @param dish_name A string representing the name of the dish.
* @return: True if any station can complete the order; false
otherwise.
*/
bool StationManager::canCompleteOrder(std::string dish_name){

    int size= getLength();
     
    //loop through all stations and check if any can complete the order
    for (int i = 0; i < size; i++){
        if (getEntry(i)->canCompleteOrder(dish_name)){
            return true;
        }
    }

    return false;
}

/**
* Prepares a dish at a specific station if possible.
* @param station_name A string representing the station's name.
* @param dish_name A string representing the name of the dish.
* @post: If the dish can be prepared, reduces the quantities of the
used ingredients at the station.
* @return: True if the dish was prepared successfully; false
otherwise.
*/
bool StationManager::prepareDishAtStation(std::string station_name, std::string dish_name){

    KitchenStation* station_ptr = findStation(station_name);

    if (station_ptr == nullptr){
        return false;
    }
    bool can_prepare = station_ptr->prepareDish(dish_name);//check if the station can prepare the dish and if it can, prepare it
    
    return can_prepare;
}