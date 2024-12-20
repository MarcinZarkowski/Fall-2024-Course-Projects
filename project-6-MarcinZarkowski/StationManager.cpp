// Marcin Zarkowski
//12/1/2024
// Station Manager definition file, this class controls a linked list of kitchen stations. It is responsible for adding, removing, and finding kitchen stations. It also 
// has a backup ingredients vector that gives ingredients to stations if they do not have enough to complete a dish. 


#include "StationManager.hpp"
#include <iostream>
#include <map>
// Default Constructor
StationManager::StationManager() {
    // Initializes an empty station manager
}


// Adds a new station to the station manager
bool StationManager::addStation(KitchenStation* station) {
    return insert(item_count_, station);
}

// Removes a station from the station manager by name
bool StationManager::removeStation(const std::string& station_name) {
    for (int i = 0; i < item_count_; ++i) {
        if (getEntry(i)->getName() == station_name) {
            return remove(i);
        }
    }
    return false;
}

// Finds a station in the station manager by name
KitchenStation* StationManager::findStation(const std::string& station_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            return searchptr->getItem();
        }
        searchptr = searchptr->getNext();
    }
    return nullptr;
}

// Moves a specified station to the front of the station manager list
bool StationManager::moveStationToFront(const std::string& station_name) {
    // First, make sure the station exists
    if (findStation(station_name) == nullptr) {
        return false;
    }
    
    // If it's already at the front, return true
    if (getHeadNode()->getItem()->getName() == station_name) {
        return true;
    }

    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == station_name) {
            // Make a copy of the station
            KitchenStation* station = searchptr->getItem();
            
            // Remove the station from its current position
            int pos = getStationIndex(searchptr->getItem()->getName());
            remove(pos);
            
            // Insert the station at the front
            insert(0, station);
            
            return true;  // Exit after moving the station
        }
        
        searchptr = searchptr->getNext();  // Move to the next node
    }
    
    return false;
}


int StationManager::getStationIndex(const std::string& name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    int index = 0;
    while (searchptr != nullptr) {
        if (searchptr->getItem()->getName() == name) {
            return index;
        }
        searchptr = searchptr->getNext();
        index++;
    }
    return -1;
}

// Merges the dishes and ingredients of two specified stations
bool StationManager::mergeStations(const std::string& station_name1, const std::string& station_name2) {
    KitchenStation* station1 = findStation(station_name1);
    KitchenStation* station2 = findStation(station_name2);
    if (station1 && station2) {
        // take all the dishes from station2 and add them to station1
        for (Dish* dish : station2->getDishes()) {
            station1->assignDishToStation(dish);
        }
        // take all the ingredients from station2 and add them to station1
        for (Ingredient ingredient : station2->getIngredientsStock()) {
            station1->replenishStationIngredients(ingredient);
        }
        // remove station2 from the list
        removeStation(station_name2);
        return true;
    }
    return false;
}

// Assigns a dish to a specific station
bool StationManager::assignDishToStation(const std::string& station_name, Dish* dish) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        return station->assignDishToStation(dish);
    }
    return false;
}

// Replenishes an ingredient at a specific station
bool StationManager::replenishIngredientAtStation(const std::string& station_name, const Ingredient& ingredient) {
    KitchenStation* station = findStation(station_name);
    if (station) {
        station->replenishStationIngredients(ingredient);
        return true;
    }
    return false;
}

// Checks if any station in the station manager can complete an order for a specific dish
bool StationManager::canCompleteOrder(const std::string& dish_name) const {
    Node<KitchenStation*>* searchptr = getHeadNode();
    while (searchptr != nullptr) {
        if (searchptr->getItem()->canCompleteOrder(dish_name)) {
            return true;
        }
        searchptr = searchptr->getNext();
    }
    return false;
}

// Prepares a dish at a specific station if possible
bool StationManager::prepareDishAtStation(const std::string& station_name, const std::string& dish_name) {
    KitchenStation* station = findStation(station_name);
    if (station && station->canCompleteOrder(dish_name)) {
        return station->prepareDish(dish_name);
    }
    return false;
}

/**
* Retrieves the current dish preparation queue.
* @return A copy of the queue containing pointers to Dish objects.
* @post: The dish preparation queue is returned unchanged.
*/
std::queue<Dish*> StationManager::getDishQueue() const{
    return dishqueue;
}

/**
* Retrieves the list of backup ingredients.
* @return A vector containing Ingredient objects representing backup
supplies.
* @post: The list of backup ingredients is returned unchanged.
*/
std::vector<Ingredient> StationManager::getBackupIngredients() const{
    return backupingredients;
}

/**
* Sets the current dish preparation queue.
* @param dish_queue A queue containing pointers to Dish objects.
* @pre: The dish_queue contains valid pointers to dynamically allocated
Dish objects.
* @post: The dish preparation queue is replaced with the provided
queue.
*/
void StationManager::setDishQueue(std::queue<Dish*> dish_queue){
    dishqueue = dish_queue;
}

