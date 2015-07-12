//aqui puntuaje se usa para contar los seres insertados, maximo 40

process crea_zona();
begin
        puntuaje=40;
        let_me_alone();
        jkeys_controller();
        f_boton=load_fpg('graficos/botones/boton.fpg');
        f_zona= load_fpg('graficos/objetos/ojetos.fpg');
        f_enem[0]=load_fpg('graficos/enemigos/seleccion.fpg');
        scroll_g=cream_map_ped();
        pal_map_assign(0,scroll_g,paleta);
	map_clear(0,scroll_g,0);
	define_region(1,0,0,320,200);
	define_region(2,2,202,158,36);
	start_scroll(0,0,scroll_g,0,1,0);
        edita_mapa();
        p_pal();
        obj(f_boton,8,160,220,6);
        boton_m(f_boton,6,170,210,&figura,0,1,0,0,0,1);
        boton_m(f_boton,7,170,228,&figura,0,2,0,0,0,1);
        boton_m(f_boton,11,190,228,&figura,0,4,0,0,0,1);
        boton_m(f_boton,12,210,210,&figura,0,3,0,0,0,1);
        boton_m(f_boton,13,210,228,&figura,0,5,0,0,0,1);
        boton_m(f_boton,14,230,210,&figura,0,6,0,0,0,1);
        boton_m(f_boton,4,230,228,&color_tinta,0,piso,0,0,0,1);
        boton_m(f_boton,1,250,210,&color_tinta,0,pared,0,0,0,1);
        boton_m(f_boton,2,250,228,&color_tinta,0,l_salto,0,0,0,1);
        boton_m(f_boton,3,270,210,&color_tinta,0,ascender,0,0,0,1);
        boton_m(f_boton,5,270,228,&figura,0,0,0,0,0,1);
        boton_m(f_boton,15,290,210,&figura,0,7,0,0,0,1);
        boton_m(f_boton,21,310,228,&color_tinta,0,fuego,0,0,0,1);
        coloca();
        boton_m(f_boton,16,290,228,&son.salto,0,1,0,0,0,1);
        inserta();
        boton_m(f_boton,17,310,210,&son.salto,0,1,0,0,0,1);
        color_tinta=1;
        frame(0);
        if (file_exists("carga/vio.dat"))
        load("carga/vio.dat",salto);
        else
        salto=0;
        end
        if (not salto)
        tutorial2("carga/"+idioma+"/tuto03.prg",12);
        salto=1;
        save("carga/vio.dat",salto);
        end
    //    write_var(0,100,100,4,fps);
loop


                if (jkeys_state[_JKEY_Select] and not exists(type tutorial2)) tutorial2("carga/"+idioma+"/tuto03.prg",11);  end
                if (jkeys_state[_JKEY_UP]) scroll.y0-=3; end
		if (jkeys_state[_JKEY_DOWN]) scroll.y0+=3; end
		if (jkeys_state[_JKEY_LEFT]) scroll.x0-=3; end
		if (jkeys_state[_JKEY_RIGHT]) scroll.x0+=3; end
		if (jkeys_state[_JKEY_MENU]) pause(1); end
if (exit_status)
			exit();
		end
frame;
end
end

function cream_map_ped();
private
byte tam;
int ancho,alto;
begin
        frame;
        tamano(&tam);
        switch (tam&7)
               case 1:
                    ancho=320;
               end
               case 2:
                    ancho=640;
               end
               case 4:
                    ancho=800;
               end
        end

        switch ((tam&56)>>3)
               case 1:
                    alto=200;
               end
               case 2:
                    alto=400;
               end
               case 4:
                    alto=600;
               end
        end
        return(new_map(ancho,alto,8));
end
process mc();
begin
file=f_boton;
graph=24;
set_center(file,graph,0,0);
region=2;
z=father.z-10;
loop
x=((color_tinta % 32)*10)+father.x;
y=((color_tinta/32)*10)+father.y;
frame;
end
end

