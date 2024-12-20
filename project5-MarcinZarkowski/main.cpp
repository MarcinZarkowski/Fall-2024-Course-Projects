#include "StationManager.hpp"



int main() {
    KitchenStation actual_station;
    KitchenStation* station = &actual_station;
    StationManager StationManager;

    StationManager.addStation(station);

    std::cout << StationManager.getLength() << std::endl;
    
    std::cout << "before making cheese" << std::endl;
    Ingredient cheese("cheese", 100, 100, 10.00);
    std::cout << "cheese created" << std::endl;
    
    std::cout << "Station name: " << "Kitchen Station" << std::endl;
    std::cout<<StationManager.replenishIngredientAtStation("Kitchen Station", cheese);
    std::cout << "ingredient replenished" << std::endl;
    Ingredient mayonaise;
    mayonaise.name = "mayonaise";
    Ingredient mayonaise2;
    mayonaise2.name = "mayonaise";
    mayonaise2.quantity = 100;
  
    Dish* dish_ptr = new Dish("Pizza", {mayonaise2}, 60, 20.00, Dish::CuisineType::ITALIAN);

    StationManager.assignDishToStation("Kitchen Station", dish_ptr);
    std::cout << StationManager.canCompleteOrder("Pizza") << std::endl;
    for (auto& ingredient : actual_station.getIngredientsStock()) {
        std::cout << ingredient.name <<" "<<ingredient.quantity<< std::endl;
    }
    std::cout<<StationManager.prepareDishAtStation("Kitchen Station","Pizza");
    mayonaise.quantity = 100;
    StationManager.replenishIngredientAtStation("Kitchen Station", mayonaise);
    std::cout << "after making cheese, quantity of ingredients is: "<< actual_station.getIngredientsStock().size() << std::endl;
    for (auto& ingredient : actual_station.getIngredientsStock()) {
        std::cout << ingredient.name<<" "<<ingredient.quantity << std::endl;
    }
    std::cout<<StationManager.prepareDishAtStation("Kitchen Station","Pizza")<<std::endl;
    for (auto& ingredient : actual_station.getIngredientsStock()) {
        std::cout << ingredient.name<<" "<<ingredient.quantity << std::endl;
    }
    //std::cout << StationManager.canCompleteOrder("Pizza") << std::endl;
}
