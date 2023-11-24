# Riley Fink
# 1895647
#
import math

l = float(input("Enter the length of a cube side: "))
h = float(input("Enter the height of a cone: "))
r = float(input("Enter the radius of a cone: "))
print("the volume of the cone is:")
coVol = float(math.pi * (r ** 2) * h / 3)
print(coVol)
cuVol = float(l ** 3)
print("the volume of the cube is:")
print(cuVol)
if coVol > cuVol:
    print("the cone has more volume")
elif coVol < cuVol:
    print("the cube has more volume")
else:
    print("the solids have the same volume")