process p_pal();
private
byte pointer mimap;
int avx;
int avy;
int hij[4];
pres;
byte cont,presionado=false;
begin
  graph=new_map(320,80,8);
  pal_map_assign(file,graph,paleta);
  mimap=map_buffer(file,graph);
  region=2;
  from z=0 to 7;
    from y=0 to 9;
      from direccion=0 to 31;
        from x=0 to 9;
          mimap[salto]=z*32+direccion;
          salto++;
        end
      end
      //salto+=2;
    end
  end
  x=2; y=202;
  set_center(file,graph,0,0);
  hij[0]=boton_m(f_boton,9,150,220,&avx,0,-1,0,0,0,0);
  hij[1]=boton_m(f_boton,9,10,220,&avx,0,1,180000,0,0,0);
  hij[2]=boton_m(f_boton,9,85,210,&avy,0,1,90000,0,0,0);
  hij[3]=boton_m(f_boton,9,85,230,&avy,0,-1,270000,0,0,0);

  boton_m(f_boton,10,190,210,&pres,0,1,0,0,0,0);
  z=-10;
  mc();
  loop
  if (pres<>0 )
    if ( presionado==false)
       presionado=true;
      if (hij[0].graph==0)
        for (cont=0;cont<4;cont++)
            hij[cont].graph=9;
        end
      else
        for (cont=0;cont<4;cont++)
            hij[cont].graph=0;
        end
      end
    end
    pres=0;
  else
    presionado=false;
  end
  if (intersec(2,203,160,238) and mouse.left)
     color_tinta=map_get_pixel(file,graph,mouse.x-x-2,mouse.y-y-1);
  end
  x+=avx;
  y+=avy;
  avx=0;
  avy=0;
  if (x<-160) x=-160; end
  if (x>2) x=2; end
  if (y<158) y=158; end
  if (y>202) y=202; end
    frame;
end
onexit;
unload_map(file,graph);
end

process edita_mapa();
private
	puntos ant;
	dcolor c_col;
	float ang,faux;
	figuraaux;
	radio;
