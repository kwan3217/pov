//Return a unit vector from the center of the Earth towards the center of the Sun
//on the given JD

#macro SunVec(JD)
  PrintNumber("JD:      ",JD)
  #local n=JD-2451545;                                                                             //Days since Epoch
  PrintNumber("n:       ",n)
  #local L=mod(280.460 +0.9856474*n,360);                                                          //Mean lon of Sun (deg)
  PrintNumber("L:       ",L)
  #local g=mod(357.528 +0.9856003*n,360);                                                          //Mean Anomaly (deg)
  PrintNumber("g:       ",g)
  #local Lambda=L+1.915*sin(radians(g))+0.020*sin(radians(2*g));                                   //Ecliptic longitude of Sun from Equation of Center (deg)
  PrintNumber("Lambda:  ",Lambda)
  #local epsilon=23.439 -0.0000004*n;                                                              //Obliquity of axis (deg)
  PrintNumber("epsilon: ",epsilon)
  #local f=180/pi;
  PrintNumber("f:       ",f)
  #local T=pow(tan(epsilon/2*pi/180),2);
  PrintNumber("T:       ",T)
  #local Alpha=Lambda-f*T*sin(2*Lambda*pi/180)+(f/2)*T*T*sin(4*Lambda*pi/180);                      //Right ascension of Sun, (deg)
  PrintNumber("Alpha:   ",Alpha)
  #local delta=asin(sin(epsilon*pi/180)*sin(Lambda*pi/180))*180/pi;                                 //Declination of Sun, (deg)
  PrintNumber("delta:   ",delta)
  #local result=(<cos(Alpha*pi/180)*cos(delta*pi/180),sin(Alpha*pi/180)*cos(delta*pi/180),sin(delta*pi/180)>);
  PrintVector("result: ",result)
  (result)
#end
