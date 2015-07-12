process barra(x,y,int * val,float eqv,int id2,salto);
begin
	z=-3;
	graph=19;
	file=f_boton;
	if (id2)
		signal(ALL_PROCESS,s_freeze);
	end
	if (salto)
		boton_m(f_boton,20,x+55,y,&direccion,0,0,0,0,1,0);
	end
	despl(x-56,y,val,eqv);
	direccion=-1;
	salto=write_var(1,x,y,4,*val);
	loop
		if (salto and direccion==0)
			signal(son,s_kill);
			delete_text(salto);
			frame;
			signal(id,s_kill);
		end
		frame;
	end
	onexit;
	delete_text(salto);
	if (id2)
		signal(ALL_PROCESS,s_wakeup);
		
	end
end

process despl(x,y,int *val,float fact);
begin
	z=-5;
	graph=18;
	file=f_boton;
	direccion=x;
	x+=*val/fact;
	loop
		if (intersec(x-4,y-8,x+4,y+8) & mouse.left)
			play_wav(s_boton,0);
			while (mouse.left)
				if (x=>direccion and x<=direccion+96)
					x=mouse.x;
					if (x<direccion) x=direccion; 
					end
					if (x>(direccion+89)) x=direccion+89; 
					end
					*val=(int)(x-direccion)*fact;
				end
				
				frame;
			end
		end
		frame;
	end
end

process boton_m(file,graph,x,y,int *swit,elim,val,angle,flags,morir,id2);
begin
	z=-50;
	loop
		if (graph<>0)
			direccion=graphic_info (file, graph, g_wide)/2;
			salto=graphic_info (file, graph,G_HEIGHT )/2;
			if (intersec(x-direccion,y-salto,x+direccion,y+salto) and mouse.left)

				if (morir)
				play_wav(s_boton,0);
					from size=100 to 50 step -5;
						alpha-=5;
						frame;
					end
					*swit=val;
					signal(id,s_kill);
				else
					size=130;
					*swit=val;
					if (id2)
					play_wav(s_boton,0);
						while (intersec(x-direccion,y-salto,x+direccion,y+salto) and mouse.left) frame; 
						end
					end
				end
			else
				size=100;
			end
		end
		frame;
	end
	onexit;
	if (elim)
		unload_map(file,graph);
	end
end

process boton_s(file,graph,int x,y,string *swit,string val,int angle,int flags,morir,id2);
begin
	z=-50;
	loop
		if (graph<>0)
			direccion=graphic_info (file, graph, g_wide)/2;
			salto=graphic_info (file, graph,G_HEIGHT )/2;
			if (intersec(x-direccion,y-salto,x+direccion,y+salto) and mouse.left)
				play_wav(s_boton,0);
				if (morir)
					from size=100 to 50 step -5;
						alpha-=5;
						frame;
					end
					*swit=val;
					signal(id,s_kill);
				else
					size=130;
					*swit=val;
					if (id2)
						while (intersec(x-direccion,y-salto,x+direccion,y+salto) and mouse.left) frame;
						end
					end
				end
			else
				size=100;
			end
		end
		frame;
	end
end

function cacha_string(string * nombre);
private;
	byte cr;
	string pls;
	botn[26];
	tam;