/**
* Adds a dish to the preparation queue without dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @pre: The dish pointer is not null.
* @post: The dish is added to the end of the queue.
*/
void StationManager::addDishToQueue(Dish* dish){
    dishqueue.push(dish);
}

/**
* Adds a dish to the preparation queue with dietary accommodations.
* @param dish A pointer to a dynamically allocated Dish object.
* @param request A DietaryRequest object specifying dietary
accommodations.
* @pre: The dish pointer is not null.
* @post: The dish is adjusted for dietary accommodations and added to
the end of the queue.
*/
void StationManager::addDishToQueue(Dish* dish, Dish::DietaryRequest request){
    dish->dietaryAccommodations(request);//make the accomodations
    dishqueue.push(dish);
}

/**
* Prepares the next dish in the queue if possible.
* @pre: The dish queue is not empty.
* @post: The dish is processed and removed from the queue.
* @return: True if the dish was prepared successfully; false otherwise.
*/
bool StationManager::prepareNextDish(){
    if (dishqueue.empty()){
        return false;
    }
    Dish* dish = dishqueue.front();//get the front of the queue

    //search for station that can complete the order for the dish in the queue, if can, make it and pop from queue and return true
    for (int i = 0; i < getLength(); i++){ 
        KitchenStation* station = getEntry(i);
        if (station->prepareDish(dish->getName())){
            dishqueue.pop();
            return true;
        }
    }
    return false;
}

/**
* Displays all dishes in the preparation queue.
* @pre: None.
* @post: Outputs the names of the dishes in the queue in order (each name
is on its own line).
*/
void StationManager::displayDishQueue() const {

    std::queue<Dish*> tempqueue = dishqueue;//create a copy of present queue

    //while there is dishes in the copy queue, display their names and pop
    while (!tempqueue.empty()){
        Dish* dish = tempqueue.front();
        std::cout<< dish->getName() << std::endl;
        tempqueue.pop();
    }

}

/**
* Clears all dishes from the preparation queue.
* @pre: None.
* @post: The dish queue is emptied and all allocated memory is freed.
*/
void StationManager::clearDishQueue(){
    //while there is dishes in the copy queue, peek to get the Dish, pop from queue and delete
    while (!dishqueue.empty()){
        Dish* dish = dishqueue.front();
        dishqueue.pop();
        delete dish;
    }
}

/**
* Replenishes a specific ingredient at a given station from the backup
ingredients stock by a specified quantity.
* @param station_name A string representing the name of the station.
* @param ingredient_name A string representing the name of the ingredient
to replenish.
* @param quantity An integer representing the amount to replenish.
* @pre None.
* @post If the ingredient is found in the backup ingredients stock and has
sufficient quantity, it is added to the station's ingredient stock by the
specified amount, and the function returns true.
* The quantity of the ingredient in the backup stock is decreased by
the specified amount.
* If the ingredient in backup stock is depleted (quantity becomes
zero), it is removed from the backup stock.
* If the ingredient does not have sufficient quantity in backup
stock, or the ingredient or station is not found, returns false.
* @return True if the ingredient was replenished from backup; false
otherwise.
*/
bool StationManager::replenishStationIngredientFromBackup(const std::string& station_name, const std::string& ingredient_name, int quantity) {
    if (quantity <= 0) { // Invalid quantity guard
        return false;
    }
    // Search for the ingredient in the backup stock
    for (size_t i = 0; i < backupingredients.size(); i++) {
        if (backupingredients[i].name == ingredient_name) {
            // Check if the quantity in stock is sufficient
            if (backupingredients[i].quantity >= quantity) {
                // Create an ingredient object for replenishment
                Ingredient ingredient;
                ingredient.name = ingredient_name;
                ingredient.quantity = quantity;

                if (replenishIngredientAtStation(station_name, ingredient)){
                    // Deduct the required quantity from backup stock
                    backupingredients[i].quantity -= quantity;

                    // Remove the ingredient from backup stock if depleted
                    if (backupingredients[i].quantity == 0) {
                        backupingredients.erase(backupingredients.begin() + i);
                        i--;
                    }

                    return true;

                }
                //if couldn't replenish, rturn false
                return false;
                
            }
            
            //if not enough quantity, break and return false
            return false;    
           
        }
    }

    // Return false if ingredient not found 
    return false;



}


/**
* Sets the backup ingredients stock with the provided list of ingredients.
* @param ingredients A vector of Ingredient objects to set as the backup
stock.
* @pre None.
* @post The backup_ingredients_ vector is replaced with the provided
ingredients.
* @return True if the ingredients were added; false otherwise.
*/
bool StationManager::addBackupIngredients(const std::vector<Ingredient>& ingredients){
    backupingredients = ingredients;
    
    return true;
}


/**
* Adds a single ingredient to the backup ingredients stock.
* @param ingredient An Ingredient object to add to the backup stock.
* @pre None.
* @post If the ingredient already exists in the backup stock, its quantity
is increased by the ingredient's quantity.
* If the ingredient does not exist, it is added to the backup stock.
* @return True if the ingredient was added; false otherwise.
*/
bool StationManager::addBackupIngredient(const Ingredient& ingredient){
    
    //loop through, if ingredient already exists, increase quantity and return false
    for (size_t i = 0; i < backupingredients.size(); i++){
        if (backupingredients[i].name == ingredient.name){
            backupingredients[i].quantity += ingredient.quantity;
            return true;
        }
    }

    //if ingredient was added, return true
    backupingredients.push_back(ingredient);
    return true;
}

