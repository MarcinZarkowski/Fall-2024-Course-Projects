/**
 * @file MainCourse.cpp
 * @brief This file contains the implementation of the MainCourse class in a virtual bistro simulation.
 * 
 *The MainCourse class is a virtual bistro dish. It overides the virtual methods of the Dish class (display and make accomidations).
 * Implements other get and set methods for the MainCourse class.
 * 
 * @date [10/25/2024]
 * @author [Marcin Zarkowski]
 */

#include "MainCourse.hpp"
#include <set>
/**
 * Default constructor.
 * Initializes all private members with default values.
 */
MainCourse::MainCourse()
    : Dish(), cooking_method_(GRILLED), protein_type_("UNKNOWN"), side_dishes_(), gluten_free_(false) {}

/**
 * Parameterized constructor.
 * @param name The name of the main course.
 * @param ingredients The ingredients used in the main course.
 * @param prep_time The preparation time in minutes.
 * @param price The price of the main course.
 * @param cuisine_type The cuisine type of the main course.
 * @param cooking_method The cooking method used for the main course.
 * @param protein_type The type of protein used in the main course.
 * @param side_dishes The side dishes served with the main course.
 * @param gluten_free Flag indicating if the main course is gluten-free.
 */
MainCourse::MainCourse(const std::string& name, const std::vector<std::string>& ingredients, const int &prep_time, const double &price, const CuisineType &cuisine_type, const CookingMethod &cooking_method, const std::string& protein_type, const std::vector<SideDish>& side_dishes, const bool &gluten_free)
    : Dish(name, ingredients, prep_time, price, cuisine_type), cooking_method_(cooking_method), protein_type_(protein_type), side_dishes_(side_dishes), gluten_free_(gluten_free) {}

/**
 * Sets the cooking method of the main course.
 * @param cooking_method The new cooking method.
 * @post Sets the private member `cooking_method_` to the value of the parameter.
 */
void MainCourse::setCookingMethod(const CookingMethod &cooking_method) {
    cooking_method_ = cooking_method;
}

/**
 * @return The cooking method of the main course.
 */
MainCourse::CookingMethod MainCourse::getCookingMethod() const {
    return cooking_method_;
}

/**
 * Sets the type of protein in the main course.
 * @param protein_type A string representing the type of protein.
 * @post Sets the private member `protein_type_` to the value of the parameter.
 */
void MainCourse::setProteinType(const std::string& protein_type) {
    protein_type_ = protein_type;
}

/**
 * @return The type of protein in the main course.
 */
std::string MainCourse::getProteinType() const {
    return protein_type_;
}

/**
 * Adds a side dish to the main course.
 * @param side_dish A SideDish struct containing the name and category of the side dish.
 * @post Adds the side dish to the `side_dishes_` vector.
 */
void MainCourse::addSideDish(const SideDish& side_dish) {
    side_dishes_.push_back(side_dish);
}

/**
 * @return A vector of SideDish structs representing the side dishes served with the main course.
 */
std::vector<MainCourse::SideDish> MainCourse::getSideDishes() const {
    return side_dishes_;
}

/**
 * Sets the gluten-free flag of the main course.
 * @param gluten_free A boolean indicating if the main course is gluten-free.
 * @post Sets the private member `gluten_free_` to the value of the parameter.
 */
void MainCourse::setGlutenFree(const bool &gluten_free) {
    gluten_free_ = gluten_free;
}

/**
 * @return True if the main course is gluten-free, false otherwise.
 */
bool MainCourse::isGlutenFree() const {
    return gluten_free_;
}

/**
* Displays the main course's details.
* @post Outputs the main course's details, including name, ingredients,
preparation time, price, cuisine type, cooking method, protein type,
side dishes, and gluten-free status to the standard output.
* The information must be displayed in the following format:
*
* Dish Name: [Name of the dish]
* Ingredients: [Comma-separated list of ingredients
* Preparation Time: [Preparation time] minutes
* Price: $[Price, formatted to two decimal places]
* Cuisine Type: [Cuisine type]
* Cooking Method: [Cooking method: e.g., Grilled, Baked, etc.]
* Protein Type: [Type of protein: e.g., Chicken, Beef, etc.]
* Side Dishes: [Side dish name] (Category: [Category: e.g., Starches,
Vegetables])
* Gluten-Free: [Yes/No]
*/

