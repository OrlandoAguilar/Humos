process arana(x,y);
begin
ctype=c_scroll;
file=f_enem[4];
  loop
    if (rand(0,200)==7 and not out_region(id,1)) play_wav(s_arana,0); end
    for (angle=0;angle<180000; angle+=5000);
    if (id2=collision(type humo)) id2.id2=4; end
    if (++graph>3)
      graph=1;
      end
    frame;
    end
      for (z=0;z<100;z++)
      if (id2=collision(type humo)) id2.id2=4; end
          y++;
          drawing_color(fuego);
          draw_fcircle(x,y,4);
          if (++graph>3)
      graph=1;
      end
          frame;
      end
    for (angle=180000;angle<360000; angle+=5000);
    if (id2=collision(type humo)) id2.id2=4; end
    if (++graph>3)
      graph=1;
      end
  frame;
  end
  
    for (z=0;z<100;z++)
        y--;
        if (id2=collision(type humo)) id2.id2=4; end
        if (++graph>3)
    graph=1;
    end
        frame;
    end
    frame;
  end
end

process mifuego(x,y);
begin
ctype=c_scroll;
file=f_enem[0];
graph=4;
while (map_get_pixel(0,scroll_g,x,y)==0)
        gravedad_enem();
        frame;
end
from z=0 to 100;
if (id2=collision(type humo)) id2.id2=4; end
  if (++graph>6)
      graph=4;
      end
frame;
end

from size=100 to 50 step -3;
if (id2=collision(type humo)) id2.id2=4; end
frame;
end
end

process vaca(x,y);
begin
ctype=c_scroll;
file=f_enem[0];
graph=1;
while (map_get_pixel(0,scroll_g,x,y)==0)
        gravedad_enem();
        frame;
end
direccion=1;
  loop
  if (rand(0,200)==7 and not out_region(id,1)) play_wav(s_vac,0); end
  if (id2=collision(type humo)) id2.id2=4; end
  if (++graph>3)
      graph=1;
      end
        gravedad_enem();
        if (rand(0,50)==8)
            mifuego(x,y);
        end
        from z=-5 to 5;
	     if (map_get_pixel(0,scroll_g,x+direccion,y+z)<>0) break; end
	end
        if (z==6)
        direccion*=-1;
        end
        x+=direccion;
        if (direccion==1)
				flags=0;
			else
				flags=1;
			end

     frame;
  end
end

function gravedad_enem();
begin
	x=father.x; y=father.y;

	if (map_get_pixel(0,scroll_g,x,y-5)<>0 and map_get_pixel(0,scroll_g,x,y-8)<>0)  father.direccion*=-1;  end
	from z=-5 to 5;
        if (map_get_pixel(0,scroll_g,x,y+z)==-1) 
        mse(x-scroll.x0,y-scroll.y0,-5,itoa(30),y-30,10.0); 
        pchispas(x,y);
        if (father.reserved.process_type <> type circulo)
        puntuaje+=30;
        else
        puntuaje+=5;
        end
        signal(father,s_kill);
        end
		if (map_get_pixel(0,scroll_g,x,y+z)<>0 or map_get_pixel(0,scroll_g,x,y+z)==fuego)
                	break;
		end

	end
		father.y+=z;
	return;
end


process lanca(x,y);
begin
ctype=c_scroll;
file=f_enem[1];
graph=1;
while (map_get_pixel(0,scroll_g,x,y)==0)
        gravedad_enem();
        frame;
end
direccion=1;
  loop
  if (rand(0,200)==7 and not out_region(id,1)) play_wav(s_lan,0); end
  if (id2=collision(type humo)) id2.id2=4; end
      if (++graph>3)
          graph=1;
      end

      if (graph==3 and ++salto>30)
         circulo(x,y);
         salto=0;
      end

     frame;
  end
end

process circulo(x,y);
private
cont;
float acel;
begin
ctype=c_scroll;
file=f_enem[1];
graph=4;

direccion=1;
  from cont=0 to 300;

  gravedad_enem();
      
      from z=-5 to 5;
	     if (map_get_pixel(0,scroll_g,x+direccion,y+z)<>0 and map_get_pixel(0,scroll_g,x-direccion,y+z)==0)
               direccion*=-1;
               break;
             end
             if (map_get_pixel(0,scroll_g,x-direccion,y+z)<>0) break; end
      end
      if (map_get_pixel(0,scroll_g,x,y-3)<>0 and map_get_pixel(0,scroll_g,x,y-6)<>0 and map_get_pixel(0,scroll_g,x+direccion,y)==0) 
         direccion*=-1;  
      end
      if (map_get_pixel(0,scroll_g,x+direccion,y)<>0 and map_get_pixel(0,scroll_g,x+direccion,y-8)<>0)
         direccion*=-1;
      end
      x+=direccion*2+acel;
      if (direccion==-1)
				angle+=5000;
				acel-=0.1;
			else
				angle-=5000;
				acel+=0.1;
			end

     if (out_region(id,0)) 
     signal(id,s_kill);
     end
     y-=12;
     if (id2=collision(type humo)) id2.id2=4; end
     frame;
     y+=12;
  end
