#ifndef _NON_OVERLAY_SECTION_MAP_H
#define _NON_OVERLAY_SECTION_MAP_H

#include <map>
#include <iostream>

// 不重叠区间 [lower_bound_, upper_bound_)
template<typename T>
class NonOverlaySection {
 public:
  T lower_bound_;
  T upper_bound_;

  NonOverlaySection() {
    *this = NonOverlaySection<T>(0, 0);
  }

  NonOverlaySection(T lower_bound, T upper_bound)
    : lower_bound_(lower_bound),
      upper_bound_(upper_bound) {
  }

  bool IsValue() const {
    return lower_bound_ == upper_bound_;
  }

  bool IsOverlayWith(const NonOverlaySection & obj) const {
    return upper_bound_ > obj.lower_bound_ && lower_bound_ < obj.upper_bound_;
  }

  bool operator<(const NonOverlaySection &obj) const {
    if (IsValue() || obj.IsValue()) {
      return upper_bound_ < obj.lower_bound_;
    } else {
      return upper_bound_ <= obj.lower_bound_;
    }
  }
  
  bool operator>(const NonOverlaySection &obj) const {
    return obj < *this;
  }

  bool operator==(const NonOverlaySection &obj) const {
    return obj.lower_bound_ >= lower_bound_ && obj.upper_bound_ <= upper_bound_;
  }
};

template<typename T, typename ValueT>
class NonOverlaySectionMap {
 public:
  // 是否存在重叠的区间
  bool HasOverlaySection(const NonOverlaySection<T> & section) const {
    for (auto &p : section_map_) {
      if (p.first.IsOverlayWith(section)) {
        return true;
      }
    }
    return false;
  }

  // 插入新的区间
  bool InsertSection(const NonOverlaySection<T> & section, const ValueT & val) {
    if (HasOverlaySection(section)) {
      std::cerr << __FILE__ << '\t' << __LINE__ << '\t' << "insert failed." << std::endl;
      return false;
    }
    section_map_.emplace(std::make_pair(section, val));    
    std::cout << "size is " << section_map_.size() << std::endl;
    return true;
  }

  bool Find(const T & value, NonOverlaySection<T> *p_section, ValueT * p_val) const  {
    NonOverlaySection<T> val_sec(value, value);
    auto iter = section_map_.find(val_sec);
    if (iter == section_map_.end()) {
      return false;
    } else {
      if (p_section != nullptr) {
        *p_section = iter->first;
      }
      if (p_val != nullptr) {
        *p_val = iter->second;
      }
      return true;
    }
  }

 private:
  // 寻找值对应的区间以及值
  std::map< NonOverlaySection<T>, ValueT > section_map_;
};

#endif //_NON_OVERLAY_SECTION_MAP_H
