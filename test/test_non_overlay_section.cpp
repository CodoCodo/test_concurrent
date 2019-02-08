#include "non_overlay_section_map.hpp"
#include <iostream>
#include <memory>
#include <sstream>
#include "person.h"

static int SimpleTestVal(const NonOverlaySectionMap<int, std::shared_ptr<Person> > & sec_map, int val) {
  NonOverlaySection<int> target_sec;
  std::shared_ptr<Person> p_person;
  if (sec_map.Find(val, &target_sec, &p_person)) {
    std::cout << val << " is in [" << target_sec.lower_bound_ << "," << target_sec.upper_bound_ << ")" << '\t' << *p_person << std::endl;     
  } else {
    std::cout << val << " not found " << std::endl;
  }
  return 0;
}

int TestFind(int argc, char *argv[]) {
  NonOverlaySectionMap<int, std::shared_ptr<Person> > sec_map;
  
  sec_map.InsertSection(NonOverlaySection<int>(1,3), std::make_shared<Person>("tdj", "0015", 30));
  sec_map.InsertSection(NonOverlaySection<int>(2,7), std::make_shared<Person>("lcy", "1990", 14));
  sec_map.InsertSection(NonOverlaySection<int>(9,10), std::make_shared<Person>("hb", "1991", 27));
  sec_map.InsertSection(NonOverlaySection<int>(8,22), std::make_shared<Person>("qy", "1993", 30));

  for (int i = 0; i < 20; ++i) {
    SimpleTestVal(sec_map, i);
  }

  return 0;
}
int main(int argc, char *argv[]) {
  return TestFind(argc, argv);
}
