union{
#declare Elbow=union{intersection{torus{6.5,1} plane{x,0} plane{z,0}}
torus{1,0.3 rotate z*90 translate -z*6.5}
torus{1,0.3 rotate x*90 translate -x*6.5}
torus{1,0.3 rotate x*90 translate -x*6.5 rotate y*-30}
torus{1,0.3 rotate x*90 translate -x*6.5 rotate y*-60}
}
cylinder{<-6.5,0,0>,<-13.5,0,0>,1}
cylinder{<-20,6.5,0>,<-20,13.5,0>,1}
object{Elbow translate z*6.5 rotate -x*90 translate x*6.5 translate -y*6.5  translate <-20,6.5,0>}
cylinder{<-13.5,20,0>,<2.74033,20,0>,1}
object{Elbow translate z*6.5 rotate y*90 rotate x*-90 translate -x*6.5 translate -y*6.5  translate <-13.5,20,0>}
cylinder{<15.7403,20,0>,<13.5,20,0>,1}
cylinder{<2.74033,20,0>,<15.7403,20,0>,1}
cylinder{<20,20,6.5>,<20,20,30.1908>,1}
object{Elbow rotate y*-90 translate -x*6.5  translate <20,20,6.5>}
cylinder{<20,13.5,36.6908>,<20,-13.5,36.6908>,1}
object{Deco[0] scale 1 rotate x*360*0.562894 rotate z*90*-1 translate <20,6.35222,36.6908>texture {Tex[0]}}
object{Deco[3] scale 1 rotate x*360*0.982712 rotate z*90*-1 translate <20,2.00186,36.6908>texture {Tex[2]}}
object{Elbow rotate y*90 rotate -z*90 translate -z*6.5  translate <20,13.5,36.6908>}
cylinder{<20,-20,43.1908>,<20,-20,33.5>,1}
object{Deco[2] scale 1 rotate x*360*0.357672 rotate y*90*1 translate <20,-20,44.1191>texture {Tex[0]}}
object{Deco[0] scale 1 rotate x*360*0.258299 rotate y*90*1 translate <20,-20,44.8417>texture {Tex[1]}}
object{Elbow rotate y*90 rotate z*90 rotate x*90 translate y*6.5  translate <20,-20,43.1908>}
cylinder{<13.5,-20,40>,<-13.5,-20,40>,1}
object{Deco[2] scale 1 rotate x*360*0.510278 scale <-1,1,1> translate <5.27303,-20,40>texture {Tex[3]}}
object{Deco[2] scale 1 rotate x*360*0.575631 scale <-1,1,1> translate <0.335619,-20,40>texture {Tex[2]}}
object{Elbow scale <-1,1,-1> translate -z*6.5  translate <13.5,-20,40>}
cylinder{<-20,-13.5,40>,<-20,3.02624,40>,1}
object{Deco[3] scale 1 rotate x*360*0.65673 rotate z*90*1 translate <-20,-9.16643,40>texture {Tex[0]}}
object{Deco[5] scale 1 rotate x*360*0.253619 rotate z*90*1 translate <-20,-7.08688,40>texture {Tex[0]}}
object{Elbow translate z*6.5 rotate -x*90 translate x*6.5 translate -y*6.5  translate <-20,-13.5,40>}
cylinder{<-13.5,9.52624,40>,<13.5,9.52624,40>,1}
object{Deco[0] scale 1 rotate x*360*0.606327 scale <1,1,1> translate <-8.495,9.52624,40>texture {Tex[1]}}
object{Deco[3] scale 1 rotate x*360*0.728805 scale <1,1,1> translate <-5.02059,9.52624,40>texture {Tex[1]}}
object{Elbow translate z*6.5 rotate y*90 rotate x*-90 translate -x*6.5 translate -y*6.5  translate <-13.5,9.52624,40>}
cylinder{<20,3.02624,40>,<20,-13.5,40>,1}
object{Deco[2] scale 1 rotate x*360*0.218162 rotate z*90*-1 translate <20,-0.712255,40>texture {Tex[1]}}
object{Deco[0] scale 1 rotate x*360*0.119055 rotate z*90*-1 translate <20,-1.82536,40>texture {Tex[2]}}
object{Elbow translate x*6.5 rotate x*90 rotate y*180 translate <20,3.02624,40>}
cylinder{<20,-20,33.5>,<20,-20,1.22116>,1}
object{Deco[6] scale 1 rotate x*360*0.33978 rotate y*90*-1 translate <20,-20,25.811>texture {Tex[3]}}
object{Deco[6] scale 1 rotate x*360*0.274669 rotate y*90*-1 translate <20,-20,20.4325>texture {Tex[3]}}
object{Elbow translate z*6.5 rotate z*90 rotate -x*90 translate <20,-20,33.5>}
cylinder{<13.5,-20,-5.27884>,<-13.5,-20,-5.27884>,1}
object{Elbow scale <-1,1,1> translate z*6.5  translate <13.5,-20,-5.27884>}
cylinder{<-20,-20,1.22116>,<-20,-20,16.8191>,1}
object{Elbow translate x*6.5  translate <-20,-20,1.22116>}
cylinder{<-13.5,-20,23.3191>,<7.45363,-20,23.3191>,1}
object{Deco[6] scale 1 rotate x*360*0.729408 scale <1,1,1> translate <-8.44233,-20,23.3191>texture {Tex[0]}}
object{Deco[4] scale 1 rotate x*360*0.501654 scale <1,1,1> translate <-2.28827,-20,23.3191>texture {Tex[3]}}
object{Elbow scale <1,1,-1> translate -z*6.5  translate <-13.5,-20,23.3191>}
cylinder{<13.9536,-20,16.8191>,<13.9536,-20,3.01754>,1}
object{Deco[3] scale 1 rotate x*360*0.492103 rotate y*90*-1 translate <13.9536,-20,14.8881>texture {Tex[0]}}
object{Deco[1] scale 1 rotate x*360*0.59535 rotate y*90*-1 translate <13.9536,-20,12.0296>texture {Tex[2]}}
object{Elbow translate x*6.5 rotate y*180 translate <13.9536,-20,16.8191>}
cylinder{<13.9536,-20,-9.98246>,<13.9536,-20,-33.5>,1}
cylinder{<13.9536,-20,3.01754>,<13.9536,-20,-9.98246>,1}
cylinder{<13.9536,-13.5,-40>,<13.9536,13.5,-40>,1}
object{Deco[6] scale 1 rotate x*360*0.00314486 rotate z*90*1 translate <13.9536,-5.34451,-40>texture {Tex[1]}}
object{Deco[6] scale 1 rotate x*360*0.697955 rotate z*90*1 translate <13.9536,-5.00728,-40>texture {Tex[2]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*6.5  translate <13.9536,-13.5,-40>}
cylinder{<7.45363,20,-40>,<-13.5,20,-40>,1}
object{Deco[3] scale 1 rotate x*360*0.454235 scale <-1,1,1> translate <1.78795,20,-40>texture {Tex[3]}}
object{Deco[4] scale 1 rotate x*360*0.727861 scale <-1,1,1> translate <-4.88354,20,-40>texture {Tex[1]}}
object{Elbow translate x*6.5 rotate x*90 rotate -z*90  translate <7.45363,20,-40>}
cylinder{<-20,13.5,-40>,<-20,-8.3054,-40>,1}
object{Deco[2] scale 1 rotate x*360*0.0599569 rotate z*90*-1 translate <-20,9.73949,-40>texture {Tex[1]}}
object{Deco[2] scale 1 rotate x*360*0.990894 rotate z*90*-1 translate <-20,3.89155,-40>texture {Tex[1]}}
object{Elbow translate x*6.5 rotate x*90 translate <-20,13.5,-40>}
cylinder{<-20,-14.8054,-33.5>,<-20,-14.8054,-17.5906>,1}
object{Deco[0] scale 1 rotate x*360*0.00954144 rotate y*90*1 translate <-20,-14.8054,-31.412>texture {Tex[0]}}
object{Deco[1] scale 1 rotate x*360*0.00320152 rotate y*90*1 translate <-20,-14.8054,-30.998>texture {Tex[0]}}
object{Elbow rotate y*90 rotate z*90 rotate x*90 translate y*6.5  translate <-20,-14.8054,-33.5>}
cylinder{<-20,-14.8054,-4.59057>,<-20,-14.8054,33.5>,1}
cylinder{<-20,-14.8054,-17.5906>,<-20,-14.8054,-4.59057>,1}
cylinder{<-20,-8.3054,40>,<-20,6.44768,40>,1}
object{Deco[6] scale 1 rotate x*360*0.840756 rotate z*90*1 translate <-20,-6.79586,40>texture {Tex[1]}}
object{Deco[2] scale 1 rotate x*360*0.884017 rotate z*90*1 translate <-20,-5.15209,40>texture {Tex[3]}}
object{Elbow rotate z*90 scale <1,1,-1> translate <-20,-8.3054,40>}
cylinder{<-13.5,12.9477,40>,<13.5,12.9477,40>,1}
object{Deco[6] scale 1 rotate x*360*0.983486 scale <1,1,1> translate <-5.72582,12.9477,40>texture {Tex[0]}}
object{Deco[4] scale 1 rotate x*360*0.271371 scale <1,1,1> translate <-1.27761,12.9477,40>texture {Tex[3]}}
object{Elbow translate z*6.5 rotate y*90 rotate x*-90 translate -x*6.5 translate -y*6.5  translate <-13.5,12.9477,40>}
cylinder{<20,12.9477,33.5>,<20,12.9477,-3.34625>,1}
object{Deco[2] scale 1 rotate x*360*0.762085 rotate y*90*-1 translate <20,12.9477,23.2832>texture {Tex[2]}}
object{Deco[5] scale 1 rotate x*360*0.604786 rotate y*90*-1 translate <20,12.9477,21.764>texture {Tex[3]}}
object{Elbow translate x*6.5 rotate y*180 translate <20,12.9477,33.5>}
cylinder{<20,12.9477,-16.3463>,<20,12.9477,-33.5>,1}
cylinder{<20,12.9477,-3.34625>,<20,12.9477,-16.3463>,1}
cylinder{<20,6.44768,-40>,<20,-13.5,-40>,1}
object{Deco[2] scale 1 rotate x*360*0.450438 rotate z*90*-1 translate <20,1.70983,-40>texture {Tex[0]}}
object{Deco[1] scale 1 rotate x*360*0.286446 rotate z*90*-1 translate <20,-4.29209,-40>texture {Tex[3]}}
object{Elbow translate z*6.5 rotate -z*90 translate <20,6.44768,-40>}
cylinder{<13.5,-20,-40>,<-13.5,-20,-40>,1}
object{Deco[6] scale 1 rotate x*360*0.264104 scale <-1,1,1> translate <12.5724,-20,-40>texture {Tex[0]}}
object{Deco[4] scale 1 rotate x*360*0.188479 scale <-1,1,1> translate <7.87008,-20,-40>texture {Tex[3]}}
object{Elbow translate z*6.5 rotate y*180 rotate x*90  translate <13.5,-20,-40>}
cylinder{<-20,-20,-33.5>,<-20,-20,-14.6139>,1}
object{Deco[6] scale 1 rotate x*360*0.101661 rotate y*90*1 translate <-20,-20,-30.3736>texture {Tex[3]}}
object{Deco[0] scale 1 rotate x*360*0.923728 rotate y*90*1 translate <-20,-20,-26.3151>texture {Tex[1]}}
object{Elbow translate x*6.5  translate <-20,-20,-33.5>}
cylinder{<-20,-13.5,-8.11386>,<-20,13.5,-8.11386>,1}
object{Elbow rotate z*90 scale <1,1,-1> translate <-20,-13.5,-8.11386>}
cylinder{<-13.5,20,-8.11386>,<13.5,20,-8.11386>,1}
object{Elbow translate z*6.5 rotate y*90 rotate x*-90 translate -x*6.5 translate -y*6.5  translate <-13.5,20,-8.11386>}
cylinder{<20,13.5,-8.11386>,<20,-13.5,-8.11386>,1}
object{Elbow translate x*6.5 rotate x*90 rotate y*180 translate <20,13.5,-8.11386>}
cylinder{<20,-20,-14.6139>,<20,-20,-33.5>,1}
object{Elbow translate z*6.5 rotate z*90 rotate -x*90 translate <20,-20,-14.6139>}
cylinder{<20,-13.5,-40>,<20,13.5,-40>,1}
object{Deco[1] scale 1 rotate x*360*0.645716 rotate z*90*1 translate <20,-13.2367,-40>texture {Tex[0]}}
object{Deco[5] scale 1 rotate x*360*0.999756 rotate z*90*1 translate <20,-7.63017,-40>texture {Tex[3]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*6.5  translate <20,-13.5,-40>}
cylinder{<13.5,20,-40>,<-13.5,20,-40>,1}
object{Deco[1] scale 1 rotate x*360*0.866214 scale <-1,1,1> translate <6.19036,20,-40>texture {Tex[2]}}
object{Deco[4] scale 1 rotate x*360*0.688373 scale <-1,1,1> translate <-0.921508,20,-40>texture {Tex[3]}}
object{Elbow translate x*6.5 rotate x*90 rotate -z*90  translate <13.5,20,-40>}
cylinder{<-20,20,-33.5>,<-20,20,-17.4314>,1}
object{Deco[0] scale 1 rotate x*360*0.792684 rotate y*90*1 translate <-20,20,-30.775>texture {Tex[1]}}
object{Deco[1] scale 1 rotate x*360*0.27446 rotate y*90*1 translate <-20,20,-25.7335>texture {Tex[1]}}
object{Elbow translate x*6.5  translate <-20,20,-33.5>}
cylinder{<-13.5,20,-10.9314>,<10.9863,20,-10.9314>,1}
object{Elbow scale <1,1,-1> translate -z*6.5  translate <-13.5,20,-10.9314>}
cylinder{<17.4863,20,-17.4314>,<17.4863,20,-33.5>,1}
object{Elbow translate x*6.5 rotate y*180 translate <17.4863,20,-17.4314>}
cylinder{<10.9863,20,-40>,<-13.5,20,-40>,1}
object{Deco[0] scale 1 rotate x*360*0.779447 scale <-1,1,1> translate <5.76529,20,-40>texture {Tex[0]}}
object{Deco[4] scale 1 rotate x*360*0.862908 scale <-1,1,1> translate <1.56802,20,-40>texture {Tex[2]}}
object{Elbow scale <-1,1,1> translate z*6.5  translate <10.9863,20,-40>}
cylinder{<-20,20,-33.5>,<-20,20,-17.9893>,1}
object{Deco[0] scale 1 rotate x*360*0.613397 rotate y*90*1 translate <-20,20,-32.0726>texture {Tex[3]}}
object{Deco[6] scale 1 rotate x*360*0.123526 rotate y*90*1 translate <-20,20,-29.899>texture {Tex[0]}}
object{Elbow translate x*6.5  translate <-20,20,-33.5>}
cylinder{<-20,20,-4.98925>,<-20,20,26.0477>,1}
cylinder{<-20,20,-17.9893>,<-20,20,-4.98925>,1}
cylinder{<-20,20,39.0477>,<-20,20,33.5>,1}
object{Deco[6] scale 1 rotate x*360*0.259137 rotate y*90*1 translate <-20,20,39.5602>texture {Tex[0]}}
object{Deco[6] scale 1 rotate x*360*0.8467 rotate y*90*1 translate <-20,20,40.6194>texture {Tex[0]}}
cylinder{<-20,20,26.0477>,<-20,20,39.0477>,1}
object{Deco[4] scale 1 rotate x*360*0.387891 rotate y*90*1 translate <-20,20,29.5912>texture {Tex[3]}}
object{Deco[1] scale 1 rotate x*360*0.188483 rotate y*90*1 translate <-20,20,29.8832>texture {Tex[3]}}
cylinder{<-13.5,20,40>,<13.5,20,40>,1}
object{Deco[0] scale 1 rotate x*360*0.671687 scale <1,1,1> translate <-11.6354,20,40>texture {Tex[2]}}
object{Deco[0] scale 1 rotate x*360*0.282245 scale <1,1,1> translate <-4.2406,20,40>texture {Tex[3]}}
object{Elbow scale <1,1,-1> translate -z*6.5  translate <-13.5,20,40>}
cylinder{<20,20,33.5>,<20,20,15.9903>,1}
object{Deco[1] scale 1 rotate x*360*0.507635 rotate y*90*-1 translate <20,20,30.843>texture {Tex[0]}}
object{Deco[4] scale 1 rotate x*360*0.946925 rotate y*90*-1 translate <20,20,26.4818>texture {Tex[1]}}
object{Elbow translate x*6.5 rotate y*180 translate <20,20,33.5>}
cylinder{<20,13.5,9.49029>,<20,-13.5,9.49029>,1}
object{Elbow translate z*6.5 rotate -z*90 translate <20,13.5,9.49029>}
cylinder{<20,-20,2.99029>,<20,-20,-25.1952>,1}
object{Elbow translate z*6.5 rotate z*90 rotate -x*90 translate <20,-20,2.99029>}
cylinder{<20,-13.5,-31.6952>,<20,13.5,-31.6952>,1}
object{Deco[5] scale 1 rotate x*360*0.85734 rotate z*90*1 translate <20,-13.2516,-31.6952>texture {Tex[0]}}
object{Deco[5] scale 1 rotate x*360*0.920497 rotate z*90*1 translate <20,-13.2105,-31.6952>texture {Tex[1]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*6.5  translate <20,-13.5,-31.6952>}
cylinder{<13.5,20,-31.6952>,<-9.18969,20,-31.6952>,1}
object{Deco[1] scale 1 rotate x*360*0.179959 scale <-1,1,1> translate <13.0027,20,-31.6952>texture {Tex[3]}}
object{Deco[1] scale 1 rotate x*360*0.972314 scale <-1,1,1> translate <8.00174,20,-31.6952>texture {Tex[0]}}
object{Elbow translate x*6.5 rotate x*90 rotate -z*90  translate <13.5,20,-31.6952>}
cylinder{<-15.6897,20,-38.1952>,<-15.6897,20,-33.5>,1}
object{Deco[4] scale 1 rotate x*360*0.530016 rotate y*90*-1 translate <-15.6897,20,-39.1688>texture {Tex[3]}}
object{Deco[4] scale 1 rotate x*360*0.438388 rotate y*90*-1 translate <-15.6897,20,-39.7923>texture {Tex[1]}}
object{Elbow scale <1,1,-1> translate x*6.5  translate <-15.6897,20,-38.1952>}
}
