from pytonik_ip_vpn_checker.ip import ip
from tkinter import Tk

pytonik_user = ip()

print(pytonik_user.vpn().ip)
print(pytonik_user.hostname)
print(pytonik_user.city)
print(pytonik_user.region)
print(pytonik_user.country)
print(pytonik_user.loc)
print(pytonik_user.org)
