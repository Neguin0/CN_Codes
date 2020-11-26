/*=====================================================================
		Include criada para poupar tempo e trabalho de Programadores/Scripters Pawno.
								_________________________________
								|					      				                |
								|			  	 Criadores:		   	      |
								|	  	 Cromatie & Neguin	 	     |
								|________________________________|

=====================================================================*/

/* 
~~~~~~[Cromatie]~~~~~~~
CN_GetNomeCarros(modeloid);//Pegar o nome do veiculo
CN_GetAvailableSeat(vehicleid, seat_inicio);//Pegar um assento valido que não tenha sido usado
CN_GetVehicleMaxSeats(vehicleid);//pegar o maximo de assento que possui o veiculo
CN_GetInfCarros(modeloid);//Pegar A distancia Frente/tras dos veiculos
CN_GetTipoCar(modeloid);//Pegar o tipo de veiculo que ele e
CN_GetNomePlayer(playerid);//Pegar o nome do jogador
CN_GetVida(playerid);//Pegar a quantia de Vida do jogador
CN_GetNomeArma(armaid);//Pegar o nome da arma

~~~~~~[Neguin]~~~~~~~
CN_SendClientMessageFormat(playerid, color, message, format); //Manda Uma Mensagem Para Todos Formatada
CN_SendClientMessageToAllFormat(color, message, format); //Manda Uma Mensagem Para Todos Formatada
CN_LoopForPlayer(i) //Loop Para Todos Os Players Conectados
CN_Loop(i, len[]) //Loop Simplificado
CN_Freeze(playerid); //Congelar Player
CN_UnFreeze(playerid); //Descongelar Player
MensagemLocal(playerid, color, text[], distancia); //Manda Uma Mensagem Local de Acordo com a distancia colocada
GetDistanceBetweenPlayers(playerid,playerid2); //Obtém distância entre os jogadores
SetPlayerPosEx(playerid, Float: X, Float: Y, Float: Z, Float: Angle, InteriorID); //Seta Float:X, Float:Y, Float:Z, Float:Angle e Interior
KickEx(playerid, timer); //Kicka um player depois de um tempo determinado
*/

#include <a_samp>

#if defined _CN_Codes_included
	#endinput
#endif
#define _CN_Codes_included

static FALSE = false;
#define CN_SendClientMessageFormat(%0,%1,%2,%3) do{new _string[128]; format(_string,sizeof(_string),%2,%3); SendClientMessage(%0,%1,_string);} while(FALSE)
#define CN_SendClientMessageToAllFormat(%0,%1,%2) do{new _string[128]; format(_string,sizeof(_string),%1,%2); SendClientMessageToAll(%0,_string);} while(FALSE)

#define CN_LoopForPlayer(%1) new %1; %1 = GetPlayerPoolSize(); for( ; %1 > -1; %1--) if(IsPlayerConnected(%1))
#define CN_Loop(%0,%1)	for(new %0 = 0; %0 < %1; %0++)

#define CN_Freeze(%0) \
		TogglePlayerControllable(%0,false)

#define CN_UnFreeze(%0) \
		TogglePlayerControllable(%0,true)

stock MensagemLocal(playerid, cor, text[], distancia)
{
	for(new i=0; i <= MAX_PLAYERS; i++)
		if(GetDistanceBetweenPlayers(playerid, i) <= distancia)
	{
		if(GetPlayerVirtualWorld(playerid) == GetPlayerVirtualWorld(i))
		{
			new string[128];
			format(string, 128, text);
			SendClientMessage(i,cor,string);
		}
	}
	return 1;
}

stock GetDistanceBetweenPlayers(playerid,playerid2)
{
	new Float:x1,Float:y1,Float:z1,Float:x2,Float:y2,Float:z2;
	new Float:tmpdis;
	GetPlayerPos(playerid,x1,y1,z1);
	GetPlayerPos(playerid2,x2,y2,z2);
	tmpdis = floatsqroot(floatpower(floatabs(floatsub(x2,x1)),2)+floatpower(floatabs(floatsub(y2,y1)),2)+floatpower(floatabs(floatsub(z2,z1)),2));
	return floatround(tmpdis);
}

stock SetPlayerPosEx(playerid, Float: X, Float: Y, Float: Z, Float: Angle, InteriorID)
{
    SetPlayerPos(playerid, Float: X, Float: Y, Float: Z);
    SetPlayerFacingAngle(playerid, Float: Angle);
    SetPlayerInterior(playerid, InteriorID);
    return 1;
}

stock KickEx(playerid, timer);
{
	SetTimerEx("KickarEx", timer, "u", playerid);
	return 1;
}

