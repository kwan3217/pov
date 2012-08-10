union{
#declare Elbow=union{intersection{torus{2.5,1.5} plane{x,0} plane{z,0}}
torus{1.5,0.45 rotate z*90 translate -z*2.5}
torus{1.5,0.45 rotate x*90 translate -x*2.5}
torus{1.5,0.45 rotate x*90 translate -x*2.5 rotate y*-30}
torus{1.5,0.45 rotate x*90 translate -x*2.5 rotate y*-60}
}
cylinder{<0,0,2.5>,<0,0,16.8939>,1.5}
cylinder{<0,0,21.8939>,<0,0,28.8195>,1.5}
cylinder{<0,0,16.8939>,<0,0,21.8939>,1.5}
cylinder{<0,2.5,31.3195>,<0,13.1962,31.3195>,1.5}
object{Elbow rotate z*90 scale <1,1,-1> translate <0,2.5,31.3195>}
cylinder{<-2.5,15.6962,31.3195>,<-14.3907,15.6962,31.3195>,1.5}
object{Elbow translate x*2.5 rotate x*90 rotate -z*90  translate <-2.5,15.6962,31.3195>}
cylinder{<-16.8907,18.1962,31.3195>,<-16.8907,17.5,31.3195>,1.5}
object{Deco[2] scale 1.5 rotate x*360*0.25162 rotate z*90*1 translate <-16.8907,18.2962,31.3195>texture {Tex[2]}}
object{Deco[1] scale 1.5 rotate x*360*0.560308 rotate z*90*1 translate <-16.8907,18.3443,31.3195>texture {Tex[2]}}
object{Deco[0] scale 1.5 rotate x*360*0.868319 rotate z*90*1 translate <-16.8907,18.5183,31.3195>texture {Tex[1]}}
object{Elbow translate z*2.5 rotate -x*90 translate x*2.5 translate -y*2.5  translate <-16.8907,18.1962,31.3195>}
cylinder{<-16.8907,20,28.8195>,<-16.8907,20,16.612>,1.5}
object{Deco[1] scale 1.5 rotate x*360*0.865764 rotate y*90*-1 translate <-16.8907,20,27.488>texture {Tex[3]}}
object{Deco[5] scale 1.5 rotate x*360*0.0802229 rotate y*90*-1 translate <-16.8907,20,24.8194>texture {Tex[3]}}
object{Deco[0] scale 1.5 rotate x*360*0.401831 rotate y*90*-1 translate <-16.8907,20,22.8757>texture {Tex[1]}}
object{Elbow rotate y*180 rotate z*90 translate -y*2.5  translate <-16.8907,20,28.8195>}
cylinder{<-14.3907,20,14.112>,<-3.59999,20,14.112>,1.5}
object{Deco[4] scale 1.5 rotate x*360*0.0984228 scale <1,1,1> translate <-12.3515,20,14.112>texture {Tex[3]}}
object{Deco[6] scale 1.5 rotate x*360*0.949473 scale <1,1,1> translate <-11.5073,20,14.112>texture {Tex[2]}}
object{Deco[0] scale 1.5 rotate x*360*0.661207 scale <1,1,1> translate <-10.9667,20,14.112>texture {Tex[1]}}
object{Elbow translate z*2.5  translate <-14.3907,20,14.112>}
cylinder{<-1.09999,20,16.612>,<-1.09999,20,26.5059>,1.5}
object{Elbow rotate y*-90 translate -x*2.5  translate <-1.09999,20,16.612>}
cylinder{<-3.59999,20,29.0059>,<-11.8277,20,29.0059>,1.5}
object{Elbow scale <-1,1,-1> translate -z*2.5  translate <-3.59999,20,29.0059>}
cylinder{<-14.3277,20,26.5059>,<-14.3277,20,11.7769>,1.5}
object{Deco[0] scale 1.5 rotate x*360*0.26541 rotate y*90*-1 translate <-14.3277,20,24.3803>texture {Tex[2]}}
object{Deco[6] scale 1.5 rotate x*360*0.797881 rotate y*90*-1 translate <-14.3277,20,20.7978>texture {Tex[2]}}
object{Deco[3] scale 1.5 rotate x*360*0.48097 rotate y*90*-1 translate <-14.3277,20,18.811>texture {Tex[3]}}
object{Elbow scale <1,1,-1> translate x*2.5  translate <-14.3277,20,26.5059>}
cylinder{<-16.8277,20,9.27694>,<-17.5,20,9.27694>,1.5}
object{Elbow scale <-1,1,1> translate z*2.5  translate <-16.8277,20,9.27694>}
cylinder{<-20,20,6.77694>,<-20,20,1.5983>,1.5}
object{Elbow scale <1,1,-1> translate x*2.5  translate <-20,20,6.77694>}
cylinder{<-20,20,-3.4017>,<-20,20,-11.3524>,1.5}
cylinder{<-20,20,1.5983>,<-20,20,-3.4017>,1.5}
cylinder{<-20,20,-16.3524>,<-20,20,-28.4628>,1.5}
object{Deco[2] scale 1.5 rotate x*360*0.296537 rotate y*90*-1 translate <-20,20,-18.7174>texture {Tex[1]}}
object{Deco[4] scale 1.5 rotate x*360*0.613865 rotate y*90*-1 translate <-20,20,-20.0789>texture {Tex[0]}}
object{Deco[4] scale 1.5 rotate x*360*0.776013 rotate y*90*-1 translate <-20,20,-20.473>texture {Tex[0]}}
cylinder{<-20,20,-11.3524>,<-20,20,-16.3524>,1.5}
object{Deco[4] scale 1.5 rotate x*360*0.0360859 rotate y*90*-1 translate <-20,20,-11.8043>texture {Tex[1]}}
object{Deco[0] scale 1.5 rotate x*360*0.277591 rotate y*90*-1 translate <-20,20,-12.7784>texture {Tex[2]}}
object{Deco[3] scale 1.5 rotate x*360*0.984597 rotate y*90*-1 translate <-20,20,-13.4205>texture {Tex[0]}}
cylinder{<-17.5,20,-30.9628>,<-6.82587,20,-30.9628>,1.5}
object{Deco[2] scale 1.5 rotate x*360*0.439209 scale <1,1,1> translate <-15.4101,20,-30.9628>texture {Tex[2]}}
object{Deco[4] scale 1.5 rotate x*360*0.389438 scale <1,1,1> translate <-12.9724,20,-30.9628>texture {Tex[2]}}
object{Deco[2] scale 1.5 rotate x*360*0.225844 scale <1,1,1> translate <-12.3266,20,-30.9628>texture {Tex[2]}}
object{Elbow translate z*2.5  translate <-17.5,20,-30.9628>}
cylinder{<-4.32587,20,-28.4628>,<-4.32587,20,-18.2775>,1.5}
object{Elbow rotate y*-90 translate -x*2.5  translate <-4.32587,20,-28.4628>}
cylinder{<-1.82587,20,-15.7775>,<10.5315,20,-15.7775>,1.5}
object{Elbow scale <1,1,-1> translate -z*2.5  translate <-1.82587,20,-15.7775>}
cylinder{<15.5315,20,-15.7775>,<17.5,20,-15.7775>,1.5}
object{Deco[6] scale 1.5 rotate x*360*0.666962 scale <1,1,1> translate <15.5504,20,-15.7775>texture {Tex[3]}}
object{Deco[5] scale 1.5 rotate x*360*0.0267036 scale <1,1,1> translate <15.6508,20,-15.7775>texture {Tex[2]}}
object{Deco[3] scale 1.5 rotate x*360*0.559593 scale <1,1,1> translate <16.0458,20,-15.7775>texture {Tex[1]}}
cylinder{<10.5315,20,-15.7775>,<15.5315,20,-15.7775>,1.5}
object{Deco[0] scale 1.5 rotate x*360*0.488222 scale <1,1,1> translate <11.453,20,-15.7775>texture {Tex[2]}}
object{Deco[1] scale 1.5 rotate x*360*0.246549 scale <1,1,1> translate <11.9901,20,-15.7775>texture {Tex[2]}}
object{Deco[3] scale 1.5 rotate x*360*0.170272 scale <1,1,1> translate <12.1057,20,-15.7775>texture {Tex[0]}}
cylinder{<20,20,-18.2775>,<20,20,-25.9331>,1.5}
object{Deco[5] scale 1.5 rotate x*360*0.826928 rotate y*90*-1 translate <20,20,-19.764>texture {Tex[0]}}
object{Deco[4] scale 1.5 rotate x*360*0.77943 rotate y*90*-1 translate <20,20,-20.4325>texture {Tex[3]}}
object{Deco[6] scale 1.5 rotate x*360*0.16154 rotate y*90*-1 translate <20,20,-21.7522>texture {Tex[3]}}
object{Elbow translate x*2.5 rotate y*180 translate <20,20,-18.2775>}
cylinder{<20,20,-30.9331>,<20,20,-37.5>,1.5}
object{Deco[5] scale 1.5 rotate x*360*0.996971 rotate y*90*-1 translate <20,20,-31.017>texture {Tex[0]}}
object{Deco[1] scale 1.5 rotate x*360*0.239673 rotate y*90*-1 translate <20,20,-32.2941>texture {Tex[1]}}
object{Deco[1] scale 1.5 rotate x*360*0.566723 rotate y*90*-1 translate <20,20,-32.9031>texture {Tex[1]}}
cylinder{<20,20,-25.9331>,<20,20,-30.9331>,1.5}
object{Deco[1] scale 1.5 rotate x*360*0.318955 rotate y*90*-1 translate <20,20,-26.1755>texture {Tex[1]}}
object{Deco[0] scale 1.5 rotate x*360*0.966265 rotate y*90*-1 translate <20,20,-26.4933>texture {Tex[2]}}
object{Deco[3] scale 1.5 rotate x*360*0.661749 rotate y*90*-1 translate <20,20,-27.6407>texture {Tex[2]}}
cylinder{<20,17.5,-40>,<20,8.81313,-40>,1.5}
object{Deco[5] scale 1.5 rotate x*360*0.701148 rotate z*90*-1 translate <20,17.4943,-40>texture {Tex[3]}}
object{Deco[1] scale 1.5 rotate x*360*0.168509 rotate z*90*-1 translate <20,15.4329,-40>texture {Tex[2]}}
object{Deco[1] scale 1.5 rotate x*360*0.046651 rotate z*90*-1 translate <20,14.9292,-40>texture {Tex[0]}}
object{Elbow translate z*2.5 rotate -z*90 translate <20,17.5,-40>}
cylinder{<17.5,6.31313,-40>,<7.65133,6.31313,-40>,1.5}
object{Deco[1] scale 1.5 rotate x*360*0.546585 scale <-1,1,1> translate <17.2226,6.31313,-40>texture {Tex[1]}}
object{Deco[0] scale 1.5 rotate x*360*0.233336 scale <-1,1,1> translate <15.1438,6.31313,-40>texture {Tex[2]}}
object{Deco[0] scale 1.5 rotate x*360*0.549534 scale <-1,1,1> translate <13.7655,6.31313,-40>texture {Tex[2]}}
object{Elbow translate z*2.5 rotate y*180 rotate x*90  translate <17.5,6.31313,-40>}
cylinder{<2.65133,6.31313,-40>,<-8.57153,6.31313,-40>,1.5}
cylinder{<7.65133,6.31313,-40>,<2.65133,6.31313,-40>,1.5}
cylinder{<-11.0715,8.81313,-40>,<-11.0715,17.5,-40>,1.5}
object{Deco[1] scale 1.5 rotate x*360*0.121144 rotate z*90*1 translate <-11.0715,9.74808,-40>texture {Tex[0]}}
object{Deco[4] scale 1.5 rotate x*360*0.185635 rotate z*90*1 translate <-11.0715,9.82597,-40>texture {Tex[2]}}
object{Deco[2] scale 1.5 rotate x*360*0.463804 rotate z*90*1 translate <-11.0715,11.6141,-40>texture {Tex[3]}}
object{Elbow translate z*2.5 rotate -x*90 translate x*2.5 translate -y*2.5  translate <-11.0715,8.81313,-40>}
cylinder{<-13.5715,20,-40>,<-17.5,20,-40>,1.5}
object{Deco[6] scale 1.5 rotate x*360*0.91578 scale <-1,1,1> translate <-13.9078,20,-40>texture {Tex[2]}}
object{Deco[4] scale 1.5 rotate x*360*0.15678 scale <-1,1,1> translate <-14.6526,20,-40>texture {Tex[3]}}
object{Deco[0] scale 1.5 rotate x*360*0.806535 scale <-1,1,1> translate <-15.1612,20,-40>texture {Tex[2]}}
object{Elbow translate x*2.5 rotate x*90 rotate -z*90  translate <-13.5715,20,-40>}
cylinder{<-20,17.5,-40>,<-20,9.67236,-40>,1.5}
object{Deco[6] scale 1.5 rotate x*360*0.263383 rotate z*90*-1 translate <-20,17.3762,-40>texture {Tex[0]}}
object{Deco[4] scale 1.5 rotate x*360*0.180566 rotate z*90*-1 translate <-20,15.5649,-40>texture {Tex[1]}}
object{Deco[1] scale 1.5 rotate x*360*0.770613 rotate z*90*-1 translate <-20,15.0336,-40>texture {Tex[1]}}
object{Elbow translate x*2.5 rotate x*90 translate <-20,17.5,-40>}
cylinder{<-20,4.67236,-40>,<-20,-8.59976,-40>,1.5}
object{Deco[5] scale 1.5 rotate x*360*0.0851739 rotate z*90*-1 translate <-20,2.92354,-40>texture {Tex[2]}}
object{Deco[6] scale 1.5 rotate x*360*0.181003 rotate z*90*-1 translate <-20,2.63086,-40>texture {Tex[2]}}
object{Deco[4] scale 1.5 rotate x*360*0.587564 rotate z*90*-1 translate <-20,1.97888,-40>texture {Tex[1]}}
cylinder{<-20,9.67236,-40>,<-20,4.67236,-40>,1.5}
object{Deco[5] scale 1.5 rotate x*360*0.487122 rotate z*90*-1 translate <-20,8.54598,-40>texture {Tex[3]}}
object{Deco[4] scale 1.5 rotate x*360*0.529843 rotate z*90*-1 translate <-20,7.77963,-40>texture {Tex[0]}}
object{Deco[4] scale 1.5 rotate x*360*0.638417 rotate z*90*-1 translate <-20,6.68922,-40>texture {Tex[0]}}
cylinder{<-20,-13.5998,-40>,<-20,-17.5,-40>,1.5}
object{Deco[1] scale 1.5 rotate x*360*0.494769 rotate z*90*-1 translate <-20,-13.8013,-40>texture {Tex[1]}}
object{Deco[4] scale 1.5 rotate x*360*0.820556 rotate z*90*-1 translate <-20,-14.6287,-40>texture {Tex[2]}}
object{Deco[1] scale 1.5 rotate x*360*0.78763 rotate z*90*-1 translate <-20,-15.5327,-40>texture {Tex[1]}}
cylinder{<-20,-8.59976,-40>,<-20,-13.5998,-40>,1.5}
object{Deco[5] scale 1.5 rotate x*360*0.965224 rotate z*90*-1 translate <-20,-9.77552,-40>texture {Tex[0]}}
object{Deco[0] scale 1.5 rotate x*360*0.0417477 rotate z*90*-1 translate <-20,-10.4693,-40>texture {Tex[0]}}
object{Deco[6] scale 1.5 rotate x*360*0.224628 rotate z*90*-1 translate <-20,-10.6175,-40>texture {Tex[0]}}
cylinder{<-20,-20,-37.5>,<-20,-20,-30.0344>,1.5}
object{Deco[0] scale 1.5 rotate x*360*0.991438 rotate y*90*1 translate <-20,-20,-36.8721>texture {Tex[1]}}
object{Deco[3] scale 1.5 rotate x*360*0.24086 rotate y*90*1 translate <-20,-20,-35.0679>texture {Tex[3]}}
object{Deco[5] scale 1.5 rotate x*360*0.480649 rotate y*90*1 translate <-20,-20,-34.5291>texture {Tex[3]}}
object{Elbow rotate y*90 rotate z*90 rotate x*90 translate y*2.5  translate <-20,-20,-37.5>}
cylinder{<-20,-17.5,-27.5344>,<-20,-4.84999,-27.5344>,1.5}
object{Deco[6] scale 1.5 rotate x*360*0.301121 rotate z*90*1 translate <-20,-15.9045,-27.5344>texture {Tex[3]}}
object{Deco[1] scale 1.5 rotate x*360*0.856589 rotate z*90*1 translate <-20,-15.4413,-27.5344>texture {Tex[1]}}
object{Deco[6] scale 1.5 rotate x*360*0.372723 rotate z*90*1 translate <-20,-14.6834,-27.5344>texture {Tex[2]}}
object{Elbow rotate z*90 scale <1,1,-1> translate <-20,-17.5,-27.5344>}
cylinder{<-20,0.150014,-27.5344>,<-20,6.49757,-27.5344>,1.5}
cylinder{<-20,-4.84999,-27.5344>,<-20,0.150014,-27.5344>,1.5}
cylinder{<-20,11.4976,-27.5344>,<-20,17.5,-27.5344>,1.5}
object{Deco[5] scale 1.5 rotate x*360*0.471705 rotate z*90*1 translate <-20,12.0281,-27.5344>texture {Tex[3]}}
object{Deco[4] scale 1.5 rotate x*360*0.370509 rotate z*90*1 translate <-20,13.2839,-27.5344>texture {Tex[1]}}
object{Deco[1] scale 1.5 rotate x*360*0.471142 rotate z*90*1 translate <-20,13.6305,-27.5344>texture {Tex[1]}}
cylinder{<-20,6.49757,-27.5344>,<-20,11.4976,-27.5344>,1.5}
object{Deco[4] scale 1.5 rotate x*360*0.0804415 rotate z*90*1 translate <-20,7.73031,-27.5344>texture {Tex[2]}}
object{Deco[3] scale 1.5 rotate x*360*0.647002 rotate z*90*1 translate <-20,7.767,-27.5344>texture {Tex[3]}}
object{Deco[3] scale 1.5 rotate x*360*0.61219 rotate z*90*1 translate <-20,8.58107,-27.5344>texture {Tex[1]}}
cylinder{<-17.5,20,-27.5344>,<-2.85645,20,-27.5344>,1.5}
object{Deco[6] scale 1.5 rotate x*360*0.666027 scale <1,1,1> translate <-14.7957,20,-27.5344>texture {Tex[1]}}
object{Deco[1] scale 1.5 rotate x*360*0.0879939 scale <1,1,1> translate <-11.9549,20,-27.5344>texture {Tex[2]}}
object{Deco[4] scale 1.5 rotate x*360*0.77275 scale <1,1,1> translate <-9.86044,20,-27.5344>texture {Tex[0]}}
object{Elbow translate z*2.5 rotate y*90 rotate x*-90 translate -x*2.5 translate -y*2.5  translate <-17.5,20,-27.5344>}
cylinder{<-0.356446,20,-30.0344>,<-0.356446,20,-37.5>,1.5}
object{Elbow translate x*2.5 rotate y*180 translate <-0.356446,20,-30.0344>}
cylinder{<2.14355,20,-40>,<10.3516,20,-40>,1.5}
object{Elbow translate z*2.5  translate <2.14355,20,-40>}
cylinder{<15.3516,20,-40>,<17.5,20,-40>,1.5}
object{Deco[0] scale 1.5 rotate x*360*0.502267 scale <1,1,1> translate <15.5587,20,-40>texture {Tex[1]}}
object{Deco[4] scale 1.5 rotate x*360*0.875934 scale <1,1,1> translate <15.7646,20,-40>texture {Tex[2]}}
object{Deco[0] scale 1.5 rotate x*360*0.15964 scale <1,1,1> translate <15.9884,20,-40>texture {Tex[3]}}
cylinder{<10.3516,20,-40>,<15.3516,20,-40>,1.5}
object{Deco[2] scale 1.5 rotate x*360*0.91298 scale <1,1,1> translate <11.2323,20,-40>texture {Tex[3]}}
object{Deco[4] scale 1.5 rotate x*360*0.759974 scale <1,1,1> translate <11.4392,20,-40>texture {Tex[2]}}
object{Deco[4] scale 1.5 rotate x*360*0.00863942 scale <1,1,1> translate <12.0699,20,-40>texture {Tex[1]}}
cylinder{<20,20,-37.5>,<20,20,-24.0488>,1.5}
object{Deco[3] scale 1.5 rotate x*360*0.213767 rotate y*90*1 translate <20,20,-35.1486>texture {Tex[0]}}
object{Deco[5] scale 1.5 rotate x*360*0.92056 rotate y*90*1 translate <20,20,-34.546>texture {Tex[3]}}
object{Deco[6] scale 1.5 rotate x*360*0.271783 rotate y*90*1 translate <20,20,-33.4794>texture {Tex[0]}}
object{Elbow rotate y*-90 translate -x*2.5  translate <20,20,-37.5>}
cylinder{<17.5,20,-21.5488>,<10.7386,20,-21.5488>,1.5}
object{Deco[4] scale 1.5 rotate x*360*0.0571332 scale <-1,1,1> translate <16.0316,20,-21.5488>texture {Tex[1]}}
object{Deco[1] scale 1.5 rotate x*360*0.292874 scale <-1,1,1> translate <14.5384,20,-21.5488>texture {Tex[2]}}
object{Deco[0] scale 1.5 rotate x*360*0.264579 scale <-1,1,1> translate <14.0148,20,-21.5488>texture {Tex[2]}}
object{Elbow scale <-1,1,-1> translate -z*2.5  translate <17.5,20,-21.5488>}
cylinder{<5.73856,20,-21.5488>,<-3.81646,20,-21.5488>,1.5}
object{Deco[3] scale 1.5 rotate x*360*0.0255783 scale <-1,1,1> translate <4.34554,20,-21.5488>texture {Tex[0]}}
object{Deco[1] scale 1.5 rotate x*360*0.933647 scale <-1,1,1> translate <4.11839,20,-21.5488>texture {Tex[0]}}
object{Deco[4] scale 1.5 rotate x*360*0.155518 scale <-1,1,1> translate <1.99548,20,-21.5488>texture {Tex[0]}}
cylinder{<10.7386,20,-21.5488>,<5.73856,20,-21.5488>,1.5}
object{Deco[1] scale 1.5 rotate x*360*0.0294019 scale <-1,1,1> translate <9.74649,20,-21.5488>texture {Tex[2]}}
object{Deco[6] scale 1.5 rotate x*360*0.585042 scale <-1,1,1> translate <8.5179,20,-21.5488>texture {Tex[1]}}
object{Deco[2] scale 1.5 rotate x*360*0.270215 scale <-1,1,1> translate <7.84728,20,-21.5488>texture {Tex[2]}}
cylinder{<-8.81646,20,-21.5488>,<-17.5,20,-21.5488>,1.5}
object{Deco[4] scale 1.5 rotate x*360*0.835305 scale <-1,1,1> translate <-9.67821,20,-21.5488>texture {Tex[2]}}
object{Deco[6] scale 1.5 rotate x*360*0.756205 scale <-1,1,1> translate <-10.3119,20,-21.5488>texture {Tex[1]}}
object{Deco[3] scale 1.5 rotate x*360*0.504124 scale <-1,1,1> translate <-11.1478,20,-21.5488>texture {Tex[3]}}
cylinder{<-3.81646,20,-21.5488>,<-8.81646,20,-21.5488>,1.5}
object{Deco[2] scale 1.5 rotate x*360*0.476996 scale <-1,1,1> translate <-4.7184,20,-21.5488>texture {Tex[2]}}
object{Deco[1] scale 1.5 rotate x*360*0.188576 scale <-1,1,1> translate <-5.50635,20,-21.5488>texture {Tex[2]}}
object{Deco[0] scale 1.5 rotate x*360*0.628237 scale <-1,1,1> translate <-6.17503,20,-21.5488>texture {Tex[3]}}
cylinder{<-20,17.5,-21.5488>,<-20,7.44969,-21.5488>,1.5}
object{Deco[3] scale 1.5 rotate x*360*0.541602 rotate z*90*-1 translate <-20,16.3488,-21.5488>texture {Tex[3]}}
object{Deco[3] scale 1.5 rotate x*360*0.876204 rotate z*90*-1 translate <-20,14.4917,-21.5488>texture {Tex[1]}}
object{Deco[2] scale 1.5 rotate x*360*0.521694 rotate z*90*-1 translate <-20,14.1618,-21.5488>texture {Tex[1]}}
object{Elbow translate x*2.5 rotate x*90 translate <-20,17.5,-21.5488>}
cylinder{<-20,2.44969,-21.5488>,<-20,-7.43174,-21.5488>,1.5}
cylinder{<-20,7.44969,-21.5488>,<-20,2.44969,-21.5488>,1.5}
cylinder{<-20,-12.4317,-21.5488>,<-20,-17.5,-21.5488>,1.5}
object{Deco[4] scale 1.5 rotate x*360*0.611537 rotate z*90*-1 translate <-20,-13.6887,-21.5488>texture {Tex[1]}}
object{Deco[0] scale 1.5 rotate x*360*0.373184 rotate z*90*-1 translate <-20,-14.4254,-21.5488>texture {Tex[1]}}
object{Deco[1] scale 1.5 rotate x*360*0.0792099 rotate z*90*-1 translate <-20,-15.0222,-21.5488>texture {Tex[2]}}
cylinder{<-20,-7.43174,-21.5488>,<-20,-12.4317,-21.5488>,1.5}
object{Deco[6] scale 1.5 rotate x*360*0.291225 rotate z*90*-1 translate <-20,-8.00322,-21.5488>texture {Tex[2]}}
object{Deco[2] scale 1.5 rotate x*360*0.998518 rotate z*90*-1 translate <-20,-9.02656,-21.5488>texture {Tex[2]}}
object{Deco[5] scale 1.5 rotate x*360*0.597486 rotate z*90*-1 translate <-20,-10.199,-21.5488>texture {Tex[3]}}
cylinder{<-17.5,-20,-21.5488>,<-8.06557,-20,-21.5488>,1.5}
object{Deco[0] scale 1.5 rotate x*360*0.912492 scale <1,1,1> translate <-15.417,-20,-21.5488>texture {Tex[0]}}
object{Deco[1] scale 1.5 rotate x*360*0.347918 scale <1,1,1> translate <-14.0377,-20,-21.5488>texture {Tex[0]}}
object{Deco[4] scale 1.5 rotate x*360*0.141989 scale <1,1,1> translate <-12.1063,-20,-21.5488>texture {Tex[0]}}
object{Elbow rotate -x*90 translate y*2.5  translate <-17.5,-20,-21.5488>}
cylinder{<-5.56557,-17.5,-21.5488>,<-5.56557,-11.826,-21.5488>,1.5}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> rotate y*-90 translate -x*2.5  translate <-5.56557,-17.5,-21.5488>}
cylinder{<-3.06557,-9.32598,-21.5488>,<11.015,-9.32598,-21.5488>,1.5}
object{Elbow translate z*2.5 rotate y*90 rotate x*-90 translate -x*2.5 translate -y*2.5  translate <-3.06557,-9.32598,-21.5488>}
cylinder{<13.515,-9.32598,-19.0488>,<13.515,-9.32598,-7.1589>,1.5}
object{Deco[4] scale 1.5 rotate x*360*0.134208 rotate y*90*1 translate <13.515,-9.32598,-17.584>texture {Tex[1]}}
object{Deco[4] scale 1.5 rotate x*360*0.663052 rotate y*90*1 translate <13.515,-9.32598,-16.3965>texture {Tex[1]}}
object{Deco[5] scale 1.5 rotate x*360*0.763676 rotate y*90*1 translate <13.515,-9.32598,-13.9797>texture {Tex[0]}}
object{Elbow rotate y*-90 translate -x*2.5  translate <13.515,-9.32598,-19.0488>}
cylinder{<13.515,-6.82598,-4.6589>,<13.515,1.10855,-4.6589>,1.5}
object{Elbow rotate z*90 scale <1,1,-1> translate <13.515,-6.82598,-4.6589>}
cylinder{<11.015,3.60855,-4.6589>,<-1.78265,3.60855,-4.6589>,1.5}
object{Elbow translate x*2.5 rotate x*90 rotate -z*90  translate <11.015,3.60855,-4.6589>}
}
