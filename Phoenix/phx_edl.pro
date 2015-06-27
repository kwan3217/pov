restore,'phx_24.sav'
if (size(state_iau_mars,/dim))[0] eq 6 then state_iau_mars=transpose(state_iau_mars)
if vlength(state_iau_mars[0,0:2]) lt 1d6 then state_iau_mars*=1d3
if (size(state_j2000,/dim))[0] eq 6 then state_j2000=transpose(state_j2000)
if vlength(state_j2000[0,0:2]) lt 1d6 then state_j2000*=1d3
if (size(state_mme,/dim))[0] eq 6 then state_mme=transpose(state_mme)
if vlength(state_mme[0,0:2]) lt 1d6 then state_mme*=1d3
a=3396190d
a_eq=3397200d
b=3376200d
f=1d -b/a
r_rel=state_iau_mars[*,0:2]
dr_rel=r_rel[1:n_elements(et)-1,*]-r_rel[0:n_elements(et)-2,*]
alt_eq=vlength(r_rel)-a_eq
;plot,et-et[0],alt_eq,/ynoz
lla=xyz_to_lla(r_rel,a=a,f=f)
llr=xyz_to_llr(r_rel)
lat=lla[*,0]
lon=lla[*,1]
alt=lla[*,2]
i_ei=1; max(where(alt_eq gt 3522200d))+1 ; First sample after crossing below EI altitude
et_ei=linterp(alt_eq[i_ei-1],et[i_ei-1],alt_eq[i_ei],et[i_ei],125000d)
utc_ei=utcd[i_ei]
print,utc_ei,et_ei-et[0],alt[i_ei-1],alt[i_ei],alt_eq[i_ei-1],alt_eq[i_ei]

agl=alt-alt[n_elements(alt)-1]
v_rel=state_iau_mars[*,3:5]
zh=llr_to_xyz([[lat],[lon],[lat*0d +1d]])
eh=normalize_grid(crossp_grid([0,0,1],zh))
nh=crossp_grid(zh,eh)
ve=comp(v_rel,eh)
vn=comp(v_rel,nh)
vz=comp(v_rel,zh)
vh=sqrt(ve^2+vn^2)
vaz=atan(ve,vn)
w=where(vaz lt 0,count)
if count gt 0 then vaz[w]+=2d*!dpi

airspd=vlength(v_rel)
r_i=state_j2000[*,0:2]
v_i=state_j2000[*,3:5]
spd_i=vlength(v_i)
dt=et[1:n_elements(et)-1]-et[0:n_elements(et)-2]
dv_i=v_i[1:n_elements(et)-1,*]-v_i[0:n_elements(et)-2,*]
dr_i=r_i[1:n_elements(et)-1,*]-r_i[0:n_elements(et)-2,*]
a_i=dv_i/[[dt],[dt],[dt]]
dr_dt_rel=dr_rel/[[dt],[dt],[dt]]
;set_plot,'z'
plot,et-et[0],dr_dt_rel[*,0]-v_rel[*,0]
;saveimage,'dr_dt_0.png',/png
plot,et-et[0],dr_dt_rel[*,1]-v_rel[*,1]
;saveimage,'dr_dt_1.png',/png
plot,et-et[0],dr_dt_rel[*,2]-v_rel[*,2]
;saveimage,'dr_dt_2.png',/png

mu=42828.314e9

denom=vlength(r_i)^3
a_g=-mu*r_i/[[denom],[denom],[denom]]
a_g=a_g[0:n_elements(et)-2,*]

a_ng=a_g-a_i


;for i=0,440,5 do begin
;  plot,et-et[0],agl,xrange=[i,i+20],xtitle="Seconds from "+utc_start+"UTC",ytitle="Nongravitational acceleration, m/s^2", title="Phoenix Parachute opening",charsize=2,background=255,color=0,/xs
;  wait,0.5
;end

;plot,et-et[0],agl,xrange=[440,460],xtitle="Seconds from "+utc_start+"UTC",ytitle="Altitude above landing site, m", title="Phoenix touchdown",charsize=2,background=255,color=0,/xs
;oplot,et-et[0],vlength(a_ng),color=254
w=where(et-et[0] gt 0)
lon0=lon[n_elements(lon)-1]
lat0=lat[n_elements(lat)-1]
;plot,(lon[w]-lon0)*sin(lat[w])*a,(lat[w]-lat0)*a,/ynoz,/isotropic

dr_dt_e=comp(v_rel,eh)
dr_dt_n=comp(v_rel,nh)
dr_dt_z=comp(v_rel,zh)
plot,et-et[0],dr_dt_e-ve
;saveimage,'dr_dt_e.png',/png
plot,et-et[0],dr_dt_n-vn
;saveimage,'dr_dt_n.png',/png
plot,et-et[0],dr_dt_z-vz
;saveimage,'dr_dt_z.png',/png

r_rel_from_v=v_rel*0d
r_rel_from_v[n_elements(et)-1,*]=r_rel[n_elements(et)-1,*]
r_rel_blend=r_rel
oodt=200d
w1=max(where(et-et[0] lt 122.955))
w2=max(where(et-et[0] lt 227.825))
w3=max(where(et-et[0] lt 404.940))
ww=[w1,w2]
for i=n_elements(et)-2,0,-1 do begin
  r_rel_from_v[i,*]=r_rel_from_v[i+1,*]-v_rel[i,*]/oodt
  if i lt w1 then begin
    ;Before parachute deploy, use official r_rel
    r_rel_blend[i,*]=r_rel[i,*]
  end else if i gt w2 then begin
    ;After lander sep, use ground-up integration
    r_rel_blend[i,*]=r_rel_from_v[i,*]
  end else begin
    ;In between, linear blend
    r_rel_blend[i,*]=linterp(double(w1),r_rel[i,*],double(w2),r_rel_from_v[i,*],double(i))
  end