forward KickarEx(playerid);
public KickarEx(playerid) return Kick(playerid);

stock CN_GetNomeArma(armaid){
	new CN_Nome[32];
	GetWeaponName(armaid, CN_Nome, sizeof(CN_Nome));
	return CN_Nome;
}

forward Float:CN_GetVida(playerid);
public Float:CN_GetVida(playerid){
	new Float:CN_Vida;
	GetPlayerHealth(playerid,CN_Vida);
	return CN_Vida;
}

stock CN_GetNomePlayer(playerid){
    new CN_Nome[MAX_PLAYER_NAME];
	GetPlayerName(playerid, CN_Nome, sizeof(CN_Nome));
	return CN_Nome;
}


new CN_NomeCarros[212][32] ={
    {"Landstalker"},{"Bravura"},{"Buffalo"},{"Linerunner"},{"Perrenial"},{"Sentinel"},{"Dumper"},
    {"Firetruck"},{"Trashmaster"},{"Stretch"},{"Manana"},{"Infernus"},{"Voodoo"},{"Pony"},{"Mule"},
    {"Cheetah"},{"Ambulance"},{"Leviathan"},{"Moonbeam"},{"Esperanto"},{"Taxi"},{"Washington"},
    {"Bobcat"},{"Mr Whoopee"},{"BF Injection"},{"Hunter"},{"Premier"},{"Enforcer"},{"Securicar"},
    {"Banshee"},{"Predator"},{"Bus"},{"Rhino"},{"Barracks"},{"Hotknife"},{"Trailer 1"},{"Previon"},
    {"Coach"},{"Cabbie"},{"Stallion"},{"Rumpo"},{"RC Bandit"},{"Romero"},{"Packer"},{"Monster"},
    {"Admiral"},{"Squalo"},{"Seasparrow"},{"Pizzaboy"},{"Tram"},{"Trailer 2"},{"Turismo"},
    {"Speeder"},{"Reefer"},{"Tropic"},{"Flatbed"},{"Yankee"},{"Caddy"},{"Solair"},{"Berkley's RC Van"},
    {"Skimmer"},{"PCJ-600"},{"Faggio"},{"Freeway"},{"RC Baron"},{"RC Raider"},{"Glendale"},{"Oceanic"},
    {"Sanchez"},{"Sparrow"},{"Patriot"},{"Quad"},{"Coastguard"},{"Dinghy"},{"Hermes"},{"Sabre"},
    {"Rustler"},{"ZR-350"},{"Walton"},{"Regina"},{"Comet"},{"BMX"},{"Burrito"},{"Camper"},{"Marquis"},
    {"Baggage"},{"Dozer"},{"Maverick"},{"News Chopper"},{"Rancher"},{"FBI Rancher"},{"Virgo"},{"Greenwood"},
    {"Jetmax"},{"Hotring"},{"Sandking"},{"Blista Compact"},{"Police Maverick"},{"Boxville"},{"Benson"},
    {"Mesa"},{"RC Goblin"},{"Hotring Racer A"},{"Hotring Racer B"},{"Bloodring Banger"},{"Rancher"},
    {"Super GT"},{"Elegant"},{"Journey"},{"Bike"},{"Mountain Bike"},{"Beagle"},{"Cropdust"},{"Stunt"},
    {"Tanker"}, {"Roadtrain"},{"Nebula"},{"Majestic"},{"Buccaneer"},{"Shamal"},{"Hydra"},{"FCR-900"},
    {"NRG-500"},{"HPV1000"},{"Cement Truck"},{"Tow Truck"},{"Fortune"},{"Cadrona"},{"FBI Truck"},
    {"Willard"},{"Forklift"},{"Tractor"},{"Combine"},{"Feltzer"},{"Remington"},{"Slamvan"},
    {"Blade"},{"Freight"},{"Streak"},{"Vortex"},{"Vincent"},{"Bullet"},{"Clover"},{"Sadler"},
    {"Firetruck LA"},{"Hustler"},{"Intruder"},{"Primo"},{"Cargobob"},{"Tampa"},{"Sunrise"},{"Merit"},
    {"Utility"},{"Nevada"},{"Yosemite"},{"Windsor"},{"Monster A"},{"Monster B"},{"Uranus"},{"Jester"},
    {"Sultan"},{"Stratum"},{"Elegy"},{"Raindance"},{"RC Tiger"},{"Flash"},{"Tahoma"},{"Savanna"},
    {"Bandito"},{"Freight Flat"},{"Streak Carriage"},{"Kart"},{"Mower"},{"Duneride"},{"Sweeper"},
    {"Broadway"},{"Tornado"},{"AT-400"},{"DFT-30"},{"Huntley"},{"Stafford"},{"BF-400"},{"Newsvan"},
    {"Tug"},{"Trailer 3"},{"Emperor"},{"Wayfarer"},{"Euros"},{"Hotdog"},{"Club"},{"Freight Carriage"},
    {"Trailer 3"},{"Andromada"},{"Dodo"},{"RC Cam"},{"Launch"},{"Police Car (LSPD)"},{"Police Car (SFPD)"},
    {"Police Car (LVPD)"},{"Police Ranger"},{"Picador"},{"S.W.A.T. Van"},{"Alpha"},{"Phoenix"},{"Glendale"},
    {"Sadler"},{"Luggage Trailer A"},{"Luggage Trailer B"},{"Stair Trailer"},{"Boxville"},{"Farm Plow"},
    {"Utility Trailer"}
};
stock CN_GetNomeCarros(modeloid){
	new CN_Nome[32];
	if(modeloid >= 400 && modeloid <= 612) CN_Nome = CN_NomeCarros[modeloid-400];
	else CN_Nome = "Nenhum";
	return CN_Nome;
}

