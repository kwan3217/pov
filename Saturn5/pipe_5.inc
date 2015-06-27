union{
#declare Elbow=union{intersection{torus{3.5,0.5} plane{x,0} plane{z,0}}
torus{0.5,0.15 rotate z*90 translate -z*3.5}
torus{0.5,0.15 rotate x*90 translate -x*3.5}
torus{0.5,0.15 rotate x*90 translate -x*3.5 rotate y*-30}
torus{0.5,0.15 rotate x*90 translate -x*3.5 rotate y*-60}
}
cylinder{<0,0,3.5>,<0,0,18.5734>,0.5}
cylinder{<0,0,25.5734>,<0,0,36.5>,0.5}
cylinder{<0,0,18.5734>,<0,0,25.5734>,0.5}
cylinder{<3.5,0,40>,<16.5,0,40>,0.5}
object{Elbow scale <1,1,-1> translate -z*3.5  translate <3.5,0,40>}
cylinder{<20,0,36.5>,<20,0,25.4464>,0.5}
object{Elbow translate x*3.5 rotate y*180 translate <20,0,36.5>}
cylinder{<20,0,18.4464>,<20,0,3.85006>,0.5}
cylinder{<20,0,25.4464>,<20,0,18.4464>,0.5}
cylinder{<20,0,-3.14994>,<20,0,-12.5187>,0.5}
cylinder{<20,0,3.85006>,<20,0,-3.14994>,0.5}
cylinder{<20,0,-19.5187>,<20,0,-34.1726>,0.5}
cylinder{<20,0,-12.5187>,<20,0,-19.5187>,0.5}
cylinder{<20,0,-41.1726>,<20,0,-36.5>,0.5}
cylinder{<20,0,-34.1726>,<20,0,-41.1726>,0.5}
cylinder{<16.5,0,-40>,<8.96626,0,-40>,0.5}
object{Elbow scale <-1,1,1> translate z*3.5  translate <16.5,0,-40>}
cylinder{<5.46626,3.5,-40>,<5.46626,16.5,-40>,0.5}
object{Elbow translate z*3.5 rotate -x*90 translate x*3.5 translate -y*3.5  translate <5.46626,3.5,-40>}
cylinder{<1.96626,20,-40>,<-9.46557,20,-40>,0.5}
object{Elbow translate x*3.5 rotate x*90 rotate -z*90  translate <1.96626,20,-40>}
cylinder{<-16.4656,20,-40>,<-16.5,20,-40>,0.5}
object{Deco[3] scale 0.5 rotate x*360*0.988268 scale <-1,1,1> translate <-16.466,20,-40>texture {Tex[2]}}
cylinder{<-9.46557,20,-40>,<-16.4656,20,-40>,0.5}
object{Deco[6] scale 0.5 rotate x*360*0.105152 scale <-1,1,1> translate <-10.3265,20,-40>texture {Tex[2]}}
cylinder{<-20,16.5,-40>,<-20,-3.80628,-40>,0.5}
object{Deco[0] scale 0.5 rotate x*360*0.939315 rotate z*90*-1 translate <-20,8.23797,-40>texture {Tex[1]}}
object{Elbow translate x*3.5 rotate x*90 translate <-20,16.5,-40>}
cylinder{<-20,-10.8063,-40>,<-20,-16.5,-40>,0.5}
object{Deco[1] scale 0.5 rotate x*360*0.674658 rotate z*90*-1 translate <-20,-10.8566,-40>texture {Tex[1]}}
cylinder{<-20,-3.80628,-40>,<-20,-10.8063,-40>,0.5}
object{Deco[1] scale 0.5 rotate x*360*0.917314 rotate z*90*-1 translate <-20,-6.56445,-40>texture {Tex[0]}}
cylinder{<-16.5,-20,-40>,<-2.43882,-20,-40>,0.5}
object{Deco[4] scale 0.5 rotate x*360*0.00509291 scale <1,1,1> translate <-10.613,-20,-40>texture {Tex[0]}}
object{Elbow rotate -x*90 translate y*3.5  translate <-16.5,-20,-40>}
cylinder{<4.56118,-20,-40>,<15.5059,-20,-40>,0.5}
cylinder{<-2.43882,-20,-40>,<4.56118,-20,-40>,0.5}
cylinder{<22.5059,-20,-40>,<16.5,-20,-40>,0.5}
object{Deco[5] scale 0.5 rotate x*360*0.249079 scale <1,1,1> translate <23.8038,-20,-40>texture {Tex[0]}}
cylinder{<15.5059,-20,-40>,<22.5059,-20,-40>,0.5}
object{Deco[1] scale 0.5 rotate x*360*0.0618606 scale <1,1,1> translate <17.1538,-20,-40>texture {Tex[3]}}
cylinder{<20,-16.5,-40>,<20,-3.95564,-40>,0.5}
object{Deco[5] scale 0.5 rotate x*360*0.745945 rotate z*90*1 translate <20,-11.9317,-40>texture {Tex[2]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> rotate y*-90 translate -x*3.5  translate <20,-16.5,-40>}
cylinder{<16.5,-0.455638,-40>,<6.76553,-0.455638,-40>,0.5}
object{Elbow translate x*3.5 rotate x*90 rotate -z*90  translate <16.5,-0.455638,-40>}
cylinder{<3.26553,3.04436,-40>,<3.26553,16.5,-40>,0.5}
object{Elbow translate z*3.5 rotate -x*90 translate x*3.5 translate -y*3.5  translate <3.26553,3.04436,-40>}
cylinder{<3.26553,20,-36.5>,<3.26553,20,-24.9599>,0.5}
object{Elbow translate z*3.5 rotate -z*90 translate -z*3.5 translate -y*3.5  translate <3.26553,20,-36.5>}
cylinder{<3.26553,20,-17.9599>,<3.26553,20,-5.4613>,0.5}
cylinder{<3.26553,20,-24.9599>,<3.26553,20,-17.9599>,0.5}
cylinder{<-0.234472,20,-1.9613>,<-16.5,20,-1.9613>,0.5}
object{Elbow scale <-1,1,-1> translate -z*3.5  translate <-0.234472,20,-1.9613>}
cylinder{<-20,20,1.5387>,<-20,20,18.8034>,0.5}
object{Elbow translate x*3.5  translate <-20,20,1.5387>}
cylinder{<-16.5,20,22.3034>,<1.83975,20,22.3034>,0.5}
object{Deco[1] scale 0.5 rotate x*360*0.539775 scale <1,1,1> translate <-12.206,20,22.3034>texture {Tex[1]}}
object{Elbow scale <1,1,-1> translate -z*3.5  translate <-16.5,20,22.3034>}
cylinder{<5.33975,20,25.8034>,<5.33975,20,35.8767>,0.5}
object{Elbow rotate y*-90 translate -x*3.5  translate <5.33975,20,25.8034>}
cylinder{<1.83975,20,39.3767>,<-11.8902,20,39.3767>,0.5}
object{Elbow scale <-1,1,-1> translate -z*3.5  translate <1.83975,20,39.3767>}
cylinder{<-15.3902,16.5,39.3767>,<-15.3902,2.40385,39.3767>,0.5}
object{Deco[0] scale 0.5 rotate x*360*0.266903 rotate z*90*-1 translate <-15.3902,11.4226,39.3767>texture {Tex[0]}}
object{Elbow translate x*3.5 rotate x*90 translate <-15.3902,16.5,39.3767>}
cylinder{<-15.3902,-4.59615,39.3767>,<-15.3902,-11.8858,39.3767>,0.5}
cylinder{<-15.3902,2.40385,39.3767>,<-15.3902,-4.59615,39.3767>,0.5}
cylinder{<-11.8902,-15.3858,39.3767>,<8.85396,-15.3858,39.3767>,0.5}
object{Deco[6] scale 0.5 rotate x*360*0.551101 scale <1,1,1> translate <-1.88829,-15.3858,39.3767>texture {Tex[2]}}
object{Elbow rotate -x*90 translate y*3.5  translate <-11.8902,-15.3858,39.3767>}
cylinder{<12.354,-11.8858,39.3767>,<12.354,8.74397,39.3767>,0.5}
object{Deco[5] scale 0.5 rotate x*360*0.681348 rotate z*90*1 translate <12.354,-1.73126,39.3767>texture {Tex[0]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> rotate y*-90 translate -x*3.5  translate <12.354,-11.8858,39.3767>}
cylinder{<12.354,12.244,35.8767>,<12.354,12.244,27.9878>,0.5}
object{Deco[1] scale 0.5 rotate x*360*0.627224 rotate y*90*-1 translate <12.354,12.244,32.2479>texture {Tex[0]}}
object{Elbow rotate y*180 rotate z*90 translate -y*3.5  translate <12.354,12.244,35.8767>}
cylinder{<8.85396,12.244,24.4878>,<-4.19776,12.244,24.4878>,0.5}
object{Deco[2] scale 0.5 rotate x*360*0.246984 scale <-1,1,1> translate <6.39191,12.244,24.4878>texture {Tex[1]}}
object{Elbow scale <-1,1,1> translate z*3.5  translate <8.85396,12.244,24.4878>}
cylinder{<-11.1978,12.244,24.4878>,<-16.5,12.244,24.4878>,0.5}
object{Deco[5] scale 0.5 rotate x*360*0.373519 scale <-1,1,1> translate <-11.9708,12.244,24.4878>texture {Tex[0]}}
cylinder{<-4.19776,12.244,24.4878>,<-11.1978,12.244,24.4878>,0.5}
object{Deco[6] scale 0.5 rotate x*360*0.529362 scale <-1,1,1> translate <-7.37265,12.244,24.4878>texture {Tex[1]}}
cylinder{<-20,8.74397,24.4878>,<-20,-9.50725,24.4878>,0.5}
object{Deco[0] scale 0.5 rotate x*360*0.0583652 rotate z*90*-1 translate <-20,2.82536,24.4878>texture {Tex[2]}}
object{Elbow translate x*3.5 rotate x*90 translate <-20,8.74397,24.4878>}
cylinder{<-20,-13.0073,27.9878>,<-20,-13.0073,36.5>,0.5}
object{Deco[6] scale 0.5 rotate x*360*0.728696 rotate y*90*1 translate <-20,-13.0073,32.2256>texture {Tex[1]}}
object{Elbow rotate y*90 rotate z*90 rotate x*90 translate y*3.5  translate <-20,-13.0073,27.9878>}
cylinder{<-20,-16.5073,40>,<-20,-16.5,40>,0.5}
object{Deco[4] scale 0.5 rotate x*360*0.55334 rotate z*90*-1 translate <-20,-16.5088,40>texture {Tex[1]}}
object{Elbow rotate y*90 rotate -z*90 translate -z*3.5  translate <-20,-16.5073,40>}
cylinder{<-16.5,-20,40>,<3.28126,-20,40>,0.5}
object{Deco[3] scale 0.5 rotate x*360*0.739502 scale <1,1,1> translate <-7.19134,-20,40>texture {Tex[3]}}
object{Elbow rotate -x*90 translate y*3.5  translate <-16.5,-20,40>}
cylinder{<6.78126,-20,36.5>,<6.78126,-20,24.3256>,0.5}
object{Deco[1] scale 0.5 rotate x*360*0.412 rotate y*90*-1 translate <6.78126,-20,33.5253>texture {Tex[1]}}
object{Elbow translate x*3.5 rotate y*180 translate <6.78126,-20,36.5>}
cylinder{<6.78126,-16.5,20.8256>,<6.78126,-6.10867,20.8256>,0.5}
object{Deco[2] scale 0.5 rotate x*360*0.165579 rotate z*90*1 translate <6.78126,-12.7131,20.8256>texture {Tex[2]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*3.5  translate <6.78126,-16.5,20.8256>}
cylinder{<6.78126,0.891325,20.8256>,<6.78126,12.289,20.8256>,0.5}
cylinder{<6.78126,-6.10867,20.8256>,<6.78126,0.891325,20.8256>,0.5}
cylinder{<6.78126,19.289,20.8256>,<6.78126,16.5,20.8256>,0.5}
object{Deco[3] scale 0.5 rotate x*360*0.548369 rotate z*90*1 translate <6.78126,20.1999,20.8256>texture {Tex[2]}}
cylinder{<6.78126,12.289,20.8256>,<6.78126,19.289,20.8256>,0.5}
object{Deco[6] scale 0.5 rotate x*360*0.584164 rotate z*90*1 translate <6.78126,13.6244,20.8256>texture {Tex[2]}}
cylinder{<6.78126,20,24.3256>,<6.78126,20,36.5>,0.5}
object{Deco[6] scale 0.5 rotate x*360*0.689297 rotate y*90*1 translate <6.78126,20,24.8584>texture {Tex[3]}}
object{Elbow translate z*3.5 rotate -z*90 translate -z*3.5 translate -y*3.5  translate <6.78126,20,24.3256>}
cylinder{<10.2813,20,40>,<16.5,20,40>,0.5}
object{Deco[5] scale 0.5 rotate x*360*0.296242 scale <1,1,1> translate <11.5432,20,40>texture {Tex[3]}}
object{Elbow scale <1,1,-1> translate -z*3.5  translate <10.2813,20,40>}
cylinder{<20,20,36.5>,<20,20,22.7784>,0.5}
object{Deco[3] scale 0.5 rotate x*360*0.664628 rotate y*90*-1 translate <20,20,32.1992>texture {Tex[1]}}
object{Elbow translate x*3.5 rotate y*180 translate <20,20,36.5>}
cylinder{<20,20,15.7784>,<20,20,5.73255>,0.5}
object{Deco[0] scale 0.5 rotate x*360*0.0723714 rotate y*90*-1 translate <20,20,11.5039>texture {Tex[0]}}
cylinder{<20,20,22.7784>,<20,20,15.7784>,0.5}
object{Deco[2] scale 0.5 rotate x*360*0.655937 rotate y*90*-1 translate <20,20,21.7704>texture {Tex[0]}}
cylinder{<16.5,20,2.23255>,<4.95924,20,2.23255>,0.5}
object{Elbow scale <-1,1,1> translate z*3.5  translate <16.5,20,2.23255>}
cylinder{<1.45924,16.5,2.23255>,<1.45924,3.16467,2.23255>,0.5}
object{Elbow translate x*3.5 rotate x*90 translate <1.45924,16.5,2.23255>}
cylinder{<1.45924,-0.335333,5.73255>,<1.45924,-0.335333,20.0824>,0.5}
object{Elbow rotate y*90 rotate z*90 rotate x*90 translate y*3.5  translate <1.45924,-0.335333,5.73255>}
}
