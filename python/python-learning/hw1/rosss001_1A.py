# CSCI 1133 Homework 1
# Anthony Ross-Sapienza
# Problem 1A
def focalLength(obj,im):
  flengthdiv=(1/obj)+(1/im)
  flength=1/flengthdiv
  return flength
print("Welcome to the Focal Length Calculator!")
objIn=float(input("Enter an object distance, in mm: "))
imIn=float(input("Enter an image distance, in mm: "))
focalOut=focalLength(objIn,imIn)
print("Focal Length: "+str(focalOut)+" mm")