end

process agua(x,y);
private
cont=0;
begin
ctype=c_scroll;
file=f_enem[3];
graph=1;
aros(-1);
aros(1);
while (map_get_pixel(0,scroll_g,x,y)==0)
        gravedad_enem();
        frame;
end
direccion=1;
  loop
  if (rand(0,150)==45 and (not out_region(id,1))) play_wav(s_lamento,0); end
  if (id2=collision(type humo)) id2.id2=4; end
  if (++graph>3)
      graph=1;
      end
        gravedad_enem();
        from z=-5 to 5;
	     if (map_get_pixel(0,scroll_g,x+direccion,y+z)<>0) break; end
	end
        if (z==6)
        direccion*=-1;
        end
        x+=direccion;
        if (direccion==1)
				flags=0;
			else
				flags=1;
			end

     frame;
     frame;
  end
end

process aros(direccion);
begin
ctype=c_scroll;
file=f_enem[3];
graph=4;

  loop
  if (not exists(father)) 
     signal(id,s_kill);
  end
  if (id2=collision(type humo)) id2.id2=4; end
  angle+=3000*direccion;
  salto=abs(cos(angle)*50);
  x=father.x+get_distx(angle,salto);
  y=father.y+get_disty(angle,salto);

  frame;
  end
end


process toro(x,y);
begin
ctype=c_scroll;
file=f_enem[2];
graph=1;
while (map_get_pixel(0,scroll_g,x,y)==0)
        gravedad_enem();
        frame;
end
direccion=1;
  loop
  if (rand(0,200)==7 and not out_region(id,1)) play_wav(s_mon,0); end
  if (id2=collision(type humo)) id2.id2=4; end
  if (++graph>3)
      graph=1;
      end
        gravedad_enem();

        from z=-5 to 5;
	     if (map_get_pixel(0,scroll_g,x+direccion,y+z)<>0) break; end
	end
        if (z==6)
        direccion*=-1;
        end
        x+=direccion;
        if (direccion==1)
				flags=0;
			else
				flags=1;
			end

     frame;
  end
end

process volador(id2,salto)
begin
ctype=c_scroll;
file=f_enem[5];
graph=1;
loop
if (rand(0,500)==7 and not out_region(id,1)) play_wav(s_mur,0); end
x=id2+get_distx(z,100+rand(-10,10));
y=salto+get_disty(z,50+rand(-10,10));
z+=1000;
if (id2=collision(type humo)) id2.id2=4; end
frame;
end
end

process enem_g(tipo);
private 
ener=3;
cont;
string cadena;
sonido;
begin

switch (tipo);
case 1:
direccion+=1000;
x=70+get_distx(direccion,salto);
salto=get_distx(direccion,190);
y=100+get_disty(direccion,salto/2);
f_enem[0]=file=load_fpg("graficos/enemigos/fantasma.fpg");
flags=4;
barra_r(100,20,100,15,5,&ener);
frame;
texttu("carga/"+idioma+"/mensmon2.prg",2);
loop
if (++graph>3) graph=1; end
direccion+=1000;
x=70+get_distx(direccion,salto);
salto=get_distx(direccion,190);
y=100+get_disty(direccion,salto/2);
if (not out_region(id,0) and rand(0,100)==28)
mifuego(x,y);
play_wav(s_golp,0);
cont++;
end
if (not out_region(id,0) and cont>3)
swich(x,y,&ener);
cont=0;
end
if (ener<1) vidas++;
 if (level_desb<=zona) 
    level_desb=zona+1;
 end
 selecciona_zona();
signal(id,s_kill);
end

frame;

end
end
case 2:
from z=1 to 4;  //monsturo 2
		ntinta[z-1]=0;
                end
f_enem[0]=file=load_fpg("graficos/enemigos/muerte.fpg");
direccion=1;
x=100;
y=24;
cont=10;
barra_r(100,20,100,15,5,&cont);
frame;
texttu("carga/"+idioma+"/mensmons.prg",2);
loop
if (++graph>3) graph=1; end
if (x>280 or x<40 ) direccion*=-1; end
x+=direccion;
if (x%40==0) cag(x,y+30); play_wav(s_arana,0); cont--; end
        if (direccion==1)
				flags=0;
			else
				flags=1;
			end
if (cont<1)
while (exists(type cag))
frame;
end
vidas++;
if (level_desb<=zona) 
level_desb=zona+1;
end
 selecciona_zona();
signal(id,s_kill);
end
			frame;
end
end
case 3:   //tablero
from z=1 to 4;
		ntinta[z-1]=0;
                end
