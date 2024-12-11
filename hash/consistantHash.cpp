#include <iostream>
#include <string>
#include <set>
#include <list>
#include "md5.h"
#include <map>

using namespace std;

/**
 * �㷨���裺
 *  һ���Թ�ϣ�㷨��������ϣֵ�ռ�����һ������ȡֵ��Χ�� 0 ~ 2^32-1 �� 4G �������ռ䣻
 *  �����з��������й�ϣ���������һ���Թ�ϣ���ϣ�
 *  ���и���ʱ���ȹ�ϣ����ֵ�õ�һ���Թ�ϣ���ϵ�һ����ϣֵ��Ȼ������˳ʱ�룬�����ĵ�һ̨���������������ո��ص��ķ�������
 * 
 * �ݴ��ԺͿ���չ�Է�����
 *  ������ĳ���������ҵ����ִ�������ϵĻ��治���ܵ�Ӱ�죬ֻ��Ҫ�����ҵ��ķ������ϵĻ�������ӳ�䵽�������������ɣ�
 *  ������һ����������ֻ��Ӱ�챾�ù��ص�˳ʱ��ת������һ���������Ļ��棻
 * 
 * ���ز���������⣺
 *  ��Ϊ���ٵķ�����ӳ�䵽 hash ���ϵľ��������������»��涼�����ص�����һС���ַ������ϡ���˿���
 *  ��������ڵ㣬����ÿ̨������������ 100�� ����ڵ㣬Ȼ��ӳ�䵽 hash ���ϣ����澭�� hash ֮����˳
 *  ʱ�������˵�һ̨����ڵ㣬���������ڵ��Ӧ����ʵ���������������Ǹû�����Ҫ���صķ�������
 */

using uint = unsigned int;

class phscialHost;

class virtualHost   //����ڵ�
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

class phscialHost   //����ڵ�
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

class consistentHash    //һ���� Hash
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
        cout << "����������" << pair.first << endl;
        cout << "�ͻ��ˣ�" << endl;
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