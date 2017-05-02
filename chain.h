/*************************************
*     Name: Dandan Lin               *
*     Class: CSCI 33500              *
*     Professor: Ioannis Stamos      *
*     Project Name: The Big Five     *
**************************************/
/*******************************************************************************
* Chain Class is a templated class that use pointers as it's underlying data  *
* structure. When user enters a chain, a series of items, this Chain class     *
* will print out all the items that user enterd.                               *
*******************************************************************************/

#ifndef CSCI335_HOMEWORK1_CHAIN_
#define CSCI335_HOMEWORK1_CHAIN_

#include <iostream>
#include <sstream>
#include <cstddef>

namespace teaching_project {
/* This Chain class is a templated class that use pointers as it's underlying
data structure.

   Class Chain can print out a series of items, which are correctly formatted.
It also can concatenate/add two Chains based on user's input
It depends on user's input.
*/
template<typename Object>
class Chain {
public:
// Default "big five" -- you have to alter them for your assignment.
// That means that you will remove the "= default" statement.
//  and you will provide an implementation.

// Zero-parameter constructor.
Chain():size_{0}, array_{nullptr} {}

// Copy-constructor.
Chain(const Chain &rhs) {
   size_ = rhs.size_;
   array_ = new Object[size_];
   // Copy each elements in rhs over
   for (int i = 0; i < size_; ++i) {
      array_[i] = rhs.array_[i];
   }
}

// Copy-assignment.
Chain& operator=(const Chain &rhs) {
   if (this != &rhs) {
      Chain copy = rhs;
      std::swap(*this, copy);
   }

   return *this;
};

// Move-constructor.
Chain(Chain &&rhs) : size_{rhs.size_}, array_{rhs.array_} {
   rhs.size_ = 0;
   rhs.array_ = nullptr;
}

// Move-assignment.
// Just use std::swap() for all variables.
Chain& operator=(Chain &&rhs) {
   std::swap(size_, rhs.size_);
   std::swap(array_, rhs.array_);

   return *this;
}

// destructor
~Chain() {
   // Reset the size
   size_ = 0;
   // Deallocate the memory
   delete []array_;
}
// End of big-five.

// One parameter constructor.
Chain(const Object& item) {
   size_ = 1;
   array_ = new Object[size_];
   array_[size_-1] = item;
}

// Read a chain from standard input.
void ReadChain() {
   std::string inputted_chain;
   std::string number_of_elements_temp;

   int first_space_position = 0;
   int number_of_space = 0;
   int number_of_elements = 0;
   bool right_format = true;

   // std::cout << "\nPlease provide a Chain formatted as [4: 4 5 76 2].\n";
   std::cout << "\n";
   // Use getline get the chain from user
   getline(std::cin, inputted_chain);

   // Check if the user input is in the correct format
   if (inputted_chain == "[]" || inputted_chain.length() < 2) {
      // Abort the program if user provided an invalid chain
      right_format = false;
      std::cout << "Wrong format. Please use a valid chain\n";
      abort();
   } else if (inputted_chain.at(0) != '['
                               || inputted_chain.at(inputted_chain.length()-1) != ']') {
      // Abort the program if the user's input is not formatted correctly
      right_format = false;
      std::cout << "Wrong format. \n";
      abort();
   } else if (inputted_chain.length() == 3 && (inputted_chain.at(1) == ' ' || inputted_chain.at(1) >= 0)) {
      right_format = false;
      std::cout << "Wrong format. \n";
      abort();
   } else {
      for (int i = 1; i < inputted_chain.length(); ++i) {
         // number_of_space == 0 means the first elemnt haven't been read
         if (number_of_space == 0 && inputted_chain.at(i) != ':' && inputted_chain.at(i) != ' ') {
            // Stor the size of the chain in a string variable first
            number_of_elements_temp += inputted_chain.at(i);
            first_space_position = i+2;
         } else if (inputted_chain.at(i) == ' '){
            // count the number of space in the input
            number_of_space++;
            number_of_elements++;
         }
      }
      // Abort the program if the number of elemets is not c0rrect
      if (inputted_chain.at(first_space_position-1) != ':') {
         right_format = false;
         std::cout << "Wrong format\n";
         abort();
      } else if (number_of_space >= 1 && std::to_string(number_of_space) != number_of_elements_temp) {
         // If the chain is correctly formatted, then the number of elemts will = number of space
         // If number_of_space != number_of_elements_temp, then it implies the format is wrong
         right_format = false;
         std::cout << "Wrong format\n";
         abort();
      }
   }

   // Once the inputted_chain is formatted correctly, we read the chain's content into array_
   if (right_format == true) {
      size_ = number_of_elements;
      array_ = new Object[number_of_elements];

      // Get the substring of all the elements user provided chain (from first element's position)
      std::string substr_temp = inputted_chain.substr(first_space_position+1, inputted_chain.length()-2-first_space_position);
      // Use stringstream to parse the substr_temp
      std::stringstream some_str(substr_temp);

      // Store each element into array_ while parsing
      for (int i = 0; i < number_of_elements; ++i) {
         some_str >> array_[i];
      }
   }
}

size_t size() const {
   return size_;
}

// @location: an index to a location in the chain.
// @returns the Object at @location.
// const version.
// abort() if out-of-range.
const Object& operator[](size_t location) const {
   // Check if provided location is in the range
   // Abort the program if it's ou of the range
   if (location > size_) {
      std::cout << "Provided location out-of-range. \n";
      abort();
   }

   return array_[location];
}

// @location: an index to a location in the range.
// @returns the Object at @location.
// non-const version.
// abort() if out-of-range.
Object& operator[](size_t location) {
   // Check if provided location is in the range
   // Abort the program if it's ou of the range
   if (location < 0 || location > size_) {
      std::cout << "Provided location out-of-range. \n";
      abort();
   }

   return array_[location];
}

//  @c1: A chain.
//  @c2: A second chain.
//  @return the concatenation of the two chains.
friend Chain operator+(const Chain &c1, const Chain &c2) {
   // The new_chain's size will be c1's size + c2's size
   size_t new_chain_size = c1.size() + c2.size();
   // A new_chain created to hold the concatenated two chains
   Chain<Object> new_chain;
   new_chain.size_ = new_chain_size;
   new_chain.array_ = new Object[new_chain_size];

   // Copy first chain's elements to new_chain
   for (int i = 0; i < c1.size(); ++i) {
      new_chain.array_[i] = c1.array_[i];
   }

   int curr_position = c1.size();
   // Add the second chain to the back of the first chain
   for (int j = 0; j < c2.size(); ++j) {
      new_chain.array_[curr_position] = c2.array_[j];
      // Increment the curr_position to go to the next index of new_chain
      curr_position++;
   }

   return new_chain;
}

friend Chain operator+(const Chain &some_chain, const Object &ob) {
   Chain<Object> new_chain;
   size_t new_chain_size = some_chain.size()+1;
   // The new_chain's size will be updated
   new_chain.size_ = new_chain_size;
   new_chain.array_ = new Object[new_chain_size];

   // Copy first chain's elements to new_chain
   for (int i = 0; i < some_chain.size(); ++i) {
      new_chain.array_[i] = some_chain.array_[i];
   }
   // Add the object to the back of the first chain
   new_chain.array_[new_chain_size-1] = ob;

   return new_chain;
}

friend std::ostream &operator<<(std::ostream &out, const Chain &a_chain) {
   // Print the chain, formatted with "[]"
   if (a_chain.size() == 0) {
      out << "[]\n";
   } else if (a_chain.size() != 0) {
      std::cout << "[";

      for (int i = 0; i < a_chain.size(); ++i){
         // Add space to the back of each elementst except the last one
         if (i != a_chain.size()-1) {
            out << a_chain.array_[i] << " ";
         } else {
            out << a_chain.array_[i];
         }
      }
      // Add closing bracket
      std::cout << "]\n";
   }

   return out;
}

private:
   size_t size_;
   Object *array_;
};

}  // namespace teaching_project
#endif // CSCI_335_HOMEWORK1_CHAIN_
