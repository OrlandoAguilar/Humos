program humos;
	import "mod_key";
	import "mod_proc";
	import "mod_grproc";
	import "mod_video";
	import "mod_mouse";
	import "mod_map";
	import "mod_screen";
	import "mod_draw";
	import "mod_sound";
	import "mod_say";
	import "mod_wm";
	import "mod_scroll";
	import "mod_text";
	import "mod_math";
	import "mod_rand";
	import "mod_time";
	import "mod_timers";
	import "mod_file";
	import "mod_dir";
	import "mod_mem";
	import "mod_string";
	
	type puntos;
	x,y;
end
type dcolor;
byte r,g,b;
end

const
	piso=85;
	pared=21;
	l_salto=38;
	ascender=54;
	fuego=232;
global
	tot=0;
	durezas=0;
	scroll_g;
	f_humo;
	f_zona;
	f_boton;
	f_obj;
	f_rocas;
	f_enem[6];
	f_modl;
	paleta;
	color_tinta;
	figura;
	fondo2;
	string cargado;
	ntinta[4];
	chumos=0;
	bloqueo=0;
	puntuaje=0;
	vidas=3;
	hum_liv=0;
	zona=2;
	cp[6];
	strll;
	mslft;
	volumen_song=90;
	volumen_efecto=128;
	musica;
	s_golp;
	s_lamento;
	s_boton;
	s_mon;
	level_desb=0;
	puntuaje_total;
	string princip_ar;
	tip_j;
	string idioma="ingles";
	string mensajes[12];
	s_mor;
	s_gan;
	s_chisp;
	s_arana;
	s_lan;
	s_vac;
	s_mur;
	include "jkeys.lib"
local
	direccion;
	salto;
	id2;
begin
	paleta=pal_load("paleta/default.pal");
	scroll_g=load_png("humo.png");
	set_icon(0,scroll_g);
	if ( os_id <> OS_GP2X_WIZ)
		scale_resolution = 06400480 ;
	else
		full_screen = true;
	end
	rand_seed(time());
	set_mode(320,240,16);
	unload_map(0,scroll_g);
	s_golp=load_wav("sonidos/golpe.wav");
	s_lamento=load_wav("sonidos/lamento.wav");
	s_boton=load_wav("sonidos/FX-Tones567.wav");
	s_mon=load_wav("sonidos/mons1.wav");
	s_gan=load_wav("sonidos/FX-Beats131.wav");
	s_mor=load_wav("sonidos/FX-Percussion362.wav");
	s_chisp=load_wav("sonidos/FX-Atmospheric84.wav");
	s_arana=load_wav("sonidos/FX-Abstract8.wav");
	s_lan=load_wav("sonidos/FX-Abstract14.wav");
	s_vac=load_wav("sonidos/FX-Abstract38.wav");
	s_mur=load_wav("sonidos/FX-Swishes533.wav");
	set_fps(40,1);
	load_fnt('fuentes/azul.fnt');
	load_fnt('fuentes/principal.fnt');
	jkeys_set_default_keys();
	strll=load_png("graficos/enemigos/chispas.png");
	mouse.graph=load_png("graficos/botones/it.png");
	for (z=0;z<6;z++)
		f_enem[z]=5000;
	end
	f_zona=load_fpg("graficos/logos/logos.fpg");
	fade(0,0,0,0);
	jkeys_controller();
	from x=1 to 3;
		put_screen(f_zona,x);
		fade(100,100,100,60);
		while (mouse.left) frame; end
		while (jkeys_state[_JKEY_MENU]) frame; end
		for  (z=0; z<100 and not jkeys_state[_JKEY_MENU] and not mouse.left; z++)
			frame;
		end
		
		
		fade(0,0,0,30);
	end
	fade(100,100,100,1);
	f_boton=load_fpg('graficos/botones/boton.fpg');
	cnarchivos(0,"carga/","*.id",&idioma);
	if (idioma=="")
		idioma="espanol.id";
	end
	load("carga/val.dat",volumen_song);
	load("carga/vals.dat",volumen_efecto);
	SET_SONG_VOLUME ( volumen_song );
	SET_CHANNEL_VOLUME ( -1, volumen_efecto );
	//pedir idioma
	
	carga_str("carga/"+idioma+"/textos.prg",&mensajes, sizeof(mensajes)/sizeof(string));
	
	menu();
	
end
#define fade_on(); fade(100,100,100,60);
#define fade_off(); fade(0,0,0,60);
#define /2 >>1
#define *2 <<1
include "edit_mapas.inc";
include "enemigos.inc";
include "gui.inc";
include "objetos.inc";

process menu();
private
	string text[7];
	string arch;
	archivo;
	int switc=-1;
	string nom[]="bosq","cab","fuego","golp","sirena","viento";
begin
	fade_off();
	let_me_alone();
	limpia_memoria();
	
	carga_str("carga/"+idioma+"/menus.prg",&text, 7);
	
	while (mouse.left) frame; end
	from z=0 to 6;
		boton_m(0,write_in_map(2,text[z],4),160,50+z*23,&switc,1,z,0,0,1,1);
	end
	scroll_g=load_png("graficos/zonas/ft16.png");
	f_humo=load_fpg("graficos/humos/"+nom[rand(0,5)]+".fpg");
	
	monito();
	put_screen(0,scroll_g);
	fade_on();
	musica=load_song("musica/wiklundandmalmen-rabbit_outfits.xm");
	FADE_MUSIC_IN (musica,-1,1000);
	vidas=3;
	frame;
	loop
		switch (switc):
			case 0:
				tip_j=0;
				while (mouse.left)
					frame;
				end
				f_boton=load_fpg('graficos/botones/boton.fpg');
				loop
					cacha_string(&arch);
					frame(0);
					if (arch=='')
						menu();
					end
					if (ucase(substr(arch,-4))<>".SAL");
						arch+=".sal";
					end
					if (file_exists("carga/"+arch) and not mensaje(150,10,0,mensajes[4]+" "+arch+"?"))
						continue;
					else
						break;
					end
				end
				if (arch<>"")
					princip_ar=arch;
					archivo=fopen("carga/"+princip_ar,O_WRITE);
					fwrite(archivo,puntuaje_total);
					fwrite(archivo,level_desb);
					fwrite(archivo,vidas);
					fwrite(archivo,hum_liv);
					fclose(archivo);
					
				end
				
				
				signal(type boton_m,s_kill);
				clear_screen();
				arch="carga/"+idioma+"/historia.prg";
				stop_song(); unload_song(musica);
				musica=load_song("musica/secret_legend_of_the.xm");
				FADE_MUSIC_IN (musica,-1,1000);
				cuenta(arch,2000);
				selecciona_zona();
			end
			case 1:
				tip_j=1;
				while (mouse.left)
					frame;
				end
				f_boton=load_fpg('graficos/botones/boton.fpg');
				cnarchivos(1,"carga/","*.sal",&arch);
				if (arch=="")
					menu();
				end
				archivo=fopen("carga/"+arch,O_READ);
				fread(archivo,puntuaje_total);
				fread(archivo,level_desb);
				fread(archivo,vidas);
				fread(archivo,hum_liv);
				fclose(archivo);
				princip_ar=arch;
				selecciona_zona();
			end
			
			case 2:
				while (mouse.left)
					frame;
				end
				clear_screen();
				crea_zona(); signal(id,s_kill);
			end
			case 3:
				tip_j=3;
				f_boton=load_fpg('graficos/botones/boton.fpg');
				cnarchivos(1,"arch_zlg_creados/","*.zlg",&arch);
				zona=-1;
				if (arch<>"")
					signal_action(s_kill,S_IGN);
					hum_liv=6;
					carga_zona("arch_zlg_creados/"+arch);
					
					
				else
					menu();
				end
				
				
				return;
			end
			case 4:
				opciones();
			end
			case 5:
				signal(type boton_m,s_kill);
				
				arch="carga/"+idioma+"/credit.prg";
				
				cuenta(arch,1400);
				menu();
			end
			case 6:
				exit();
			end
		end
		frame;
	end