void MainCourse::display() const {
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
    std::cout << "\n";  // newline after the list
    
    std::cout << "Preparation Time: " << getPrepTime() << " minutes\n";
    std::cout << "Price: $" << std::fixed << std::setprecision(2) << getPrice() << "\n";
    std::cout << "Cuisine Type: " << getCuisineType() << "\n";

    // Print cooking method using switch statement
    std::string cookingMethod;
    switch (getCookingMethod()) {
        case GRILLED: cookingMethod = "Grilled"; break;
        case BAKED: cookingMethod = "Baked"; break;
        case BOILED: cookingMethod = "Boiled"; break;
        case FRIED: cookingMethod = "Fried"; break;
        case STEAMED: cookingMethod = "Steamed"; break;
        case RAW: cookingMethod = "Raw"; break;
    }
    std::cout << "Cooking Method: " << cookingMethod << "\n";
    std::cout << "Protein Type: " << getProteinType() << "\n";

    // Store side dishes to avoid repeated calls
    const auto& sideDishes = getSideDishes();
    std::cout << "Side Dishes: ";
    
    for (size_t i = 0; i < sideDishes.size(); i++) {
        std::string category; // Store string representation of the category
        switch (sideDishes[i].category) {
            case GRAIN: category = "Grain"; break;
            case PASTA: category = "Pasta"; break;
            case LEGUME: category = "Legume"; break;
            case BREAD: category = "Bread"; break;
            case SALAD: category = "Salad"; break;
            case SOUP: category = "Soup"; break;
            case STARCHES: category = "Starches"; break;
            case VEGETABLE: category = "Vegetable"; break;
            
        }

        std::cout << sideDishes[i].name << " (Category: " << category << ")";
        if (i != sideDishes.size() - 1) {
            std::cout << ", ";
        }
    }
    std::cout << "\n";  // Ensure a newline after the list
    //print yes is true and no if false
    std::cout << "Gluten-Free: " << (isGlutenFree() ? "Yes" : "No") << "\n";  // Cleaner output
}


/**
* Modifies the main course based on dietary accommodations.
* @param request A DietaryRequest structure specifying the dietary
accommodations.
* @post Adjusts the main course's attributes to meet the specified
dietary needs.
* - If `request.vegetarian` is true:
* - Changes `protein_type_` to "Tofu".
* - Searches `ingredients_` for any non-vegetarian
ingredients and replaces the first occurrence with "Beans". If there are
other non-vegetarian ingredients, the next non-vegetarian ingredient is
replaced with "Mushrooms". If there are more, they will be removed
without substitution.
* Non-vegetarian ingredients are: "Meat", "Chicken",
"Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon".
* - If `request.vegan` is true:
* - Changes `protein_type_` to "Tofu".
* - Removes dairy and egg ingredients from `ingredients_`.
* Dairy and egg ingredients are: "Milk", "Eggs", "Cheese",
"Butter", "Cream", "Yogurt".
* - If `request.gluten_free` is true:
* - Sets `gluten_free_` to true.
* - Removes side dishes from `side_dishes_` whose category
involves gluten.
* Gluten-containing side dish categories are: `GRAIN`,
`PASTA`, `BREAD`, `STARCHES`.
*/
void MainCourse::dietaryAccommodations(Dish::DietaryRequest request) {
    std::set<std::string> meats = {"Meat", "Chicken", "Fish", "Beef", "Pork", "Lamb", "Shrimp", "Bacon"};
    std::set<std::string> dairy = {"Milk", "Eggs", "Cheese", "Butter", "Cream", "Yogurt"};
    std::set<Category> gluten = {GRAIN, PASTA, BREAD, STARCHES};
    std::vector<std::string> meat_sub = {"Beans", "Mushrooms"};
    int meat_replaced_count = 0;

    if (request.vegetarian || request.gluten_free || request.vegan) {
        
        std::vector<std::string> ingredients = getIngredients();
        
        size_t i = 0;

        // Handle vegetarian and vegan requests
        if (request.vegetarian || request.vegan) {
            protein_type_ = "Tofu";

            //loop through ingredients
            while (i < ingredients.size()) {

                // Handle vegetarian ingredients
                if (request.vegetarian && (meats.find(ingredients[i]) != meats.end())) {
                    if (meat_replaced_count < 2) {
                        ingredients[i] = meat_sub[meat_replaced_count];
                        meat_replaced_count++;
                    } else {
                        ingredients.erase(ingredients.begin() + i); //remove ingredient and shift others down (keeps order intact since only first and second instances of meat should be changed to Beans and Mushrooms)  
                    }
                } 
                
                // Handle vegan ingredients
                else if (request.vegan && (dairy.find(ingredients[i]) != dairy.end())) {      
                    ingredients.erase(ingredients.begin() + i); //remove ingredient and shift others down (keeps order intact since only first and second instances of meat should be changed to Beans and Mushrooms)
                }
                else{
                    i++; // Increment after checks
                }
            }
            setIngredients(ingredients); // Set modified ingredients
        }
       
        // Handle gluten-free side dishes
        if (request.gluten_free) {
            gluten_free_ = true;
            std::vector<SideDish> side_dishes = getSideDishes();
           
            size_t side_i = 0;
            while (side_i < side_dishes.size()) {
                if (gluten.find(side_dishes[side_i].category) != gluten.end()) {                
                   side_dishes.erase(side_dishes.begin() + side_i); //remove ingredient and shift others down (keeps order intact since only first and second instances of meat should be changed to Beans and Mushrooms)
                   
                }
                else{
                    side_i++; 
                } 
            }
            side_dishes_ = side_dishes; // Set modified side dishes
        }    
    }
}
