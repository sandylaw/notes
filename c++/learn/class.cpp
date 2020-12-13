#include <iostream>
class Dog{
    std::string name;
    int weight;
    public:
    Dog();
    void setName(const std::string& dogsName);
    void setWeight(int dogsWeight);
    virtual void print() const;
    void bark() const { std::cout << name << " barks!\n"; }
    virtual ~Dog();

};
Dog::Dog()
{
    std::cout << "A dog has been constructed\n";
}
void Dog::setName(const std::string& dogsName)
{
    name = dogsName;
}
void Dog::setWeight(int dogsWeight)
{
    weight = dogsWeight;
}
void Dog::print() const
{
    std::cout << "Dog is " << name << " and weights " << weight << "kg\n";
}
Dog::~Dog()
{
    std::cout << "Goodbye " << name << "\n";
}
int main()
{
    Dog myDog;
    myDog.setName("Barkley");
    myDog.setWeight(10);
    myDog.print();
    return 0;
}
class OwnedDog : public Dog 
{
    public:
        void setOwner(const std::string& dogsOwner);
        void print() const override;
    private:
        std::string owner;
};

void OwnedDog::setOwner(const std::string& dogsOwner)
{
    owner = dogsOwner;
}

void OwnedDog::print() const
{
    Dog::print(); // 调用基类Dog中的print方法
    // "Dog is <name> and weights <weight>"

    std::cout << "Dog is owned by " << owner << "\n";
    // "Dog is owned by <owner>"
}

