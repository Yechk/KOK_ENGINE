#include <glm/glm.hpp>
//#include <iostream>
//#include <chrono>

//using namespace std;
//using namespace std::chrono;


glm::mat4 Mut(glm::mat4 op0, glm::mat4 op1)
{
  return op0 * op1;
}

//int main()
//{
//  glm::mat4 test1 = glm::mat4(2.0f);

//  high_resolution_clock::time_point t1 = high_resolution_clock::now();

//  for (long long i = 0; i < 10000000; i++) Mut(test1, test1, test1);

//  high_resolution_clock::time_point t2 = high_resolution_clock::now();

//  auto duration = duration_cast<microseconds>(t2 - t1).count();

//  cout << duration << endl;



//  return 0;
//}