end
process monito();
begin
	file=f_humo;
	graph=1;
	direccion=rand(1,4);
	x=100; y=100;
	loop
		if (rand (0,75)==8) pchispas(x,y); direccion=rand(1,4); end
		
		if (x>320) x=0; end
		if (x<0) x=320; end
		if (y<0) y=240; end
		if (y>240) y=0; end
		switch (direccion);
			case 1:
				x++;
				if (id2<>direccion) graph=1; flags=0; end
				if (++graph>3) graph=1; end
			end
			case 2:
				y--;
				if (id2<>direccion) graph=4; end
				if (++graph>6) graph=4; end
			end
			case 3:
				x--;
				
				if (id2<>direccion) graph=1; flags=1; end
				if (++graph>3) graph=1; end
			end
			case 4:
				if (id2<>direccion) graph=7; end
				y++;
				if (++graph>9) graph=7; end
			end
		end
		id2=direccion;
		frame;
	end
end
process opciones();
private
	fndo;
begin
	fade_off();
	let_me_alone();
	limpia_memoria();
	while (mouse.left) frame; end
	fndo=load_png("graficos/zonas/opci.png");
	put_screen(0,fndo);
	f_boton=load_fpg('graficos/botones/boton.fpg');
	write(2,180,20,4,mensajes[0]);
	barra(180,50,&volumen_song,1.44,0,0);
	write(2,180,120,4,mensajes[1]);
	barra(180,150,&volumen_efecto,1.44,0,0);
	boton_m(f_boton,10,238,50,&salto,0,-1,0,1,0,0);
	son.z=-50;
	boton_m(f_boton,10,238,150,&id2,0,-1,0,1,0,0);
	son.z=-50;
	musica=load_song("musica/beek-clumsy.it");
	
	boton_m(f_boton,20,158,200,&direccion,0,-1,0,0,0,0);
	
	fade_on();
	while (direccion<>-1)
		if (salto<>0) SET_SONG_VOLUME ( volumen_song ); play_song(musica,0); salto=0; while (mouse.left) frame; end end
		if (id2<>0) SET_CHANNEL_VOLUME ( -1, volumen_efecto );  play_wav(s_gan,0); id2=0; while (mouse.left) frame; end end
		frame;
	end
	SET_SONG_VOLUME ( volumen_song );
	SET_CHANNEL_VOLUME ( -1, volumen_efecto );
	save("carga/val.dat",volumen_song);
	save("carga/vals.dat",volumen_efecto);
	unload_map(0,fndo);
	let_me_alone();
	menu();
end

process opciones_tr();
private
	fndo;
	w1,w2;
begin
	signal(ALL_PROCESS,s_freeze);
	while (mouse.left) frame; end
	f_boton=load_fpg('graficos/botones/boton.fpg');
	w1=write(2,160,50,4,mensajes[0]);
	barra(160,80,&volumen_song,1.44,0,0);
	W2=write(2,160,103,4,mensajes[1]);
	barra(160,130,&volumen_efecto,1.44,0,0);
	boton_m(f_boton,10,218,80,&salto,0,-1,0,1,0,0);
	son.z=-50;
	boton_m(f_boton,10,218,130,&id2,0,-1,0,1,0,0);
	son.z=-50;
	boton_m(f_boton,20,150,160,&direccion,0,-1,0,0,0,0);
	fade_on();
	while (direccion<>-1)
		if (salto<>0) SET_SONG_VOLUME ( volumen_song ); play_song(musica,0); salto=0; end
		if (id2<>0) SET_CHANNEL_VOLUME ( -1, volumen_efecto );  play_wav(s_gan,0); id2=0; end
		frame;
	end
	SET_SONG_VOLUME ( volumen_song );
	SET_CHANNEL_VOLUME ( -1, volumen_efecto );
	delete_Text(w1);
	delete_Text(w2);
	save("carga/val.dat",volumen_song);
	save("carga/vals.dat",volumen_efecto);
	signal(ALL_PROCESS,s_wakeup);
	signal(father,s_kill);
	signal(id,s_kill_tree);
end



process selecciona_zona();
private
	cont;
	archivo;
	string arch;