new Float:CN_InfFTCarros[] ={
//0, 1 , 2 , 3 , 4  	, 5 , 6 , 7 , 8 , 9
2.0,2.5,2.5,4.5,5.2		,2.5,5.5,4.5,5.0,4.0,      //0  (400~409)
2.5,2.5,2.5,2.5,2.7 	,2.5,3.0,0.0,2.5,2.5,      //1  (410~419)
2.5,2.5,2.5,2.5,1.5		,2.5,0.0,3.5,2.5,2.5,      //2  (420~429)
4.5,6.0,5.0,4.0,2.0		,0.0,2.5,5.5,2.5,2.5,      //3  (430~439)
2.5,0.5,3.0,6.0,3.0		,2.5,5.0,0.0,1.0,5.0,      //4  (440~449)
5.0,2.5,4.5,5.0,6.0		,4.0,3.5,1.0,2.5,2.5,      //5  (450~459)
0.0,0.0,0.0,0.0,0.0		,0.0,2.5,2.5,0.0,0.0,      //6  (460~469)
2.5,0.0,4.0,2.0,2.5		,2.5,0.0,2.5,2.5,2.5,      //7  (470~479)
2.5,0.0,2.5,3.0,7.0		,2.0,3.5,0.0,0.0,3.0,      //8  (480~489)
3.5,2.5,2.5,4.5,2.5		,2.5,2.5,0.0,3.0,2.5,      //9  (490~499)
0.0,0.0,2.5,2.5,2.5		,2.5,2.5,2.5,3.0,0.0,      //10 (500~509)

0.0,0.0,0.0,0.0,4.5		,4.5,2.5,3.0,2.5,0.0,      //11 (510~519)
0.0,0.0,0.0,0.0,4.0		,3.0,2.5,2.5,2.5,2.5,      //12 (520~529)
1.5,1.5,1.5,2.5,3.0		,2.5,2.5,0.0,0.0,2.0,      //13 (530~539)
2.5,2.5,2.5,2.5,4.0		,2.0,2.5,2.5,0.0,2.5,      //14 (540~549)
2.5,2.5,3.0,0.0,2.5		,2.5,2.5,2.5,2.5,2.5,      //15 (550~559)
2.5,2.5,2.5,0.0,0.0		,2.0,2.5,3.0,2.0,0.0,      //16 (560~569)
0.0,1.0,1.0,3.5,2.0		,2.5,2.5,0.0,5.0,2.5,      //17 (570~579)
2.5,0.0,2.5,1.5,0.0		,2.5,0.0,2.5,3.5,2.5,      //18 (580~589)
0.0,0.0,0.0,0.0,0.0		,5.0,2.5,2.5,2.5,2.5,      //19 (590~599)
0.0,2.5,2.5,2.5,2.5		,2.5,2.5,2.5,2.5,2.5,      //20 (600~609)
2.5,3.0,2.5,2.5,2.5		,2.5,0.0,0.0,0.0,3.0,      //21 (610~619)
0.0,0.0,0.0	     							  	   //22 (613)
};

forward Float:CN_GetInfCarros(modeloid);
public Float:CN_GetInfCarros(modeloid){
	new Float:CN_Code;
	if(modeloid >= 400 && modeloid <= 612) CN_Code = CN_InfFTCarros[modeloid-400];
	else CN_Code = -1.0;
	return CN_Code;
}

