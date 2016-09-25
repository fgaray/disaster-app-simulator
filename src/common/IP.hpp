#ifndef _H_IP_H_
#define _H_IP_H_

typedef unsigned char IPByte;

/**
 * Una IPv4
 * */
class IP{
  private:
    IPByte ip0, ip1, ip2, ip3;

  public:
    IP(IPByte _ip0, IPByte _ip1, IPByte _ip2, IPByte _ip3);
    IP();

    IPByte getByte0();
    IPByte getByte1();
    IPByte getByte2();
    IPByte getByte3();

    bool operator==(const IP &other) const;

};


#endif