begin
	fade_off();
	let_me_alone();
	limpia_memoria();
	musica=load_song("musica/secret_legend_of_the.xm");
	FADE_MUSIC_IN (musica,-1,1000);
	while (mouse.left)
		frame;
	end
	if (vidas<0)level_desb=1; vidas=0; end
	f_boton=load_fpg('graficos/botones/boton.fpg');
	file=f_zona=load_fpg("graficos/zonas/sel.fpg");
	put_screen(f_zona,1);
	fade_on();
	graph=2;
	if (zona<1) zona=1; end
	archivo=fopen("carga/"+princip_ar,O_WRITE);
	fwrite(archivo,puntuaje_total);
	fwrite(archivo,level_desb);
	fwrite(archivo,vidas);
	fwrite(archivo,hum_liv);
	fclose(archivo);
	zona=level_desb+1;
	get_point(f_zona,1,zona,&x,&y);
	jkeys_controller();
	for (z=1; z<zona; z++)
		get_point(f_zona,1,z,&id2,&salto);
		obj(f_zona,3,id2,salto,100);
	end
	
	if (tip_j==0)
		frame;
		
		arch="carga/"+idioma+"/tuto01.prg";
		
		f_boton=load_fpg('graficos/botones/boton.fpg');
		texttu(arch,9);
	end
	tip_j=1;
	write(1,17,180,4,mensajes[5]);
	write(1,119,180,4,mensajes[9]);
	write(1,66,147,4,mensajes[10]);
	write(1,66,213,4,mensajes[11]);
	if ( os_id == OS_GP2X_WIZ)
		set_center(f_zona,4,0,0);
		obj(f_zona,4,29,151,1);
	else
		set_center(f_zona,5,0,0);
		obj(f_zona,5,28,150,1);
	end
	loop
		if (jkeys_state[_JKEY_A]) break; end
		if (jkeys_state[_JKEY_B]) exit(); end
		if (jkeys_state[_JKEY_Y]) menu(); end
		if (jkeys_state[_JKEY_X])
			delete_text(all_text);
			
			arch="carga/"+idioma+"/tuto01.prg";
			
			if (not file_exists(f_boton))
				f_boton=load_fpg('graficos/botones/boton.fpg');
			end
			texttu(arch,9);
			
			write(1,17,180,4,mensajes[5]);
			write(1,119,180,4,mensajes[9]);
			write(1,66,147,4,mensajes[10]);
			write(1,66,213,4,mensajes[11]);
		end
		from z=1 to 16;
			get_point(f_zona,1,z,&id2,&salto);
			if (fget_dist(id2,salto,mouse.x,mouse.y)<25 and mouse.left and z<(level_desb+2) and zona<>z)
				cont=zona;
				zona=z;
				repeat
					if (cont<z) cont++;
					else cont--;
					end
                                        get_point(f_zona,1,cont,&id2,&salto);
					while (x<>id2 or y<>salto)
						if (x>id2) x--;
						elseif (x<id2) x++;
						end
						if (y>salto) y--;
						elseif (y<salto) y++;
						end
						frame;
					end
					
				until (cont==z);
				break;
				
			end
		end
		frame;
	end
	zona--;
	let_me_alone();
	switch (level_desb);
		case 3:hum_liv=1;
		end
		case 6:hum_liv=3;
		end
		case 9:hum_liv=4;
		end
		case 12:hum_liv=6;
		end
	end
	switch (zona)
		case 0:
			carga_zona("zonas/tuto.zlg"); 
			return;
		end
		case 1:
			carga_zona("zonas/zonuno.zlg");
			return;
		end
		case 2:
			carga_zona("zonas/zona dos.zlg");
			return;
		end
		case 3:
			carga_zona("zonas/enem.zlg");
			return;
		end
		case 4:
			carga_zona("zonas/lava.zlg");
			return;
		end
		case 5:
			carga_zona("zonas/mosque.zlg");
			return;
		end
		case 6:
			carga_zona("zonas/embudo.zlg");
			return;
		end
		case 7:
			carga_zona("zonas/queso.zlg");
			return;
		end
		case 8:
			carga_zona("zonas/salt.zlg");
			return;
		end
		case 12:
			carga_zona("zonas/recorre.zlg");
			return;
		end
		case 10:
			carga_zona("zonas/mult.zlg");
			return;
		end
		case 11:
			carga_zona("zonas/sscen.zlg");
			return;
		end
		case 13:
			carga_zona("zonas/buuu.zlg");
			return;
		end
		case 14:
			carga_zona("zonas/xjco.zlg");
			return;
		end
		case 9,15:
			carga_zona("zonas/pq.zlg");
			return;
			
		end
	end
end

process elige();
begin
	fade_off();
	let_me_alone();
	limpia_memoria();
	fade_on();
	loop
		switch (zona);
			case 5:
			end
		end
		frame;
	end
end
process intersec(x,y,x1,y1);
begin
	if (mouse.x>x and mouse.x<x1  and mouse.y>y and mouse.y<y1)
		return(1);
	else
		return(0);
	end
end

function limpia_memoria();
begin
	delete_text(0);
	delete_draw(0);
	if (map_exists(0,scroll_g))
		stop_scroll(0);
		unload_map(0,scroll_g);
	end
	clear_screen();
	if (fpg_exists(f_humo))
		unload_fpg(f_humo);
	end
	if (fpg_exists(f_modl))
		unload_fpg(f_modl);
	end
	if (fpg_exists(f_obj))
		unload_fpg(f_obj);
	end
	if (fpg_exists(f_rocas))
		unload_fpg(f_rocas);
	end
	if (fpg_exists(f_zona))
		unload_fpg(f_zona);
	end
	if (fpg_exists(f_boton))
		unload_fpg(f_boton);
	end
	for (z=0;z<6;z++)
		if (fpg_exists(f_enem[z]))
			unload_fpg(f_enem[z]);
		end
	end
	if (musica<>0) stop_song(); unload_song(musica); musica=0; end
end
function carga_humo_rand();
private
string nom[]="bosq","cab","fuego","golp","sirena","viento";
begin
return(load_fpg("graficos/humos/"+nom[rand(0,5)]+".fpg"));
end


process carga_zona(string arch);
private
	ancho,alto,ancho1,alto1;
	float cancho,calto;
	int pos;
	int cnt;
	tx_b;