/**
* Empties the backup ingredients vector
* @post The backup_ingredients_ private member variable is empty.
*/
void StationManager::clearBackupIngredients(){
    backupingredients.clear();
}

/**
* Processes all dishes in the queue and displays detailed results.
* @pre: None.
* @post: All dishes are processed, and detailed information is displayed
(as per the format in the specifications), including station replenishments
and preparation results.
* If a dish cannot be prepared even after replenishing ingredients, it
stays in the queue in its original order...
* i.e. if multiple dishes cannot be prepared, they will remain in the queue
in the same order
*/
void StationManager::processAllDishes() {
    Dish* firstUnpreparedDish = nullptr; // Pointer to track the first unprepared dish.

    while (!dishqueue.empty()) {
        Dish* dish = dishqueue.front();

        // Check if we've cycled through the queue without making progress.
        if (firstUnpreparedDish == dish) {
            break; // Exit the loop to prevent infinite cycling.
        }
        dishqueue.pop();

        bool dishCompleted = false;
        std::cout << "PREPARING DISH: " << dish->getName() << std::endl;

        for (int i = 0; i < getLength(); i++) {
            if (dishCompleted) break;

            KitchenStation* station = getEntry(i);
            std::cout << station->getName() << " attempting to prepare " << dish->getName() << "..." << std::endl;

            // Check if the station can prepare the dish.
            bool found = false;
            std::vector<Dish*> dishes = station->getDishes();
            for (size_t j = 0; j < dishes.size(); j++) {
                if (dishes[j]->getName() == dish->getName()) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                std::cout << station->getName() << ": Dish not available. Moving to next station..." << std::endl;
                continue;
            }


            //if cant complete, try to replenish ingredients
            if (!station->canCompleteOrder(dish->getName())) {
                std::cout << station->getName() << ": Insufficient ingredients. Replenishing ingredients..." << std::endl;

                std::vector<Ingredient> stock = station->getIngredientsStock();
                std::vector<Ingredient> required = dish->getIngredients();
                

            
                bool cantComplete = false;//flag indicating if you can complete a dish after replenishing
                
                //loop through required ingredients, replenish if not enough in stock, and break out if cant replenish
                for (const auto& req : required) {
                    bool ingredientFoundInStock = false;

                    // Check if the required ingredient is in the stock.
                    for (auto& st : stock) {
                        if (st.name == req.name) {
                            ingredientFoundInStock = true;
                            int deficit = req.required_quantity - st.quantity;
                            // std::cout << "Required quantity: " << req.required_quantity << std::endl;
                            // std::cout << "Stock quantity: " << st.quantity << std::endl;
                            // std::cout << "Deficit: " << deficit << std::endl;

                            // Replenish if there's a deficit.
                            if (deficit > 0) { 
                                if (!replenishStationIngredientFromBackup(station->getName(), req.name, deficit)) {
                                    std::cout << station->getName() << ": Unable to replenish ingredients. Failed to prepare " << dish->getName() << "." << std::endl;
                                    cantComplete = true;
                                    break;
                                }
                                
                            }
                            break; // if ingredient found in stock, break and look for next required ingredient
                        }
                    }

                    if (cantComplete) {
                        break;
                    }

                    // If the ingredient is not found in the stock, try to replenish it from backup.
                    if (!ingredientFoundInStock) {
                        int deficit = req.required_quantity;
                        //std::cout << "Required ingredient not found in stock: " << req.name << ". Attempting to replenish from backup." << std::endl;

                        if (!replenishStationIngredientFromBackup(station->getName(), req.name, deficit)) {
                            std::cout << station->getName() << ": Unable to replenish ingredients. Failed to prepare " << dish->getName() << "." << std::endl;
                            cantComplete = true;
                            break;
                        }

                        
                    }  
                }
  
                if (cantComplete) {

                    continue; // Skip to the next station.
                }

                if (!cantComplete){
                    std::cout << station->getName() << ": Ingredients replenished." << std::endl;
                }
            }
            
            // Attempt to prepare the dish.
            if (station->prepareDish(dish->getName())) {
                std::cout << station->getName() << ": Successfully prepared " << dish->getName() << "." << std::endl;
                dishCompleted = true;
                break;
            }
            //std::cout<<"result of trying to prepare dish: "<<station->prepareDish(dish->getName())<<std::endl;

        }

        if (!dishCompleted) {
            std::cout << dish->getName() << " was not prepared." << std::endl;

            // Track the first unprepared dish.
            if (firstUnpreparedDish == nullptr) {
                firstUnpreparedDish = dish;
            }

            dishqueue.push(dish); // Requeue the unprepared dish.
        } 

        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "All dishes have been processed." << std::endl;
}