begin
	*nombre=cargado;
	signal(ALL_PROCESS,s_sleep);
	graph=new_map(145,105,16);
	map_clear(file,graph,rgb(153,102,0));
	drawing_map(0,graph);
	drawing_color(rgb(64,36,0));
	draw_rect(44,84,138, 99);
	set_center(file,graph,0,0);
	for (cr=97 ; cr<123;cr++)
		boton_s(f_boton,23,10+x*20,10+20*y,&pls,chr(cr),0,0,0,1);
		botn[z]=write(1,10+x*20,(10+20*y),4,chr(cr));
		z++;
		x++;
		if (z mod 7 ==0)
			y++;
			x=0;
		end
	end
	boton_s(f_boton,23,10+x*20,10+20*y,&pls," ",0,0,0,1);
	boton_m(f_boton,5,10+(++x)*20,(10+20*y),&direccion,0,5,0,0,0,1);
	x=0;
	boton_m(f_boton,20,10,(10+20*(++y)),&direccion,0,2,0,0,1,1);
	boton_m(f_boton,22,10+(++x)*20,(10+20*y),&direccion,0,4,0,0,1,1);
	salto=write_var(1,92,93,4,*nombre);
	x=0;y=0;
	while (direccion<>2 and direccion<>4)
		if (direccion==5 )
			tam=len(*nombre);
			if (tam>0)
				*nombre=substr(*nombre,0,tam-1);
			end
			direccion=0;
		end
		if (pls<>"" and text_width(1,*nombre+pls)<94)
			*nombre+=pls;
		end
		pls="";
		frame;
	end
	if (direccion==4)
		*nombre='';
	end
	signal(ALL_PROCESS,s_wakeup);
	delete_text(salto);
	from z=0 to 25;
		delete_text(botn[z]);
	end
	unload_map(file,graph);
	//signal(type edita_mapa,s_freeze);
	signal(id,s_kill_tree);
end


function cnarchivos(int sino,string ruta, string ext,string *archivo_sel);
private
	string *nomb;
	string nombre,archivos[10];
	int direct,ajs,sub,boton[5];
	byte selct;
	ito;
begin
	graph=new_map(140,150,16);
	map_clear(file,graph,rgb(153,102,0));
	drawing_map(0,graph);
	drawing_color(rgb(64,36,0));
	draw_rect(0,0,139, 149);
	drawing_color(rgb(148,84,0));
	draw_rect(1,1,138,148);
	  
	//pintado de los cuadros
	drawing_color(rgb(204,176,124));
	draw_box(10,10,130,110);
	drawing_color(rgb(204,176,124));
	draw_box(10,115,130,125);
	
	drawing_color(rgb(148,84,0));
	draw_rect(10,10,130,110);
	drawing_color(rgb(148,84,0));
	draw_rect(10,115,130,125);
	//fin de pintado de los cuadros
	
	signal(ALL_PROCESS,s_sleep);
	salto=cuantos_archivos(ruta+ext);
	nomb=(string*)alloc(sizeof(string)*salto);
	direct=DIROPEN (ruta+ext);
	repeat
		nombre=DIRREAD(direct);
		if (nombre<>"" and nombre<>"." and nombre<>"..")
			nomb[z++]=nombre;
		end
	until(nombre=="");
	DIRCLOSE (direct);
	x=160;
	y=100;
	for (z=0;z<10;z++)
		if (z<salto)
			archivos[z]=nomb[z];
		end
		write_var(1,103,40+z*9,0,archivos[z]);
	end
	*archivo_sel=archivos[0];
	write_var(1,160,144,4,*archivo_sel);
	boton[0]=boton_m(f_boton,20,218,163,&direccion,0,2,0,0,1,0);
	boton[1]=boton_m(f_boton,22,198,163,&direccion,0,4,0,0,0,1);
	if (sino)
        boton[2]=boton_m(f_boton,5,178,163,&direccion,0,3,0,0,0,1);
        end
	
	boton[3]=boton_m(f_boton,9,110,163,&id2,0,-1,90000,0,0,1);
	boton[4]=boton_m(f_boton,9,130,163,&id2,0,1,270000,0,0,1);
	while (direccion<>2 and direccion<>4)
		if (mouse.x>100 and mouse.x<220 and mouse.y>40 and mouse.y<130 and mouse.left)
			selct=(mouse.y-43)/9;
			if (selct<salto and archivos[selct]<>"")
				*archivo_sel=archivos[selct];
			end
		end
		ajs=salto-10;
		if (ajs>0 and sub<ajs)
			if (id2==1) sub++; 
			end
			for (z=0;z<10 and z<salto;z++)
				archivos[z]=nomb[z+sub];
			end
		end
		if (ajs>0 and sub>0)
			if (id2==-1) sub--; 
			end
			for (z=0;z<10 and z<salto;z++)
				archivos[z]=nomb[z+sub];
			end
		end
		
		if (direccion==3)
			delete_text(all_text);
			if (*archivo_sel<>"" and mensaje(x+10,10,0,mensajes[7]+" "+substr(*archivo_sel,0,10)+"...?"))
				rm(ruta+*archivo_sel);
				for (z=selct+sub;z<salto-1;z++)
					nomb[z]=nomb[z+1];
				end


				nomb[salto]="";

				salto--;
				for (z=0;z<10;z++)
					if (z<salto)
						archivos[z]=nomb[z];
					else
						archivos[z]='';
					end

				end
				*archivo_sel=archivos[0];

			end
			for (z=0;z<10;z++)
			write_var(1,103,40+z*9,0,archivos[z]);
			end
			write_var(1,160,144,4,*archivo_sel);
			direccion=0;
			signal(ALL_PROCESS,s_sleep);
			signal(id,s_wakeup_tree);
			
		end
		id2=0;
		
		frame;
	end
	delete_text(all_text);
	cargado=*archivo_sel;
	free(nomb);
	unload_map(file,graph);
	signal(ALL_PROCESS,s_wakeup);
	from z=0 to 4;
	if (boton[z]<>0)
        	signal(boton[z],s_kill);
	end
	end
	if (direccion==4)
		*archivo_sel='';
	end
	frame;