begin
	fade(0,0,0,0);
	let_me_alone();
	chumos=0;
	frame;
	limpia_memoria();
	frame(0);
	jkeys_controller();
	fade_on();
	tx_b=write (2,100,100,4,mensajes[6]);
	frame;
        switch (zona)
		case 0..3:
        f_humo=load_fpg('graficos/humos/cab.fpg');
        end
        case 4..5:
        f_humo=load_fpg('graficos/humos/fuego.fpg');
        end
        case 6..7:
        f_humo=load_fpg('graficos/humos/golp.fpg');
        end
        case 10..12:
        f_humo=load_fpg('graficos/humos/sirena.fpg');
        end
        case 13:
        f_humo=load_fpg('graficos/humos/bosq.fpg');
        end
        case 14:
        f_humo=load_fpg('graficos/humos/viento.fpg');
        end
        default:
        f_humo=carga_humo_rand();
        end
        end

        f_modl=load_fpg('graficos/humos/modl.fpg');
	define_region(1,0,0,320,200);
	f_boton=load_fpg('graficos/botones/boton.fpg');
	f_obj=load_fpg('graficos/zonas/objetos.fpg');
	scroll.camera=0;
	carga_nivel(arch);
	ancho=graphic_info (0, scroll_g, g_wide );
	alto=graphic_info (0, scroll_g, G_HEIGHT);
	ancho1=graphic_info (0, fondo2, g_wide );
	alto1=graphic_info (0, fondo2, G_HEIGHT);
	cancho=ancho1*1.0/ancho;
	calto=alto1*1.0/alto;
	reloj(240);
	dibuja();
	pod(220,0,&pos);
	pod(240,1,&pos);
	pod(260,2,&pos);
	x=100; y=100;
	obj(f_boton,8,160,220,6);
	
	switch (zona)
		case 0:
			from z=1 to 4;
				ntinta[z-1]=100;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
		end
		case 1:
			from z=1 to 4;
				ntinta[z-1]=0;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
			ntinta[2]=20;
		end
		case 2:
			from z=1 to 4;
				ntinta[z-1]=100;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
		end
		case 3:
			from z=1 to 4;
				ntinta[z-1]=0;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
			ntinta[1]=300;
			ntinta[2]=50;
		end
		case 4:
			from z=1 to 4;
				ntinta[z-1]=0;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
		end
		case 5..11:
			from z=1 to 4;
				ntinta[z-1]=100;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
		end

		case 12:
		from z=1 to 4;
				ntinta[z-1]=100;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
		end

		case 13:
			from z=1 to 4;
				ntinta[z-1]=100;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
		end
		case 14:
			from z=1 to 4;
				ntinta[z-1]=100;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
		end
		case 9,15:
			from z=1 to 4;
				ntinta[z-1]=100;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
			
		end
		default:
			from z=1 to 4;
				ntinta[z-1]=100;
				write_var(1,z*25,230,4,ntinta[z-1]);
			end
		end
	end
	
	boton_m(f_boton,3,25,212,&color_tinta,0,ascender ,0,0,0,1);
	boton_m(f_boton,4,50,212,&color_tinta,0,piso ,0,0,0,1);
	boton_m(f_boton,1,75,212,&color_tinta,0,pared,0,0,0,1);
	boton_m(f_boton,2,100,212,&color_tinta,0,l_salto,0,0,0,1);
	boton_m(f_boton,5,125,212,&color_tinta,0,0,0,0,0,1);
	boton_m(f_boton,6,150,212,&figura,0,3,0,0,0,1);
	boton_m(f_boton,7,175,212,&figura,0,2,0,0,0,1);
	boton_m(f_boton,9,200,220,&cnt,0,-1,0,1,0,1);
	boton_m(f_boton,9,280,220,&cnt,0,1,0,0,0,1);
	color_tinta=piso;
	puntuaje_total+=puntuaje;
	vidas+=puntuaje/100;
	f_rocas=load_fpg("graficos/enemigos/rocas.fpg");
	write_int(1,307,230,4,&puntuaje);
	write(1,280,230,4,"p x ");
	obj(f_modl,24,127,230,5);
	write_int(1,165,230,4,&vidas);
	write(1,142,230,4,"x");
	from direccion=0 to 5;
		cp[direccion]=0;
	end
	scroll.x0=0;
	scroll.y0=0;
	frame;
	switch (zona)
		case 3,6,9,12,15:
			enem_g(zona/3);

		end
	end
	if (tip_j==3) zona=rand(0,15); end
	switch (zona)
		case 0:
			musica=load_song("musica/quasian_-_my_cup_of_tea.it");
		end
		case 1:
			musica=load_song("musica/hyo-u1.it");
		end
		case 2:
			musica=load_song("musica/my_valentine.xm");
		end
		case 3:
			musica=load_song("musica/soft_maniac_-_downtime.xm");
		end
		case 4:
			musica=load_song("musica/quasian_-_happy-go-lucky.it");
		end
		case 5:
			musica=load_song("musica/polka_puke.xm");
		end
		case 6:
			musica=load_song("musica/esoteric_-_2_be_with_you.it");
		end
		case 7:
			musica=load_song("musica/beek-clumsy.it");
		end
		case 8:
			musica=load_song("musica/sergeeo-polvo_sa.it");
		end
		case 12:
			musica=load_song("musica/jessica2.xm");
		end
		case 10:
			musica=load_song("musica/radix-unreal_superhero.xm");
		end
		case 11:
			musica=load_song("musica/wings_over_dunwyn.xm");
		end
		case 13:
			musica=load_song("musica/alone_in_the_scene.xm");
		end
		case 14:
			musica=load_song("musica/wiklundandmalmen-rabbit_outfits.xm");
		end
		case 9:
			musica=load_song("musica/beek-oh_delia.it");
		end
		case 15:
			musica=load_song("musica/joule-littlewe_kladdcakes.xm");
		end
	end
	if (tip_j==3) zona=-1; end
	FADE_MUSIC_IN (musica,-1,1000);
	delete_text(tx_b);
	IF (zona==0)
		
		
		arch="carga/"+idioma+"/tuto02.prg";
		
		
		tutorial(arch,9);//terminar
	end
	puntuaje=0;
	loop
		
		pos+=cnt;
		cnt=0;
		if (pos<0)
			pos=0;
		end
		if (pos>3)
			pos=3;
		end
		if (chumos==-1)
			game_over();
		end
		if (jkeys_state[_JKEY_MENU]) pause(0); end
		if (mouse.left) mslft=true; else  mslft=false; end
		if (zona%3<>0)
			if (jkeys_state[_JKEY_UP]) scroll.camera=0; scroll.y0-=3; end
			if (jkeys_state[_JKEY_DOWN])  scroll.camera=0; scroll.y0+=3; end
			if (jkeys_state[_JKEY_LEFT])  scroll.camera=0; scroll.x0-=3; end
			if (jkeys_state[_JKEY_RIGHT])  scroll.camera=0; scroll.x0+=3; end
			
			if (jkeys_state[_JKEY_B])
				if (scroll.camera==0)
					scroll.camera=get_id(type humo);
				else
					while ((id2=get_id(type humo))<>scroll.camera)
					end
					scroll.camera=get_id(type humo);
				end
				while (jkeys_state[_JKEY_B]) frame; end
			end
		end
		
		//if (key(_s)) humo(50,50); end
		
		//while (key(_s)) frame; end
		if (exit_status)
			exit();
		end
		
		frame;
	end
	