begin
	drawing_color(piso);
	drawing_map(0,scroll_g);
	z=0;
	figura=1;
	figuraaux=figura;
	loop
         drawing_map(0,scroll_g);
		if (figuraaux<>figura and figura==2)
		   barra(160,100,&radio,0.14,1,1);
                end
                figuraaux=figura;
	drawing_color(color_tinta);

		x=mouse.x;
		y=mouse.y;
		switch (figura)
		        case 0:
                              if (mouse.left)
                              drawing_color(0);
                              ant.x=mouse.x+scroll.x0; ant.y=mouse.y+scroll.y0;
					while(mouse.left)
						if (mouse.y>200) break; end
						frame;
                                                ang=fget_angle(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0);
					        faux=fget_dist(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0);
                                                if (faux>0)
                                                  for (z=0;z<faux;z++)
  						    draw_fcircle(ant.x+cos(ang)*z,ant.y-sin(ang)*z,5);
                                                  end
                                                  ant.x+=cos(ang)*z;
                                                  ant.y-=sin(ang)*z;
                                                end
					end

				end
		        end
			case 1:
				if (mouse.left and mouse.y<200)
				 signal(type boton_m,s_freeze);
				 signal(type p_pal,s_freeze);
				               GET_COLORS (paleta, color_tinta, 1, &c_col );
				               drawing_color(rgb(c_col.r,c_col.g,c_col.b));
					drawing_z(500);
					ant.x=mouse.x; ant.y=mouse.y;
					while (mouse.left)
						if (z<>0) delete_draw(0); end
						if (mouse.y<200)
								z=draw_line(ant.x,ant.y,mouse.x,mouse.y);
							  else
                                                                	z=draw_line(ant.x,ant.y,ant.x+(1.0*(200-ant.y)/(mouse.y-ant.y))*(mouse.x-ant.x),200);
								end



						frame;
					end
					z=0;
					delete_draw(0);
					drawing_map(0,scroll_g);
					drawing_color(color_tinta);


					if (mouse.y<200)
						draw_line(ant.x+scroll.x0,ant.y+scroll.y0,mouse.x+scroll.x0,mouse.y+scroll.y0);
							  else
                                        draw_line(ant.x+scroll.x0,ant.y+scroll.y0,ant.x+(1.0*(200-ant.y)/(mouse.y-ant.y))*(mouse.x-ant.x)+scroll.x0,200+scroll.y0);
                                        end
					signal(type boton_m,s_wakeup);
					signal(type p_pal,s_wakeup);
				end
			end
			case 2:
				if (mouse.left)

					if (radio<1)
                                                while(mouse.left)
        						if (mouse.y>200) break; end
        						ant.x=mouse.x+scroll.x0; ant.y=mouse.y+scroll.y0;
        						frame;
        
        						draw_line(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0);
        
        					end
					else
                                                ant.x=mouse.x+scroll.x0; ant.y=mouse.y+scroll.y0;
        					while(mouse.left)
        						if (mouse.y>200) break; end
        						frame;
                                                        ang=fget_angle(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0);
        					        faux=fget_dist(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0);
                                                        if (faux>0)
                                                          for (z=0;z<faux;z++)
          						    draw_fcircle(ant.x+cos(ang)*z,ant.y-sin(ang)*z,radio);
                                                          end
                                                          ant.x+=cos(ang)*z;
                                                          ant.y-=sin(ang)*z;
                                                        end
        					end
					end
				end

			end
			case 3:
				if (mouse.left and mouse.y<200)
				signal(type boton_m,s_freeze);
				 signal(type p_pal,s_freeze);
				               GET_COLORS (paleta, color_tinta, 1, &c_col );
				               drawing_color(rgb(c_col.r,c_col.g,c_col.b));
					drawing_z(500);
					ant.x=mouse.x; ant.y=mouse.y;
					while (mouse.left)
						if (z<>0) delete_draw(0); end
						if (mouse.y<200)
                                                z=draw_box(ant.x,ant.y,mouse.x,mouse.y);
                                                else
						z=draw_box(ant.x,ant.y,mouse.x,200);
					        end
						frame;
					end
					z=0;
					delete_draw(0);
					drawing_map(0,scroll_g);
					drawing_color(color_tinta);
					if (mouse.y<200)
						draw_box(ant.x+scroll.x0,ant.y+scroll.y0,mouse.x+scroll.x0,mouse.y+scroll.y0);
						else
						draw_box(ant.x+scroll.x0,ant.y+scroll.y0,mouse.x+scroll.x0,200+scroll.y0);
					end
				end
				signal(type boton_m,s_wakeup);
					signal(type p_pal,s_wakeup);
			end
			case 4:
				if (mouse.left and mouse.y<200)
				signal(type boton_m,s_freeze);
				 signal(type p_pal,s_freeze);
				               GET_COLORS (paleta, color_tinta, 1, &c_col );
				               drawing_color(rgb(c_col.r,c_col.g,c_col.b));
					drawing_z(500);
					ant.x=mouse.x; ant.y=mouse.y;
					while (mouse.left)
						if (z<>0) delete_draw(0); end
						if (mouse.y<200)
                                                z=draw_rect(ant.x,ant.y,mouse.x,mouse.y);
						else
                                                z=draw_rect(ant.x,ant.y,mouse.x,200);
                                                end
						frame;
					end
					z=0;
					delete_draw(0);
					drawing_map(0,scroll_g);
					drawing_color(color_tinta);
					if (mouse.y<200)
						draw_rect(ant.x+scroll.x0,ant.y+scroll.y0,mouse.x+scroll.x0,mouse.y+scroll.y0);
					else
						draw_rect(ant.x+scroll.x0,ant.y+scroll.y0,mouse.x+scroll.x0,200+scroll.y0);
					end
					signal(type boton_m,s_wakeup);
					signal(type p_pal,s_wakeup);
				end
			end
			case 5:
				if (mouse.left and y<200)
				signal(type boton_m,s_freeze);
				 signal(type p_pal,s_freeze);
				               GET_COLORS (paleta, color_tinta, 1, &c_col );
				               drawing_color(rgb(c_col.r,c_col.g,c_col.b));
					drawing_z(500);
					ant.x=mouse.x; ant.y=mouse.y;
					while (mouse.left)
						if (z<>0) delete_draw(0); end
						direccion=fget_dist(mouse.x,mouse.y,ant.x,ant.y);
						z=draw_circle(ant.x,ant.y,direccion);

						frame;
					end
					z=0;
					delete_draw(0);
					drawing_map(0,scroll_g);
					drawing_color(color_tinta);

						draw_circle(ant.x+scroll.x0,ant.y+scroll.y0,direccion);

					signal(type boton_m,s_wakeup);
					signal(type p_pal,s_wakeup);
				end
			end
			case 6:
				if (mouse.left and y<200)
				signal(type boton_m,s_freeze);
				 signal(type p_pal,s_freeze);
				               GET_COLORS (paleta, color_tinta, 1, &c_col );
				               drawing_color(rgb(c_col.r,c_col.g,c_col.b));
					drawing_z(500);
					ant.x=mouse.x; ant.y=mouse.y;
					while (mouse.left)
						if (z<>0) delete_draw(0); end
						direccion=fget_dist(mouse.x,mouse.y,ant.x,ant.y);
						z=draw_fcircle(ant.x,ant.y,direccion);

						frame;
					end
					z=0;
					delete_draw(0);
					drawing_map(0,scroll_g);
					drawing_color(color_tinta);

						draw_fcircle(ant.x+scroll.x0,ant.y+scroll.y0,direccion);

					signal(type boton_m,s_wakeup);
					signal(type p_pal,s_wakeup);
				end
			end
			case 7:
				if (mouse.left and mouse.y<200)
				               ant.x=mouse.x+scroll.x0; ant.y=mouse.y+scroll.y0;

                                                        if (!exists(type rellenar))
                                                            rellenar(scroll_g,ant.x,ant.y,color_tinta,255);
                                                        end
                			       while (mouse.left)
                			             frame;
                                               end
                                 end

			end
		end
		frame;
	end
