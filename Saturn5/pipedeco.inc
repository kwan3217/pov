// ========================================
// Pipe decorations
// by Gilles Tran (c) 1999
// ----------------------------------------
#declare Eye=union{
        torus{4.5,0.5}
        difference{
                sphere{0,4.3}

                box{-5,5 scale <1,1,0.05>}
                box{-5,5 scale <1,1,0.05> translate z}
                box{-5,5 scale <1,1,0.05> translate z*2}
                box{-5,5 scale <1,1,0.05> translate z*3}
                box{-5,5 scale <1,1,0.05> translate z*4}
                box{-5,5 scale <1,1,0.05> translate -z}
                box{-5,5 scale <1,1,0.05> translate -z*2}
                box{-5,5 scale <1,1,0.05> translate -z*3}
                box{-5,5 scale <1,1,0.05> translate -z*4}
                scale <1,0.7,1>
        }

}
#declare Deco[0]=union{
        torus{1,0.5 rotate z*90}
        cylinder{0,x*3,1.5}
        torus{1.5,0.2 rotate z*90 translate x*1.5}
        torus{1,0.5 rotate z*90 translate x*3}
        }
#declare Deco[1]=union{
        superellipsoid{<0.1,0.1> translate x*1 scale 1.2}
        superellipsoid{<0.1,0.1> translate x*1 scale 1.2 translate x*4}
        torus{1.5,0.2 rotate z*90 translate x*2}
        torus{1.5,0.2 rotate z*90 translate x*3}
        }

#declare Deco[2]=union{
        cone{0,1,x*2,2}
        torus{2,0.5 translate x*2.5}
        cone{0,2,x*4,1 translate x*3}
        }
#declare Deco[3]=union{
        cylinder{-0.2*x,0.2*x,1.2}
        torus{1.1,0.1 rotate z*90 scale <2,1,1> translate -x*0.2}
        torus{1.1,0.1 rotate z*90 scale <2,1,1> translate x*0.2}
        union{
                #declare i=0;
                #while (i<360)
                        union{
                                sphere{0,0.1 translate <0.15,1.2,0>}
                                sphere{0,0.1 translate <-0.15,1.2,0> rotate x*10}
                                rotate x*i
                        }
                        #declare i=i+20;
                #end
        }
        translate x*0.2
}

//-----------------------------------------
// Pipe 3 Length=10*x
//-----------------------------------------
#declare Deco[4]=union{
        torus{1.5,1 rotate z*90 translate -x*5}
        cylinder{-x*5,0,2.4}
        cylinder{0,x*5,1}
        torus{2.4,0.1 rotate z*90 translate -x*0.1}
        sphere{0,2.4 scale <1/2.4,1,1>}
        torus{1,0.3 rotate z*90 translate x*5}
        #declare Teta=-90;
        #while (Teta<91)
                union{
                        box{<-5,-1,-0.3>,<-2,0.2,0.3> translate y*2.4}
                        torus{0.5,0.1 translate <-1.5,2.4,0>}
                        torus{0.5,0.1 translate <2.5,2.4,0>}
                        torus{0.5,0.1 translate <2.5,1.5,0>}
                        cylinder{0,2.4*y,0.5 translate x*2.5}
                        sphere{0,0.3 scale <1,0.6,1> translate <-4.5,2.4,0> rotate x*35}
                        sphere{0,0.3 scale <1,0.6,1> translate <-3.5,2.4,0> rotate x*25}
                        sphere{0,0.3 scale <1,0.6,1> translate <-2.5,2.4,0> rotate x*35}
                        sphere{0,0.3 scale <1,0.6,1> translate <-1.5,2.4,0> rotate x*25}
                        sphere{0,0.3 scale <1,0.6,1> translate <-0.5,2.4,0> rotate x*35}
                        intersection{
                                torus{2,0.4 rotate x*90 translate <0.5,2.4,0>}
                                plane{y,2.4 inverse}
                        }
                        rotate x*Teta
                }
                #declare Teta=Teta+60;
        #end
        translate x*5
}
//-----------------------------------------
// Pipe 5
//-----------------------------------------
#declare Deco[5]=union{
        torus{1.5,0.3 rotate z*90 translate -x}
        cylinder{-x,x,1.5}
        superellipsoid{<0.2,0.2> scale <1.5,2,2.5> translate x*2.5}
        object{Eye scale 1.5/7 rotate -x*90 translate <2.5,0,-2.5>}
        object{Eye scale 1.5/7 rotate -x*90 translate <2.5,0,-2.5> scale <1,1,-1>}
        sphere{0,1.5 scale <0.5,1,1> translate x*4}
        union{
                torus{0.5,0.1}
                intersection{torus{2.5,0.5 rotate x*90} plane{y,0 inverse} plane{x,0} translate x*2.5}
                torus{0.5,0.1 translate -x*2.5 rotate z*-30 translate x*2.5 }
                torus{0.5,0.1 translate -x*2.5 rotate z*-60 translate x*2.5 }
                torus{0.5,0.1 translate -x*2.5 rotate z*-90 translate x*2.5 }
                union{
                        cylinder{0,9*x,0.5}
                        sphere{9*x,0.6}
                        cylinder{2*x,5*x,0.7}
                        torus{0.5,0.2 rotate z*90 translate x*2}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*2.3}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*2.6}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*2.9}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*3.2}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*3.5}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*3.8}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*4.1}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*4.4}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*4.7}
                }
                translate <2.5,2,1.7>
        }
        union{
                torus{0.5,0.1}
                intersection{torus{2.5,0.5 rotate x*90} plane{y,0 inverse} plane{x,0} translate x*2.5}
                torus{0.5,0.1 translate -x*2.5 rotate z*-30 translate x*2.5 }
                torus{0.5,0.1 translate -x*2.5 rotate z*-60 translate x*2.5 }
                torus{0.5,0.1 translate -x*2.5 rotate z*-90 translate x*2.5 }
                union{
                        cylinder{0,9*x,0.5}
                        sphere{9*x,0.6}
                        cylinder{3*x,6*x,0.7}
                        sphere{6*x,0.8}
                        torus{0.5,0.2 rotate z*90 translate x*3}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*3.3}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*3.6}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*3.9}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*4.2}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*4.5}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*4.8}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*5.1}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*5.4}
                        torus{0.7,0.2 scale <0.2,1,1> rotate z*90 translate x*5.7}
                        translate <2.5,2.5,0>
                }
                translate <2.5,2,-1.7>
        }
        #declare Teta=0;
        #while (Teta<360)
                union{
                        box{<0,-0.1,-0.05>,<12,0.1,0.05> translate <4,1.2,0>}
                        cylinder{-x,2*x,0.1 translate y*1.5}
                        rotate x*Teta
                }
                #declare Teta=Teta+20;
        #end

        translate x
}


#declare Deco[6]=union{
        torus{1,0.5 rotate z*90}
        cylinder{0,x*3,1.5}
        torus{1.5,0.2 rotate z*90 translate x*1.5}
        torus{1,0.5 rotate z*90 translate x*3}
        }