end

process obj(file,graph,x,y,z);
begin
	loop
		frame;
	end
end

process dibuja();
private
	
	puntos ant;
	dcolor c_col;
	float ang,faux;
	byte auxf;
	byte numcl;
	//float dist;
begin
	
	
	//drawing
	drawing_color(piso);
	drawing_map(0,scroll_g);
	z=0;
	figura=2;
	//write_var(0,100,100,4,dist);
	loop
		drawing_color(color_tinta);
		x=mouse.x;
		y=mouse.y;
		if (mouse.left and map_get_pixel(0,scroll_g,x,y)==fuego) mouse.size=150; else mouse.size=100; end
		if (figura<>1)
			auxf=figura;
		end
		switch (color_tinta);
			case l_salto:
				numcl=3;
			end
			case pared:
				numcl=2;
			end
			case ascender :
				numcl=0;
			end
			case  piso:
				numcl=1;
			end
		end
		if (color_tinta==ascender) figura=1; else figura=auxf; end
		if (mouse.y<200)
			if (color_tinta==0)
				if (mouse.left)
					drawing_color(0);
					ant.x=mouse.x+scroll.x0; ant.y=mouse.y+scroll.y0;
					while(mouse.left)
						//if (bloqueo==9) break; end
						if (mouse.y>200) break; end
						frame;
						ang=fget_angle(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0);
						faux=fget_dist(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0);
						if (faux>0)
							drawing_color(0);
							for (z=0;z<faux;z++)
								if (bloqueo==9) break; end
								draw_fcircle(ant.x+cos(ang)*z,ant.y-sin(ang)*z,5);
								
							end
							ant.x+=cos(ang)*z;
							ant.y-=sin(ang)*z;
						end
					end
					
				end
			elseif (ntinta[numcl]<>0)
				switch (figura)
					
					case 1:
						if (mouse.left)
							drawing_z(500);
							GET_COLORS (paleta, color_tinta, 1, &c_col );
							drawing_color(rgb(c_col.r,c_col.g,c_col.b));
							ant.x=mouse.x; ant.y=mouse.y;
							signal(father,s_freeze);
							signal(type boton_m,s_freeze);
							signal(type pod,s_freeze);
							while (mouse.left)
								drawing_color(rgb(c_col.r,c_col.g,c_col.b));
								if (bloqueo==8) break; end
								if (z<>0) delete_draw(0); end
								
								if (mouse.y<200)
									if ((abs(ant.y-mouse.y))<ntinta[numcl])
										z=draw_line(ant.x,ant.y,ant.x,mouse.y);
									else
										z=draw_line(ant.x,ant.y,ant.x,ant.y+(ntinta[numcl])*(mouse.y>ant.y? 1 : -1));
									end
								else
									if ((abs(ant.y-mouse.y))<ntinta[numcl])
										z=draw_line(ant.x,ant.y,ant.x,200);
									else
										z=draw_line(ant.x,ant.y,ant.x,ant.y+(ntinta[numcl])*(mouse.y>ant.y? 1 : -1));
									end
									
									
								end
								frame;
							end
							z=0;
							delete_draw(0);
							drawing_map(0,scroll_g);
							drawing_color(color_tinta);
							if  (bloqueo<>8)
								if (mouse.y<200 )
									if ((abs(ant.y-mouse.y))<ntinta[numcl])
										z=draw_line(ant.x+scroll.x0,ant.y+scroll.y0,ant.x+scroll.x0,mouse.y+scroll.y0);
										ntinta[numcl]-=abs(ant.y-mouse.y);
									else
										z=draw_line(ant.x+scroll.x0,ant.y+scroll.y0,ant.x+scroll.x0,ant.y+scroll.y0+(ntinta[numcl])*(mouse.y>ant.y? 1 : -1));
										ntinta[numcl]=0;
									end
								else
									
									if ((abs(ant.y-mouse.y))<ntinta[numcl])
										z=draw_line(ant.x+scroll.x0,ant.y+scroll.y0,ant.x+scroll.x0,200+scroll.y0);
										ntinta[numcl]-=abs(ant.y-200);
									else
										z=draw_line(ant.x+scroll.x0,ant.y+scroll.y0,ant.x+scroll.x0,ant.y+scroll.y0+(ntinta[numcl])*(mouse.y>ant.y? 1 : -1));
										ntinta[numcl]=0;
									end
								end
							end
							signal(father,s_wakeup);
							signal(type boton_m,s_wakeup);
							signal(type pod,s_wakeup);
						end
					end
					case 2:
						if (mouse.left)
							while(mouse.left)
								
								if (mouse.y>200 or bloqueo==8) break; end
								ant.x=mouse.x+scroll.x0; ant.y=mouse.y+scroll.y0;
								frame;
								drawing_color(color_tinta);
								if (ntinta[numcl]>0)
									if((fget_dist(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0))<ntinta[numcl])
										draw_line(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0);
										ntinta[numcl]-=fget_dist(ant.x,ant.y,mouse.x+scroll.x0,mouse.y+scroll.y0);
									else
										ang=fget_angle(ant.x,ant.y,mouse.x,mouse.y);
										draw_line(ant.x,ant.y,ant.x+ntinta[numcl]*cos(ang),ant.y-ntinta[numcl]*sin(ang));
										ntinta[numcl]=0;
									end
									
								end
								
							end
						end
					end
					case 3:
						if (mouse.left)
							drawing_z(500);
							signal(type boton_m,s_freeze);
							GET_COLORS (paleta, color_tinta, 1, &c_col );
							drawing_color(rgb(c_col.r,c_col.g,c_col.b));
							ant.x=mouse.x; ant.y=mouse.y;
							while (mouse.left)
								if (bloqueo==8) break; end
								drawing_color(rgb(c_col.r,c_col.g,c_col.b));
								if (z<>0) delete_draw(0); end
								//z=draw_line(ant.x,ant.y,mouse.x,mouse.y);
								if (mouse.y<200)
									if ((fget_dist(ant.x,ant.y,mouse.x,mouse.y))<ntinta[numcl])
										z=draw_line(ant.x,ant.y,mouse.x,mouse.y);
									else
										ang=fget_angle(ant.x,ant.y,mouse.x,mouse.y);
										z=draw_line(ant.x,ant.y,ant.x+ntinta[numcl]*cos(ang),ant.y-ntinta[numcl]*sin(ang));
									end
								else
									if ((fget_dist(ant.x,ant.y,ant.x+(1.0*(200-ant.y)/(mouse.y-ant.y))*(mouse.x-ant.x),200))<ntinta[numcl])
										z=draw_line(ant.x,ant.y,ant.x+(1.0*(200-ant.y)/(mouse.y-ant.y))*(mouse.x-ant.x),200);
										
									else
										
										ang=fget_angle(ant.x,ant.y,mouse.x,mouse.y);
										z=draw_line(ant.x,ant.y,ant.x+ntinta[numcl]*cos(ang),ant.y-ntinta[numcl]*sin(ang));
										
									end
									
									
								end
								frame;
							end
							z=0;
							delete_draw(0);
							drawing_map(0,scroll_g);
							
							drawing_color(color_tinta);
							if (bloqueo<>8)
								if (mouse.y<200)
									if ((fget_dist(ant.x,ant.y,mouse.x,mouse.y))<ntinta[numcl])
										z=draw_line(ant.x+scroll.x0,ant.y+scroll.y0,mouse.x+scroll.x0,mouse.y+scroll.y0);
										ntinta[numcl]-=fget_dist(ant.x,ant.y,mouse.x,mouse.y);
									else
										ang=fget_angle(ant.x,ant.y,mouse.x,mouse.y);
										z=draw_line(ant.x+scroll.x0,ant.y+scroll.y0,ant.x+scroll.x0+ntinta[numcl]*cos(ang),ant.y+scroll.y0-ntinta[numcl]*sin(ang));
										ntinta[numcl]=0;
									end
								else
									
									if ((fget_dist(ant.x,ant.y,mouse.x,mouse.y))<ntinta[numcl])
										draw_line(ant.x+scroll.x0,ant.y+scroll.y0,ant.x+scroll.x0+(1.0*(200-ant.y)/(mouse.y-ant.y))*(mouse.x-ant.x),200+scroll.y0);
										ntinta[numcl]-=fget_dist(ant.x,ant.y,ant.x+(1.0*(200-ant.y)/(mouse.y-ant.y))*(mouse.x-ant.x),200);
									else
										ang=fget_angle(ant.x,ant.y,mouse.x,mouse.y);
										//z=fget_dist(ant.x,ant.y,ant.x+(1.0*(200-ant.y)/(mouse.y-ant.y))*(mouse.x-ant.x),200);
										draw_line(ant.x+scroll.x0,ant.y+scroll.y0,ant.x+scroll.x0+ntinta[numcl]*cos(ang),ant.y+scroll.y0-ntinta[numcl]*sin(ang));
										ntinta[numcl]=0;
									end
								end
								signal(type boton_m,s_wakeup);
							end
							
						end
					end
				end
			end
		end
		bloqueo=0;
		frame;
	end
