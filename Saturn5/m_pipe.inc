// ========================================
// mPipe macro
// by Gilles Tran (c) 1999
// ----------------------------------------
// This macro creates a random pipe in a space defined by a container.
// The full pipe is made up of pipe elements connected by quarter toruses.
// The pipe elements go in the x,y,z,-x,-y,-z direction, like in the
// old Windows screensaver.
// Objects are randomly added along the pipe path to make it more interesting
// rPipe is the pipe radius
// lPipe is the pipe element length
// nPipe is the number of pipe elements (not counting toruses and decorations)
// box_container is the upper left point of the container of the pipe object
//	for instance <100,100,100> defines a box <-1000,-1000,-1000>,<1000,1000,1000>
// box_hole defines the upper left point of the hole where there are no decorations
// 	this is because no decorations are needed where you don't see them
//    set box_hole <0,0,0> if you want decorations everywhere
// nDeco is the max number of decorations to use on a pipe element
// sd is the random seed
// doFile = true creates a file
// fname is the file name
// ----------------------------------------
// Before you use the macro you need to have defined an array of "decorations" named Deco.
// The decoration can be whatever object but the objects are considered to be
// along the x axis and they must be at least larger that a cylinder of rPipe radius
// The decorations are positionned by the mBrochette macro.
// ----------------------------------------
// If you set doFile = true, the macro outputs a file containing a
// union of all the pipe elements and toruses. The Deco[] elements MUST have
// been declared before. This may be practical if you want to have simple
// decorations for test and use more complex decos for the final render.
// ----------------------------------------
#macro mPipe(rPipe,lPipe,nPipe,box_container,box_hole,nDeco,sd,doFile,fname)
#if (doFile=true)
        #warning concat(fname," pipe file creation starts\n")
        #fopen filehandle fname write  // creates the mesh
        #write(filehandle,"union{\n")
#end
#local re=lPipe*0.5; // the torus radius is half the size of the length of the pipe element

#local Elbow=union{
        intersection{torus{re,rPipe} plane{x,0} plane{z,0}}
        torus{rPipe,rPipe*0.3 rotate z*90 translate -z*re}
        torus{rPipe,rPipe*0.3 rotate x*90 translate -x*re}
        torus{rPipe,rPipe*0.3 rotate x*90 translate -x*re rotate y*-30}
        torus{rPipe,rPipe*0.3 rotate x*90 translate -x*re rotate y*-60}
}
#if (doFile=true)
        #write(filehandle,"#declare Elbow=union{intersection{torus{",re,",",rPipe,"} plane{x,0} plane{z,0}}\n")
        #write(filehandle,"torus{",rPipe,",",rPipe*0.3," rotate z*90 translate -z*",re,"}\n")
        #write(filehandle,"torus{",rPipe,",",rPipe*0.3," rotate x*90 translate -x*",re,"}\n")
        #write(filehandle,"torus{",rPipe,",",rPipe*0.3," rotate x*90 translate -x*",re," rotate y*-30}\n")
        #write(filehandle,"torus{",rPipe,",",rPipe*0.3," rotate x*90 translate -x*",re," rotate y*-60}\n")
        #write(filehandle,"}\n")
#end

