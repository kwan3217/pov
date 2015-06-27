// ========================================
// Example of usage for the mPipe macro
// by Gilles Tran (c) 1999
// ----------------------------------------
// Run the example with -h512 -w384 (vertical format)
// and -UV -UL (if the light buffers make the disk swap like crazy)
// Beware of the possible HIGH number of objects in the scenes (29000)
// ----------------------------------------
#version 3.1;
#include "colors.inc"
#include "metals.inc"
// ----------------------------------------
#declare PdV=<0,100,-400>;
#declare PdA=<-5,0,10>;
camera{location  PdV  direction 2.*z  right 4/3*x up y sky <0,1,0> look_at   PdA}

//-----------------------------------------
// Lamps
//-----------------------------------------
#declare colLum1=rgb<0.5,0.95,1.3>;
#declare colLum2=rgb<1,0.5,0.2>;
light_source{PdV color colLum1*0.5}
#declare LumLampCage=light_source{PdV color colLum1*2 fade_distance 100 fade_power 2}

//-----------------------------------------
// Texture
//-----------------------------------------
#declare txtPipe=texture{T_Chrome_4A}

//-----------------------------------------
// Decorations (need to be declared before)
//-----------------------------------------
#declare nDeco=7;
#declare Deco=array[nDeco]
#include "pipedeco.inc"
//#include "pipedeco0.inc" // (test decorations = spheres)

#declare nTex=4;
#declare Tex=array[nTex]
{texture {T_Chrome_4A},texture {pigment {color Red}},texture {T_Chrome_1A},texture {pigment {color White}}}

//-----------------------------------------
// Pipes
//-----------------------------------------
#declare yCage=20;  // all pipes are contained in a box of same height

//-----------------------------------------
// Uncomment the following lines when you launch it for the first time
//-----------------------------------------

#include "m_pipe.inc"
#declare nPipe=50; // all pipes have the same number of elements

#declare rPipe=1.5;
#declare lPipe=5;
#declare box_container=<yCage,yCage,yCage*2>;
#declare box_hole=box_container*0.3;
#declare Pipe_1=object{mPipe(rPipe,lPipe,nPipe,box_container,box_hole,3,23,true,"pipe_1.inc") }


#declare rPipe=1.2;
#declare lPipe=15;
#declare box_hole=box_container*0.3;
#declare Pipe_2=object{mPipe(rPipe,lPipe,nPipe,box_container,box_hole,2,12,true,"pipe_2.inc") }

#declare rPipe=1;
#declare lPipe=13;
#declare box_hole=box_container*0.3;
#declare Pipe_3=object{mPipe(rPipe,lPipe,nPipe,box_container,box_hole,2,17,true,"pipe_3.inc") }

#declare rPipe=0.6;
#declare lPipe=6;
#declare box_hole=box_container*0.3;
#declare Pipe_4=object{mPipe(rPipe,lPipe,nPipe,box_container,box_hole,1,53,true,"pipe_4.inc") }

#declare rPipe=0.5;
#declare lPipe=7;
#declare box_hole=box_container*0.3;
#declare Pipe_5=object{mPipe(rPipe,lPipe,nPipe,box_container,box_hole,1,54,true,"pipe_5.inc") }


// once the pipes are created, just include the files (no need to call the macro)

#declare Cage=union{
        #include "pipe_1.inc"
        #include "pipe_2.inc"
        #include "pipe_4.inc"
        #include "pipe_5.inc"
        texture{txtPipe}
        }

union{
//        cylinder{-yCage*2*y,y*yCage,25 pigment{colWall}}
        object{LumLampCage translate <-10,yCage*0.5,-35>}
        object{LumLampCage translate <-10,-yCage*0.4,-35>}

        object{Cage}
        object{Cage scale -0.9 rotate y*-90}
        rotate y*-45
}



light_source{<-1400,300,-2000> color colLum2*2}
light_source{<-540,100,-100> color colLum1*3}