end

process humo(x,y);
	//private
	//byte ic;
begin
	ctype=c_scroll;
	direccion=1;
	file=f_humo;
	graph=1;
	from z=1 to 3;
	set_center(f_humo,z,graphic_info(f_humo,z,g_wide)/2,graphic_info(f_humo,z,g_height));
	end
        z=2;
	direccion=rand(1,-1); if (direccion==0) frame; direccion=-1; end
	loop
		
		if (++graph>3) graph=1; end
		if (map_get_pixel(0,scroll_g,x,y)==-1) id2=4; end
		
		if (graph<>8)gravedad();end
		if (z=>0)
			if (salto>0)
				salto--;
			end
			if (direccion==1)
				flags=0;
			else
				flags=1;
			end
			x+=direccion;
		elseif (z<0)
			graph=4;
			while (map_get_pixel(0,scroll_g,x,y)<>ascender)
				y--;
				if (++graph>6) graph=4; end
				frame;
			end
			
			while (map_get_pixel(0,scroll_g,x,y)==ascender)
				y--;
				if (++graph>6) graph=4; end
				frame;
			end
			z=2;
			x+=direccion*=-1;
			graph=1;
		end
		if (exists(type prop) and id2==4)
		id2=0;
		end
		if (id2==4 )

			graph=7;
			for (z=0 ;z< 50;z++);
				y-=2;
				angle+=30000;
				size+=5;
				if (exists(type menu)) break; end
				frame;
			end
			while (not out_region(id,1))
				y+=4;
				angle+=30000;
				size-=5;
				if (exists(type menu)) break; end
				frame;
			end
			chumos=-1;
			play_wav(s_mor,0);
			signal(id,s_kill);
		end
		if (id2=collision(type puerta))
			z=-40;
			while (get_dist(id2)>10)
				if (++graph>3) graph=1; end
				if (x>id2.x)x--; else x++;end
				if (y>id2.y)y--; else y++; end
				
				frame;
			end
			graph=4;
			for (size=100;size> 20;size-=3)
				if (++graph>6) graph=4; end
				if (exists(type menu)) break; end
				frame;
			end
			chumos--;
			signal(id,s_kill);
		end
		id2=0;
		frame;
	end
end

function gravedad();
private x1;
	int col;
begin
	x=father.x; y=father.y;
	
	if (map_get_pixel(0,scroll_g,x,y-5)<>0 and map_get_pixel(0,scroll_g,x,y-6)<>0) father.direccion*=-1;  end
	from z=-5 to 5;
		col=map_get_pixel(0,scroll_g,x,y+z);
		if (col==fuego)
			father.id2=4;
			return;
		elseif (col==l_salto)
			father.salto=15;
			break;
		elseif (col==ascender)
									
			father.z=z;
			break;
		elseif (col<>0)
			father.salto=0;
			break;
		end
		if (map_get_pixel(0,scroll_g,x+father.direccion,y+z)==pared) father.direccion*=-1;  end
		
	end
	if (father.salto<>0)
		father.y-=5;
	else
		father.y+=z;
	end
	return;
end

process pause(byte val);
private
	string text[7];
	string arch;
	int switc=-1;
	int b[7];
	cont;