#local xc=box_container.x;
#local yc=box_container.y;
#local zc=box_container.z;
#local rd=seed(sd);
#local dirP=array[6]
#local dirP[0]=x;
#local dirP[1]=-x;
#local dirP[2]=y;
#local dirP[3]=-y;
#local dirP[4]=z;
#local dirP[5]=-z;
#local posPipe=array[nPipe]
#local dirPipe=array[nPipe]
#local posPipe[0]=<0,0,0>;
union{
#local i=0;
#while (i<nPipe-1)
        #local dirPipe[i]=dirP[int(rand(rd)*6-0.00001)]; // direction is random
        #if (i>0)
                #if (vlength(vnormalize(posPipe[i]-posPipe[i-1])+dirPipe[i])=0)
                        #local dirPipe[i]=-dirPipe[i];
                #end
        #end
        #local lPipetmp=(lPipe+2*re)*(1+rand(rd));
        #local posPipetmp=posPipe[i]+(lPipetmp)*dirPipe[i];
        #local xp=posPipetmp.x;
        #local yp=posPipetmp.y;
        #local zp=posPipetmp.z;
        #if (xp>xc) #local xp=xc; #end
        #if (xp<-xc) #local xp=-xc; #end
        #if (yp>yc) #local yp=yc; #end
        #if (yp<-yc) #local yp=-yc; #end
        #if (zp>zc) #local zp=zc; #end
        #if (zp<-zc) #local zp=-zc; #end
        #if (vlength(posPipe[i]-<xp,yp,zp>) != 0)
                #local posPipe[i+1]=<xp,yp,zp>;
                #if (abs(posPipe[i].x)>=box_hole.x & abs(posPipe[i].y)>=box_hole.y & abs(posPipe[i].z)>=box_hole.z)
                    #local nDecotmp=nDeco;
                #else
                    #local nDecotmp=0; // no decorations within the hole

                #end
                        cylinder{posPipe[i]+re*dirPipe[i],posPipe[i+1]-re*dirPipe[i],rPipe}
                        #if (doFile=true)
                                #write(filehandle,"cylinder{<",posPipe[i].x+re*dirPipe[i].x,",",posPipe[i].y+re*dirPipe[i].y,",",posPipe[i].z+re*dirPipe[i].z,">,<",posPipe[i+1].x-re*dirPipe[i].x,",",posPipe[i+1].y-re*dirPipe[i].y,",",posPipe[i+1].z-re*dirPipe[i].z,">,",rPipe,"}\n")
                        #end
                        mBrochette(nDecotmp,dirPipe[i],posPipe[i]+re*dirPipe[i],posPipe[i+1]-re*dirPipe[i],rPipe,doFile)
                        #if (i>0)
                                #if (vlength(dirPipe[i]-dirPipe[i-1])=0)
                                        cylinder{posPipe[i]-re*dirPipe[i],posPipe[i]+re*dirPipe[i],rPipe}
                                        #if (doFile=true)
                                                #write(filehandle,"cylinder{<",posPipe[i].x-re*dirPipe[i].x,",",posPipe[i].y-re*dirPipe[i].y,",",posPipe[i].z-re*dirPipe[i].z,">,<",posPipe[i].x+re*dirPipe[i].x,",",posPipe[i].y+re*dirPipe[i].y,",",posPipe[i].z+re*dirPipe[i].z,">,",rPipe,"}\n")
                                        #end
                                        mBrochette(nDecotmp,dirPipe[i],posPipe[i]-re*dirPipe[i],posPipe[i]+re*dirPipe[i],rPipe,doFile)
                                #else
                                        object{Elbow
                                        #if (doFile=true) #write(filehandle,"object{Elbow ") #end
                                        #if (vlength(dirPipe[i]+x)=0 & vlength(dirPipe[i-1]+y)=0)
                                                translate z*re rotate y*180 rotate x*90
                                                #if (doFile=true) #write(filehandle,"translate z*",re," rotate y*180 rotate x*90 ") #end
                                        #end

