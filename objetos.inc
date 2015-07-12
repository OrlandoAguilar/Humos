process tintas(x,y,graph,salto);
begin
file=f_obj;
ctype=c_scroll;
loop
if (collision(type humo)) 
ntinta[graph-1]+=salto;
		for(size=100; size>50; size-=3);
                   frame;
		end
		signal(id,s_kill);

end
frame;
end
end

process bloquea_r(x,y,salto,direccion,cr);
private
int rdn,toe;
begin
  ctype=c_scroll;
    graph=new_map(salto, direccion,8);
    pal_map_assign(0,graph,paleta);
    drawing_color((cr-8)*15+6);
    drawing_map(0,graph);
    draw_rect(0,0,salto-1, direccion-1);
    set_center(file,graph,0,0);
   drawing_map(0,scroll_g);
rdn=x; toe=y;
  loop
if (cr==9)
 x=rdn+rand(-1,1);
 else
  y=toe+rand(-1,1);
 end
  if (intersec(x-scroll.x0,y-scroll.y0,x+salto-scroll.x0,y+direccion-scroll.y0))

  bloqueo=cr;
  end
 frame;
 end
end

function instfront(x,y,x0,y0,id2);
begin
while ((salto=get_id(id2))<>0)
if(salto.x>x and salto.x<x0 and salto.y>y and salto.y<y0)
return(salto);
end
end
end

process poder(graph);
private
int types[7];
sonido;
begin
ctype=c_scroll;
signal(all_process,s_freeze);
file=f_modl;
types[0]=type arana;
types[1]=type vaca;
types[2]=type lanca;
types[3]=type agua;
types[4]=type toro;
types[5]=type volador;
types[6]=type mifuego;
      switch (graph);
      case 1:
      graph=0;
      sonido=load_wav("sonidos/FX-Specials507.wav");
      play_wav(sonido,0);

      from z=0 to 5; //tierra
           while ((id2=get_id(types[z]))<>0)
                 if (not out_region(id2,1)) map_xputnp (0,scroll_g,f_rocas,z+1,id2.x,id2.y,id2.angle,100,100,0); puntuaje+=5; mse(id2.x,id2.y,-5,itoa(5),y-30,10.0);
                 signal(id2,s_kill);
                 end
           end
      end

           from z=0 to 319 step 5;
            from x=0 to 4;
                 from y=0 to 239;
                 if (map_get_pixel(0,scroll_g,z+x+scroll.x0,y+scroll.y0)==fuego) map_put_pixel(0,scroll_g,z+scroll.x0+x,y+scroll.y0,piso); end
                 end
            end
            frame;
           end
      signal(all_process,s_wakeup);
      unload_wav(sonido);
      end
      case 20:
      while ((id2=get_id(type humo))<>0)
            prop(id2,graph,0,0);
      end
      end
      case 19:    //guante
      sonido=load_wav("sonidos/FX-Specials502.wav");

      x=scroll.x0+160;
      y=scroll.y0+110;
      while (mouse.left)
      frame; end
      while (not mouse.left)
      angle=fget_angle(x-scroll.x0,y-scroll.y0,mouse.x,mouse.y);
      frame; end
      while (mouse.left) 
      angle=fget_angle(x-scroll.x0,y-scroll.y0,mouse.x,mouse.y);
      frame; end
      signal(all_process,s_wakeup);
      play_wav(sonido,0);
      while (not out_region(id,1))
      from z=0 to 6;
      if ((id2=collision(types[z]))<>0)
      play_wav(s_golp,0);
      mse(id2.x,id2.y,-5,itoa(5),y-30,10.0);
      puntuaje+=(salto=salto+5);
      signal(id2,s_kill);
      end
      end
      advance(5);
      frame;
      end
      unload_wav(sonido);

      end
      case 21:  //burbuja
      while (mouse.left)
      frame; 
      end
      while (not mouse.left)
      x=mouse.x+scroll.x0; y=mouse.y+scroll.y0;

      frame;
      end
            while (mouse.left)
            x=mouse.x+scroll.x0; y=mouse.y+scroll.y0;
      frame; end
      frame;
      while ((id2=get_id(type humo))<>0)
            prop(id2,graph,x,y);

      end
      end
      case 22: //coloca piso
     play_wav(s_chisp,0);
      while (mouse.left)
      frame; end
      while (not mouse.left)
      x=mouse.x+scroll.x0; y=mouse.y+scroll.y0;
      frame; end
      while (mouse.left) frame; end
      while (not mouse.left)
      frame; end
      drawing_map(0,scroll_g);
      drawing_color(piso);
      draw_line(x,y,mouse.x+scroll.x0,y);
      drawing_color(ascender);
      draw_line(mouse.x+scroll.x0,y,mouse.x+scroll.x0,mouse.y+scroll.y0);
      signal(all_process,s_wakeup);
      end
      case 23:  //viento
      sonido=load_wav("sonidos/FX-Atmospheric100.wav");
      direccion=play_wav(sonido,3);
                     x=scroll.x0+160; y=scroll.y0+110;
      from salto =0 to 120;
         from z=0 to 6;
           while ((id2=get_id(types[z]))<>0)
                 if (not out_region(id2,1))
                 id2.x+=cos(get_angle(id2))*3;
                 end
           end
         end
         size_x=rand(50,150);
      frame;
      end
      stop_wav(direccion);
      unload_wav(sonido);
      end
      end