end


/*process rellenar(x,y,color,fondo);
begin
tot++;
if (map_get_pixel(0,scroll_g,x,y)<>fondo or x<0 or x>800 or y<0 or y>600)
signal(id,s_kill);
end
map_put_pixel(0,scroll_g,x,y,color);
frame;
if (map_get_pixel(0,scroll_g,x,y-1)==fondo)

   rellenar(x,y-1,color,fondo);
   frame;
end

if (map_get_pixel(0,scroll_g,x,y+1)==fondo)

   rellenar(x,y+1,color,fondo);
   frame;
end

if (map_get_pixel(0,scroll_g,x-1,y)==fondo)

   rellenar(x-1,y,color,fondo);
   frame;
end

if (map_get_pixel(0,scroll_g,x+1,y)==fondo)

   rellenar(x+1,y,color,fondo);
   frame;
end


onexit;
tot--;
end   */

/* por SplinterGU */
FUNCTION rellenar(INT mapa,xa,ya,ColorA,INT alfa);
PRIVATE
    INT ColorAnt;
    int lx, rx;
    int flx, frx;
    int fup, fdn;
    int gwide, gheight;
    int i;
BEGIN
    ColorAnt = map_get_pixel(0,mapa,xa,ya);

    IF (ColorAnt==ColorA) RETURN 0; END

    gwide = graphic_info(0,mapa,g_wide);
    gheight = graphic_info(0,mapa,g_height);

    lx = xa;
    rx = xa;
    flx = false;
    frx = false;
    fup = false;
    fdn = false;

    map_put_pixel(0,mapa, xa, ya, ColorA);

    while(flx == false || frx == false)
        if ( flx == false )
            if ( lx > 0 && map_get_pixel(0, mapa, lx-1, ya) == ColorAnt )
                lx--;
                map_put_pixel(0,mapa, lx, ya, ColorA);
            else
                flx = true;
            end

        end

        if ( frx == false )
            if ( rx < gwide && map_get_pixel(0, mapa, rx+1, ya) == ColorAnt )
                rx++;
                map_put_pixel(0,mapa, rx, ya, ColorA);
            else
                frx = true;
            end

        end
    end

    for (i=lx;i<=rx;i++)
        if ( map_get_pixel(0, mapa, i, ya-1) == ColorAnt )
            if (fup == false)
                fup = true;
                rellenar(mapa,i,ya-1,ColorA,alfa);
            end
        else
            fup = false;
        end

        if ( map_get_pixel(0, mapa, i, ya+1) == ColorAnt )
            if (fdn == false)
                fdn = true;
                rellenar(mapa,i,ya+1,ColorA,alfa);
            end
        else
            fdn = false;
        end
    end

    RETURN 0;

