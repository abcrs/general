#CSCI 1133 Homework 1
#Anthony Ross-Sapienza
#Problem 1D
def absError(actV,meaV):
  absV=round(abs(actV-meaV),6)
  return absV
def relError(actV,meaV):
  absV=abs(actV-meaV)
  relV=round(absV/actV,6)
  return relV
value1=3.2
value2=3.3
absolute=absError(value1,value2)
relative=relError(value1,value2)
