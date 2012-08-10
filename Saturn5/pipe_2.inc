union{
#declare Elbow=union{intersection{torus{7.5,1.2} plane{x,0} plane{z,0}}
torus{1.2,0.36 rotate z*90 translate -z*7.5}
torus{1.2,0.36 rotate x*90 translate -x*7.5}
torus{1.2,0.36 rotate x*90 translate -x*7.5 rotate y*-30}
torus{1.2,0.36 rotate x*90 translate -x*7.5 rotate y*-60}
}
cylinder{<7.5,0,0>,<12.5,0,0>,1.2}
cylinder{<20,7.5,0>,<20,12.5,0>,1.2}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> rotate y*-90 translate -x*7.5  translate <20,7.5,0>}
cylinder{<20,20,7.5>,<20,20,28.6204>,1.2}
object{Elbow translate z*7.5 rotate -z*90 translate -z*7.5 translate -y*7.5  translate <20,20,7.5>}
cylinder{<20,20,43.6204>,<20,20,32.5>,1.2}
object{Deco[6] scale 1.2 rotate x*360*0.108715 rotate y*90*1 translate <20,20,43.8111>texture {Tex[0]}}
object{Deco[2] scale 1.2 rotate x*360*0.898383 rotate y*90*1 translate <20,20,45.2647>texture {Tex[0]}}
cylinder{<20,20,28.6204>,<20,20,43.6204>,1.2}
object{Deco[1] scale 1.2 rotate x*360*0.07804 rotate y*90*1 translate <20,20,29.7193>texture {Tex[0]}}
object{Deco[0] scale 1.2 rotate x*360*0.388874 rotate y*90*1 translate <20,20,33.7681>texture {Tex[1]}}
cylinder{<20,12.5,40>,<20,-12.5,40>,1.2}
object{Deco[5] scale 1.2 rotate x*360*0.776642 rotate z*90*-1 translate <20,5.16706,40>texture {Tex[0]}}
object{Deco[0] scale 1.2 rotate x*360*0.903849 rotate z*90*-1 translate <20,1.00278,40>texture {Tex[0]}}
object{Elbow rotate y*90 rotate -z*90 translate -z*7.5  translate <20,12.5,40>}
cylinder{<20,-20,32.5>,<20,-20,12.7566>,1.2}
object{Deco[0] scale 1.2 rotate x*360*0.17091 rotate y*90*-1 translate <20,-20,29.8362>texture {Tex[3]}}
object{Deco[3] scale 1.2 rotate x*360*0.289119 rotate y*90*-1 translate <20,-20,23.7145>texture {Tex[2]}}
object{Elbow translate z*7.5 rotate z*90 rotate -x*90 translate <20,-20,32.5>}
cylinder{<20,-20,-2.24344>,<20,-20,-32.5>,1.2}
cylinder{<20,-20,12.7566>,<20,-20,-2.24344>,1.2}
cylinder{<12.5,-20,-40>,<-12.5,-20,-40>,1.2}
object{Deco[2] scale 1.2 rotate x*360*0.871824 scale <-1,1,1> translate <7.21574,-20,-40>texture {Tex[1]}}
object{Deco[6] scale 1.2 rotate x*360*0.896985 scale <-1,1,1> translate <5.35109,-20,-40>texture {Tex[0]}}
object{Elbow scale <-1,1,1> translate z*7.5  translate <12.5,-20,-40>}
cylinder{<-20,-12.5,-40>,<-20,5.14466,-40>,1.2}
object{Deco[5] scale 1.2 rotate x*360*0.0733566 rotate z*90*1 translate <-20,-7.48238,-40>texture {Tex[2]}}
object{Deco[1] scale 1.2 rotate x*360*0.671716 rotate z*90*1 translate <-20,-4.91531,-40>texture {Tex[1]}}
object{Elbow translate z*7.5 rotate -x*90 translate x*7.5 translate -y*7.5  translate <-20,-12.5,-40>}
cylinder{<-12.5,12.6447,-40>,<12.5,12.6447,-40>,1.2}
object{Deco[4] scale 1.2 rotate x*360*0.709103 scale <1,1,1> translate <-8.5218,12.6447,-40>texture {Tex[3]}}
object{Deco[3] scale 1.2 rotate x*360*0.638623 scale <1,1,1> translate <-3.80602,12.6447,-40>texture {Tex[2]}}
object{Elbow translate z*7.5 rotate y*90 rotate x*-90 translate -x*7.5 translate -y*7.5  translate <-12.5,12.6447,-40>}
cylinder{<20,5.14466,-40>,<20,-12.5,-40>,1.2}
object{Deco[4] scale 1.2 rotate x*360*0.382865 rotate z*90*-1 translate <20,5.04285,-40>texture {Tex[1]}}
object{Deco[0] scale 1.2 rotate x*360*0.805667 rotate z*90*-1 translate <20,0.980363,-40>texture {Tex[1]}}
object{Elbow translate x*7.5 rotate x*90 rotate y*180 translate <20,5.14466,-40>}
cylinder{<12.5,-20,-40>,<-12.5,-20,-40>,1.2}
object{Deco[5] scale 1.2 rotate x*360*0.929568 scale <-1,1,1> translate <6.41472,-20,-40>texture {Tex[0]}}
object{Deco[3] scale 1.2 rotate x*360*0.961512 scale <-1,1,1> translate <0.227088,-20,-40>texture {Tex[0]}}
object{Elbow translate z*7.5 rotate y*180 rotate x*90  translate <12.5,-20,-40>}
cylinder{<-20,-20,-32.5>,<-20,-20,10.4471>,1.2}
object{Deco[4] scale 1.2 rotate x*360*0.807609 rotate y*90*1 translate <-20,-20,-26.7233>texture {Tex[3]}}
object{Deco[2] scale 1.2 rotate x*360*0.723139 rotate y*90*1 translate <-20,-20,-12.6758>texture {Tex[0]}}
object{Elbow translate x*7.5  translate <-20,-20,-32.5>}
cylinder{<-12.5,-20,17.9471>,<4.66342,-20,17.9471>,1.2}
object{Deco[5] scale 1.2 rotate x*360*0.452011 scale <1,1,1> translate <-10.2228,-20,17.9471>texture {Tex[0]}}
object{Deco[4] scale 1.2 rotate x*360*0.658485 scale <1,1,1> translate <-4.79629,-20,17.9471>texture {Tex[3]}}
object{Elbow scale <1,1,-1> translate -z*7.5  translate <-12.5,-20,17.9471>}
cylinder{<12.1634,-20,10.4471>,<12.1634,-20,-29.5489>,1.2}
object{Deco[0] scale 1.2 rotate x*360*0.0347505 rotate y*90*-1 translate <12.1634,-20,0.46226>texture {Tex[3]}}
object{Deco[1] scale 1.2 rotate x*360*0.793737 rotate y*90*-1 translate <12.1634,-20,-11.0811>texture {Tex[2]}}
object{Elbow translate x*7.5 rotate y*180 translate <12.1634,-20,10.4471>}
cylinder{<12.1634,-20,-44.5489>,<12.1634,-20,-32.5>,1.2}
object{Deco[4] scale 1.2 rotate x*360*0.231262 rotate y*90*-1 translate <12.1634,-20,-44.8346>texture {Tex[1]}}
object{Deco[5] scale 1.2 rotate x*360*0.652073 rotate y*90*-1 translate <12.1634,-20,-48.214>texture {Tex[1]}}
cylinder{<12.1634,-20,-29.5489>,<12.1634,-20,-44.5489>,1.2}
object{Deco[6] scale 1.2 rotate x*360*0.536897 rotate y*90*-1 translate <12.1634,-20,-30.7204>texture {Tex[0]}}
object{Deco[6] scale 1.2 rotate x*360*0.714825 rotate y*90*-1 translate <12.1634,-20,-32.1572>texture {Tex[0]}}
cylinder{<19.6634,-20,-40>,<12.5,-20,-40>,1.2}
object{Deco[2] scale 1.2 rotate x*360*0.648624 scale <1,1,1> translate <20.8298,-20,-40>texture {Tex[3]}}
object{Deco[2] scale 1.2 rotate x*360*0.898617 scale <1,1,1> translate <22.6933,-20,-40>texture {Tex[0]}}
object{Elbow translate z*7.5  translate <19.6634,-20,-40>}
cylinder{<20,-20,-32.5>,<20,-20,3.31582>,1.2}
object{Deco[2] scale 1.2 rotate x*360*0.728313 rotate y*90*1 translate <20,-20,-30.0819>texture {Tex[3]}}
object{Deco[3] scale 1.2 rotate x*360*0.31775 rotate y*90*1 translate <20,-20,-26.3912>texture {Tex[3]}}
object{Elbow rotate y*-90 translate -x*7.5  translate <20,-20,-32.5>}
cylinder{<20,-12.5,10.8158>,<20,12.5,10.8158>,1.2}
object{Elbow rotate z*90 scale <1,1,-1> translate <20,-12.5,10.8158>}
cylinder{<12.5,20,10.8158>,<-3.15466,20,10.8158>,1.2}
object{Elbow translate x*7.5 rotate x*90 rotate -z*90  translate <12.5,20,10.8158>}
cylinder{<-10.6547,12.5,10.8158>,<-10.6547,-12.5,10.8158>,1.2}
object{Elbow translate x*7.5 rotate x*90 translate <-10.6547,12.5,10.8158>}
cylinder{<-18.1547,-20,10.8158>,<-12.5,-20,10.8158>,1.2}
object{Elbow translate z*7.5 rotate y*180 rotate x*90  translate <-18.1547,-20,10.8158>}
cylinder{<-20,-20,18.3158>,<-20,-20,32.5>,1.2}
object{Elbow translate x*7.5  translate <-20,-20,18.3158>}
cylinder{<-12.5,-20,40>,<12.5,-20,40>,1.2}
object{Deco[5] scale 1.2 rotate x*360*0.0663583 scale <1,1,1> translate <-8.33383,-20,40>texture {Tex[1]}}
object{Deco[5] scale 1.2 rotate x*360*0.508881 scale <1,1,1> translate <-3.13658,-20,40>texture {Tex[1]}}
object{Elbow scale <1,1,-1> translate -z*7.5  translate <-12.5,-20,40>}
cylinder{<20,-20,32.5>,<20,-20,11.5823>,1.2}
object{Deco[5] scale 1.2 rotate x*360*0.330277 rotate y*90*-1 translate <20,-20,27.2871>texture {Tex[3]}}
object{Deco[6] scale 1.2 rotate x*360*0.331666 rotate y*90*-1 translate <20,-20,20.7436>texture {Tex[2]}}
object{Elbow translate x*7.5 rotate y*180 translate <20,-20,32.5>}
cylinder{<20,-20,-3.41774>,<20,-20,-23.726>,1.2}
cylinder{<20,-20,11.5823>,<20,-20,-3.41774>,1.2}
cylinder{<20,-20,-38.726>,<20,-20,-32.5>,1.2}
object{Deco[3] scale 1.2 rotate x*360*0.91206 rotate y*90*-1 translate <20,-20,-40.7982>texture {Tex[3]}}
object{Deco[2] scale 1.2 rotate x*360*0.0817674 rotate y*90*-1 translate <20,-20,-42.5206>texture {Tex[1]}}
cylinder{<20,-20,-23.726>,<20,-20,-38.726>,1.2}
object{Deco[2] scale 1.2 rotate x*360*0.834243 rotate y*90*-1 translate <20,-20,-27.8573>texture {Tex[2]}}
object{Deco[0] scale 1.2 rotate x*360*0.537406 rotate y*90*-1 translate <20,-20,-32.679>texture {Tex[2]}}
cylinder{<20,-12.5,-40>,<20,12.5,-40>,1.2}
object{Deco[0] scale 1.2 rotate x*360*0.0218429 rotate z*90*1 translate <20,-12.13,-40>texture {Tex[3]}}
object{Deco[2] scale 1.2 rotate x*360*0.637672 rotate z*90*1 translate <20,-11.7865,-40>texture {Tex[1]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*7.5  translate <20,-12.5,-40>}
cylinder{<20,20,-32.5>,<20,20,-15.1597>,1.2}
object{Deco[0] scale 1.2 rotate x*360*0.756502 rotate y*90*1 translate <20,20,-28.1798>texture {Tex[1]}}
object{Deco[2] scale 1.2 rotate x*360*0.521775 rotate y*90*1 translate <20,20,-25.3199>texture {Tex[1]}}
object{Elbow translate z*7.5 rotate -z*90 translate -z*7.5 translate -y*7.5  translate <20,20,-32.5>}
cylinder{<20,20,-0.159732>,<20,20,23.1678>,1.2}
cylinder{<20,20,-15.1597>,<20,20,-0.159732>,1.2}
cylinder{<12.5,20,30.6678>,<-12.5,20,30.6678>,1.2}
object{Deco[6] scale 1.2 rotate x*360*0.997559 scale <-1,1,1> translate <6.08716,20,30.6678>texture {Tex[1]}}
object{Deco[5] scale 1.2 rotate x*360*0.561418 scale <-1,1,1> translate <4.66491,20,30.6678>texture {Tex[0]}}
object{Elbow scale <-1,1,-1> translate -z*7.5  translate <12.5,20,30.6678>}
cylinder{<-20,20,23.1678>,<-20,20,-2.11292>,1.2}
object{Deco[2] scale 1.2 rotate x*360*0.725918 rotate y*90*-1 translate <-20,20,14.8485>texture {Tex[3]}}
object{Deco[2] scale 1.2 rotate x*360*0.210189 rotate y*90*-1 translate <-20,20,14.5728>texture {Tex[3]}}
object{Elbow scale <1,1,-1> translate x*7.5  translate <-20,20,23.1678>}
cylinder{<-20,20,-17.1129>,<-20,20,-32.5>,1.2}
cylinder{<-20,20,-2.11292>,<-20,20,-17.1129>,1.2}
cylinder{<-12.5,20,-40>,<12.5,20,-40>,1.2}
object{Deco[3] scale 1.2 rotate x*360*0.392446 scale <1,1,1> translate <-7.13039,20,-40>texture {Tex[3]}}
object{Deco[4] scale 1.2 rotate x*360*0.965169 scale <1,1,1> translate <-4.64403,20,-40>texture {Tex[0]}}
object{Elbow translate z*7.5  translate <-12.5,20,-40>}
cylinder{<20,12.5,-40>,<20,-12.5,-40>,1.2}
object{Deco[6] scale 1.2 rotate x*360*0.353172 rotate z*90*-1 translate <20,11.676,-40>texture {Tex[3]}}
object{Deco[2] scale 1.2 rotate x*360*0.221324 rotate z*90*-1 translate <20,8.8357,-40>texture {Tex[1]}}
object{Elbow translate x*7.5 rotate x*90 rotate y*180 translate <20,12.5,-40>}
cylinder{<20,-20,-32.5>,<20,-20,-11.7905>,1.2}
object{Deco[1] scale 1.2 rotate x*360*0.312966 rotate y*90*1 translate <20,-20,-32.4212>texture {Tex[1]}}
object{Deco[2] scale 1.2 rotate x*360*0.9168 rotate y*90*1 translate <20,-20,-27.5993>texture {Tex[2]}}
object{Elbow rotate y*90 rotate z*90 rotate x*90 translate y*7.5  translate <20,-20,-32.5>}
cylinder{<12.5,-20,-4.29046>,<-12.5,-20,-4.29046>,1.2}
object{Elbow scale <-1,1,-1> translate -z*7.5  translate <12.5,-20,-4.29046>}
cylinder{<-20,-20,-11.7905>,<-20,-20,-32.5>,1.2}
object{Elbow scale <1,1,-1> translate x*7.5  translate <-20,-20,-11.7905>}
cylinder{<-20,-12.5,-40>,<-20,12.5,-40>,1.2}
object{Deco[3] scale 1.2 rotate x*360*0.636215 rotate z*90*1 translate <-20,-10.2042,-40>texture {Tex[3]}}
object{Deco[0] scale 1.2 rotate x*360*0.361935 rotate z*90*1 translate <-20,-9.82997,-40>texture {Tex[2]}}
object{Elbow rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*7.5  translate <-20,-12.5,-40>}
cylinder{<-20,20,-32.5>,<-20,20,1.22375>,1.2}
object{Deco[5] scale 1.2 rotate x*360*0.520636 rotate y*90*1 translate <-20,20,-30.9787>texture {Tex[2]}}
object{Deco[1] scale 1.2 rotate x*360*0.453347 rotate y*90*1 translate <-20,20,-22.1032>texture {Tex[2]}}
object{Elbow translate z*7.5 rotate -z*90 translate -z*7.5 translate -y*7.5  translate <-20,20,-32.5>}
cylinder{<-20,20,16.2238>,<-20,20,32.5>,1.2}
cylinder{<-20,20,1.22375>,<-20,20,16.2238>,1.2}
cylinder{<-12.5,20,40>,<12.5,20,40>,1.2}
object{Deco[4] scale 1.2 rotate x*360*0.337389 scale <1,1,1> translate <-4.36183,20,40>texture {Tex[0]}}
object{Deco[2] scale 1.2 rotate x*360*0.0782498 scale <1,1,1> translate <3.97013,20,40>texture {Tex[2]}}
object{Elbow scale <1,1,-1> translate -z*7.5  translate <-12.5,20,40>}
cylinder{<20,20,32.5>,<20,20,3.88865>,1.2}
object{Deco[6] scale 1.2 rotate x*360*0.935465 rotate y*90*-1 translate <20,20,31.1021>texture {Tex[1]}}
object{Deco[2] scale 1.2 rotate x*360*0.0815008 rotate y*90*-1 translate <20,20,29.7944>texture {Tex[3]}}
object{Elbow translate x*7.5 rotate y*180 translate <20,20,32.5>}
cylinder{<12.5,20,-3.61135>,<-12.5,20,-3.61135>,1.2}
object{Elbow scale <-1,1,1> translate z*7.5  translate <12.5,20,-3.61135>}
cylinder{<-20,12.5,-3.61135>,<-20,-12.5,-3.61135>,1.2}
object{Elbow translate x*7.5 rotate x*90 translate <-20,12.5,-3.61135>}
cylinder{<-12.5,-20,-3.61135>,<12.5,-20,-3.61135>,1.2}
object{Elbow rotate -x*90 translate y*7.5  translate <-12.5,-20,-3.61135>}
cylinder{<20,-20,-11.1113>,<20,-20,-32.5>,1.2}
object{Elbow translate x*7.5 rotate y*180 translate <20,-20,-11.1113>}
cylinder{<12.5,-20,-40>,<-12.5,-20,-40>,1.2}
object{Deco[4] scale 1.2 rotate x*360*0.554925 scale <-1,1,1> translate <10.4772,-20,-40>texture {Tex[0]}}
object{Deco[0] scale 1.2 rotate x*360*0.281664 scale <-1,1,1> translate <3.51039,-20,-40>texture {Tex[1]}}
object{Elbow scale <-1,1,1> translate z*7.5  translate <12.5,-20,-40>}
cylinder{<-20,-12.5,-40>,<-20,12.5,-40>,1.2}
object{Deco[5] scale 1.2 rotate x*360*0.248016 rotate z*90*1 translate <-20,-11.1466,-40>texture {Tex[2]}}
object{Deco[5] scale 1.2 rotate x*360*0.0619544 rotate z*90*1 translate <-20,-8.10447,-40>texture {Tex[2]}}
object{Elbow translate z*7.5 rotate -x*90 translate x*7.5 translate -y*7.5  translate <-20,-12.5,-40>}
}
