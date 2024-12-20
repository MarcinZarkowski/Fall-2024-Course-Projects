#include "StationManager.hpp"
#include "Appetizer.hpp"

int main() {
    // Initialize Station Manager and Stations
    StationManager* stationManager = new StationManager();
    KitchenStation* station1 = new KitchenStation("Station1");
    KitchenStation* station2 = new KitchenStation("Station2");

    // Add stations to the manager
    stationManager->addStation(station1);
    stationManager->addStation(station2);

    // Create ingredients
    Ingredient cheese;
    cheese.name= "cheese";
    cheese.quantity=10;
    cheese.required_quantity= 5;
    Ingredient bread;
    bread.name= "bread";
    bread.quantity=10;
    bread.required_quantity= 5;
    Ingredient meat;
    meat.name= "meat";
    meat.quantity=10;
    meat.required_quantity= 5;
    Ingredient tomato;
    tomato.name= "tomato";
    tomato.quantity=0;
    tomato.required_quantity=5; // Initially unavailable

    // Add backup ingredients to StationManager
    stationManager->addBackupIngredient(cheese);
    stationManager->addBackupIngredient(bread);
    stationManager->addBackupIngredient(meat);
    stationManager->addBackupIngredient(tomato);

    // Create dishes
    Dish* pizza = new Appetizer("Pizza", {cheese, bread}, 10, 9.99, Dish::CuisineType::ITALIAN, Appetizer::ServingStyle::PLATED, 4, false);
    Dish* burger = new Appetizer("Burger", {bread, meat}, 8, 7.49, Dish::CuisineType::AMERICAN, Appetizer::ServingStyle::PLATED, 3, false);
    Dish* salad = new Appetizer("Salad", {tomato}, 6, 5.99, Dish::CuisineType::ITALIAN, Appetizer::ServingStyle::PLATED, 2, true);

    // Assign dishes to stations
    station1->assignDishToStation(pizza);
    station2->assignDishToStation(burger);
    station1->assignDishToStation(salad);

    // Add dishes to the queue
    stationManager->addDishToQueue(pizza);
    stationManager->addDishToQueue(burger);
    stationManager->addDishToQueue(salad);

    // Display initial queue
    std::cout << "Initial Dish Queue:" << std::endl;
    stationManager->displayDishQueue();

    // Process all dishes
    std::cout << "\nProcessing all dishes..." << std::endl;
    stationManager->processAllDishes();

    // Display queue after processing
    std::cout << "\nDish Queue After Processing:" << std::endl;
    stationManager->displayDishQueue();

    // Cleanup
    delete pizza;
    delete burger;
    delete salad;
    delete station1;
    delete station2;
    delete stationManager;

    return 0;
}