cadena=itoa(puntuaje)+" / 500";
write_var(1,40,179,4,cadena);
f_enem[0]=file=load_fpg("graficos/enemigos/tab.fpg");
graph=1;
set_center(file,graph,0,0);
chumos=1;
puntuaje=1;
loop
ener=rand(1,3);
for (id2=0; id2<ener; id2++)
bnt();
end

while (exists(type bnt))
frame;
end
if (puntuaje>500) vidas++; if (level_desb<=zona) level_desb=zona+1; end  selecciona_zona(); signal(id,s_kill); end
if (puntuaje<=0) tot++; puntuaje=1; end
if (tot>3) game_over(); end
end
end
case 4:
		while (not exists(id2=get_id(type humo))) //encuentra un humo valido
                end
                scroll.x0=0;
                frame(500);
loop
		if (out_region(id2,1))
		game_over();
		end

		scroll.x0++;
frame(500);
end
end
case 5:  //recorre
f_enem[0]=file=load_fpg("graficos/zonas/zona15.fpg");
graph=2;
obj(file,1,160,100,5);
obj(file,3,169,78,5);
x=23; y=174;
frame;
texttu("carga/"+idioma+"/cobj_fin.prg",6);
loop
if ((id2=collision(type obj))<>0)
if (not is_playing_wav(sonido)) sonido=play_wav(s_boton,0); end

   if (id2.graph==1) x=direccion; y=salto;
   else  vidas++; if (level_desb<=zona)  end
   let_me_alone();
fin();
   signal(id,s_kill);
   end
   else
   direccion=x; salto=y;
   if (jkeys_state[_JKEY_UP]) y--; end
   if (jkeys_state[_JKEY_DOWN])  y++; end
   if (jkeys_state[_JKEY_LEFT])  x--; end
   if (jkeys_state[_JKEY_RIGHT])  x++; end

end



frame;
end
end
end

onexit;
pchispas(x,y);
end

process cag(x,y);
private
cont;
begin
ctype=c_scroll;
file=f_enem[0];
graph=4;

direccion=rand(-1,1);
direccion=direccion<>0? direccion : 1;

  from cont=0 to 300;

  from z=-5 to 1;

		if (map_get_pixel(0,scroll_g,x,y+z)<>0 or map_get_pixel(0,scroll_g,x,y+z)==fuego)
                	break;
		end

  end
  y+=z;
      
      from z=-5 to 5;
	     if (map_get_pixel(0,scroll_g,x+direccion,y+z)<>0 and map_get_pixel(0,scroll_g,x-direccion,y+z)==0)
               direccion*=-1;
               break;
             end
             if (map_get_pixel(0,scroll_g,x-direccion,y+z)<>0) break; end
      end
      if (map_get_pixel(0,scroll_g,x,y-3)<>0 and map_get_pixel(0,scroll_g,x,y-6)<>0 and map_get_pixel(0,scroll_g,x+direccion,y)==0) 
         direccion*=-1;  
      end
      if (map_get_pixel(0,scroll_g,x+direccion,y)<>0 and map_get_pixel(0,scroll_g,x+direccion,y-8)<>0)
         direccion*=-1;
      end
      x+=direccion*2;
      if (direccion==-1)
				angle+=5000;
			else
				angle-=5000;
                        end

     if (out_region(id,0))
     signal(id,s_kill);
     end
     y-=12;
     if (id2=collision(type humo)) id2.id2=4; end
     if (collision(type mouse) and mouse.left and mslft==false)
     signal(id,s_kill);
     end
     frame;
     y+=12;
  end
end

process swich(x,y,int * ener);
begin
graph=7; file=f_enem[0];

loop
        gravedad_enem();
        angle+=rand(0,360000);
        advance(5);
if (collision(type humo))
*ener=*ener-1;
puntuaje+=100;
pchispas(x,y);
signal(type swich,s_kill);
end
frame;
end
end

process pchispas(x,y);
begin
ctype=c_scroll;
graph=strll;
play_wav(s_chisp,0);
from z=0 to 14;
chispas();
frame;
end
end

process chispas();
begin
graph=strll;
size=rand(20,100);
z=-200;
x=father.x+rand(-40,40);
y=father.y-rand(0,40);
for (angle=0; angle<360000; angle+=10000)
y--;
frame;
end
end

process bnt();
begin
graph=rand(2,5);
file=f_enem[0];
x=40+60*rand(0,4);
y=45+70*rand(0,1);
z=-200;
while(mouse.left) frame; end
if (collision(type bnt)) signal(id,s_kill); end
salto=rand(60,120);
for (id2=0;id2<salto;id2++)
if (fget_dist(mouse.x, mouse.y, x,y)<25 and mouse.left and mslft==false)
switch (graph);
case 2,3:
puntuaje+=graph*20;
play_wav(s_golp,0);
end
case 4:
puntuaje++;
play_wav(s_lamento,0);
end
case 5:
puntuaje=0;
play_wav(s_arana,0);
end
end
pchispas(x,y);
signal(id,s_kill);
end
frame;
end
if (graph==2 or graph==3)
puntuaje-=70;
end
end