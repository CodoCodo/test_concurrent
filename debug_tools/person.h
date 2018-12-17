#ifndef _PERSON_H
#define _PERSON_H

#include <string>
#include <iostream>

class Person {
    friend std::ostream &operator<<(std::ostream &os, const Person &obj);
public:
    Person();

    Person(const std::string &name, const std::string &id, const int age);

    /* 复制构造函数 */
    Person(const Person &obj);
    /* 移动构造函数 */
    Person(Person &&obj);

    /* 赋值函数 */
    Person &operator=(const Person &obj);
    /* 移动赋值函数 */
    Person &operator=(const Person &&obj);

    ~Person();

    std::string mName;
    std::string mId;
    int mAge;

    static const std::string description_;
};

#endif /* _PERSON_H */
