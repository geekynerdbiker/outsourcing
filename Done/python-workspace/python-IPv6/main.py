organization_block = input('Input organization block: ').split('/')
subnet_identifier = input('Input subnet identifier: ')
ethernet_address = input('Input Ethernet_address: ').split('-')

organization_block = organization_block[0] + ':'
ipv6 = organization_block + subnet_identifier + ':'

index = 0
for address in ethernet_address:
    if index == 0:
        address = str(hex(int('0x' + address, 16) | 2)).replace('0x', '').upper()
    elif index == 3:
        ipv6 += 'FF:FE'
        # index += 1
    if index != 0 and index % 2 == 0:
        ipv6 += ':'
    ipv6 += address
    index += 1

print('Mapped IPv6 address: ' + ipv6 + '/128')
