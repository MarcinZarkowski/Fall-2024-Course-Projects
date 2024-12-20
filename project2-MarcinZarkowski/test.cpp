#include "Dessert.hpp"
#include "Dish.hpp"
#include "MainCourse.hpp"
#include "Appetizer.hpp"
#include <iostream>
#include <string>
#include <vector>

int main(){
    //Create Appetizer instance
    Appetizer appetizer;
    appetizer.setServingStyle(Appetizer::ServingStyle::FAMILY_STYLE);
    appetizer.setSpicinessLevel(7);
    appetizer.setVegetarian(true);
    
    //Display Appetizer instance testing display and getter functions
    appetizer.display();
    std::cout<<"Spiciness Level: "<<appetizer.getSpicinessLevel()<<std::endl;
    std::cout<<"Serving Style: "<<appetizer.getServingStyle()<<std::endl;
    std::cout<<std::boolalpha<<"Vegetarian: "<<appetizer.isVegetarian()<<std::endl;

    std::cout<<std::endl;
    std::cout<<appetizer.getName();
    std::vector<std::string> ingredients = appetizer.getIngredients();

    //loop through ingredients and display each one
    for ( int i =0; i<ingredients.size(); i++){
        std::cout<<ingredients[i]<<std::endl;  
    }
    std::cout<<"Price: "<<appetizer.getPrice()<<std::endl;
    std::cout<<"Prep Time: "<<appetizer.getPrepTime()<<std::endl;  
    std::cout<<"Cuisine Type: "<<appetizer.getCuisineType()<<std::endl;
    std::cout<<std::endl;


    //Create Main Course instance
    
    //Create Side Dish instances to add to Main Course
    MainCourse::SideDish MashedPotatoes;
    MashedPotatoes.name="Mashed Potatoes";
    MashedPotatoes.category=MainCourse::Category::STARCHES;

    MainCourse::SideDish GreenBeans;
    GreenBeans.name="Green Beans";
    GreenBeans.category=MainCourse::Category::VEGETABLE;
    
    MainCourse course
    (
        "Grilled Chicken",
        {"Chicken", "Olive Oil", "Garlic", "Rosemary"},
        30,
        18.99,
        MainCourse::Dish::CuisineType::AMERICAN,
        MainCourse::CookingMethod::GRILLED,
        "Chicken",
        {MashedPotatoes, GreenBeans}, 
        true
        
    );

    std::cout<<std::endl;

    //Display Main Course instance testing display and getter functions
    course.display();   
    std::cout<<"Cooking Method: "<<course.getCookingMethod()<<std::endl;
    std::cout<<"Protein Type: "<<course.getProteinType()<<std::endl;
    std::cout<<"Side Dishes: ";

    std::vector<MainCourse::SideDish> sideDishes= course.getSideDishes();

    //loops through SideDishes vector and prints each side dish.
    for( std::vector<MainCourse::SideDish>::size_type i=0; i<sideDishes.size(); i++){
        if (i==sideDishes.size()-1){
            std::cout<<sideDishes[i].name<<" ";
            std::cout<<"("<<sideDishes[i].category<<")"<<std::endl;
        }
        else{
            std::cout<<sideDishes[i].name<<" ";
            std::cout<<"("<<sideDishes[i].category<<")"<<",";}
    }
    std::cout<<"Gluten-Free: "<<course.isGlutenFree()<<std::endl;

    //More Main Course testing for setter functions (using setter functions instead of constructor)
    course.setCookingMethod(MainCourse::CookingMethod::FRIED);
    course.setProteinType("Beef");
    course.addSideDish(MashedPotatoes);
    course.setGlutenFree(false);

    //checking if the setter functions worked by displaying instance again
    std::cout<<std::endl;
    course.display();   
    std::cout<<"Cooking Method: "<<course.getCookingMethod()<<std::endl;
    std::cout<<"Protein Type: "<<course.getProteinType()<<std::endl;
    std::cout<<"Side Dishes: ";

    std::vector<MainCourse::SideDish> sideDishes2= course.getSideDishes();
    
    //loops through SideDishes vector and prints each of them
    for( std::vector<MainCourse::SideDish>::size_type i=0; i<sideDishes2.size(); i++){
        if (i==sideDishes2.size()-1){
            std::cout<<" "<<sideDishes2[i].name<<" ";
            std::cout<<"("<<sideDishes[i].category<<")"<<std::endl;
        }
        else{
            std::cout<<sideDishes2[i].name<<" ";
            std::cout<<"("<<sideDishes2[i].category<<")"<<",";}
    }
    std::cout<<"Gluten-Free: "<<course.isGlutenFree()<<std::endl;
    std::cout<<std::endl;
    std::cout<<course.getName();
    std::vector<std::string> ingredients1 = course.getIngredients();

    //loops through ingredients and prints each of them
    for ( int i =0; i<ingredients1.size(); i++){
        std::cout<<ingredients1[i]<<std::endl;  
    }
    std::cout<<"Price: "<<course.getPrice()<<std::endl;
    std::cout<<"Prep Time: "<<course.getPrepTime()<<std::endl;  
    std::cout<<"Cuisine Type: "<<course.getCuisineType()<<std::endl;


    //Create Dessert instance
    Dessert dessert("Chocolate Cake", {"Flour", "Sugar", "Cocoa Powder", "Eggs"}, 45, 7.99, Dessert::Dish::CuisineType::FRENCH, Dessert::FlavorProfile::SWEET, 9, false);
    dessert.setName("Chocolate Cake");
    dessert.setIngredients({"Flour", "Sugar", "Cocoa Powder", "Eggs"});
    dessert.setPrepTime(45);
    dessert.setPrice(7.99);
    dessert.setCuisineType(Dessert::Dish::CuisineType::FRENCH);
    dessert.setFlavorProfile(Dessert::FlavorProfile::SWEET);
    dessert.setSweetnessLevel(9);
    dessert.setContainsNuts(false);

    //Display Dessert instance with "display" method and getter functions
    dessert.display();
    std::cout<<"Flavor Profile: "<<dessert.getFlavorProfile()<<std::endl;
    std::cout<<"Sweetness Level: "<<dessert.getSweetnessLevel()<<std::endl;
    std::cout<<"Contains Nuts: "<<dessert.containsNuts();

    std::cout<<std::endl;
    std::cout<<dessert.getName();
    std::vector<std::string> ingredients2 = dessert.getIngredients();

    //loops through ingredients and prints each of them
    for ( int i =0; i<ingredients2.size(); i++){
        std::cout<<ingredients2[i]<<std::endl;  
    }
    std::cout<<"Price: "<<dessert.getPrice()<<std::endl;
    std::cout<<"Prep Time: "<<dessert.getPrepTime()<<std::endl;  
    std::cout<<"Cuisine Type: "<<dessert.getCuisineType()<<std::endl;
}