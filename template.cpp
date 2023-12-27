#include <iostream>
#include <stdlib>
template <typename T>
void func(T value){
    std::cout << value << std::endl;
} 

int main(){
    std::cout << "test" << std::endl;
    func(5);
    func("kangziwne");
    func(5.5f);
    return 0;
}
