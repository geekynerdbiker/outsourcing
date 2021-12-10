from ortools.linear_solver import pywraplp
import pandas as pd
import S_20210018

df = pd.read_csv("Input_data.csv")
route, distance = S_20210018.p1(df)
print("Solution: ")
print(route)
print("Distane: ")
print(distance)

S_20210018.p2(pywraplp)