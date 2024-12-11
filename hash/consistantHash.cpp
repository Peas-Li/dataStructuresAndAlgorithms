#include <iostream>
#include <string>
#include <set>
#include <list>
#include "md5.h"
#include <map>

using namespace std;

/**
 * 算法步骤：
 *  一致性哈希算法将整个哈希值空间理解成一个环，取值范围是 0 ~ 2^32-1 共 4G 的整数空间；
 *  将所有服务器进行哈希，落在这个一致性哈希环上；
 *  进行负载时，先哈希输入值得到一致性哈希环上的一个哈希值，然后沿着顺时针，遇到的第一台服务器，就是最终负载到的服务器；
 * 
 * 容错性和可扩展性分析：
 *  当遇到某个服务器挂掉后，现存服务器上的缓存不会受到影响，只需要将被挂掉的服务器上的缓存重新映射到其他服务器即可；
 *  当增加一个服务器后，只会影响本该挂载到顺时针转动的下一个服务器的缓存；
 * 
 * 负载不均衡的问题：
 *  因为过少的服务器映射到 hash 环上的距离可能相近，导致缓存都被挂载到其中一小部分服务器上。因此可以
 *  增加虚拟节点，例如每台服务器各增加 100个 虚拟节点，然后映射到 hash 环上，缓存经过 hash 之后沿顺
 *  时针遇到了第一台虚拟节点，那这个虚拟节点对应的真实的主机服务器就是该缓存需要挂载的服务器。
 */

using uint = unsigned int;

class phscialHost;

class virtualHost   //虚拟节点
{
    public:
        virtualHost(string ip, phscialHost *p)
            : _virtualIP(ip)
            , _phscialHost(p)
        {
            _md5 = MD5(_virtualIP).getMD5();
        }

        bool operator<(const virtualHost& host) const 
        {
            return _md5 < host._md5;
        }

        bool operator==(const virtualHost& host) const
        {
            return _md5 == host._md5;
            //return _virtualIP == host._virtualIP;
        }

        uint getMD5() const
        {
            return _md5;
        }

        const phscialHost* getPhscialHost() const
        {
            return _phscialHost;
        }

    private:
        uint _md5; 
        string _virtualIP;
        phscialHost *_phscialHost;
};

class phscialHost   //物理节点
{
    public:
        phscialHost(string ip, int vnumber)
            : _ip(ip)
        {
            for(int i = 0; i < vnumber; i++)
            {
                _virtualHosts.emplace_back(ip + "#" + ::to_string(i), this);
            }
        }

        const string& getIP() const
        {
            return _ip;
        }
        
        const list<virtualHost>& getVirtuaHosts() const
        {
            return _virtualHosts;
        }


    private:
        string _ip;
        list<virtualHost> _virtualHosts;
};

class consistentHash    //一致性 Hash
{
    public:
        void addHost(phscialHost &host)
        {
            auto list = host.getVirtuaHosts();
            for(auto host : list)
            {
                _hashCircle.insert(host);
            }
        }

        void delHost(phscialHost &host)
        {
            auto list = host.getVirtuaHosts();
            for(auto host : list)
            {
                _hashCircle.erase(host);
            }
        }

        string getHost(string clientIp)
        {
            uint md5Val = MD5(clientIp).getMD5();
            for(auto vhost : _hashCircle)
            {
                if(vhost.getMD5() > md5Val)
                {
                    return vhost.getPhscialHost()->getIP();
                }
            }

            return _hashCircle.begin()->getPhscialHost()->getIP();
        }

    private:
        set<virtualHost> _hashCircle;
};

void showConsistentHash(consistentHash& chash)
{
    list<string> ipList{
        "192.168.1.123",
        "192.168.1.12",
        "192.168.1.13",
        "192.168.1.23",
        "192.168.1.54",
        "192.168.1.89",
        "192.168.1.21",
        "192.168.1.27",
        "192.168.1.49",
        "192.168.1.145",
        "192.168.2.34",
        "192.168.6.78",
        "192.168.2.90",
        "192.168.4.5"
    };

    map<string, list<string>> logMap;

    for(auto clientIP : ipList)
    {
        string host = chash.getHost(clientIP);
        logMap[host].emplace_back(clientIP);
    }

    for(auto pair : logMap)
    {
        cout << "物理主机：" << pair.first << endl;
        cout << "客户端：" << endl;
        for(auto ip : pair.second)
        {
            cout << ip << endl;
        }
    }
}

int main()
{
    phscialHost host1("10.117.124.10", 150);
    phscialHost host2("10.117.124.20", 150);
    phscialHost host3("10.117.124.30", 150);

    consistentHash chash;
    chash.addHost(host1);
    chash.addHost(host2);
    chash.addHost(host3);

    showConsistentHash(chash);

    chash.delHost(host1);
    showConsistentHash(chash);
}