end

function mensaje(x,y,vr,string mensajer);
private
	ids[2];
begin
	frame(0);
	//  signal_action(s_sleep_tree,S_IGN);
	if (vr)
        signal(ALL_PROCESS,s_freeze);
	else
	signal(ALL_PROCESS,s_sleep);
	end
	id2=text_width(1,mensajer);
	graph=new_map(id2+50,20,16);
	map_clear(file,graph,rgb(153,102,0));
	direccion=write(1,x+20,y,4,mensajer);
	drawing_map(0,graph);
        drawing_color(rgb(64,36,0));
        draw_rect(0,0,id2+49, 19);
        drawing_map(0,scroll_g);
	ids[0]=boton_m(f_boton,20,x-id2/2-10,y,&salto,0,1,0,0,1,0);
	ids[1]=boton_m(f_boton,22,x-id2/2+10,y,&salto,0,0,0,0,1,0);
	salto=2;
	while(salto<>1 and salto<>0)
		frame;
	end
	delete_text(direccion);
	unload_map(file,graph);
	signal(all_process,s_wakeup);
	signal(type edita_mapa,s_freeze);
	signal(ids[0],s_kill);
	signal(ids[1],s_kill);
	frame(0);
	signal(type edita_mapa,s_wakeup);
	//frame;
	//  while (mouse.left) frame; end
	return(salto);
end

function cuantos_archivos(string ext);
private
	vamos,direct;
	string nombre;
begin
	direct=DIROPEN (ext);
	repeat
		nombre=DIRREAD(direct);
		if (FILEINFO.hidden==false and nombre<>"" and nombre<>"." and nombre<>"..")
			vamos++;
		end
	until(nombre=="");
	DIRCLOSE (direct);
	return(vamos);
end

function tamano(byte pointer tam);
private
	botn[6];
	byte a=1,b=8;
begin
	graph=new_map(160,90,16);
	map_clear(file,graph,rgb(153,102,0));
	drawing_map(0,graph);
	drawing_color(rgb(64,36,0));
	draw_rect(0,0,159, 89);
	drawing_color(rgb(148,84,0));
	draw_rect(1,1,158,88);
	draw_rect(81,19,142,80);
	delete_text(0);
	x=160;
	y=100;
	drawing_map(0,scroll_g);
	boton_m(f_boton,20,105,126,&salto,0,1,0,0,1,0);
	salto=2;
	for (z=0;z<3;z++)
		boton_m(f_boton,23,105+z*20,85,&a,0,pow(2,z),0,0,0,1);
		botn[z]=write(1,105+z*20,85,4,'x'+(z+1));
	end
	for (z=3;z<6;z++)
		boton_m(f_boton,23,105+(z-3)*20,105,&b,0,pow(2,z),0,0,0,1);
		botn[z]=write(1,105+(z-3)*20,105,4,'x'+(z-2));
	end
	write(1,160,65,4,mensajes[8]);
	rect(&a,&b,192,105);
	while(salto<>1)
		frame;
	end
	delete_text(direccion);
	unload_map(file,graph);
	*tam=a|b;
	signal(id,s_kill_tree);