                                        #if (vlength(dirPipe[i]+x)=0 & vlength(dirPipe[i-1]-y)=0)
                                                translate x*re rotate x*90 rotate -z*90
                                                #if (doFile=true) #write(filehandle,"translate x*",re," rotate x*90 rotate -z*90 ") #end
                                        #end
                                        #if (vlength(dirPipe[i]+x)=0 & vlength(dirPipe[i-1]+z)=0)
                                                scale <-1,1,1> translate z*re
                                                #if (doFile=true) #write(filehandle,"scale <-1,1,1> translate z*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]+x)=0 & vlength(dirPipe[i-1]-z)=0)
                                                scale <-1,1,-1> translate -z*re
                                                #if (doFile=true) #write(filehandle,"scale <-1,1,-1> translate -z*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-x)=0 & vlength(dirPipe[i-1]+y)=0)
                                                rotate -x*90 translate y*re
                                                #if (doFile=true) #write(filehandle,"rotate -x*90 translate y*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-x)=0 & vlength(dirPipe[i-1]-y)=0)
                                                translate z*re rotate y*90 rotate x*-90 translate -x*re translate -y*re
                                                #if (doFile=true) #write(filehandle,"translate z*",re," rotate y*90 rotate x*-90 translate -x*",re," translate -y*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-x)=0 & vlength(dirPipe[i-1]+z)=0)
                                                translate z*re
                                                #if (doFile=true) #write(filehandle,"translate z*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-x)=0 & vlength(dirPipe[i-1]-z)=0)
                                                scale <1,1,-1> translate -z*re
                                                #if (doFile=true) #write(filehandle,"scale <1,1,-1> translate -z*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]+y)=0 & vlength(dirPipe[i-1]+x)=0)
                                                translate x*re rotate x*90
                                                #if (doFile=true) #write(filehandle,"translate x*",re," rotate x*90") #end
                                        #end
                                        #if (vlength(dirPipe[i]+y)=0 & vlength(dirPipe[i-1]-x)=0)
                                                translate x*re rotate x*90 rotate y*180
                                                #if (doFile=true) #write(filehandle,"translate x*",re," rotate x*90 rotate y*180") #end
                                        #end
                                        #if (vlength(dirPipe[i]+y)=0 & vlength(dirPipe[i-1]+z)=0)
                                                translate z*re rotate -z*90
                                                #if (doFile=true) #write(filehandle,"translate z*",re," rotate -z*90") #end
                                        #end
                                        #if (vlength(dirPipe[i]+y)=0 & vlength(dirPipe[i-1]-z)=0)
                                                rotate y*90 rotate -z*90 translate -z*re
                                                #if (doFile=true) #write(filehandle,"rotate y*90 rotate -z*90 translate -z*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-y)=0 & vlength(dirPipe[i-1]+x)=0)
                                                translate z*re rotate -x*90 translate x*re translate -y*re
                                                #if (doFile=true) #write(filehandle,"translate z*",re," rotate -x*90 translate x*",re," translate -y*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-y)=0 & vlength(dirPipe[i-1]-x)=0)
                                                rotate y*90 rotate -z*90 scale <1,-1,-1> rotate y*-90 translate -x*re
                                                #if (doFile=true) #write(filehandle,"rotate y*90 rotate -z*90 scale <1,-1,-1> rotate y*-90 translate -x*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-y)=0 & vlength(dirPipe[i-1]+z)=0)
                                                rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*re
                                                #if (doFile=true) #write(filehandle,"rotate y*90 rotate -z*90 scale <1,-1,-1> translate z*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-y)=0 & vlength(dirPipe[i-1]-z)=0)
                                                rotate z*90 scale <1,1,-1>
                                                #if (doFile=true) #write(filehandle,"rotate z*90 scale <1,1,-1>") #end
                                        #end
                                        #if (vlength(dirPipe[i]+z)=0 & vlength(dirPipe[i-1]+x)=0)
                                                scale <1,1,-1> translate x*re
                                                #if (doFile=true) #write(filehandle,"scale <1,1,-1> translate x*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]+z)=0 & vlength(dirPipe[i-1]-x)=0)
                                                translate x*re rotate y*180
                                                #if (doFile=true) #write(filehandle,"translate x*",re," rotate y*180") #end
                                        #end
                                        #if (vlength(dirPipe[i]+z)=0 & vlength(dirPipe[i-1]+y)=0)
                                                translate z*re rotate z*90 rotate -x*90
                                                #if (doFile=true) #write(filehandle,"translate z*",re," rotate z*90 rotate -x*90") #end
                                        #end
                                        #if (vlength(dirPipe[i]+z)=0 & vlength(dirPipe[i-1]-y)=0)
                                                rotate y*180 rotate z*90 translate -y*re
                                                #if (doFile=true) #write(filehandle,"rotate y*180 rotate z*90 translate -y*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-z)=0 & vlength(dirPipe[i-1]+x)=0)
                                                translate x*re
                                                #if (doFile=true) #write(filehandle,"translate x*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-z)=0 & vlength(dirPipe[i-1]-x)=0)
                                                rotate y*-90 translate -x*re
                                                #if (doFile=true) #write(filehandle,"rotate y*-90 translate -x*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-z)=0 & vlength(dirPipe[i-1]+y)=0)
                                                rotate y*90 rotate z*90 rotate x*90 translate y*re
                                                #if (doFile=true) #write(filehandle,"rotate y*90 rotate z*90 rotate x*90 translate y*",re," ") #end
                                        #end
                                        #if (vlength(dirPipe[i]-z)=0 & vlength(dirPipe[i-1]-y)=0)
                                                translate z*re rotate -z*90 translate -z*re translate -y*re
                                                #if (doFile=true) #write(filehandle,"translate z*",re," rotate -z*90 translate -z*",re," translate -y*",re," ") #end
                                        #end
                                        translate posPipe[i]+re*dirPipe[i]
                                        #if (doFile=true) #write(filehandle," translate <",posPipe[i].x+re*dirPipe[i].x,",",posPipe[i].y+re*dirPipe[i].y,",",posPipe[i].z+re*dirPipe[i].z,">}\n") #end
                                        }
                                #end
                        #end
                //#end
        #else
//                #warning concat("couic","\n")
                #local i=i-1;
        #end
#local i=i+1;
#end

}
#if (doFile=true)
        #write (filehandle,"}\n")
        #fclose filehandle
        #warning concat(fname," file created\n")
