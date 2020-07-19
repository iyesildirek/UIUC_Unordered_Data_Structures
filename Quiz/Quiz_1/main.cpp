#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <functional>

int insert(int value, std::vector<int> &table) {
  // Code to insert value into a hashed location in table
  // where table is a vector of length 1000.
  // Returns the number of collisions encountered when
  // trying to insert value into table.

  int hashVal = 0; //key
  int flag = 0; //clear flag 
  int counter = 0; //Number of skips
  
  //Start Hash Function
  if (value >=0 && value < 1000)
  {
	hashVal = value;
  }
  else
  {
	hashVal = value %1000;  
  } 
   //End Hash Function.
   
 //Check if table is empty
  if(table.at(hashVal) == -1)
  {
	table.at(hashVal) = value;
  }
  else
  {
	flag++;
	counter++;
	int loopIndex = 0; //allow to loop back to index 0.
	while (flag)
	{
		loopIndex = hashVal + counter;
		if(loopIndex <1000)
		{
			if(table.at(loopIndex) == -1)
			{
			table.at(loopIndex) = value;
			flag = 0;	
			}
			else 
			{
			counter++;
			}
		}
		// Loop back to index 0 and continue to
		// search for an empty slot.
		else
		{
			hashVal = 0;
			counter = 0;
		}
	}
  }
  return counter;
}

int main() {
  // Prepare some random but distinct values
  constexpr int NUM_VALUES = 999;
  std::vector<int> value(NUM_VALUES);
  int prev_value = 0;
  for (int i = 0; i < NUM_VALUES; i++) {
    prev_value += rand()%25 + 1;
    value[i] = prev_value;
  }

  // Create hash table of size 1000 initialized with -1
  std::vector<int> table(1000,-1);

  // Insert values and track the maximum number of collisions
  int max_hit = 0, max_value = -1;
  for (int i = 0; i < NUM_VALUES; i++) {
    int hit = insert(value[i],table);
    if (hit > max_hit) {
      max_hit = hit;  
      max_value = value[i];
    }
  }

  std::cout << "Inserting value " << max_value << " experienced " << max_hit << " collisions." << std::endl <<std::endl;

  // Print the table contents
  for (int j = 0; j < 1000; j += 10) {
    std::cout << std::setw(3) << j << ":";
    for (int i = 0; i < 10; i++) {
      if (table[j+i] == -1)
        std::cout << "      ";
      else
        std::cout << std::setw(6) << table[j+i];
    }
    std::cout << std::endl;
  }

  return 0;
}
