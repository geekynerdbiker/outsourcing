import dpkt

sender = '130.245.145.12'
receiver = '128.208.2.198'


class Packet:
    def __init__(self, timestamp, buffer):
        self.src_IP = str(buffer[26]) + '.' + str(buffer[27]) + '.' + str(buffer[28]) + '.' + str(buffer[29])
        self.dst_IP = str(buffer[30]) + '.' + str(buffer[31]) + '.' + str(buffer[32]) + '.' + str(buffer[33])
        self.src_port = int.from_bytes(buffer[34:36], byteorder='big')
        self.dst_port = int.from_bytes(buffer[36:38], byteorder='big')
        self.seq_number = int.from_bytes(buffer[38:42], byteorder='big')
        self.ack_number = int.from_bytes(buffer[42:46], byteorder='big')

        flags_bits = int.from_bytes(buffer[47:48], byteorder='big')
        flags_bits = flags_bits >> 1
        self.syn = flags_bits & 1
        flags_bits = flags_bits >> 3
        self.ack = flags_bits & 1
        self.window_size = int.from_bytes(buffer[48:50], byteorder='big')
        self.window_scale = 16384
        self.mss = buffer[56:58]
        self.size = len(buffer)
        self.timestamp = timestamp


class Connection:
    src_port = dest_port = src_ip = dest_ip = str

    def __init__(self, s, d, s_ip, d_ip):
        self.src_port = s
        self.dest_port = d
        self.src_ip = s_ip
        self.dest_ip = d_ip
        self.packets = []


def calculate_throughput(packets):
    start = end = total_bytes = 0
    for pack in packets:
        if pack.src_IP == sender:
            if start == 0:
                start = pack.timestamp
            else:
                total_bytes += int(pack.size)
                end = pack.timestamp
    time = end - start
    if time != 0:
        throughput = total_bytes / time
    else:
        return None
    return throughput


def check_flow(packets, connections):
    for k in packets:
        for j in range(0, len(connections)):
            if (k.src_port == connections[j].src_port and k.dst_port == connections[j].dest_port) \
                    or (k.src_port == connections[j].dest_port and k.dst_port == connections[j].src_port):
                connections[j].packets.append(k)


def check_SourceDest(packet):
    flag = False
    if packet.src_IP == sender and packet.dst_IP == receiver:
        flag = True
    return flag


def check_DestSource(packet):
    flag = False
    if packet.dst_IP == sender and packet.src_IP == receiver:
        flag = True
    return flag


def calculate_congestion_windows(conns):
    conn_windows = []
    initial_pack = 0
    for y in conns.packets:
        if len(conn_windows) < 3:
            if check_SourceDest(y):
                initial_pack = y.seq_number
            elif check_DestSource(y) and initial_pack - y.ack_number > 0:
                congestion = initial_pack - y.ack_number
                conn_windows.append(congestion)
        else:
            break
    return conn_windows


def first_2_transactions(connections):
    count = sender = 0
    for x in connections.packets:
        if x.src_IP == sender:
            if sender == 0:
                sender += 1
            else:
                while count < 2:
                    if x.seq_number is None or x.ack_number is None or x.window_size is None:
                        print("Failed!")
                    else:
                        print("Sequence number: ", x.seq_number, "|Acknowledgement number: ", x.ack_number,
                              "|Window: ", x.window_size * x.window_scale)
                    count += 1


def triple_duplicate_ack(conns):
    ack1, ack2, ack3 = [], [], []
    for z in conns.packets:
        if check_DestSource(z):
            if z.ack_number in ack1 and z.ack_number not in ack2:
                ack2.append(z.ack_number)
            elif z.ack_number in ack1 and z.ack_number in ack2 and z.ack_number not in ack3:
                ack3.append(z.ack_number)
            else:
                ack1.append(z.ack_number)
        else:
            continue
    trip_ack_loss = len(ack3)
    print("Triple Duplicate Ack retransmissions:", trip_ack_loss)
    print("\n")


tcp_connections = 0
packet_arr, connections_arr = [], []
file = open('assignment2.pcap', 'rb')
pcap_file = dpkt.pcap.Reader(file)
for ts, bf in pcap_file:
    packet = Packet(ts, bf)
    packet_arr.append(packet)

for p in packet_arr:
    if p.ack == 1 and p.syn == 1:
        tcp_connections += 1
        connection = Connection(p.src_port, p.dst_port, p.src_IP, p.dst_IP)
        connections_arr.append(connection)

check_flow(packet_arr, connections_arr)

print('Number of TCP Connections = ', tcp_connections, "\n")
for i in range(len(connections_arr)):
    print("Connection", i + 1)
    print("----------------")
    print("Source Port: ", connections_arr[i].dest_port, "|", "Source IP", connections_arr[i].dest_ip
          , "|", "Destination Port: ", connections_arr[i].src_port, "|", "Destination IP: ",
          connections_arr[i].src_ip)
    print("Sender throughput (bytes over time): ", calculate_throughput(connections_arr[i].packets))
    print("First two transactions: ")
    if first_2_transactions(connections_arr[i]) is None:
        print("")
    else:
        print(first_2_transactions(connections_arr[i]))
    congestion_windows = calculate_congestion_windows(connections_arr[i])
    for j in congestion_windows:
        print("Congestion window: ", j)
    triple_duplicate_ack(connections_arr[i])

file.close()
