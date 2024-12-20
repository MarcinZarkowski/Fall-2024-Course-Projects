#include "Kitchen.hpp"
#include "Appetizer.hpp"
#include "MainCourse.hpp"

int main(){


    Kitchen kitchen("dish.csv");
    //std::cout<<kitchen.elaborateDishCount()<<std::endl; 
    //kitchen.displayMenu();


    Dish::DietaryRequest dietaryRequest;
    dietaryRequest.vegetarian = true;
    dietaryRequest.vegan = true;
    dietaryRequest.gluten_free = true;
    dietaryRequest.nut_free = true;
    dietaryRequest.low_sodium = true;
    dietaryRequest.low_sugar = true;

    kitchen.dietaryAdjustment(dietaryRequest);
    //std::cout<<kitchen.elaborateDishCount()<<std::endl; 
    kitchen.displayMenu();

    //MainCourse dish;
   // dish.setIngredients({"Beans", "Rice", "Lamb", "Cheese", "Meat"});
    //dish.display();
   // std::cout<<std::endl;
  //  dish.dietaryAccommodations(dietaryRequest);
  //  dish.display();

}