END
/* fin de funcion de splinter */


process  coloca();
begin
file=f_zona;
x=50; y=50;
graph=0;
loop

if (salto<>0)
graph=(graph==0? 1 : 0);
figura=-1;
salto=0;
end
if (graph<>0)
if (figura<>-1) graph=0; continue; end
id2=get_id(type inserta);
if (exists(id2)) id2.graph=0; end
if (jkeys_state[_JKEY_B])
    graph++;
    if (graph>5) graph=1; end
while (jkeys_state[_JKEY_B]) frame; end
end
if (jkeys_state[_JKEY_A])
    map_xputnp(0,scroll_g,file,graph,x+scroll.x0,y+scroll.y0,0,100,100,0);
while (jkeys_state[_JKEY_A]) frame; end
elseif (intersec(x-20,y-20,x+20,y+20) and mouse.left)
     x=mouse.x;
     y=mouse.y;
     if (x<20) x=20; end
     if (x>300) x=300; end
     if (y<20) y=20; end
     if (y>180) y=180; end
end
end

frame;
end
end

process  inserta();
begin
file=f_enem[0];
x=50; y=50;
graph=0;
presn();
loop
if (salto<>0)
graph=(graph==0? 1 : 0);
figura=-1;
salto=0;
end
if (graph<>0)
if (figura<>-1) graph=0; continue; end
id2=get_id(type coloca);
if (exists(id2)) id2.graph=0; end
if (jkeys_state[_JKEY_B])
    graph++;
    if (graph>14) graph=1; end
while (jkeys_state[_JKEY_B]) frame; end
end
if (jkeys_state[_JKEY_A] and puntuaje>0)
puntuaje--;
    if (graph==8 or graph==9)
    bloquea(x+scroll.x0-13,y+scroll.y0-13,0,0,graph);
    else
    planta(x+scroll.x0,y+scroll.y0,graph);
    end
while (jkeys_state[_JKEY_A]) frame; end
elseif (intersec(x-20,y-20,x+20,y+20) and mouse.left)
     x=mouse.x;
     y=mouse.y;
     if (x<20) x=20; end
     if (x>300) x=300; end
     if (y<20) y=20; end
     if (y>180) y=180; end
end
end

frame;
end
end

process planta(x,y,graph);
begin
  ctype=c_scroll;
  file=f_enem[0];
  z=-3;
  loop
    if (collision (type mouse) and mouse.left and jkeys_state[_JKEY_X])
           signal(id,s_kill);
    end
    frame;
  end
end

process bloquea(x,y,salto,direccion,graphr);
begin
  ctype=c_scroll;
  if (salto==0)
    father.graph=0;
    signal(ALL_PROCESS,s_freeze);
    signal(type crea_zona,s_wakeup);
    signal(type  jkeys_controller,s_wakeup);
    drawing_color((graphr-8)*15+6);
    drawing_z(500);
    while (not mouse.left)
      draw_rect(x-scroll.x0,y-scroll.y0,mouse.x,mouse.y);
      frame;
      delete_draw(0);
    end
    while (mouse.left)
      draw_rect(x-scroll.x0,y-scroll.y0,mouse.x,mouse.y);
      frame;
      delete_draw(0);
    end
  
    if ((y-mouse.y+scroll.y0)<>0)
      salto=abs(x-scroll.x0-mouse.x);
      direccion=abs(y-scroll.y0-mouse.y);
      graph=new_map(salto,direccion ,8);
      pal_map_assign(0,graph,paleta);
      drawing_color((graphr-8)*15+6);
      drawing_map(0,graph);
      draw_rect(0,0,salto-1, direccion-1);
      set_center(file,graph,0,0);
    else
    return;
    end
    if (x>(mouse.x+scroll.x0)) x=(mouse.x+scroll.x0); end
    if (y>(mouse.y+scroll.y0)) y=(mouse.y+scroll.y0); end
    signal(ALL_PROCESS,s_wakeup);
    father.graph=6;
  else
    graph=new_map(salto, direccion,8);
    pal_map_assign(0,graph,paleta);
    drawing_color((graphr-8)*15+6);
    drawing_map(0,graph);
    draw_rect(0,0,salto-1, direccion-1);
    set_center(file,graph,0,0);

  end
  drawing_map(0,scroll_g);
  z=graphr;
  loop
      if (collision (type mouse) and mouse.left and jkeys_state[_JKEY_X])
       signal(id,s_kill);
      end
    frame;
  end
  onexit;
  unload_map(file,graph);
