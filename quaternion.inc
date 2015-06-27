#macro quat2matx(q1,q2,q3,q4)
  #local Row1=<pow(q4,2)+pow(q1,2)-pow(q2,2)-pow(q3,2),2*(q1*q2+q3*q4),2*(q1*q3-q2*q4)>;
	PrintVector("Row1: ",Row1)
	#local Row2=<2*(q1*q2-q3*q4),pow(q4,2)-pow(q1,2)+pow(q2,2)-pow(q3,2),2*(q2*q3+q1*q4)>;
	PrintVector("Row2: ",Row2)
  #local Row3=<2*(q1*q3+q2*q4),2*(q2*q3-q1*q4),pow(q4,2)-pow(q1,2)-pow(q2,2)+pow(q3,2)>;
	PrintVector("Row3: ",Row3)
#end

#include "KwanMath.inc"

quat2matx(-0.328590,0.716557,-0.536785,0.300727)
