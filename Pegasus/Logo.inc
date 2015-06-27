#macro LogoThruL(LogoFN,xpix,ypix,xsize,xpos,ypos)
  texture {
    pigment {
      image_map {
        png concat(LogoFN,".svg.png")
        once
      }
      translate -y*0.5
      scale <-1,ypix/xpix,-1>
      scale xsize
      translate x*(xpos+xsize)
      translate y*ypos
    }
    finish {ambient 0.5}
  }
#end

#macro LogoThruR(LogoFN,xpix,ypix,xsize,xpos,ypos)
  texture {
    pigment {
      image_map {
        png concat(LogoFN,".svg.png")
        once
      }
      translate -y*0.5
      scale <1,ypix/xpix,-1>
      scale xsize
      translate x*xpos
      translate y*ypos
    }
    finish {ambient 0.5}
  }
#end

#macro LogoSame(LogoFN,xpix,ypix,xsize,xpos,ypos)
  texture {
    pigment {
      image_map {
        png concat(LogoFN,".svg.png")
        map_type cubic
        once
      }
      translate -y*0.5
      scale <1,ypix/xpix,-1000>
      scale xsize
      translate x*xpos
      translate y*ypos
    }
    finish {ambient 0.5}
  }
  texture {
    pigment {
      image_map {
        png concat(LogoFN,".svg.png")
        map_type cubic
        once
      }
      translate -y*0.5
      rotate y*180
      translate x
      scale <1,ypix/xpix,-1000>
      scale xsize
      translate x*xpos
      translate y*ypos
    }
    finish {ambient 0.5}
  }
#end

#macro LogoSameRot(LogoFN,xpix,ypix,xsize,xpos,yrot)
  texture {
    pigment {
      image_map {
        png concat(LogoFN,".svg.png")
        map_type cubic
        once
      }
      translate -y*0.5
      scale <1,ypix/xpix,-1000>
      scale xsize
      translate x*xpos
      rotate x*yrot
    }
    finish {ambient 0.5}
  }
  texture {
    pigment {
      image_map {
        png concat(LogoFN,".svg.png")
        map_type cubic
        once
      }
      translate -y*0.5
      rotate y*180
      translate x
      scale <1,ypix/xpix,-1000>
      scale xsize
      translate x*xpos
      rotate -x*yrot
    }
    finish {ambient 0.5}
  }
#end

#macro LogoDiff(LogoFN,xpix,ypix,xsize,xpos,ypos)
  texture {
    pigment {
      image_map {
        png concat(LogoFN,"Right.svg.png")
        map_type cubic
        once
      }
      translate -y*0.5
      scale <1,ypix/xpix,-1000>
      scale xsize
      translate x*xpos
      translate y*ypos
    }
    finish {ambient 0.5}
  }
  texture {
    pigment {
      image_map {
        png concat(LogoFN,"Left.svg.png")
        map_type cubic
        once
      }
      translate -y*0.5
      rotate y*180
      translate x
      scale <1,ypix/xpix,-1000>
      scale xsize
      translate x*xpos
      translate y*ypos
    }
    finish {ambient 0.5}
  }
#end

