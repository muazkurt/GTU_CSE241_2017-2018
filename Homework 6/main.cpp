#include "Sources/GTUSetAbstract.cpp"
#include "Sources/GTUSet.cpp"
#include "Sources/GTUMap.cpp"
#include "Sources/GTUGlobal.cpp"
int main(void)
{
    try
    {
        GTU::GTUMap<int, char> a;
        for(int d = 80; d < 100; ++d)
            a.insert(std::make_pair(d,d));
        GTU::GTUMap<int, char> b;
        for(int d = 80; d < 100; ++d)
            b.insert(std::make_pair(d,d));
        b.erase(std::make_pair(80,80));
        GTU::GTUMap<int, char> aat;
        GTU::setIntersection(a,b, aat);
        for(GTU::GTUMap<int, char>::GTUIterator k = aat.begin(); k != aat.end(); ++k)
            std::cout << std::get<0>(*k) << "/ " << std::get<1>(*k) << std::endl;
        a.insert(std::make_pair(80, 80));
    }
    catch (std::bad_pafram)
    {
        std::cout << "Well there seems to be a problem" << std::endl;
    }
    return 0;
}