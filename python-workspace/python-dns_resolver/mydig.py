import math
from dns import message, query
import datetime as time

root_servers = ['198.41.0.4', '199.9.14.201', '192.33.4.12', '199.7.91.13', '192.203.230.10', '192.5.5.241',
                '192.112.36.4', '198.97.190.53', '192.36.148.17', '192.58.128.30', '193.0.14.129', '199.7.83.42',
                '202.12.27.33']


def get_list(text):
    l, rd = [], []

    for t in text:
        nl = t.to_text().split(" ")
        if nl[-2] != 'AAAA':
            l.append(nl[-1])
            rd.append(nl[-2])

    return l, rd


def request(url, rdtype, servers, index):
    server = servers[index]
    rdtype = rdtype[index]

    try:
        req = message.make_query(url, rdtype=rdtype, rdclass=1)
        rsp = query.udp(req, server, 1)

        return rsp
    except:
        print("Cannot connect current server : " + url)
        request(url=url, rdtype=rdtype, servers=servers, index=index + 1)


def resolve_root(url, rdtype, servers, index):
    try:
        server = servers[index]
        req = message.make_query(url, rdtype, rdclass=1)
        rsp = query.udp(req, server, 1)

        return rsp
    except:
        print("Cannot connect current server : " + url)
        resolve_root(url, rdtype, servers, index + 1)


def resolve(rsp, address):
    while not rsp.answer:
        if rsp.additional:
            servers, rd_list = get_list(rsp.additional)
            try:
                rsp = request(url=address, rdtype=rd_list, servers=servers, index=0)
            except:
                print("Cannot resolve additional data requests.")
                exit(0)
        elif rsp.authority:
            servers, rd_list = get_list(rsp.authority)
            address = servers[0]
            try:
                rsp = request(url=address, rdtype=rd_list, servers=root_servers, index=0)
            except:
                print("Cannot resolve authority data requests.")
                exit(0)
        else:
            print("Cannot resolve authority intermediate requests.")
    return rsp


def run():
    url = input('Enter the url : ')
    url = url + "."

    print('\nQUESTION SECTION:')
    print(url, '\t\tIN A\n')

    start_time = time.datetime.now()
    index = 0

    try:
        rsp = resolve_root(url=url, rdtype=1, servers=root_servers, index=index)
    except:
        print("Cannot connect to root.")
        exit(0)

    address = url

    try:
        rsp = resolve(rsp, address)
        name = rsp.answer[0].name.to_text()
        if name != url:
            ipv4 = rsp.answer[0].to_text().split(" ")[-1]
            req = message.make_query(url, rdtype=1, rdclass=1)
            rsp = query.udp(req, ipv4, 1)
    except:
        print("Cannot be resolved.")
        exit(0)

    if rsp.answer[0].rdtype == 5:
        address = rsp.answer[0].to_text().split(" ")[-1]
        rd_list = [5]
        try:
            rsp = request(url=address, rdtype=rd_list, servers=root_servers, index=0)
            while not rsp.answer:
                if rsp.additional:
                    servers, rd_list = get_list(rsp.additional)
                    try:
                        new_rsp = request(url=address, rdtype=rd_list, servers=servers,
                                          index=0)
                        rsp = new_rsp
                    except:
                        print("Cannot resolve additional data requests.")
                        exit(0)
                elif rsp.authority:
                    name_list, rd_list = get_list(rsp.authority)
                    address = name_list[0]
                    try:
                        rsp = request(url=address, rdtype=rd_list, servers=root_servers,
                                      index=0)
                    except:
                        print("Cannot resolve authority data requests.")
                        exit(0)
                else:
                    print("Cannot resolve CNAME.")
        except:
            print("Cannot resolve CNAME requests.")
            exit(0)

    ipv4 = rsp.answer[0].to_text().split(" ")[-1]

    if rsp.answer[0].rdtype == 2:
        rd_type = 'NS'
    elif rsp.answer[0].rdtype == 5:
        rd_type = 'CNAME'
    elif rsp.answer[0].rdtype == 15:
        rd_type = 'MX'
    else:
        rd_type = 'A'
    final_answer = url + " " + str(rsp.answer[0].ttl) + " IN " + rd_type + ' ' + ipv4

    print('ANSWER SECTION:')
    print(final_answer)

    t = time.datetime.now() - start_time
    print('\nQUERY TIME: ', math.floor(t.microseconds / 1000), ' (ms)')
    print('WHEN: ', time.datetime.now())

run()