begin
	
	graph=new_map(150,150,16);
	map_clear(file,graph,rgb(153,102,0));
	drawing_map(0,graph);
	drawing_color(rgb(64,36,0));
	draw_rect(0,0,149, 149);
	drawing_color(rgb(148,84,0));
	draw_rect(1,1,148,148);
	signal(ALL_PROCESS,s_freeze);
	carga_str("carga/"+idioma+"/pausa.prg",&text,7);
	x=160;
	y=100;
	if (val==1)
		from z=0 to 3;
			b[z]=boton_m(0,write_in_map(2,text[z],4),160,40+z*23,&switc,1,z,0,0,1,1);
		end
		from cont=5 to 6;
			b[z]=boton_m(0,write_in_map(2,text[cont],4),160,40+z*23,&switc,1,cont,0,0,1,1);
			z++;
		end
	else
		z=0;
		b[z]=boton_m(0,write_in_map(2,text[z],4),160,50+z*23,&switc,1,z,0,0,1,1);
		
		from cont=3 to 6;
			z++;
			b[z]=boton_m(0,write_in_map(2,text[cont],4),160,50+z*23,&switc,1,cont,0,0,1,1);
		end
		
	end
	drawing_map(0,scroll_g);
	loop
		switch (switc):
			case 0:
				while (mouse.left)
					frame;
				end
				signal(ALL_PROCESS,s_wakeup);
				from z=0 to 6;
					if (exists(b[z]))
						signal(b[z],s_kill);
					end
				end
				
				signal(id,s_kill);
				
			end
			
			case 2:
				if (val==1)
					loop
						cacha_string(&arch);
						frame(0);
						if (arch=='') 
							break;
						end
						if (ucase(substr(arch,-4))<>".ZLG");
							arch+=".zlg";
						end
						if (file_exists("arch_zlg_creados/"+arch) and not mensaje(x+10,10,0,mensajes[4]+arch+"?"))
							continue;
						else
							break;
						end
					end
					if (arch<>"")
						cargado=arch;
						guarda_mapa("arch_zlg_creados/"+arch);
					end
				end
				//frame;
				signal(type edita_mapa,s_freeze);
				from z=0 to 6;
					if (exists(b[z]))
						signal(b[z],s_kill);
					end
				end
				frame;
				x=-1000;
				while(mouse.left)
					frame;
				end
				signal(type edita_mapa,s_wakeup);
				unload_map(0,graph);
				signal(id,s_kill);
				
			end
			
			case 3:
				while (mouse.left)
					frame;
				end
				menu(); signal(id,s_kill);
			end
			case 4:
				while (mouse.left)
					frame;
				end
				selecciona_zona(); signal(id,s_kill);
			end
			case 5:
				from z=0 to 6;
					if (exists(b[z]))
						signal(b[z],s_kill);
					end
				end
				frame;
				opciones_tr();
			end
			case 6:
				exit();
			end
			case 1:
				signal(type planta,s_kill);
				signal(type bloquea,s_kill);
				frame;
				cnarchivos(1,"arch_zlg_creados/","*.zlg",&arch);
				if (arch<>"")
					carga_mapa("arch_zlg_creados/"+arch);
				end
				signal(ALL_PROCESS,s_wakeup);
				frame;
				signal(type edita_mapa,s_freeze);
				from z=0 to 6;
					if (exists(b[z]))
						signal(b[z],s_kill);
					end
				end
				frame;
				while(mouse.left)
					frame;
				end
				signal(type edita_mapa,s_wakeup);
				signal(id,s_kill);
			end
		end
		frame;
	end
	onexit;
	unload_map(0,graph);
end

function guarda_mapa(string nombre);
private
	archivo;
	byte * arr;
	ancho,alto;
	cant;
	elems;
begin
	archivo=fopen(nombre,O_ZWRITE);
	arr=map_buffer(0,scroll_g);
	ancho=graphic_info (0, scroll_g, g_wide );
	alto=graphic_info (0, scroll_g, G_HEIGHT);
	cant=ancho*alto;
	fwrite(archivo,ancho);
	fwrite(archivo,alto);
	for (z=0;z<cant;z++)
		fwrite(archivo,arr[z]);
	end
	elems=cant_pross(type bloquea);
	fwrite(archivo,elems);
	id2=get_id(type bloquea);
	while (id2<>0)
		fwrite(archivo,id2.x);
		fwrite(archivo,id2.y);
		fwrite(archivo,id2.salto);
		fwrite(archivo,id2.direccion);
		fwrite(archivo,id2.z);
		id2=get_id(type bloquea);
	end
	elems=cant_pross(type planta);
	fwrite(archivo,elems);
	id2=get_id(type planta);
	while (id2<>0)
		fwrite(archivo,id2.x);
		fwrite(archivo,id2.y);
		fwrite(archivo,id2.graph);
		id2=get_id(type planta);
	end
	fclose(archivo);
end

function carga_mapa(string nombre);
private
	archivo;
	byte * arr;
	ancho,alto;
	cant,cr;
	elems;
begin
puntuaje=40;
	archivo=fopen(nombre,O_ZREAD);
	stop_scroll(0);
	unload_map(0,scroll_g);
	fread(archivo,ancho);
	fread(archivo,alto);
	cant=ancho*alto;
	scroll_g=new_map(ancho,alto,8);
	pal_map_assign(0,scroll_g,paleta);
	arr=map_buffer(0,scroll_g);
	for (z=0;z<cant;z++)
		fread(archivo,arr[z]);
	end
	fread(archivo,elems);
	for (z=0;z<elems;z++)
		fread(archivo,x);
		fread(archivo,y);
		fread(archivo,salto);
		fread(archivo,direccion);
		fread(archivo,cr);
		bloquea(x,y,salto,direccion,cr);
		puntuaje--;
	end
	fread(archivo,elems);
	for (z=0;z<elems;z++)
		fread(archivo,x);
		fread(archivo,y);
		fread(archivo,graph);
		planta(x,y,graph);
		puntuaje--;
	end
	fclose(archivo);
	start_scroll(0,0,scroll_g,0,1,0);
end

function cant_pross(x);
begin
	id2=0;
	y=get_id(x);
	while (y<>0)
		id2++;
		y=get_id(x);
	end
	frame;
	return(id2);
end


function carga_nivel(string nombre);
private
	archivo;
	byte * arr;
	ancho,alto;
	cant,cr;
	elems;