end

wset,0
plot,et[w]-et[0],r_rel[w,0]-r_rel_from_v[w,0],/ynoz,charsize=2,yrange=[-1000,1000],/ys
oplot,et[w]-et[0],r_rel[w,1]-r_rel_from_v[w,1],color=254
oplot,et[w]-et[0],r_rel[w,2]-r_rel_from_v[w,2],color=192
oplot,et[w]-et[0],vlength(r_rel[w,*]-r_rel_from_v[w,*]),color=128
oplot,et[ww]-et[0],r_rel[ww,0]-r_rel_from_v[ww,0],psym=1
oplot,et[ww]-et[0],r_rel[ww,1]-r_rel_from_v[ww,1],color=254,psym=1
oplot,et[ww]-et[0],r_rel[ww,2]-r_rel_from_v[ww,2],color=192,psym=1
oplot,et[ww]-et[0],vlength(r_rel[ww,*]-r_rel_from_v[ww,*]),color=128,psym=1

;wset,1
;plot,et[w]-et[0],r_rel_from_v[w,0]-r_rel_blend[w,0],/ynoz,charsize=2,yrange=[-100,500],/ys
;oplot,et[w]-et[0],r_rel_from_v[w,1]-r_rel_blend[w,1],color=254
;oplot,et[w]-et[0],r_rel_from_v[w,2]-r_rel_blend[w,2],color=192
;oplot,et[w]-et[0],vlength(r_rel_from_v[w,*]-r_rel_blend[w,*]),color=128
;oplot,et[ww]-et[0],r_rel_from_v[ww,0]-r_rel_blend[ww,0],psym=1
;oplot,et[ww]-et[0],r_rel_from_v[ww,1]-r_rel_blend[ww,1],color=254,psym=1
;oplot,et[ww]-et[0],r_rel_from_v[ww,2]-r_rel_blend[ww,2],color=192,psym=1
;oplot,et[ww]-et[0],vlength(r_rel_from_v[ww,*]-r_rel_blend[ww,*]),color=128,psym=1

;wset,2
;plot,et[w]-et[0],r_rel[w,0]-r_rel_blend[w,0],/ynoz,charsize=2,yrange=[-100,500],/ys
;oplot,et[w]-et[0],r_rel[w,1]-r_rel_blend[w,1],color=254
;oplot,et[w]-et[0],r_rel[w,2]-r_rel_blend[w,2],color=192
;oplot,et[w]-et[0],vlength(r_rel[w,*]-r_rel_blend[w,*]),color=128
;oplot,et[ww]-et[0],r_rel[ww,0]-r_rel_blend[ww,0],psym=1
;oplot,et[ww]-et[0],r_rel[ww,1]-r_rel_blend[ww,1],color=254,psym=1
;oplot,et[ww]-et[0],r_rel[ww,2]-r_rel_blend[ww,2],color=192,psym=1
;oplot,et[ww]-et[0],vlength(r_rel[ww,*]-r_rel_blend[ww,*]),color=128,psym=1

lla_blend=xyz_to_lla(r_rel_blend,a=a,f=f)
lat_blend=lla_blend[*,0]
lon_blend=lla_blend[*,1]
alt_blend=lla_blend[*,2]
lat2=lat[n_elements(et)-1]
lon2=lon[n_elements(et)-1]
alt2=alt[n_elements(et)-1]

old_fps=fix(0.5d +1d/(et[1]-et[0]))
new_fps=30d
n_frames=fix((et[n_elements(et)-1]-et[0])*new_fps)+1
f_new_in_old=dindgen(n_frames)*old_fps/new_fps
plot,f_new_in_old
r_rel_blend_24=dblarr(n_frames,3)
r_rel_blend_24[*,0]=interpolate(r_rel_blend[*,0],f_new_in_old)
r_rel_blend_24[*,1]=interpolate(r_rel_blend[*,1],f_new_in_old)
r_rel_blend_24[*,2]=interpolate(r_rel_blend[*,2],f_new_in_old)
et_24=interpolate(et,f_new_in_old)
lat_24=interpolate(lat_blend,f_new_in_old)
lon_24=interpolate(lon_blend,f_new_in_old)
alt_24=interpolate(alt_blend,f_new_in_old)
ve_24=interpolate(ve,f_new_in_old)
vn_24=interpolate(vn,f_new_in_old)
vz_24=interpolate(vz,f_new_in_old)

for i=0,n_elements(et_24)-1 do begin
  lat1=lat_24[I]
  lon1=lon_24[I]
  alt1=alt_24[I]
  agl=alt1-alt2
  dist=ell_dist(lat1,lon1,lat2,lon2,a=a,b=b,h=alt2,/rad,ell_az=az)
  vtol,ve[I<I_land],vn[I<I_land],vz[I<I_land],agl,dist,az,string(I,format='(%"svg/VTOL%05d.svg")')
  if i mod 100 eq 0 then print,i
end

end



