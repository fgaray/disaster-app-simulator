#include "IP.hpp"

IP::IP(IPByte _ip0, IPByte _ip1, IPByte _ip2, IPByte _ip3){
  this->ip0 = _ip0;
  this->ip1 = _ip1;
  this->ip2 = _ip2;
  this->ip3 = _ip3;
}

IP::IP(){

}

IPByte IP::getByte0(){
  return this->ip0;
}

IPByte IP::getByte1(){
  return this->ip1;
}

IPByte IP::getByte2(){
  return this->ip2;
}

IPByte IP::getByte3(){
  return this->ip3;
}

bool IP::operator==(const IP &other) const{
  return
    other.ip0 == this->ip0 && 
    other.ip1 == this->ip1 &&
    other.ip2 == this->ip2 &&
    other.ip3 == this->ip3;

}