end

function linea(x,y,x1,y1);
private
float ang,faux;
begin
ang=fget_angle(x,y,x1,y1);

					        faux=fget_dist(x,y,x1,y1);

                                                if (faux>0)
                                                  for (z=0;z<faux;z++)
  						    draw_fcircle(x+cos(ang)*z,y-sin(ang)*z,5);
                                                  end
                                                  end
end


process presn();
begin
graph=write_in_map(1,puntuaje,4);
id2=puntuaje;
z=-500;
loop
if (father.graph<>0)
x=father.x; y=father.y+15;
if (puntuaje<>id2)
unload_map(file,graph);
graph=write_in_map(1,puntuaje,4);
id2=puntuaje;
end
else
x=-100; y=-100;
end
frame;
end
end


process tutorial2(string arch,int salto);
private
int var;
int ids[4];
begin
  id2=fopen(arch,O_READ);
  if (mensaje(160,20,1,fgets(id2)));
  fgets(id2);
  fgets(id2);
  color_tinta=0;
  var=write(1,160,20,4,fgets(id2));
  while (color_tinta==0)
          frame;
  end
  delete_text(var);
  texttu("carga/"+idioma+"/ccol.prg",2);

  from z=0 to 2;
  frame;
  var=write(1,160,20,4,fgets(id2));
  switch (z);
      case 0:
  obj(f_boton,7,160,40,-5);
  while (figura<>2)
          frame;
  end
  end
  case 1:
  obj(f_boton,6,160,40,-5);
  while (figura<>1)
          frame;
    end
  end
  case 2:
  obj(f_boton,12,160,40,-5);
  while (figura<>3)
          frame;
    end
  end
end
    signal(son,s_kill);

    delete_text(var);
    frame(0);
      switch (z);
      case 0:
      texttu("carga/"+idioma+"/cmanal.prg",3);
      end
      case 1:
      texttu("carga/"+idioma+"/cfig.prg",2);
      end

      end

  end
  ids[0]=obj(f_boton,3,130,100,text_z);
  ids[1]=obj(f_boton,1,130,120,text_z);
  ids[2]=obj(f_boton,2,130,140,text_z);
  ids[3]=obj(f_boton,21,130,160,text_z);
  texttu("carga/"+idioma+"/cint.prg",10);
  from var=0 to 3;
  signal(ids[var],s_kill);
  end
frame(0);

  mensaje(160,20,1,fgets(id2));
  var=write(1,160,20,4,fgets(id2));
  obj(f_boton,16,160,40,-500);
    ids[1]=get_id(type coloca);
    while (ids[1].graph==0)
          frame;
    end
    delete_text(var);
    signal(son,s_kill);
    frame;
    texttu("carga/"+idioma+"/cobj.prg",7);
    frame(0);
    var=write(1,160,20,4,fgets(id2));
    while (not jkeys_state[_JKEY_A])
          frame;
    end
    delete_text(var);
    texttu("carga/"+idioma+"/cinsot.prg",2); //insertar humos
    frame(0);

    obj(f_boton,17,160,40,-500);
    var=write(1,160,20,4,fgets(id2));
    ids[1]=get_id(type inserta);
    while (ids[1].graph==0)
          frame;
    end
    delete_text(var);
    signal(son,s_kill);

    var=write(1,160,20,4,fgets(id2));
    while (not jkeys_state[_JKEY_A])
          frame;
    end
    delete_text(var);


    texttu("carga/"+idioma+"/cfin2.prg",8);
    else
    var=write(1,160,20,4,fgets(id2));
    salto=write(1,160,40,4,fgets(id2));
      from z=0 to 40;
      frame;
      end
    delete_text(var);
    delete_text(salto);
    end
    fclose(id2);
    frame;
//    signal(id,s_kill_tree);


end