begin
	archivo=fopen(nombre,O_ZREAD);
	fread(archivo,ancho);
	fread(archivo,alto);
	cant=ancho*alto;
	scroll_g=new_map(ancho,alto,8);
	pal_map_assign(0,scroll_g,paleta);
	arr=map_buffer(0,scroll_g);
	for (z=0;z<cant;z++)
		fread(archivo,arr[z]);
	end
	fread(archivo,elems);
	for (z=0;z<elems;z++)
		fread(archivo,x);
		fread(archivo,y);
		fread(archivo,salto);
		fread(archivo,direccion);
		fread(archivo,cr);
		bloquea_r(x,y,salto,direccion,cr);
	end
	fread(archivo,elems);
	for (z=0;z<elems;z++)
		fread(archivo,x);
		fread(archivo,y);
		fread(archivo,graph);
		switch (graph);
			case 1:
				humo(x,y);
				chumos++;
			end
			case 2:
				puerta(x,y);
			end
			case 3:
				if (!fpg_exists(f_enem[0]))
					f_enem[0]=load_fpg("graficos/enemigos/vaca.fpg");
				end
				vaca(x,y);
			end
			case 4:
				if (!fpg_exists(f_enem[1]))
					f_enem[1]=load_fpg("graficos/enemigos/bac.fpg");
				end
				lanca(x,y);
			end
			case 5:
				if (!fpg_exists(f_enem[2]))
					f_enem[2]=load_fpg("graficos/enemigos/tor.fpg");
				end
				toro(x,y);
			end
			case 6:
				if (!fpg_exists(f_enem[3]))
					f_enem[3]=load_fpg("graficos/enemigos/agua.fpg");
				end
				agua(x,y);
			end
			case 7:
				if (!fpg_exists(f_enem[4]))
					f_enem[4]=load_fpg("graficos/enemigos/arana.fpg");
				end
				arana(x,y);
			end
			case 10:
				if (!fpg_exists(f_enem[5]))
					f_enem[5]=load_fpg("graficos/enemigos/volad.fpg");
				end
				volador(x,y);
			end
			case 11..14:
				tintas(x,y,graph-10,30);
			end
		end
	end
	fclose(archivo);
	start_scroll(0,0,scroll_g,0,1,0);
end

process puerta(x,y);
begin
	ctype=c_scroll;
	graph=load_png('graficos/zonas/puerta_8.png');
	z=500;
	while (not exists(type humo))
		frame;
	end
	z=50;
	loop
		if (chumos==0)
			fade_music_off(1000);
			play_wav(s_gan,0);
			write(2,220,55,4,puntuaje);
			write(2,220,85,4,puntuaje/100);
			write(2,220,98,4,vidas);
			write(2,220,125,4,puntuaje_total+puntuaje);
			texttu("carga/"+idioma+"/tabla.prg",8);
			if (level_desb<=zona)
				level_desb=zona+1;
			end
			if (tip_j==3) menu(); else selecciona_zona();  end
		end
		frame;
	end
	onexit;
	unload_map(file,graph);
end

process reloj(salto);
private
	string fech;
begin
	timer[0]=0;
	x=305;
	y=210;
	write_var(1,x,y,4,fech);
	graph=new_map(25,13,16);
	map_clear(file,graph,rgb(153,102,0));
	drawing_map(0,graph);
	drawing_color(rgb(64,36,0));
	draw_rect(0,0,24,12);
	drawing_color(rgb(148,84,0));
	draw_rect(1,1,23,11);
	z=-89;
	loop
		if (timer[0]>100)
			timer[0]=0; salto--; fech=salto/60+':'+salto % 60;
			from direccion=0 to 5;
				if (cp [direccion]>0) cp[direccion]--; end
			end
		end
		if (salto<1) game_over(); end
		frame;
	end
end

process game_over();
begin
	fade_off();
	let_me_alone();
	limpia_memoria();
	write(2,160,110,4,mensajes[2]);
	fade_on();
	jkeys_controller();
	vidas--;
	salto=write_in_map(2,"Menu",4);
	obj(0,salto,160,190,-20);

	loop
		son.size=rand(90,110);
                if (jkeys_state[_JKEY_MENU] or jkeys_state[_JKEY_A])
		signal(son,s_kill);
		unload_map(0,salto);
                if (tip_j==3)
                 menu();
                 else 
                 selecciona_zona(); end 
                 end
		frame;
	end
end

function dentro(id2);
begin
	while ((salto=get_id(id2))<>0)
		if (not out_region(salto,1)) return(1); end
	end
	return(0);
end

function cuenta(string arch,int vel);
begin
	jkeys_controller();
	id2=fopen(arch,O_READ);
	while ((not jkeys_state[_JKEY_Menu]) and !feof(id2))
		mse(160,240,-5,fgets(id2),-5,0);
		son.salto=200;
		frame(vel);
	end
	
	while (exists(type mse));
		if (jkeys_state[_JKEY_Menu]) break; end
		frame;
	end
	fclose(id2);
end

function carga_str(string arch,string * elm, int salto);
begin
	id2=fopen(arch,O_READ);
	for (z=0;z<salto; z++);
		elm[z]=fgets(id2);
	end
	fclose(id2);
end


process tutorial(string arch,int salto);
private
	color[]=ascender,pared,l_salto,piso,0;
	int var;
begin
	id2=fopen(arch,O_READ);
	mensaje(160,20,1,fgets(id2));
	from z=0 to 4;
		frame;
		var=write(1,160,20,4,fgets(id2));
		switch (z);
			case 0:
				obj(f_boton,3,160,40,-5);
			end
			case 1,2:
				obj(f_boton,z,160,40,-5);
			end
			case 3:
				obj(f_boton,4,160,40,-5);
			end
		end
		
		while (color_tinta<>color[z])
			frame;
		end
		if (z<4)
			signal(son,s_kill);
		end
		delete_text(var);
		frame;
		switch (z);
			case 0:
				texttu("carga/"+idioma+"/cazul.prg",4);
			end
			case 1:
				texttu("carga/"+idioma+"/crojo.prg",3);
			end
			case 2:
				texttu("carga/"+idioma+"/cverde.prg",1);
			end
			case 3:
				texttu("carga/"+idioma+"/cvioleta.prg",3);
			end
		end
		
	end
	mensaje(160,20,1,fgets(id2));
	mensaje(160,20,1,fgets(id2));
	
	var=write(1,160,20,4,fgets(id2));
	obj(f_boton,6,160,40,-5);
	while (figura<>3)
		frame;
	end
	signal(son,s_kill);
	delete_text(var);

	var=write(1,160,20,4,fgets(id2));
	obj(f_boton,7,160,40,-5);
	while (figura<>2)
		frame;
	end
	signal(son,s_kill);
	delete_text(var);
	fclose(id2);
	frame(0);
	texttu("carga/"+idioma+"/cfin.prg",12);
end

process fin();
begin
   let_me_alone();
   limpia_memoria();
   frame(0);
   cuenta("carga/"+idioma+"/fin.prg",1500);
   cuenta("carga/"+idioma+"/credit.prg",1400);
   selecciona_zona();
   end