signal(all_process,s_wakeup);
end

process prop(direccion,graph,dx,dy);
private
int types[8];
sonidos,snd;
begin
ctype=c_scroll;
types[0]=type arana;
types[1]=type vaca;
types[2]=type lanca;
types[3]=type agua;
types[4]=type toro;
types[5]=type volador;
types[6]=type mifuego;
types[7]=type circulo;
file=father.file;

if (graph==21)    //burbuja

x=direccion.x; y=direccion.y;
while (fget_dist(dx,dy,x,y)>15)
angle=fget_angle(x,y,dx,dy)+rand(-1000,1000);
advance(3);
if (exists(direccion))direccion.graph=8; direccion.x=x; direccion.y=y; else signal(id,s_kill); end
from z=0 to 6;
             if ((id2=collision(types[z]))<>0)
              id2.x+=get_distx(get_angle(id2),get_dist(id2));
              puntuaje+=(salto=salto+5);
             end
             end
frame;

play_wav(s_boton,0);
end
while (fget_dist(dx,dy,x,y)>3)
angle=fget_angle(x,y,dx,dy);
advance(3);
if (exists(direccion))direccion.x=x; direccion.graph=8; direccion.y=y; else signal(id,s_kill); end
from z=0 to 7;
             if ((id2=collision(types[z]))<>0)
              signal(id2,s_kill);
              puntuaje+=(salto=salto+5);
             end
             end
frame;
end

else
          sonidos=load_wav("sonidos/FX-Specials513.wav");
          snd=play_wav(sonidos,0);
           from angle=0 to 1000000 step 3000;
           x=direccion.x; y=direccion.y-15;
             from z=0 to 6;
             if ((id2=collision(types[z]))<>0)
              signal(id2,s_kill);
              puntuaje+=(salto=salto+5);
             end
             end
             direccion.id2=0;
             frame;
           end
           while (not out_region(id,1))
             y-=5;
              from z=0 to 6;
              if ((id2=collision(types[z]))<>0)
              signal(id2,s_kill);
              puntuaje+=(salto=salto+5);
             end
             end
             frame;
           end
        unload_wav(sonidos);
end
end

process barra_r(x,y,ancho,alto,region,int * var);
private
float fr;
begin
z=25;
graph=new_map(ancho,alto,8);
map_clear(file,graph,87);
set_center(file,graph,0,0);
salto=*var;
obj(0,direccion=new_map(ancho+2,alto+2,8),x,y,z+1);
map_clear(0,direccion,104);
set_center(0,direccion,1,1);

  loop
  fr=ancho*((*var)*1.0/salto);
  define_region(region,x,y,fr,alto);
      frame;
  end
  onexit;
  unload_map(file,graph);
  unload_map(0,direccion);
end