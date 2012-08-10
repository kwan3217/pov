union{
#declare Elbow=union{intersection{torus{3,0.6} plane{x,0} plane{z,0}}
torus{0.6,0.18 rotate z*90 translate -z*3}
torus{0.6,0.18 rotate x*90 translate -x*3}
torus{0.6,0.18 rotate x*90 translate -x*3 rotate y*-30}
torus{0.6,0.18 rotate x*90 translate -x*3 rotate y*-60}
}
cylinder{<0,3,0>,<0,15.6733,0>,0.6}
cylinder{<0,21.6733,0>,<0,17,0>,0.6}
cylinder{<0,15.6733,0>,<0,21.6733,0>,0.6}
cylinder{<-3,20,0>,<-17,20,0>,0.6}
object{Elbow translate x*3 rotate x*90 rotate -z*90  translate <-3,20,0>}
cylinder{<-20,20,3>,<-20,20,18.7139>,0.6}
object{Elbow translate x*3  translate <-20,20,3>}
cylinder{<-20,20,24.7139>,<-20,20,37>,0.6}
object{Deco[1] scale 0.6 rotate x*360*0.581243 rotate y*90*1 translate <-20,20,28.0764>texture {Tex[3]}}
cylinder{<-20,20,18.7139>,<-20,20,24.7139>,0.6}
object{Deco[0] scale 0.6 rotate x*360*0.577689 rotate y*90*1 translate <-20,20,19.6029>texture {Tex[3]}}
cylinder{<-20,17,40>,<-20,9.97021,40>,0.6}
object{Deco[0] scale 0.6 rotate x*360*0.910799 rotate z*90*-1 translate <-20,13.5697,40>texture {Tex[0]}}
object{Elbow rotate y*90 rotate -z*90 translate -z*3  translate <-20,17,40>}
cylinder{<-17,6.97021,40>,<-1.00687,6.97021,40>,0.6}
object{Deco[2] scale 0.6 rotate x*360*0.317613 scale <1,1,1> translate <-16.7686,6.97021,40>texture {Tex[2]}}
object{Elbow rotate -x*90 translate y*3  translate <-17,6.97021,40>}
cylinder{<4.99313,6.97021,40>,<16.9654,6.97021,40>,0.6}
cylinder{<-1.00687,6.97021,40>,<4.99313,6.97021,40>,0.6}
cylinder{<19.9654,6.97021,37>,<19.9654,6.97021,21.041>,0.6}
object{Deco[4] scale 0.6 rotate x*360*0.683592 rotate y*90*-1 translate <19.9654,6.97021,34.8519>texture {Tex[2]}}
object{Elbow translate x*3 rotate y*180 translate <19.9654,6.97021,37>}
cylinder{<22.9654,6.97021,18.041>,<17,6.97021,18.041>,0.6}
object{Deco[3] scale 0.6 rotate x*360*0.43438 scale <1,1,1> translate <25.3534,6.97021,18.041>texture {Tex[3]}}
object{Elbow translate z*3  translate <22.9654,6.97021,18.041>}
cylinder{<20,6.97021,21.041>,<20,6.97021,29.056>,0.6}
object{Deco[6] scale 0.6 rotate x*360*0.907281 rotate y*90*1 translate <20,6.97021,23.2885>texture {Tex[0]}}
object{Elbow rotate y*-90 translate -x*3  translate <20,6.97021,21.041>}
cylinder{<20,3.97021,32.056>,<20,-2.32386,32.056>,0.6}
object{Deco[5] scale 0.6 rotate x*360*0.959181 rotate z*90*-1 translate <20,2.50357,32.056>texture {Tex[1]}}
object{Elbow rotate y*90 rotate -z*90 translate -z*3  translate <20,3.97021,32.056>}
cylinder{<20,-8.32386,32.056>,<20,-17,32.056>,0.6}
cylinder{<20,-2.32386,32.056>,<20,-8.32386,32.056>,0.6}
cylinder{<17,-20,32.056>,<10.5273,-20,32.056>,0.6}
object{Deco[6] scale 0.6 rotate x*360*0.860364 scale <-1,1,1> translate <14.608,-20,32.056>texture {Tex[2]}}
object{Elbow translate z*3 rotate y*180 rotate x*90  translate <17,-20,32.056>}
cylinder{<7.52727,-20,29.056>,<7.52727,-20,12.0488>,0.6}
object{Deco[4] scale 0.6 rotate x*360*0.324702 rotate y*90*-1 translate <7.52727,-20,26.6764>texture {Tex[2]}}
object{Elbow scale <1,1,-1> translate x*3  translate <7.52727,-20,29.056>}
cylinder{<7.52727,-17,9.04882>,<7.52727,-8.87728,9.04882>,0.6}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*3  translate <7.52727,-17,9.04882>}
cylinder{<4.52727,-5.87728,9.04882>,<-3.88903,-5.87728,9.04882>,0.6}
object{Elbow translate x*3 rotate x*90 rotate -z*90  translate <4.52727,-5.87728,9.04882>}
cylinder{<-9.88903,-5.87728,9.04882>,<-17,-5.87728,9.04882>,0.6}
cylinder{<-3.88903,-5.87728,9.04882>,<-9.88903,-5.87728,9.04882>,0.6}
cylinder{<-20,-8.87728,9.04882>,<-20,-17,9.04882>,0.6}
object{Elbow translate x*3 rotate x*90 translate <-20,-8.87728,9.04882>}
cylinder{<-17,-20,9.04882>,<-1.19418,-20,9.04882>,0.6}
object{Elbow rotate -x*90 translate y*3  translate <-17,-20,9.04882>}
cylinder{<4.80582,-20,9.04882>,<16.0054,-20,9.04882>,0.6}
cylinder{<-1.19418,-20,9.04882>,<4.80582,-20,9.04882>,0.6}
cylinder{<19.0054,-17,9.04882>,<19.0054,-9.23056,9.04882>,0.6}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> rotate y*-90 translate -x*3  translate <19.0054,-17,9.04882>}
cylinder{<19.0054,-3.23056,9.04882>,<19.0054,10.562,9.04882>,0.6}
cylinder{<19.0054,-9.23056,9.04882>,<19.0054,-3.23056,9.04882>,0.6}
cylinder{<19.0054,13.562,6.04882>,<19.0054,13.562,-2.22223>,0.6}
object{Elbow rotate y*180 rotate z*90 translate -y*3  translate <19.0054,13.562,6.04882>}
cylinder{<19.0054,13.562,-8.22223>,<19.0054,13.562,-25.5682>,0.6}
cylinder{<19.0054,13.562,-2.22223>,<19.0054,13.562,-8.22223>,0.6}
cylinder{<19.0054,10.562,-28.5682>,<19.0054,3.35656,-28.5682>,0.6}
object{Deco[6] scale 0.6 rotate x*360*0.229916 rotate z*90*-1 translate <19.0054,10.4883,-28.5682>texture {Tex[3]}}
object{Elbow translate z*3 rotate -z*90 translate <19.0054,10.562,-28.5682>}
cylinder{<19.0054,-2.64344,-28.5682>,<19.0054,-13.176,-28.5682>,0.6}
cylinder{<19.0054,3.35656,-28.5682>,<19.0054,-2.64344,-28.5682>,0.6}
cylinder{<19.0054,-16.176,-31.5682>,<19.0054,-16.176,-37>,0.6}
object{Deco[1] scale 0.6 rotate x*360*0.176073 rotate y*90*-1 translate <19.0054,-16.176,-32.4692>texture {Tex[0]}}
object{Elbow translate z*3 rotate z*90 rotate -x*90 translate <19.0054,-16.176,-31.5682>}
cylinder{<19.0054,-13.176,-40>,<19.0054,-5.87671,-40>,0.6}
object{Deco[0] scale 0.6 rotate x*360*0.740895 rotate z*90*1 translate <19.0054,-11.8396,-40>texture {Tex[0]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*3  translate <19.0054,-13.176,-40>}
cylinder{<19.0054,-2.87671,-37>,<19.0054,-2.87671,-19.2813>,0.6}
object{Elbow translate z*3 rotate -z*90 translate -z*3 translate -y*3  translate <19.0054,-2.87671,-37>}
cylinder{<16.0054,-2.87671,-16.2813>,<6.88585,-2.87671,-16.2813>,0.6}
object{Elbow scale <-1,1,-1> translate -z*3  translate <16.0054,-2.87671,-16.2813>}
cylinder{<3.88585,-2.87671,-19.2813>,<3.88585,-2.87671,-30.3223>,0.6}
object{Elbow scale <1,1,-1> translate x*3  translate <3.88585,-2.87671,-19.2813>}
cylinder{<6.88585,-2.87671,-33.3223>,<17,-2.87671,-33.3223>,0.6}
object{Elbow translate z*3  translate <6.88585,-2.87671,-33.3223>}
cylinder{<20,-2.87671,-30.3223>,<20,-2.87671,-17.65>,0.6}
object{Elbow rotate y*-90 translate -x*3  translate <20,-2.87671,-30.3223>}
cylinder{<17,-2.87671,-14.65>,<10.7798,-2.87671,-14.65>,0.6}
object{Elbow scale <-1,1,-1> translate -z*3  translate <17,-2.87671,-14.65>}
cylinder{<7.77983,-5.87671,-14.65>,<7.77983,-17,-14.65>,0.6}
object{Elbow translate x*3 rotate x*90 translate <7.77983,-5.87671,-14.65>}
cylinder{<7.77983,-20,-17.65>,<7.77983,-20,-29.1279>,0.6}
object{Deco[0] scale 0.6 rotate x*360*0.532324 rotate y*90*-1 translate <7.77983,-20,-18.6802>texture {Tex[1]}}
object{Elbow translate z*3 rotate z*90 rotate -x*90 translate <7.77983,-20,-17.65>}
cylinder{<10.7798,-20,-32.1279>,<17,-20,-32.1279>,0.6}
object{Deco[0] scale 0.6 rotate x*360*0.941633 scale <1,1,1> translate <13.4906,-20,-32.1279>texture {Tex[0]}}
object{Elbow translate z*3  translate <10.7798,-20,-32.1279>}
cylinder{<20,-20,-35.1279>,<20,-20,-37>,0.6}
object{Deco[6] scale 0.6 rotate x*360*0.0620132 rotate y*90*-1 translate <20,-20,-35.8824>texture {Tex[3]}}
object{Elbow translate x*3 rotate y*180 translate <20,-20,-35.1279>}
cylinder{<20,-17,-40>,<20,-9.71678,-40>,0.6}
object{Deco[1] scale 0.6 rotate x*360*0.766759 rotate z*90*1 translate <20,-15.3114,-40>texture {Tex[3]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*3  translate <20,-17,-40>}
cylinder{<20,-6.71678,-37>,<20,-6.71678,-24.762>,0.6}
object{Deco[3] scale 0.6 rotate x*360*0.844841 rotate y*90*1 translate <20,-6.71678,-33.2551>texture {Tex[2]}}
object{Elbow translate z*3 rotate -z*90 translate -z*3 translate -y*3  translate <20,-6.71678,-37>}
cylinder{<20,-6.71678,-18.762>,<20,-6.71678,-12.2008>,0.6}
object{Deco[5] scale 0.6 rotate x*360*0.440733 rotate y*90*1 translate <20,-6.71678,-18.5849>texture {Tex[0]}}
cylinder{<20,-6.71678,-24.762>,<20,-6.71678,-18.762>,0.6}
object{Deco[4] scale 0.6 rotate x*360*0.70634 rotate y*90*1 translate <20,-6.71678,-22.3637>texture {Tex[2]}}
cylinder{<20,-6.71678,-6.20083>,<20,-6.71678,11.5214>,0.6}
cylinder{<20,-6.71678,-12.2008>,<20,-6.71678,-6.20083>,0.6}
cylinder{<20,-3.71678,14.5214>,<20,5.59371,14.5214>,0.6}
object{Deco[0] scale 0.6 rotate x*360*0.588443 rotate z*90*1 translate <20,-2.76131,14.5214>texture {Tex[1]}}
object{Elbow rotate z*90 scale <1,1,-1> translate <20,-3.71678,14.5214>}
cylinder{<20,8.59371,17.5214>,<20,8.59371,27.2796>,0.6}
object{Deco[2] scale 0.6 rotate x*360*0.88054 rotate y*90*1 translate <20,8.59371,18.0149>texture {Tex[3]}}
object{Elbow translate z*3 rotate -z*90 translate -z*3 translate -y*3  translate <20,8.59371,17.5214>}
cylinder{<20,8.59371,33.2796>,<20,8.59371,37>,0.6}
object{Deco[0] scale 0.6 rotate x*360*0.828215 rotate y*90*1 translate <20,8.59371,34.937>texture {Tex[0]}}
cylinder{<20,8.59371,27.2796>,<20,8.59371,33.2796>,0.6}
object{Deco[6] scale 0.6 rotate x*360*0.970049 rotate y*90*1 translate <20,8.59371,28.0111>texture {Tex[0]}}
cylinder{<20,11.5937,40>,<20,17,40>,0.6}
object{Deco[0] scale 0.6 rotate x*360*0.503477 rotate z*90*1 translate <20,11.7958,40>texture {Tex[3]}}
object{Elbow rotate z*90 scale <1,1,-1> translate <20,11.5937,40>}
cylinder{<20,20,37>,<20,20,25.246>,0.6}
object{Deco[5] scale 0.6 rotate x*360*0.287347 rotate y*90*-1 translate <20,20,31.6061>texture {Tex[0]}}
object{Elbow rotate y*180 rotate z*90 translate -y*3  translate <20,20,37>}
cylinder{<20,20,19.246>,<20,20,10.895>,0.6}
object{Deco[4] scale 0.6 rotate x*360*0.757727 rotate y*90*-1 translate <20,20,16.9433>texture {Tex[3]}}
cylinder{<20,20,25.246>,<20,20,19.246>,0.6}
object{Deco[5] scale 0.6 rotate x*360*0.326596 rotate y*90*-1 translate <20,20,24.8056>texture {Tex[3]}}
}