new CN_TypeCarr[]={
// [1.0 = CARRO] , [2.0 = GOVERNO]  , [3.0 = VAN,PICAPE] , [4.0 = SERV] , [5.0 = MOTO] ,  [6.0 = AVIÃO] ,  [7.0 = HELICOP] ,
// [8.0 = TRAILER] ,  [9.0 = Caminhão/Carreta] ,   [1.1 = TREM,RC VEH] ,  [1.2 = BARCO] ,
//1,2,3,4       ,5,6,7,8,9
1,1,1,9,1		,1,9,2,4,1,      //0  (400~409)
1,1,1,3,9		,1,2,7,3,1,      //1  (410~419)
4,1,3,9,1		,7,1,2,2,1,      //2  (420~429)
12,4,2,2,1		,8,1,4,4,1,      //3  (430~439)
3,11,1,9,1		,1,12,7,5,11,    //4  (440~449)
8,1,12,12,12	,9,9,1,1,3,      //5  (450~459)
6,5,5,5,11		,11,1,1,5,7,     //6  (460~469)
2,5,12,12,1		,1,6,1,3,1,      //7  (470~479)
1,5,3,1,12		,4,9,7,7,1,      //8  (480~489)
2,1,1,12,1		,1,1,7,9,9,      //9  (490~499)
5,11,1,1,1		,1,1,1,1,5,      //10 (500~509)

5,6,6,6,9		,9,1,1,1,6,      //11 (510~519)
6,5,5,2,9		,4,1,1,2,1,      //12 (520~529)
3,9,9,1,1		,1,1,11,11,12,   //13 (530~539)
1,1,1,3,2		,1,1,1,7,1,      //14 (540~549)
1,1,4,6,3		,1,1,1,1,1,      //15 (550~559)
1,1,1,7,11		,11,1,1,1,11,    //16 (560~569)
11,1,3,9,4		,1,1,6,1,1,      //17 (570~579)
1,5,3,3,8		,1,5,1,9,1,      //18 (580~589)
11,8,6,6,11		,12,2,2,2,2,     //19 (590~599)
5,2,1,1,1		,3,8,8,8,9,      //20 (600~609)
8,1,1,1,1		,1,8,8,8,3,      //21 (610~619)
11,11,11
};

stock CN_GetTipoCar(modeloid){
	if(modeloid >= 400 && modeloid <= 612) return CN_TypeCarr[modeloid-400];
	else return -1;
}

stock CN_GetAvailableSeat(vehicleid, start = 1){//nativa: GetAvailableSeat(400,0)
	new seats = GetVehicleMaxSeats(vehicleid);
	for (new i = start; i < seats; i ++) if (!IsVehicleSeatUsed(vehicleid, i)) return i;
	return -1;
}
stock CN_GetVehicleMaxSeats(vehicleid){
    static const g_arrMaxSeats[] = {
		4, 2, 2, 2, 4, 4, 1, 2, 2, 4, 2, 2, 2, 4, 2, 2, 4, 2, 4, 2, 4, 4, 2, 2, 2, 1, 4, 4, 4, 2,
		1, 7, 1, 2, 2, 0, 2, 7, 4, 2, 4, 1, 2, 2, 2, 4, 1, 2, 1, 0, 0, 2, 1, 1, 1, 2, 2, 2, 4, 4,
		2, 2, 2, 2, 1, 1, 4, 4, 2, 2, 4, 2, 1, 1, 2, 2, 1, 2, 2, 4, 2, 1, 4, 3, 1, 1, 1, 4, 2, 2,
		4, 2, 4, 1, 2, 2, 2, 4, 4, 2, 2, 1, 2, 2, 2, 2, 2, 4, 2, 1, 1, 2, 1, 1, 2, 2, 4, 2, 2, 1,
		1, 2, 2, 2, 2, 2, 2, 2, 2, 4, 1, 1, 1, 2, 2, 2, 2, 7, 7, 1, 4, 2, 2, 2, 2, 2, 4, 4, 2, 2,
		4, 4, 2, 1, 2, 2, 2, 2, 2, 2, 4, 4, 2, 2, 1, 2, 4, 4, 1, 0, 0, 1, 1, 2, 1, 2, 2, 1, 2, 4,
		4, 2, 4, 1, 0, 4, 2, 2, 2, 2, 0, 0, 7, 2, 2, 1, 4, 4, 4, 2, 2, 2, 2, 2, 4, 2, 0, 0, 0, 4,
		0, 0
	};
	new model = GetVehicleModel(vehicleid);
	if (model >= 400 && model <= 611) return g_arrMaxSeats[model - 400];
	return 0;
}
stock CN_IsVehicleSeatUsed(vehicleid, seat){
	for(new i=0; i<MAX_PLAYERS; i++)	if(IsPlayerConnected(i))
			if (IsPlayerInVehicle(i, vehicleid) && GetPlayerVehicleSeat(i) == seat) return 1;
	return 0;
}