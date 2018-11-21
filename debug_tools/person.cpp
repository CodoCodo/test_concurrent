#include "person.h"
#include "concurrent_common.h"

using namespace std;

#define MEMBER_COPY \
    do { \
        mName = obj.mName; \
        mId = obj.mId; \
        mAge = obj.mAge;\
    } while (0)

#define MEMBER_MOVE \
    do { \
        mName = std::move(obj.mName); \
        mId = std::move(obj.mId); \
        mAge = std::move(obj.mAge); \
    } while (0)

std::ostream &operator<<(std::ostream &os, const Person &obj) {
    os << "Person " << obj.mName << '\t' << obj.mId << '\t' << obj.mAge << '\t';
    return os;
}

Person::Person(){
    CONCURRENT_COMMON_COUT << "构造函数" << endl;   
}

Person::Person(const std::string &name, const std::string &id, const int age)
    :mName(name),
     mId(id),
     mAge(age) {
    CONCURRENT_COMMON_COUT << "带参数构造函数" << endl;   
}

/* 复制构造函数 */
Person::Person(const Person &obj){
    CONCURRENT_COMMON_COUT << "复制构造函数" << endl;   
    MEMBER_COPY;
}

/* 移动构造函数 */
Person::Person(Person &&obj){
    CONCURRENT_COMMON_COUT << "移动构造函数" << endl;   
    MEMBER_MOVE;
}

/* 赋值函数 */
Person & Person::operator=(const Person &obj){
    CONCURRENT_COMMON_COUT << "赋值函数" << endl;   
    MEMBER_COPY;
    return *this;
}

/* 移动赋值函数 */
Person & Person::operator=(const Person &&obj){
    CONCURRENT_COMMON_COUT << "移动赋值函数" << endl;   
    MEMBER_MOVE;
    return *this;
}

Person::~Person() {
    CONCURRENT_COMMON_COUT << "析构函数函数" << endl;   
}