#end

#end

// ========================================
// mBrochette macro
// ----------------------------------------
// This macro makes a kebab using objects instead of lamb or tomatoes
// Works with the mPipe macro
// nObjects is the number of objects to align along the line P1->P2
// dirAxis is the direction (x,y,z,-x,-y,-z) (redundant with the points below actually...)
// P1 is the starting point
// P2 is the end point
// sc is the general scale of the objects
// doFile = true creates a file (within the mPipe macro only)
// ----------------------------------------

#macro mBrochette(nObjects,dirAxis,P1,P2,sc,doFile)
        #local i=0;
        #local k=0;
        #local nO=dimension_size(Deco,1);
        #local lAxis=vlength(P2-P1);
        #while (i<nObjects)
                #local k=k+rand(rd)*lAxis/(nObjects+1);
                #if (k<lAxis)
                        #local iObject=int(rand(rd)*nO-0.00001);
                        #local rrd=rand(rd);
                        #local rtd=int(rand(rd)*nTex-0.00001);
                        object{Deco[iObject] scale sc rotate x*360*rrd
                                #if (abs(dirAxis.x)=1) scale <dirAxis.x,1,1> #end
                                #if (abs(dirAxis.y)=1) rotate z*90*(dirAxis.y) #end
                                #if (abs(dirAxis.z)=1) rotate y*90*(dirAxis.z) #end
                                translate dirAxis*k+P1
                                texture {Tex[rtd]}
                        }
                        #if (doFile=true)
                        #write(filehandle,"object{Deco[",iObject,"] scale ",sc," rotate x*360*",rrd," ")
                                #if (abs(dirAxis.x)=1) #write(filehandle,"scale <",dirAxis.x,",1,1> ") #end
                                #if (abs(dirAxis.y)=1) #write(filehandle,"rotate z*90*",dirAxis.y," ") #end
                                #if (abs(dirAxis.z)=1) #write(filehandle,"rotate y*90*",dirAxis.z," ") #end

                                #write(filehandle,"translate <",k*dirAxis.x+P1.x,",",k*dirAxis.y+P1.y,",",k*dirAxis.z+P1.z,">")
                                #write(filehandle,"texture {Tex[",rtd,"]}}\n")
                        #end
                #end
                #local i=i+1;
        #end
#end

