import socket
import struct


class DNSQuery:
    def __init__(self, domain, typ, clss):
        self.domain = domain
        self.type = typ
        self.clss = clss

    def __repr__(self):
        return '<DNSQuery domain=\'' + self.domain + '\' type=' + str(self.type) + ' class=' + str(self.clss) + '>'

    def __str__(self):
        return self.__repr__()


class DNSAnswer:
    def __init__(self, domain, typ, clss, ttl, addr):
        self.domain = domain
        self.type = typ
        self.clss = clss
        self.ttl = ttl
        self.addr = addr

    def __repr__(self):
        return '<DNSAnswer domain=\'' + self.domain + '\' type=' + str(self.type) + ' class=' + str(
            self.clss) + ' ttl=' + str(self.ttl) + ' address=' + self.addr + '>'

    def __str__(self):
        return self.__repr__()


def parseDomain(data):
    i = 0
    out = ''
    while i < len(data):
        length = data[i]
        if length == 0:
            break
        length = length + 1
        for x in range(1, length):
            out += chr(data[i + x])
        i = i + length
        out += '.'
    i = i + 1
    return out, i


def parseQuery(data):
    out, i = parseDomain(data)
    others = struct.unpack('HH', data[i:i + 4])
    dnsdata = DNSQuery(out[:-1], socket.ntohs(others[0]), socket.ntohs(others[1]))
    return dnsdata, i + 4


def parseAnswer(data):
    address = ''
    if data[0] == 0xC0:
        address = data[1]
    else:
        address, i = parseDomain(data[1:])
        data = data[i:]

    rheader = data[:12]
    header = struct.unpack('xxHH', rheader[:6])
    header += struct.unpack('LH', rheader[6:])
    addr_len = socket.ntohs(header[3])
    addr = data[12:12 + addr_len]
    if addr_len == 4:
        addr = socket.inet_ntop(socket.AF_INET, addr)
    elif addr_len == 16:
        addr = socket.inet_ntop(socket.AF_INET6, addr)
    else:
        addr = 'no match'
    dns_info = DNSAnswer(address, socket.ntohs(header[0]), socket.ntohs(header[1]), socket.ntohl(header[2]), addr)
    return dns_info, 12 + addr_len


def parseDNS(data):
    dns_header = data[4:8]
    data = data[12:]

    dns_header = struct.unpack('HH', dns_header)
    queries = {}
    answers = []

    i = 0
    for di in range(0, socket.ntohs(dns_header[0])):
        dheader, ofx = parseQuery(data[i:])
        queries[i] = (dheader)
        i = i + ofx

    for di in range(0, socket.ntohs(dns_header[1])):
        dheader, ofx = parseAnswer(data[i:])
        i = i + ofx
        if dheader.domain is not str:
            dheader.domain = queries[dheader.domain - 12].domain
        answers.append(dheader)

    queries = list(queries.values())
    return queries, answers


HOST = socket.gethostbyname(socket.gethostname())
s = socket.socket(socket.AF_INET, socket.SOCK_RAW, socket.IPPROTO_UDP)
s.bind((HOST, 0))
s.setsockopt(socket.IPPROTO_IP, socket.IP_HDRINCL, 1)
s.ioctl(socket.SIO_RCVALL, socket.RCVALL_ON)

n = 1
while (n <= 10):
    data = s.recvfrom(65565)
    packet = data[0]
    address = data[1]
    header = struct.unpack('!BBHHHBBHBBBBBBBB', packet[:20])
    if address[0] != HOST and address[0] != '168.126.63.1':
        continue
    udp_header = struct.unpack('HHHH', packet[20:28])
    if socket.ntohs(udp_header[0]) == 53 or socket.ntohs(udp_header[1]) == 53:
        print('from', address[0])
        try:
            q, a = parseDNS(packet[28:])
            print(q, a)
        except Exception as e:
            print(e)
        n = n + 1

s.close()
