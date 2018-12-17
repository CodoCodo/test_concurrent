#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

static int test_list_splice(int argc, char *argv[]) {
  list<int> tmp_list = {8, 2, 2, 8, 2, 5, 9, 2};
  list<int> result;
  result.splice(result.begin(), tmp_list, tmp_list.begin());
  return 0;
}

static int test_partition(int argc, char *argv[]) {
  list<int> tmp_list = {8, 2, 2, 8, 2, 5, 9, 2};
  list<int> result;
  result.splice(result.end(), tmp_list, tmp_list.begin());
  result.splice(result.end(), tmp_list, tmp_list.begin());
  const int & pivot = *result.begin();
  auto divide_point = std::partition(tmp_list.begin(), tmp_list.end(), 
                          [&](const int &t) {return t < pivot;}); 

  list<int> lower_part;
  lower_part.splice(lower_part.end(), tmp_list, tmp_list.begin(), divide_point);
  return 0;
}

int main(int argc, char *argv[]) {
  return test_partition(argc, argv);
}