end

process rect(byte * xt,byte * yt,x,y);
private
	byte ancho=20, alto=20,aux=1,auy=8;
begin
	graph=new_map(ancho,alto,8);
	map_clear(file,graph,5);
	loop
		if (aux<>*xt or auy<>*yt)
			switch (*xt)
				case 1:
					ancho=20;
				end
				case 2:
					ancho=40;
				end
				case 4:
					ancho=60;
				end
			end
			switch (*yt)
				case 8:
					alto=20;
				end
				case 16:
					alto=40;
				end
				case 32:
					alto=60;
				end
			end
			aux=*xt; 
			auy=*yt;
			unload_map(file,graph);
			graph=new_map(ancho,alto,8);
			map_clear(file,graph,5);
		end
		frame;
	end
	onexit;
	unload_map(file,graph);
end

process pod(x,id2,int *pntr);
begin
	file=f_modl;
	graph=1;
	y=220;
	loop
		direccion=*pntr+id2;
		if (hum_liv>direccion)
			if (++salto%4==0)
				graph++;
			end
			if (graph<direccion*3+1 or graph>(direccion*3+3))
				graph=direccion*3+1;
			end
			
			if (intersec(x-10,y-12,x+10,y+12) and mouse.left )
				if (cp[direccion]==0)
					switch (direccion)
						case 0:
							poder(1); //graph
							cp[direccion]=100;
						end
						case 1:
							poder(20);
							cp[direccion]=100;
						end
						case 2:
							if (dentro(type humo))
								poder(19);
								cp[direccion]=12;
							end
						end
						case 3:
						if (dentro(type humo))
                                                	poder(21);
							cp[direccion]=100;
							end
						end
						case 4:

                                                	poder(22);
							cp[direccion]=80;
						end
						case 5:
							poder(23);
							cp[direccion]=70;
						end
					end
				else
					mse(x,y-25,-50,itoa(cp[direccion]),y-30,10.0);
				end
				while (mouse.left) frame;
				end
			end
		else graph=0;
		end
		frame;
	end
end

process mse(x,y,z,string msg,int direccion,float b);
private
	float a=255;
begin
	graph=write_in_map(1,msg,4);
	salto=100;
	for (;y>direccion;y--)
		alpha=a-=b;
		frame(salto);
	end
	unload_map(file,graph);
end

function texttu(string arch,int salto);
private
string * txt;
string cad[20];
int dat[20];
pos;
cont;
son1[2];
begin
z=text_z+1;
graph=new_map(280,200,8);
map_clear(file,graph,121);
drawing_map(0,graph);
drawing_color(rgb(64,36,0));
draw_rect(0,0,279, 199);
drawing_map(0,scroll_g);
signal(all_process,s_freeze);
txt=(string *)realloc(txt,sizeof(string)*salto);
carga_str(arch,txt, salto);
x=160; y=120;
son1[0]=boton_m(f_boton,9,110,208,&direccion,0,-1,90000,0,0,1);
son.z=text_z;
son1[1]=boton_m(f_boton,9,130,208,&direccion,0,1,270000,0,0,1);
son.z=text_z;
boton_m(f_boton,20,150,208,&direccion,0,3,0,0,1,1);
son.z=text_z;

   for (cont=0;cont<salto and cont<20; cont++)
       dat[cont]=write_var(2,160,30+cont*13,4,cad[cont]);
       cad[cont]=txt[cont];
   end
while (direccion<>3)
if (direccion==1 and (pos+20)<salto) pos++; end
if (direccion==-1 and pos>0) pos--; end
if (direccion<>0)
   for (cont=0;(cont+pos)<salto and cont<20; cont++)
       cad[cont]=txt[cont+pos];
   end
end
direccion=0;
frame;
end
for (cont=0;cont<salto and cont<20; cont++)
    delete_text(dat[cont]);
end
signal(all_process,s_wakeup);
free(txt);
unload_map(file,graph);
frame(0);
signal(son1[0],s_kill);
signal(son1[1],s_kill);
frame(0);
end
